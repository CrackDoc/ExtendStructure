#ifndef CVector3D_h__
#define CVector3D_h__

#include "ExtendStructureConstant.h"
#include "ExtendStructureExport.h"

//����
class ExtendStructure_EXPORT CVector3D
{
public:
	static const CVector3D ZERO;	//0����
	static const CVector3D X_AXIS;	//x������
	static const CVector3D Y_AXIS;	//y������
	static const CVector3D Z_AXIS;	//z������
	static const CVector3D UNIT;	//��λ����(δ��һ��)

	enum
	{
		E_DATA_LENGTH = sizeof(KFLOAT) * 3,
	};
public:
	CVector3D(KFLOAT _x = 0.0, KFLOAT _y = 0.0, KFLOAT _z = 0.0);

	CVector3D(const CVector3D& rhs);

	~CVector3D(void);

	CVector3D& operator=(const CVector3D& rhs);

	bool operator==(const CVector3D& rhs) const;

	bool operator!=(const CVector3D& rhs) const;

	bool operator>(const CVector3D& rhs) const;

	bool operator<(const CVector3D& rhs) const;

	CVector3D& operator*=(KFLOAT rhs);

	CVector3D& operator+=(const CVector3D& rhs);

	CVector3D& operator-=(const CVector3D& rhs);

	CVector3D& operator/=(KFLOAT rhs);

	bool IsRightSide(const CVector3D& rhs, const CVector3D& upVector = CVector3D::Z_AXIS) const;

	KFLOAT operator[](int nIndex) const;

	KFLOAT GetLength() const;

	KFLOAT Sqrt2() const;

	KFLOAT Sqrt() const;

	void ToString(void *input);

	KFLOAT CrossAngle(const CVector3D& rhs) const;

	CVector3D CrossProduct(const CVector3D& rhs) const;

	KFLOAT DotProduct(const CVector3D& rhs) const;

	// ��������������ͶӰ���� [9/18/2019 kyske]
	CVector3D Projection(const CVector3D& rhs) const;

	// һ�������������Ĵ�ֱ���� [9/18/2019 kyske]
	CVector3D Vertical(const CVector3D& rhs) const;

	// ����ͬ��,����ƽ�� [9/19/2019 kyske]
	bool IsSameDirection(const CVector3D& rhs) const;

	bool IsVertical(const CVector3D& rhs) const;

	bool IsParallel(const CVector3D& rhs) const;

	void Normalize();

	CVector3D GetNormal() const;

	// ��������Ϊ��������,���뷨��,��������,��ѡ������� [9/20/2019 kyske]
	CVector3D Reflect(const CVector3D& rNormal, CVector3D* pOutPlane = NULL) const;

	bool IsEqual(const CVector3D& rhs) const ;

public:
	union
	{
		struct  
		{
			KFLOAT x, y, z;
		};
		KFLOAT _v[3];
	};
};

ExtendStructure_EXPORT CVector3D operator*(const CVector3D& lhs, KFLOAT rhs);

ExtendStructure_EXPORT CVector3D operator*(KFLOAT lhs, const CVector3D& rhs);

ExtendStructure_EXPORT CVector3D operator+(const CVector3D& lhs, const CVector3D& rhs);

ExtendStructure_EXPORT CVector3D operator-(const CVector3D& lhs, const CVector3D& rhs);

ExtendStructure_EXPORT CVector3D operator/(const CVector3D& lhs, KFLOAT rhs);

#endif // CVector3D_h__

