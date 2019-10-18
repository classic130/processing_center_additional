/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/sc/policymodule/include/Attic/vspmutilP.h,v 1.1.2.1 2001/09/06 22:32:20 ajayaram Exp $
 */

/*-----------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1999. All rights reserved.        |
| This is an unpublished work protected as such under copyright law.     |
| This work contains proprietary, confidential, and trade secret         |
| information of VeriSign, Inc.  Use, disclosure or reproduction without |
| the expressed written authorization of VeriSign, Inc.  is prohibited.  |
\-----------------------------------------------------------------------*/


#ifndef _VSPMUTILP_H_
#define _VSPMUTILP_H_

#include "vsnvp.h"
#include "vspmutil.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VERSION_STR	"Version"
#define MAJ_VER_LEN	2
#define MIN_VER_LEN	2

#ifdef  __cplusplus
}
#endif

//////////////////////////////////////////////////////////////////////////////////
class VSContainer : public VSNode
//      The VSContainer is a node that has a list of children
//////////////////////////////////////////////////////////////////////////////////
{
public:
        VSContainer(VSNode *parent, const char *name, unsigned int nameLen);
        ~VSContainer(void);

        // Return the first container
        VSNode *firstContainer(void);

        // Return the next container
        VSNode *nextContainer(void);

        // Return the first item
        VSNode *firstItem(void);

        // Return the next item
        VSNode *nextItem(void);

        // find a container in the list with the matching name
        VSNode *searchContainer(const char *name);

        // find an item in the list with the matching name
        VSNode *searchItem(const char *name);

        // return number of container
        unsigned int countContainer(void) const { return _containerCount; }

        // return number of item
        unsigned int countItem(void) const { return _itemCount; }

        // add this container to the list
        void addContainer(VSNode *node);

        // add this item to the list
        void addItem(VSNode *node);

        // delete a container from the list
        void deleteContainer(VSNode *node);

        // delete an item from the list
        void deleteItem(VSNode *node);

        // delete a container at a given index from the list
        void deleteContainerAt(unsigned int index);

        // delete an item at a given index from the list
        void deleteItemAt(unsigned int index);

        // insert this container at a given index
        void insertContainer(VSNode *node, unsigned int index);

        // insert this item at a given index
        void insertItem(VSNode *node, unsigned int index);

	// set the major version number
	void setMajorVersion(unsigned short maj) { _major = maj; }

	// get the major version number
	unsigned short getMajorVersion(void) const { return _major; }

	// set the minor version number
	void setMinorVersion(unsigned short min) { _minor = min; }

	// get the minor version number
	unsigned short getMinorVersion(void) const { return _minor; }

protected:
        virtual void printMe (FILE *fp, int level) const;

	virtual VSNode *duplicateMe(VSNode *dad);

	virtual int parseVersion(const char * verStr,
                                 unsigned int verStrLen,
                                 unsigned short *maj,
                                 unsigned short *min);

        VSNode      *_containerList;
        VSNode      *_currentContainer;
        unsigned int _containerCount;

        VSNode      *_itemList;
        VSNode      *_currentItem;
        unsigned int _itemCount;

	unsigned short _major;
	unsigned short _minor;

};

#endif  /* _VSPMUTILP_H_ */
