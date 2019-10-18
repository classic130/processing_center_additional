/*
$Revision: 1.1.2.1 $
$Header: /cvs/itgclient/client/apps/fet/vsfe/h/Attic/vsnvp.h,v 1.1.2.1 2000/02/25 01:38:10 aranade Exp $
*/

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifndef _VSNVP_H_
#define _VSNVP_H_

#include <stdio.h>

typedef enum
{
	VS_NAME_VALUE_NODE,
	VS_SESSION_NODE
} VSNodeType;

typedef enum
{
	VS_DUP_ONE,
	VS_DUP_ALL
} VSDuplicationFlag;


//////////////////////////////////////////////////////////////////////////////////
class VSNode
//	VSNode represents a node in the tree. It has link to the parent node.
//	It also has links with the previous and next siblings.
//	The first node in the list has its previous node link to NULL.
//	The last node in the list has its next node link to NULL.
//////////////////////////////////////////////////////////////////////////////////
{
public:
	VSNode(VSNode *dad, VSNodeType type, const char *name, int nameLen);

	// delete the whole list
	virtual ~VSNode(void);

	// return the parent node
	VSNode *dad(void)            { return _dad;  }

	// return the next sibling
	VSNode *next(void)           { return _next; }

	// return the previous sibling
	VSNode *prev(void)           { return _prev; }

	// return the type of this node
	int type(void) const         { return _type; }

	// return the name of this node
	const char *name(void) const { return _name; }

	// set the name of this node
	void setName(const char *name);

	// find a node in the list with the matching name
	VSNode *find(const char *name);

	// insert the node at the end of the list
	void insert(VSNode *next);

	// insert the node right after the current node
	void insertAt(VSNode *next);

	// remove itself from the list
	void remove(VSNode *node);

	// print me and my next sibling
	void print (FILE *fp, int level, int printSibling = 1) const;

	// duplicate me and my next sibling
	VSNode * duplicate (VSNode *dad, VSDuplicationFlag flag);

protected:
	// print my content
	virtual void printMe (FILE *fp, int level) const {}

	virtual VSNode *duplicateMe(VSNode *dad) { return NULL; }

private:
	VSNode    *_dad;
	VSNode    *_next;
	VSNode    *_prev;
	char      *_name;
	VSNodeType _type;
};


//////////////////////////////////////////////////////////////////////////////////
class VSNvp : public VSNode
//	The VSNvp is a node with a value assigned to it.
//////////////////////////////////////////////////////////////////////////////////
{
public:
	VSNvp(VSNode *dad, const char *name, unsigned int nameLen,
		const unsigned char *value = NULL, unsigned int valueLen = 0);
	~VSNvp(void);

	unsigned int valueLen(void) const { return _valueLen; }
	const unsigned char *value(void) const { return _value; }
	void setValue (const unsigned char * value, unsigned int valueLen);

protected:
	virtual void printMe (FILE *fp, int level) const;

	virtual VSNode *duplicateMe(VSNode *dad);

private:
	unsigned char *_value;
	unsigned int   _valueLen;
};


//////////////////////////////////////////////////////////////////////////////////
class VSSection : public VSNode
//	The VSSection is a node that has a list of children
//////////////////////////////////////////////////////////////////////////////////
{
public:
	VSSection(VSNode *dad, const char *name, unsigned int nameLen);
	~VSSection(void);

	// Return the first child
	VSNode *first(void);

	// Return the next child
	VSNode *next(void);

	// find a child in the list with the matching name
	VSNode *search(const char *name);

	// return number of children
	unsigned int count(void) const { return _count; }

	// add this child to the list
	void add(VSNode *node);

protected:
	virtual void printMe (FILE *fp, int level) const;

	virtual VSNode *duplicateMe(VSNode *dad);

private:
	VSNode      *_nvpList;
	VSNode      *_current;
	unsigned int _count;
};

#endif
