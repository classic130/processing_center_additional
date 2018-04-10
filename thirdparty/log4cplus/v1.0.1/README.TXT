
File description:

  archive/log4cplus-1.0.1.tar.gz - original source code
  log4cplus-1.0.1-docs.tar.gz    - original document

  log4cplus-1.0.1-src.tar.gz     - Locally modified version to produce 
                                   binary delivery
  log4cplus-1.0.1-bin.zip - Built library and header files as well as document. 
                            Only window library is built now.

The code in log4cplus-1.0.1.zip includes following minor changes over 
log4cplus v1.0.1 original code in order to build on windows.

1. Header files:
   
     include/config.h and include/config-macosx.h 
     
   Several macro definition is removed for WIN32 platform with #ifndef WIN32
   added, e.g., HAVE_GETTIMEOFDAY
   
2. MSVC 6.0 makefile for log4cplus_static CODE-GENERATION flag is changed
   from "Multithreaded" to "Multithreaded DLL".

There is no document change.
