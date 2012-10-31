#pragma once

#include "XySubRenderIntf.h"

interface ISubPicProviderEx;
interface IXyOptions;
interface ISubPicEx;
interface ISubPicProviderEx2;

class XySubRenderProviderWrapper: public CUnknown, public IXySubRenderProvider
{
public:
    XySubRenderProviderWrapper( ISubPicProviderEx *provider, IXyOptions *consumer
        , HRESULT* phr/*=NULL*/ );
    virtual ~XySubRenderProviderWrapper() {}

    DECLARE_IUNKNOWN;
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void** ppv);

    // IXySubRenderProvider
    STDMETHODIMP_(POSITION) GetStartPosition(REFERENCE_TIME rt);
    STDMETHODIMP_(POSITION) GetNext(POSITION pos);

    STDMETHODIMP RequestFrame(IXySubRenderFrame**subRenderFrame, REFERENCE_TIME *start, REFERENCE_TIME *stop, POSITION pos);

    STDMETHODIMP_(bool) IsColorTypeSupported(int type);
    STDMETHODIMP SetColorType(int type);

private:
    HRESULT Render( REFERENCE_TIME start, REFERENCE_TIME stop, double fps );
    HRESULT ResetAllocator();
    HRESULT Invalidate();
private:
    IXyOptions *m_consumer;
    CComPtr<ISubPicProviderEx> m_provider;
    CComPtr<ISubPicExAllocator> m_allocator;
    CComPtr<ISubPicEx> m_pSubPic;
    CComPtr<IXySubRenderFrame> m_xy_sub_render_frame;
    CRect m_output_rect;
};

class XySubRenderProviderWrapper2: public CUnknown, public IXySubRenderProvider
{
public:
    XySubRenderProviderWrapper2( ISubPicProviderEx2 *provider, IXyOptions *consumer
        , HRESULT* phr/*=NULL*/ );
    virtual ~XySubRenderProviderWrapper2() {}

    DECLARE_IUNKNOWN;
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void** ppv);

    // IXySubRenderProvider
    STDMETHODIMP_(POSITION) GetStartPosition(REFERENCE_TIME rt);
    STDMETHODIMP_(POSITION) GetNext(POSITION pos);

    STDMETHODIMP RequestFrame(IXySubRenderFrame**subRenderFrame, REFERENCE_TIME *start, REFERENCE_TIME *stop, POSITION pos);

    STDMETHODIMP_(bool) IsColorTypeSupported(int type);
    STDMETHODIMP SetColorType(int type);

private:
    HRESULT Render( REFERENCE_TIME start, REFERENCE_TIME stop, double fps );

    HRESULT Invalidate();
private:
    IXyOptions *m_consumer;
    CComPtr<ISubPicProviderEx2> m_provider;
    CComPtr<IXySubRenderFrame> m_xy_sub_render_frame;
    REFERENCE_TIME m_start, m_stop;
    CRect m_output_rect;
    CSize m_original_video_size;
    double m_fps;
};
