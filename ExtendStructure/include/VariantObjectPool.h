#ifndef VariantObjectPool_h__
#define VariantObjectPool_h__

#include <vector>
#include "VariantObject.h"

// Brief:�ɱ����ݳ� [2016/11/3 CETC] 
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

	// Brief:����һ�����õĶ��� [2016/11/3 CETC] 
	int AllocateAvailableObject();

	void GiveBackObject(int nObject);

	//����ȫ���Ķ���,�ռ䱣��(�Ƚϱ���������Ӧ�ò�����)
	void GiveBackAllObject();

	CVariantObject& ReferenceObject(int nObjectId);

	const CVariantObject& ReferenceObject(int nObjectId) const;

	bool IsObjectIdAvariable(int nObjectId) const;

protected:
	std::vector<int> m_vecObjectInUseMark;				//����ʹ�ñ�ǩ
	std::vector<CVariantObject> m_vecVariantObjects;	//ʹ�ó����������л��ٶ�
};
#endif // VariantObjectPool_h__
