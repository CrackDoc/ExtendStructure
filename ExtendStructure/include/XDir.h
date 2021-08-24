#ifndef XDir_h__
#define XDir_h__
#include "XFile.h"
#include "ExtendStructureExport.h"

namespace IOx
{
    class XFile;
    class ExtendStructure_EXPORT XDir
    {
	public:
        class  ExtendStructure_EXPORT IDirVisitor
		{
		        public:
                        virtual ~IDirVisitor() {}
  
                        //文件访问
                        virtual bool applyDir(XFile rFile) = 0;

                        //目录访问
                        virtual bool applyDir(XDir rDir) = 0;

                        virtual void setFilter(const char * rToken) = 0;

                        virtual const char* filter() = 0;

                        virtual void setAbsolutePath(const char *filePath) = 0;

                        virtual char *GetAbsolutePath() = 0;
		};
    public:
        XDir(const char *szDir = "./");
        ~XDir();

        bool exist() const;

        const char * absolutePath() const;

        const char * relativePath() const;

		const char * dirName() const;

        void setDirPath(const char * strDirPath);

        static bool isAbsolutePath(const char * strPath);

		bool isAbsolutePath();

        //获取目录下所有文件 参数:std::vector<IOx::XDir>&
        bool getAllFiles(void * rLstFile, const char* strFilter = "*.*") ;

        //获取目录下所有目录  参数:std::vector<IOx::XDir>&
        bool getAllDir(void * rLstDir);
		// 参数: std::vector<IOx::XDir>&
		bool getOneLevelAllDir(void* rLstDir);

        //遍历文件目录,(默认递归)
        bool travel(IDirVisitor& rVisitor);

        //创建文件
        bool createFile(const char * strFileName);

        //移除文件
        bool removeFile(const char * strFileName);

        //移除目录
        bool removeSubDir(const char * strDirName);

        bool valid() const;

        bool create();

        bool remove();

		bool cleanup();

		// 返回上一级目录 [3/19/2016 Administrator]
		XDir prevDir();

		// +目录 [3/19/2016 Administrator]
		XDir append(const char * strAppendPath);

		// 参数：std::vector<std::string>&
		bool SplitDir(void *input) const;
		// 参数：std::vector<std::string>&
		static bool SplitDir(void* input,const char *strPath);

		void Normalize();

		// 参数：std::string &
		static void Normalize(void *input,const char * strDir);

		XDir createSubDir(const char * strSubDir);

		// 参数：std::string &
		static void GetPWD(void *input);

	private:
        char mAbsolutePath[256];
        char mRelativePath[256];
    };
}

#endif // XDir_h__

