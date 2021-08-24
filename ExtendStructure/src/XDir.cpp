#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <locale.h>

#ifdef WIN32
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <codecvt>
#elif defined __linux__
#include <unistd.h>
#include <sys/stat.h> ��
#include <sys/types.h>
#elif defined VXWORKS
#endif
#include "XDir.h"
#include "StlUtil.h"
#include "XFile.h"
#include "dirent.h"
#include <locale.h>  
#include <locale>  
#include <sstream>
#include <vector>
#include <string.h>
#include <assert.h>
#include "dirent.h"
using std::locale;  

namespace IOx
{
	XDir::XDir(const char* szDir)
	{
		memset(mAbsolutePath, '\0', sizeof(char) * 256);
		memset(mRelativePath, '\0', sizeof(char) * 256);

		std::string strDir = szDir;

		if(!strDir.empty())
		{
			std::string dir;
			stlu::normalizePath(&dir,strDir.c_str());

			// �ж��Ƿ������·��
			bool isRelativePath = false;
			if(stlu::isStartWith(dir.c_str(),"./"))
			{
				isRelativePath = true;
				strcat(mRelativePath, dir.c_str());

				stlu::trimLeft(&dir,"./");

				std::stringstream ss;
				std::string pwdString;
				GetPWD(&pwdString);
				ss<< pwdString <<"/"<<dir;
				strcat(mAbsolutePath, ss.str().c_str());

			}
			else if(stlu::isStartWith(dir.c_str(),"../"))
			{
				isRelativePath = true;
				strcat(mRelativePath, dir.c_str());

				std::vector<std::string> splits;
				stlu::split(dir.c_str(), "../",&splits);

				size_t size = splits.size();
				std::string currentDir;
				GetPWD(&currentDir);
				for(size_t i = 0; i < size; ++i)
				{
					stlu::trimRight(&currentDir,"/");
				}
				std::stringstream ss;
				ss<<currentDir;
				for(size_t i = 0; i < size; ++i)
				{
					ss<<"/"<<splits[i];
				}
				strcat(mAbsolutePath, ss.str().c_str());
			}
			else
			{
				strcat(mRelativePath, "./");
				if(dir.empty())
				{
					std::string strpwd;
					GetPWD(&strpwd);
					strcat(mAbsolutePath, strpwd.c_str());
				}
				else
				{
					strcat(mAbsolutePath, dir.c_str());
				
				}
			}
		}
	}


	XDir::~XDir()
	{

	}

	bool XDir::exist() const
	{
		return stlu::dirExist(mAbsolutePath);
	}

	const char* XDir::absolutePath() const
	{
		return mAbsolutePath;
	}

	const char* XDir::relativePath() const
	{
		return mRelativePath;
	}

	 const char *XDir::dirName() const
	{
		return mAbsolutePath;
	}

	void XDir::setDirPath( const char *szstrDirPath )
	{
		memset(mAbsolutePath, '\0', sizeof(char) * 256);
		memset(mRelativePath, '\0', sizeof(char) * 256);

		std::string strDir = szstrDirPath;

		if (!strDir.empty())
		{
			std::string dir;
			stlu::normalizePath(&dir, strDir.c_str());

			// �ж��Ƿ������·��
			bool isRelativePath = false;
			if (stlu::isStartWith(dir.c_str(), "./"))
			{
				isRelativePath = true;
				strcat(mRelativePath, dir.c_str());

				stlu::trimLeft(&dir, "./");

				std::stringstream ss;
				std::string pwdString;
				GetPWD(&pwdString);
				ss << pwdString << "/" << dir;
				strcat(mAbsolutePath, ss.str().c_str());

			}
			else if (stlu::isStartWith(dir.c_str(), "../"))
			{
				isRelativePath = true;
				strcat(mRelativePath, dir.c_str());

				std::vector<std::string> splits;
				stlu::split(dir.c_str(), "../", &splits);

				size_t size = splits.size();
				std::string currentDir;
				GetPWD(&currentDir);
				for (size_t i = 0; i < size; ++i)
				{
					stlu::trimRight(&currentDir, "/");
				}
				std::stringstream ss;
				ss << currentDir;
				for (size_t i = 0; i < size; ++i)
				{
					ss << "/" << splits[i];
				}
				strcat(mAbsolutePath, ss.str().c_str());
			}
			else
			{
				strcat(mRelativePath, "./");
				if (dir.empty())
				{
					std::string strpwd;
					GetPWD(&strpwd);
					strcat(mAbsolutePath, strpwd.c_str());
				}
				else
				{
					strcat(mAbsolutePath, dir.c_str());

				}
			}
		}
	}

