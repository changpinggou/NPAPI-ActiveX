

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Wed May 13 14:33:47 2015
 */
/* Compiler settings for .\QQGameAssistPlugin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __QQGameAssistPlugin_i_h__
#define __QQGameAssistPlugin_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __QQGameHallAssist_FWD_DEFINED__
#define __QQGameHallAssist_FWD_DEFINED__

#ifdef __cplusplus
typedef class QQGameHallAssist QQGameHallAssist;
#else
typedef struct QQGameHallAssist QQGameHallAssist;
#endif /* __cplusplus */

#endif 	/* __QQGameHallAssist_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __QQGameAssistPluginLib_LIBRARY_DEFINED__
#define __QQGameAssistPluginLib_LIBRARY_DEFINED__

/* library QQGameAssistPluginLib */
/* [helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_QQGameAssistPluginLib,0xEDF9E233,0x1D93,0x43D0,0x92,0x11,0x94,0xC0,0x4B,0xDE,0x23,0x82);

DEFINE_GUID(CLSID_QQGameHallAssist,0x10C3DA1D,0xB8AA,0x4e0a,0x96,0x12,0xD0,0x51,0x64,0x9B,0x66,0x0C);

#ifdef __cplusplus

class DECLSPEC_UUID("10C3DA1D-B8AA-4e0a-9612-D051649B660C")
QQGameHallAssist;
#endif
#endif /* __QQGameAssistPluginLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


