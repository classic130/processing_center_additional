#ifndef _DEFINES
#define _DEFINES

#if defined(EOL_CRLF)
#define EOL "\r\n"
#elif defined(EOL_LF)
#define EOL "\n"
#else
#error "Must define EOL_CRLF OR EOL_LF" 
#endif 

#endif // _DEFINES