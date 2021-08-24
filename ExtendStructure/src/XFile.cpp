#include "XFile.h"
#include "StlUtil.h"
#include <sstream>
#include <vector>
#include <locale.h>  
#include <locale>  
#include <assert.h>
#include <memory.h>
#include <cstring>
using std::locale;  

namespace IOx
{
	XFile::XFile( const char *strFilePath /*= ""*/ )
	{
		memset(mAbsolutePath, '\0', sizeof(char) * 256);
		memset(mRelativePath, '\0', sizeof(char) * 256);
		memset(m_strSuffix, '\0', sizeof(char) * 20);
		memset(m_strBaseName, '\0', sizeof(char) * 32);
		memset(m_strFileName, '\0', sizeof(char) * 52);
		int  mFileSize = 0;
		std::string file;

		m_Dir =  new IOx::XDir(strFilePath);

		stlu::normalizePath(&file,strFilePath);
		std::string strSuffix;
		stlu::parseFileSuffix(&strSuffix,file.c_str());
		strcat_s(m_strSuffix, strSuffix.c_str());
		std::string strBaseName;
		stlu::parseFileBaseName(&strBaseName, file.c_str());
		strcat_s(m_strBaseName, strBaseName.c_str());

		std::string strFileName;
		stlu::parseFileName(&strFileName, file.c_str());
		strcat_s(m_strFileName, strFileName.c_str());

		XDir xDir(file.c_str());
		std::string strRelativePath = std::string(xDir.relativePath()) + std::string(m_strFileName);
		std::string strmAbsolutePath = std::string(xDir.absolutePath()) + "/" + std::string(m_strFileName);
		strcat_s(mRelativePath, strRelativePath.c_str());
		strcat_s(mAbsolutePath, strmAbsolutePath.c_str());
	}

	XFile::XFile( const XDir& rDir, const char* szstrFileName )
	{
		m_Dir = new IOx::XDir(rDir.absolutePath());
		m_Dir->Normalize();
		memset(mAbsolutePath, '\0', sizeof(char) * 256);
		memset(mRelativePath, '\0', sizeof(char) * 256);
		memset(m_strSuffix, '\0', sizeof(char) * 20);
		memset(m_strBaseName, '\0', sizeof(char) * 32);
		memset(m_strFileName, '\0', sizeof(char) * 52);
		int  mFileSize = 0;
		std::string file = std::string(m_Dir->absolutePath()) + "/" + std::string(szstrFileName);
		std::string strSuffix;
		stlu::parseFileSuffix(&strSuffix, file.c_str());
        strcat(m_strSuffix, strSuffix.c_str());

		std::string strBaseName;
		stlu::parseFileBaseName(&strBaseName, file.c_str());
		strcat_s(m_strBaseName, strBaseName.c_str());

		std::string strFileName;
		stlu::parseFileName(&strFileName, file.c_str());
		strcat_s(m_strFileName, strFileName.c_str());

		XDir xDir(file.c_str());
		std::string strRelativePath = std::string(xDir.relativePath()) + std::string(m_strFileName);
		std::string strmAbsolutePath = std::string(xDir.absolutePath()) + "/" + std::string(m_strFileName);
		strcat_s(mRelativePath, strRelativePath.c_str());
		strcat_s(mAbsolutePath, strmAbsolutePath.c_str());

	}

	XFile::XFile( const XFile& rhs )
	{
		*this = rhs;
	}

	XFile::~XFile()
	{

	}

	bool XFile::exist() const
	{
		return stlu::fileExist(mAbsolutePath);
	}

	const char* XFile::absolutePath() const
	{
		return mAbsolutePath;

	}
	const char* XFile::relativePath() const
	{
		return mRelativePath;
	}

	const char* XFile::absoluteDir() const
	{
		return m_Dir->absolutePath();
	}

	int XFile::size()
	{
		mFileSize = stlu::fileSize(mAbsolutePath);
		return mFileSize;
	}

	void XFile::dir( XDir& rDir )
	{
		rDir.setDirPath(absoluteDir());
	}

	bool XFile::valid() const
	{
		XDir xDir(mAbsolutePath);

		if(!xDir.valid())
		{
			return false;
		}
		std::string strName = fileName();
		if(strName.empty())
		{
			return false;
		}
		// 3 特殊字符
		if(strName.find("/") > 0 || strName.find("/") > 0 || strName.find(":") > 0 || strName.find("*") > 0 || strName.find("?") > 0 
			|| strName.find("\"") > 0|| strName.find("<") > 0 || strName.find(">") > 0)
		{
			return false;
		}
		return true;
	}
	const char* XFile::suffix() const
	{
		return m_strSuffix;
	}

	const char* XFile::baseName() const
	{
		return m_strBaseName;
	}

	const char* XFile::fileName() const
	{
		return m_strFileName;
	}

	void XFile::setFilePath( const char* strFilePath )
	{
		memset(mAbsolutePath, '\0', sizeof(char) * 256);
		memset(mRelativePath, '\0', sizeof(char) * 256);
		memset(m_strSuffix, '\0', sizeof(char) * 20);
		memset(m_strBaseName, '\0', sizeof(char) * 32);
		memset(m_strFileName, '\0', sizeof(char) * 52);
		int  mFileSize = 0;
		std::string file = strFilePath;
		m_Dir = new IOx::XDir(file.c_str());
		std::string strSuffix;
		stlu::parseFileSuffix(&strSuffix, file.c_str());
		strcat_s(m_strSuffix, strSuffix.c_str());

		std::string strBaseName;
		stlu::parseFileBaseName(&strBaseName, file.c_str());
		strcat_s(m_strBaseName, strBaseName.c_str());

		std::string strFileName;
		stlu::parseFileName(&strFileName, file.c_str());
		strcat_s(m_strFileName, strFileName.c_str());

		XDir xDir(file.c_str());
		std::string strRelativePath = std::string(xDir.relativePath()) + std::string(m_strFileName);
		std::string strmAbsolutePath = std::string(xDir.absolutePath()) + "/" + std::string(m_strFileName);
		strcat_s(mRelativePath, strRelativePath.c_str());
		strcat_s(mAbsolutePath, strmAbsolutePath.c_str());
	}

