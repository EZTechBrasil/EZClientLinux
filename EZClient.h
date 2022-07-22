//-----------------------------------------------------------------------------
//
//  Empresa     :  EzTech Tecnologia e Automa��o Ltda
//        				 http://www.eztech.ind.br/
//
//	Created     : 24/08/2012
//
//  Modified    : 27/11/2017
//
//  Name        : Diego Aquino
//
//  Descricao   : Classe para carga e acesso da biblioteca EZClient.dll
//
//  Observacoes : 
//
//-----------------------------------------------------------------------------
#ifndef __EZ_CLIENT_INTERFACE__
#define __EZ_CLIENT_INTERFACE__

//-----------------------------------------------------------------------------
//#if defined( _LINUX_ )
#if defined(__linux__)

//#define _WIDE_CHARS_ 

typedef time_t					DATE ;
typedef unsigned char			BYTE ;
typedef long long 				__int64 ;
typedef long long 				LONGLONG ;
typedef unsigned long long  	__uint64 ;
typedef unsigned long long  	ULONGLONG ;
// typedef wchar_t					WCHAR ;
// typedef char					CHAR ;
// typedef unsigned char			UCHAR ;

#ifdef _WIDE_CHARS_ 

#define STRNCPY 				wcsncpy
#define STRLEN					wcslen 
typedef wchar_t					LCHAR ;
typedef wchar_t					TCHAR;
typedef unsigned wchar_t		UCHAR ;

#else 

#define STRNCPY 				strncpy
#define STRLEN					strlen 
typedef unsigned char			UCHAR ;
typedef char					LCHAR ;
typedef char					TCHAR;

#endif 

typedef LCHAR*					PLCHAR ;
typedef PLCHAR					BSTR ;
typedef PLCHAR					PBSTR ;
typedef short					SHORT ;
typedef unsigned short 			WORD ;
typedef unsigned short			USHORT ;
typedef int						LONG ;
typedef unsigned int       		ULONG ;
typedef unsigned int       		LPARAM ;
typedef unsigned int			DWORD ;
typedef int						SOCKET ;
typedef void*					HANDLE ;
typedef HANDLE					HWND ;
typedef HANDLE					HMODULE ;
typedef HANDLE					HINSTANCE ;
typedef struct sockaddr			SOCKADDR ;
typedef void*					PVOID;
typedef void 					VOID;
typedef __int64 				INT64;

typedef bool 					BOOL;
typedef void*					LPVOID;            

union CURRENCY
{
	double value;
	__int64 int64;
};

#define INVALID_HANDLE_VALUE	((HANDLE)(-1))
#define INVALID_SOCKET  		(SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#define Sleep( s )				usleep( ( s ) * 1000 )
#define FALSE   				0
#define TRUE    				1
#define WINAPI
#define MAX_PATH 260

#define EZ_DLL_CALL             extern "C" __attribute__ ((noinline)) LONG 
#define EZ_DLL_BSTR             extern "C" __attribute__ ((noinline)) LCHAR* 

#define __stdcall 




// OVJ - 31/10/2012
#define INT64  __int64

#define WINAPI
#define MAX_PATH 260

#define stricmp strcasecmp

#define LPTSTR LCHAR*

#define EZ_LIB_NAME "EZClient.so.1"

// OVJ - 19/10/2012 - Funcoes de carga dinamica de bibliotecas
#define  LoadLibrary(a)		dlopen(a, RTLD_LAZY)	// Carrega bibliote em memoria
#define  GetProcAddress		dlsym					// Encontra apontador para funcao
#define  FreeLibrary		dlclose					// Libera biblioteca da memoria

//-----------------------------------------------------------------------------
#elif defined(_WIN32)

typedef BSTR*			PBSTR ;

#define EZ_LIB_NAME "EZClient.dll"

#endif

class CEZCLProcess ;

//-----------------------------------------------------------------------------
// Declaracao das funcoes da API EZForecourt
typedef LONG (WINAPI *typeDllVersion)( PBSTR pName );
typedef LONG (WINAPI *typeServerVersion)( PBSTR pName );
typedef LONG (WINAPI *typeClientLogon)( LONG ClientID , short ClientType , HANDLE Event , HWND hWnd, unsigned int wMsg);
typedef LONG (WINAPI *typeClientLogonEx)( LONG ClientID , short ClientType , BSTR ServerName , unsigned short CallPortNo , unsigned short EventsPortNo , LONG CallTimeout, HANDLE Event , HWND hWnd, unsigned int wMsg);
typedef LONG (WINAPI *typeClientLogoff)();
typedef LONG (WINAPI *typeClientStatus)( short* pPumpsReserved , short* pdeliveriesLocked );
typedef LONG (WINAPI *typeGetLicenseType)( short* pLicenseType );
typedef LONG (WINAPI *typeFireClientEvent)( LONG EventID , BSTR EventStr );
typedef LONG (WINAPI *typeTestConnection)();
typedef LONG (WINAPI *typeProcessEvents)();
typedef LONG (WINAPI *typeGetEventsCount)( LONG* pCount );
typedef LONG (WINAPI *typeGetNextEventType)( short* pType );
typedef LONG (WINAPI *typeDiscardNextEvent)();
typedef LONG (WINAPI *typeGetNextPumpEvent)( LONG* pPumpID, short* pPumpNumber, short* pState, short* pReservedFor, LONG* pReservedBy, LONG* pHoseID ,
							   short* pHoseNumber, LONG* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume,
							   double* pValue, short* pStackSize );
typedef LONG (WINAPI *typeGetNextDeliveryEvent)( LONG* pDeliveryID , LONG* pPumpID, short* pPumpNumber, LONG* pHoseID, short* pHoseNumber ,
								LONG* pGradeID, PBSTR pGradeName ,PBSTR pShortGradeName, short* pPriceLevel, double* pPrice, double* pVolume, double* pValue,
								short* pDeliveryState , short* pDeliveryType, LONG* pLockedBy, LONG* pReservedBy, LONG* pAge , DATE* pCompletedDT , LONG* pAttendantID );
typedef LONG (WINAPI *typeGetNextServerEvent)( LONG* pEventID, PBSTR pEventText );
typedef LONG (WINAPI *typeGetNextClientEvent)( LONG* pClientID, LONG* pEventID, PBSTR pEventText );
typedef LONG (WINAPI *typeGetNextDBLogEvent)( LONG* pEventType , LONG* pDeviceID , DATE* pEventDT , PBSTR pEventText );
typedef LONG (WINAPI *typeGetNextDBLogDeliveryEvent)( LONG* pDeliveryID, LONG* pHoseID, short* pDeliveryState, short* pDeliveryType, double* pVolume, short* pPriceLevel,
							 double* pPrice, double* pValue, double* pVolume2, LONG* pReservedBy , LONG* pAttendantID, DATE* pDeliveryDT );
typedef LONG (WINAPI *typeGetNextDBClearDeliveryEvent)( LONG* pDeliveryID, short* pDeliveryType, LONG* pClearedBY, DATE* pClearedDT, LONG* pAttendantID );
typedef LONG (WINAPI *typeGetNextDBStackDeliveryEvent)( LONG* pDeliveryID );
typedef LONG (WINAPI *typeGetNextDBHoseETotalsEvent)( LONG* pHoseID , double* pVolume , double* pValue , double* pVolumeETot , double* pValueETot );
typedef LONG (WINAPI *typeGetNextDBTriggerEvent)( LONG* pTableID ,LONG* pRowID );
typedef LONG (WINAPI *typeGetNextDBAttendantLogonEvent)( LONG* pAttendantID ,LONG* pPumpID );
typedef LONG (WINAPI *typeGetNextDBAttendantLogoffEvent)( LONG* pAttendantID );
typedef LONG (WINAPI *typeGetNextDBTankStatusEvent)( LONG* pTankID , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature ,
							          double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel );
typedef LONG (WINAPI *typeGetPumpsCount)( LONG* pCount );
typedef LONG (WINAPI *typeGetPumpByNumber)( LONG Number , LONG* pID );
typedef LONG (WINAPI *typeGetPumpByName)( BSTR Name , LONG* pID );
typedef LONG (WINAPI *typeGetPumpByOrdinal)( LONG Index , LONG* pID );
typedef LONG (WINAPI *typeGetPumpProperties)(LONG ID , LONG* pNumber, PBSTR pName, short* pPhysicalNumber, short* pSide, short* pAddress, short* pPriceLevel1,
						      short* pPriceLevel2, short* pPriceDspFormat, short* pVolumeDspFormat, short* pValueDspFormat, short* pType,
						      LONG* pPortID, LONG* pAttendantID, short* pAuthMode, short* pStackMode, short* pPrepayAllowed, short* pPreauthAllowed );
typedef LONG (WINAPI *typeSetPumpProperties)(LONG ID , LONG Number, BSTR Name, short PhysicalNumber, short Side, short Address, short PriceLevel1,
						      short PriceLevel2, short PriceDspFormat, short VolumeDspFormat, short ValueDspFormat, short Type,
						      LONG PortID, LONG AttendantID, short AuthMode, short StackMode, short PrepayAllowed, short PreauthAllowed );
typedef LONG (WINAPI *typeDeletePump)( LONG ID );
typedef LONG (WINAPI *typeGetPumpHosesCount)( LONG ID , LONG* pCount );
typedef LONG (WINAPI *typeGetPumpHoseByNumber)( LONG ID , LONG Number , LONG* pHoseID );
typedef LONG (WINAPI *typeGetPumpStatus)( LONG ID , short* pState, short* pReservedFor, LONG* pReservedBy, LONG* pHoseID, short* pHoseNumber ,
						   LONG* pGradeID, PBSTR pGradeName ,PBSTR pShortGradeName, short* pPriceLevel , double* pPrice , double* pVolume , double* pValue ,
						   short* pStackSize );

typedef LONG (WINAPI *typeGetPumpStatusEx)( LONG ID , LONG* pPumpNumber, PBSTR pPumpName, LONG* pPhysicalNumber, short* pState, short* pReservedFor, LONG* pReservedBy, LONG* pHoseID, LONG* pHoseNumber , LONG* pHosePhysicalNumber , LONG* pGradeID ,
					   LONG* pGradeNumber , PBSTR pGradeName, PBSTR pShortGradeName, short* pPriceLevel , double* pPrice , double* pVolume , double* pValue ,
					   short* pStackSize , __int64* pTag ,
					   LONG* pAttendantID , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
					   LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag );

typedef LONG (WINAPI *typeGetPumpDeliveryProperties)( LONG ID , short Index , LONG* pDeliveryID , short* pType , short* pState, LONG* pHoseID,
									   short* pHoseNum, LONG* pGradeID , PBSTR pGradeName ,PBSTR pShortGradeName, short* pPriceLevel, double* pPrice , double* pVolume ,
									   double* pValue , LONG* pLockedBy , LONG* pReservedBy , LONG* pAge , DATE* pCompletedDT , LONG* pAttendantID  );
typedef LONG (WINAPI *typeGetPumpDeliveryPropertiesEx)( LONG ID , short Index , LONG* pDeliveryID , short* pType , short* pState, LONG* pHoseID, short* pHoseNum, LONG* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName ,
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , LONG* pLockedBy ,
									    LONG* pReservedBy , LONG* pAge , DATE* pCompletedDT , LONG* pAttendantID , double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag );
typedef LONG (WINAPI *typeGetPumpDeliveryPropertiesEx2)( LONG ID , short Index , LONG* pDeliveryID , short* pType , short* pState, LONG* pHoseID, short* pHoseNum, LONG* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName ,
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , LONG* pLockedBy ,
									    LONG* pReservedBy , LONG* pAge , DATE* pCompletedDT , LONG* pAttendantID ,
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
										__int64* pTag , LONG * pDuration );
typedef LONG (WINAPI *typeGetPumpDeliveryPropertiesEx3)( LONG ID , short Index , LONG* pDeliveryID , short* pType , short* pState, LONG* pHoseID, short* pHoseNum, LONG* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName ,
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , LONG* pLockedBy ,
									    LONG* pReservedBy , LONG* pAge , DATE* pCompletedDT , LONG* pAttendantID ,
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
										__int64* pTag , LONG * pDuration , LONG* pCardClientID );
typedef LONG (WINAPI *typePrepayReserve)( LONG ID );
typedef LONG (WINAPI *typePrepayCancel)( LONG ID  );
typedef LONG (WINAPI *typePrepayAuthorise)( LONG ID , short LimitType , double Value , short Hose , short PriceLevel );
typedef LONG (WINAPI *typePreauthReserve)( LONG ID );
typedef LONG (WINAPI *typePreauthCancel)( LONG ID );
typedef LONG (WINAPI *typePreauthAuthorise)( LONG ID , short LimitType , double Value , short Hose , short PriceLevel );
typedef LONG (WINAPI *typeLoadPreset)( LONG ID , short LimitType , double Value , short Hose , short PriceLevel );
typedef LONG (WINAPI *typeLoadPresetWithPrice)( LONG ID , short LimitType , double Value , short Hose , short PriceLevel , double Price );
typedef LONG (WINAPI *typeTagAuthorise)( LONG ID , __int64 Tag , short LimitType , double Value , short Hose , short PriceLevel );
typedef LONG (WINAPI *typeAttendantAuthorise)( LONG ID , LONG AttendantID );
typedef LONG (WINAPI *typeAuthorise)( LONG ID );
typedef LONG (WINAPI *typeCancelAuthorise)( LONG ID );
typedef LONG (WINAPI *typeTempStop)( LONG ID );
typedef LONG (WINAPI *typeReAuthorise)( LONG ID );
typedef LONG (WINAPI *typeTerminateDelivery)( LONG ID );
typedef LONG (WINAPI *typeStackCurrentDelivery)( LONG ID );
typedef LONG (WINAPI *typeGetDensity)( LONG ID , double* pDensity);
typedef LONG (WINAPI *typeEnablePump)( LONG ID );
typedef LONG (WINAPI *typeDisablePump)( LONG ID );
typedef LONG (WINAPI *typeGetHosesCount)( LONG* pCount );
typedef LONG (WINAPI *typeGetHoseByOrdinal)( LONG Index , LONG* pID );
typedef LONG (WINAPI *typeGetHoseProperties)(LONG ID , LONG* pNumber, LONG* pPumpID ,LONG* pTankID , LONG* pPhysicalNumber,
		                      double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue ,
				              double* pMtrElecVolume );
typedef LONG (WINAPI *typeSetHoseProperties)(LONG ID , LONG Number,LONG PumpID, LONG TankID , LONG PhysicalNumber,
		                      double MtrTheoValue , double MtrTheoVolume ,double MtrElecValue ,
				              double MtrElecVolume );
typedef LONG (WINAPI *typeGetHoseSummary)(	LONG ID , LONG* pNumber, LONG* pPhysicalNumber,
							LONG* pPumpID, LONG* pPumpNumber, PBSTR pPumpName,
							LONG* pTankID, LONG* pTankNumber, PBSTR pTankName,
							LONG* pGradeID , LONG* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
		                    double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue , double* pMtrElecVolume );

typedef LONG (WINAPI *typeGetHoseSummaryEx)(	LONG ID , LONG* pNumber, LONG* pPhysicalNumber,
							LONG* pPumpID, LONG* pPumpNumber, PBSTR pPumpName,
							LONG* pTankID, LONG* pTankNumber, PBSTR pTankName,
							LONG* pGradeID , LONG* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
		                    double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue , double* pMtrElecVolume ,
							double* pPrice1 , double* pPrice2 , short* pEnabled);

typedef LONG (WINAPI *typeDeleteHose)( LONG ID );
typedef LONG (WINAPI *typeGetDeliveriesCount)( LONG* pCount );
typedef LONG (WINAPI *typeGetDeliveryByOrdinal)( LONG Index , LONG* pID );
typedef LONG (WINAPI *typeGetAllDeliveriesCount)( LONG* pCount )  ;
typedef LONG (WINAPI *typeGetAllDeliveryByOrdinal)( LONG Index , LONG* pID );

typedef LONG (WINAPI *typeAckDeliveryDBLog)( LONG ID );
typedef LONG (WINAPI *typeGetDeliveryIDByOrdinalNotLogged)( LONG Ordinal , LONG* pID );
typedef LONG (WINAPI *typeGetDeliveriesCountNotLogged)( LONG* pCount );
typedef LONG (WINAPI *typeAckDeliveryVolLog)( LONG ID );
typedef LONG (WINAPI *typeGetDeliveryIDByOrdinalNotVolLogged)( LONG Ordinal , LONG* pID );
typedef LONG (WINAPI *typeGetDeliveriesCountNotVolLogged)( LONG* pCount );

typedef LONG (WINAPI *typeGetDeliveryProperties)( LONG ID , LONG* pHoseID ,short* pState ,short* pType ,double* pVolume ,
								   short* pPriceLevel ,double* pPrice ,double* pValue ,double* pVolume2 ,
								   DATE* pCompletedDT ,LONG* pLockedBy , LONG* pReservedBy , LONG* pAttendantID , LONG* pAge );
typedef LONG (WINAPI *typeGetDeliveryPropertiesEx)( LONG ID , LONG* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                           double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, LONG* pReservedBy , LONG* pAttendantID , LONG* pAge ,
								   DATE* pClearedDT ,double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag );
typedef LONG (WINAPI *typeGetDeliveryPropertiesEx2)( LONG ID , LONG* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                           double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, LONG* pReservedBy ,
								   LONG* pAttendantID , LONG* pAge , DATE* pClearedDT ,
								   double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
								   double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
								   __int64* pTag , LONG * pDuration );
typedef LONG (WINAPI *typeGetDeliveryPropertiesEx3)( LONG ID , LONG* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                           double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, LONG* pReservedBy ,
								   LONG* pAttendantID , LONG* pAge , DATE* pClearedDT ,
								   double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
								   double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
								   __int64* pTag , LONG * pDuration , LONG* pCardClientID );

typedef LONG (WINAPI *typeSetDeliveryProperties)( LONG ID , LONG HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2, DATE CompletedDT ,LONG LockedBy, LONG ReservedBy ,
								   LONG AttendantID , LONG Age );
typedef LONG (WINAPI *typeSetDeliveryPropertiesEx)( LONG ID , LONG HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,LONG LockedBy,
								   LONG ReservedBy , LONG AttendantID , LONG Age , DATE ClearedDT , double VolumeETot , double Volume2ETot , double ValueETot , __int64 Tag );
typedef LONG (WINAPI *typeSetDeliveryPropertiesEx2)( LONG ID , LONG HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,LONG LockedBy,
								   LONG ReservedBy , LONG AttendantID , LONG Age , DATE ClearedDT ,
								   double OldVolumeETot , double OldVolume2ETot , double OldValueETot ,
								   double NewVolumeETot , double NewVolume2ETot , double NewValueETot ,
								   __int64 Tag , LONG Duration );


typedef LONG (WINAPI *typeSetDeliveryPropertiesEx3)( LONG ID , LONG HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,LONG LockedBy,
								   LONG ReservedBy , LONG AttendantID , LONG Age , DATE ClearedDT ,
								   double OldVolumeETot , double OldVolume2ETot , double OldValueETot ,
								   double NewVolumeETot , double NewVolume2ETot , double NewValueETot ,
								   __int64 Tag , LONG Duration , LONG CardClientID );

typedef LONG (WINAPI *typeGetDeliverySummary)( LONG ID , LONG* pHoseID ,LONG* pHoseNumber, LONG* pHosePhysicalNumber,
	  							LONG* pPumpID, LONG* pPumpNumber, PBSTR  pPumpName,
								LONG* pTankID, LONG* pTankNumber, PBSTR  pTankName,
								LONG* pGradeID , LONG* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
								double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy,
								LONG* pReservedBy , LONG* pAttendantID , LONG* pAge ,DATE* pClearedDT ,
								double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag);
typedef LONG (WINAPI *typeGetDeliverySummaryEx)( LONG ID , LONG* pHoseID ,LONG* pHoseNumber, LONG* pHosePhysicalNumber,
	  							LONG* pPumpID, LONG* pPumpNumber, PBSTR  pPumpName,
								LONG* pTankID, LONG* pTankNumber, PBSTR  pTankName,
								LONG* pGradeID , LONG* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                        double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy,
								LONG* pReservedBy , LONG* pAttendantID , LONG* pAge ,DATE* pClearedDT ,
								double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
								double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
								__int64* pTag , LONG * pDuration );
typedef LONG (WINAPI *typeGetDeliverySummaryEx2)( LONG ID , LONG* pHoseID ,LONG* pHoseNumber, LONG* pHosePhysicalNumber,
	  							LONG* pPumpID, LONG* pPumpNumber, PBSTR  pPumpName,
								LONG* pTankID, LONG* pTankNumber, PBSTR  pTankName,
								LONG* pGradeID , LONG* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                        double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy,
								LONG* pReservedBy , LONG* pAttendantID , LONG* pAge ,DATE* pClearedDT ,
								double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
								double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
								__int64* pTag , LONG * pDuration , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
								LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag );
