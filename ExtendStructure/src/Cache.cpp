#include "Cache.h"
#include <memory>
#include <string>
#include <assert.h>

CCache::CCache(bool bDeepCopy):
	m_bDeepCopy(bDeepCopy)
	,m_nBufferLength(0)
	,m_pBuffer(NULL)
	,m_nIndex(0)
{

}
CCache::CCache(void* pBuffer, int nLen, bool bDeepCopy )
{
	assert(pBuffer);
	m_nIndex = 0;
	m_nBufferLength = nLen;
	m_bDeepCopy = bDeepCopy;
	SetBuffer(pBuffer,nLen);
}

CCache::CCache( const CCache& rhs )
{
	m_nIndex = 0;
	m_nBufferLength = rhs.length();
	m_bDeepCopy = rhs.IsDeepCopy();
	SetBuffer(rhs.GetBuffer(),rhs.length());
}
CCache::~CCache()
{
	if(m_pBuffer != NULL)
	{
		delete  []m_pBuffer;
		m_pBuffer = NULL;
	}
}

void CCache::operator<<( const char* szstrBuffer )
{
	std::string strBuffer = szstrBuffer;
	AttachBuffer(&strBuffer,strBuffer.length());
}

void CCache::operator>>(void *input )
{
	assert(input);
	*static_cast<std::string*>(input) = *static_cast<std::string*>(m_pBuffer);
}

void CCache::operator>>( unsigned char &ch )
{
	if(m_nIndex >= length())
	{
		m_nIndex = 0;
		return;
	}
	ch = ((unsigned char*)&m_pBuffer)[m_nIndex];
	m_nIndex++;
}

void CCache::operator>>( unsigned short &ch )
{
	if(m_nIndex >= length())
	{
		m_nIndex = 0;
		return;
	}
	ch = ((unsigned short*)&m_pBuffer)[m_nIndex];
	m_nIndex +=2;
}

void CCache::operator>>( unsigned int &ch )
{
	if(m_nIndex >= length())
	{
		m_nIndex = 0;
		return;
	}
	ch = ((unsigned int*)&m_pBuffer)[m_nIndex];
	m_nIndex +=4;
}

void CCache::operator>>( long long &ch )
{
	if(m_nIndex >= length())
	{
		m_nIndex = 0;
		return;
	}
	ch = ((long long*)&m_pBuffer)[m_nIndex];
	m_nIndex +=8;
}

void CCache::operator>>( double &ch )
{
	if(m_nIndex >= length())
	{
		m_nIndex = 0;
		return;
	}
	ch = ((double*)&m_pBuffer)[m_nIndex];
	m_nIndex +=8;
}

void CCache::operator>>( float &ch )
{
	if(m_nIndex >= length())
	{
		m_nIndex = 0;
		return;
	}
	ch = ((float*)&m_pBuffer)[m_nIndex];
	m_nIndex +=4;
}

void CCache::operator>>( char &ch )
{
	if(m_nIndex >= length())
	{
		m_nIndex = 0;
		return;
	}
	ch = ((char*)&m_pBuffer)[m_nIndex];
	m_nIndex++;
}

void CCache::operator>>( short &ch )
{
	if(m_nIndex >= length())
	{
		m_nIndex = 0;
		return;
	}
	ch = ((short*)&m_pBuffer)[m_nIndex];
	m_nIndex +=2;
}

void CCache::operator>>( int &ch )
{
	if(m_nIndex >= length())
	{
		m_nIndex = 0;
		return;
	}
	ch = ((int*)&m_pBuffer)[m_nIndex];
	m_nIndex +=4;
}

void* CCache::operator[]( int i )
{
	if(i > length() || i < 0)
	{
		return NULL;
	}
	return (void *)(&m_pBuffer+i);
}

void CCache::AttachBuffer( void* pBuffer, size_t nLen )
{
	assert(pBuffer);

	m_nBufferLength += nLen;
	void *pTmpBuffer = nullptr;

	if(!m_bDeepCopy)
	{
		pTmpBuffer = pBuffer;
	}
	else
	{
		pTmpBuffer = new unsigned char[nLen];
		memcpy(pTmpBuffer,pBuffer,sizeof(char)*nLen);

	}
	void* pReAlloc = (void *)realloc(m_pBuffer,nLen);
	assert(pReAlloc);
	memcpy(pReAlloc,pTmpBuffer,nLen);
}

void CCache::SetBuffer(void* pBuffer, size_t nLen )
{
	assert(pBuffer);
	if(!m_bDeepCopy)
	{
		m_pBuffer = pBuffer;
		m_nBufferLength = nLen;
	}
	else
	{
		m_nBufferLength = nLen;
		memcpy(pBuffer,m_pBuffer,sizeof(char)*m_nBufferLength);
	}
}

void CCache::ManualDeleteBuffer()
{
	if(m_pBuffer != NULL)
	{
		m_nBufferLength = 0;
		delete []m_pBuffer;
		m_pBuffer = NULL;
	}
	 
}

void* CCache::GetBuffer() const
{
	return m_pBuffer;
}

size_t CCache::length() const
{
	return m_nBufferLength;
}

size_t CCache::size() const
{
	return m_nBufferLength;
}

void CCache::SetDeepCopy( bool bDeepCopy )
{
	m_bDeepCopy = bDeepCopy;
}

bool CCache::IsDeepCopy() const
{
	return m_bDeepCopy;
}

bool CCache::IsValid() const
{
	return (m_pBuffer!=NULL);
}

CCache * CCache::Clone()
{
	CCache *pCCache = new CCache;
	pCCache->SetDeepCopy(m_bDeepCopy);
	pCCache->SetBuffer(m_pBuffer,m_nBufferLength);
	return pCCache;
}

bool CCache::IsEmpty()
{
	return m_pBuffer== NULL;
}

CCache& CCache::operator=( const CCache& rhs )
{
	m_bDeepCopy = rhs.IsDeepCopy();
	m_nBufferLength = rhs.length();
	if(m_bDeepCopy)
	{
		memcpy(rhs.GetBuffer(),m_pBuffer,sizeof(unsigned char)*m_nBufferLength);
	}
	else
	{
		m_pBuffer = rhs.GetBuffer();
	}
	return *this;
}

bool CCache::operator==(const CCache& rhs) const
{
	return (std::strcmp((char*)m_pBuffer,(char*)rhs.GetBuffer()) == 0);
}