	bool XFile::isAbsolutePath( const char *strFilePath )
	{
		return XDir::isAbsolutePath(strFilePath);
	}

	XFile XFile::getApplicationPath()
	{
		std::string strMoudule;
		stlu::moduleDir(&strMoudule);
		return XFile(strMoudule.c_str());
	}

	bool XFile::open( bool bReadOnly /*= true*/)
	{
		locale loc = std::locale::global(std::locale(""));
		bool bOpen = false;
		if(bReadOnly)
		{
			mReadStream.open(mAbsolutePath);
			bOpen = mReadStream.is_open();
		}
		else
		{
			mWriteStream.open(mAbsolutePath);
			bOpen = mWriteStream.is_open();

		}
		locale::global(loc);
		return bOpen;
	}

	bool XFile::read( unsigned char* pBuffer, int nSize /*= -1*/ )
	{
		int readBytes = 0;
		int nTotalFileSize = size();

		if (nSize > 0 && nSize <= nTotalFileSize)
		{
			//开辟相应的缓冲区
			pBuffer =  new unsigned char[nSize];
			memset(pBuffer,0,sizeof(unsigned char)*nSize);

			while(!mReadStream.eof() && readBytes < nSize)
			{
				mReadStream.read((char *)pBuffer + readBytes,nSize - readBytes);
				if (mReadStream.fail())
				{
					delete pBuffer;
					pBuffer = NULL;
					return false;
				}
				readBytes += (int)mReadStream.gcount();
			}
			mReadStream.clear();
		}
		return true;
	}

	bool XFile::write( unsigned char* pBuffer, int nSize )
	{
		mWriteStream.write((char *)pBuffer,nSize);
		return true;
	}

	void XFile::close()
	{
		if(mReadStream.is_open())
		{
			mReadStream.close();
		}
		if(mWriteStream.is_open())
		{
			mWriteStream.close();
		}
	}

	bool XFile::isOpen() const
	{
		return mReadStream.is_open() || mWriteStream.is_open();
	}

	bool XFile::create()
	{
		return stlu::fileCreate(mAbsolutePath);
	}

	bool XFile::remove() const
	{
		return stlu::fileRemove(mAbsolutePath);
	}

	void XFile::clear()
	{
		memset(mAbsolutePath, '\0', sizeof(char) * 256);
		memset(mRelativePath, '\0', sizeof(char) * 256);
		memset(m_strSuffix, '\0', sizeof(char) * 20);
		memset(m_strBaseName, '\0', sizeof(char) * 32);
		memset(m_strFileName, '\0', sizeof(char) * 52);
		int  mFileSize = 0;
	}

	void XFile::SplitDir(void *input) const
	{
		assert(input);
		stlu::split(mAbsolutePath,"/",input);
	}

	void XFile::Normalize()
	{
		std::string strNormlize;
		stlu::normalizePath(&strNormlize,mAbsolutePath);
		memset(mAbsolutePath, '\0', sizeof(char) * 256);
		strcat_s(mAbsolutePath, strNormlize.c_str());
	}

	bool XFile::copyTo( const XFile& rFile ) const
	{
		std::string strDestFile = rFile.absoluteDir();
		return stlu::fileCopy(mAbsolutePath,strDestFile.c_str());
	}

	bool XFile::copyToDir( const XDir& rDir ) const
	{
		std::string strDestDir = rDir.absolutePath();

		return stlu::fileCopy(mAbsolutePath,strDestDir.c_str());
	}

	XFile& XFile::operator=( const XFile& rhs )
	{
		memset(mAbsolutePath, '\0', sizeof(char) * 256);
		memset(mRelativePath, '\0', sizeof(char) * 256);
		memset(m_strSuffix, '\0', sizeof(char) * 20);
		memset(m_strBaseName, '\0', sizeof(char) * 32);
		memset(m_strFileName, '\0', sizeof(char) * 52);
		int  mFileSize = 0;

		std::string file = rhs.absolutePath();

		m_Dir = new IOx::XDir(file.c_str());

		std::string strSuffix;
		stlu::parseFileSuffix(&strSuffix, file.c_str());
		strcat_s(m_strSuffix, strSuffix.c_str());

		std::string strBaseName;
		stlu::parseFileBaseName(&strBaseName, file.c_str());
		strcat_s(m_strBaseName, strBaseName.c_str());

		std::string strFileName;
		stlu::parseFileName(&strFileName, file.c_str());
		strcat_s(m_strFileName, strFileName.c_str());

		XDir xDir(file.c_str());
		std::string strRelativePath = std::string(xDir.relativePath()) + std::string(m_strFileName);
		std::string strmAbsolutePath = std::string(xDir.absolutePath()) + "/" + std::string(m_strFileName);
		strcat_s(mRelativePath, strRelativePath.c_str());
		strcat_s(mAbsolutePath, strmAbsolutePath.c_str());

		return *this;
	}

	bool XFile::operator==( const XFile& rhs )
	{
		return strcmp(mAbsolutePath, rhs.absolutePath()) == 0;
	}

}


