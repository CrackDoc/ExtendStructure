#ifndef ExtendStructureExport_h__
#define ExtendStructureExport_h__

#if defined(WIN32)
#ifdef ExtendStructure_EXPORTS
#define ExtendStructure_EXPORT __declspec(dllexport)
#else
#define  ExtendStructure_EXPORT __declspec(dllimport)
#endif

#pragma warning( disable: 4251 )

#elif __linux__
#define ExtendStructure_EXPORT

#else
#define ExtendStructure_EXPORT 
#endif
#endif // ExtendStructureExport_h__
