#include "Vector3D.h"
#include <sstream>
#include <string>

const CVector3D CVector3D::ZERO = CVector3D();

const CVector3D CVector3D::X_AXIS = CVector3D(1,0,0);

const CVector3D CVector3D::Y_AXIS = CVector3D(0,1,0);

const CVector3D CVector3D::Z_AXIS = CVector3D(0,0,1);

const CVector3D CVector3D::UNIT = CVector3D(1,1,1);

CVector3D::CVector3D( KFLOAT _x /*= 0.0*/, KFLOAT _y /*= 0.0*/, KFLOAT _z /*= 0.0*/ )
{
	x = _x;
	y = _y;
	z = _z;
}

CVector3D::CVector3D( const CVector3D& rhs )
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}

CVector3D::~CVector3D( void )
{

}
CVector3D& CVector3D::operator=(const CVector3D& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}
bool CVector3D::operator==(const CVector3D& rhs) const
{
	return IsEquivalent(x,rhs.x) && IsEquivalent(y,rhs.y)&&IsEquivalent(z,rhs.z);
}
bool CVector3D::operator!=(const CVector3D& rhs) const
{
	bool bEquient = false;
	bEquient = IsEquivalent(x,rhs.x) && IsEquivalent(y,rhs.y)&&IsEquivalent(z,rhs.z);

	return !bEquient;
}
bool CVector3D::operator>(const CVector3D& rhs) const
{
	return x>rhs.x&& y>rhs.y && z>rhs.z;
}

bool CVector3D::operator<(const CVector3D& rhs) const
{
	return x<rhs.x&& y<rhs.y && z<rhs.z;
}

bool CVector3D::IsRightSide( const CVector3D& rhs, const CVector3D& upVector /*= Z_AXIS*/ ) const
{
	// 在某个平面的右边

	return false;
}

CVector3D& CVector3D::operator*=(KFLOAT rhs)
{
	return *this;
}

CVector3D& CVector3D::operator+=(const CVector3D& rhs)
{
	return *this;
}

CVector3D& CVector3D::operator-=(const CVector3D& rhs)
{
	return *this;
}

CVector3D& CVector3D::operator/=(KFLOAT rhs)
{
	return *this;
}
KFLOAT CVector3D::operator[](int nIndex) const
{
	return 0;
}

KFLOAT CVector3D::GetLength() const
{
	return 0;
}

KFLOAT CVector3D::Sqrt2() const
{
	return 0;
}

KFLOAT CVector3D::Sqrt() const
{
	return 0;
}

void  CVector3D::ToString(void *input)
{
	std::stringstream ss;
	ss << x << "_" << y << "_" << z;
	std::string xyzstring = ss.str();
	*static_cast<std::string*>(input) = *static_cast<std::string*>(&xyzstring);
}

KFLOAT CVector3D::CrossAngle( const CVector3D& rhs ) const
{
	return 0;
}

CVector3D CVector3D::CrossProduct( const CVector3D& rhs ) const
{
	return CVector3D();
}

KFLOAT CVector3D::DotProduct( const CVector3D& rhs ) const
{
	return 0;
}

CVector3D CVector3D::Projection( const CVector3D& rhs ) const
{
	return CVector3D();
}

CVector3D CVector3D::Vertical( const CVector3D& rhs ) const
{
	return CVector3D();
}

bool CVector3D::IsSameDirection( const CVector3D& rhs ) const
{
	return false;
}

bool CVector3D::IsVertical( const CVector3D& rhs ) const
{
	return false;
}

bool CVector3D::IsParallel( const CVector3D& rhs ) const
{
	return false;
}

void CVector3D::Normalize()
{

}

CVector3D CVector3D::GetNormal() const
{
	return CVector3D();
}

CVector3D CVector3D::Reflect( const CVector3D& rNormal, CVector3D* pOutPlane /*= NULL*/ ) const
{
	return CVector3D();
}

bool CVector3D::IsEqual( const CVector3D& rhs ) const
{
	return false;
}

CVector3D operator*(const CVector3D& lhs, KFLOAT rhs)
{
	return CVector3D(lhs.x*rhs,lhs.y*rhs,lhs.z*rhs);
}

CVector3D operator*(KFLOAT lhs, const CVector3D& rhs)
{
	return CVector3D(lhs*rhs.x,lhs*rhs.y,lhs*rhs.z);
}

CVector3D operator+(const CVector3D& lhs, const CVector3D& rhs)
{
	return CVector3D();
}

CVector3D operator-(const CVector3D& lhs, const CVector3D& rhs)
{
	return CVector3D();
}
CVector3D operator/(const CVector3D& lhs, KFLOAT rhs)
{
	return CVector3D();
}
