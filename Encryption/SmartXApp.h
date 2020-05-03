#ifndef SMARTXAPP_H_INCLUDED
#define SMARTXAPP_H_INCLUDED

#ifdef WIN32 

	#ifdef _DEBUG
		#ifndef _CONSOLE
			#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")
		#endif
	#endif

#endif

#define 	DT_CHAR					 1
#define 	DT_UCHAR				 2
#define 	DT_SHORT				 3
#define 	DT_USHORT				 4
#define 	DT_INT					 5
#define 	DT_UINT					 6
#define 	DT_LONG					 7
#define 	DT_ULONG				 8
#define 	DT_FLOAT				 9
#define 	DT_DOUBLE				 10
#define 	DT_LONGLONG				 11
#define 	DT_ULONGLONG			 12


#ifdef __cplusplus
extern "C"
{
#endif
	//Get last error
	long SmartXGetLastError();

	//Find all connected keys in and get their handles
	long SmartXFind(char appID[32], long * keyHandles, long * keyNumber);
	
	//Check the dongle still exists
	long SmartXCheckExist(long keyHandle);

	//Get the hardware id of the dongle
	long SmartXGetUid(long keyHandle, char UID[32]);
 
	//user code execution
	long SmartXSetVar(long keyHandle, long varIndex, long dataType, void * pVar, long length);
	
	long SmartXExecute(long keyHandle, long fileId, long * returnValue);

	long SmartXClearVar(long keyHandle);
	
	long SmartXClose(long keyHandle);
	
	long SmartXExit();

	long SmartXGetSoftVersion(long keyHandle, char softVersion[32]);

#ifdef __cplusplus
}
#endif



#endif // SmartXAPP_H_INCLUDED
