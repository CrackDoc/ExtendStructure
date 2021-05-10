#ifndef Vector2D_h__
#define Vector2D_h__

#include "ExtendStructureExport.h"
#include "ExtendStructureConstant.h"

//向量2D
class ExtendStructure_EXPORT CVector2D
{
public:
	static const CVector2D ZERO;	//0向量
	static const CVector2D X_AXIS;	//x轴向量
	static const CVector2D Y_AXIS;	//y轴向量
	static const CVector2D UNIT;	//单位向量(未归一化)

	enum
	{
		E_DATA_LENGTH = sizeof(KFLOAT) * 2,
	};

public:
	CVector2D(KFLOAT _x = 0.0, KFLOAT _y = 0.0);

	CVector2D(const CVector2D& rhs);

	~CVector2D(void);

	CVector2D& operator=(const CVector2D& rhs);

	bool operator==(const CVector2D& rhs) const;

	bool operator!=(const CVector2D& rhs) const;

	bool operator>(const CVector2D& rhs) const;

	bool operator<(const CVector2D& rhs) const;

	CVector2D& operator*=(KFLOAT rhs);

	CVector2D& operator+=(const CVector2D& rhs);

	CVector2D& operator-=(const CVector2D& rhs);

	CVector2D& operator/=(KFLOAT rhs);

	CVector2D operator-() const;

	KFLOAT GetLength() const;

	KFLOAT Sqrt2() const;

	KFLOAT Sqrt() const;

	void ToString(void* input);

	CVector2D P3(const CVector2D& P1, const CVector2D& P2, const CVector2D& P3) const;

	KFLOAT CrossProduct(const CVector2D& rhs) const;

	KFLOAT DotProduct(const CVector2D& rhs) const;

	KFLOAT CrossAngle(const CVector2D& rhs) const;

	void Normalize();

	bool IsEqual(const CVector2D& rhs) const;

public:
	union
	{
		struct  
		{
			KFLOAT x, y;
		};
		KFLOAT _v[2];
	};
};

ExtendStructure_EXPORT CVector2D operator*(const CVector2D& lhs, KFLOAT rhs);

ExtendStructure_EXPORT CVector2D operator*(KFLOAT lhs, const CVector2D& rhs);

ExtendStructure_EXPORT CVector2D operator+(const CVector2D& lhs, const CVector2D& rhs);

ExtendStructure_EXPORT CVector2D operator-(const CVector2D& lhs, const CVector2D& rhs);

ExtendStructure_EXPORT CVector2D operator/(const CVector2D& lhs, KFLOAT rhs);

#endif // Vector2D_h__
