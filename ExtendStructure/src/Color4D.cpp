#include "Color4D.h"

#pragma warning( disable: 4244 )

const CColor4D CColor4D::COLOR_NONE = CColor4D(255,255,255,0);

const CColor4D CColor4D::COLOR_BLACK = CColor4D(0,0,0,255);

const CColor4D CColor4D::COLOR_RED = CColor4D(255,0,0,255);

const CColor4D CColor4D::COLOR_GREEN = CColor4D(0,255,0,255);

const CColor4D CColor4D::COLOR_BLUE = CColor4D(0,0,255,255);

const CColor4D CColor4D::COLOR_WHITE = CColor4D(255,255,255,255);

const CColor4D CColor4D::COLOR_YELLOW = CColor4D(255,255,0,255);

CColor4D::CColor4D()
{

}

CColor4D::CColor4D(KFLOAT _r, KFLOAT _g, KFLOAT _b, KFLOAT _a)
{
	SetRedF(_r);
	SetGreedF(_g);
	SetBlueF(_b);
	SetAlphaF(_a);
}

CColor4D::CColor4D(int _r, int _g, int _b, int _a)
{
	SetRed(_r);
	SetGreen(_g);
	SetBlue(_b);
	SetAlpha(_a);

}

CColor4D::CColor4D(int nColor)
{
	_color = nColor;
}

CColor4D::CColor4D(const CColor4D& rhs)
{
	_color = rhs._color;
}

CColor4D::~CColor4D(void)
{

}

bool CColor4D::operator<(const CColor4D& rhs) const
{
	return _color < rhs._color;
}

unsigned int CColor4D::GetColor() const
{
	return _color;
}

unsigned char CColor4D::GetRed() const
{
	return r;
}

KFLOAT CColor4D::GetRedF() const
{
	return (KFLOAT)r/255.0;
}

unsigned char CColor4D::GetGreen() const
{
	return g;
}

KFLOAT CColor4D::GetGreenF() const
{
	return (KFLOAT)g/255.0;
}

unsigned char CColor4D::GetBlue() const
{
	return b;
}

KFLOAT CColor4D::GetBlueF() const
{
	return (KFLOAT)b/255.0;
}

unsigned char CColor4D::GetAlpha() const
{
	return a;
}

KFLOAT CColor4D::GetAlphaF() const
{
	return (KFLOAT)a/255.0;
}

void CColor4D::SetColor(unsigned int nColor)
{
	_color = nColor;
}

void CColor4D::SetRedF(KFLOAT fRed)
{
	r = 255*fRed;
}

void CColor4D::SetRed(unsigned char nRed)
{
	r = nRed;
}

void CColor4D::SetGreedF(KFLOAT fGreen)
{
	g = 255*fGreen;
}

void CColor4D::SetGreen(unsigned char nGreen)
{
	g = nGreen;
}

void CColor4D::SetBlueF(KFLOAT fBlue)
{
	b = fBlue*255;
}

void CColor4D::SetBlue(unsigned char nBlue)
{
	b = nBlue;
}

void CColor4D::SetAlphaF(KFLOAT fAlpha)
{
	a = 255*fAlpha;
}

void CColor4D::SetAlpha(unsigned char nAlpha)
{
	a = nAlpha;
}

void CColor4D::SetARGB(int nArgbColor)
{
	CColor4D ArgbColor(nArgbColor);
	r = ArgbColor._v[1];
	g = ArgbColor._v[2];
	b = ArgbColor._v[3];
	a = ArgbColor._v[0];
}

int CColor4D::GetARGB() const
{
	CColor4D ArgbColor;

	ArgbColor.a = _v[3];
	ArgbColor.r = _v[0];
	ArgbColor.g = _v[1];
	ArgbColor.b = _v[2];
	return ArgbColor._color;
}

void CColor4D::ToHSV(KFLOAT& H, KFLOAT& S, KFLOAT& V)
{
	KFLOAT R, G, B;
	R = GetRedF();
	G = GetGreenF();
	B = GetBlueF();
	KFLOAT min, max, delta,tmp;
	tmp = R>G?G:R;
	min = tmp>B?B:tmp;
	tmp = R>G?R:G;
	max = tmp>B?tmp:B;
	V = max; // v
	delta = max - min;
	if( max != 0 )
		S = delta / max; // s
	else
	{
		// r = g = b = 0 // s = 0, v is undefined
		S = 0;
		H = 0;
		return;
	}
	if (delta == 0){
		H = 0;
		return;
	}
	else if(R == max){
		if (G >= B)
			H = (G - B) / delta; // between yellow & magenta
		else
			H = (G - B) / delta + 6.0;
	}
	else if( G == max )
		H = 2.0 + ( B - R ) / delta; // between cyan & yellow
	else if (B == max)
		H = 4.0 + ( R - G ) / delta; // between magenta & cyan
	H *= 60.0; // degrees
}

