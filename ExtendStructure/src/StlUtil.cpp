#include "StlUtil.h"
#ifdef WIN32
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <codecvt>
#elif defined __linux__
#include <unistd.h>
#include <sys/stat.h> 　
#include <sys/types.h>
#elif defined VXWORKS
#endif
#include <stdio.h>
#include <locale.h>  
#include <locale>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <list>
#include <time.h>
#include <assert.h>

using std::locale;  

using namespace std;

namespace stlu
{
	 bool upper(void* szstrSrc)
	{
		 assert(szstrSrc);
		 string& strSrc = *static_cast<string*>(szstrSrc);

		 transform(strSrc.begin(), strSrc.end(), strSrc.begin(), ::toupper);
		 
		 return true;
	}
	bool lower(void* szstrSrc)
	{
		assert(szstrSrc);
		string& strSrc = *static_cast<string*>(szstrSrc);

		transform(strSrc.begin(), strSrc.end(), strSrc.begin(), ::tolower);

		return true;
	}
	bool trimC(void* szstrSrc)
	{
		assert(szstrSrc);
		string& strSrc = *static_cast<string*>(szstrSrc);
		std::string::iterator it = strSrc.begin();
		for (; it != strSrc.end();)
		{
			if (*it == ' ')
			{
				it = strSrc.erase(it);
			}
			else
			{
				++it;
			}
		}
		return true;

	}
	void trim(void* szstrSrc)
	{
		assert(szstrSrc);
		string& strSrc = *static_cast<string*>(szstrSrc);

		std::string::iterator it = strSrc.begin();
		for (; it != strSrc.end();)
		{
			if (*it == ' ')
			{
				it = strSrc.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void trimLeft(void* szstrSrc, const char* szstrToken /*= "\n"*/)
	{
		assert(szstrSrc);
		string& strSrc = *static_cast<string*>(szstrSrc);
		string strToken = szstrToken;
		if (strSrc.empty() || strToken.empty())
		{
			return;
		}
		string drop = strToken;

		if ((int)strSrc.find(drop) < 0)
		{
			return;
		}
		strSrc.erase(0, strSrc.find_first_of(drop));
	}

	void trimRight(void* szstrSrc, const char* szstrToken /*= "\n"*/)
	{
		assert(szstrSrc);
		string& strSrc = *static_cast<string*>(szstrSrc);
		string strToken = szstrToken;

		if(strSrc.empty() || strToken.empty())
		{
			return;
		}

		string drop = strToken;
		if((int)strSrc.find(drop) < 0)
		{
			return;
		}
        int pos = strSrc.find_last_of(drop);
		strSrc.erase(pos);
	}

	void replace(void* szstrSrc, const char* szorigial, const char* szstrToken)
	{
		assert(szstrSrc);
		string &strSrc = *static_cast<string*>(szstrSrc);
		string strToken = szstrToken;
		string origial = szorigial;
		if(strSrc.empty() || origial.empty() || strToken.empty())
		{
			return;
		}
		string drop = strToken;
		int len = origial.length();
		int index = (int)strSrc.find_first_of(szorigial);
		while(index > 0)
		{
			strSrc.replace(index,len,drop);
			index = (int)strSrc.find_first_of(szorigial);
		}
	}

    int firstToken(const char* szstrSrc, const char* szstrToken)
	{
		std::string strSrc = szstrSrc;
		std::string strToken = szstrToken;
		if(strSrc.empty() || strToken.empty())
		{
			return -1;
		}
		return strSrc.find_first_of(strToken);
	}
	bool isStartWith(const char* szstrSrc, const char* szstrToken)
	{
		std::string strSrc = szstrSrc;
		std::string strToken = szstrToken;

		if(strSrc.empty() || strToken.empty())
		{
			return false;
		}
		return strSrc.find(strToken)==0?true:false;
	}
	bool isEndWith(const char* szstrSrc, const char* szstrToken)
	{
		std::string strSrc = szstrSrc;
		std::string strToken = szstrToken;
		if(strSrc.empty() || strToken.empty())
		{
			return false;
		}
		return strSrc.rfind(strToken)==(strSrc.length()-strToken.length())?true:false;
	}
	void split(const char* szstrSrc, const char* szstrToken, void* input)
	{  
		assert(input);

		string strSrc = szstrSrc;
		string token = szstrToken;
		std::vector<std::string>& vStr = *static_cast<vector<string>*>(input);
		if(strSrc.empty() || token.empty())
		{
			return;
		}
		char * strs = new char[strSrc.length() + 1] ;
		strcpy(strs, strSrc.c_str());   
		char * d = new char[token.length() + 1];  
		strcpy(d, token.c_str());  
		char *p = strtok(strs, d);  
		while(p) {  
			string s = p; //分割得到的字符串转换为string类型 
			vStr.push_back(s); //存入结果数组 
			p = strtok(NULL, d);  
		}
		delete[]strs;
		delete[]d;
	}
	void reverse(void* szstrSrc)
	{
		assert(szstrSrc);
		string &strSrc = *static_cast<string*>(szstrSrc);
		if(strSrc.empty())
		{
			return;
		}
		std::reverse(strSrc.begin(),strSrc.end());
	}
	bool extendName(void* input, const char* szstrSrc, const char* szstrToken)
	{
		assert(input);

		string strSrc = szstrSrc;
		string strToken = szstrToken;

		if(strSrc.empty() || strToken.empty())
		{
			return false;
		}
		string drop = strToken;

		if((int)strSrc.find(drop) < 0)
		{
			return false;
		}
		strSrc.erase(0, strSrc.find_first_of(drop));

		*static_cast<string*>(input) = *static_cast<string*>(&strSrc);

		return true;

	}
	bool complateDir(void* input, const char* szpath, const char* sztoken)
	{
		assert(input);

		string path = szpath;
		if ((int)path.find("\\") > 0)
		{
			replace(&path, "\\", "/");
		}
		string token = sztoken;

		if(path.empty() || token.empty())
		{
			return false;
		}
		std::string strDest;
		normalizePath(&strDest,path.c_str());

		if((int)strDest.find(".") > 0)
		{
			trimRight(&strDest,"/");
		}
		if(!isEndWith(path.c_str(),token.c_str()))
		{
			std::stringstream ss;
			ss<<strDest<<"/";
			strDest = ss.str();
		}
		*static_cast<string*>(input) = *static_cast<string*>(&strDest);

		return true;
	}
	void eraserSuffix(void* szstr)
	{
		assert(szstr);
		string& str = *static_cast<string*>(szstr);
		if ((int)str.find("\\") > 0)
		{
			replace(&str, "\\", "/");
		}
		if(str.empty())
		{
			return;
		}
		string drop = ".";
		if((int)str.find(drop) < 0)
		{
			return;
		}
		str.erase(str.find_last_of(drop));
	}
	void eraserLastOf(void* szstr, const char* sztoken)
	{
		assert(szstr);

		string& str = *static_cast<string*>(szstr);
		if ((int)str.find("\\") > 0)
		{
			replace(&str, "\\", "/");
		}
		string token = sztoken;

		if(str.empty() || token.empty())
		{
			return;
		}
		string drop = token;

		if((int)str.find(drop) < 0)
		{
			return;
		}
		str.erase(str.find_last_of(drop)+1);

	}
	void endOfString(void* szstr, const char* sztoken)
	{
		assert(szstr);
		string& str = *static_cast<string*>(szstr);
		if ((int)str.find("\\") > 0)
		{
			replace(&str, "\\", "/");
		}
		string token = sztoken;

		if(str.empty() || token.empty())
		{
			return;
		}
		std::stringstream ss;
		ss<<str<<token;
		str = ss.str();
	}
	bool parseFileName(void* input, const char* szpath)
	{
		assert(input);

		string path = szpath;

		if(path.empty())
		{
			return false;
		}
		if ((int)path.find("\\") > 0)
		{
			replace(&path, "\\", "/");
		}
		string drop = "/";
		string strDest;
		normalizePath(&strDest,path.c_str());

		if((int)strDest.find(drop) < 0)
		{
			return false;
		}
		strDest.erase(0,strDest.find_last_of(drop)+1);

		*static_cast<string*>(input) = *static_cast<string*>(&strDest);

		return true;
	}

	bool parseFileSuffix(void* input, const char* szstrPath)
	{
		assert(input);
		string drop = ".";
		string strPath = szstrPath;

		if ((int)strPath.find("\\") > 0)
		{
			replace(&strPath, "\\", "/");
		}

		if(strPath.empty() || (int)strPath.find(drop) < 0)
		{
			return false;
		}
		string strDest = strPath;
		strDest.erase(0,strDest.find_last_of(drop));
		*static_cast<string*>(input) = *static_cast<string*>(&strDest);
		return true;
	}
	bool parseFileBaseName(void* input, const char* strPath)
	{
		assert(input);
		std::string fileName;
		std::string str = strPath;
		if ((int)str.find("\\") > 0)
		{
			replace(&str, "\\", "/");
		}
		parseFileName(&fileName, str.c_str());
		if(fileName.empty())
		{
			return false;
		}
		string strDest = fileName;
		if(strDest.empty())
		{
			return false;
		}
		string drop = ".";
		int ndx = strDest.find_last_of(drop);
		if (ndx != -1)
		{
			strDest.erase(ndx);
		}
		*static_cast<string*>(input) = *static_cast<string*>(&strDest);
		return true;
	}
	bool toBoolean( const std::string& str )
	{
		return str.empty()?false:true;
	}
	bool toString(void* input, bool val)
	{
		assert(input);
		*static_cast<string*>(input) = (val ? "1" : "0");
		return true;
	}

	bool yesOrNo(void* input, bool val)
	{
		assert(input);
		*static_cast<string*>(input) = (val ? "yes" : "no");
		return true;
	}

	bool fileCreate(const char* szstrFilePath, bool bReplace)
	{
		string filePath = szstrFilePath;
		if ((int)filePath.find("\\") > 0)
		{
			replace(&filePath, "\\", "/");
		}
		if(filePath.empty())
		{
			return false;
		}
		locale loc = std::locale::global(std::locale(""));
		std::string strFilePath;
		normalizePath(&strFilePath,filePath.c_str());
		int nOk = 0;
	#ifdef WIN32
			nOk = 0;
	#elif defined __linux__
			nOk = F_OK;
	#elif defined VXWORKS
	#endif // WIN32
		if(strFilePath.find(".") < 0 || (int)strFilePath.find("/") < 0)
		{
			return false;
		}
		std::string dirPath =strFilePath;
		trimRight(&dirPath,"/");
        int i;
		char str[256] = {0};
		strcpy(str,dirPath.c_str());//缓存文件路径
        int len = strlen(str);
		for(i = 0; i<len; i++)
		{
			if( str[i] == '/')
			{
				str[i] = '\0';
				if(_access(str,nOk) != 0)
				{
					if(_mkdir(str) < 0)
					{
						return false;
					}
				}
				str[i] ='/';
			}
		}
		if( len > 0 && _access(str ,nOk)!=0) //检测是否创建成功
		{
			if(_mkdir(str) < 0)
			{
				return false;
			}
		}
		// 判断文件是否存在
		if(fileExist(strFilePath.c_str()) && bReplace)
		{
			fileRemove(strFilePath.c_str());
		}
		//1.fopen的函数原型：FILE * fopen(const char * path,const char * mode);
		//fopen函数的第一个参数是文件路径，第二个参数是打开方式，有以下几种方式：
		//	r 以只读方式打开文件，该文件必须存在。
		//	r+ 以可读写方式打开文件，该文件必须存在。
		//	rb+ 读写打开一个二进制文件，允许读数据。
		//	rw+ 读写打开一个文本文件，允许读和写。
		//	w 打开只写文件，若文件存在则文件长度清为0，即该文件内容会消失。若文件不存在则建立该文件。
		//	w+ 打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
		//	a 以附加的方式打开只写文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留。（EOF符保留）
		//	a+ 以附加方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留。 （原来的EOF符不保留）
		//	wb 只写打开或新建一个二进制文件；只允许写数据。
		//	wb+ 读写打开或建立一个二进制文件，允许读和写。
		//	wt+ 读写打开或着建立一个文本文件；允许读写。
		//	at+ 读写打开一个文本文件，允许读或在文本末追加数据。
		//	ab+ 读写打开一个二进制文件，允许读或在文件末追加数据。上述的形态字符串都可以再加一个b字符，如rb、w+b或ab+等组合，加入b 字符用来告诉函数库打开的文件为二进制文件，而非纯文字文件。
		//	返回值：文件顺利打开后，指向该流的文件指针就会被返回。如果文件打开失败则返回NULL，并把错误代码存在errno中。
		FILE*fp_filename = fopen(strFilePath.c_str(), "a+");
		if(fp_filename == NULL)
		{
			return false;
		}
		fclose(fp_filename);
		fp_filename = NULL;
		locale::global(loc);
 		return true;
	}

	bool fileExist(const char* szstrFilePath)
	{
		string strFilePath = szstrFilePath;
		if ((int)strFilePath.find("\\") > 0)
		{
			replace(&strFilePath, "\\", "/");
		}

		if(strFilePath.empty())
		{
			return false;
		}
		locale loc = std::locale::global(std::locale(""));
		std::string strDest = strFilePath;
		// 0 存在
		// 2 可写
		// 4 可读
		// 6 可读可写
		int nOk = 0;
#ifdef WIN32
	nOk = 0;
#elif defined __linux__
	nOk = F_OK;
#elif defined VXWORKS
#endif // WIN32

		bool bSucc = (_access( strDest.c_str(),nOk) != -1 );
		locale::global(loc);
		return bSucc;
	}

	unsigned int fileSize(const char* szstrFilePath)
	{
		string filePath = szstrFilePath;
		if(filePath.empty())
		{
			return -1;
		}
		std::string strFilePath;
		normalizePath(&strFilePath,filePath.c_str());

		if((int)strFilePath.find(".") < 0 || (int)strFilePath.find("/") < 0)
		{
			return -1;
		}
		locale loc = std::locale::global(std::locale(""));
		FILE* pFile = NULL;
		errno_t err = 0;
		err = fopen_s(&pFile,strFilePath.c_str(),"r");
		fseek(pFile, 0, SEEK_END);  //先用fseek将文件指针移到文件末尾  
		unsigned int size = ftell(pFile);    //再用ftell获取文件内指针当前的文件位置。
		fclose(pFile);
		locale::global(loc);
		return size;
	}
	bool fileRemove(const char* szstrFilePath)
	{
		string filePath = szstrFilePath;
		if(filePath.empty())
		{
			return false;
		}
		std::string strFilePath;
		normalizePath(&strFilePath,filePath.c_str());
		if((int)strFilePath.find(".") < 0 || (int)strFilePath.find("/") < 0)
		{
			return false;
		}
		return remove(strFilePath.c_str()) < 0?false:true;
	}
	bool fileRename(const char* szstrFilePath, const char* szstrNewPath)
	{
		string strFile = szstrFilePath;
		string newPath = szstrNewPath;
		if(strFile.empty() || newPath.empty())
		{
			return false;
		}
		std::string strFilePath;
		normalizePath(&strFilePath,strFile.c_str());
		std::string strNewPath;
		normalizePath(&strNewPath,newPath.c_str());

		if((int)strFilePath.find(".") < 0 || (int)strFilePath.find("/") < 0 || (int)strNewPath.find(".") < 0 || (int)strNewPath.find("/") < 0)
		{
			return false;
		}
		return rename(strFilePath.c_str(),strNewPath.c_str())< 0?false:true;
	}

	bool fileCopy(const char* szstrSrcPath, const char* szstrDstPath, bool bCover)
	{
		string srcPath = szstrSrcPath;
		string dstPath = szstrDstPath;
		if(srcPath.empty() || dstPath.empty())
		{
			return false;
		}
		std::string strSrcPath;
		normalizePath(&strSrcPath,srcPath.c_str());
		std::string strDstPath;
		normalizePath(&strDstPath,dstPath.c_str());

		if((int)strSrcPath.find(".") < 0 || (int)strSrcPath.find("/") < 0 || (int)strDstPath.find(".") < 0 || (int)strDstPath.find("/") < 0)
		{
			return false;
		}
		locale loc = std::locale::global(std::locale(""));
		if(bCover)
		{
			if(fileExist(strDstPath.c_str()))
			{
				fileRemove(strDstPath.c_str());
			}
		}
		else
		{
			if(fileExist(strDstPath.c_str()))
			{
				return false;
			}
		}
		char buff[1024];
		FILE*fp_filename = fopen(strSrcPath.c_str(), "r");
		FILE*fp_fileout = fopen(strDstPath.c_str(), "w+");
		if (!fp_filename)
		{
			return false;
		}
		if (!fp_fileout)
		{
			return false;
		}
		while (!feof(fp_filename))
		{
            int len = fread(buff, sizeof(char), sizeof(buff), fp_filename);
			fwrite(buff, sizeof(char), len, fp_fileout);
		}
		fclose(fp_filename);
		fclose(fp_fileout);

		locale::global(loc);
		return true;
	}

	bool currentDir(void* input)
	{
		assert(input);
		locale loc = std::locale::global(std::locale(""));
		string strDest; 
#ifdef WIN32
		TCHAR Buffer[MAX_PATH];
		memset(Buffer,0,MAX_PATH);
		if(GetCurrentDirectory(MAX_PATH,Buffer)!=0) 
		{ 
			strDest = (char*)Buffer;
		}
#elif defined __linux__
		string strDest; 
		char buf[256] = {0};
		getcwd((char*)buf,sizeof(char)*256);
		strDest = buf;

#elif defined VXWORKS
#endif // WIN32
		locale::global(loc);
		if ((int)strDest.find("\\") > 0)
		{
			replace(&strDest, "\\", "/");
		}
		if(isEndWith(strDest.c_str(),"/"))
		{
			trimRight(&strDest,"/");
		}
		*static_cast<string*>(input) = *static_cast<string*>(&strDest);
		return true;
	}
	bool changeDir(const char* szstrPath)
	{
		string path = szstrPath;
		if(path.empty())
		{
			return false;
		}
		std::string strPath;
		normalizePath(&strPath,path.c_str());

		if((int)strPath.find(".") < 0 || (int)strPath.find("/") < 0)
		{
			return false;
		}
		int bRet = 0;
		locale loc = std::locale::global(std::locale(""));
#ifdef WIN32
		bRet = SetCurrentDirectory((LPTSTR)strPath.c_str())?1:0;
#elif defined __linux__
		bRet = chdir(strPath.c_str());
#elif defined VXWORKS
#endif // WIN32
		locale::global(loc);

		return (bRet < 0)?false:true;
	}
	bool moduleDir(void* input)
	{
		assert(input);
		locale loc = std::locale::global(std::locale(""));
		string strDest;
#ifdef WIN32
		TCHAR exeFullPath[MAX_PATH]; // MAX_PATH在WINDEF.h中定义了，等于260
		memset(exeFullPath,0,MAX_PATH);

		GetModuleFileName(NULL,exeFullPath,MAX_PATH);

		 //strDest = (char*)exeFullPath;

#elif defined __linux__
        sint ret;
		char *buf[256] = {0};
		ret =  readlink(“/proc/self/exe”,(char*)buf, sizeof(char)*256);
		strDest=buf;
#elif defined VXWORKS
#endif // WIN32
		locale::global(loc);

		normalizePath(&strDest, (char*)exeFullPath);

		trimRight(&strDest,"/");
		*static_cast<string*>(input) = *static_cast<string*>(&strDest);
		return true;
	}

	bool dirCreate(const char* szstrDirPath)
	{
		string dirPath = szstrDirPath;
		if(dirPath.empty())
		{
			return false;
		}
		std::string strDirPath;
		normalizePath(&strDirPath,dirPath.c_str());

		if((int)strDirPath.find("/") < 0)
		{
			return false;
		}
		locale loc = std::locale::global(std::locale(""));
		int nOk = 0;
#ifdef WIN32
		nOk = 0;
#elif defined __linux__
		nOk = F_OK;
#elif defined VXWORKS
#endif // WIN32
		std::string strDest = strDirPath;

		if(isEndWith(strDest.c_str(),"/"))
		{
			trimRight(&strDest,"/");
		}
		std::vector<std::string> listDir;
		split(strDest.c_str(), "/", &listDir);

		std::string strDir;
		for (int i = 0; i < listDir.size(); ++i)
		{
			strDir.append(listDir[i]);
			strDir.append("/");
			if (!dirExist(strDir.c_str()))
			{
				_mkdir(strDir.c_str());
			}
		}
		locale::global(loc);
		return true;

	}

	bool dirRemove(const char* szstrDirPath)
	{
		std::string strDirPath;
		normalizePath(&strDirPath, szstrDirPath);

		if((int)strDirPath.find(".") < 0 || (int)strDirPath.find("/") < 0)
		{
			return false;
		}
		locale loc = std::locale::global(std::locale(""));
		if(_rmdir(strDirPath.c_str()) < 0)
		{
			return false;
		}
		locale::global(loc);
		return true;
	}

	bool dirExist(const char* szstrDirPath)
	{
		std::string strDirPath;
		normalizePath(&strDirPath, szstrDirPath);

		if((int)strDirPath.find(".") < 0 || (int)strDirPath.find("/") < 0)
		{
			return false;
		}
		locale loc = std::locale::global(std::locale(""));
		int nOk = 0;
#ifdef WIN32
		nOk = 0;
#elif defined __linux__
		nOk = F_OK;
#elif defined VXWORKS
#endif // WIN32
		bool bSucc = (_access(strDirPath.c_str(),nOk) == 0)?true:false;
		locale::global(loc);
		return bSucc;
	}
	bool normalizePath(void* input, const char* szstrDir)
	{
		assert(input);
		std::string strDir = szstrDir;
		if ((int)strDir.find("\\") > 0)
		{
			replace(&strDir, "\\", "/");
		}
		if(strDir.empty())
		{
			return false;
		}
		if((int)strDir.find("/") < 0)
		{
			return "";
		}

		std::vector<std::string> Dirs;
		split(strDir.c_str(), "/", &Dirs);

		std::stringstream ss;
        for(int i = 0; i < Dirs.size();++i)
		{
			if(Dirs[i].empty())
			{
				continue;
			}
			ss<<Dirs[i]<<"/";
		}
		std::string strDest = ss.str();

		trimRight(&strDest,"/");
		
		*static_cast<string*>(input) = *static_cast<string*>(&strDest);

		return true;
	}

	bool OpenFolder(const char* szstrFolder)
	{
		std::string folder = szstrFolder;

		if(folder.empty())
		{
			return false;
		}
		std::string strFolder;
		normalizePath(&strFolder,folder.c_str());

		if((int)strFolder.find("/") < 0)
		{
			return false;
		}
		locale loc = std::locale::global(std::locale(""));
#ifdef WIN32
		stringstream ss;
		ss << "/select, "<<strFolder.c_str();
		wchar_t* pUnicode = NULL;
		pUnicode = (wchar_t*)strFolder.c_str();
		ShellExecute(NULL, TEXT("open"), TEXT("Explorer.exe"), (LPCTSTR)pUnicode, NULL, SW_SHOWNORMAL);
		return true;
#elif defined __linux__
		return false;
#elif defined VXWORKS
		return false;
#endif // WIN32
		locale::global(loc);
	}
	void sleepMS( int nMilSecond )
	{
		#ifdef WIN32
				Sleep(nMilSecond);
		#elif defined __linux__
				usleep(nMilSecond * 1000);
		#elif defined VXWORKS
		#endif // WIN32
	}

}

