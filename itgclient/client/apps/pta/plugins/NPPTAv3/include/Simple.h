/* DO NOT EDIT THIS FILE - it is machine generated */
#include "jri.h"

/* Header for class Simple */

#ifndef _Simple_H_
#define _Simple_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct java_lang_String;
struct java_lang_Object;
struct java_lang_Class;

/*******************************************************************************
 * Class Simple
 ******************************************************************************/

typedef struct Simple Simple;

#define classname_Simple	"Simple"

#define class_Simple(env) \
	((struct java_lang_Class*)JRI_FindClass(env, classname_Simple))

/*******************************************************************************
 * Public Methods
 ******************************************************************************/

#ifdef DEBUG

/*** public static fact (I)I ***/
extern JRI_PUBLIC_API(jint)
Simple_fact(JRIEnv* env, struct java_lang_Class* clazz, jint a);

/*** public native printToStdout (Ljava/lang/String;)V ***/
extern JRI_PUBLIC_API(void)
Simple_printToStdout(JRIEnv* env, struct Simple* self, struct java_lang_String *a);

/*** public native getDispatch (Ljava/lang/Object;)V ***/
extern JRI_PUBLIC_API(void)
Simple_getDispatch(JRIEnv* env, struct Simple* self, struct java_lang_Object *a);

/*** public doit (Ljava/lang/String;)V ***/
extern JRI_PUBLIC_API(void)
Simple_doit(JRIEnv* env, struct Simple* self, struct java_lang_String *a);

#else /* !DEBUG */

/*** public static fact (I)I ***/
#define Simple_fact(env, clazz, a) \
	((jint)JRI_CallStaticMethodInt(env)(env, JRI_CallStaticMethod_op, clazz, methodID_Simple_fact, a))

/*** public native printToStdout (Ljava/lang/String;)V ***/
#define Simple_printToStdout(env, obj, a) \
	((void)JRI_CallMethod(env)(env, JRI_CallMethod_op, obj, methodID_Simple_printToStdout, a))

/*** public native getDispatch (Ljava/lang/Object;)V ***/
#define Simple_getDispatch(env, obj, a) \
	((void)JRI_CallMethod(env)(env, JRI_CallMethod_op, obj, methodID_Simple_getDispatch, a))

/*** public doit (Ljava/lang/String;)V ***/
#define Simple_doit(env, obj, a) \
	((void)JRI_CallMethod(env)(env, JRI_CallMethod_op, obj, methodID_Simple_doit, a))

#endif /* !DEBUG*/

/*** public static fact (I)I ***/
extern JRIMethodID FAR methodID_Simple_fact;
#define name_Simple_fact	"fact"
#define sig_Simple_fact 	"(I)I"
#define use_Simple_fact(env, clazz)	\
	(methodID_Simple_fact =	\
		JRI_GetStaticMethodID(env, clazz,	\
			name_Simple_fact,	\
			sig_Simple_fact))
#define unuse_Simple_fact(env, clazz)	\
	(methodID_Simple_fact = JRIUninitialized)

/*** public native printToStdout (Ljava/lang/String;)V ***/
extern JRIMethodID FAR methodID_Simple_printToStdout;
#define name_Simple_printToStdout	"printToStdout"
#define sig_Simple_printToStdout 	"(Ljava/lang/String;)V"
#define use_Simple_printToStdout(env, clazz)	\
	(methodID_Simple_printToStdout =	\
		JRI_GetMethodID(env, clazz,	\
			name_Simple_printToStdout,	\
			sig_Simple_printToStdout))
#define unuse_Simple_printToStdout(env, clazz)	\
	(methodID_Simple_printToStdout = JRIUninitialized)

/*** public native getDispatch (Ljava/lang/Object;)V ***/
extern JRIMethodID FAR methodID_Simple_getDispatch;
#define name_Simple_getDispatch	"getDispatch"
#define sig_Simple_getDispatch 	"(Ljava/lang/Object;)V"
#define use_Simple_getDispatch(env, clazz)	\
	(methodID_Simple_getDispatch =	\
		JRI_GetMethodID(env, clazz,	\
			name_Simple_getDispatch,	\
			sig_Simple_getDispatch))
#define unuse_Simple_getDispatch(env, clazz)	\
	(methodID_Simple_getDispatch = JRIUninitialized)

/*** public doit (Ljava/lang/String;)V ***/
extern JRIMethodID FAR methodID_Simple_doit;
#define name_Simple_doit	"doit"
#define sig_Simple_doit 	"(Ljava/lang/String;)V"
#define use_Simple_doit(env, clazz)	\
	(methodID_Simple_doit =	\
		JRI_GetMethodID(env, clazz,	\
			name_Simple_doit,	\
			sig_Simple_doit))
#define unuse_Simple_doit(env, clazz)	\
	(methodID_Simple_doit = JRIUninitialized)

/*******************************************************************************
 * IMPLEMENTATION SECTION: 
 * Define the IMPLEMENT_Simple symbol 
 * if you intend to implement the native methods of this class. This 
 * symbol makes the private and protected methods available. You should 
 * also call the register_Simple routine 
 * to make your native methods available.
 ******************************************************************************/