void CColor4D::FromHSV(KFLOAT h, KFLOAT s ,KFLOAT v)
{
	int i;
	KFLOAT  RGB_min, RGB_max;
	RGB_max = v*2.55f;
	RGB_min = RGB_max*(100 - s)/ 100.0f;

	i = h / 60;
	int difs = (int)h%60; // factorial part of h

	// RGB adjustment amount by hue 
	float RGB_Adj = (RGB_max - RGB_min)*difs / 60.0f;

	switch (i) {
	case 0:
		r = RGB_max;
		g = RGB_min + RGB_Adj;
		b = RGB_min;
		break;
	case 1:
		r = RGB_max - RGB_Adj;
		g = RGB_max;
		b = RGB_min;
		break;
	case 2:
		r = RGB_min;
		g = RGB_max;
		b = RGB_min + RGB_Adj;
		break;
	case 3:
		r = RGB_min;
		g = RGB_max - RGB_Adj;
		b = RGB_max;
		break;
	case 4:
		r = RGB_min + RGB_Adj;
		g = RGB_min;
		b = RGB_max;
		break;
	default:		// case 5:
		r = RGB_max;
		g = RGB_min;
		b = RGB_max - RGB_Adj;
		break;
	}
}

CColor4D CColor4D::P3(const CColor4D& C0, const CColor4D& C1, const CColor4D& C2, KFLOAT u, KFLOAT v)
{
	return CColor4D();
}

CColor4D CColor4D::FromARGB(int nArgb)
{
	CColor4D ArgbColor(nArgb);
	unsigned char nRed = ArgbColor._v[1];
	unsigned char nGreen  = ArgbColor._v[2];
	unsigned char nBlue= ArgbColor._v[3];
	unsigned char nAlpha  = ArgbColor._v[0];
	return CColor4D(nRed,nGreen,nBlue,nAlpha);
}
bool CColor4D::operator==(const CColor4D& rhs) const
{
	return r == rhs.r &&
		   b == rhs.b &&
		   g == rhs.g &&
		   a == rhs.a;
}

bool CColor4D::operator!=(const CColor4D& rhs) const
{
	bool bEqual = (r == rhs.r &&
		b == rhs.b &&
		g == rhs.g &&
		a == rhs.a);
	return !bEqual;
}
CColor4D& CColor4D::operator=(unsigned int nColor)
{
	_color = nColor;
	return *this;
}

CColor4D& CColor4D::operator=(const CColor4D& rhs)
{
	_color = rhs._color;
	return *this;
}

CColor4D operator*(const CColor4D& lhs, KFLOAT rhs)
{
	int nRed = lhs.r*rhs;
	if(nRed > 255)
	{
		nRed = 255;
	}
	int nGreen = lhs.g*rhs;
	if(nGreen > 255)
	{
		nGreen = 255;
	}
	int nBlue = lhs.b*rhs;
	if(nBlue > 255)
	{
		nBlue = 255;
	}
	return CColor4D(nRed,nGreen,nBlue,lhs.a);
}

CColor4D operator*(KFLOAT lhs, const CColor4D& rhs)
{
	int nRed = rhs.r*lhs;
	if(nRed > 255)
	{
		nRed = 255;
	}
	int nGreen = rhs.g*lhs;
	if(nGreen > 255)
	{
		nGreen = 255;
	}
	int nBlue = rhs.b*lhs;
	if(nBlue > 255)
	{
		nBlue = 255;
	}
	return CColor4D(nRed,nGreen,nBlue,rhs.a);
}
CColor4D operator+(const CColor4D& lhs, const CColor4D& rhs)
{
	int nRed = lhs.r+rhs.r;
	if(nRed > 255)
	{
		nRed = 255;
	}
	int nGreen = lhs.g+rhs.g;
	if(nGreen > 255)
	{
		nGreen = 255;
	}
	int nBlue = lhs.b+rhs.b;
	if(nBlue > 255)
	{
		nBlue = 255;
	}
	int nAlph = lhs.a+rhs.a;

	if(nAlph > 255)
	{
		nAlph = 255;
	}
	return CColor4D(nRed,nGreen,nBlue,nAlph);
}
CColor4D operator-(const CColor4D& lhs, const CColor4D& rhs)
{
	int nRed = lhs.r-rhs.r;
	if(nRed < 0)
	{
		nRed = 0;
	}
	int nGreen = lhs.g-rhs.g;
	if(nGreen < 0)
	{
		nGreen = 0;
	}
	int nBlue = lhs.b-rhs.b;
	if(nBlue < 0)
	{
		nBlue = 255;
	}
	int nAlph = lhs.a-rhs.a;

	if(nAlph < 0)
	{
		nAlph = 0;
	}
	return CColor4D(nRed,nGreen,nBlue,nAlph);
}
CColor4D operator/(const CColor4D& lhs, KFLOAT rhs)
{
	if(IsEquivalent(rhs,0.0))
	{
		return CColor4D(lhs._color);
	}
	int nRed = lhs.r/rhs;
	if(nRed > 255)
	{
		nRed = 255;
	}
	int nGreen = lhs.g/rhs;
	if(nGreen > 255)
	{
		nGreen = 255;
	}
	int nBlue = lhs.b/rhs;
	if(nBlue > 255)
	{
		nBlue = 255;
	}
	return CColor4D(nRed,nGreen,nBlue,lhs.a);
}
