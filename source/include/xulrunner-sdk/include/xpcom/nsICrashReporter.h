/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/xr19rel/WINNT_5.2_Depend/mozilla/xpcom/system/nsICrashReporter.idl
 */

#ifndef __gen_nsICrashReporter_h__
#define __gen_nsICrashReporter_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsICrashReporter */
#define NS_ICRASHREPORTER_IID_STR "4d6449fe-d642-45e5-9773-41af5793c99a"

#define NS_ICRASHREPORTER_IID \
  {0x4d6449fe, 0xd642, 0x45e5, \
    { 0x97, 0x73, 0x41, 0xaf, 0x57, 0x93, 0xc9, 0x9a }}

/**
 * Provides access to crash reporting functionality.
 * @status UNSTABLE - This interface is not frozen and will probably change in
 *                    future releases.
 */
class NS_NO_VTABLE NS_SCRIPTABLE nsICrashReporter : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICRASHREPORTER_IID)

  /**
   * Add some extra data to be submitted with a crash report.
   * @param key
   *        Name of the data to be added.
   * @param data
   *        Data to be added.
   *
   * @throw NS_ERROR_NOT_INITIALIZED if crash reporting not initialized
   * @throw NS_ERROR_INVALID_ARG if key or data contain invalid characters.
   *                             Invalid characters for key are '=' and
   *                             '\n'.  Invalid character for data is '\0'.
   */
  /* void annotateCrashReport (in ACString key, in ACString data); */
  NS_SCRIPTABLE NS_IMETHOD AnnotateCrashReport(const nsACString & key, const nsACString & data) = 0;

  /**
    * Write a minidump immediately, with the user-supplied exception
    * information. This is implemented on Windows only, because
    * SEH (structured exception handling) exists on Windows only.
    * @param aExceptionInfo  EXCEPTION_INFO* provided by Window's SEH
    */
  /* [noscript] void WriteMinidumpForException (in voidPtr aExceptionInfo); */
  NS_IMETHOD WriteMinidumpForException(void * aExceptionInfo) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsICrashReporter, NS_ICRASHREPORTER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICRASHREPORTER \
  NS_SCRIPTABLE NS_IMETHOD AnnotateCrashReport(const nsACString & key, const nsACString & data); \
  NS_IMETHOD WriteMinidumpForException(void * aExceptionInfo); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICRASHREPORTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD AnnotateCrashReport(const nsACString & key, const nsACString & data) { return _to AnnotateCrashReport(key, data); } \
  NS_IMETHOD WriteMinidumpForException(void * aExceptionInfo) { return _to WriteMinidumpForException(aExceptionInfo); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICRASHREPORTER(_to) \
  NS_SCRIPTABLE NS_IMETHOD AnnotateCrashReport(const nsACString & key, const nsACString & data) { return !_to ? NS_ERROR_NULL_POINTER : _to->AnnotateCrashReport(key, data); } \
  NS_IMETHOD WriteMinidumpForException(void * aExceptionInfo) { return !_to ? NS_ERROR_NULL_POINTER : _to->WriteMinidumpForException(aExceptionInfo); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsCrashReporter : public nsICrashReporter
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICRASHREPORTER

  nsCrashReporter();

private:
  ~nsCrashReporter();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsCrashReporter, nsICrashReporter)

nsCrashReporter::nsCrashReporter()
{
  /* member initializers and constructor code */
}

nsCrashReporter::~nsCrashReporter()
{
  /* destructor code */
}

/* void annotateCrashReport (in ACString key, in ACString data); */
NS_IMETHODIMP nsCrashReporter::AnnotateCrashReport(const nsACString & key, const nsACString & data)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void WriteMinidumpForException (in voidPtr aExceptionInfo); */
NS_IMETHODIMP nsCrashReporter::WriteMinidumpForException(void * aExceptionInfo)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsICrashReporter_h__ */