typedef LONG (WINAPI *typeLockDelivery)( LONG ID );
typedef LONG (WINAPI *typeUnlockDelivery)( LONG ID );
typedef LONG (WINAPI *typeClearDelivery)( LONG ID , short Type );
typedef LONG (WINAPI *typeLockAndClearDelivery)( LONG ID , short Type );
typedef LONG (WINAPI *typeGetDuration)( LONG ID , LONG* pDuration );
typedef LONG (WINAPI *typeGetGradesCount)( LONG* pCount );
typedef LONG (WINAPI *typeGetGradeByNumber)( LONG Number , LONG* pID );
typedef LONG (WINAPI *typeGetGradeByName)( BSTR Name , LONG* pID );
typedef LONG (WINAPI *typeGetGradeByOrdinal)( LONG Index , LONG* pID );
typedef LONG (WINAPI *typeGetGradeProperties)(LONG ID , LONG* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pCode );
typedef LONG (WINAPI *typeSetGradeProperties)(LONG ID , LONG Number, BSTR Name , BSTR ShortName , BSTR Code  );
typedef LONG (WINAPI *typeDeleteGrade)( LONG ID );
typedef LONG (WINAPI *typeSetGradePrice)( LONG ID , short Level , double Price );
typedef LONG (WINAPI *typeGetGradePrice)( LONG ID , short Level , double* pPrice );
typedef LONG (WINAPI *typeGetTanksCount)( LONG* pCount );
typedef LONG (WINAPI *typeGetTankByNumber)( LONG Number , LONG* pID );
typedef LONG (WINAPI *typeGetTankByName)( BSTR Name , LONG* pID );
typedef LONG (WINAPI *typeGetTankByOrdinal)( LONG Index , LONG* pID );
typedef LONG (WINAPI *typeGetTankProperties)(LONG ID , LONG* pNumber, PBSTR pName , LONG* pGradeID , short* pType , double* pCapacity , double* pDiameter ,
							  double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature ,
							  double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, LONG* pGaugeID, short* pProbeNo );
typedef LONG (WINAPI *typeSetTankProperties)(LONG ID , LONG Number, BSTR Name , LONG GradeID , short Type , double Capacity , double Diameter , double TheoVolume ,
		                      double GaugeVolume , double GaugeTCVolume ,double GaugeUllage ,double GaugeTemperature , double GaugeLevel ,
							  double GaugeWaterVolume, double GaugeWaterLevel, LONG GaugeID , short ProbeNo );
typedef LONG (WINAPI *typeSetTankPropertiesEx)(LONG ID , LONG Number, BSTR Name , LONG GradeID , short Type , double Capacity , double Diameter , double TheoVolume ,
		                      double GaugeVolume , double GaugeTCVolume ,double GaugeUllage ,double GaugeTemperature , double GaugeLevel ,
							  double GaugeWaterVolume, double GaugeWaterLevel, LONG GaugeID , short ProbeNo, LONG GaugeAlarmsMask);
typedef LONG (WINAPI *typeGetTankSummary)(LONG ID , LONG* pNumber, PBSTR pName , LONG* pGradeID ,
						   LONG* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
						   short* pType , double* pCapacity , double* pDiameter ,
						   double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature ,
						   double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, LONG* pGaugeID, short* pProbeNo );
typedef LONG (WINAPI *typeTankDrop)( LONG ID , double Volume , DATE DropDT , BSTR Terminal , BSTR DocumentType , DATE DocumentDT  , BSTR DocumentFolio , double PEMEXVolume );
typedef LONG (WINAPI *typeDeleteTank)( LONG ID );
typedef LONG (WINAPI *typeGetPortsCount)( LONG* pCount );
typedef LONG (WINAPI *typeGetPortByNumber)( LONG Number , LONG* pID );
typedef LONG (WINAPI *typeGetPortByName)( BSTR Name , LONG* pID );
typedef LONG (WINAPI *typeGetPortByOrdinal)( LONG Index , LONG* pID );
typedef LONG (WINAPI *typeGetPortProperties)(LONG ID , LONG* pNumber, PBSTR pName , LONG* pProtocolID , short* pDeviceType , PBSTR pSerialNo );
typedef LONG (WINAPI *typeSetPortProperties)(LONG ID , LONG Number, BSTR Name, LONG ProtocolID , short DeviceType , BSTR SerialNo );
typedef LONG (WINAPI *typeGetAttendantsCount)( LONG* pCount );
typedef LONG (WINAPI *typeGetAttendantByNumber)( LONG Number , LONG* pID );
typedef LONG (WINAPI *typeGetAttendantByName)( BSTR Name , LONG* pID );
typedef LONG (WINAPI *typeGetAttendantByOrdinal)( LONG Index , LONG* pID );
typedef LONG (WINAPI *typeGetAttendantProperties)(LONG ID , LONG* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pPassword , PBSTR pTag );
typedef LONG (WINAPI *typeSetAttendantProperties)(LONG ID , LONG Number, BSTR Name , BSTR ShortName , BSTR Password , BSTR Tag );
typedef LONG (WINAPI *typeGetAttendantPropertiesEx)(LONG ID , LONG* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pPassword , PBSTR pTag ,
									 short* pShiftAStart , short* pShiftAEnd , short* pShiftBStart , short* pShiftBEnd , short* pEnabled )  ;
typedef LONG (WINAPI *typeSetAttendantPropertiesEx)(LONG ID , LONG Number, BSTR Name , BSTR ShortName , BSTR Password , BSTR Tag,
									 short ShiftAStart , short ShiftAEnd , short ShiftBStart , short ShiftBEnd , short Enabled )  ;
typedef LONG (WINAPI *typeDeleteAttendant)( LONG ID );
typedef LONG (WINAPI *typeAttendantLogon)( LONG ID , LONG PumpID );
typedef LONG (WINAPI *typeAttendantLogoff)( LONG ID );

typedef LONG (WINAPI *typeGetCardReadsCount)( LONG* pCount );
typedef LONG (WINAPI *typeGetCardReadByNumber)( LONG Number , LONG* pID );
typedef LONG (WINAPI *typeGetCardReadByName)( BSTR Name , LONG* pID );
typedef LONG (WINAPI *typeGetCardReadByOrdinal)( LONG Index , LONG* pID );
typedef LONG (WINAPI *typeGetCardReadProperties)(LONG ID , LONG* pNumber, PBSTR pName , LONG* pPumpID , short* pType , LONG* pParentID , __int64* pTag , DATE* pTimeStamp )  ;
typedef LONG (WINAPI *typeSetCardReadProperties)(LONG ID , LONG Number, BSTR Name , LONG PumpID , short Type , LONG ParentID , __int64 Tag , DATE TimeStamp)  ;
typedef LONG (WINAPI *typeDeleteCardRead)( LONG ID );
typedef LONG (WINAPI *typeGetCardClientsCount)( LONG* pCount );
typedef LONG (WINAPI *typeGetCardClientByNumber)( LONG Number , LONG* pID );
typedef LONG (WINAPI *typeGetCardClientByName)( BSTR Name , LONG* pID );
typedef LONG (WINAPI *typeGetCardClientByOrdinal)( LONG Index , LONG* pID );
typedef LONG (WINAPI *typeGetCardClientProperties)(LONG ID , LONG* pNumber, PBSTR pName , PBSTR pTag , short* pEnabled )  ;
typedef LONG (WINAPI *typeSetCardClientProperties)(LONG ID , LONG Number, BSTR Name , BSTR Tag , short Enabled )  ;
typedef LONG (WINAPI *typeDeleteCardClient)( LONG ID );

typedef LONG (WINAPI *typeAllStop)();
typedef LONG (WINAPI *typeAllAuthorise)();
typedef LONG (WINAPI *typeAllReAuthorise)();
typedef LONG (WINAPI *typeAllStopIfIdle)();
typedef LONG (WINAPI *typeReadAllTanks)();
typedef LONG (WINAPI *typeGetAllPumpStatuses)( PBSTR pStates , PBSTR pCurrentHoses , PBSTR pDeliveriesCount );
typedef LONG (WINAPI *typeGetIniValue)( BSTR Section , BSTR Key , PBSTR pValue );
typedef LONG (WINAPI *typeSetIniValue)( BSTR Section , BSTR Key , BSTR Value );
typedef LONG (WINAPI *typeSetNextDeliveryID)( LONG ID );
typedef LONG (WINAPI *typeRemovePort)( LONG ID );
typedef LONG (WINAPI *typeLicenseStatus)();
typedef LONG (WINAPI *typeCheckSocketClosed)( LPARAM lParam );

typedef BSTR (WINAPI *typeResultString)( LONG Res );
typedef BSTR (WINAPI *typePumpStateString)( short State );
typedef BSTR (WINAPI *typeDeliveryStateString)( short State );
typedef BSTR (WINAPI *typeDeliveryTypeString)( short Type );
typedef BSTR (WINAPI *typeReserveTypeString)( short Type );

// *** new APIS
typedef LONG (WINAPI *typeGetNextPumpEventEx)( LONG* pPumpID, short* pPumpNumber, short* pState, short* pReservedFor, LONG* pReservedBy, LONG* pHoseID ,
							    short* pHoseNumber,LONG* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume,
							    double* pValue, short* pStackSize , PBSTR pPumpName , short* pPhysicalNumber , short* pSide , short* pAddress,
								short* pPriceLevel1 , short* pPriceLevel2 , short* pType , LONG* pPortID , short* pAuthMode , short* pStackMode ,  short* pPrepayAllowed,
								short* pPreauthAllowed ,  short* pPriceFormat , short* pValueFormat , short* pVolumeFormat  );

typedef LONG (WINAPI *typeGetNextPumpEventEx2)( LONG* pPumpID, LONG* pPumpNumber, short* pState, short* pReservedFor, LONG* pReservedBy, LONG* pHoseID ,
							    LONG* pHoseNumber,LONG* pHosePhysicalNumber,LONG* pGradeID,LONG* pGradeNumber, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume,
							    double* pValue, short* pStackSize , PBSTR pPumpName , LONG* pPhysicalNumber , short* pSide , short* pAddress,
								short* pPriceLevel1 , short* pPriceLevel2 , short* pType , LONG* pPortID , short* pAuthMode , short* pStackMode ,  short* pPrepayAllowed,
								short* pPreauthAllowed ,  short* pPriceFormat , short* pValueFormat , short* pVolumeFormat , __int64* pTag ,
							    LONG* pAttendantID , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							    LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag  );

typedef LONG (WINAPI *typeGetNextDeliveryEventEx)( LONG* pDeliveryID , LONG* pPumpID, short* pPumpNumber, LONG* pHoseID, short* pHoseNumber ,
								    LONG* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel, double* pPrice,
									double* pVolume, double* pValue, short* pDeliveryState ,
								    short* pDeliveryType, LONG* pLockedBy, LONG* pReservedBy, LONG* pAge , DATE* pCompletedDT ,
									LONG* pAttendantID, double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag);
typedef LONG (WINAPI *typeGetNextDeliveryEventEx2)( LONG* pDeliveryID , LONG* pPumpID, short* pPumpNumber, LONG* pHoseID, short* pHoseNumber ,
								     LONG* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel, double* pPrice,
									 double* pVolume, double* pValue, short* pDeliveryState ,
								     short* pDeliveryType, LONG* pLockedBy, LONG* pReservedBy, LONG* pAge , DATE* pCompletedDT ,
									 LONG* pAttendantID,
									 double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
									 double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
									 __int64* pTag , LONG* pDuration );
typedef LONG (WINAPI *typeGetNextDeliveryEventEx3)( LONG* pDeliveryID, LONG* pHoseID ,LONG* pHoseNumber, LONG* pHosePhysicalNumber,
	  									LONG* pPumpID, LONG* pPumpNumber, PBSTR pPumpName,
										LONG* pTankID, LONG* pTankNumber, PBSTR pTankName,
										LONG* pGradeID , LONG* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
										short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT , LONG* pLockedBy,
										LONG* pReservedBy , LONG* pAttendantID , LONG* pAge , DATE* pClearedDT ,
										double* pOldVolumeETot, double* pOldVolume2ETot, double* pOldValueETot ,
										double* pNewVolumeETot, double* pNewVolume2ETot, double* pNewValueETot ,
										__int64* pTag , LONG* pDuration , LONG* pAttendantNumber , PBSTR AttendantName, __int64* pAttendantTag ,
										LONG* pCardClientID , LONG* pCardClientNumber , PBSTR CardClientName, __int64* pCardClientTag );
typedef LONG (WINAPI *typeGetNextCardReadEvent)( LONG* pCardReadID , LONG* pNumber, PBSTR pName , LONG* pPumpID , short* pType , LONG* pParentID , __int64* pTag , DATE* pTimeStamp);
typedef LONG (WINAPI *typeGetNextDBHoseETotalsEventEx)( LONG* pHoseID , double* pVolume , double* pValue , double* pVolumeETot , double* pValueETot ,
										 LONG* pHoseNumber , LONG* pHosePhysicalNumber , LONG* pPumpID , LONG* pPumpNumber , PBSTR pPumpName ,
										 LONG* pTankID , LONG* pTankNumber , PBSTR pTankName , LONG* pGradeID , PBSTR pGradeName );
typedef LONG (WINAPI *typeGetNextDBTankStatusEventEx)( LONG* pTankID , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage,
									    double* pGaugeTemperature , double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel ,
									    LONG* pTankNumber , PBSTR pTankName , LONG* pGradeID , PBSTR pGradeName , short*pType  ,
										double* pCapacity , double* pDiameter , LONG* pGaugeID , short* pProbeNo);
typedef LONG (WINAPI *typeGetZigBeeCount)( LONG* pCount );
typedef LONG (WINAPI *typeGetZigBeeByNumber)( LONG Number , LONG* pID );
typedef LONG (WINAPI *typeGetZigBeeByName)( BSTR Name , LONG* pID );
typedef LONG (WINAPI *typeGetZigBeeByOrdinal)( LONG Index , LONG* pID );
typedef LONG (WINAPI *typeGetZigBeeProperties)(LONG ID , LONG* pNumber, PBSTR pName , short* pDeviceType , PBSTR pSerialNumber , PBSTR pNodeIdentifier , LONG* pPortID );
typedef LONG (WINAPI *typeSetZigBeeProperties)(LONG ID , LONG Number, BSTR Name , short DeviceType , BSTR SerialNumber , BSTR NodeIdentifier , LONG PortID );
typedef LONG (WINAPI *typeDeleteZigBee)( LONG ID );
typedef LONG (WINAPI *typeGetHosePropertiesEx)(LONG ID , LONG* pNumber, LONG* pPumpID ,LONG* pTankID , LONG* pPhysicalNumber,
		                      double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue ,
				              double* pMtrElecVolume , short* pUVEAntenna );
typedef LONG (WINAPI *typeSetHosePropertiesEx)(LONG ID , LONG Number,LONG PumpID, LONG TankID , LONG PhysicalNumber,
		                      double MtrTheoValue , double MtrTheoVolume ,double MtrElecValue ,
				              double MtrElecVolume , short UVEAntenna );
typedef LONG (WINAPI *typeGetHosePropertiesEx2)(LONG ID , LONG* pNumber, LONG* pPumpID ,LONG* pTankID , LONG* pPhysicalNumber,
		                      double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue ,
				              double* pMtrElecVolume , short* pUVEAntenna , double* pPrice1 , double* pPrice2 , short* pEnabled );
typedef LONG (WINAPI *typeSetHosePropertiesEx2)(LONG ID , LONG Number,LONG PumpID, LONG TankID , LONG PhysicalNumber,
		                      double MtrTheoValue , double MtrTheoVolume ,double MtrElecValue ,
				              double MtrElecVolume , short UVEAntenna , double Price1 , double Price2 , short Enabled );
typedef LONG (WINAPI *typeSetPumpPropertiesEx)(LONG ID , LONG Number, BSTR Name, short PhysicalNumber, short Side, short Address, short PriceLevel1,
						        short PriceLevel2, short PriceDspFormat, short VolumeDspFormat, short ValueDspFormat, short Type,
						        LONG PortID, LONG AttendantID, short AuthMode, short StackMode, short PrepayAllowed, short PreauthAllowed ,
								LONG SlotZigBeeID , LONG MuxSlotZigBeeID , short PriceControl , short HasPreset );
typedef LONG (WINAPI *typeGetPumpPropertiesEx)(LONG ID , LONG* pNumber, PBSTR pName, short* pPhysicalNumber, short* pSide, short* pAddress, short* pPriceLevel1,
						      short* pPriceLevel2, short* pPriceDspFormat, short* pVolumeDspFormat, short* pValueDspFormat, short* pType,
						      LONG* pPortID, LONG* pAttendantID, short* pAuthMode, short* pStackMode, short* pPrepayAllowed, short* pPreauthAllowed ,
							  LONG* pSlotZigBeeID , LONG* pMuxSlotZigBeeID , short* pPriceControl , short* pHasPreset);
typedef LONG (WINAPI *typeGetSerialNo)( LONG ID , PBSTR pSerialNo );
typedef LONG (WINAPI *typeGetDeviceDetails)( LONG ID , LONG ZBID , PBSTR pSerialNo , PBSTR pBootVersion , PBSTR pFirmwareVersion );
typedef LONG (WINAPI *typeResetDevice)( LONG ID , LONG ZBID );
typedef LONG (WINAPI *typeRequestVersion)( LONG ID , LONG ZBID );
typedef LONG (WINAPI *typeSetHoseETotals)( LONG ID , double Volume , double Value );
typedef LONG (WINAPI *typeGetNextZBStatusEvent)( LONG* pPortID , LONG* pZBID , __int64* pZBAddress, short* pCondition , short* pCount , short* pStrength );
typedef LONG (WINAPI *typeGetNextZBPanIDEvent)( LONG* pPortID , __int64* pZBPanID );
typedef LONG (WINAPI *typeGetNextZeroDeliveryEvent)( LONG* pPumpID , LONG* pPumpNumber , LONG* pHoseID , LONG* pHoseNumber );
typedef LONG (WINAPI *typeSetHosePrices)( LONG ID , short DurationType , short PriceType , double Price1 , double Price2 );
typedef LONG (WINAPI *typeGetHosePrices)( LONG ID , short* pDurationType , short* pPriceType , double* pPrice1 , double* pPrice2 );
typedef LONG (WINAPI *typeSetPumpDefaultPriceLevel)( LONG ID , short Level );
typedef LONG (WINAPI *typeSetDateTime)( DATE DateTime );
typedef LONG (WINAPI *typeGetSensorsCount)(LONG* pCount);
typedef LONG (WINAPI *typeGetSensorByOrdinal)(LONG Index, LONG* ID);
typedef LONG (WINAPI *typeGetSensorProperties)(LONG ID, LONG* Number, PBSTR Name, LONG* PortID, short* Type, short* Address, short* SensorNo);
typedef LONG (WINAPI *typeSetGradePropertiesEx)(LONG GradeID, LONG GradeNumber, PBSTR GradeName, PBSTR GradeShortName, PBSTR GradeCode, short GradeType);
typedef LONG (WINAPI *typeGetClientsCount)( LONG* pCount );
typedef LONG (WINAPI *typeGetPumpStatusEx2)( LONG ID , LONG* pPumpNumber, PBSTR pPumpName, LONG* pPhysicalNumber, short* pState, short* pReservedFor, LONG* pReservedBy, LONG* pHoseID, LONG* pHoseNumber , LONG* pHosePhysicalNumber , LONG* pGradeID , 
							  LONG* pGradeNumber , PBSTR pGradeName, PBSTR pShortGradeName, short* pPriceLevel , double* pPrice , double* pVolume , double* pValue , short* pStackSize , __int64* pTag , 
							  LONG* pAttendantID , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							  LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag , 
							  double* pCurFlowRate , double* pPeakFlowRate );
typedef LONG (WINAPI *typeCheckforManagementFtn)();
typedef LONG (WINAPI *typeFireEvents)();
typedef LONG (WINAPI *typePaymentReserve)( LONG ID , LONG TermID , BSTR TermHash );
typedef LONG (WINAPI *typePaymentCancel)( LONG ID , LONG TermID , BSTR TermHash );
typedef LONG (WINAPI *typePaymentAuthorise)( LONG ID , LONG TermID , BSTR TermHash ,
							  LONG AttendantID , __int64 AttendantTag , 
							  LONG CardClientID , __int64 CardClientTag , 
							  short AuthType , __int64 ExtTag ,
							  short GradeType , short PriceType  , short PriceLevel , double Price , 
							  short PresetType , double Value , short Hose ,
							  double Odometer , double Odometer2 , BSTR Plate , 
							  BSTR ExtTransactionID , BSTR DriverID , BSTR AuthorisationID );
typedef LONG (WINAPI *typeDeliveriesCountFiltered)(LONG* pCount, LONG PumpID, LONG HoseID, 
	                          LONG GradeID, LONG TankID, LONG LockedBy, LONG ReservedBy, short State, 
	                          short Type, __int64 Tag, LONG AttendantID, LONG CardClientID);
typedef LONG (WINAPI *typeGetDeliveryIDByOrdinalFiletered)(LONG Ordinal, LONG* pID, LONG PumpID, 
	                          LONG HoseID, LONG GradeID, LONG TankID, LONG LockedBy, LONG ReservedBy, 
	                          short State, short Type, __int64 Tag, LONG AttendantID, LONG CardClientID);
