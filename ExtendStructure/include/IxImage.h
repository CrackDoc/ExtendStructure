#ifndef IxImage_h__
#define IxImage_h__
#include "ExtendStructureExport.h"
#include "Cache.h"
class ExtendStructure_EXPORT CIxImage
{
public:
	enum E_IMAGE_TYPE
	{
		E_JPG,
		E_PNG,
		E_BMP,
		E_TGA,
		E_HDR
	};
public:
	CIxImage();
	CIxImage(int nWidth,int nHeight);
	~CIxImage(void);

	bool LoadFromData(const char *szBuffer,int nLength,bool bDeepCopy);

	bool LoadFromCache(CCache &cache);

	bool LoadFromFile(const char *szFile);

	bool Save(const char* szFile,E_IMAGE_TYPE eType = E_JPG);

private:
	int m_nPixWidth;
	int m_nPixHeight;
	CCache m_CCache;
	int nBandCnt;
};
#endif // IxImage_h__

