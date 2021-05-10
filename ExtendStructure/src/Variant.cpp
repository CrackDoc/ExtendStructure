#include "Variant.h"
#include <string>
Variant::Variant():
	 ptr(NULL)
	,mSharedMemory(false) 
{

}

Variant::~Variant()
{

}

void Variant::destroy()
{
	if(ptr != NULL)
	{
		delete ptr;
		ptr = NULL;
		mSize = 0;
		mFixedSize = 0;
		//mType.clear();
		mSharedMemory = false;
	}
}

void Variant::zero()
{
	memset(ptr,'\0',mSize);
}

bool Variant::isValid() const
{
	return (ptr != NULL);
}

int Variant::size() const
{
	return mSize;
}

bool Variant::isShared() const
{
	return mSharedMemory;
}
Variant& Variant::operator=( Variant rValue )
{
	mSize = rValue.size();
	//mType = rValue.typeString();
	memcpy(ptr,rValue.toVoidPtr(),rValue.size());
	return *this;
}

void Variant::construct( char c )
{
	ptr = new char(1);
	char *szPtr = (char*)ptr;
	*szPtr = c;
	mFixedSize = 1;
	mSize = 1;
	//mType = "char";
}

void Variant::construct( unsigned char uc )
{
	ptr = new unsigned char(1);
	unsigned char *szPtr = (unsigned char*)ptr;
	*szPtr = uc;
	mFixedSize = 1;
	mSize = 1;
	//mType = "unsigned char";
}

void Variant::construct( short s )
{
	ptr = new short(1);
	short *szPtr = (short*)ptr;
	*szPtr = s;
	mFixedSize = 2;
	mSize = 2;
	//mType = "short";

}

void Variant::construct( unsigned short us )
{
	ptr =  new unsigned short(1);
	unsigned short *szPtr = (unsigned short*)ptr;
	*szPtr = us;
	mFixedSize = 2;
	mSize = 2;
	//mType = "unsigned short";

}

void Variant::construct( int i )
{
	ptr =  new int(1);
	int *szPtr = (int*)ptr;
	*szPtr = i;
	mFixedSize = 4;
	mSize = 4;
	//mType = "int";
}

void Variant::construct( unsigned int i )
{
	ptr =  new unsigned int(1);
	unsigned int *szPtr = (unsigned int*)ptr;
	*szPtr = i;
	mFixedSize = 4;
	mSize = 4;
	//mType = "unsigned int";

}

void Variant::construct( long long ll )
{
	ptr =  new long long (1);
	long long  *szPtr = (long long *)ptr;
	*szPtr = ll;
	mFixedSize = 8;
	mSize = 8;
	//mType = "long long";
}

void Variant::construct( unsigned long long ull )
{
	ptr =  new unsigned long long (1);
	unsigned long long  *szPtr = (unsigned long long *)ptr;
	*szPtr = ull;
	mFixedSize = 8;
	mSize = 8;
	//mType = "unsigned long long";
}

void Variant::construct( float f )
{
	ptr =  new float (1);
	float  *szPtr = (float *)ptr;
	*szPtr = f;
	mFixedSize = 4;
	mSize = 4;
	//mType = "float";
}

void Variant::construct( double d )
{
	ptr =  new double (1);
	double  *szPtr = (double *)ptr;
	*szPtr = d;
	mFixedSize = 8;
	mSize = 8;
	//mType = "double";

}

void Variant::construct( void* srcPtr,int nSize)
{
	mFixedSize = nSize;
	mSize = nSize;
	//mType = "void *";
	memcpy(srcPtr,ptr,nSize);
}

char Variant::toChar() const
{
	return c;
}

unsigned char Variant::toUChar() const
{
	return uc;
}

short Variant::toShort() const
{
	return s;
}

unsigned short Variant::toUShort() const
{
	return us;
}

int Variant::toInt() const
{
	return i;
}

unsigned int Variant::toUInt() const
{
	return ui;
}

long long Variant::toLongLong() const
{
	return ll;
}

unsigned long long Variant::toULongLong() const
{
	return ull;
}

float Variant::toFloat() const
{
	return f;
}

double Variant::toDouble() const
{
	return d;
}

void* Variant::toVoidPtr() const
{
	return ptr;
}

void Variant::toString(void *input) const
{
	*static_cast<std::string*>(input) = *static_cast<std::string*>(ptr);
}

