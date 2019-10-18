// Implements the IVSNZUIPrefs interface

#include "stdafx.h"
#include <comutil.h>
#include "ptav3.h"
#include "vsdnotz.h"
#include "nzuser.h"
#include "notarize.h"
#include "nzutils.h"
#include "nzerrs.h"
#include "nzmacros.h"
#include "VSNZ.h"


STDMETHODIMP CVSNZ::put_UILogoUrl(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrLogoUrl = newVal.bstrVal;

	return S_OK;
}


STDMETHODIMP CVSNZ::put_UISelFileTitle(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrSelFileTitle = newVal.bstrVal;

	return S_OK;
}


STDMETHODIMP CVSNZ::put_UISelFileDescription(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrSelFileDescription = newVal.bstrVal;

	return S_OK;
}


STDMETHODIMP CVSNZ::put_UISelFileHelpUrl(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrSelFileHelpUrl = newVal.bstrVal;

	return S_OK;
}

STDMETHODIMP CVSNZ::put_UIProgressTitle(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrProgressTitle = newVal.bstrVal;

	return S_OK;
}


STDMETHODIMP CVSNZ::put_UIProgressDescription(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrProgressDescription = newVal.bstrVal;

	return S_OK;
}


STDMETHODIMP CVSNZ::put_UIProgressHelpUrl(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrProgressHelpUrl = newVal.bstrVal;

	return S_OK;
}


STDMETHODIMP CVSNZ::put_UIVerifyRcptTitle(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrVerifyRcptTitle = newVal.bstrVal;

	return S_OK;
}


STDMETHODIMP CVSNZ::put_UIVerifyRcptDescription(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrVerifyRcptDescription = newVal.bstrVal;

	return S_OK;
}


STDMETHODIMP CVSNZ::put_UIVerifyRcptHelpUrl(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrVerifyRcptHelpUrl = newVal.bstrVal;

	return S_OK;
}


STDMETHODIMP CVSNZ::put_UIWizardTitle(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrDigNotWizTitle = newVal.bstrVal;

	return S_OK;
}