typedef LONG (WINAPI *typeGetDeliveryPropertiesEx4)( LONG ID , LONG* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, LONG* pReservedBy , 
										LONG* pAttendantID , LONG* pAge , DATE* pClearedDT ,
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , LONG * pDuration , LONG* pCardClientID , double* pPeakFlowRate ) ;
typedef LONG (WINAPI *typeSetDeliveryPropertiesEx4)( LONG ID , LONG HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,LONG LockedBy, 
								   LONG ReservedBy , LONG AttendantID , LONG Age , DATE ClearedDT , 
								   double OldVolumeETot , double OldVolume2ETot , double OldValueETot , 
								   double NewVolumeETot , double NewVolume2ETot , double NewValueETot , 
								   __int64 Tag , LONG Duration , LONG CardClientID, double PeakFlowRate ) ;
typedef LONG (WINAPI *typeGetPumpDeliveryPropertiesEx4)( LONG ID , short Index , LONG* pDeliveryID , short* pType , short* pState, LONG* pHoseID, short* pHoseNum, LONG* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName , 
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , LONG* pLockedBy , 
									    LONG* pReservedBy , LONG* pAge , DATE* pCompletedDT , LONG* pAttendantID , 
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , LONG * pDuration , LONG* pCardClientID , double* pPeakFlowRate  ) ;
typedef LONG (WINAPI *typeGetDeliverySummaryEx3)( LONG ID , LONG* pHoseID ,LONG* pHoseNumber, LONG* pHosePhysicalNumber,
	  							LONG* pPumpID, LONG* pPumpNumber, PBSTR  pPumpName,
								LONG* pTankID, LONG* pTankNumber, PBSTR  pTankName,
								LONG* pGradeID , LONG* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                        double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, 
								LONG* pReservedBy , LONG* pAttendantID , LONG* pAge ,DATE* pClearedDT ,
								double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
								double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
								__int64* pTag , LONG * pDuration , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
								LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag  , double* pPeakFlowRate ) ;
typedef LONG (WINAPI *typeGetDeliverySummaryEx4)(LONG ID, LONG* pHoseID, LONG* pHoseNumber, LONG* pHosePhysicalNumber,
								LONG* pPumpID, LONG* pPumpNumber, PBSTR  pPumpName,
								LONG* pTankID, LONG* pTankNumber, PBSTR  pTankName,
								LONG* pGradeID, LONG* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
								short* pState, short* pType, double* pVolume, short* pPriceLevel,
								double* pPrice, double* pValue, double* pVolume2, DATE* pCompletedDT, LONG* pLockedBy,
								LONG* pReservedBy, LONG* pAttendantID, LONG* pAge, DATE* pClearedDT,
								double* pOldVolumeETot, double* pOldVolume2ETot, double* pOldValueETot,
								double* pNewVolumeETot, double* pNewVolume2ETot, double* pNewValueETot,
								__int64* pTag, LONG * pDuration, LONG* pAttendantNumber, PBSTR pAttendantName, __int64* pAttendantTag, PBSTR pAttendantIDNumber,
								LONG* pCardClientID, LONG* pCardClientNumber, PBSTR pCardClientName, __int64* pCardClientTag, PBSTR pCardClientIDNumber, double* pPeakFlowRate);
typedef LONG (WINAPI *typeSetDeliveryExt)( LONG ID , BSTR Plate , double Odometer , double Odometer2 , BSTR ExtTransactionID ,
                                BSTR DriverID , BSTR AuthID, short AuthType ) ;
typedef LONG (WINAPI *typeGetDeliveryExt)( LONG ID , PBSTR pPlate , double* pOdometer , double* pOdometer2 , PBSTR pExtTransactionID ,
                                PBSTR pDriverID , PBSTR pAuthID, short* pAuthType ) ;
typedef LONG (WINAPI *typeGetGradePropertiesEx)(LONG ID , LONG* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pCode , 
	                            short* pType );
typedef LONG (WINAPI *typeGetTankPropertiesEx)(LONG ID , LONG* pNumber, PBSTR pName , LONG* pGradeID , short* pType , double* pCapacity , double* pDiameter , 
							  double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
							  double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, LONG* pGaugeID, short* pProbeNo , LONG* pGaugeAlarmsMask );
typedef LONG (WINAPI *typeGetTankSummaryEx)(LONG ID , LONG* pNumber, PBSTR pName , LONG* pGradeID , 
						      LONG* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode, 
						      short* pType , double* pCapacity , double* pDiameter , 
						      double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
						      double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, LONG* pGaugeID, short* pProbeNo , 
						      short* pState , LONG* pGaugeAlarmsMask);
typedef LONG (WINAPI *typeGetAttendantPropertiesEx2)(LONG ID, LONG* pNumber, PBSTR pName, PBSTR pShortName, PBSTR pPassword, 
	                          PBSTR pTag, PBSTR pIDNumber,short* pShiftAStart, short* pShiftAEnd, short* pShiftBStart, 
	                          short* pShiftBEnd, short* pType);
typedef LONG (WINAPI *typeSetAttendantPropertiesEx2)(LONG ID, LONG Number, BSTR Name, BSTR ShortName, BSTR Password, BSTR Tag, 
	                          BSTR IDNumber,short ShiftAStart, short ShiftAEnd, short ShiftBStart, short ShiftBEnd, short Type);
typedef LONG (WINAPI *typeGetAttendantState)( LONG ID , short* pType , short* pLoggedOn ) ;
typedef LONG (WINAPI *typeGetCardClientPropertiesEx)(LONG ID , LONG* pNumber, PBSTR pName , PBSTR pTag , short* pEnabled , 
	                          short* pPriceLevel, PBSTR pPlate  ) ;
typedef LONG (WINAPI *typeSetCardClientPropertiesEx)(LONG ID , LONG Number, BSTR Name , BSTR Tag , short Enabled , short PriceLevel , BSTR Plate );
typedef LONG (WINAPI *typeSetCardClientPropertiesEx2)(LONG ID , LONG Number, BSTR Name , BSTR Tag , short Enabled , short PriceLevel ,
                              BSTR Plate , short GradeType, short CardType, short LimitType, double Limit, short EntryType,
                              DATE ExpirationDate, LONG ParentID ) ;
typedef LONG (WINAPI *typeGetCardClientPropertiesEx2)(LONG ID , LONG* pNumber, PBSTR pName , PBSTR pTag , short* pEnabled , 
	                          short* pPriceLevel , PBSTR pPlate , short* pGradeType, short* pCardType, short* pLimitType, 
	                          double* pLimit, short* pEntryType, DATE* pExpirationDate, LONG* pParentID ) ;
typedef LONG (WINAPI *typeGetCardClientPropertiesEx3)(LONG ID, LONG* pNumber, PBSTR pName, PBSTR pTag, short* pEnabled, 
	                          short* pPriceLevel, PBSTR pPlate, PBSTR pIDNumber, PBSTR pShortName, PBSTR pPassword,
	                          short* pGradeType, short* pCardType, short* pLimitType, double* pLimit, short* pEntryType,
	                          DATE* pExpirationDate, LONG* pParentID);
typedef LONG (WINAPI *typeSetCardClientPropertiesEx3)(LONG ID, LONG Number, BSTR Name, BSTR Tag, short Enabled, short PriceLevel,
							  BSTR Plate, BSTR IDNumber, BSTR ShortName, BSTR Password, short GradeType, short CardType, 
							  short LimitType, double Limit, short EntryType, DATE ExpirationDate, LONG ParentID);
typedef LONG (WINAPI *typeScheduleBeep)( LONG ID , short Pitch1 , short Duration1 , short Pitch2 , short Duration2,
                              short Pitch3 , short Duration3, short Pitch4 , short Duration4, short Pitch5 , short Duration5 );
typedef LONG (WINAPI *typeFlashLEDS)( LONG ID , short Side , short PeriodMs , short Cycles );
typedef LONG (WINAPI *typeGetIniValueEx)( BSTR FileName , BSTR Section , BSTR Key , PBSTR pValue );
typedef LONG (WINAPI *typeSetIniValueEx)( BSTR FileName , BSTR Section , BSTR Key , BSTR Value );
typedef LONG (WINAPI *typeGetCardType)( BSTR Tag , short* pTagType , LONG* pID, PBSTR pName, LONG* pNumber  );
typedef LONG (WINAPI *typeFindCard)(BSTR Tag, short* pCardType, short* pTagType, LONG* pID, PBSTR pName, LONG* pNumber);
typedef LONG (WINAPI *typeGetNextPumpEventEx3)( LONG* pPumpID, LONG* pPumpNumber, short* pState, short* pReservedFor, LONG* pReservedBy, LONG* pHoseID ,
							    LONG* pHoseNumber,LONG* pHosePhysicalNumber,LONG* pGradeID,LONG* pGradeNumber, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume, 
							    double* pValue, short* pStackSize , PBSTR pPumpName , LONG* pPhysicalNumber , short* pSide , short* pAddress, 
								short* pPriceLevel1 , short* pPriceLevel2 , short* pType , LONG* pPortID , short* pAuthMode , short* pStackMode ,  short* pPrepayAllowed, 
								short* pPreauthAllowed ,  short* pPriceFormat , short* pValueFormat , short* pVolumeFormat , __int64* pTag , 
							    LONG* pAttendantID , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							    LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag , 
								double* pCurFlowRate , double* pPeakFlowRate );
typedef LONG (WINAPI *typeGetNextDeliveryEventEx4)( LONG* pDeliveryID, LONG* pHoseID ,LONG* pHoseNumber, LONG* pHosePhysicalNumber,
	  									LONG* pPumpID, LONG* pPumpNumber, PBSTR pPumpName,
										LONG* pTankID, LONG* pTankNumber, PBSTR pTankName,
										LONG* pGradeID , LONG* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
										short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT , LONG* pLockedBy, 
										LONG* pReservedBy , LONG* pAttendantID , LONG* pAge , DATE* pClearedDT , 
										double* pOldVolumeETot, double* pOldVolume2ETot, double* pOldValueETot , 
										double* pNewVolumeETot, double* pNewVolume2ETot, double* pNewValueETot , 
										__int64* pTag , LONG* pDuration , LONG* pAttendantNumber , PBSTR AttendantName, __int64* pAttendantTag ,
										LONG* pCardClientID , LONG* pCardClientNumber , PBSTR CardClientName, __int64* pCardClientTag , double* pPeakFlowRate) ;
typedef LONG (WINAPI *typeGetNextDBTankStatusEventEx2)( LONG* pTankID , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, 
									    double* pGaugeTemperature , double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel , 
									    LONG* pTankNumber , PBSTR pTankName , LONG* pGradeID , PBSTR pGradeName , short*pType  , double* pCapacity , 
										double* pDiameter , LONG* pGaugeID , short* pProbeNo , short* pState , LONG* pAlarmsMask ) ;
typedef LONG (WINAPI *typeGetNextSerialPortEvent)( LONG* pPortID , LONG* pZBID , short* pSlot , short* pResult , PBSTR pRxMsg ) ;
typedef LONG (WINAPI *typeGetNextZBEvent)( LONG* pPortID , LONG* pZBID , __int64* pZBAddress, short* pResult , short* pMsgType , PBSTR pRxMsg ) ;
typedef LONG (WINAPI *typeGetNextUVEEvent)( LONG* pPumpID , LONG* pPumpNumber , LONG* pHoseID , LONG* pHoseNumber , PBSTR pUVE ) ;
typedef LONG (WINAPI *typeSetZBCoordPan)( LONG ID , __int64 Pan ) ;
typedef LONG (WINAPI *typeGetZBCoordPan)( LONG ID ) ;
typedef LONG (WINAPI *typeSetLineMode)( LONG ID , LONG ZBID , short Mode ) ;
typedef LONG (WINAPI *typeGetDateTime)( DATE* pDateTime ) ;
typedef LONG (WINAPI *typeGetNextZB2GStatusEvent)( LONG* pPortID , __int64* pZBAddress, short* pLQI , short* pRSSI , __int64*  pParZBAddress, short* pZBChannel , short* pMemBlocks , short* pMemFree ) ;
typedef LONG (WINAPI *typeGetZB2GConfig)( LONG ID , __int64* pPanID , LONG* pChannels , __int64* pKeyA , __int64* pKeyB );
typedef LONG (WINAPI *typeGetLogEventCount)( LONG* pCount , short DeviceType , LONG DeviceID , short EventLevel , short EventType , LONG ClearedBy, LONG  AckedBy ) ;
typedef LONG (WINAPI *typeGetLogEventByOrdinal)( LONG Index , LONG* pID , short DeviceType , LONG DeviceID , short EventLevel , short EventType ,LONG  ClearedBy, LONG  AckedBy ) ;
typedef LONG (WINAPI *typeGetLogEventProperties)(LONG ID , short* pDeviceType , LONG* pDeviceID , LONG* pDeviceNumber ,	PBSTR pDeviceName , short* pEventLevel ,
								        short* pEventType , PBSTR pEventDesc , DATE* pGeneratedDT , DATE* pClearedDT , LONG* pClearedBy , LONG* pAckedBy , double* pVolume ,
								        double* pValue , double* pProductVolume , double* pProductLevel , double* pWaterLevel , double* pTemperature);
typedef LONG (WINAPI *typeSetLogEventProperties)(LONG ID , short DeviceType , LONG DeviceID , LONG DeviceNumber , BSTR DeviceName , short EventLevel ,
									short EventType , BSTR  EventDesc , DATE GeneratedDT , DATE ClearedDT , LONG  ClearedBy , LONG AckedBy , double  Volume ,
									double  Value , double  ProductVolume ,	double  ProductLevel , double  WaterLevel , double  Temperature );
typedef LONG (WINAPI *typeDeleteLogEvent)( LONG ID );
typedef LONG (WINAPI *typeGetNextLogEventEvent)(LONG* pLogEventID , short* pDeviceType , LONG* pDeviceID , LONG* pDeviceNumber ,	PBSTR pDeviceName , short* pEventLevel ,
								     short* pEventType , PBSTR pEventDesc , DATE* pGeneratedDT , DATE* pClearedDT , LONG* pClearedBy , LONG* pAckedBy , double* pVolume ,
								     double* pValue , double* pProductVolume , double* pProductLevel , double* pWaterLevel , double* pTemperature);
typedef LONG (WINAPI *typeClearLogEvent)( LONG ID  , LONG ClientID );
typedef LONG (WINAPI *typeAckLogEvent)( LONG ID  , LONG ClientID );
typedef LONG (WINAPI *typeGetSensorByNumber)( LONG Number , LONG* pID );
typedef LONG (WINAPI *typeGetSensorByName)( BSTR Name , LONG* pID ) ;
typedef LONG (WINAPI *typeSetSensorProperties)(LONG ID , LONG Number, BSTR Name , LONG PortID , short Type, short Address , short SensorNo );
typedef LONG (WINAPI *typeSetSensorStatus)(LONG ID , short State , short IsResponding );
typedef LONG (WINAPI *typeGetSensorStatus)(LONG ID , short* pState , short* pIsResponding );
typedef LONG (WINAPI *typeDeleteSensor)( LONG ID ) ;
typedef LONG (WINAPI *typeSetLogPath)(BSTR Path);
typedef LONG (WINAPI *typeLog)(BSTR Text);
typedef LONG (WINAPI *typeSetClientType)( LONG ClientKey ) ;
typedef LONG (WINAPI *typeGetNextSaleItemEvent)(LONG* pSaleItemID, LONG* pProductID, LONG* pProductNumber, PBSTR pProductName, __int64* pProductTag, LONG* pProductGroup, PBSTR pProductGroupName, PBSTR pBarcode,
								 LONG* pPumpID, LONG* pPumpNumber, PBSTR pPumpName,
								 LONG* pAttendantID, LONG* pAttendantNumber, PBSTR pAttendantName, __int64* pAttendantTag,
								 LONG* pCardClientID, LONG* pCardClientNumber, PBSTR pCardClientName, __int64* pCardClientTag,
								 short* pPriceLevel, double* pPrice, double* pQuantity, DATE* pAddedDT, DATE* pClearedDT,
								 LONG* pLockedBy, LONG* pClearedBy, short* pLoggedDB, short* pLoggedVolumetric,
								 PBSTR pPlate, PBSTR pDriverID, PBSTR pExtTransactionID, PBSTR pAuthID, short* pAuthType);
typedef LONG (WINAPI *typeGetProductByNumber)(LONG Number, LONG* pID);
typedef LONG (WINAPI *typeGetProductByName)(BSTR Name, LONG* pID);
typedef LONG (WINAPI *typeGetProductProperties)(LONG ID, LONG* pNumber, PBSTR pName, PBSTR pTag, short* pEnabled, PBSTR pShortName,
                                 PBSTR pBarcode, double* pPrice1, double* pPrice2, LONG* pProductGroup);
typedef LONG (WINAPI *typeSetProductProperties)(LONG ID, LONG Number, BSTR Name, BSTR Tag, short Enabled, BSTR ShortName, 
	                             BSTR Barcode, double Price1, double Price2, LONG ProductGroup);
typedef LONG (WINAPI *typeDeleteProduct)(LONG ID);
typedef LONG (WINAPI *typeGetProductsCount)(LONG* pCount, LONG Number, BSTR Name, BSTR ShortName, BSTR Tag, BSTR Barcode, LONG ProductGroup);
typedef LONG (WINAPI *typeGetProductByOrdinal)(LONG Index, LONG* pID, LONG Number, BSTR Name, BSTR ShortName, BSTR Tag, BSTR Barcode, LONG ProductGroup);
typedef LONG (WINAPI *typeDeleteSaleItem)(LONG ID);

//--------------------------------------- M�todos MT ----------------------------------------//


typedef LONG (WINAPI *typeServerVersionMT)(CEZCLProcess* pCLProcess ,  PBSTR pName ) ;
typedef LONG (WINAPI *typeClientLogonMT)(CEZCLProcess** ppCLProcess ,  LONG ClientID , short ClientType , HANDLE Event , HWND hWnd, unsigned int wMsg) ;
typedef LONG (WINAPI *typeClientLogonExMT)(CEZCLProcess** ppCLProcess ,  LONG ClientID , short ClientType , BSTR ServerName , unsigned short CallPortNo , unsigned short EventsPortNo , LONG CallTimeout, HANDLE Event , HWND hWnd, unsigned int wMsg) ;
typedef LONG (WINAPI *typeClientLogoffMT)(CEZCLProcess** ppCLProcess ) ;
typedef LONG (WINAPI *typeClientStatusMT)(CEZCLProcess* pCLProcess ,  short* pPumpsReserved , short* pdeliveriesLocked ) ;
typedef LONG (WINAPI *typeGetLicenseTypeMT)(CEZCLProcess* pCLProcess ,  short* pLicenseType ) ;
typedef LONG (WINAPI *typeFireClientEventMT)(CEZCLProcess* pCLProcess ,  LONG EventID , BSTR EventStr ) ;
typedef LONG (WINAPI *typeCheckForManagementFtnMT)(CEZCLProcess** ppCLProcess);
typedef LONG (WINAPI *typeTestConnectionMT)(CEZCLProcess* pCLProcess ) ;
typedef LONG (WINAPI *typeFireEventsMT)(CEZCLProcess* pCLProcess);
typedef LONG (WINAPI *typeProcessEventsMT)(CEZCLProcess* pCLProcess ) ;
typedef LONG (WINAPI *typeGetEventsCountMT)(CEZCLProcess* pCLProcess ,  LONG* pCount ) ;
typedef LONG (WINAPI *typeGetNextEventTypeMT)(CEZCLProcess* pCLProcess ,  short* pType ) ;
typedef LONG (WINAPI *typeDiscardNextEventMT)(CEZCLProcess* pCLProcess ) ;
typedef LONG (WINAPI *typeGetNextPumpEventMT)(CEZCLProcess* pCLProcess ,  LONG* pPumpID, short* pPumpNumber, short* pState, short* pReservedFor, LONG* pReservedBy, LONG* pHoseID ,
							   short* pHoseNumber, LONG* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume, 
							   double* pValue, short* pStackSize ) ;
typedef LONG (WINAPI *typeGetNextDeliveryEventMT)(CEZCLProcess* pCLProcess ,  LONG* pDeliveryID , LONG* pPumpID, short* pPumpNumber, LONG* pHoseID, short* pHoseNumber , 
								LONG* pGradeID, PBSTR pGradeName ,PBSTR pShortGradeName, short* pPriceLevel, double* pPrice, double* pVolume, double* pValue, 
								short* pDeliveryState , short* pDeliveryType, LONG* pLockedBy, LONG* pReservedBy, LONG* pAge , DATE* pCompletedDT , LONG* pAttendantID ) ;
