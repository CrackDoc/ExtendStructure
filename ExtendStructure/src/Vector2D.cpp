#include "Vector2D.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <math.h>

const CVector2D CVector2D::ZERO = CVector2D(0,0);
const CVector2D CVector2D::X_AXIS = CVector2D(1,0);
const CVector2D CVector2D::Y_AXIS = CVector2D(0,1);
const CVector2D CVector2D::UNIT = CVector2D(1,1);

CVector2D::CVector2D( KFLOAT _x /*= 0.0*/, KFLOAT _y /*= 0.0*/ )
{
	x = _x;
	y = _y;
}

CVector2D::CVector2D( const CVector2D& rhs )
{
	x = rhs.x;
	y = rhs.y;

}

CVector2D::~CVector2D( void )
{

}

bool CVector2D::operator>( const CVector2D& rhs ) const
{
	return x > rhs.x && y > rhs.y;
}

bool CVector2D::operator<( const CVector2D& rhs ) const
{
	return x < rhs.x && y < rhs.y;
}

bool CVector2D::operator!=( const CVector2D& rhs ) const
{
	bool bEquient = false;
	bEquient = IsEquivalent(x,rhs.x) && IsEquivalent(y,rhs.y);

	return !bEquient;
}

CVector2D& CVector2D::operator=( const CVector2D& rhs )
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}
bool CVector2D::operator==( const CVector2D& rhs )const
{
	return IsEquivalent(x,rhs.x) && IsEquivalent(y,rhs.y);
}
CVector2D& CVector2D::operator*=(KFLOAT rhs)
{
	x*=rhs;
	y*=rhs;
	return *this;
}

CVector2D& CVector2D::operator+=(const CVector2D& rhs)
{
	x+=rhs.x;
	y+=rhs.y;
	return *this;
}

CVector2D& CVector2D::operator-=(const CVector2D& rhs)
{
	x-=rhs.x;
	y-=rhs.y;
	return *this;
}
CVector2D& CVector2D::operator/=(KFLOAT rhs)
{
	x/=rhs;
	y/=rhs;
	return *this;
}
CVector2D CVector2D::operator-() const
{
	CVector2D vert2D;
	vert2D.x = -x;
	vert2D.y = -y;
	return vert2D;
}

KFLOAT CVector2D::GetLength() const
{
	return sqrt(x*x + y*y);
}

KFLOAT CVector2D::Sqrt2() const
{
	return GetLength();
}

KFLOAT CVector2D::Sqrt() const
{
	return x*x+y*y;
}
void CVector2D::ToString(void *input)
{
	assert(input);
	std::stringstream ss;
	ss << x << "_" << y;
	std::string xyzstring = ss.str();
	*static_cast<std::string*>(input) = *static_cast<std::string*>(&xyzstring);
}

CVector2D CVector2D::P3(const CVector2D& P1, const CVector2D& P2, const CVector2D& P3) const
{
	return CVector2D();
}

KFLOAT CVector2D::CrossProduct(const CVector2D& rhs) const
{
	return x*rhs.y - y*rhs.x;
}

KFLOAT CVector2D::DotProduct(const CVector2D& rhs) const
{
	return x*rhs.x + y*rhs.y;
}

KFLOAT CVector2D::CrossAngle(const CVector2D& rhs) const
{
	return DotProduct(rhs)/GetLength();
}

void CVector2D::Normalize()
{
	x = x/GetLength();
	y = y/GetLength();
}

bool CVector2D::IsEqual(const CVector2D& rhs) const
{
	return IsEquivalent(x,rhs.x,NUM_DOUBLE_MIN)&&IsEquivalent(y,rhs.y,NUM_DOUBLE_MIN);
}
CVector2D operator*(const CVector2D& lhs, KFLOAT rhs)
{
	return CVector2D(lhs.x*rhs,lhs.y*rhs);
}

CVector2D operator*(KFLOAT lhs, const CVector2D& rhs)
{
	return CVector2D(lhs*rhs.x,lhs*rhs.y);
}

CVector2D operator+(const CVector2D& lhs, const CVector2D& rhs)
{
	return CVector2D(lhs.x*rhs.x,rhs.y*rhs.y);
}

CVector2D operator-(const CVector2D& lhs, const CVector2D& rhs)
{
	return CVector2D(lhs.x-rhs.x,rhs.y-rhs.y);
}

CVector2D operator/(const CVector2D& lhs, KFLOAT rhs)
{
	return CVector2D(lhs.x/rhs,lhs.y/rhs);
}
