/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/sc/policymodule/sources/Attic/vsnvp.cpp,v 1.1.2.1 2001/09/06 22:32:31 ajayaram Exp $
 */

static char *_VSNVP_C= "$Id: vsnvp.cpp,v 1.1.2.1 2001/09/06 22:32:31 ajayaram Exp $";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsnvp.h"


//////////////////////////////////////////////////////////////////////////////////
VSNode::VSNode(VSNode *dad, VSNodeType type, const char *name, int nameLen)
//////////////////////////////////////////////////////////////////////////////////
{
	_dad = dad;
	_next = _prev = NULL;
	_type = type;
	_name = (char *)malloc(nameLen + 1);
	if (_name)
	{
		memcpy(_name, name, nameLen);
		_name[nameLen] = '\0';
	}
}


//////////////////////////////////////////////////////////////////////////////////
VSNode::~VSNode(void)
//////////////////////////////////////////////////////////////////////////////////
{
	if (_next)
		delete _next;
	if (_name)
		free(_name);
}


//////////////////////////////////////////////////////////////////////////////////
void VSNode::insert(VSNode *next)
//////////////////////////////////////////////////////////////////////////////////
{
	if (_next)
		_next->insert(next);
	else
	{
		next->_prev = this;
		//next->_next = _next;
		_next = next;
	}
}


//////////////////////////////////////////////////////////////////////////////////
void VSNode::insertAt(VSNode *node)
//////////////////////////////////////////////////////////////////////////////////
{
	node->_prev = this;
	node->_next = _next;
	_next = node;

	if (node->_next) {
		node->_next->_prev = node;
	}
}


//////////////////////////////////////////////////////////////////////////////////
VSNode *VSNode::find(const char *name)
//////////////////////////////////////////////////////////////////////////////////
{
	if (!strcmp(_name, name))
		return this;
	else if (_next)
		return _next->find(name);
	else
		return NULL;
}


//////////////////////////////////////////////////////////////////////////////////
void VSNode::remove(VSNode *node)
//////////////////////////////////////////////////////////////////////////////////
{

	if (this == node) {
		if (_next) {
			_next->_prev = _prev;
			_next = NULL;
		}

		if (_prev) {
			_prev->_next = _next;
			_prev = NULL;
		}
	}
	else if (_next) {
		_next->remove(node);
	}

}


