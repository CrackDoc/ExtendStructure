#include "IxImage.h"
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

CIxImage::CIxImage( int nWidth,int nHeight )
	:m_nPixWidth(nWidth)
	,m_nPixHeight(nHeight)
	,nBandCnt(3)
{

}

CIxImage::CIxImage()
	:m_nPixWidth(0)
	,m_nPixHeight(0)
	,nBandCnt(3)
{

}

CIxImage::~CIxImage(void)
{

}
bool CIxImage::LoadFromData(const char *szBuffer,int nLength,bool bDeepCopy )
{
	if(szBuffer == NULL)
	{
		return false;
	}
	m_CCache.SetDeepCopy(bDeepCopy);
	std::string strBuffer = szBuffer;
	m_CCache.SetBuffer(&strBuffer,nLength);
	return true;
}

bool CIxImage::LoadFromCache( CCache &cache )
{
	if(cache.length() == 0)
	{
		return false;
	}
	m_CCache = cache;
	return true;
}

bool CIxImage::LoadFromFile( const char *szFile )
{
	int w, h, n;
	unsigned char *data = stbi_load(szFile, &w, &h, &n, 0);
	if(data == NULL)
	{
		return false;
	}
	int nLength = w*h*n;
	m_CCache.SetDeepCopy(false);
	m_CCache.SetBuffer(data,nLength);
	m_nPixWidth = w;
	m_nPixHeight = h;
	nBandCnt = n;
	return true;
}

bool CIxImage::Save( const char* szFile,E_IMAGE_TYPE eType /*= E_JPG*/ )
{
	bool bSucc = false;
	if(!m_CCache.IsValid())
	{
		return bSucc;
	}
	switch(eType)
	{
	case E_JPG:
		{
			bSucc = (stbi_write_jpg(szFile,m_nPixWidth,m_nPixHeight,nBandCnt,m_CCache.GetBuffer(),100)==0?false:true);
		}
		break;
	case E_BMP:
		{
			bSucc = (stbi_write_bmp(szFile,m_nPixWidth,m_nPixHeight,nBandCnt,m_CCache.GetBuffer())==0?false:true);
		}
		break;
	case E_PNG:
		{
			bSucc = (stbi_write_png(szFile,m_nPixWidth,m_nPixHeight,nBandCnt,m_CCache.GetBuffer(),m_nPixWidth*3)==0?false:true);	
		}
		break;
	case E_HDR:
		{
			bSucc = (stbi_write_hdr(szFile,m_nPixWidth,m_nPixHeight,nBandCnt,(float*)m_CCache.GetBuffer())==0?false:true);
		}
		break;
	case E_TGA:
		{
			bSucc = (stbi_write_tga(szFile,m_nPixWidth,m_nPixHeight,nBandCnt,m_CCache.GetBuffer())==0?false:true);
		}
		break;
	}
	return bSucc;
}
