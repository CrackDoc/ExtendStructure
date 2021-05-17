#ifndef Cache_h__
#define Cache_h__

#include "ExtendStructureExport.h"

class ExtendStructure_EXPORT CCache
{
public:
	CCache(bool bDeepCopy = true);
	//����Ǵ��������,�����,����ʹ��Boost�� ����c++11 �е�����ָ�� share_Ptr��Weak_Ptr һ��ʹ��,��������ǳ��������ͷŴ����������
	// boost::makeSharePtr<std::string>("hello world") boost ��scope_Ptr ��c++11 unique_Ptr ��ռ��������������ʹ��  share_ptr ��weak_ptr ���ʹ�� ���Կ���,���ü���

	// ��������ʹ����� ,ӦΪCCache ���󲻺ù���,ǳ����,����������m_pBuffer,�ͷ�Ҫ�Կ�ָ������п� 
	CCache(void* pBuffer, int nLen, bool bDeepCopy = true);

	CCache(const CCache& rhs);

	virtual ~CCache();

	CCache& operator=(const CCache& rhs);

	bool operator==(const CCache& rhs) const;

	void operator<<(const char * strBuffer);

	void operator>>(void *input);

	void operator>>(unsigned char &ch);

	void operator>>(char &ch);

	void operator>>(unsigned short &ch);

	void operator>>(short &ch);

	void operator>>(unsigned int &ch);

	void operator>>(int &ch);

	void operator>>(long long &ch);

	void operator>>(double &ch);

	void operator>>(float &ch);

	void* operator[](int i);

	//�ֶ��ͷſռ�,ǳ����Ҳ����ɾ���ռ�,ʹ�õ�ʱ���뱣��ͷ������
	void ManualDeleteBuffer();

	void* GetBuffer() const;

	size_t length() const;

	size_t size() const;

	// ǿ���޸������־ [7/17/2019 kyske]
	void SetDeepCopy(bool bDeepCopy);

	bool IsDeepCopy() const;

	bool IsValid() const;

	CCache *Clone();

	bool IsEmpty();

	void AttachBuffer(void* pBuffer, size_t nLen);

	void SetBuffer(void* pBuffer, size_t nLen);

protected:

	size_t  m_nBufferLength;
	void* m_pBuffer;
	bool m_bDeepCopy;
	int m_nIndex;
};
#endif // Cache_h__