	bool XDir::isAbsolutePath( const char* szstrPath )
	{
		std::string strPath = szstrPath;

		if(strPath.empty())
		{
			return false;
		}
		bool isAbsolute = true;
		if(stlu::isStartWith(strPath.c_str(),"./") || stlu::isStartWith(strPath.c_str(),"../"))
		{
			isAbsolute = false;
		}
		return isAbsolute;
	}

	bool XDir::isAbsolutePath()
	{
		return isAbsolutePath(mAbsolutePath);
	}

	void find_directoryFiles(std::vector<IOx::XFile>& rLstDirs, const std::string& strDirName, const std::string& strFilter /*= "*.*"*/)
	{
		if(strDirName.empty())
		{
			return;
		}
		locale loc = std::locale::global(std::locale(""));

		DIR *dir;
		char buffer[PATH_MAX + 2];
		char *p = buffer;
		const char *src;
		char *end = &buffer[PATH_MAX];
		int ok;

		const char *dirname = strDirName.c_str();
		/* Copy directory name to buffer */
		src = dirname;

		while (p < end  &&  *src != '\0') {
			*p++ = *src++;
		}
		*p = '\0';

		/* Open directory stream */
		dir = opendir (dirname);
		if (dir != NULL) {
			struct dirent *ent;

			/* Print all files and directories within the directory */
			while ((ent = readdir (dir)) != NULL) {

				char *q = p;
				char c;

				/* Get final character of directory name */
				if (buffer < q) {
					c = q[-1];
				} else {
					c = ':';
				}

				/* Append directory separator if not already there */
				if (c != ':'  &&  c != '/'  &&  c != '/') {
					*q++ = '/';
				}

				/* Append file name */
				src = ent->d_name;
				while (q < end  &&  *src != '\0') {
					*q++ = *src++;
				}
				*q = '\0';

				/* Decide what to do with the directory entry */
				switch (ent->d_type) {
				case DT_LNK:
				case DT_REG:
					/* Output file name with directory */
					{
						std::vector<std::string> splits;
						stlu::split(strFilter.c_str(), ".",&splits);
						if(splits.size() != 2)
						{
							rLstDirs.push_back(XFile(buffer));
						}
						else
						{
							if(strcmp (splits[0].c_str(), "*") == 0 || strcmp (splits[1].c_str(), "*") == 0)
							{
								rLstDirs.push_back(XFile(buffer));
							}
							else if(strcmp (splits[0].c_str(), "*") != 0 || strcmp (splits[1].c_str(), "*") == 0)
							{
								if(stlu::isStartWith(buffer,splits[0].c_str()))
								{
									rLstDirs.push_back(XFile(buffer));
								}
							}
							else if(strcmp (splits[0].c_str(), "*") == 0 || strcmp (splits[1].c_str(), "*") != 0)
							{
								if(stlu::isEndWith(buffer,splits[1].c_str()))
								{
									rLstDirs.push_back(XFile(buffer));
								}
								
							}
							else
							{
								if(stlu::isStartWith(buffer,splits[0].c_str()) && stlu::isEndWith(buffer,splits[1].c_str()))
								{
									rLstDirs.push_back(XFile(buffer));
								}
							}
						}
					}
					break;
				case DT_DIR:
					{
						/* Scan sub-directory recursively */
						if (strcmp (ent->d_name, ".") != 0
							&&  strcmp (ent->d_name, "..") != 0) 
						{
							std::string strNestDir = buffer;

							find_directoryFiles (rLstDirs,strNestDir,strFilter);
						}
					}
					break;

				default:
					/* Ignore device entries */
					/*NOP*/;
				}

			}

			closedir (dir);
			ok = 1;

		} else {
			/* Could not open directory */
			fprintf (stderr, "Cannot open %s (%s)\n", dirname, strerror (errno));
			ok = 0;
		}
		locale::global(loc);
	}
	void find_directory( std::vector<IOx::XDir>& rLstDirs,const std::string& strDirName,bool bUnder = false)
	{
		if(strDirName.empty())
		{
			return;
		}
		locale loc = std::locale::global(std::locale(""));
		DIR *dir;
		char buffer[PATH_MAX + 2];
		char *p = buffer;
		const char *src;
		char *end = &buffer[PATH_MAX];
		int ok;

		const char *dirname =  strDirName.c_str();
		/* Copy directory name to buffer */
		src = dirname;

		while (p < end  &&  *src != '\0') {
			*p++ = *src++;
		}
		*p = '\0';

		/* Open directory stream */
		dir = opendir (dirname);
		if (dir != NULL) {
			struct dirent *ent;

			/* Print all files and directories within the directory */
			while ((ent = readdir (dir)) != NULL) {

				char *q = p;
				char c;

				/* Get final character of directory name */
				if (buffer < q) {
					c = q[-1];
				} else {
					c = ':';
				}

				/* Append directory separator if not already there */
				if (c != ':'  &&  c != '/'  &&  c != '/') {
					*q++ = '/';
				}

				/* Append file name */
				src = ent->d_name;
				while (q < end  &&  *src != '\0') {
					*q++ = *src++;
				}
				*q = '\0';

				/* Decide what to do with the directory entry */
				switch (ent->d_type) {
				case DT_LNK:
				case DT_REG:
					/* Output file name with directory */
					printf ("%s\n", buffer);
					break;

				case DT_DIR:
					{
						/* Scan sub-directory recursively */
						if (strcmp (ent->d_name, ".") != 0
							&&  strcmp (ent->d_name, "..") != 0) 
						{
							std::string strNestDir = buffer;

							rLstDirs.push_back(XDir(strNestDir.c_str()));
							if (!bUnder)
							{
								find_directory(rLstDirs, strNestDir);
							}
						}
					}

					break;

				default:
					/* Ignore device entries */
					/*NOP*/;
				}

			}

			closedir (dir);
			ok = 1;

		} else {
			/* Could not open directory */
			fprintf (stderr, "Cannot open %s (%s)\n", dirname, strerror (errno));
			ok = 0;
		}
		locale::global(loc);
	}