extern JRI_PUBLIC_API(struct java_lang_Class*)
use_Simple(JRIEnv* env);

extern JRI_PUBLIC_API(void)
unuse_Simple(JRIEnv* env);

extern JRI_PUBLIC_API(struct java_lang_Class*)
register_Simple(JRIEnv* env);

extern JRI_PUBLIC_API(void)
unregister_Simple(JRIEnv* env);

#ifdef IMPLEMENT_Simple

/*******************************************************************************
 * Native Methods: 
 * These are the signatures of the native methods which you must implement.
 ******************************************************************************/

/*** public native printToStdout (Ljava/lang/String;)V ***/
extern JRI_PUBLIC_API(void)
native_Simple_printToStdout(JRIEnv* env, struct Simple* self, struct java_lang_String *a);

/*** public native getDispatch (Ljava/lang/Object;)V ***/
extern JRI_PUBLIC_API(void)
native_Simple_getDispatch(JRIEnv* env, struct Simple* self, struct java_lang_Object *a);

/*******************************************************************************
 * Implementation Field Accessors: 
 * You should only use these from within the native method definitions.
 ******************************************************************************/

#ifdef DEBUG

/*** count I ***/
extern JRI_PUBLIC_API(jint)
get_Simple_count(JRIEnv* env, Simple* obj);
extern JRI_PUBLIC_API(void)
set_Simple_count(JRIEnv* env, Simple* obj, jint v);

#else /* !DEBUG */

/*** count I ***/
#define get_Simple_count(env, obj) \
	(JRI_GetFieldInt(env, obj, fieldID_Simple_count))
#define set_Simple_count(env, obj, v) \
	JRI_SetFieldInt(env, obj, fieldID_Simple_count, v)

#endif /* !DEBUG*/

extern JRIFieldID FAR fieldID_Simple_count;
#define name_Simple_count	"count"
#define sig_Simple_count 	"I"
#define use_Simple_count(env, clazz)	\
	(fieldID_Simple_count =	\
		JRI_GetFieldID(env, clazz,	\
			name_Simple_count,	\
			sig_Simple_count))
#define unuse_Simple_count(env, clazz)	\
		(fieldID_Simple_count = JRIUninitialized)

/*******************************************************************************
 * Implementation Methods: 
 * You should only use these from within the native method definitions.
 ******************************************************************************/

#ifdef DEBUG

/*** <init> ()V ***/
extern JRI_PUBLIC_API(struct Simple*)
Simple_new(JRIEnv* env, struct java_lang_Class* clazz);

#else /* !DEBUG */

/*** <init> ()V ***/
#define Simple_new(env, clazz)	\
	((struct Simple*)JRI_NewObject(env)(env, JRI_NewObject_op, clazz, methodID_Simple_new))

#endif /* !DEBUG*/

/*** <init> ()V ***/
extern JRIMethodID FAR methodID_Simple_new;
#define name_Simple_new	"<init>"
#define sig_Simple_new 	"()V"
#define use_Simple_new(env, clazz)	\
	(methodID_Simple_new =	\
		JRI_GetMethodID(env, clazz,	\
			name_Simple_new,	\
			sig_Simple_new))
#define unuse_Simple_new(env, clazz)	\
	(methodID_Simple_new = JRIUninitialized)

#endif /* IMPLEMENT_Simple */

#ifdef __cplusplus
} /* extern "C" */

/*******************************************************************************
 * C++ Definitions
 ******************************************************************************/

#include "netscape_plugin_Plugin.h"

struct Simple : virtual public netscape_plugin_Plugin {

	static struct java_lang_Class* _use(JRIEnv* env) {
		return use_Simple(env);
	}

	static void _unuse(JRIEnv* env) {
		unuse_Simple(env);
	}

	static struct java_lang_Class* _register(JRIEnv* env) {
		return register_Simple(env);
	}

	static void _unregister(JRIEnv* env) {
		unregister_Simple(env);
	}

	static struct java_lang_Class* _class(JRIEnv* env) {
		return class_Simple(env);
	}

	/* Public Methods */
	/*** public static fact (I)I ***/
	static jint fact(JRIEnv* env, struct java_lang_Class* clazz, jint a) {
		return Simple_fact(env, clazz, a);
	}

	/*** public native printToStdout (Ljava/lang/String;)V ***/
	void printToStdout(JRIEnv* env, struct java_lang_String *a) {
		Simple_printToStdout(env, this, a);
	}

	/*** public native getDispatch (Ljava/lang/Object;)V ***/
	void getDispatch(JRIEnv* env, struct java_lang_Object *a) {
		Simple_getDispatch(env, this, a);
	}

	/*** public doit (Ljava/lang/String;)V ***/
	void doit(JRIEnv* env, struct java_lang_String *a) {
		Simple_doit(env, this, a);
	}

#ifdef IMPLEMENT_Simple

#endif /* IMPLEMENT_Simple */
};

#endif /* __cplusplus */

#endif /* Class Simple */
