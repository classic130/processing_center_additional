#ifdef WIN32
/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define if you don't have vprintf but do have _doprnt.  */
/* #undef HAVE_DOPRNT */

/* Define if you have <unistd.h>.  */
/* #undef HAVE_UNISTD_H */

/* Define if you have the vprintf function.  */
#define HAVE_VPRINTF 1

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if your processor stores words with the most significant
   byte first (like Motorola and SPARC, unlike Intel and VAX).  */
/* #undef WORDS_BIGENDIAN */

/* #undef ENABLE_MEM_CHECK */
/* #undef ENABLE_MEM_PROFILE */

#define REALLOC_0_WORKS 1

#define G_COMPILED_WITH_DEBUGGING "minimum"
/* #undef G_THREADS_ENABLED */

/* #undef GLIB_SIZEOF_GMUTEX */
/* #undef GLIB_BYTE_CONTENTS_GMUTEX */

/* #undef HAVE_BROKEN_WCTYPE */
/* #undef HAVE_DOPRNT */
#define HAVE_FLOAT_H 1
/* #undef HAVE_GETPWUID_R */
/* #undef HAVE_GETPWUID_R_POSIX */
#define HAVE_LIMITS_H 1
/* #undef HAVE_LONG_DOUBLE */
/* #undef HAVE_POLL */
/* #undef HAVE_PTHREAD_COND_TIMEDWAIT_POSIX */
/* #undef HAVE_PTHREAD_GETSPECIFIC_POSIX */
/* #undef HAVE_PTHREAD_MUTEX_TRYLOCK_POSIX */
/* #undef HAVE_PWD_H */
/* #undef HAVE_SYS_PARAM_H */
/* #undef HAVE_SYS_POLL_H */
/* #undef HAVE_SYS_SELECT_H */
/* #undef HAVE_SYS_TIME_H */
/* #undef HAVE_SYS_TIMES_H */
#define HAVE_STRERROR 1
/* #undef HAVE_STRSIGNAL */
/* #undef HAVE_UNISTD_H */
/* #undef HAVE_VALUES_H */
#define HAVE_WCHAR_H 1
#define HAVE_WCTYPE_H 1

#define NO_FD_SET 1
/* #undef NO_SYS_ERRLIST */
#define NO_SYS_SIGLIST 1
#define NO_SYS_SIGLIST_DECL 1

/* #undef G_VA_COPY */
/* #undef G_VA_COPY_AS_ARRAY */
#define G_HAVE___INLINE 1
/* #undef G_HAVE___INLINE__ */
/* #undef G_HAVE_INLINE */

#define GLIB_MAJOR_VERSION 1
#define GLIB_MINOR_VERSION 2
#define GLIB_MICRO_VERSION 10
#define GLIB_INTERFACE_AGE 10
#define GLIB_BINARY_AGE 10

#define G_THREAD_SOURCE "gthread-none.c"

/* The number of bytes in a char.  */
#define SIZEOF_CHAR 1

/* The number of bytes in a int.  */
#define SIZEOF_INT 4

/* The number of bytes in a long.  */
#define SIZEOF_LONG 4

/* The number of bytes in a long long.  */
#define SIZEOF_LONG_LONG 0

/* The number of bytes in a short.  */
#define SIZEOF_SHORT 2

/* The number of bytes in a void *.  */
#define SIZEOF_VOID_P 4

/* Define if you have the atexit function.  */
#define HAVE_ATEXIT 1

/* Define if you have the localtime_r function.  */
/* #undef HAVE_LOCALTIME_R */

/* Define if you have the lstat function.  */
/* #undef HAVE_LSTAT */

/* Define if you have the memmove function.  */
#define HAVE_MEMMOVE 1

/* Define if you have the on_exit function.  */
/* #undef HAVE_ON_EXIT */

/* Define if you have the poll function.  */
/* #undef HAVE_POLL */

/* Define if you have the rand_r function.  */
/* #undef HAVE_RAND_R */

/* Define if you have the strcasecmp function.  */
/* #undef HAVE_STRCASECMP */

/* Define if you have the strerror function.  */
#define HAVE_STRERROR 1

/* Define if you have the strncasecmp function.  */
/* #undef HAVE_STRNCASECMP */

/* Define if you have the strsignal function.  */
/* #undef HAVE_STRSIGNAL */

/* Define if you have the vsnprintf function.  */
/* #undef HAVE_VSNPRINTF */

/* Define if you have the <float.h> header file.  */
#define HAVE_FLOAT_H 1

/* Define if you have the <limits.h> header file.  */
#define HAVE_LIMITS_H 1

/* Define if you have the <pwd.h> header file.  */
/* #undef HAVE_PWD_H */

/* Define if you have the <sys/param.h> header file.  */
/* #undef HAVE_SYS_PARAM_H */

/* Define if you have the <sys/poll.h> header file.  */
/* #undef HAVE_SYS_POLL_H */

/* Define if you have the <sys/select.h> header file.  */
/* #undef HAVE_SYS_SELECT_H */

/* Define if you have the <sys/time.h> header file.  */
/* #undef HAVE_SYS_TIME_H */

/* Define if you have the <sys/times.h> header file.  */
/* #undef HAVE_SYS_TIMES_H */

/* Define if you have the <unistd.h> header file.  */
/* #undef HAVE_UNISTD_H */

