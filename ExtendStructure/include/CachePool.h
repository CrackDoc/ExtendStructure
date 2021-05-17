#ifndef CachePool_h__
#define CachePool_h__

#include "Cache.h"

class ExtendStructure_EXPORT CCachePool
{
public:

	class CCacheVisitor
	{
	public:
		virtual ~CCacheVisitor(){}

		virtual void Apply(const CCache& rBuffer) = 0;
	};

public:
	CCachePool(void *vectorPool);

	~CCachePool();

	CCachePool& operator=(const CCachePool& rhs);

	void AppendCacheBuffer(const CCache& rObject);

	void Travel(CCacheVisitor& rVisitor);

	void CleanupCache();

	size_t GetCacheCount() const;

	size_t GetBufferSize() const;

	int CopyToBuffer(unsigned char* pBuffer, int nMaxBufferLen) const;

	void * GetCache();

protected:
	mutable void* m_lstBufferObject;

};

#endif // CachePool_h__