typedef LONG (WINAPI *typeGetNextServerEventMT)(CEZCLProcess* pCLProcess ,  LONG* pEventID, PBSTR pEventText ) ;
typedef LONG (WINAPI *typeGetNextClientEventMT)(CEZCLProcess* pCLProcess ,  LONG* pClientID, LONG* pEventID, PBSTR pEventText ) ;
typedef LONG (WINAPI *typeGetNextDBLogEventMT)(CEZCLProcess* pCLProcess ,  LONG* pEventType , LONG* pDeviceID , DATE* pEventDT , PBSTR pEventText ) ;
typedef LONG (WINAPI *typeGetNextDBLogDeliveryEventMT)(CEZCLProcess* pCLProcess ,  LONG* pDeliveryID, LONG* pHoseID, short* pDeliveryState, short* pDeliveryType, double* pVolume, short* pPriceLevel, 
							 double* pPrice, double* pValue, double* pVolume2, LONG* pReservedBy , LONG* pAttendantID, DATE* pDeliveryDT ) ;
typedef LONG (WINAPI *typeGetNextDBClearDeliveryEventMT)(CEZCLProcess* pCLProcess ,  LONG* pDeliveryID, short* pDeliveryType, LONG* pClearedBY, DATE* pClearedDT, LONG* pAttendantID ) ;
typedef LONG (WINAPI *typeGetNextDBStackDeliveryEventMT)(CEZCLProcess* pCLProcess ,  LONG* pDeliveryID ) ;
typedef LONG (WINAPI *typeGetNextDBHoseETotalsEventMT)(CEZCLProcess* pCLProcess ,  LONG* pHoseID , double* pVolume , double* pValue , double* pVolumeETot , double* pValueETot ) ;
typedef LONG (WINAPI *typeGetNextDBTriggerEventMT)(CEZCLProcess* pCLProcess ,  LONG* pTableID ,LONG* pRowID ) ;
typedef LONG (WINAPI *typeGetNextDBAttendantLogonEventMT)(CEZCLProcess* pCLProcess ,  LONG* pAttendantID ,LONG* pPumpID ) ;
typedef LONG (WINAPI *typeGetNextDBAttendantLogoffEventMT)(CEZCLProcess* pCLProcess ,  LONG* pAttendantID ) ;
typedef LONG (WINAPI *typeGetNextDBTankStatusEventMT)(CEZCLProcess* pCLProcess ,  LONG* pTankID , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
							          double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel ) ;
typedef LONG (WINAPI *typeGetClientsCountMT)( CEZCLProcess* pCLProcess , LONG* pCount ) ;
typedef LONG (WINAPI *typeGetPumpsCountMT)(CEZCLProcess* pCLProcess ,  LONG* pCount ) ;
typedef LONG (WINAPI *typeGetPumpByNumberMT)(CEZCLProcess* pCLProcess ,  LONG Number , LONG* pID ) ;
typedef LONG (WINAPI *typeGetPumpByNameMT)(CEZCLProcess* pCLProcess ,  BSTR Name , LONG* pID ) ;
typedef LONG (WINAPI *typeGetPumpByOrdinalMT)(CEZCLProcess* pCLProcess ,  LONG Index , LONG* pID ) ;
typedef LONG (WINAPI *typeGetPumpPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName, short* pPhysicalNumber, short* pSide, short* pAddress, short* pPriceLevel1,
						      short* pPriceLevel2, short* pPriceDspFormat, short* pVolumeDspFormat, short* pValueDspFormat, short* pType,  
						      LONG* pPortID, LONG* pAttendantID, short* pAuthMode, short* pStackMode, short* pPrepayAllowed, short* pPreauthAllowed ) ;
typedef LONG (WINAPI *typeSetPumpPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name, short PhysicalNumber, short Side, short Address, short PriceLevel1,
						      short PriceLevel2, short PriceDspFormat, short VolumeDspFormat, short ValueDspFormat, short Type, 
						      LONG PortID, LONG AttendantID, short AuthMode, short StackMode, short PrepayAllowed, short PreauthAllowed ) ;
typedef LONG (WINAPI *typeDeletePumpMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeGetPumpHosesCountMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG* pCount ) ;
typedef LONG (WINAPI *typeGetPumpHoseByNumberMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG Number , LONG* pHoseID ) ;
typedef LONG (WINAPI *typeGetPumpStatusMT)(CEZCLProcess* pCLProcess ,  LONG ID , short* pState, short* pReservedFor, LONG* pReservedBy, LONG* pHoseID, short* pHoseNumber , 
						   LONG* pGradeID, PBSTR pGradeName ,PBSTR pShortGradeName, short* pPriceLevel , double* pPrice , double* pVolume , double* pValue , 
						   short* pStackSize ) ;
typedef LONG (WINAPI *typeGetPumpStatusExMT)( CEZCLProcess* pCLProcess , LONG ID , LONG* pPumpNumber, PBSTR pPumpName, LONG* pPhysicalNumber, 
							   short* pState, short* pReservedFor, LONG* pReservedBy, 
							   LONG* pHoseID, LONG* pHoseNumber , LONG* pHosePhysicalNumber , 
							   LONG* pGradeID , LONG* pGradeNumber , PBSTR pGradeName, PBSTR pShortGradeName, 
							   short* pPriceLevel , double* pPrice , double* pVolume , double* pValue , short* pStackSize , __int64* pTag , 
							   LONG* pAttendantID , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							   LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag ) ;

typedef LONG (WINAPI *typeGetPumpStatusEx2MT)( CEZCLProcess* pCLProcess , LONG ID , LONG* pPumpNumber, PBSTR pPumpName, LONG* pPhysicalNumber, 
							  short* pState, short* pReservedFor, LONG* pReservedBy, 
							  LONG* pHoseID, LONG* pHoseNumber , LONG* pHosePhysicalNumber , 
							  LONG* pGradeID , LONG* pGradeNumber , PBSTR pGradeName, PBSTR pShortGradeName, 
							  short* pPriceLevel , double* pPrice , double* pVolume , double* pValue , short* pStackSize , __int64* pTag , 
							  LONG* pAttendantID , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							  LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag , 
							  double* pCurFlowRate , double* pPeakFlowRate ) ;

typedef LONG (WINAPI *typeGetPumpDeliveryPropertiesMT)(CEZCLProcess* pCLProcess ,  LONG ID , short Index , LONG* pDeliveryID , short* pType , short* pState, LONG* pHoseID, 
									   short* pHoseNum, LONG* pGradeID , PBSTR pGradeName ,PBSTR pShortGradeName, short* pPriceLevel, double* pPrice , double* pVolume , 
									   double* pValue , LONG* pLockedBy , LONG* pReservedBy , LONG* pAge , DATE* pCompletedDT , LONG* pAttendantID  ) ;
typedef LONG (WINAPI *typeGetPumpDeliveryPropertiesExMT)(CEZCLProcess* pCLProcess ,  LONG ID , short Index , LONG* pDeliveryID , short* pType , short* pState, LONG* pHoseID, short* pHoseNum, LONG* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName , 
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , LONG* pLockedBy , 
									    LONG* pReservedBy , LONG* pAge , DATE* pCompletedDT , LONG* pAttendantID , double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag ) ;
typedef LONG (WINAPI *typeGetPumpDeliveryPropertiesEx2MT)( CEZCLProcess* pCLProcess , LONG ID , short Index , LONG* pDeliveryID , short* pType , short* pState, LONG* pHoseID, short* pHoseNum, LONG* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName , 
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , LONG* pLockedBy , 
									    LONG* pReservedBy , LONG* pAge , DATE* pCompletedDT , LONG* pAttendantID , 
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , LONG * pDuration ) ;
typedef LONG (WINAPI *typeGetPumpDeliveryPropertiesEx3MT)( CEZCLProcess* pCLProcess , LONG ID , short Index , LONG* pDeliveryID , short* pType , short* pState, 
										   LONG* pHoseID, short* pHoseNum, 
										   LONG* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName , 
											short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , LONG* pLockedBy , 
											LONG* pReservedBy , LONG* pAge , DATE* pCompletedDT , LONG* pAttendantID , 
											double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
											double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
											__int64* pTag , LONG * pDuration , LONG* pCardClientID ) ;
typedef LONG (WINAPI *typePrepayReserveMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typePrepayCancelMT)(CEZCLProcess* pCLProcess ,  LONG ID  ) ;
typedef LONG (WINAPI *typePrepayAuthoriseMT)(CEZCLProcess* pCLProcess ,  LONG ID , short LimitType , double Value , short Hose , short PriceLevel ) ;
typedef LONG (WINAPI *typePreauthReserveMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typePreauthCancelMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typePreauthAuthoriseMT)(CEZCLProcess* pCLProcess ,  LONG ID , short LimitType , double Value , short Hose , short PriceLevel ) ;
typedef LONG (WINAPI *typeLoadPresetMT)(CEZCLProcess* pCLProcess ,  LONG ID , short LimitType , double Value , short Hose , short PriceLevel ) ;
typedef LONG (WINAPI *typeLoadPresetWithPriceMT)(CEZCLProcess* pCLProcess ,  LONG ID , short LimitType , double Value , short Hose , short PriceLevel , double Price ) ;
typedef LONG (WINAPI *typeTagAuthoriseMT)(CEZCLProcess* pCLProcess ,  LONG ID , __int64 Tag , short LimitType , double Value , short Hose , short PriceLevel ) ;
typedef LONG (WINAPI *typePaymentReserveMT)( CEZCLProcess* pCLProcess , LONG ID , LONG TermID , BSTR TermHash ) ;
typedef LONG (WINAPI *typePaymentCancelMT)( CEZCLProcess* pCLProcess , LONG ID , LONG TermID , BSTR TermHash ) ;
typedef LONG (WINAPI *typePaymentAuthoriseMT)( CEZCLProcess* pCLProcess , LONG ID , LONG TermID , BSTR TermHash ,
							  LONG AttendantID , __int64 AttendantTag , 
							  LONG CardClientID , __int64 CardClientTag , 
							  short AuthType , __int64 ExtTag ,
							  short GradeType , short PriceType  , short PriceLevel , double Price , 
							  short PresetType , double Value , short Hose ,
							  double Odometer , double Odometer2 , BSTR Plate , 
							  BSTR ExtTransactionID , BSTR DriverID , BSTR AuthorisationID ) ;
typedef LONG (WINAPI *typeAttendantAuthoriseMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG AttendantID ) ;
typedef LONG (WINAPI *typeAuthoriseMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeCancelAuthoriseMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeTempStopMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeReAuthoriseMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeTerminateDeliveryMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeStackCurrentDeliveryMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeGetDensityMT)( CEZCLProcess* pCLProcess , LONG ID , double* pDensity ) ;
typedef LONG (WINAPI *typeEnablePumpMT)( CEZCLProcess* pCLProcess , LONG ID ) ;
typedef LONG (WINAPI *typeDisablePumpMT)( CEZCLProcess* pCLProcess , LONG ID ) ;
typedef LONG (WINAPI *typeGetHosesCountMT)(CEZCLProcess* pCLProcess ,  LONG* pCount ) ;
typedef LONG (WINAPI *typeGetHoseByOrdinalMT)(CEZCLProcess* pCLProcess ,  LONG Index , LONG* pID ) ;
typedef LONG (WINAPI *typeGetHosePropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, LONG* pPumpID ,LONG* pTankID , LONG* pPhysicalNumber, 
		                      double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue ,
				              double* pMtrElecVolume ) ;
typedef LONG (WINAPI *typeSetHosePropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number,LONG PumpID, LONG TankID , LONG PhysicalNumber, 
		                      double MtrTheoValue , double MtrTheoVolume ,double MtrElecValue ,
				              double MtrElecVolume ) ;
typedef LONG (WINAPI *typeGetHoseSummaryMT)(CEZCLProcess* pCLProcess , 	LONG ID , LONG* pNumber, LONG* pPhysicalNumber,
							LONG* pPumpID, LONG* pPumpNumber, PBSTR pPumpName,
							LONG* pTankID, LONG* pTankNumber, PBSTR pTankName,
							LONG* pGradeID , LONG* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
		                    double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue , double* pMtrElecVolume ) ;
typedef LONG (WINAPI *typeGetHoseSummaryExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, LONG* pPhysicalNumber,
							LONG* pPumpID, LONG* pPumpNumber, PBSTR pPumpName,
							LONG* pTankID, LONG* pTankNumber, PBSTR pTankName,
							LONG* pGradeID , LONG* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
		                    double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue , double* pMtrElecVolume ,
							double* pPrice1 , double* pPrice2 , short* pEnabled ) ;
typedef LONG (WINAPI *typeDeleteHoseMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeGetDeliveriesCountMT)(CEZCLProcess* pCLProcess ,  LONG* pCount ) ;
typedef LONG (WINAPI *typeGetDeliveryByOrdinalMT)(CEZCLProcess* pCLProcess ,  LONG Index , LONG* pID ) ;
typedef LONG (WINAPI *typeGetAllDeliveriesCountMT)(CEZCLProcess* pCLProcess ,  LONG* pCount )  ;
typedef LONG (WINAPI *typeGetAllDeliveryByOrdinalMT)(CEZCLProcess* pCLProcess ,  LONG Index , LONG* pID ) ;

typedef LONG (WINAPI *typeAckDeliveryDBLogMT)(CEZCLProcess* pCLProcess , LONG ID ) ; 
typedef LONG (WINAPI *typeGetDeliveryIDByOrdinalNotLoggedMT)(CEZCLProcess* pCLProcess , LONG Ordinal , LONG* pID ) ;
typedef LONG (WINAPI *typeGetDeliveriesCountNotLoggedMT)(CEZCLProcess* pCLProcess , LONG* pCount ) ;

typedef LONG (WINAPI *typeDeliveriesCountFilteredMT)(CEZCLProcess* pCLProcess, LONG* pCount, LONG PumpID, LONG HoseID, LONG GradeID, LONG TankID, LONG LockedBy, LONG ReservedBy, short State, short Type, __int64 Tag, LONG AttendantID, LONG CardClientID);
typedef LONG (WINAPI *typeGetDeliveryIDByOrdinalFileteredMT)(CEZCLProcess* pCLProcess, LONG Ordinal, LONG* pID, LONG PumpID, LONG HoseID, LONG GradeID, LONG TankID, LONG LockedBy, LONG ReservedBy, short State, short Type, __int64 Tag, LONG AttendantID, LONG CardClientID);

typedef LONG (WINAPI *typeAckDeliveryVolLogMT)(CEZCLProcess* pCLProcess , LONG ID ) ; 
typedef LONG (WINAPI *typeGetDeliveryIDByOrdinalNotVolLoggedMT)(CEZCLProcess* pCLProcess , LONG Ordinal , LONG* pID ) ;
typedef LONG (WINAPI *typeGetDeliveriesCountNotVolLoggedMT)(CEZCLProcess* pCLProcess , LONG* pCount ) ;

typedef LONG (WINAPI *typeGetDeliveryPropertiesMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG* pHoseID ,short* pState ,short* pType ,double* pVolume ,
								   short* pPriceLevel ,double* pPrice ,double* pValue ,double* pVolume2 , 
								   DATE* pCompletedDT ,LONG* pLockedBy , LONG* pReservedBy , LONG* pAttendantID , LONG* pAge ) ;
typedef LONG (WINAPI *typeGetDeliveryPropertiesExMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                           double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, LONG* pReservedBy , LONG* pAttendantID , LONG* pAge , 
								   DATE* pClearedDT ,double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag ) ;
typedef LONG (WINAPI *typeGetDeliveryPropertiesEx2MT)( CEZCLProcess* pCLProcess , LONG ID , LONG* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, LONG* pReservedBy , 
										LONG* pAttendantID , LONG* pAge , DATE* pClearedDT ,
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , LONG * pDuration ) ;
typedef LONG (WINAPI *typeGetDeliveryPropertiesEx3MT)( CEZCLProcess* pCLProcess , LONG ID , LONG* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, LONG* pReservedBy , 
										LONG* pAttendantID , LONG* pAge , DATE* pClearedDT ,
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , LONG * pDuration , LONG* pCardClientID ) ;
typedef LONG (WINAPI *typeGetDeliveryPropertiesEx4MT)( CEZCLProcess* pCLProcess , LONG ID , LONG* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, LONG* pReservedBy , 
										LONG* pAttendantID , LONG* pAge , DATE* pClearedDT ,
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , LONG * pDuration , LONG* pCardClientID , double* pPeakFlowRate ) ;

typedef LONG (WINAPI *typeSetDeliveryPropertiesEx4MT)( CEZCLProcess* pCLProcess , LONG ID , LONG HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,LONG LockedBy, 
								   LONG ReservedBy , LONG AttendantID , LONG Age , DATE ClearedDT , 
								   double OldVolumeETot , double OldVolume2ETot , double OldValueETot , 
								   double NewVolumeETot , double NewVolume2ETot , double NewValueETot , 
								   __int64 Tag , LONG Duration , LONG CardClientID, double PeakFlowRate ) ;
typedef LONG (WINAPI *typeGetPumpDeliveryPropertiesEx4MT)( CEZCLProcess* pCLProcess , LONG ID , short Index , LONG* pDeliveryID , short* pType , short* pState, 
										   LONG* pHoseID, short* pHoseNum, 
										   LONG* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName , 
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , LONG* pLockedBy , 
									    LONG* pReservedBy , LONG* pAge , DATE* pCompletedDT , LONG* pAttendantID , 
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , LONG * pDuration , LONG* pCardClientID , double* pPeakFlowRate ) ;
typedef LONG (WINAPI *typeSetDeliveryPropertiesMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2, DATE CompletedDT ,LONG LockedBy, LONG ReservedBy , 
								   LONG AttendantID , LONG Age ) ;
typedef LONG (WINAPI *typeSetDeliveryPropertiesExMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,LONG LockedBy, 
								   LONG ReservedBy , LONG AttendantID , LONG Age , DATE ClearedDT , double VolumeETot , double Volume2ETot , double ValueETot , __int64 Tag ) ;
typedef LONG (WINAPI *typeSetDeliveryPropertiesEx2MT)( CEZCLProcess* pCLProcess , LONG ID , LONG HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,LONG LockedBy, 
								   LONG ReservedBy , LONG AttendantID , LONG Age , DATE ClearedDT , 
								   double OldVolumeETot , double OldVolume2ETot , double OldValueETot , 
								   double NewVolumeETot , double NewVolume2ETot , double NewValueETot , 
								   __int64 Tag , LONG Duration ) ;
typedef LONG (WINAPI *typeSetDeliveryPropertiesEx3MT)( CEZCLProcess* pCLProcess , LONG ID , LONG HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,LONG LockedBy, 
								   LONG ReservedBy , LONG AttendantID , LONG Age , DATE ClearedDT , 
								   double OldVolumeETot , double OldVolume2ETot , double OldValueETot , 
								   double NewVolumeETot , double NewVolume2ETot , double NewValueETot , 
								   __int64 Tag , LONG Duration , LONG CardClientID ) ;
typedef LONG (WINAPI *typeGetDeliverySummaryMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG* pHoseID ,LONG* pHoseNumber, LONG* pHosePhysicalNumber,
	  							LONG* pPumpID, LONG* pPumpNumber, PBSTR  pPumpName,
								LONG* pTankID, LONG* pTankNumber, PBSTR  pTankName,
								LONG* pGradeID , LONG* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
								short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
								double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, 
								LONG* pReservedBy , LONG* pAttendantID , LONG* pAge ,DATE* pClearedDT ,
								double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag) ;
typedef LONG (WINAPI *typeGetDeliverySummaryExMT)( CEZCLProcess* pCLProcess , LONG ID , LONG* pHoseID ,LONG* pHoseNumber, LONG* pHosePhysicalNumber,
	  							LONG* pPumpID, LONG* pPumpNumber, PBSTR  pPumpName,
								LONG* pTankID, LONG* pTankNumber, PBSTR  pTankName,
								LONG* pGradeID , LONG* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                        double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, 
								LONG* pReservedBy , LONG* pAttendantID , LONG* pAge ,DATE* pClearedDT ,
								double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
								double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
								__int64* pTag , LONG * pDuration ) ;
typedef LONG (WINAPI *typeGetDeliverySummaryEx2MT)( CEZCLProcess* pCLProcess , LONG ID , LONG* pHoseID ,LONG* pHoseNumber, LONG* pHosePhysicalNumber,
	  							LONG* pPumpID, LONG* pPumpNumber, PBSTR  pPumpName,
								LONG* pTankID, LONG* pTankNumber, PBSTR  pTankName,
								LONG* pGradeID , LONG* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                        double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, 
								LONG* pReservedBy , LONG* pAttendantID , LONG* pAge ,DATE* pClearedDT ,
								double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
								double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
								__int64* pTag , LONG * pDuration , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
								LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag ) ;

typedef LONG (WINAPI *typeGetDeliverySummaryEx3MT)( CEZCLProcess* pCLProcess , LONG ID , LONG* pHoseID ,LONG* pHoseNumber, LONG* pHosePhysicalNumber,
	  							LONG* pPumpID, LONG* pPumpNumber, PBSTR  pPumpName,
								LONG* pTankID, LONG* pTankNumber, PBSTR  pTankName,
								LONG* pGradeID , LONG* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                        double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,LONG* pLockedBy, 
								LONG* pReservedBy , LONG* pAttendantID , LONG* pAge ,DATE* pClearedDT ,
								double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
								double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
								__int64* pTag , LONG * pDuration , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
								LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag , double* pPeakFlowRate ) ;

