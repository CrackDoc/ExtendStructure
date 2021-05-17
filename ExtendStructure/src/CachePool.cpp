#include "CachePool.h"
#include <vector>
#include <assert.h>

CCachePool::CCachePool(void* vectorPool)
	:m_lstBufferObject(vectorPool)
{
	if (!m_lstBufferObject)
	{
		m_lstBufferObject = new std::vector<CCache>();
	}
}
void* CCachePool::GetCache()
{
	return m_lstBufferObject;
}
CCachePool::~CCachePool()
{

}

void CCachePool::AppendCacheBuffer( const CCache& rObject )
{
	CCache lpcache = rObject;
	assert(m_lstBufferObject);
	std::vector<CCache>& vectorCaches = *static_cast<std::vector<CCache>*>(m_lstBufferObject);
	vectorCaches.push_back(lpcache);
}

void CCachePool::Travel( CCacheVisitor& rVisitor )
{
	assert(m_lstBufferObject);
	std::vector<CCache>& vectorCaches = *static_cast<std::vector<CCache>*>(m_lstBufferObject);

	std::vector<CCache>::iterator it0 = vectorCaches.begin();

	for(;it0 != vectorCaches.end();++it0)
	{
		CCache cache = *it0;
		rVisitor.Apply(cache);
	}
}

void CCachePool::CleanupCache()
{
	assert(m_lstBufferObject);
	std::vector<CCache>& vectorCaches = *static_cast<std::vector<CCache>*>(m_lstBufferObject);

	std::vector<CCache>::iterator it0 = vectorCaches.begin();

	for(;it0 != vectorCaches.end();++it0)
	{
		CCache cache = *it0;
		cache.ManualDeleteBuffer();
	}
	vectorCaches.clear();
}

size_t CCachePool::GetCacheCount() const
{
	assert(m_lstBufferObject);
	std::vector<CCache>& vectorCaches = *static_cast<std::vector<CCache>*>(m_lstBufferObject);

	return vectorCaches.size();
}

size_t CCachePool::GetBufferSize() const
{
	assert(m_lstBufferObject);

	std::vector<CCache>& vectorCaches = *static_cast<std::vector<CCache>*>(m_lstBufferObject);
	std::vector<CCache>::iterator it0 = vectorCaches.begin();
	size_t nCount = 0;
	for(;it0 != vectorCaches.end();++it0)
	{
		CCache &cache = *it0;
		nCount += cache.length();
	}
	return nCount;
}

int CCachePool::CopyToBuffer( unsigned char* pBuffer, int nMaxBufferLen ) const
{
	assert(m_lstBufferObject);
	CCache cache(pBuffer,nMaxBufferLen,true);
	std::vector<CCache>& vectorCaches = *static_cast<std::vector<CCache>*>(m_lstBufferObject);

	vectorCaches.push_back(cache);
	return nMaxBufferLen;
}
CCachePool& CCachePool::operator=( const CCachePool& rhs )
{
	CleanupCache();
	CCachePool pool = rhs;
	m_lstBufferObject = pool.GetCache();
	return *this;
}

