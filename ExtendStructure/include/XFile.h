#pragma once
#ifndef XFile_h__
#define XFile_h__

#include "ExtendStructureExport.h"
#include "XDir.h"
#include <iostream> 
#include <fstream>

namespace IOx
{
	class XDir;

    class  ExtendStructure_EXPORT XFile
    {
    public:
        XFile(const char * strFilePath = "");

		//通过目录和文件来构造文件对象
		XFile(const XDir& rDir, const char * strFileName);

        XFile(const XFile& rhs);

        ~XFile();

        bool operator==(const XFile& rhs);

        XFile& operator=(const XFile& rhs);

        bool exist() const;

        //绝对路径 [10/30/2015 Administrator]
        const char *absolutePath() const;

        //相对路径
        const char * relativePath() const;

		// 绝对路径目录 [2/22/2016 Administrator]
		const char* absoluteDir() const;

        int size();

        void dir(XDir& rDir);

        bool valid() const;

        const char * suffix() const;

        const char* baseName() const;

        const char* fileName() const;

        void setFilePath(const char * strFilePath);

        static bool isAbsolutePath(const char *strFilePath);

		static XFile getApplicationPath();

    public:

        //打开文件
        bool open(bool bReadOnly = true);

        //读文件
        bool read(unsigned char* pBuffer, int nSize = -1);

        //写文件
        bool write(unsigned char* pBuffer, int nSize);

        //关闭文件
        void close();

        //是否打开
        bool isOpen() const;

        bool create();

        bool remove() const;

        void clear();

		void SplitDir(void *input) const;

		void Normalize();

		bool copyTo(const XFile& rFile) const;

		bool copyToDir(const XDir& rDir) const;

    protected:
        char mAbsolutePath[256];
        char mRelativePath[256];
        std::ofstream mWriteStream; //写文件流
        std::ifstream mReadStream;  //读文件流
        int  mFileSize;
        char m_strSuffix[20];
        char m_strBaseName[32];
        char m_strFileName[52];
        XDir *m_Dir;
    };
}

#endif // XFile_h__