typedef LONG (WINAPI *typeGetDeliverySummaryEx4MT)(CEZCLProcess* pCLProcess, LONG ID, LONG* pHoseID, LONG* pHoseNumber, LONG* pHosePhysicalNumber,
								LONG* pPumpID, LONG* pPumpNumber, PBSTR  pPumpName,
								LONG* pTankID, LONG* pTankNumber, PBSTR  pTankName,
								LONG* pGradeID, LONG* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
								short* pState, short* pType, double* pVolume, short* pPriceLevel,
								double* pPrice, double* pValue, double* pVolume2, DATE* pCompletedDT, LONG* pLockedBy,
								LONG* pReservedBy, LONG* pAttendantID, LONG* pAge, DATE* pClearedDT,
								double* pOldVolumeETot, double* pOldVolume2ETot, double* pOldValueETot,
								double* pNewVolumeETot, double* pNewVolume2ETot, double* pNewValueETot,
								__int64* pTag, LONG * pDuration, LONG* pAttendantNumber, PBSTR pAttendantName, __int64* pAttendantTag, PBSTR pAttendantIDNumber,
								LONG* pCardClientID, LONG* pCardClientNumber, PBSTR pCardClientName, __int64* pCardClientTag, PBSTR pCardClientIDNumber, double* pPeakFlowRate);


typedef LONG (WINAPI *typeLockDeliveryMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeUnlockDeliveryMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeClearDeliveryMT)(CEZCLProcess* pCLProcess ,  LONG ID , short Type ) ;
typedef LONG (WINAPI *typeLockAndClearDeliveryMT)(CEZCLProcess* pCLProcess ,  LONG ID , short Type ) ;
typedef LONG (WINAPI *typeGetDurationMT)( CEZCLProcess* pCLProcess , LONG ID , LONG* pDuration ) ;
typedef LONG (WINAPI *typeSetDeliveryExtMT)( CEZCLProcess* pCLProcess , LONG ID , BSTR Plate , double Odometer , double Odometer2 , BSTR ExtTransactionID , BSTR DriverID , BSTR AuthID, short AuthType ) ;
typedef LONG (WINAPI *typeGetDeliveryExtMT)( CEZCLProcess* pCLProcess , LONG ID , PBSTR pPlate , double* pOdometer , double* pOdometer2 , PBSTR pExtTransactionID , PBSTR pDriverID , PBSTR pAuthID, short* pAuthType) ;
typedef LONG (WINAPI *typeGetGradesCountMT)(CEZCLProcess* pCLProcess ,  LONG* pCount ) ;
typedef LONG (WINAPI *typeGetGradeByNumberMT)(CEZCLProcess* pCLProcess ,  LONG Number , LONG* pID ) ;
typedef LONG (WINAPI *typeGetGradeByNameMT)(CEZCLProcess* pCLProcess ,  BSTR Name , LONG* pID ) ;
typedef LONG (WINAPI *typeGetGradeByOrdinalMT)(CEZCLProcess* pCLProcess ,  LONG Index , LONG* pID ) ;
typedef LONG (WINAPI *typeGetGradePropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pCode ) ;
typedef LONG (WINAPI *typeSetGradePropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name , BSTR ShortName , BSTR Code  ) ;
typedef LONG (WINAPI *typeGetGradePropertiesExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pCode , short* pType ) ;
typedef LONG (WINAPI *typeSetGradePropertiesExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name , BSTR ShortName , BSTR Code , short Type  ) ;
typedef LONG (WINAPI *typeDeleteGradeMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeSetGradePriceMT)(CEZCLProcess* pCLProcess ,  LONG ID , short Level , double Price ) ;
typedef LONG (WINAPI *typeGetGradePriceMT)(CEZCLProcess* pCLProcess ,  LONG ID , short Level , double* pPrice ) ;
typedef LONG (WINAPI *typeGetTanksCountMT)(CEZCLProcess* pCLProcess ,  LONG* pCount ) ;
typedef LONG (WINAPI *typeGetTankByNumberMT)(CEZCLProcess* pCLProcess ,  LONG Number , LONG* pID ) ;
typedef LONG (WINAPI *typeGetTankByNameMT)(CEZCLProcess* pCLProcess ,  BSTR Name , LONG* pID ) ;
typedef LONG (WINAPI *typeGetTankByOrdinalMT)(CEZCLProcess* pCLProcess ,  LONG Index , LONG* pID ) ;



typedef LONG (WINAPI *typeGetTankPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , LONG* pGradeID , short* pType , double* pCapacity , double* pDiameter , 
							  double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
							  double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, LONG* pGaugeID, short* pProbeNo ) ;
typedef LONG (WINAPI *typeSetTankPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name , LONG GradeID , short Type , double Capacity , double Diameter , double TheoVolume , 
		                      double GaugeVolume , double GaugeTCVolume ,double GaugeUllage ,double GaugeTemperature , double GaugeLevel , 
							  double GaugeWaterVolume, double GaugeWaterLevel, LONG GaugeID , short ProbeNo ) ;

typedef LONG (WINAPI *typeGetTankPropertiesExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , LONG* pGradeID , short* pType , double* pCapacity , double* pDiameter , 
							  double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
							  double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, LONG* pGaugeID, short* pProbeNo , LONG* pGaugeAlarmsMask ) ;
typedef LONG (WINAPI *typeSetTankPropertiesExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name , LONG GradeID , short Type , double Capacity , double Diameter , double TheoVolume , 
		                      double GaugeVolume , double GaugeTCVolume ,double GaugeUllage ,double GaugeTemperature , double GaugeLevel , 
							  double GaugeWaterVolume, double GaugeWaterLevel, LONG GaugeID , short ProbeNo , LONG GaugeAlarmsMask ) ;

typedef LONG (WINAPI *typeGetTankSummaryMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , LONG* pGradeID , 
						   LONG* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode, 
						   short* pType , double* pCapacity , double* pDiameter , 
						   double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
						   double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, LONG* pGaugeID, short* pProbeNo ) ;

typedef LONG (WINAPI *typeGetTankSummaryExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , LONG* pGradeID , 
						   LONG* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode, 
						   short* pType , double* pCapacity , double* pDiameter , 
						   double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
						   double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, LONG* pGaugeID, short* pProbeNo , 
						   short* pState , LONG* pGaugeAlarmsMask ) ;

typedef LONG (WINAPI *typeTankDropMT)(CEZCLProcess* pCLProcess ,  LONG ID , double Volume , DATE DropDT , BSTR Terminal , BSTR DocumentType , DATE DocumentDT  , BSTR DocumentFolio , double PEMEXVolume ) ;
typedef LONG (WINAPI *typeDeleteTankMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeGetPortsCountMT)(CEZCLProcess* pCLProcess ,  LONG* pCount ) ;
typedef LONG (WINAPI *typeGetPortByNumberMT)(CEZCLProcess* pCLProcess ,  LONG Number , LONG* pID ) ;
typedef LONG (WINAPI *typeGetPortByNameMT)(CEZCLProcess* pCLProcess ,  BSTR Name , LONG* pID ) ;
typedef LONG (WINAPI *typeGetPortByOrdinalMT)(CEZCLProcess* pCLProcess ,  LONG Index , LONG* pID ) ;
typedef LONG (WINAPI *typeGetPortPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , LONG* pProtocolID , short* pDeviceType , PBSTR pSerialNo ) ;
typedef LONG (WINAPI *typeSetPortPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name, LONG ProtocolID , short DeviceType , BSTR SerialNo ) ;
typedef LONG (WINAPI *typeDeletePortMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeGetAttendantsCountMT)(CEZCLProcess* pCLProcess ,  LONG* pCount ) ;
typedef LONG (WINAPI *typeGetAttendantByNumberMT)(CEZCLProcess* pCLProcess ,  LONG Number , LONG* pID ) ;
typedef LONG (WINAPI *typeGetAttendantByNameMT)(CEZCLProcess* pCLProcess ,  BSTR Name , LONG* pID ) ;
typedef LONG (WINAPI *typeGetAttendantByOrdinalMT)(CEZCLProcess* pCLProcess ,  LONG Index , LONG* pID ) ;
typedef LONG (WINAPI *typeGetAttendantPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pPassword , PBSTR pTag ) ; 
typedef LONG (WINAPI *typeSetAttendantPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name , BSTR ShortName , BSTR Password , BSTR Tag) ; 
typedef LONG (WINAPI *typeSetAttendantPropertiesExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name , BSTR ShortName , BSTR Password , BSTR Tag , short ShiftAStart , short ShiftAEnd , short ShiftBStart , short ShiftBEnd , short Type )  ;
typedef LONG (WINAPI *typeGetAttendantPropertiesExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pPassword , PBSTR pTag , short* pShiftAStart , short* pShiftAEnd , short* pShiftBStart , short* pShiftBEnd , short* pType ) ; 
typedef LONG (WINAPI *typeGetAttendantPropertiesEx2MT)(CEZCLProcess* pCLProcess, LONG ID, LONG* pNumber, PBSTR pName, PBSTR pShortName, PBSTR pPassword, PBSTR pTag, PBSTR pIDNumber, short* pShiftAStart, short* pShiftAEnd, short* pShiftBStart, short* pShiftBEnd, short* pType);
typedef LONG (WINAPI *typeSetAttendantPropertiesEx2MT)(CEZCLProcess* pCLProcess, LONG ID, LONG Number, BSTR Name, BSTR ShortName, BSTR Password, BSTR Tag, BSTR IDNumber, short ShiftAStart, short ShiftAEnd, short ShiftBStart, short ShiftBEnd, short Type);


