#pragma once
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
		class  ExtendStructure_EXPORT DirVisitor
		{
		public:
			DirVisitor(const char* filePath = "./");
			virtual ~DirVisitor();

			//�ļ�����
			virtual bool apply(XFile& rFile);

			//Ŀ¼����
			virtual bool apply(XDir& rDir);

			virtual void SetAbsolutePath(const char * strPath);

			virtual const char* GetAbsolutePath();

			void setFilter(const char * rToken);

			const char* filter();


		protected:
			char mFilterToken[256];
			char mAbsolutePath[256];
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

        //��ȡĿ¼�������ļ� ����:std::vector<IOx::XDir>&
        bool getAllFiles(void * rLstFile, const char* strFilter = "*.*") ;

        //��ȡĿ¼������Ŀ¼  ����:std::vector<IOx::XDir>&
        bool getAllDir(void * rLstDir);
		// ����: std::vector<IOx::XDir>&
		bool getOneLevelAllDir(void* rLstDir);

        //�����ļ�Ŀ¼,(Ĭ�ϵݹ�)
        bool travel(DirVisitor& rVisitor);

        //�����ļ�
        bool createFile(const char * strFileName);

        //�Ƴ��ļ�
        bool removeFile(const char * strFileName);

        //�Ƴ�Ŀ¼
        bool removeSubDir(const char * strDirName);

        bool valid() const;

        bool create();

        bool remove();

		bool cleanup();

		// ������һ��Ŀ¼ [3/19/2016 Administrator]
		XDir prevDir();

		// +Ŀ¼ [3/19/2016 Administrator]
		XDir append(const char * strAppendPath);

		// ������std::vector<std::string>&
		bool SplitDir(void *input) const;
		// ������std::vector<std::string>&
		static bool SplitDir(void* input,const char *strPath);

		void Normalize();

		// ������std::string &
		static void Normalize(void *input,const char * strDir);

		XDir createSubDir(const char * strSubDir);

		// ������std::string &
		static void GetPWD(void *input);

	private:
        char mAbsolutePath[256];
		char mRelativePath[256];
    };
}

#endif // XDir_h__

