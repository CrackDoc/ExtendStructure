#pragma once
#ifndef Color4D_h__
#define Color4D_h__

#include "ExtendStructureConstant.h"
#include "ExtendStructureExport.h"

//向量
class ExtendStructure_EXPORT CColor4D
{
public:
	enum
	{
		NUM_MAX_MONO_COLOR = 0xFF,
		E_DATA_LENGTH = 4,
	};

	static const CColor4D COLOR_NONE;	//无色透明
	static const CColor4D COLOR_BLACK;	//黑色
	static const CColor4D COLOR_RED;	//红色
	static const CColor4D COLOR_GREEN;	//绿色
	static const CColor4D COLOR_BLUE;	//蓝色
	static const CColor4D COLOR_WHITE;	//白色
	static const CColor4D COLOR_YELLOW;	//黄色
public:
	CColor4D();

	CColor4D(KFLOAT _r, KFLOAT _g, KFLOAT _b, KFLOAT _a);

	CColor4D(int _r, int _g, int _b, int _a);

	CColor4D(int nColor);

	CColor4D(const CColor4D& rhs);

	~CColor4D(void);

	CColor4D& operator=(const CColor4D& rhs);

	CColor4D& operator=(unsigned int nColor);

	bool operator==(const CColor4D& rhs) const;

	bool operator!=(const CColor4D& rhs) const;

	bool operator<(const CColor4D& rhs) const;

	unsigned int GetColor() const;

	unsigned char GetRed() const;

	KFLOAT GetRedF() const;

	unsigned char GetGreen() const;

	KFLOAT GetGreenF() const;

	unsigned char GetBlue() const;

	KFLOAT GetBlueF() const;

	unsigned char GetAlpha() const;

	KFLOAT GetAlphaF() const;

	void SetColor(unsigned int nColor);

	void SetRedF(KFLOAT fRed);

	void SetRed(unsigned char nRed);

	void SetGreedF(KFLOAT fGreen);

	void SetGreen(unsigned char nGreen);

	void SetBlueF(KFLOAT fBlue);

	void SetBlue(unsigned char nBlue);

	void SetAlphaF(KFLOAT fAlpha);

	void SetAlpha(unsigned char nAlpha);

	void SetARGB(int nArgbColor);

	int GetARGB() const;

	void ToHSV(KFLOAT& H, KFLOAT& S, KFLOAT& V);

	void FromHSV(KFLOAT H, KFLOAT S, KFLOAT	V);

	static CColor4D P3(const CColor4D& C0, const CColor4D& C1, const CColor4D& C2, KFLOAT u, KFLOAT v);

public:
	static CColor4D FromARGB(int nArgb);

public:
	union
	{
		struct  
		{
			unsigned char r, g, b, a;
		};

		unsigned char _v[4];
		unsigned int _color;
	};
};

ExtendStructure_EXPORT CColor4D operator*(const CColor4D& lhs, KFLOAT rhs);

ExtendStructure_EXPORT CColor4D operator*(KFLOAT lhs, const CColor4D& rhs);

ExtendStructure_EXPORT CColor4D operator+(const CColor4D& lhs, const CColor4D& rhs);

ExtendStructure_EXPORT CColor4D operator-(const CColor4D& lhs, const CColor4D& rhs);

ExtendStructure_EXPORT CColor4D operator/(const CColor4D& lhs, KFLOAT rhs);

#endif // Color4D_h__
