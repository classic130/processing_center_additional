/*
$Revision: 1.1.2.1 $
$Header: /cvs/itgclient/server/apps/sc/policymodule/sources/Attic/vscontainer.cpp,v 1.1.2.1 2001/09/06 22:32:29 ajayaram Exp $
*/

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1999. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "vspmutilP.h"


//////////////////////////////////////////////////////////////////////////////////
VSContainer::VSContainer(VSNode *parent, const char *name, unsigned int nameLen) :
//////////////////////////////////////////////////////////////////////////////////
        VSNode(parent, VS_SESSION_NODE, name, nameLen)
{
        _containerList = _currentContainer = NULL;
        _itemList = _currentItem = NULL;
        _containerCount = 0;
        _itemCount = 0;
	_major = 0;
	_minor = 0;
}


//////////////////////////////////////////////////////////////////////////////////
VSContainer::~VSContainer(void)
//////////////////////////////////////////////////////////////////////////////////
{
        if (_containerList)
                delete _containerList;

        if (_itemList)
                delete _itemList;

}


//////////////////////////////////////////////////////////////////////////////////
VSNode *VSContainer::firstContainer(void)
//////////////////////////////////////////////////////////////////////////////////
{
        return _currentContainer = _containerList;
}


//////////////////////////////////////////////////////////////////////////////////
VSNode *VSContainer::nextContainer(void)
//////////////////////////////////////////////////////////////////////////////////
{
        if (_currentContainer)
                return _currentContainer = _currentContainer->next();
        else
                return NULL;
}


//////////////////////////////////////////////////////////////////////////////////
VSNode *VSContainer::firstItem(void)
//////////////////////////////////////////////////////////////////////////////////
{
        return _currentItem = _itemList;
}


//////////////////////////////////////////////////////////////////////////////////
VSNode *VSContainer::nextItem(void)
//////////////////////////////////////////////////////////////////////////////////
{
        if (_currentItem)
                return _currentItem = _currentItem->next();
        else
                return NULL;
}


//////////////////////////////////////////////////////////////////////////////////
void VSContainer::addContainer(VSNode *node)
//////////////////////////////////////////////////////////////////////////////////
{
        if (_containerList)
                _containerList->insert(node);
        else
                _containerList = _currentContainer = node;
        _containerCount++;
}


//////////////////////////////////////////////////////////////////////////////////
void VSContainer::deleteContainer(VSNode *node)
//////////////////////////////////////////////////////////////////////////////////
{
	if (_containerList) {
		_containerList->remove(node);
		delete node;
		_containerCount--;
	}
}