/* Define if you have the <values.h> header file.  */
/* #undef HAVE_VALUES_H */

/* Define if you have the w library (-lw).  */
/* #undef HAVE_LIBW */

#else
/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define if you don't have vprintf but do have _doprnt.  */
/* #undef HAVE_DOPRNT */

/* Define if you have <unistd.h>.  */
#define HAVE_UNISTD_H 1

/* Define if you have the vprintf function.  */
#define HAVE_VPRINTF 1

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if your processor stores words with the most significant
   byte first (like Motorola and SPARC, unlike Intel and VAX).  */
#define WORDS_BIGENDIAN 1

/* #undef ENABLE_MEM_CHECK */
/* #undef ENABLE_MEM_PROFILE */

/* #undef REALLOC_0_WORKS */

#define G_COMPILED_WITH_DEBUGGING "minimum"
/* #undef G_THREADS_ENABLED */

#define GLIB_SIZEOF_GMUTEX 24
#define GLIB_BYTE_CONTENTS_GMUTEX 0,0,0,0,0,0,77,88,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

/* #undef HAVE_BROKEN_WCTYPE */
/* #undef HAVE_DOPRNT */
#define HAVE_FLOAT_H 1
#define HAVE_GETPWUID_R 1
/* #undef HAVE_GETPWUID_R_POSIX */
#define HAVE_LIMITS_H 1
/* #undef HAVE_LONG_DOUBLE */
#define HAVE_POLL 1
/* #undef HAVE_PTHREAD_COND_TIMEDWAIT_POSIX */
/* #undef HAVE_PTHREAD_GETSPECIFIC_POSIX */
/* #undef HAVE_PTHREAD_MUTEX_TRYLOCK_POSIX */
#define HAVE_PWD_H 1
#define HAVE_SYS_PARAM_H 1
#define HAVE_SYS_POLL_H 1
#define HAVE_SYS_SELECT_H 1
#define HAVE_SYS_TIME_H 1
#define HAVE_SYS_TIMES_H 1
#define HAVE_STRERROR 1
#define HAVE_STRSIGNAL 1
#define HAVE_UNISTD_H 1
#define HAVE_VALUES_H 1
#define HAVE_WCHAR_H 1
#define HAVE_WCTYPE_H 1

/* #undef NO_FD_SET */
/* #undef NO_SYS_ERRLIST */
#define NO_SYS_SIGLIST 1
#define NO_SYS_SIGLIST_DECL 1

#define G_VA_COPY __va_copy
/* #undef G_VA_COPY_AS_ARRAY */
#define G_HAVE___INLINE 1
#define G_HAVE___INLINE__ 1
#define G_HAVE_INLINE 1

#define GLIB_MAJOR_VERSION 1
#define GLIB_MINOR_VERSION 2
#define GLIB_MICRO_VERSION 10
#define GLIB_INTERFACE_AGE 10
#define GLIB_BINARY_AGE 10

#define G_THREAD_SOURCE "gthread-solaris.c"

/* The number of bytes in a char.  */
#define SIZEOF_CHAR 1

/* The number of bytes in a int.  */
#define SIZEOF_INT 4

/* The number of bytes in a long.  */
#define SIZEOF_LONG 4

/* The number of bytes in a long long.  */
#define SIZEOF_LONG_LONG 8

/* The number of bytes in a short.  */
#define SIZEOF_SHORT 2

/* The number of bytes in a void *.  */
#define SIZEOF_VOID_P 4

/* Define if you have the atexit function.  */
#define HAVE_ATEXIT 1

/* Define if you have the localtime_r function.  */
#define HAVE_LOCALTIME_R 1

/* Define if you have the lstat function.  */
#define HAVE_LSTAT 1

/* Define if you have the memmove function.  */
#define HAVE_MEMMOVE 1

/* Define if you have the on_exit function.  */
/* #undef HAVE_ON_EXIT */

/* Define if you have the poll function.  */
#define HAVE_POLL 1

/* Define if you have the rand_r function.  */
#define HAVE_RAND_R 1

/* Define if you have the strcasecmp function.  */
#define HAVE_STRCASECMP 1

/* Define if you have the strerror function.  */
#define HAVE_STRERROR 1

/* Define if you have the strncasecmp function.  */
#define HAVE_STRNCASECMP 1

/* Define if you have the strsignal function.  */
#define HAVE_STRSIGNAL 1

/* Define if you have the vsnprintf function.  */
#define HAVE_VSNPRINTF 1

/* Define if you have the <float.h> header file.  */
#define HAVE_FLOAT_H 1

/* Define if you have the <limits.h> header file.  */
#define HAVE_LIMITS_H 1

/* Define if you have the <pwd.h> header file.  */
#define HAVE_PWD_H 1

/* Define if you have the <sys/param.h> header file.  */
#define HAVE_SYS_PARAM_H 1

/* Define if you have the <sys/poll.h> header file.  */
#define HAVE_SYS_POLL_H 1

/* Define if you have the <sys/select.h> header file.  */
#define HAVE_SYS_SELECT_H 1

/* Define if you have the <sys/time.h> header file.  */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <sys/times.h> header file.  */
#define HAVE_SYS_TIMES_H 1

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the <values.h> header file.  */
#define HAVE_VALUES_H 1

/* Define if you have the w library (-lw).  */
/* #undef HAVE_LIBW */
#endif
