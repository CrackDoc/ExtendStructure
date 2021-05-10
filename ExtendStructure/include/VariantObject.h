#ifndef VariantObject_h__
#define VariantObject_h__

#include "ExtendStructureConstant.h"
#include "ExtendStructureExport.h"
#include <map>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Color4D.h"
#include "AABB.h"
#include "OBB.h"
#include "Rectangle2D.h"
#include "DateAttribute.h"
#include "TimeAttribute.h"
#include "DateTimeAttribute.h"
#include "FontAttribute.h"
#include "../../FreezeLib/Include/JsonValue.h"
#include "NamedFeatureObject.h"
#include "NamedArrayFeatureObject.h"
#include "BufferConverter.h"

class CFeatureObject;
//Filed字段定义
class EXTENDSTRUCTURE_EXPORT CVariantObject
	{
public:
// 	class CVariantObjectObserver
// 	{
// 	public:
// 		virtual ~CVariantObjectObserver(){}
// 
// 		virtual void OnValueChanged(const CVariantObject& rValue) = 0;
// 	};

public:
	static const CVariantObject NULL_VALUE;

public:
	enum E_DATA_TYPE
	{
		E_DATA_TYPE_UNKNOWN = 0,
		E_DATA_TYPE_CHAR = 1,
		E_DATA_TYPE_UNSIGNED_CHAR = 2,
		E_DATA_TYPE_SHORT = 3,
		E_DATA_TYPE_UNSIGNED_SHORT = 4,
		E_DATA_TYPE_INTEGER = 5,
		E_DATA_TYPE_UNSIGNED_INTEGER = 6,
		E_DATA_TYPE_ENUM = 7,			//枚举
		E_DATA_TYPE_FLOAT = 8,
		E_DATA_TYPE_DOUBLE = 9,
		E_DATA_TYPE_LONG = 10,
		E_DATA_TYPE_UNSIGNED_LONG = 11,
		E_DATA_TYPE_LONG_LONG = 12,
		E_DATA_TYPE_UNSIGNED_LONG_LONG = 13,
		E_DATA_TYPE_BOOLEAN = 14,
		E_DATA_TYPE_CHAR_BUFFER = 15,
		E_DATA_TYPE_STRING = 16,
		E_DATA_TYPE_RAW_POINTER = 17,	//特殊1
		E_DATA_TYPE_STRUCT		= 18,	//特殊2
		E_DATA_TYPE_VECTOR2D	= 19,	//二维向量
		E_DATA_TYPE_VECTOR3D	= 20,	//三维向量
		E_DATA_TYPE_VECTOR4D	= 21,	//四维向量
		E_DATA_TYPE_COLOR4D		= 22,	//颜色向量
		E_DATA_TYPE_RECTANGLE2D = 23,	//二维区域
		E_DATA_TYPE_AABB		= 24,	//包围盒
		E_DATA_TYPE_OBB			= 25,	//包围球
		E_DATA_TYPE_DATE		= 26,	//日期
		E_DATA_TYPE_TIME		= 27,	//时间
		E_DATA_TYPE_DATE_TIME	= 28,	//日期-时间
		E_DATA_TYPE_FONT		= 29,	//字体
		E_DATA_TYPE_FEATURE		= 40,	//特征
		E_DATA_TYPE_NAMED_FEATURE=41,	//命名特征
		E_DATA_TYPE_ARRAY		= 42,	//数组[==不实现==]
		E_DATA_TYPE_INTEGER_LIST= 43,	//整数数组
		E_DATA_TYPE_FLOAT_LIST	= 44,	//浮点数组
		E_DATA_TYPE_DOUBLE_LIST = 45,	//双精度浮点数组
		E_DATA_TYPE_STRING_LIST = 46,	//字符串数组
		E_DATA_TYPE_WSTRING		= 47,	//宽字符串
		E_DATA_TYPE_WSTRING_LIST= 48,	//宽字符串数组
		E_DATA_TYPE_RESERVERED,
		E_DATA_TYPE_USER		= 100,	//用户定义
	};

	enum E_ORDER_TYPE
	{
		E_ORDER_TYPE_LITTLE = 0,		//本地字节序
		E_ORDER_TYPE_BIG = 1,			//大端字节序
		E_ORDER_TYPE_LOCAL = 2,			//小端字节序
		E_ORDER_TYPE_UNSURPORT = 3,		//不支持的字节序
	};

public:
	CVariantObject(const std::string& strName = "", const std::string& strDesc = "");

	CVariantObject(const CVariantObject& rhs);

	~CVariantObject(void);

	CVariantObject& operator=(const CVariantObject& rhs);

	bool operator==(const CVariantObject& rhs) const;

	bool operator!=(const CVariantObject& rhs) const;

	void SetName(const std::string& strName);

	std::string& GetName();

	const std::string& GetName() const;

	void SetDescription(const std::string& strDescription);

	std::string& GetDescription();

	const std::string& GetDescription() const;

	int GetDataLength() const;

	int GetBufferLength() const;

	bool IsValid() const;

	E_ORDER_TYPE GetLocalOrderType() const;

	void SetDataType(E_DATA_TYPE eDataTye);

	E_DATA_TYPE GetDataType() const;

	void SetOrderType(E_ORDER_TYPE eOrderType);

	E_ORDER_TYPE GetOrderType() const;

	// Brief:仅对整形系列有效 [2016/10/28 CETC] 
	void SetBitNum(int nBitNum);

	void SetVisible(bool bVisible);

	bool IsVisible() const;

	void SetEnable(bool bEnable);

	bool IsEnabled() const;

	void SetScriptEnable(bool bEnable);

	bool IsScriptEnabled() const;

	void SetMinValue(const std::string& strValue);

	void SetMaxValue(const std::string& strValue);

	std::string GetMinValue() const;

	std::string GetMaxValue() const;

	void SetUnit(const std::string& strUnit);

	std::string GetUnit() const;

	void SetUserMask(int nMask);

	int GetUserMask() const;

	void SetFormatDescription(int nIndex, const std::string& strDesc);

	void ClearFormatDescription();

	int GetFormatDescriptionNumber() const;

	//用于枚举
	std::string GetFormatDescription(int nIndex) const;

	std::map<int, std::string>& GetAllFormatDescription();

	const std::map<int, std::string>& GetAllFormatDescription() const;

	void SetScript(const std::string& strValue);

	std::string GetScript() const;

	//这个操作与JSON无关,只是单纯的字符串交换
	void SetExchangeString(const std::string& strValue);

	std::string GetExchangeString() const;

	bool SetExchangeJson(CJsonValue& rJson);

	bool GetExchangeJson(CJsonValue& rJson) const;

	void SetSupportJsonExpression(bool bSupport);

	bool IsJsonExpressionSupport() const;

	std::string GetDataTypeSymbol() const;

	static E_DATA_TYPE ConvertSymbolToDataType(const std::string& strDataTypeSymbol);

	bool CanConvertToJson() const;

public:	//value set
	void SetIntegerValue(int nValue, int nBitNum = 32);

	//-
	void SetUnsignedIntegerValue(unsigned int nValue, int nBitNum = 32);

	void SetEnumValue(int nValue, int nBitNum = 32);

	void SetCharValue(char cValue);

	//-
	void SetUnsignedCharValue(unsigned char cValue);

	void SetShortValue(short sValue, int nBitNum = 16);

	//-
	void SetUnsignedShortValue(unsigned short usValue, int nBitNum = 16);

	void SetFloatValue(float fValue);

	void SetDoubleValue(double dValue);

	void SetLongValue(long lValue);

	//-
	void SetUnsignedLongValue(unsigned long lValue);

	void SetLongLongValue(long long llValue);

	//-
	void SetUnsignedLongLongValue(unsigned long long llValue);

	void SetBooleanValue(bool bValue);

	void SetCharBuffer(const char* pBuffer, int nBufferLen, bool bCopy = true);

	void SetStringValue(const std::string& strValue);

	void SetCharBufferHexString(const std::string& strHex);

	//不支持大小端序
	template <typename T> void SetStructValue(const T& rValue)
	{
		int nSize = sizeof(T);
		if (m_nBufferLength < nSize)
		{
			Allocate(nSize);
		}

		m_nDataLength = nSize;
		m_bValueSet = true;
		m_eDataType = E_DATA_TYPE_STRUCT;
		memcpy(m_pBuffer, &rValue, nSize);
	}

	void SetPointerValue(void* pValue);

	void SetFeatureValue(CFeatureObject* pFeatureObject);

	void SetNamedFeatureValue(const CNamedFeatureObject& rFeature);

	void SetNamedArrayFeatureValue(const CNamedArrayFeatureObject& rFeature);

	void SetVector2DValue(const CVector2D& rValue);

	void SetVector3DValue(const CVector3D& rValue);

	void SetVector4DValue(const CVector4D& rValue);

	void SetColor4DValue(const CColor4D& rValue);

	void SetAABBValue(const CAABB& rValue);

	void SetOBBValue(const COBB& rValue);

	void SetRectangle2DValue(const CRectangle2D& rValue);

	void SetDateValue(const CDateAttribute& rValue);

	void SetTimeValue(const CTimeAttribute& rValue);

	void SetDateTimeValue(const CDateTimeAttribute& rValue);

	void SetFontValue(const CFontAttribute& rValue);

	//--新增
	void SetIntegerListValue(const std::vector<int>& rVaue);

	void SetFloatListValue(const std::vector<float>& rValue);

	void SetDoubleListValue(const std::vector<double>& rValue);

	void SetStringListValue(const std::vector<std::string>& rValue);

	void SetWStringValue(const std::wstring& strValue);

	void SetWStringListValue(const std::vector<std::wstring>& rValue);

public:	//value get
	char GetValueAsChar(bool* bOk = NULL) const;

	unsigned char GetValueAsUnsignedChar(bool* bOk = NULL) const;

	short GetValueAsShort(bool* bOk = NULL) const;

	unsigned short GetValueAsUnsignedShort(bool* bOk = NULL) const;

	int GetValueAsInteger(bool* bOk = NULL) const;

	unsigned int GetValueAsUnsignedInteger(bool* bOk = NULL) const;

	int GetValueAsEnum(bool* bOk = NULL) const;

	float GetValueAsFloat(bool* bOk = NULL) const;

	double GetValueAsDouble(bool* bOk = NULL) const;

	long GetValueAsLong(bool* bOk = NULL) const;

	unsigned long GetValueAsUnsignedLong(bool* bOk = NULL) const;

	long long GetValueAsLongLong(bool* bOk = NULL) const;

	unsigned long long GetValueAsUnsignedLongLong(bool* bOk = NULL) const;

	bool GetValueAsBoolean(bool* bOk = NULL) const;

	char* GetValueAsCharBuffer(bool* bOk = NULL) const;

	std::string GetValueAsString(bool* bOk = NULL) const;

	std::string GetValueAsHexString(bool* bOk = NULL) const;

	template <typename T> T GetValueAsStruct(bool *bOk = NULL) const
	{
		int nSize = sizeof(T);
		if (nSize > m_nDataLength)
		{
			if (NULL != bOk)
			{
				*bOk = false;
			}
			return T();
		}

		if (NULL != bOk)
		{
			*bOk = true;
		}

		T tResult;
		memcpy(&tResult, m_pBuffer, nSize);

		return tResult;
	}

	void* GetValueAsPointer(bool* bOk = NULL) const;

	CFeatureObject* GetValueAsFeature(bool* bOk = NULL) const;

	CNamedFeatureObject GetValueAsNamedFeature(bool* bOk = NULL) const;

	CNamedArrayFeatureObject GetValueAsNamedArrayFeature(bool* bOk = NULL) const;

	CVector2D GetValueAsVector2D(bool* bOk = NULL) const;

	CVector3D GetValueAsVector3D(bool* bOk = NULL) const;

	CVector4D GetValueAsVector4D(bool* bOk = NULL) const;

	CColor4D GetValueAsColor4D(bool* bOk = NULL) const;

	CAABB GetValueAsAABB(bool* bOk = NULL) const;

	COBB GetValueAsOBB(bool* bOk = NULL) const;

	CRectangle2D GetValueAsRectangle2D(bool* bOk = NULL) const;

	CDateAttribute GetValueAsDate(bool* bOk = NULL) const;

	CTimeAttribute GetValueAsTime(bool* bOk = NULL) const;

	CDateTimeAttribute GetValueAsDateTime(bool* bOk = NULL) const;

	CFontAttribute GetValueAsFont(bool* bOk = NULL) const;

	//--新增
	std::vector<int> GetValueAsIntegerList(bool* bOk = NULL) const;

	std::vector<float> GetValueAsFloatList(bool* bOk = NULL) const;

	std::vector<double> GetValueAsDoubleList(bool* bOk = NULL) const;

	std::vector<std::string> GetValueAsStringList(bool* bOk = NULL) const;

	std::wstring GetValueAsWString(bool* bOk = NULL) const;

	std::vector<std::wstring> GetValueAsWStringList(bool* bOk = NULL) const;

public:	//copy value
	int CopyValue(void* pDst, int nMaxLength) const;

	// Brief:强制更改缓冲区,如果数据类型已定,那么默认写入需要的长度 [2016/10/20 CETC] 
	int ForceWriteValue(void* pSrc, int nSrcLen = -1);

protected:
	
	//无效节点构造函数
	CVariantObject(bool bValid);

	bool Allocate(int nDataLength);

	void Release();

	int GetDefaultSize(E_DATA_TYPE eDataType);

protected:
	
	bool m_bValueSet;
	E_DATA_TYPE m_eDataType;		//数据类型
	E_ORDER_TYPE m_eOrderType;		//字节序
	int m_nDataLength;				//数据长度
	int m_nBufferLength;			//缓冲区长度
	char* m_pBuffer;				//缓冲区
	std::string m_strName;			//名称
	std::string m_strDescription;	//描述
	bool m_bVisible;				//可见性
	bool m_bEnable;					//是否允许
	bool m_bScriptEnable;			//脚本是否启用
	std::string m_strMinValue;		//最小值
	std::string m_strMaxValue;		//最大值
	std::string m_strUnit;			//单位
	int m_nUserMask;				//用户掩码
	std::string m_strScript;		//脚本
	bool m_bJsonSupport;			//JSON支持
	std::map<int, std::string> m_mapFormatDescription;	//格式化描述
};

BufferConverter::E_BYTEORDER_TYPE VariantOrderTypeToBufferOrderType(CVariantObject::E_ORDER_TYPE eOrderType);

#endif // VariantObject_h__

