//*********************************************************************
//*                  Microsoft Windows                               **
//*            Copyright(c) Microsoft Corp., 1996-1997               **
//*********************************************************************

#ifndef __XMLDOMDID_H__
#define __XMLDOMDID_H__

#define DISPID_XOBJ_MIN                 0x00010000
#define DISPID_XOBJ_MAX                 0x0001FFFF
#define DISPID_XOBJ_BASE                DISPID_XOBJ_MIN


#define  DISPID_DOM_NODE                  DISPID_XOBJ_BASE
#define  DISPID_DOM_NODE_TYPE             DISPID_DOM_NODE  +  1
#define  DISPID_DOM_NODE_NAME             DISPID_DOM_NODE  +  2
#define  DISPID_DOM_NODE_VALUE            DISPID_DOM_NODE  +  3
#define  DISPID_DOM_NODE_PARENT           DISPID_DOM_NODE  +  4
#define  DISPID_DOM_NODE_SETATTRIBUTE     DISPID_DOM_NODE  +  5
#define  DISPID_DOM_NODE_GETATTRIBUTE     DISPID_DOM_NODE  +  6
#define  DISPID_DOM_NODE_REMOVEATTRIBUTE  DISPID_DOM_NODE  +  7
#define  DISPID_DOM_NODE_SPECIFIED        DISPID_DOM_NODE  +  8
#define  DISPID_DOM_NODE_INSERT           DISPID_DOM_NODE  +  9
#define  DISPID_DOM_NODE_REMOVE           DISPID_DOM_NODE  +  10
#define  DISPID_DOM_NODE_REPLACE          DISPID_DOM_NODE  +  11
#define  DISPID_DOM_NODE_ATTRIBUTES       DISPID_DOM_NODE  +  12
#define  DISPID_DOM_NODE_CHILDREN         DISPID_DOM_NODE  +  13

#define  DISPID_XMLDOM_NODE                    DISPID_DOM_NODE + 100
#define  DISPID_XMLDOM_NODE_DEFINITION         DISPID_XMLDOM_NODE  +  1
#define  DISPID_XMLDOM_NODE_QUALIFIEDNAME      DISPID_XMLDOM_NODE  +  2
#define  DISPID_XMLDOM_NODE_NAMESPACE          DISPID_XMLDOM_NODE  +  3
#define  DISPID_XMLDOM_NODE_NODETYPEDVALUE     DISPID_XMLDOM_NODE  +  4
#define  DISPID_XMLDOM_NODE_GETTYPEDATTRIBUTE  DISPID_XMLDOM_NODE  +  5
#define  DISPID_XMLDOM_NODE_SETTYPEDATTRIBUTE  DISPID_XMLDOM_NODE  +  6
#define  DISPID_XMLDOM_NODE_DATATYPE           DISPID_XMLDOM_NODE  +  7

#define  DISPID_DOM_NODELIST              DISPID_XMLDOM_NODE  + 100
#define  DISPID_DOM_NODELIST_LENGTH       DISPID_DOM_NODELIST  +  1
#define  DISPID_DOM_NODELIST_ITEM         DISPID_DOM_NODELIST  +  2
#define  DISPID_DOM_NODELIST_NEXT         DISPID_DOM_NODELIST  +  3
#define  DISPID_DOM_NODELIST_CURRENT      DISPID_DOM_NODELIST  +  4
#define  DISPID_DOM_NODELIST_PREVIOUS     DISPID_DOM_NODELIST  +  5
#define  DISPID_DOM_NODELIST_MOVETO       DISPID_DOM_NODELIST  +  6
#define  DISPID_DOM_NODELIST_MOVETONODE   DISPID_DOM_NODELIST  +  7
#define  DISPID_DOM_NODELIST_NEWENUM      DISPID_DOM_NODELIST  +  8

#define  DISPID_DOM_DOCUMENT                   DISPID_DOM_NODELIST  + 100
#define  DISPID_DOM_DOCUMENT_DOCUMENTTYPE      DISPID_DOM_DOCUMENT + 1
#define  DISPID_DOM_DOCUMENT_DOCUMENTELEMENT   DISPID_DOM_DOCUMENT + 2
#define  DISPID_DOM_DOCUMENT_DOCUMENTNODE      DISPID_DOM_DOCUMENT + 3
#define  DISPID_DOM_DOCUMENT_CREATENODE        DISPID_DOM_DOCUMENT + 4

#define  DISPID_XMLDOM_DOCUMENT                    DISPID_DOM_DOCUMENT + 100
#define  DISPID_XMLDOM_DOCUMENT_GETNODE            DISPID_XMLDOM_DOCUMENT + 1
#define  DISPID_XMLDOM_DOCUMENT_NAMESPACES         DISPID_XMLDOM_DOCUMENT + 2
#define  DISPID_XMLDOM_DOCUMENT_LOAD               DISPID_XMLDOM_DOCUMENT + 3
#define  DISPID_XMLDOM_DOCUMENT_READYSTATE         DISPID_XMLDOM_DOCUMENT + 4
#define  DISPID_XMLDOM_DOCUMENT_LASTERROR          DISPID_XMLDOM_DOCUMENT + 5
#define  DISPID_XMLDOM_DOCUMENT_URL                DISPID_XMLDOM_DOCUMENT + 6
#define  DISPID_XMLDOM_DOCUMENT_ASYNC              DISPID_XMLDOM_DOCUMENT + 7
#define  DISPID_XMLDOM_DOCUMENT_ABORT              DISPID_XMLDOM_DOCUMENT + 8
#define  DISPID_XMLDOM_DOCUMENT_SAVENODE           DISPID_XMLDOM_DOCUMENT + 9
#define  DISPID_XMLDOM_DOCUMENT_LOADXML            DISPID_XMLDOM_DOCUMENT + 10
#define  DISPID_XMLDOM_DOCUMENT_DEFINITION         DISPID_XMLDOM_DOCUMENT  +  11
#define  DISPID_XMLDOM_DOCUMENT_QUALIFIEDNAME      DISPID_XMLDOM_DOCUMENT  +  12
#define  DISPID_XMLDOM_DOCUMENT_NAMESPACE          DISPID_XMLDOM_DOCUMENT  +  13
#define  DISPID_XMLDOM_DOCUMENT_NODETYPEDVALUE     DISPID_XMLDOM_DOCUMENT  +  14
#define  DISPID_XMLDOM_DOCUMENT_GETTYPEDATTRIBUTE  DISPID_XMLDOM_DOCUMENT  +  15
#define  DISPID_XMLDOM_DOCUMENT_SETTYPEDATTRIBUTE  DISPID_XMLDOM_DOCUMENT  +  16
#define  DISPID_XMLDOM_DOCUMENT_DATATYPE           DISPID_XMLDOM_DOCUMENT  +  17

#define  DISPID_DOM_ERROR                      DISPID_XMLDOM_DOCUMENT  + 100
#define  DISPID_DOM_ERROR_ERRORCODE            DISPID_DOM_ERROR  +  1
#define  DISPID_DOM_ERROR_URL                  DISPID_DOM_ERROR  +  2
#define  DISPID_DOM_ERROR_REASON               DISPID_DOM_ERROR  +  3
#define  DISPID_DOM_ERROR_SRCTEXT              DISPID_DOM_ERROR  +  4
#define  DISPID_DOM_ERROR_LINE                 DISPID_DOM_ERROR  +  5
#define  DISPID_DOM_ERROR_LINEPOS              DISPID_DOM_ERROR  +  6
#define  DISPID_DOM_ERROR_FILEPOS              DISPID_DOM_ERROR  +  7

#endif // __XMLDOMDID_H__
