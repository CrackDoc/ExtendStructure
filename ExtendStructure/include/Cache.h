#ifndef Cache_h__
#define Cache_h__

#include "ExtendStructureExport.h"

class ExtendStructure_EXPORT CCache
{
public:
	CCache(bool bDeepCopy = true);
	//如果是大数据深拷贝,会很慢,建议使用Boost库 或者c++11 中的智能指针 share_Ptr和Weak_Ptr 一起使用,不会引起浅拷贝多次释放带来软件崩溃
	// boost::makeSharePtr<std::string>("hello world") boost 库scope_Ptr 和c++11 unique_Ptr 独占自能在作用域中使用  share_ptr 和weak_ptr 配合使用 可以拷贝,引用计数

	// 在这儿最好使用深拷贝 ,应为CCache 对象不好管理,浅拷贝,多个对象持有m_pBuffer,释放要对空指针进行判空 
    CCache(unsigned char* pBuffer, int nLen, bool bDeepCopy = true);

	CCache(const CCache& rhs);

	virtual ~CCache();

	CCache& operator=(const CCache& rhs);

	bool operator==(const CCache& rhs) const;

	void operator<<(const char * strBuffer);

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

	//手动释放空间,浅拷贝也可以删除空间,使用的时候，请保持头脑清醒
	void ManualDeleteBuffer();

    unsigned char* GetBuffer() const;

    int length() const;

    int size() const;

	// 强制修改深拷贝标志 [7/17/2019 kyske]
	void SetDeepCopy(bool bDeepCopy);

	bool IsDeepCopy() const;

	bool IsValid() const;

	CCache *Clone();

	bool IsEmpty();

    void AttachBuffer(unsigned char* pBuffer, int nLen);

    void SetBuffer(unsigned char* pBuffer, int nLen);

protected:

    int  m_nBufferLength;
    unsigned char* m_pBuffer;
	bool m_bDeepCopy;
	int m_nIndex;
};
#endif // Cache_h__