typedef LONG (WINAPI *typeGetAttendantStateMT)(CEZCLProcess* pCLProcess , LONG ID , short* pType , short* pLoggedOn ) ;
typedef LONG (WINAPI *typeDeleteAttendantMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeAttendantLogonMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG PumpID ) ;
typedef LONG (WINAPI *typeAttendantLogoffMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;

typedef LONG (WINAPI *typeGetCardReadsCountMT)( CEZCLProcess* pCLProcess , LONG* pCount ) ;
typedef LONG (WINAPI *typeGetCardReadByNumberMT)( CEZCLProcess* pCLProcess , LONG Number , LONG* pID ) ;
typedef LONG (WINAPI *typeGetCardReadByNameMT)( CEZCLProcess* pCLProcess , BSTR Name , LONG* pID ) ;
typedef LONG (WINAPI *typeGetCardReadByOrdinalMT)( CEZCLProcess* pCLProcess , LONG Index , LONG* pID ) ;
typedef LONG (WINAPI *typeGetCardReadPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , LONG* pPumpID , short* pType , LONG* pParentID , __int64* pTag , DATE* pTimeStamp  )  ;
typedef LONG (WINAPI *typeSetCardReadPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name , LONG PumpID , short Type , LONG ParentID , __int64 Tag , DATE TimeStamp )  ;
typedef LONG (WINAPI *typeDeleteCardReadMT)( CEZCLProcess* pCLProcess , LONG ID ) ;
typedef LONG (WINAPI *typeGetCardClientsCountMT)( CEZCLProcess* pCLProcess , LONG* pCount ) ;
typedef LONG (WINAPI *typeGetCardClientByNumberMT)( CEZCLProcess* pCLProcess , LONG Number , LONG* pID ) ;
typedef LONG (WINAPI *typeGetCardClientByNameMT)( CEZCLProcess* pCLProcess , BSTR Name , LONG* pID ) ;
typedef LONG (WINAPI *typeGetCardClientByOrdinalMT)( CEZCLProcess* pCLProcess , LONG Index , LONG* pID ) ;
typedef LONG (WINAPI *typeGetCardClientPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , PBSTR pTag , short* pEnabled  )  ;
typedef LONG (WINAPI *typeSetCardClientPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name , BSTR Tag , short Enabled  )  ;
typedef LONG (WINAPI *typeSetCardClientPropertiesExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name , BSTR Tag , short Enabled , short PriceLevel , BSTR Plate )  ;
typedef LONG (WINAPI *typeGetCardClientPropertiesExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , PBSTR pTag , short* pEnabled , short* pPriceLevel , PBSTR pPlate )  ;
typedef LONG (WINAPI *typeSetCardClientPropertiesEx2MT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name , BSTR Tag , short Enabled , short PriceLevel , BSTR Plate , short GradeType, short CardType, short LimitType, double Limit, short EntryType, DATE ExpirationDate, LONG ParentID )  ;
typedef LONG (WINAPI *typeGetCardClientPropertiesEx2MT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , PBSTR pTag , short* pEnabled , short* pPriceLevel , PBSTR pPlate , short* pGradeType, short* pCardType, short* pLimitType, double* pLimit, short* pEntryType, DATE* pExpirationDate, LONG* pParentID )  ;
typedef LONG (WINAPI *typeGetCardClientPropertiesEx3MT)(CEZCLProcess* pCLProcess, LONG ID, LONG* pNumber, PBSTR pName, PBSTR pTag, short* pEnabled, short* pPriceLevel, PBSTR pPlate, PBSTR pIDNumber, PBSTR pShortName, PBSTR pPassword, short* pGradeType, short* pCardType, short* pLimitType, double* pLimit, short* pEntryType, DATE* pExpirationDate, LONG* pParentID);
typedef LONG (WINAPI *typeSetCardClientPropertiesEx3MT)(CEZCLProcess* pCLProcess, LONG ID, LONG Number, BSTR Name, BSTR Tag, short Enabled, short PriceLevel, BSTR Plate, BSTR IDNumber, BSTR ShortName, BSTR Password, short GradeType, short CardType, short LimitType, double Limit, short EntryType, DATE ExpirationDate, LONG ParentID);
typedef LONG (WINAPI *typeDeleteCardClientMT)( CEZCLProcess* pCLProcess , LONG ID ) ;

typedef LONG (WINAPI *typeAllStopMT)(CEZCLProcess* pCLProcess ) ;
typedef LONG (WINAPI *typeAllAuthoriseMT)(CEZCLProcess* pCLProcess ) ;
typedef LONG (WINAPI *typeAllReAuthoriseMT)(CEZCLProcess* pCLProcess ) ;
typedef LONG (WINAPI *typeAllStopIfIdleMT)(CEZCLProcess* pCLProcess ) ;
typedef LONG (WINAPI *typeReadAllTanksMT)(CEZCLProcess* pCLProcess ) ;
typedef LONG (WINAPI *typeGetAllPumpStatusesMT)(CEZCLProcess* pCLProcess ,  PBSTR pStates , PBSTR pCurrentHoses , PBSTR pDeliveriesCount ) ; 
typedef LONG (WINAPI *typeGetIniValueMT)(CEZCLProcess* pCLProcess ,  BSTR Section , BSTR Key , PBSTR pValue ) ; 
typedef LONG (WINAPI *typeSetIniValueMT)(CEZCLProcess* pCLProcess ,  BSTR Section , BSTR Key , BSTR Value ) ; 
typedef LONG (WINAPI *typeGetIniValueExMT)( CEZCLProcess* pCLProcess , BSTR FileName , BSTR Section , BSTR Key , PBSTR pValue ) ; 
typedef LONG (WINAPI *typeSetIniValueExMT)( CEZCLProcess* pCLProcess , BSTR FileName , BSTR Section , BSTR Key , BSTR Value ) ; 
typedef LONG (WINAPI *typeSetNextDeliveryIDMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeRemovePortMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeLicenseStatusMT)(CEZCLProcess* pCLProcess ) ;
typedef LONG (WINAPI *typeCheckSocketClosedMT)(CEZCLProcess* pCLProcess ,  LPARAM lParam ) ;

typedef LONG (WINAPI *typeGetCardTypeMT)( CEZCLProcess* pCLProcess , BSTR Tag , short* pTagType , LONG* pID, PBSTR pName, LONG* pNumber  ) ;
typedef LONG (WINAPI *typeFindCardMT)(CEZCLProcess* pCLProcess, BSTR Tag, short* pCardType, short* pTagType, LONG* pID, PBSTR pName, LONG* pNumber);


// *** new APIS
typedef LONG (WINAPI *typeGetNextPumpEventExMT)(CEZCLProcess* pCLProcess ,  LONG* pPumpID, short* pPumpNumber, short* pState, short* pReservedFor, LONG* pReservedBy, LONG* pHoseID ,
							    short* pHoseNumber,LONG* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume, 
							    double* pValue, short* pStackSize , PBSTR pPumpName , short* pPhysicalNumber , short* pSide , short* pAddress, 
								short* pPriceLevel1 , short* pPriceLevel2 , short* pType , LONG* pPortID , short* pAuthMode , short* pStackMode ,  short* pPrepayAllowed, 
								short* pPreauthAllowed ,  short* pPriceFormat , short* pValueFormat , short* pVolumeFormat  ) ;

typedef LONG (WINAPI *typeGetNextDeliveryEventExMT)(CEZCLProcess* pCLProcess ,  LONG* pDeliveryID , LONG* pPumpID, short* pPumpNumber, LONG* pHoseID, short* pHoseNumber , 
								    LONG* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel, double* pPrice, 
									double* pVolume, double* pValue, short* pDeliveryState , 
								    short* pDeliveryType, LONG* pLockedBy, LONG* pReservedBy, LONG* pAge , DATE* pCompletedDT , 
									LONG* pAttendantID, double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag) ;

typedef LONG (WINAPI *typeGetNextPumpEventEx2MT)( CEZCLProcess* pCLProcess , LONG* pPumpID, LONG* pPumpNumber, short* pState, short* pReservedFor, LONG* pReservedBy, LONG* pHoseID ,
							    LONG* pHoseNumber, LONG* pHosePhysicalNumber,LONG* pGradeID,LONG* pGradeNumber, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume, 
							    double* pValue, short* pStackSize , PBSTR pPumpName , LONG* pPhysicalNumber , short* pSide , short* pAddress, 
								short* pPriceLevel1 , short* pPriceLevel2 , short* pType , LONG* pPortID , short* pAuthMode , short* pStackMode ,  short* pPrepayAllowed, 
								short* pPreauthAllowed ,  short* pPriceFormat , short* pValueFormat , short* pVolumeFormat , __int64* pTag , 
							    LONG* pAttendantID , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							    LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag ) ;

typedef LONG (WINAPI *typeGetNextPumpEventEx3MT)( CEZCLProcess* pCLProcess , LONG* pPumpID, LONG* pPumpNumber, short* pState, short* pReservedFor, LONG* pReservedBy, LONG* pHoseID ,
							    LONG* pHoseNumber, LONG* pHosePhysicalNumber,LONG* pGradeID,LONG* pGradeNumber, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume, 
							    double* pValue, short* pStackSize , PBSTR pPumpName , LONG* pPhysicalNumber , short* pSide , short* pAddress, 
								short* pPriceLevel1 , short* pPriceLevel2 , short* pType , LONG* pPortID , short* pAuthMode , short* pStackMode ,  short* pPrepayAllowed, 
								short* pPreauthAllowed ,  short* pPriceFormat , short* pValueFormat , short* pVolumeFormat , __int64* pTag , 
							    LONG* pAttendantID , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							    LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag , 
								double* pCurFlowRate , double* pPeakFlowRate ) ;


typedef LONG (WINAPI *typeGetNextDeliveryEventEx2MT)( CEZCLProcess* pCLProcess , LONG* pDeliveryID , LONG* pPumpID, short* pPumpNumber, LONG* pHoseID, short* pHoseNumber , 
								     LONG* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel, double* pPrice, 
									 double* pVolume, double* pValue, short* pDeliveryState , 
								     short* pDeliveryType, LONG* pLockedBy, LONG* pReservedBy, LONG* pAge , DATE* pCompletedDT , 
									 LONG* pAttendantID, double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
									 double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
									 __int64* pTag , LONG* pDuration ) ;

typedef LONG (WINAPI *typeGetNextDeliveryEventEx3MT)( CEZCLProcess* pCLProcess , LONG* pDeliveryID , LONG* pPumpID, short* pPumpNumber, LONG* pHoseID, short* pHoseNumber , 
								     LONG* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel, double* pPrice, 
									 double* pVolume, double* pValue, short* pDeliveryState , 
								     short* pDeliveryType, LONG* pLockedBy, LONG* pReservedBy, LONG* pAge , DATE* pCompletedDT , 
									 LONG* pAttendantID, 
									 double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
									 double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
									 __int64* pTag , LONG* pDuration , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
									 LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag ) ;

typedef LONG (WINAPI *typeGetNextDeliveryEventEx4MT)( CEZCLProcess* pCLProcess , 
									    LONG* pDeliveryID, LONG* pHoseID ,LONG* pHoseNumber, LONG* pHosePhysicalNumber,
	  									LONG* pPumpID, LONG* pPumpNumber, PBSTR pPumpName,
										LONG* pTankID, LONG* pTankNumber, PBSTR pTankName,
										LONG* pGradeID , LONG* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
										short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT , LONG* pLockedBy, 
										LONG* pReservedBy , LONG* pAttendantID , LONG* pAge , DATE* pClearedDT , 
										double* pOldVolumeETot, double* pOldVolume2ETot, double* pOldValueETot , 
										double* pNewVolumeETot, double* pNewVolume2ETot, double* pNewValueETot , 
										__int64* pTag , LONG* pDuration , LONG* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
										LONG* pCardClientID , LONG* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag , double* pPeakFlowRate ) ;

typedef LONG (WINAPI *typeGetNextCardReadEventMT)( CEZCLProcess* pCLProcess , LONG* pCardReadID , LONG* pNumber, PBSTR pName , LONG* pPumpID , short* pType , LONG* pParentID , __int64* pTag , DATE* pTimeStamp ) ;
typedef LONG (WINAPI *typeGetNextDBHoseETotalsEventExMT)(CEZCLProcess* pCLProcess ,  LONG* pHoseID , double* pVolume , double* pValue , double* pVolumeETot , double* pValueETot , 
										 LONG* pHoseNumber , LONG* pHosePhysicalNumber , LONG* pPumpID , LONG* pPumpNumber , PBSTR pPumpName , 
										 LONG* pTankID , LONG* pTankNumber , PBSTR pTankName , LONG* pGradeID , PBSTR pGradeName ) ;
typedef LONG (WINAPI *typeGetNextDBTankStatusEventExMT)(CEZCLProcess* pCLProcess ,  LONG* pTankID , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, 
									    double* pGaugeTemperature , double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel , 
									    LONG* pTankNumber , PBSTR pTankName , LONG* pGradeID , PBSTR pGradeName , short*pType  , 
										double* pCapacity , double* pDiameter , LONG* pGaugeID , short* pProbeNo) ;

typedef LONG (WINAPI *typeGetNextDBTankStatusEventEx2MT)( CEZCLProcess* pCLProcess , LONG* pTankID , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, 
									    double* pGaugeTemperature , double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel , 
									    LONG* pTankNumber , PBSTR pTankName , LONG* pGradeID , PBSTR pGradeName , short*pType  , double* pCapacity , 
										double* pDiameter , LONG* pGaugeID , short* pProbeNo, short* pState , LONG* pAlarmsMask ) ;

typedef LONG (WINAPI *typeGetNextSerialPortEventMT)(CEZCLProcess* pCLProcess ,  LONG* pPortID , LONG* pZBID , short* pSlot , short* pResult , PBSTR pRxMsg ) ; 
typedef LONG (WINAPI *typeGetNextZBEventMT)(CEZCLProcess* pCLProcess ,  LONG* pPortID , LONG* pZBID , __int64* pZBAddress, short* pResult , short* pMsgType , PBSTR pRxMsg ) ; 
typedef LONG (WINAPI *typeGetNextUVEEventMT)(CEZCLProcess* pCLProcess ,  LONG* pPumpID , LONG* pPumpNumber , LONG* pHoseID , LONG* pHoseNumber , PBSTR pUVE ) ;
typedef LONG (WINAPI *typeGetZigBeeCountMT)(CEZCLProcess* pCLProcess ,  LONG* pCount ) ;
typedef LONG (WINAPI *typeGetZigBeeByNumberMT)(CEZCLProcess* pCLProcess ,  LONG Number , LONG* pID ) ;
typedef LONG (WINAPI *typeGetZigBeeByNameMT)(CEZCLProcess* pCLProcess ,  BSTR Name , LONG* pID ) ;
typedef LONG (WINAPI *typeGetZigBeeByOrdinalMT)(CEZCLProcess* pCLProcess ,  LONG Index , LONG* pID ) ;
typedef LONG (WINAPI *typeGetZigBeePropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , short* pDeviceType , PBSTR pSerialNumber , PBSTR pNodeIdentifier , LONG* pPortID ) ;
typedef LONG (WINAPI *typeSetZigBeePropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name , short DeviceType , BSTR SerialNumber , BSTR NodeIdentifier , LONG PortID ) ;
typedef LONG (WINAPI *typeDeleteZigBeeMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeGetHosePropertiesExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, LONG* pPumpID ,LONG* pTankID , LONG* pPhysicalNumber, 
		                      double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue ,
				              double* pMtrElecVolume , short* pUVEAntenna ) ;

typedef LONG (WINAPI *typeSetHosePropertiesExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number,LONG PumpID, LONG TankID , LONG PhysicalNumber, 
		                      double MtrTheoValue , double MtrTheoVolume ,double MtrElecValue ,
				              double MtrElecVolume , short UVEAntenna );

typedef LONG (WINAPI *typeSetHosePropertiesEx2MT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number,LONG PumpID, LONG TankID , LONG PhysicalNumber, 
		                      double MtrTheoValue , double MtrTheoVolume ,double MtrElecValue ,
				              double MtrElecVolume , short UVEAntenna , double Price1 , double Price2 , short Enabled ) ;

typedef LONG (WINAPI *typeGetHosePropertiesEx2MT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, LONG* pPumpID ,LONG* pTankID , LONG* pPhysicalNumber, 
		                      double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue ,
				              double* pMtrElecVolume , short* pUVEAntenna , double* pPrice1 , double* pPrice2 , short* pEnabled ) ;


typedef LONG (WINAPI *typeSetPumpPropertiesExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name, short PhysicalNumber, short Side, short Address, short PriceLevel1,
						        short PriceLevel2, short PriceDspFormat, short VolumeDspFormat, short ValueDspFormat, short Type, 
						        LONG PortID, LONG AttendantID, short AuthMode, short StackMode, short PrepayAllowed, short PreauthAllowed , 
								LONG SlotZigBeeID , LONG MuxSlotZigBeeID , short PriceControl , short HasPreset ) ;
typedef LONG (WINAPI *typeGetPumpPropertiesExMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName, short* pPhysicalNumber, short* pSide, short* pAddress, short* pPriceLevel1,
						      short* pPriceLevel2, short* pPriceDspFormat, short* pVolumeDspFormat, short* pValueDspFormat, short* pType, 
						      LONG* pPortID, LONG* pAttendantID, short* pAuthMode, short* pStackMode, short* pPrepayAllowed, short* pPreauthAllowed ,
							  LONG* pSlotZigBeeID , LONG* pMuxSlotZigBeeID , short* pPriceControl , short* pHasPreset) ;
typedef LONG (WINAPI *typeCTFReserveMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeCTFCancelMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeCTFAuthoriseMT)(CEZCLProcess* pCLProcess ,  LONG ID , short LimitType , double Value , double Value2 , short Hose , short PriceLevel , BSTR UVE , short UVEType , short UVETimeout, short IBMPulserTimeout, short StopDelay ) ;
typedef LONG (WINAPI *typeGetSerialNoMT)(CEZCLProcess* pCLProcess ,  LONG ID , PBSTR pSerialNo ) ; 
typedef LONG (WINAPI *typeGetDeviceDetailsMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG ZBID , PBSTR pSerialNo , PBSTR pBootVersion , PBSTR pFirmwareVersion ) ;
typedef LONG (WINAPI *typeResetDeviceMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG ZBID ) ;
typedef LONG (WINAPI *typeRequestVersionMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG ZBID ) ;
typedef LONG (WINAPI *typeZBRegisterInterestMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG ZBID ) ; 
typedef LONG (WINAPI *typeZBExceptionRegisterInterestMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeZBHeartBeatRegisterInterestMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeSerialPortSendMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG ZBID , short Slot , short Type , BSTR TxMsg ) ;
typedef LONG (WINAPI *typeSerialPortConfigMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG ZBID , short Slot , short COMPort , LONG BPS , short DataBits , short Parity , short StopBits , short ResponseMaxLen , short ResponseTimeout , short ResponseInterCharTimeout ) ;
typedef LONG (WINAPI *typeZBSendMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG ZBID, __int64 ZBAddress, short MsgType , BSTR TxMsg ) ; 
typedef LONG (WINAPI *typeGetDeviceDetailsMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG ZBID , PBSTR pSerialNo , PBSTR pBootVersion , PBSTR pFirmwareVersion ) ;
typedef LONG (WINAPI *typeSetZBCoordPanMT)(CEZCLProcess* pCLProcess ,  LONG ID , __int64 Pan ) ;
typedef LONG (WINAPI *typeGetZBCoordPanMT)(CEZCLProcess* pCLProcess ,  LONG ID ) ;
typedef LONG (WINAPI *typeReadUVEMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG ZBID , short Antenna ) ; 
typedef LONG (WINAPI *typeSetHoseETotalsMT)(CEZCLProcess* pCLProcess ,  LONG ID , double Volume , double Value ) ;
typedef LONG (WINAPI *typeGetNextZBStatusEventMT)(CEZCLProcess* pCLProcess , LONG* pPortID , LONG* pZBID , __int64* pZBAddress, short* pCondition , short* pCount , short* pStrength ) ;
typedef LONG (WINAPI *typeGetNextZBPanIDEventMT)(CEZCLProcess* pCLProcess , LONG* pPortID , __int64* pZBPanID ) ;
typedef LONG (WINAPI *typeGetNextZeroDeliveryEventMT)(CEZCLProcess* pCLProcess ,  LONG* pPumpID , LONG* pPumpNumber , LONG* pHoseID , LONG* pHoseNumber ) ;
typedef LONG (WINAPI *typeSetIOPinMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG ZBID , short Slot , short IOPin , short Value ) ;
typedef LONG (WINAPI *typeSetHosePricesMT)(CEZCLProcess* pCLProcess ,  LONG ID , short DurationType , short PriceType , double Price1 , double Price2 ) ;
typedef LONG (WINAPI *typeGetHosePricesMT)( CEZCLProcess* pCLProcess , LONG ID , short* pDurationType , short* pPriceType , double* pPrice1 , double* pPrice2 ) ;
typedef LONG (WINAPI *typeSetPumpDefaultPriceLevelMT)(CEZCLProcess* pCLProcess ,  LONG ID , short Level ) ;
typedef LONG (WINAPI *typeSetDateTimeMT)( CEZCLProcess* pCLProcess , DATE DateTime ) ;
typedef LONG (WINAPI *typeGetDateTimeMT)( CEZCLProcess* pCLProcess , DATE* pDateTime ) ;
typedef LONG (WINAPI *typeGetNextZBCmdEventMT)(CEZCLProcess* pCLProcess , LONG* pPortID , LONG* pZBID , __int64* pZBAddress, PBSTR pRxMsg ) ;
typedef LONG (WINAPI *typeGetNextZBRawEventMT)(CEZCLProcess* pCLProcess , LONG* pPortID , LONG* pZBID , __int64* pZBAddress, PBSTR pRxMsg ) ;
typedef LONG (WINAPI *typeGetNextZB2GStatusEventMT)( CEZCLProcess* pCLProcess , LONG* pPortID , __int64* pZBAddress, short* pLQI , short* pRSSI , __int64*  pParZBAddress, short* pZBChannel , short* pMemBlocks , short* pMemFree ) ;
typedef LONG (WINAPI *typeZBSendRawMT)(CEZCLProcess* pCLProcess ,  LONG ID , LONG ZBID , __int64 ZBAddress , BSTR TxMsg ) ;
typedef LONG (WINAPI *typeZBSendCmdMT)(CEZCLProcess* pCLProcess ,LONG ID , LONG ZBID , __int64 ZBAddress , BSTR TxMsg ) ;
typedef LONG (WINAPI *typeZBCmdRegisterInterestMT)(CEZCLProcess* pCLProcess , LONG ID , LONG ZBID ) ;
typedef LONG (WINAPI *typeZBRawRegisterInterestMT)(CEZCLProcess* pCLProcess , LONG ID , LONG ZBID ) ;
typedef LONG (WINAPI *typeGetZB2GConfigMT)(CEZCLProcess* pCLProcess , LONG ID , __int64* pPanID , LONG* pChannels , __int64* pKeyA , __int64* pKeyB ) ;
typedef LONG (WINAPI *typeScheduleBeepMT)( CEZCLProcess* pCLProcess , LONG ID , short Pitch1 , short Duration1 , short Pitch2 , short Duration2, short Pitch3 , short Duration3, short Pitch4 , short Duration4, short Pitch5 , short Duration5 ) ;
typedef LONG (WINAPI *typeFlashLEDSMT)( CEZCLProcess* pCLProcess , LONG ID , short Side , short PeriodMs , short Cycles ) ;

// Version 3 APIs 

typedef LONG (WINAPI *typeGetLogEventCountMT)( CEZCLProcess* pCLProcess , LONG* pCount , short DeviceType , LONG DeviceID , short EventLevel , short EventType ,LONG  ClearedBy ,LONG  AckedBy)  ;
typedef LONG (WINAPI *typeGetLogEventByOrdinalMT)( CEZCLProcess* pCLProcess , LONG Index , LONG* pID , short DeviceType , LONG DeviceID , short EventLevel , short EventType ,LONG  ClearedBy ,LONG  AckedBy) ;
typedef LONG (WINAPI *typeGetLogEventPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , short* pDeviceType , LONG* pDeviceID , LONG* pDeviceNumber ,	PBSTR pDeviceName , short* pEventLevel ,
									short* pEventType , PBSTR pEventDesc , DATE* pGeneratedDT , DATE* pClearedDT , LONG* pClearedBy , LONG* pAckedBy , double* pVolume ,
									double* pValue , double* pProductVolume , double* pProductLevel , double* pWaterLevel , double* pTemperature );
typedef LONG (WINAPI *typeSetLogEventPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , short DeviceType , LONG DeviceID , LONG DeviceNumber , BSTR DeviceName , short EventLevel ,
									short EventType , BSTR  EventDesc , DATE GeneratedDT , DATE ClearedDT , LONG  ClearedBy , LONG  AckedBy , double  Volume ,
									double  Value , double  ProductVolume ,	double  ProductLevel , double  WaterLevel , double  Temperature  );
typedef LONG (WINAPI *typeDeleteLogEventMT)( CEZCLProcess* pCLProcess , LONG ID ) ;
typedef LONG (WINAPI *typeGetNextLogEventEventMT)( CEZCLProcess* pCLProcess , LONG* pLogEventID , short* pDeviceType , LONG* pDeviceID , LONG* pDeviceNumber ,	PBSTR pDeviceName , short* pEventLevel ,
								     short* pEventType , PBSTR pEventDesc , DATE* pGeneratedDT , DATE* pClearedDT , LONG* pClearedBy , LONG* pAckedBy , double* pVolume ,
								     double* pValue , double* pProductVolume , double* pProductLevel , double* pWaterLevel , double* pTemperature) ;
typedef LONG (WINAPI *typeClearLogEventMT)( CEZCLProcess* pCLProcess , LONG ID , LONG ClientID ) ;
typedef LONG (WINAPI *typeAckLogEventMT)( CEZCLProcess* pCLProcess , LONG ID , LONG ClientID ) ;


typedef LONG (WINAPI *typeGetSensorsCountMT)( CEZCLProcess* pCLProcess , LONG* pCount ) ;
typedef LONG (WINAPI *typeGetSensorByNumberMT)( CEZCLProcess* pCLProcess , LONG Number , LONG* pID ) ;
typedef LONG (WINAPI *typeGetSensorByNameMT)( CEZCLProcess* pCLProcess , BSTR Name , LONG* pID ) ;
typedef LONG (WINAPI *typeGetSensorByOrdinalMT)( CEZCLProcess* pCLProcess , LONG Index , LONG* pID ) ;
typedef LONG (WINAPI *typeGetSensorPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG* pNumber, PBSTR pName , LONG* pPortID , short* pType , short* pAddress , short* pSensorNo )  ;
typedef LONG (WINAPI *typeSetSensorPropertiesMT)(CEZCLProcess* pCLProcess , LONG ID , LONG Number, BSTR Name , LONG PortID , short Type , short Address , short SensorNo )  ;
typedef LONG (WINAPI *typeSetSensorStatusMT)(CEZCLProcess* pCLProcess , LONG ID , short State , short IsResponding )  ;
typedef LONG (WINAPI *typeGetSensorStatusMT)(CEZCLProcess* pCLProcess , LONG ID , short* pState , short* pIsResponding) ; 
typedef LONG (WINAPI *typeDeleteSensorMT)( CEZCLProcess* pCLProcess , LONG ID ) ;

typedef LONG (WINAPI *typeSetLogPathMT)(CEZCLProcess* pCLProcess, BSTR Path);
typedef LONG (WINAPI *typeLogMT)(CEZCLProcess* pCLProcess, BSTR Text);
typedef LONG (WINAPI *typeSetClientTypeMT)( CEZCLProcess* pCLProcess, LONG ClientKey ) ; 
typedef LONG (WINAPI *typeGetNextSaleItemEventMT)(CEZCLProcess* pCLProcess,
									LONG* pSaleItemID, LONG* pProductID, LONG* pProductNumber, PBSTR pProductName, __int64* pProductTag, LONG* pProductGroup, PBSTR pProductGroupName, PBSTR pBarcode,
									LONG* pPumpID, LONG* pPumpNumber, PBSTR pPumpName,
									LONG* pAttendantID, LONG* pAttendantNumber, PBSTR pAttendantName, __int64* pAttendantTag,
									LONG* pCardClientID, LONG* pCardClientNumber, PBSTR pCardClientName, __int64* pCardClientTag,
									short* pPriceLevel, double* pPrice, double* pQuantity, DATE* pAddedDT, DATE* pClearedDT,
									LONG* pLockedBy, LONG* pClearedBy, short* pLoggedDB, short* pLoggedVolumetric,
									PBSTR pPlate, PBSTR pDriverID, PBSTR pExtTransactionID, PBSTR pAuthID, short* pAuthType);

typedef LONG (WINAPI *typeGetProductByNumberMT)(CEZCLProcess* pCLProcess, LONG Number, LONG* pID);
typedef LONG (WINAPI *typeMT)(CEZCLProcess* pCLProcess, BSTR Name, LONG* pID);
typedef LONG (WINAPI *typeGetProductPropertiesMT)(CEZCLProcess* pCLProcess, LONG ID, LONG* pNumber, PBSTR pName, PBSTR pTag, short* pEnabled, PBSTR pShortName, PBSTR pBarcode, double* pPrice1, double* pPrice2, LONG* pProductGroup);
typedef LONG (WINAPI *typeSetProductPropertiesMT)(CEZCLProcess* pCLProcess, LONG ID, LONG Number, BSTR Name, BSTR Tag, short Enabled, BSTR ShortName, BSTR Barcode, double Price1, double Price2, LONG ProductGroup);
typedef LONG (WINAPI *typeDeleteProductMT)(CEZCLProcess* pCLProcess, LONG ID);
typedef LONG (WINAPI *typeGetProductsCountMT)(CEZCLProcess* pCLProcess, LONG* pCount, LONG Number, BSTR Name, BSTR ShortName, BSTR Tag, BSTR Barcode, LONG ProductGroup);
typedef LONG (WINAPI *typeGetProductByOrdinalMT)(CEZCLProcess* pCLProcess, LONG Index, LONG* pID, LONG Number, BSTR Name, BSTR ShortName, BSTR Tag, BSTR Barcode, LONG ProductGroup);

typedef LONG (WINAPI *typeGetSaleItemPropertiesMT)(CEZCLProcess* pCLProcess, LONG ID, LONG* pProductID, LONG* pPumpID, LONG* pAttendantID, LONG* pCardClientID, short* pPriceLevel, double* pPrice,
	double* pQuantity, DATE* pAddedDT, DATE* pClearedDT, LONG* pLockedBy, LONG* pClearedBy, short* pLoggedDB, short* pLoggedVolumetric,
	PBSTR pPlate, PBSTR pDriverID, PBSTR pExtTransactionID, PBSTR pAuthID, short* pAuthType);
typedef LONG (WINAPI *typeSetSaleItemPropertiesMT)(CEZCLProcess* pCLProcess, LONG ID, LONG ProductID, LONG PumpID, LONG AttendantID, LONG CardClientID, short PriceLevel, double Price,
	double Quantity, DATE AddedDT, DATE ClearedDT, LONG LockedBy, LONG ClearedBy, short LoggedDB, short LoggedVolumetric,
	BSTR Plate, BSTR DriverID, BSTR ExtTransactionID, BSTR AuthID, short AuthType);
typedef LONG (WINAPI *typeDeleteSaleItemMT)(CEZCLProcess* pCLProcess, LONG ID);
typedef LONG (WINAPI *typeGetSaleItemsCountMT)(CEZCLProcess* pCLProcess, LONG* pCount, LONG ProductID, LONG PumpID, LONG AttendantID, LONG CardClientID, LONG LockedBy, LONG ClearedBy, short LoggedDB, short LoggedVolumetric);
typedef LONG (WINAPI *typeGetSaleItemByOrdinalMT)(CEZCLProcess* pCLProcess, LONG Index, LONG* pID, LONG ProductID, LONG PumpID, LONG AttendantID, LONG CardClientID, LONG LockedBy, LONG ClearedBy, short LoggedDB, short LoggedVolumetric);

typedef LONG (WINAPI *typeSaleItemLockMT)(CEZCLProcess* pCLProcess, LONG ID);
typedef LONG (WINAPI *typeSaleItemUnlockMT)(CEZCLProcess* pCLProcess, LONG ID);
typedef LONG (WINAPI *typeSaleItemClearMT)(CEZCLProcess* pCLProcess, LONG ID);
typedef LONG (WINAPI *typeSaleItemLockAndClearMT)(CEZCLProcess* pCLProcess, LONG ID);
typedef LONG (WINAPI *typeSaleItemAckDBLogMT)(CEZCLProcess* pCLProcess, LONG ID);
typedef LONG (WINAPI *typeSaleItemAckVolLogMT)(CEZCLProcess* pCLProcess, LONG ID);
typedef LONG (WINAPI *typeGetSaleItemSummaryMT)(CEZCLProcess* pCLProcess, LONG ID, LONG* pProductID, LONG* pProductNumber, PBSTR pProductName, __int64* pProductTag, LONG* pProductGroup, PBSTR pProductGroupName, PBSTR pBarcode,
	LONG* pPumpID, LONG* pPumpNumber, PBSTR pPumpName,
	LONG* pAttendantID, LONG* pAttendantNumber, PBSTR pAttendantName, __int64* pAttendantTag,
	LONG* pCardClientID, LONG* pCardClientNumber, PBSTR pCardClientName, __int64* pCardClientTag,
	short* pPriceLevel, double* pPrice, double* pQuantity, DATE* pAddedDT, DATE* pClearedDT,
	LONG* pLockedBy, LONG* pClearedBy, short* pLoggedDB, short* pLoggedVolumetric,
	PBSTR pPlate, PBSTR pDriverID, PBSTR pExtTransactionID, PBSTR pAuthID, short* pAuthType);

typedef LONG (WINAPI *typeGetPriceSignElementMT)(CEZCLProcess* pCLProcess, short Element , short* pElementType , LONG* pLinkID  , short* pDecimals , double* pPrice, short* pState , short* pOnTime, short* pOffTime ) ;
typedef LONG (WINAPI *typeSetPriceSignElementMT)(CEZCLProcess* pCLProcess, short Element , short ElementType , LONG LinkID , short Decimals  , double Price , short State , short OnTime, short OffTime );
typedef LONG (WINAPI *typeGetStappingTableDataMT)(CEZCLProcess* pCLProcess, LONG ID, double* pStepSize, double* pDiameter, double* pOffset, double* pCapacity, LONG* pAlarms);
typedef LONG (WINAPI *typeSetStappingTableDataMT)(CEZCLProcess* pCLProcess, LONG ID, double StepSize, double Diameter, double Offset, double Capacity, LONG Alarms);
typedef LONG (WINAPI *typeGetStappingTableElementMT)(CEZCLProcess* pCLProcess, LONG ID, LONG Element, short* pPasses, double* pHeight, double* pStartDelta, double* pCurDelta, double* pStartVolume, double* pCurVolume);
typedef LONG (WINAPI *typeSetStappingTableElementMT)(CEZCLProcess* pCLProcess, LONG ID, LONG Element, short Passes, double StartDelta, double CurDelta);


// not valid for CE
//typedef LONG (*typeIsValidMACLicense)( BSTR LicenseKey );

//-----------------------------------------------------------------------------

class CEZClient
{
public:
	CEZClient();

	CEZClient(char* dllpath);

	~CEZClient();

	bool isLoaded();

	void GetLastErrorText(DWORD erro, LPTSTR lpszBuffer, DWORD dwSize);
	char KBget();
	int  KBhit();

protected:
	bool	dllLoaded;
	HMODULE	dllHandle;
	void	Initializer();
	int		LoadAPIs(char* dllpath);

#if defined(__linux__)
	termios oldTerm;
#endif

//-----------------------------------------------------------------------------
public:  // Declaracao dos ponteiros de pontos de entrada
	typeDllVersion							DllVersion;
	typeServerVersion						ServerVersion;
	typeClientLogon							ClientLogon;
	typeClientLogonEx						ClientLogonEx;
	typeClientLogoff						ClientLogoff;
	typeClientStatus						ClientStatus;
	typeGetLicenseType						GetLicenseType;
	typeFireClientEvent						FireClientEvent;
	typeTestConnection						TestConnection;
	typeProcessEvents						ProcessEvents;
	typeGetEventsCount						GetEventsCount;
	typeGetNextEventType					GetNextEventType;
	typeDiscardNextEvent					DiscardNextEvent;
	typeGetNextPumpEvent					GetNextPumpEvent;
	typeGetNextDeliveryEvent				GetNextDeliveryEvent;
	typeGetNextServerEvent					GetNextServerEvent;
	typeGetNextClientEvent					GetNextClientEvent;
	typeGetNextDBLogEvent					GetNextDBLogEvent;
	typeGetNextDBLogDeliveryEvent			GetNextDBLogDeliveryEvent;
	typeGetNextDBClearDeliveryEvent			GetNextDBClearDeliveryEvent;
	typeGetNextDBStackDeliveryEvent			GetNextDBStackDeliveryEvent;
	typeGetNextDBHoseETotalsEvent			GetNextDBHoseETotalsEvent;
	typeGetNextDBTriggerEvent				GetNextDBTriggerEvent;
	typeGetNextDBAttendantLogonEvent		GetNextDBAttendantLogonEvent;
	typeGetNextDBAttendantLogoffEvent		GetNextDBAttendantLogoffEvent;
	typeGetNextDBTankStatusEvent			GetNextDBTankStatusEvent;
	typeGetPumpsCount						GetPumpsCount;
	typeGetPumpByNumber						GetPumpByNumber;
	typeGetPumpByName						GetPumpByName;
	typeGetPumpByOrdinal					GetPumpByOrdinal;
	typeGetPumpProperties					GetPumpProperties;
	typeSetPumpProperties					SetPumpProperties;
	typeDeletePump							DeletePump;
	typeGetPumpHosesCount					GetPumpHosesCount;
	typeGetPumpHoseByNumber					GetPumpHoseByNumber;
	typeGetPumpStatus						GetPumpStatus;
	typeGetPumpStatusEx						GetPumpStatusEx;
	typeGetPumpDeliveryProperties			GetPumpDeliveryProperties;
	typeGetPumpDeliveryPropertiesEx			GetPumpDeliveryPropertiesEx;
	typeGetPumpDeliveryPropertiesEx2		GetPumpDeliveryPropertiesEx2;
	typeGetPumpDeliveryPropertiesEx3		GetPumpDeliveryPropertiesEx3;
	typePrepayReserve						PrepayReserve;
	typePrepayCancel						PrepayCancel;
	typePrepayAuthorise						PrepayAuthorise;
	typePreauthReserve						PreauthReserve;
	typePreauthCancel						PreauthCancel;
	typePreauthAuthorise					PreauthAuthorise;
	typeLoadPreset							LoadPreset;
	typeLoadPresetWithPrice					LoadPresetWithPrice;
	typeTagAuthorise						TagAuthorise;
	typeAttendantAuthorise					AttendantAuthorise;
	typeAuthorise							Authorise;
	typeCancelAuthorise						CancelAuthorise;
	typeTempStop							TempStop;
	typeReAuthorise							ReAuthorise;
	typeTerminateDelivery					TerminateDelivery;
	typeStackCurrentDelivery				StackCurrentDelivery;
	typeGetDensity							GetDensity;
	typeEnablePump							EnablePump;
	typeDisablePump							DisablePump;
	typeGetHosesCount						GetHosesCount;
	typeGetHoseByOrdinal					GetHoseByOrdinal;
	typeGetHoseProperties					GetHoseProperties;
	typeSetHoseProperties					SetHoseProperties;
	typeGetHoseSummary						GetHoseSummary;
	typeGetHoseSummaryEx					GetHoseSummaryEx;
	typeDeleteHose							DeleteHose;
	typeGetDeliveriesCount					GetDeliveriesCount;
	typeGetDeliveryByOrdinal				GetDeliveryByOrdinal;
	typeGetAllDeliveriesCount				GetAllDeliveriesCount;
	typeGetAllDeliveryByOrdinal				GetAllDeliveryByOrdinal;
	typeAckDeliveryDBLog					AckDeliveryDBLog;
	typeGetDeliveryIDByOrdinalNotLogged		GetDeliveryIDByOrdinalNotLogged;
	typeGetDeliveriesCountNotLogged			GetDeliveriesCountNotLogged;
	typeAckDeliveryVolLog					AckDeliveryVolLog;
	typeGetDeliveryIDByOrdinalNotVolLogged	GetDeliveryIDByOrdinalNotVolLogged;
	typeGetDeliveriesCountNotVolLogged		GetDeliveriesCountNotVolLogged;
	typeGetDeliveryProperties				GetDeliveryProperties;
	typeGetDeliveryPropertiesEx				GetDeliveryPropertiesEx;
	typeGetDeliveryPropertiesEx2			GetDeliveryPropertiesEx2;
	typeGetDeliveryPropertiesEx3			GetDeliveryPropertiesEx3;
	typeSetDeliveryProperties				SetDeliveryProperties;
	typeSetDeliveryPropertiesEx				SetDeliveryPropertiesEx;
	typeSetDeliveryPropertiesEx2			SetDeliveryPropertiesEx2;
	typeSetDeliveryPropertiesEx3			SetDeliveryPropertiesEx3;
	typeGetDeliverySummary					GetDeliverySummary;
	typeGetDeliverySummaryEx				GetDeliverySummaryEx;
	typeGetDeliverySummaryEx2				GetDeliverySummaryEx2;
	typeLockDelivery						LockDelivery;
	typeUnlockDelivery						UnlockDelivery;
	typeClearDelivery						ClearDelivery;
	typeLockAndClearDelivery				LockAndClearDelivery;
	typeGetDuration							GetDuration;
	typeGetGradesCount						GetGradesCount;
	typeGetGradeByNumber					GetGradeByNumber;
	typeGetGradeByName						GetGradeByName;
	typeGetGradeByOrdinal					GetGradeByOrdinal;
	typeGetGradeProperties					GetGradeProperties;
	typeSetGradeProperties					SetGradeProperties;
	typeDeleteGrade							DeleteGrade;
	typeSetGradePrice						SetGradePrice;
	typeGetGradePrice						GetGradePrice;
	typeGetTanksCount						GetTanksCount;
	typeGetTankByNumber						GetTankByNumber;
	typeGetTankByName						GetTankByName;
	typeGetTankByOrdinal					GetTankByOrdinal;
	typeGetTankProperties					GetTankProperties;
	typeSetTankProperties					SetTankProperties;
	typeSetTankPropertiesEx                 SetTankPropertiesEx;
	typeGetTankSummary						GetTankSummary;
	typeTankDrop							TankDrop;
	typeDeleteTank							DeleteTank;
	typeGetPortsCount						GetPortsCount;
	typeGetPortByNumber						GetPortByNumber;
	typeGetPortByName						GetPortByName;
	typeGetPortByOrdinal					GetPortByOrdinal;
	typeGetPortProperties					GetPortProperties;
	typeSetPortProperties					SetPortProperties;
	typeGetAttendantsCount					GetAttendantsCount;
	typeGetAttendantByNumber				GetAttendantByNumber;
	typeGetAttendantByName					GetAttendantByName;
	typeGetAttendantByOrdinal				GetAttendantByOrdinal;
	typeGetAttendantProperties				GetAttendantProperties;
	typeSetAttendantProperties				SetAttendantProperties;
	typeGetAttendantPropertiesEx			GetAttendantPropertiesEx;
	typeSetAttendantPropertiesEx			SetAttendantPropertiesEx;
	typeDeleteAttendant						DeleteAttendant;
	typeAttendantLogon						AttendantLogon;
	typeAttendantLogoff						AttendantLogoff;
	typeGetCardReadsCount					GetCardReadsCount;
	typeGetCardReadByNumber					GetCardReadByNumber;
	typeGetCardReadByName					GetCardReadByName;
	typeGetCardReadByOrdinal				GetCardReadByOrdinal;
	typeGetCardReadProperties				GetCardReadProperties;
	typeSetCardReadProperties				SetCardReadProperties;
	typeDeleteCardRead						DeleteCardRead;
	typeGetCardClientsCount					GetCardClientsCount;
	typeGetCardClientByNumber				GetCardClientByNumber;
	typeGetCardClientByName					GetCardClientByName;
	typeGetCardClientByOrdinal				GetCardClientByOrdinal;
	typeGetCardClientProperties				GetCardClientProperties;
	typeSetCardClientProperties				SetCardClientProperties;
	typeDeleteCardClient					DeleteCardClient;
	typeAllStop								AllStop;
	typeAllAuthorise						AllAuthorise;
	typeAllReAuthorise						AllReAuthorise;
	typeAllStopIfIdle						AllStopIfIdle;
	typeReadAllTanks						ReadAllTanks;
	typeGetAllPumpStatuses					GetAllPumpStatuses;
	typeGetIniValue							GetIniValue;
	typeSetIniValue							SetIniValue;
	typeSetNextDeliveryID					SetNextDeliveryID;
	typeRemovePort							RemovePort;
	typeLicenseStatus						LicenseStatus;
	typeCheckSocketClosed					CheckSocketClosed;
	typeResultString						ResultString;
	typePumpStateString						PumpStateString;
	typeDeliveryStateString					DeliveryStateString;
	typeDeliveryTypeString					DeliveryTypeString;
	typeReserveTypeString					ReserveTypeString;
	typeGetNextPumpEventEx					GetNextPumpEventEx;
	typeGetNextPumpEventEx2					GetNextPumpEventEx2;
	typeGetNextDeliveryEventEx				GetNextDeliveryEventEx;
	typeGetNextDeliveryEventEx2				GetNextDeliveryEventEx2;
	typeGetNextDeliveryEventEx3				GetNextDeliveryEventEx3;
	typeGetNextCardReadEvent				GetNextCardReadEvent;
	typeGetNextDBHoseETotalsEventEx			GetNextDBHoseETotalsEventEx;
	typeGetNextDBTankStatusEventEx			GetNextDBTankStatusEventEx;
	typeGetZigBeeCount						GetZigBeeCount;
	typeGetZigBeeByNumber					GetZigBeeByNumber;
	typeGetZigBeeByName						GetZigBeeByName;
	typeGetZigBeeByOrdinal					GetZigBeeByOrdinal;
	typeGetZigBeeProperties					GetZigBeeProperties;
	typeSetZigBeeProperties					SetZigBeeProperties;
	typeDeleteZigBee						DeleteZigBee;
	typeGetHosePropertiesEx					GetHosePropertiesEx;
	typeSetHosePropertiesEx					SetHosePropertiesEx;
	typeGetHosePropertiesEx2				GetHosePropertiesEx2;
	typeSetHosePropertiesEx2				SetHosePropertiesEx2;
	typeSetPumpPropertiesEx					SetPumpPropertiesEx;
	typeGetPumpPropertiesEx					GetPumpPropertiesEx;
	typeGetSerialNo							GetSerialNo;
	typeGetDeviceDetails					GetDeviceDetails;
	typeResetDevice							ResetDevice;
	typeRequestVersion						RequestVersion;
	typeSetHoseETotals						SetHoseETotals;
	typeGetNextZBStatusEvent				GetNextZBStatusEvent;
	typeGetNextZBPanIDEvent					GetNextZBPanIDEvent;
	typeGetNextZeroDeliveryEvent			GetNextZeroDeliveryEvent;
	typeSetHosePrices						SetHosePrices;
	typeGetHosePrices						GetHosePrices;
	typeSetPumpDefaultPriceLevel			SetPumpDefaultPriceLevel;
	typeSetDateTime							SetDateTime;
	typeGetSensorsCount						GetSensorsCount;
	typeGetSensorByOrdinal                  GetSensorByOrdinal;
	typeGetSensorProperties                 GetSensorProperties;
	typeSetGradePropertiesEx                SetGradePropertiesEx;
	typeGetClientsCount                     GetClientsCount;
	typeGetPumpStatusEx2                    GetPumpStatusEx2;
	typeCheckforManagementFtn               CheckforManagementFtn;
	typeFireEvents                          FireEvents;
	typePaymentReserve                      PaymentReserve;
	typePaymentCancel                       PaymentCancel;
	typePaymentAuthorise                    PaymentAuthorise;
	typeDeliveriesCountFiltered             DeliveriesCountFiltered;
	typeGetDeliveryIDByOrdinalFiletered     GetDeliveryIDByOrdinalFiletered;
	typeGetDeliveryPropertiesEx4            GetDeliveryPropertiesEx4;
	typeSetDeliveryPropertiesEx4            SetDeliveryPropertiesEx4;
	typeGetPumpDeliveryPropertiesEx4        GetPumpDeliveryPropertiesEx4;
	typeGetDeliverySummaryEx3               GetDeliverySummaryEx3;
	typeGetDeliverySummaryEx4               GetDeliverySummaryEx4;
	typeSetDeliveryExt                      SetDeliveryExt;
	typeGetDeliveryExt                      GetDeliveryExt;
	typeGetGradePropertiesEx                GetGradePropertiesEx;
	typeGetTankPropertiesEx                 GetTankPropertiesEx;
	typeGetTankSummaryEx                    GetTankSummaryEx;
	typeGetAttendantPropertiesEx2           GetAttendantPropertiesEx2;
	typeSetAttendantPropertiesEx2           SetAttendantPropertiesEx2;
	typeGetAttendantState                   GetAttendantState;
	typeGetCardClientPropertiesEx           GetCardClientPropertiesEx;
	typeSetCardClientPropertiesEx           SetCardClientPropertiesEx;
	typeSetCardClientPropertiesEx2          SetCardClientPropertiesEx2;
	typeGetCardClientPropertiesEx2          GetCardClientPropertiesEx2;
	typeGetCardClientPropertiesEx3          GetCardClientPropertiesEx3;
	typeSetCardClientPropertiesEx3          SetCardClientPropertiesEx3;
	typeScheduleBeep                        ScheduleBeep;
	typeFlashLEDS                           FlashLEDS;
	typeGetIniValueEx                       GetIniValueEx;
	typeSetIniValueEx                       SetIniValueEx;
	typeGetCardType                         GetCardType;
	typeFindCard                            FindCard;
	typeGetNextPumpEventEx3                 GetNextPumpEventEx3;
	typeGetNextDeliveryEventEx4             GetNextDeliveryEventEx4;
	typeGetNextDBTankStatusEventEx2         GetNextDBTankStatusEventEx2;
	typeGetNextSerialPortEvent              GetNextSerialPortEvent;
	typeGetNextZBEvent                      GetNextZBEvent;
	typeGetNextUVEEvent                     GetNextUVEEvent;
	typeSetZBCoordPan                       SetZBCoordPan;
	typeGetZBCoordPan                       GetZBCoordPan;
	typeSetLineMode                         SetLineMode;
	typeGetDateTime                         GetDateTime;
	typeGetNextZB2GStatusEvent              GetNextZB2GStatusEvent;
	typeGetZB2GConfig                       GetZB2GConfig;
	typeGetLogEventCount                    GetLogEventCount;
	typeGetLogEventByOrdinal                GetLogEventByOrdinal;
	typeGetLogEventProperties               GetLogEventProperties;
	typeSetLogEventProperties               SetLogEventProperties;
	typeDeleteLogEvent                      DeleteLogEvent;
	typeGetNextLogEventEvent                GetNextLogEventEvent;
	typeClearLogEvent                       ClearLogEvent;
	typeAckLogEvent                         AckLogEvent;
	typeGetSensorByNumber                   GetSensorByNumber;
	typeGetSensorByName                     GetSensorByName;
	typeSetSensorProperties                 SetSensorProperties;
	typeSetSensorStatus                     SetSensorStatus;
	typeGetSensorStatus                     GetSensorStatus;
	typeDeleteSensor                        DeleteSensor;
	typeSetLogPath                          SetLogPath;
	typeLog                                 Log;
	typeSetClientType                       SetClientType;
	typeGetNextSaleItemEvent                GetNextSaleItemEvent;
	typeGetProductByNumber                  GetProductByNumber;
	typeGetProductByName                    GetProductByName;
	typeGetProductProperties                GetProductProperties;
	typeSetProductProperties                SetProductProperties;
	typeDeleteProduct                       DeleteProduct;
	typeGetProductsCount                    GetProductsCount;
	typeGetProductByOrdinal                 GetProductByOrdinal;
	typeDeleteSaleItem                      DeleteSaleItem;

	       //-------------M�todos MT --------------//


    typeServerVersionMT                     ServerVersionMT;
	typeClientLogonMT                       ClientLogonMT;
	typeClientLogoffMT                      ClientLogoffMT;
	typeClientLogonExMT                     ClientLogonExMT;
	typeClientStatusMT                      ClientStatusMT;
	typeGetLicenseTypeMT                    GetLicenseTypeMT;
	typeFireClientEventMT                   FireClientEventMT;
	typeCheckForManagementFtnMT             CheckForManagementFtnMT;
	typeTestConnectionMT                    TestConnectionMT;
	typeFireEventsMT                        FireEventsMT;
	typeProcessEventsMT                     ProcessEventsMT;
	typeGetEventsCountMT                    GetEventsCountMT;
	typeGetNextEventTypeMT                  GetNextEventTypeMT;               
	typeDiscardNextEventMT                  DiscardNextEventMT;
	typeGetNextPumpEventMT                  GetNextPumpEventMT;
	typeGetNextDeliveryEventMT              GetNextDeliveryEventMT;
	typeGetNextServerEventMT                GetNextServerEventMT;
	typeGetNextClientEventMT                GetNextClientEventMT;
	typeGetNextDBLogEventMT                 GetNextDBLogEventMT;
	typeGetNextDBLogDeliveryEventMT         GetNextDBLogDeliveryEventMT;
	typeGetNextDBClearDeliveryEventMT       GetNextDBClearDeliveryEventMT;
	typeGetNextDBStackDeliveryEventMT       GetNextDBStackDeliveryEventMT;
	typeGetNextDBHoseETotalsEventMT         GetNextDBHoseETotalsEventMT;
	typeGetNextDBTriggerEventMT             GetNextDBTriggerEventMT;
	typeGetNextDBAttendantLogonEventMT      GetNextDBAttendantLogonEventMT;
	typeGetNextDBAttendantLogoffEventMT     GetNextDBAttendantLogoffEventMT;
	typeGetNextDBTankStatusEventMT 			GetNextDBTankStatusEventMT;				        
	typeGetClientsCountMT                   GetClientsCountMT;
	typeGetPumpsCountMT                     GetPumpsCountMT;
	typeGetPumpByNumberMT                   GetPumpByNumberMT;
	typeGetPumpByNameMT                     GetPumpByNameMT;
	typeGetPumpByOrdinalMT                  GetPumpByOrdinalMT;
	typeGetPumpPropertiesMT		            GetPumpPropertiesMT;				     
	typeSetPumpPropertiesMT		            SetPumpPropertiesMT;				   
	typeDeletePumpMT                        DeletePumpMT;
	typeGetPumpHosesCountMT                 GetPumpHosesCountMT;
	typeGetPumpHoseByNumberMT               GetPumpHoseByNumberMT;
	typeGetPumpStatusMT                     GetPumpStatusMT;
							 
	typeGetPumpStatusExMT                   GetPumpStatusExMT;
							

	typeGetPumpStatusEx2MT                  GetPumpStatusEx2MT;
							

	typeGetPumpDeliveryPropertiesMT         GetPumpDeliveryPropertiesMT;
										
	typeGetPumpDeliveryPropertiesExMT       GetPumpDeliveryPropertiesExMT;
									
	typeGetPumpDeliveryPropertiesEx2MT      GetPumpDeliveryPropertiesEx2MT;
									       
	typeGetPumpDeliveryPropertiesEx3MT      GetPumpDeliveryPropertiesEx3MT;
											  
	typePrepayReserveMT                     PrepayReserveMT;
	typePrepayCancelMT                      PrepayCancelMT;
	typePrepayAuthoriseMT                   PrepayAuthoriseMT;
	typePreauthReserveMT                    PreauthReserveMT;
	typePreauthCancelMT                     PreauthCancelMT;
	typePreauthAuthoriseMT                  PreauthAuthoriseMT;
	typeLoadPresetMT                        LoadPresetMT;
	typeLoadPresetWithPriceMT               LoadPresetWithPriceMT;
	typeTagAuthoriseMT                      TagAuthoriseMT;
	typePaymentReserveMT                    PaymentReserveMT;
	typePaymentCancelMT                     PaymentCancelMT;
	typePaymentAuthoriseMT                  PaymentAuthoriseMT;
								 
	typeAttendantAuthoriseMT                AttendantAuthoriseMT;
	typeAuthoriseMT                         AuthoriseMT;
	typeCancelAuthoriseMT                   CancelAuthoriseMT;
	typeTempStopMT                          TempStopMT;
	typeReAuthoriseMT                       ReAuthoriseMT;
	typeTerminateDeliveryMT                 TerminateDeliveryMT;
	typeStackCurrentDeliveryMT              StackCurrentDeliveryMT;
	typeGetDensityMT                        GetDensityMT;
	typeEnablePumpMT                        EnablePumpMT;
	typeDisablePumpMT                       DisablePumpMT;
	typeGetHosesCountMT                     GetHosesCountMT;
	typeGetHoseByOrdinalMT                  GetHoseByOrdinalMT;
	typeGetHosePropertiesMT                 GetHosePropertiesMT;
			                      
	typeSetHosePropertiesMT                 SetHosePropertiesMT;
			                     
	typeGetHoseSummaryMT                    GetHoseSummaryMT;
								
	typeGetHoseSummaryExMT                  GetHoseSummaryExMT;
								
	typeDeleteHoseMT                        DeleteHoseMT;
	typeGetDeliveriesCountMT                GetDeliveriesCountMT;
	typeGetDeliveryByOrdinalMT              GetDeliveryByOrdinalMT;
	typeGetAllDeliveriesCountMT             GetAllDeliveriesCountMT;
	typeGetAllDeliveryByOrdinalMT           GetAllDeliveryByOrdinalMT;

	typeAckDeliveryDBLogMT                  AckDeliveryDBLogMT;
	typeGetDeliveryIDByOrdinalNotLoggedMT   GetDeliveryIDByOrdinalNotLoggedMT;
	typeGetDeliveriesCountNotLoggedMT       GetDeliveriesCountNotLoggedMT;

	typeDeliveriesCountFilteredMT           DeliveriesCountFilteredMT;
	typeGetDeliveryIDByOrdinalFileteredMT   GetDeliveryIDByOrdinalFileteredMT;

	typeAckDeliveryVolLogMT                 AckDeliveryVolLogMT;
	typeGetDeliveryIDByOrdinalNotVolLoggedMT GetDeliveryIDByOrdinalNotVolLoggedMT;
	typeGetDeliveriesCountNotVolLoggedMT    GetDeliveriesCountNotVolLoggedMT;

	typeGetDeliveryPropertiesMT             GetDeliveryPropertiesMT;
									   
	typeGetDeliveryPropertiesExMT           GetDeliveryPropertiesExMT;
			                  
	typeGetDeliveryPropertiesEx2MT          GetDeliveryPropertiesEx2MT;
											
	typeGetDeliveryPropertiesEx3MT          GetDeliveryPropertiesEx3MT;
											
	typeGetDeliveryPropertiesEx4MT          GetDeliveryPropertiesEx4MT;
											
 
	typeSetDeliveryPropertiesEx4MT          SetDeliveryPropertiesEx4MT;
									   
	typeGetPumpDeliveryPropertiesEx4MT      GetPumpDeliveryPropertiesEx4MT;
										
	typeSetDeliveryPropertiesMT             SetDeliveryPropertiesMT;
									  
	typeSetDeliveryPropertiesExMT           SetDeliveryPropertiesExMT;
									 
	typeSetDeliveryPropertiesEx2MT          SetDeliveryPropertiesEx2MT;
									 
	typeSetDeliveryPropertiesEx3MT          SetDeliveryPropertiesEx3MT;
									  
	typeGetDeliverySummaryMT                GetDeliverySummaryMT;
		  							
	typeGetDeliverySummaryExMT              GetDeliverySummaryExMT;
		  							
	typeGetDeliverySummaryEx2MT             GetDeliverySummaryEx2MT;
		  							
	typeGetDeliverySummaryEx3MT             GetDeliverySummaryEx3MT;
		  							
	typeGetDeliverySummaryEx4MT             GetDeliverySummaryEx4MT;
									
	typeLockDeliveryMT                      LockDeliveryMT;
	typeUnlockDeliveryMT                    UnlockDeliveryMT;
	typeClearDeliveryMT                     ClearDeliveryMT;
	typeLockAndClearDeliveryMT              LockAndClearDeliveryMT;
	typeGetDurationMT                       GetDurationMT;
	typeSetDeliveryExtMT                    SetDeliveryExtMT;
	typeGetDeliveryExtMT                    GetDeliveryExtMT;
	typeGetGradesCountMT                    GetGradesCountMT;
	typeGetGradeByNumberMT                  GetGradeByNumberMT;
	typeGetGradeByNameMT                    GetGradeByNameMT;
	typeGetGradeByOrdinalMT                 GetGradeByOrdinalMT;
	typeGetGradePropertiesMT                GetGradePropertiesMT;
	typeSetGradePropertiesMT                SetGradePropertiesMT;
	typeGetGradePropertiesExMT              GetGradePropertiesExMT;
	typeSetGradePropertiesExMT              SetGradePropertiesExMT;
	typeDeleteGradeMT                       DeleteGradeMT;
	typeSetGradePriceMT                     SetGradePriceMT;
	typeGetGradePriceMT                     GetGradePriceMT;
	typeGetTanksCountMT                     GetTanksCountMT;
	typeGetTankByNumberMT                   GetTankByNumberMT;
	typeGetTankByNameMT                     GetTankByNameMT;
	typeGetTankByOrdinalMT                  GetTankByOrdinalMT;

	typeGetTankPropertiesMT                 GetTankPropertiesMT;
								  
	typeSetTankPropertiesMT                 SetTankPropertiesMT;
			                     
	typeGetTankPropertiesExMT               GetTankPropertiesExMT;
								
	typeSetTankPropertiesExMT               SetTankPropertiesExMT;
			                     

	typeGetTankSummaryMT                    GetTankSummaryMT;
							 

	typeGetTankSummaryExMT                  GetTankSummaryExMT;
							  
	typeTankDropMT                          TankDropMT;
	typeDeleteTankMT                        DeleteTankMT;
	typeGetPortsCountMT                     GetPortsCountMT;
	typeGetPortByNumberMT                   GetPortByNumberMT;
	typeGetPortByNameMT                     GetPortByNameMT;
	typeGetPortByOrdinalMT                  GetPortByOrdinalMT;
	typeGetPortPropertiesMT                 GetPortPropertiesMT;
	typeSetPortPropertiesMT                 SetPortPropertiesMT;
	typeDeletePortMT                        DeletePortMT;
	typeGetAttendantsCountMT                GetAttendantsCountMT;
	typeGetAttendantByNumberMT              GetAttendantByNumberMT;
	typeGetAttendantByNameMT                GetAttendantByNameMT;
	typeGetAttendantByOrdinalMT             GetAttendantByOrdinalMT;
	typeGetAttendantPropertiesMT            GetAttendantPropertiesMT;
	typeSetAttendantPropertiesMT            SetAttendantPropertiesMT;
	typeSetAttendantPropertiesExMT          SetAttendantPropertiesExMT;
	typeGetAttendantPropertiesExMT          GetAttendantPropertiesExMT;
	typeGetAttendantPropertiesEx2MT         GetAttendantPropertiesEx2MT;
	typeSetAttendantPropertiesEx2MT         SetAttendantPropertiesEx2MT;

	typeGetAttendantStateMT                 GetAttendantStateMT;
	typeDeleteAttendantMT                   DeleteAttendantMT;
	typeAttendantLogonMT                    AttendantLogonMT;
	typeAttendantLogoffMT                   AttendantLogoffMT;

	typeGetCardReadsCountMT                 GetCardReadsCountMT;
	typeGetCardReadByNumberMT               GetCardReadByNumberMT;
	typeGetCardReadByNameMT                 GetCardReadByNameMT;
	typeGetCardReadByOrdinalMT              GetCardReadByOrdinalMT;
	typeGetCardReadPropertiesMT             GetCardReadPropertiesMT;
	typeSetCardReadPropertiesMT             SetCardReadPropertiesMT;
	typeDeleteCardReadMT                    DeleteCardReadMT;
	typeGetCardClientsCountMT               GetCardClientsCountMT;
	typeGetCardClientByNumberMT             GetCardClientByNumberMT;
	typeGetCardClientByNameMT               GetCardClientByNameMT;
	typeGetCardClientByOrdinalMT            GetCardClientByOrdinalMT;
	typeGetCardClientPropertiesMT           GetCardClientPropertiesMT;
	typeSetCardClientPropertiesMT           SetCardClientPropertiesMT;
	typeSetCardClientPropertiesExMT         SetCardClientPropertiesExMT;
	typeGetCardClientPropertiesExMT         GetCardClientPropertiesExMT;
	typeSetCardClientPropertiesEx2MT        SetCardClientPropertiesEx2MT;
	typeGetCardClientPropertiesEx2MT        GetCardClientPropertiesEx2MT;
	typeGetCardClientPropertiesEx3MT        GetCardClientPropertiesEx3MT;
	typeSetCardClientPropertiesEx3MT        SetCardClientPropertiesEx3MT;
	typeDeleteCardClientMT                  DeleteCardClientMT;

	typeAllStopMT                           AllStopMT;
	typeAllAuthoriseMT                      AllAuthoriseMT;
	typeAllReAuthoriseMT                    AllReAuthoriseMT;
	typeAllStopIfIdleMT                     AllStopIfIdleMT;
	typeReadAllTanksMT                      ReadAllTanksMT;
	typeGetAllPumpStatusesMT                GetAllPumpStatusesMT;
	typeGetIniValueMT                       GetIniValueMT;
	typeSetIniValueMT                       SetIniValueMT;
	typeGetIniValueExMT                     GetIniValueExMT;
	typeSetIniValueExMT                     SetIniValueExMT;
	typeSetNextDeliveryIDMT                 SetNextDeliveryIDMT;
	typeRemovePortMT                        RemovePortMT;
	typeLicenseStatusMT                     LicenseStatusMT;
	typeCheckSocketClosedMT                 CheckSocketClosedMT;

	typeGetCardTypeMT                       GetCardTypeMT;
	typeFindCardMT                          FindCardMT;


	// *** new APIS
	typeGetNextPumpEventExMT                GetNextPumpEventExMT;            
								   

	typeGetNextDeliveryEventExMT            GetNextDeliveryEventExMT;
									

	typeGetNextPumpEventEx2MT               GetNextPumpEventEx2MT;
								   

	typeGetNextPumpEventEx3MT               GetNextPumpEventEx3MT;
								    


	typeGetNextDeliveryEventEx2MT           GetNextDeliveryEventEx2MT;

	typeGetNextDeliveryEventEx3MT           GetNextDeliveryEventEx3MT;
									   
	typeGetNextDeliveryEventEx4MT           GetNextDeliveryEventEx4MT;
										   
	typeGetNextCardReadEventMT              GetNextCardReadEventMT;
	typeGetNextDBHoseETotalsEventExMT       GetNextDBHoseETotalsEventExMT;
											
	typeGetNextDBTankStatusEventExMT        GetNextDBTankStatusEventExMT;
										   
	typeGetNextDBTankStatusEventEx2MT       GetNextDBTankStatusEventEx2MT;
										  
	typeGetNextSerialPortEventMT            GetNextSerialPortEventMT;
	typeGetNextZBEventMT                    GetNextZBEventMT;
	typeGetNextUVEEventMT                   GetNextUVEEventMT;
	typeGetZigBeeCountMT                    GetZigBeeCountMT;
	typeGetZigBeeByNumberMT                 GetZigBeeByNumberMT;
	typeGetZigBeeByNameMT                   GetZigBeeByNameMT;
	typeGetZigBeeByOrdinalMT                GetZigBeeByOrdinalMT;
	typeGetZigBeePropertiesMT               GetZigBeePropertiesMT;
	typeSetZigBeePropertiesMT               SetZigBeePropertiesMT;
	typeDeleteZigBeeMT                      DeleteZigBeeMT;
	typeGetHosePropertiesExMT               GetHosePropertiesExMT;
			                      
	typeSetHosePropertiesExMT               SetHosePropertiesExMT;
			                     
	typeSetHosePropertiesEx2MT              SetHosePropertiesEx2MT;
			                    
	typeGetHosePropertiesEx2MT              GetHosePropertiesEx2MT;
			                      

	typeSetPumpPropertiesExMT               SetPumpPropertiesExMT;
							        
	typeGetPumpPropertiesExMT               GetPumpPropertiesExMT;
							       
	typeCTFReserveMT                        CTFReserveMT;
	typeCTFCancelMT                         CTFCancelMT;
	typeCTFAuthoriseMT                      CTFAuthoriseMT;
	typeGetSerialNoMT                       GetSerialNoMT;
	typeGetDeviceDetailsMT                  GetDeviceDetailsMT;
	typeResetDeviceMT                       ResetDeviceMT;
	typeRequestVersionMT                    RequestVersionMT;
	typeZBRegisterInterestMT                ZBRegisterInterestMT;
	typeZBExceptionRegisterInterestMT       ZBExceptionRegisterInterestMT;
	typeZBHeartBeatRegisterInterestMT       ZBHeartBeatRegisterInterestMT;
	typeSerialPortSendMT                    SerialPortSendMT;
	typeSerialPortConfigMT                  SerialPortConfigMT;
	typeZBSendMT                            ZBSendMT;
	//typeGetDeviceDetailsMT                  GetDeviceDetailsMT;
	typeSetZBCoordPanMT                     SetZBCoordPanMT;
	typeGetZBCoordPanMT                     GetZBCoordPanMT;
	typeReadUVEMT                           ReadUVEMT;
	typeSetHoseETotalsMT                    SetHoseETotalsMT;
	typeGetNextZBStatusEventMT              GetNextZBStatusEventMT;
	typeGetNextZBPanIDEventMT               GetNextZBPanIDEventMT;            
	typeGetNextZeroDeliveryEventMT          GetNextZeroDeliveryEventMT;
	typeSetIOPinMT                          SetIOPinMT;
	typeSetHosePricesMT                     SetHosePricesMT;
	typeGetHosePricesMT                     GetHosePricesMT;
	typeSetPumpDefaultPriceLevelMT          SetPumpDefaultPriceLevelMT;
	typeSetDateTimeMT                       SetDateTimeMT;
	typeGetDateTimeMT                       GetDateTimeMT;
	typeGetNextZBCmdEventMT                 GetNextZBCmdEventMT;
	typeGetNextZBRawEventMT                 GetNextZBRawEventMT;
	typeGetNextZB2GStatusEventMT            GetNextZB2GStatusEventMT;
	typeZBSendRawMT                         ZBSendRawMT;
	typeZBSendCmdMT                         ZBSendCmdMT;
	typeZBCmdRegisterInterestMT             ZBCmdRegisterInterestMT;
	typeZBRawRegisterInterestMT             ZBRawRegisterInterestMT;
	typeGetZB2GConfigMT                     GetZB2GConfigMT;
	typeScheduleBeepMT                      ScheduleBeepMT;
	typeFlashLEDSMT                         FlashLEDSMT;

	// Version 3 APIs 

	typeGetLogEventCountMT                  GetLogEventCountMT;
	typeGetLogEventByOrdinalMT              GetLogEventByOrdinalMT;
	typeGetLogEventPropertiesMT             GetLogEventPropertiesMT;
									
	typeSetLogEventPropertiesMT             SetLogEventPropertiesMT;
										
	typeDeleteLogEventMT                    DeleteLogEventMT;
	typeGetNextLogEventEventMT              GetNextLogEventEventMT;
									  
	typeClearLogEventMT                     ClearLogEventMT;
	typeAckLogEventMT                       AckLogEventMT;


	typeGetSensorsCountMT                   GetSensorsCountMT;
	typeGetSensorByNumberMT                 GetSensorByNumberMT;
	typeGetSensorByNameMT                   GetSensorByNameMT;
	typeGetSensorByOrdinalMT                GetSensorByOrdinalMT;
	typeGetSensorPropertiesMT               GetSensorPropertiesMT;
	typeSetSensorPropertiesMT               SetSensorPropertiesMT;
	typeSetSensorStatusMT                   SetSensorStatusMT;
	typeGetSensorStatusMT                   GetSensorStatusMT;
	typeDeleteSensorMT                      DeleteSensorMT;

	typeSetLogPathMT                        SetLogPathMT;
	typeLogMT                               LogMT;
	typeSetClientTypeMT                     SetClientTypeMT;
	typeGetNextSaleItemEventMT              GetNextSaleItemEventMT;
										

	typeGetProductByNumberMT                GetProductByNumberMT;
	typeMT                                  MT;
	typeGetProductPropertiesMT              GetProductPropertiesMT;
	typeSetProductPropertiesMT              SetProductPropertiesMT;
	typeDeleteProductMT                     DeleteProductMT;
	typeGetProductsCountMT                  GetProductsCountMT;
	typeGetProductByOrdinalMT               GetProductByOrdinalMT ;

	typeGetSaleItemPropertiesMT             GetSaleItemPropertiesMT;
		
	typeSetSaleItemPropertiesMT             SetSaleItemPropertiesMT;
		
	typeDeleteSaleItemMT                    DeleteSaleItemMT;
	typeGetSaleItemsCountMT                 GetSaleItemsCountMT;
	typeGetSaleItemByOrdinalMT              GetSaleItemByOrdinalMT;

	typeSaleItemLockMT                      SaleItemLockMT;
	typeSaleItemUnlockMT                    SaleItemUnlockMT;
	typeSaleItemClearMT                     SaleItemClearMT;
	typeSaleItemLockAndClearMT              SaleItemLockAndClearMT;
	typeSaleItemAckDBLogMT                  SaleItemAckDBLogMT;
	typeSaleItemAckVolLogMT                 SaleItemAckVolLogMT;
	typeGetSaleItemSummaryMT                GetSaleItemSummaryMT;

	typeGetPriceSignElementMT               GetPriceSignElementMT;
	typeSetPriceSignElementMT               SetPriceSignElementMT;
	typeGetStappingTableDataMT              GetStappingTableDataMT;
	typeSetStappingTableDataMT              SetStappingTableDataMT;
	typeGetStappingTableElementMT           GetStappingTableElementMT;
	typeSetStappingTableElementMT           SetStappingTableElementMT;


};

//-----------------------------------------------------------------------------
#endif // __EZ_CLIENT_INTERFACE__