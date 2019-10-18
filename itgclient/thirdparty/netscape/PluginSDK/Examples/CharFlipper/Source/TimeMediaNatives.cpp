//------------------------------------------------------------
// TMPNative.cpp
//
// Native code implementation of the TimeMediaPlugin
//------------------------------------------------------------
#include "npapi.h"
#include "CCharFlipper.h"

#define IMPLEMENT_TimeMediaPlugin
#include "TimeMediaPlugin.h"

//------------------------------------------------------------
// IntializeJavaClass()
//
// Called from NPP_GetJavaClass in CNetscapePlugin.cpp
//------------------------------------------------------------
jref InitializeJavaClass(void)
{
	jref theRef = NULL;
	// LiveConnect is not working on 68k machines, so we need to disable it in our code.
#ifndef __MC68K__
	JRIEnv* env = NPN_GetJavaEnv();
  if(env == NULL)
    return NULL;

	theRef = (jref)TimeMediaPlugin::_use( env );

	netscape_plugin_Plugin::_use( env );
	TimeMediaPlugin::_register(env);
#endif /* !__MC68K__ */
	return theRef;
}

/*** public native SetSource (Ljava/net/URL;)V ***/
extern JRI_PUBLIC_API(void)
native_TimeMediaPlugin_SetSourceNative(JRIEnv* env, struct TimeMediaPlugin* self, struct java_lang_String *a)
{
	NPP instance = (NPP) (self->getPeer(env));
	CCharFlipper* flipper = (CCharFlipper*) instance->pdata;

	const char* theURL = JRI_GetStringUTFChars( env, a );
	NPN_GetURL( instance, theURL, NULL );
}

/*** public native Start ()V ***/
extern JRI_PUBLIC_API(void)
native_TimeMediaPlugin_Start(JRIEnv* env, struct TimeMediaPlugin* self)
{
	NPP instance = (NPP) (self->getPeer(env));
	CCharFlipper* flipper = (CCharFlipper*) instance->pdata;
	
	flipper->StartAtFrame( 0 );
}

/*** public native Stop ()V ***/
extern JRI_PUBLIC_API(void)
native_TimeMediaPlugin_Stop(JRIEnv* env, struct TimeMediaPlugin* self)
{
	NPP instance = (NPP) (self->getPeer(env));
	CCharFlipper* flipper = (CCharFlipper*) instance->pdata;
	
	flipper->SetRunning( FALSE );
}

/*** public native IsRunning ()Z ***/
extern JRI_PUBLIC_API(jbool)
native_TimeMediaPlugin_IsRunning(JRIEnv* env, struct TimeMediaPlugin* self)
{
	NPP instance = (NPP) (self->getPeer(env));
	CCharFlipper* flipper = (CCharFlipper*) instance->pdata;
	
	return flipper->GetRunning();
}

/*** public native Loop (Z)V ***/
extern JRI_PUBLIC_API(void)
native_TimeMediaPlugin_Loop(JRIEnv* env, struct TimeMediaPlugin* self, jbool a)
{
	NPP instance = (NPP) (self->getPeer(env));
	CCharFlipper* flipper = (CCharFlipper*) instance->pdata;
	
	flipper->SetLooping( a );
}

/*** public native IsLooping ()Z ***/
extern JRI_PUBLIC_API(jbool)
native_TimeMediaPlugin_IsLooping(JRIEnv* env, struct TimeMediaPlugin* self)
{
	NPP instance = (NPP) (self->getPeer(env));
	CCharFlipper* flipper = (CCharFlipper*) instance->pdata;
	
	return flipper->GetLooping();
}

/*** public native SetSpeed (I)V ***/
extern JRI_PUBLIC_API(void)
native_TimeMediaPlugin_SetSpeed(JRIEnv* env, struct TimeMediaPlugin* self, jint a)
{
	NPP instance = (NPP) (self->getPeer(env));
	CCharFlipper* flipper = (CCharFlipper*) instance->pdata;
	
	flipper->SetSpeed( a );
}

/*** public native GetSpeed ()I ***/
extern JRI_PUBLIC_API(jint)
native_TimeMediaPlugin_GetSpeed(JRIEnv* env, struct TimeMediaPlugin* self)
{
	NPP instance = (NPP) (self->getPeer(env));
	CCharFlipper* flipper = (CCharFlipper*) instance->pdata;
	
	return flipper->GetSpeed();
}