	bool XDir::getAllFiles(void* rLstFile, const char* strFilter)
	{
		assert(rLstFile);
		std::vector<IOx::XFile> * rFiles0 = static_cast<std::vector<IOx::XFile>*>(rLstFile);
		assert(rFiles0);
		std::vector<IOx::XFile>& rFiles = *rFiles0;

		find_directoryFiles(rFiles,mAbsolutePath,strFilter);
	
		return rFiles.empty()?false:true;
	}

	bool XDir::getAllDir(void* rLstDir)
	{
		std::vector<IOx::XDir>& rDirs = *static_cast<std::vector<IOx::XDir>*>(rLstDir);

		find_directory(rDirs,mAbsolutePath);

		return rDirs.empty()?false:true;
	}

	bool XDir::getOneLevelAllDir(void* rLstDir)
	{
		std::vector<IOx::XDir>& rDirs = *static_cast<std::vector<IOx::XDir>*>(rLstDir);

		find_directory(rDirs, mAbsolutePath,true);

		return rDirs.empty() ? false : true;

	}

    bool XDir::travel(IDirVisitor& rVisitor)
	{
		locale loc = std::locale::global(std::locale(""));
		DIR *dir;
		char buffer[PATH_MAX + 2];
		char *p = buffer;
		const char *src;
		char *end = &buffer[PATH_MAX];
		int ok;

        const char *dirname =  rVisitor.GetAbsolutePath();
		/* Copy directory name to buffer */
		src = dirname;

		while (p < end  &&  *src != '\0') {
			*p++ = *src++;
		}
		*p = '\0';

		/* Open directory stream */
		dir = opendir (dirname);
		if (dir != NULL) {
			struct dirent *ent;

			/* Print all files and directories within the directory */
			while ((ent = readdir (dir)) != NULL) {

				char *q = p;
				char c;

				/* Get final character of directory name */
				if (buffer < q) {
					c = q[-1];
				} else {
					c = ':';
				}

				/* Append directory separator if not already there */
				if (c != ':'  &&  c != '/'  &&  c != '/') {
					*q++ = '/';
				}

				/* Append file name */
				src = ent->d_name;
				while (q < end  &&  *src != '\0') {
					*q++ = *src++;
				}
				*q = '\0';

				/* Decide what to do with the directory entry */
				switch (ent->d_type) {
				case DT_LNK:
				case DT_REG:
					/* Output file name with directory */
					{
						std::vector<std::string> splits;
						stlu::split(rVisitor.filter(), ".",&splits);
						if(splits.size() != 2)
						{
                            rVisitor.applyDir(XFile(buffer));
						}
						else
						{
							if(strcmp (splits[0].c_str(), "*") == 0 || strcmp (splits[1].c_str(), "*") == 0)
							{
                                rVisitor.applyDir(XFile(buffer));
							}
							else if(strcmp (splits[0].c_str(), "*") != 0 || strcmp (splits[1].c_str(), "*") == 0)
							{
								if(stlu::isStartWith(buffer,splits[0].c_str()))
								{
                                    rVisitor.applyDir(XFile(buffer));
								}
							}
							else if(strcmp (splits[0].c_str(), "*") == 0 || strcmp (splits[1].c_str(), "*") != 0)
							{
								if(stlu::isEndWith(buffer,splits[1].c_str()))
								{
                                    rVisitor.applyDir(XFile(buffer));
								}

							}
							else
							{
								if(stlu::isStartWith(buffer,splits[0].c_str()) && stlu::isEndWith(buffer,splits[1].c_str()))
								{
                                    rVisitor.applyDir(XFile(buffer));
								}
							}
						}
					}
					break;

				case DT_DIR:
					{
						/* Scan sub-directory recursively */
						if (strcmp (ent->d_name, ".") != 0
							&&  strcmp (ent->d_name, "..") != 0) 
						{
							std::string strNestDir = buffer;
                            rVisitor.applyDir(XDir(strNestDir.c_str()));
                            rVisitor.setAbsolutePath(strNestDir.c_str());
							travel(rVisitor);
						}
					}

					break;

				default:
					/* Ignore device entries */
					/*NOP*/;
				}

			}

			closedir (dir);
			ok = 1;

		} else {
			/* Could not open directory */
			fprintf (stderr, "Cannot open %s (%s)\n", dirname, strerror (errno));
			ok = 0;
		}
		locale::global(loc);
		return true;
	}