//////////////////////////////////////////////////////////////////////////////////
void VSContainer::addItem(VSNode *node)
//////////////////////////////////////////////////////////////////////////////////
{

	VSNvp *item = (VSNvp *)node;
	int status = 0;
	unsigned short maj = 0, min = 0;

        if (_itemList)
                _itemList->insert(node);
        else
                _itemList = _currentItem = node;
        _itemCount++;

	if (strcmp(node->name(), VERSION_STR) == 0) {
		status = parseVersion((const char*)item->value(), item->valueLen(), &maj, &min);
		if (!status) {
			setMajorVersion(maj);
			setMinorVersion(min);
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////
void VSContainer::deleteContainerAt(unsigned int index)
//////////////////////////////////////////////////////////////////////////////////
{
	VSNode *trvCnt = _containerList;

	if (! trvCnt) {
		return;
	}

	if (index >= _containerCount)
		return;

	int i;
	for (i = 0; i < index; i++) {

		trvCnt = trvCnt->next();

	}

	trvCnt->remove(trvCnt);
	delete trvCnt;

	_containerCount--;

}


//////////////////////////////////////////////////////////////////////////////////
void VSContainer::deleteItem(VSNode *node)
//////////////////////////////////////////////////////////////////////////////////
{
	if (_itemList) {
		_itemList->remove(node);
		delete node;
		_itemCount--;
	}
}


//////////////////////////////////////////////////////////////////////////////////
void VSContainer::deleteItemAt(unsigned int index)
//////////////////////////////////////////////////////////////////////////////////
{
	VSNvp *trvItm = (VSNvp *)_itemList;

	if (! trvItm) {
		return;
	}

	if (index >= _itemCount)
		return;

	int i;
	for (i = 0; i < index; i++) {

		trvItm = (VSNvp *)trvItm->next();

	}

	trvItm->remove((VSNode *)trvItm);
	delete trvItm;

	_itemCount--;

}


//////////////////////////////////////////////////////////////////////////////////
void VSContainer::insertContainer(VSNode *node, unsigned int index)
//////////////////////////////////////////////////////////////////////////////////
{
	VSContainer *trvCnt = (VSContainer *) _containerList;

	if (! trvCnt) {
		addContainer(node);
		return;
	}

	if (index >= _containerCount)
		return;

	int i;
	for (i = 0; i < index; i++) {

		trvCnt = (VSContainer *) trvCnt->next();

	}

	trvCnt->insertAt(node);
	_containerCount++;

}


//////////////////////////////////////////////////////////////////////////////////
void VSContainer::insertItem(VSNode *node, unsigned int index)
//////////////////////////////////////////////////////////////////////////////////
{
	VSNvp *trvItm = (VSNvp *) _itemList;

	if (! trvItm) {
		addItem(node);
		return;
	}

	if (index >= _itemCount)
		return;

	int i;
	for (i = 0; i < index; i++) {

		trvItm = (VSNvp *) trvItm->next();

	}

	trvItm->insertAt(node);
	_itemCount++;

}


//////////////////////////////////////////////////////////////////////////////////
VSNode *VSContainer::searchContainer(const char *name)
//////////////////////////////////////////////////////////////////////////////////
{
        if (_containerList)
                return _containerList->find(name);
        return NULL;
}


//////////////////////////////////////////////////////////////////////////////////
VSNode *VSContainer::searchItem(const char *name)
//////////////////////////////////////////////////////////////////////////////////
{
        if (_itemList)
                return _itemList->find(name);
        return NULL;
}


//////////////////////////////////////////////////////////////////////////////////
void VSContainer::printMe (FILE *fp, int level) const
//////////////////////////////////////////////////////////////////////////////////
{
        int i;

        fprintf(fp, " { # %d sub containers\n", _containerCount);
	if (_itemList)
		_itemList->print(fp, level+1);
        if (_containerList)
                _containerList->print(fp, level+1);
        for (i=0; i<level; i++)
                fprintf(fp, "    ");
        fprintf(fp, "}\n");

}


//////////////////////////////////////////////////////////////////////////////////
VSNode * VSContainer::duplicateMe (VSNode *dad)
//////////////////////////////////////////////////////////////////////////////////
{

        VSContainer *meNode = NULL;
        VSNode *newList = NULL;
        VSNode *trev = NULL;
        VSNode *newNode = NULL;
        //int i;

        meNode = new VSContainer(dad, name(), strlen(name()));
	meNode->_major = _major;
	meNode->_minor = _minor;
        if (_containerList) {
                newNode = _containerList->duplicate(meNode, VS_DUP_ALL);
                meNode->_containerCount = _containerCount;
                meNode->_containerList = newNode;
                meNode->_currentContainer = newNode;
        }

	newNode = NULL;
        if (_itemList) {
                newNode = _itemList->duplicate(meNode, VS_DUP_ALL);
                meNode->_itemCount = _itemCount;
                meNode->_itemList = newNode;
                meNode->_currentItem = newNode;
        }

        return (VSNode *)meNode;

}


//////////////////////////////////////////////////////////////////////////////////
int VSContainer::parseVersion(const char * verStr, unsigned int verStrLen,
                              unsigned short *maj, unsigned short *min)
//////////////////////////////////////////////////////////////////////////////////
{
	int status = 0;
	int i;
	unsigned int verLen = MAJ_VER_LEN + MIN_VER_LEN;
	unsigned short major = 0;
	unsigned short minor = 0;

	if (! verStr)
		return VSPM_INVALID_VERSION;

	if (verStrLen != verLen)
		return VSPM_INVALID_VERSION;
	
	for (i = 0; i < MAJ_VER_LEN; i++) {
		major = major * 10 + (*(verStr++) - '0');
	}

	for (i = 0; i < MIN_VER_LEN; i++) {
		minor = minor * 10 + (*(verStr++) - '0');
	}

	*maj = major;
	*min = minor;
	
	return status;
}
