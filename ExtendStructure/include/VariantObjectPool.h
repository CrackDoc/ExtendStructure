#ifndef VariantObjectPool_h__
#define VariantObjectPool_h__

#include <vector>
#include "VariantObject.h"

// Brief:可变数据池 [2016/11/3 CETC] 
class CVariantObjectPool
{
public:
	enum
	{
		NUM_INVALID_OBJECT_ID	= -1,
		NUM_INUSE_OBJECT_ID		= 1,
	};
public:
	CVariantObjectPool(int nInitSize);
	~CVariantObjectPool();

	// Brief:分配一个可用的对象 [2016/11/3 CETC] 
	int AllocateAvailableObject();

	void GiveBackObject(int nObject);

	//回收全部的对象,空间保留(比较暴力的做法应该不常用)
	void GiveBackAllObject();

	CVariantObject& ReferenceObject(int nObjectId);

	const CVariantObject& ReferenceObject(int nObjectId) const;

	bool IsObjectIdAvariable(int nObjectId) const;

protected:
	std::vector<int> m_vecObjectInUseMark;				//对象使用标签
	std::vector<CVariantObject> m_vecVariantObjects;	//使用池来增加序列化速度
};
#endif // VariantObjectPool_h__
