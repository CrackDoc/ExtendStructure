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
//Filed�ֶζ���
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
		E_DATA_TYPE_ENUM = 7,			//ö��
		E_DATA_TYPE_FLOAT = 8,
		E_DATA_TYPE_DOUBLE = 9,
		E_DATA_TYPE_LONG = 10,
		E_DATA_TYPE_UNSIGNED_LONG = 11,
		E_DATA_TYPE_LONG_LONG = 12,
		E_DATA_TYPE_UNSIGNED_LONG_LONG = 13,
		E_DATA_TYPE_BOOLEAN = 14,
		E_DATA_TYPE_CHAR_BUFFER = 15,
		E_DATA_TYPE_STRING = 16,
		E_DATA_TYPE_RAW_POINTER = 17,	//����1
		E_DATA_TYPE_STRUCT		= 18,	//����2
		E_DATA_TYPE_VECTOR2D	= 19,	//��ά����
		E_DATA_TYPE_VECTOR3D	= 20,	//��ά����
		E_DATA_TYPE_VECTOR4D	= 21,	//��ά����
		E_DATA_TYPE_COLOR4D		= 22,	//��ɫ����
		E_DATA_TYPE_RECTANGLE2D = 23,	//��ά����
		E_DATA_TYPE_AABB		= 24,	//��Χ��
		E_DATA_TYPE_OBB			= 25,	//��Χ��
		E_DATA_TYPE_DATE		= 26,	//����
		E_DATA_TYPE_TIME		= 27,	//ʱ��
		E_DATA_TYPE_DATE_TIME	= 28,	//����-ʱ��
		E_DATA_TYPE_FONT		= 29,	//����
		E_DATA_TYPE_FEATURE		= 40,	//����
		E_DATA_TYPE_NAMED_FEATURE=41,	//��������
		E_DATA_TYPE_ARRAY		= 42,	//����[==��ʵ��==]
		E_DATA_TYPE_INTEGER_LIST= 43,	//��������
		E_DATA_TYPE_FLOAT_LIST	= 44,	//��������
		E_DATA_TYPE_DOUBLE_LIST = 45,	//˫���ȸ�������
		E_DATA_TYPE_STRING_LIST = 46,	//�ַ�������
		E_DATA_TYPE_WSTRING		= 47,	//���ַ���
		E_DATA_TYPE_WSTRING_LIST= 48,	//���ַ�������
		E_DATA_TYPE_RESERVERED,
		E_DATA_TYPE_USER		= 100,	//�û�����
	};

	enum E_ORDER_TYPE
	{
		E_ORDER_TYPE_LITTLE = 0,		//�����ֽ���
		E_ORDER_TYPE_BIG = 1,			//����ֽ���
		E_ORDER_TYPE_LOCAL = 2,			//С���ֽ���
		E_ORDER_TYPE_UNSURPORT = 3,		//��֧�ֵ��ֽ���
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

	// Brief:��������ϵ����Ч [2016/10/28 CETC] 
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

	//����ö��
	std::string GetFormatDescription(int nIndex) const;

	std::map<int, std::string>& GetAllFormatDescription();

	const std::map<int, std::string>& GetAllFormatDescription() const;

	void SetScript(const std::string& strValue);

	std::string GetScript() const;

	//���������JSON�޹�,ֻ�ǵ������ַ�������
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

	//��֧�ִ�С����
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

	//--����
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

	//--����
	std::vector<int> GetValueAsIntegerList(bool* bOk = NULL) const;

	std::vector<float> GetValueAsFloatList(bool* bOk = NULL) const;

	std::vector<double> GetValueAsDoubleList(bool* bOk = NULL) const;

	std::vector<std::string> GetValueAsStringList(bool* bOk = NULL) const;

	std::wstring GetValueAsWString(bool* bOk = NULL) const;

	std::vector<std::wstring> GetValueAsWStringList(bool* bOk = NULL) const;

public:	//copy value
	int CopyValue(void* pDst, int nMaxLength) const;

	// Brief:ǿ�Ƹ��Ļ�����,������������Ѷ�,��ôĬ��д����Ҫ�ĳ��� [2016/10/20 CETC] 
	int ForceWriteValue(void* pSrc, int nSrcLen = -1);

protected:
	
	//��Ч�ڵ㹹�캯��
	CVariantObject(bool bValid);

	bool Allocate(int nDataLength);

	void Release();

	int GetDefaultSize(E_DATA_TYPE eDataType);

protected:
	
	bool m_bValueSet;
	E_DATA_TYPE m_eDataType;		//��������
	E_ORDER_TYPE m_eOrderType;		//�ֽ���
	int m_nDataLength;				//���ݳ���
	int m_nBufferLength;			//����������
	char* m_pBuffer;				//������
	std::string m_strName;			//����
	std::string m_strDescription;	//����
	bool m_bVisible;				//�ɼ���
	bool m_bEnable;					//�Ƿ�����
	bool m_bScriptEnable;			//�ű��Ƿ�����
	std::string m_strMinValue;		//��Сֵ
	std::string m_strMaxValue;		//���ֵ
	std::string m_strUnit;			//��λ
	int m_nUserMask;				//�û�����
	std::string m_strScript;		//�ű�
	bool m_bJsonSupport;			//JSON֧��
	std::map<int, std::string> m_mapFormatDescription;	//��ʽ������
};

BufferConverter::E_BYTEORDER_TYPE VariantOrderTypeToBufferOrderType(CVariantObject::E_ORDER_TYPE eOrderType);

#endif // VariantObject_h__