//////////////////////////////////////////////////////////////////////////////////
void VSNode::setName(const char *name)
//////////////////////////////////////////////////////////////////////////////////
{
	int nameLen = 0;
	char *oldName = _name;

	if (name) {
		nameLen = strlen(name);
		_name = (char *)malloc(nameLen + 1);
		if (_name)
		{
			memcpy(_name, name, nameLen);
			_name[nameLen] = '\0';

			free(oldName);
		}
		else {
			_name = oldName;
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////
void VSNode::print(FILE *fp, int level, int nextSibling) const
//////////////////////////////////////////////////////////////////////////////////
{
	int i;

	for (i=0; i<level; i++)
		fprintf(fp, "    ");
	fprintf(fp,"%s", _name);
	printMe(fp, level);
	if (_next && nextSibling)
		_next->print(fp, level);
}


//////////////////////////////////////////////////////////////////////////////////
VSNode * VSNode::duplicate(VSNode *dad, VSDuplicationFlag flag)
//////////////////////////////////////////////////////////////////////////////////
{
	VSNode *node;
	VSNode *nextDup;

	node = duplicateMe(dad);
	if (_next && (flag == VS_DUP_ALL)) {
		nextDup = _next->duplicate(dad, flag);
		node->insert(nextDup);
	}
	
	return node;
}


//////////////////////////////////////////////////////////////////////////////////
VSNvp::VSNvp(VSNode *dad, const char *name, unsigned int nameLen,
			 const unsigned char *value, unsigned int valueLen) :
//////////////////////////////////////////////////////////////////////////////////
    VSNode(dad, VS_NAME_VALUE_NODE, name, nameLen)
{
	_valueLen = valueLen;
	if (value)
	{
		_value = (unsigned char *)malloc(valueLen + 1);
		memcpy(_value, value, valueLen);
		_value[valueLen] = '\0';
	}
	else
		_value = NULL;
}


//////////////////////////////////////////////////////////////////////////////////
void VSNvp::setValue(const unsigned char *value, unsigned int valueLen)
//////////////////////////////////////////////////////////////////////////////////
{
	unsigned char *oldValue = _value;

	if (value) {
		_value = (unsigned char *)malloc(valueLen + 1);
		if (_value)
		{
			memcpy(_value, value, valueLen);
			_value[valueLen] = '\0';
			_valueLen = valueLen;

			free(oldValue);
		}
		else {
			_value = oldValue;
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////
VSNvp::~VSNvp(void)
//////////////////////////////////////////////////////////////////////////////////
{
	if (_value)
		free(_value);
}


//////////////////////////////////////////////////////////////////////////////////
void VSNvp::printMe(FILE *fp, int level) const 
//////////////////////////////////////////////////////////////////////////////////
{
	unsigned i;

	fprintf(fp, ":");
	for (i=0; i<_valueLen; i++)
		fprintf(fp, "%c", _value[i]);
	fprintf(fp, "\n");
}


//////////////////////////////////////////////////////////////////////////////////
VSNode * VSNvp::duplicateMe(VSNode *dad)
//////////////////////////////////////////////////////////////////////////////////
{
	VSNvp *meNode = NULL;

	meNode = new VSNvp(dad, name(), strlen(name()), _value, _valueLen);

	return (VSNode *)meNode;

}


//////////////////////////////////////////////////////////////////////////////////
VSSection::VSSection(VSNode *dad, const char *name, unsigned int nameLen) :
//////////////////////////////////////////////////////////////////////////////////
	VSNode(dad, VS_SESSION_NODE, name, nameLen)
{
	_nvpList = _current = NULL;
	_count = 0;
}


//////////////////////////////////////////////////////////////////////////////////
VSSection::~VSSection(void)
//////////////////////////////////////////////////////////////////////////////////
{
	if (_nvpList)
		delete _nvpList;
}


//////////////////////////////////////////////////////////////////////////////////
VSNode *VSSection::first(void)
//////////////////////////////////////////////////////////////////////////////////
{
	return _current = _nvpList;
}


//////////////////////////////////////////////////////////////////////////////////
VSNode *VSSection::next(void)
//////////////////////////////////////////////////////////////////////////////////
{
	if (_current)
		return _current = _current->next();
	else
		return NULL;
}


//////////////////////////////////////////////////////////////////////////////////
void VSSection::add(VSNode *node)
//////////////////////////////////////////////////////////////////////////////////
{
	if (_nvpList)
		_nvpList->insert(node);
	else
		_nvpList = _current = node;
	_count++;
}


//////////////////////////////////////////////////////////////////////////////////
VSNode *VSSection::search(const char *name)
//////////////////////////////////////////////////////////////////////////////////
{
	if (_nvpList)
		return _nvpList->find(name);
	return NULL;
}


//////////////////////////////////////////////////////////////////////////////////
void VSSection::printMe (FILE *fp, int level) const
//////////////////////////////////////////////////////////////////////////////////
{
	int i;

	fprintf(fp, " { # %d nodes\n", _count);
	if (_nvpList)
		_nvpList->print(fp, level+1);
	for (i=0; i<level; i++)
		fprintf(fp, "    ");
	fprintf(fp, "}\n");
}


//////////////////////////////////////////////////////////////////////////////////
VSNode * VSSection::duplicateMe (VSNode *dad)
//////////////////////////////////////////////////////////////////////////////////
{

	VSSection *meNode = NULL;
	VSNode *newList = NULL;
	VSNode *trev = NULL;
	VSNode *newNode = NULL;
	//int i;

	meNode = new VSSection(dad, name(), strlen(name()));
	if (_nvpList) {
		newNode = _nvpList->duplicate(meNode, VS_DUP_ALL);
		meNode->_count = _count;
		meNode->_nvpList = newNode;
		meNode->_current = newNode;
	}

	return (VSNode *)meNode;

}
