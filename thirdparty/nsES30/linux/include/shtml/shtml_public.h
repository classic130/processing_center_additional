#ifndef _SHTML_PUBLIC_H_
#define _SHTML_PUBLIC_H_

#include "netsite.h"

NSPR_BEGIN_EXTERN_C
#define TagUserData void*
typedef TagUserData (*ShtmlTagInstanceLoad)(const char* tag, 
                                            pblock*, const char*, size_t); 
typedef void (*ShtmlTagInstanceUnload)(TagUserData); 
typedef int (*ShtmlTagExecuteFunc)(pblock*, Session*, Request*, 
                                   TagUserData, TagUserData); 
typedef TagUserData (*ShtmlTagPageLoadFunc)(pblock* pb, Session*, Request*); 
typedef void (*ShtmlTagPageUnLoadFunc)(TagUserData);


NSAPI_PUBLIC int shtml_add_tag(const char* tag,
                               ShtmlTagInstanceLoad ctor,
                               ShtmlTagInstanceUnload dtor,
                               ShtmlTagExecuteFunc execFn, 
                               ShtmlTagPageLoadFunc pageLoadFn,
                               ShtmlTagPageUnLoadFunc pageUnLoadFn);

NSAPI_PUBLIC int shtml_add_html_tag(const char* tag,
                               ShtmlTagInstanceLoad ctor,
                               ShtmlTagInstanceUnload dtor,
                               ShtmlTagExecuteFunc execFn, 
                               ShtmlTagPageLoadFunc pageLoadFn,
                               ShtmlTagPageUnLoadFunc pageUnLoadFn);
NSPR_END_EXTERN_C

#endif /* _SHTML_PUBLIC_H_ */
