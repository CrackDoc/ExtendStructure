#ifndef CMAKE_PROJECTExport_h__
#define CMAKE_PROJECTExport_h__

#if defined(WIN32)
#ifdef CMAKE_PROJECT_EXPORTS
#define CMAKE_PROJECT_EXPORT __declspec(dllexport)
#else
#define  CMAKE_PROJECT_EXPORT __declspec(dllimport)
#endif

#pragma warning( disable: 4251 )

#elif __linux__
#define CMAKE_PROJECT_EXPORT

#else
#define CMAKE_PROJECT_EXPORT 
#endif
#endif // ExtendStructureExport_h__
