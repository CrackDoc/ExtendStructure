#ifndef StlUtil_h__
#define StlUtil_h__

#include "ExtendStructureExport.h"

namespace stlu
{
	// 大写 [4/8/2015 Administrator]
	extern ExtendStructure_EXPORT bool upper(void *strSrc);

	// 小写 [4/8/2015 Administrator]

	extern ExtendStructure_EXPORT bool lower(void* strSrc);

	// 去除空白 [4/8/2015 Administrator]
	extern ExtendStructure_EXPORT bool trimC(void* strSrc);

	extern ExtendStructure_EXPORT void trim(void* strSrc);

	extern ExtendStructure_EXPORT void trimLeft(void* strSrc, const char * strToken = "\n");

	extern ExtendStructure_EXPORT void trimRight(void* strSrc, const char* strToken = " ");

	// 替换 [4/8/2015 Administrator]
	extern ExtendStructure_EXPORT void replace(void* strSrc, const char* origial,const char* strToken);

	// 是否存在 [4/20/2019 kyske]
    extern ExtendStructure_EXPORT int firstToken(const char * strSrc, const char* strToken);

	// 开头是否为 [4/8/2015 Administrator]
	extern ExtendStructure_EXPORT bool isStartWith(const char* strSrc, const char* strToken);

	// 是否结束为 [4/8/2015 Administrator]
	extern ExtendStructure_EXPORT bool isEndWith(const char* strSrc, const char* strToken);

	// 拆分字符串 [4/8/2015 Administrator]
	extern ExtendStructure_EXPORT void split(const char* strSrc, const char* strToken, void* input);

	// 反转 [4/8/2015 Administrator]
	extern ExtendStructure_EXPORT void reverse(void* strSrc);

	// 扩展名 [4/8/2015 Administrator]
	extern ExtendStructure_EXPORT bool extendName(void *input,const char * strSrc, const char* strToken = ".");

	// 完整目录 [4/8/2015 Administrator]
	extern ExtendStructure_EXPORT bool complateDir(void* input,const char* path, const char * token = "/");

	// 去掉结尾 [4/8/2015 Administrator]
	extern ExtendStructure_EXPORT void eraserSuffix(void *str);

	// 去掉某个标志以后的字符串 [3/19/2016 Administrator]
	extern ExtendStructure_EXPORT void eraserLastOf(void* str, const char* token);

	// 字符串结尾 [4/8/2015 Administrator]
	extern ExtendStructure_EXPORT void endOfString(void* str, const char* token = "/");

	// 解析文件名 [4/8/2015 Administrator]
	extern ExtendStructure_EXPORT bool parseFileName(void* input,const char* path);

	extern ExtendStructure_EXPORT bool  parseFileSuffix(void* input, const char* strPath);

	extern ExtendStructure_EXPORT bool parseFileBaseName(void* input, const char *strPath);
};

// 模板实现常用的函数 [4/8/2015 Administrator]
namespace stlu
{
	extern ExtendStructure_EXPORT bool toBoolean(const char *val);

	extern ExtendStructure_EXPORT bool toString(void *input,bool val);

	extern ExtendStructure_EXPORT bool yesOrNo(void* input,bool bVal);
}

//文件相关的简单函数
namespace stlu
{
	//文件创建
	extern ExtendStructure_EXPORT bool fileCreate(const char * strFilePath,bool bReplace = true);

	//文件存在
	extern ExtendStructure_EXPORT bool fileExist(const char * strFilePath);

	//文件大小
	extern ExtendStructure_EXPORT unsigned int fileSize(const char * strFilePath);

	//文件删除
	extern ExtendStructure_EXPORT bool fileRemove(const char * strFilePath);

	//重命名
	extern ExtendStructure_EXPORT bool fileRename(const char * strFilePath, const char* strNewPath);

	extern ExtendStructure_EXPORT bool fileCopy(const char * strSrcPath, const char * strDstPath, bool bCover = true);

	//返回当前工作路径
	extern ExtendStructure_EXPORT bool currentDir(void *input);

	//设置当前工作路径
	extern ExtendStructure_EXPORT bool changeDir(const char * strPath);

	//可执行程序路径
	extern ExtendStructure_EXPORT bool  moduleDir(void* input);

	//创建目录
	extern ExtendStructure_EXPORT bool dirCreate(const char *strDirPath);

	//移除目录,只能移除空目录
	extern ExtendStructure_EXPORT bool dirRemove(const char* strDirPath);

	extern ExtendStructure_EXPORT bool dirExist(const char* strDirPath);

	extern ExtendStructure_EXPORT bool normalizePath(void* input,const char * strDir);

	//打开目录
	extern ExtendStructure_EXPORT bool OpenFolder(const char* strFolder);
}

//系统相关
namespace stlu
{
	//睡眠(毫秒)
	extern ExtendStructure_EXPORT void sleepMS(int nMilSecond);
}

#endif // StlUtil_h__