	bool XDir::createFile( const char *strFileName )
	{
		return stlu::fileCreate(strFileName);
	}

	bool XDir::removeFile( const char* strFileName )
	{
		return stlu::fileRemove(strFileName);
	}

	bool XDir::removeSubDir( const char * strDirName )
	{
		return stlu::dirRemove(strDirName);
	}

	bool XDir::valid() const
	{
		std::string filePath = mAbsolutePath;

		if(filePath.empty())
		{
			return false;
		}
		if(isAbsolutePath(mAbsolutePath))
		{
			// 1 �ж� �Ƿ����̷���ʼ��
			filePath = std::string(mAbsolutePath);
			if(filePath.find(":") < 0)
			{
				return false;
			}
		}
		else
		{
			filePath = mRelativePath;
			
		}
		if(filePath.empty())
		{
			return false;
		}
		std::vector<std::string> splits;
		SplitDir(&splits,filePath.c_str());
		// 2 �ж��ļ������Ƿ���/
		if(splits.empty())
		{
			return false;
		}
		for(size_t i = 0; i < splits.size();++i)
		{
			std::string file = splits[i];
			if(file.length() > 256)
			{
				return false;
			}
			// 3 �����ַ�
			if(filePath.find("/") > 0 || filePath.find("/") > 0 || filePath.find(":") > 0 || filePath.find("*") > 0 || filePath.find("?") > 0 
				|| filePath.find("\"") > 0|| filePath.find("<") > 0 || filePath.find(">") > 0)
			{
				return false;
			}
		}
		return true;
	}

	bool XDir::create()
	{
		return stlu::dirCreate(mAbsolutePath);
	}

	bool XDir::remove()
	{
		return stlu::dirRemove(mAbsolutePath);
	}

	bool XDir::cleanup()
	{
		memset(mAbsolutePath, '\0', sizeof(char) * 256);
		memset(mRelativePath, '\0', sizeof(char) * 256);
		return true;
	}

	XDir XDir::prevDir()
	{
		std::string strPath(mAbsolutePath);
		if(strPath.empty())
		{
			return *this;
		}
		stlu::trimRight(&strPath,"/");
		cleanup();
		memcpy(mAbsolutePath, strPath.c_str(), sizeof(char) * strPath.length());
		return *this;
	}

	XDir XDir::append( const char* strAppendPath )
	{
		if(std::string(strAppendPath).empty())
		{
			return *this;
		}
		strcat(mAbsolutePath, "/");
		strcat(mAbsolutePath, strAppendPath);
		return *this;
	}

	bool XDir::SplitDir(void* input) const
	{
		assert(input);
		return SplitDir(input, mAbsolutePath);
	}

	bool XDir::SplitDir(void* input,const char* strPath )
	{
		std::vector<std::string> splits;
		std::string path = strPath;
		if (path.empty())
		{
			return false;
		}
	    stlu::split(path.c_str(),"/", input);
		return true;
	}

	void XDir::Normalize()
	{
		std::string strDestDir;
		Normalize(&strDestDir, mAbsolutePath);
		memcpy(mAbsolutePath, strDestDir.c_str(), sizeof(char) * strDestDir.length());
	}

	void XDir::Normalize(void* input, const char* strDir)
	{
		assert(input);
		std::vector<std::string> vDirs;
		SplitDir(&vDirs,strDir);
		std::stringstream ss;
		for(size_t i = 0; i < vDirs.size();++i)
		{
			if(vDirs.empty())
			{
				continue;
			}
			ss<<vDirs[i]<<"/";
		}
		std::string strDestDir = ss.str();
		stlu::trimRight(&strDestDir, "/");
		*static_cast<std::string*>(input) = *static_cast<std::string*>(&strDestDir);
	}

	XDir XDir::createSubDir( const char* strSubDir )
	{
		return append(strSubDir);
	}

	void XDir::GetPWD(void* input)
	{
		assert(input);
		char szBuffer[256];
		memset(szBuffer,'\0',sizeof(char)*256);
		getcwd(szBuffer,256);

		*static_cast<std::string*>(input) = szBuffer;
	}

}


