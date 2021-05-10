#ifndef IxDataStream_h__
#define IxDataStream_h__

#include "Cache.h"
#include "PublicMarco.h"

template<typename T>
class CIxDataStream
{
public:
	enum EEndian{
		E_LittleEndian = 0,
		E_BigEndian
	};
public:
	CIxDataStream(CCache &cache,bool bReadOnly = true)
		: m_bReadOnly(bReadOnly)
		, m_eEndian(E_LittleEndian){}
	~CIxDataStream(void){}
	void SetByteOrder(EEndian eEndian)
	{
		m_eEndian = eEndian;
	}
	void operator<<(const T& tValue );

	void operator>>(T& tValue );

private:
	CCache m_CCache;
	bool   m_bReadOnly;
	EEndian m_eEndian;
};

template <typename T>
void CIxDataStream<T>::operator<<(const T& nValue)
{
	int nTSize = sizeof(T);
	void *ptr = malloc(nTSize);
	if((GLOBALUtility::isHostLittleEndian() && m_eEndian == E_BigEndian) || (!GLOBALUtility::isHostLittleEndian && m_eEndian == E_LittleEndian))
	{
		//if(nTSize == 16)
		//{
		//	memcpy(ptr, &BYTESWAP16(nValue), nTSize);
		//}
		//else if(nTSize == 32)
		//{
		//	memcpy(ptr, &BYTESWAP32(nValue), nTSize);
		//}
		//else if(nTSize == 64)
		//{
		//	memcpy(ptr, &BYTESWAP64(nValue), nTSize);
		//}
	}
	else
	{
		memcpy(ptr, &nValue, nTSize);
	}
	CIxDataStream<T>::m_CCache.AttachBuffer((unsigned char*)ptr,nTSize);

	if(CIxDataStream<T>::m_CCache.IsDeepCopy())
	{
		free(ptr);
		ptr = NULL;
	}
}

template <typename T>
void CIxDataStream<T>::operator>>( T &nValue )
{
	CIxDataStream<T>::m_CCache>>nValue;
}

#endif // IxDataStream_h__

