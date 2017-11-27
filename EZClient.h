//-----------------------------------------------------------------------------
//
//  Empresa     :  EzTech Tecnologia e Automação Ltda
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

typedef time_t					DATE ;
typedef unsigned char			BYTE ;
typedef long long 				__int64 ;
typedef unsigned long long  	__uint64 ;
typedef wchar_t					BSTR ;
typedef wchar_t*				PBSTR ;
typedef wchar_t					WCHAR ;
typedef short					SHORT ;
typedef unsigned short			USHORT ;
typedef long					LONG ;
typedef unsigned long       	ULONG ;
typedef unsigned long       	LPARAM ;
typedef unsigned long			DWORD ;
typedef int						SOCKET ;
typedef void*					HANDLE ;
typedef HANDLE					HWND ;
typedef HANDLE					HMODULE ;
typedef HANDLE					HINSTANCE ;
typedef struct sockaddr			SOCKADDR ;
typedef void*					PVOID;
#define INVALID_HANDLE_VALUE	((HANDLE)(-1))
#define INVALID_SOCKET  		(SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#define Sleep( s )				usleep( ( s ) * 1000 )
#define FALSE   				0
#define TRUE    				1

// OVJ - 31/10/2012
#define INT64  __int64

#define WINAPI
#define MAX_PATH 260

#define stricmp strcasecmp

#define LPTSTR char*

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
typedef long (WINAPI *typeDllVersion)( PBSTR pName );
typedef long (WINAPI *typeServerVersion)( PBSTR pName );
typedef long (WINAPI *typeClientLogon)( long ClientID , short ClientType , HANDLE Event , HWND hWnd, unsigned int wMsg);
typedef long (WINAPI *typeClientLogonEx)( long ClientID , short ClientType , BSTR ServerName , unsigned short CallPortNo , unsigned short EventsPortNo , long CallTimeout, HANDLE Event , HWND hWnd, unsigned int wMsg);
typedef long (WINAPI *typeClientLogoff)();
typedef long (WINAPI *typeClientStatus)( short* pPumpsReserved , short* pdeliveriesLocked );
typedef long (WINAPI *typeGetLicenseType)( short* pLicenseType );
typedef long (WINAPI *typeFireClientEvent)( long EventID , BSTR EventStr );
typedef long (WINAPI *typeTestConnection)();
typedef long (WINAPI *typeProcessEvents)();
typedef long (WINAPI *typeGetEventsCount)( long* pCount );
typedef long (WINAPI *typeGetNextEventType)( short* pType );
typedef long (WINAPI *typeDiscardNextEvent)();
typedef long (WINAPI *typeGetNextPumpEvent)( long* pPumpID, short* pPumpNumber, short* pState, short* pReservedFor, long* pReservedBy, long* pHoseID ,
							   short* pHoseNumber, long* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume,
							   double* pValue, short* pStackSize );
typedef long (WINAPI *typeGetNextDeliveryEvent)( long* pDeliveryID , long* pPumpID, short* pPumpNumber, long* pHoseID, short* pHoseNumber ,
								long* pGradeID, PBSTR pGradeName ,PBSTR pShortGradeName, short* pPriceLevel, double* pPrice, double* pVolume, double* pValue,
								short* pDeliveryState , short* pDeliveryType, long* pLockedBy, long* pReservedBy, long* pAge , DATE* pCompletedDT , long* pAttendantID );
typedef long (WINAPI *typeGetNextServerEvent)( long* pEventID, PBSTR pEventText );
typedef long (WINAPI *typeGetNextClientEvent)( long* pClientID, long* pEventID, PBSTR pEventText );
typedef long (WINAPI *typeGetNextDBLogEvent)( long* pEventType , long* pDeviceID , DATE* pEventDT , PBSTR pEventText );
typedef long (WINAPI *typeGetNextDBLogDeliveryEvent)( long* pDeliveryID, long* pHoseID, short* pDeliveryState, short* pDeliveryType, double* pVolume, short* pPriceLevel,
							 double* pPrice, double* pValue, double* pVolume2, long* pReservedBy , long* pAttendantID, DATE* pDeliveryDT );
typedef long (WINAPI *typeGetNextDBClearDeliveryEvent)( long* pDeliveryID, short* pDeliveryType, long* pClearedBY, DATE* pClearedDT, long* pAttendantID );
typedef long (WINAPI *typeGetNextDBStackDeliveryEvent)( long* pDeliveryID );
typedef long (WINAPI *typeGetNextDBHoseETotalsEvent)( long* pHoseID , double* pVolume , double* pValue , double* pVolumeETot , double* pValueETot );
typedef long (WINAPI *typeGetNextDBTriggerEvent)( long* pTableID ,long* pRowID );
typedef long (WINAPI *typeGetNextDBAttendantLogonEvent)( long* pAttendantID ,long* pPumpID );
typedef long (WINAPI *typeGetNextDBAttendantLogoffEvent)( long* pAttendantID );
typedef long (WINAPI *typeGetNextDBTankStatusEvent)( long* pTankID , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature ,
							          double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel );
typedef long (WINAPI *typeGetPumpsCount)( long* pCount );
typedef long (WINAPI *typeGetPumpByNumber)( long Number , long* pID );
typedef long (WINAPI *typeGetPumpByName)( BSTR Name , long* pID );
typedef long (WINAPI *typeGetPumpByOrdinal)( long Index , long* pID );
typedef long (WINAPI *typeGetPumpProperties)(long ID , long* pNumber, PBSTR pName, short* pPhysicalNumber, short* pSide, short* pAddress, short* pPriceLevel1,
						      short* pPriceLevel2, short* pPriceDspFormat, short* pVolumeDspFormat, short* pValueDspFormat, short* pType,
						      long* pPortID, long* pAttendantID, short* pAuthMode, short* pStackMode, short* pPrepayAllowed, short* pPreauthAllowed );
typedef long (WINAPI *typeSetPumpProperties)(long ID , long Number, BSTR Name, short PhysicalNumber, short Side, short Address, short PriceLevel1,
						      short PriceLevel2, short PriceDspFormat, short VolumeDspFormat, short ValueDspFormat, short Type,
						      long PortID, long AttendantID, short AuthMode, short StackMode, short PrepayAllowed, short PreauthAllowed );
typedef long (WINAPI *typeDeletePump)( long ID );
typedef long (WINAPI *typeGetPumpHosesCount)( long ID , long* pCount );
typedef long (WINAPI *typeGetPumpHoseByNumber)( long ID , long Number , long* pHoseID );
typedef long (WINAPI *typeGetPumpStatus)( long ID , short* pState, short* pReservedFor, long* pReservedBy, long* pHoseID, short* pHoseNumber ,
						   long* pGradeID, PBSTR pGradeName ,PBSTR pShortGradeName, short* pPriceLevel , double* pPrice , double* pVolume , double* pValue ,
						   short* pStackSize );

typedef long (WINAPI *typeGetPumpStatusEx)( long ID , long* pPumpNumber, PBSTR pPumpName, long* pPhysicalNumber, short* pState, short* pReservedFor, long* pReservedBy, long* pHoseID, long* pHoseNumber , long* pHosePhysicalNumber , long* pGradeID ,
					   long* pGradeNumber , PBSTR pGradeName, PBSTR pShortGradeName, short* pPriceLevel , double* pPrice , double* pVolume , double* pValue ,
					   short* pStackSize , __int64* pTag ,
					   long* pAttendantID , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
					   long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag );

typedef long (WINAPI *typeGetPumpDeliveryProperties)( long ID , short Index , long* pDeliveryID , short* pType , short* pState, long* pHoseID,
									   short* pHoseNum, long* pGradeID , PBSTR pGradeName ,PBSTR pShortGradeName, short* pPriceLevel, double* pPrice , double* pVolume ,
									   double* pValue , long* pLockedBy , long* pReservedBy , long* pAge , DATE* pCompletedDT , long* pAttendantID  );
typedef long (WINAPI *typeGetPumpDeliveryPropertiesEx)( long ID , short Index , long* pDeliveryID , short* pType , short* pState, long* pHoseID, short* pHoseNum, long* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName ,
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , long* pLockedBy ,
									    long* pReservedBy , long* pAge , DATE* pCompletedDT , long* pAttendantID , double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag );
typedef long (WINAPI *typeGetPumpDeliveryPropertiesEx2)( long ID , short Index , long* pDeliveryID , short* pType , short* pState, long* pHoseID, short* pHoseNum, long* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName ,
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , long* pLockedBy ,
									    long* pReservedBy , long* pAge , DATE* pCompletedDT , long* pAttendantID ,
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
										__int64* pTag , long * pDuration );
typedef long (WINAPI *typeGetPumpDeliveryPropertiesEx3)( long ID , short Index , long* pDeliveryID , short* pType , short* pState, long* pHoseID, short* pHoseNum, long* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName ,
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , long* pLockedBy ,
									    long* pReservedBy , long* pAge , DATE* pCompletedDT , long* pAttendantID ,
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
										__int64* pTag , long * pDuration , long* pCardClientID );
typedef long (WINAPI *typePrepayReserve)( long ID );
typedef long (WINAPI *typePrepayCancel)( long ID  );
typedef long (WINAPI *typePrepayAuthorise)( long ID , short LimitType , double Value , short Hose , short PriceLevel );
typedef long (WINAPI *typePreauthReserve)( long ID );
typedef long (WINAPI *typePreauthCancel)( long ID );
typedef long (WINAPI *typePreauthAuthorise)( long ID , short LimitType , double Value , short Hose , short PriceLevel );
typedef long (WINAPI *typeLoadPreset)( long ID , short LimitType , double Value , short Hose , short PriceLevel );
typedef long (WINAPI *typeLoadPresetWithPrice)( long ID , short LimitType , double Value , short Hose , short PriceLevel , double Price );
typedef long (WINAPI *typeTagAuthorise)( long ID , __int64 Tag , short LimitType , double Value , short Hose , short PriceLevel );
typedef long (WINAPI *typeAttendantAuthorise)( long ID , long AttendantID );
typedef long (WINAPI *typeAuthorise)( long ID );
typedef long (WINAPI *typeCancelAuthorise)( long ID );
typedef long (WINAPI *typeTempStop)( long ID );
typedef long (WINAPI *typeReAuthorise)( long ID );
typedef long (WINAPI *typeTerminateDelivery)( long ID );
typedef long (WINAPI *typeStackCurrentDelivery)( long ID );
typedef long (WINAPI *typeGetDensity)( long ID , double* pDensity);
typedef long (WINAPI *typeEnablePump)( long ID );
typedef long (WINAPI *typeDisablePump)( long ID );
typedef long (WINAPI *typeGetHosesCount)( long* pCount );
typedef long (WINAPI *typeGetHoseByOrdinal)( long Index , long* pID );
typedef long (WINAPI *typeGetHoseProperties)(long ID , long* pNumber, long* pPumpID ,long* pTankID , long* pPhysicalNumber,
		                      double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue ,
				              double* pMtrElecVolume );
typedef long (WINAPI *typeSetHoseProperties)(long ID , long Number,long PumpID, long TankID , long PhysicalNumber,
		                      double MtrTheoValue , double MtrTheoVolume ,double MtrElecValue ,
				              double MtrElecVolume );
typedef long (WINAPI *typeGetHoseSummary)(	long ID , long* pNumber, long* pPhysicalNumber,
							long* pPumpID, long* pPumpNumber, PBSTR pPumpName,
							long* pTankID, long* pTankNumber, PBSTR pTankName,
							long* pGradeID , long* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
		                    double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue , double* pMtrElecVolume );

typedef long (WINAPI *typeGetHoseSummaryEx)(	long ID , long* pNumber, long* pPhysicalNumber,
							long* pPumpID, long* pPumpNumber, PBSTR pPumpName,
							long* pTankID, long* pTankNumber, PBSTR pTankName,
							long* pGradeID , long* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
		                    double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue , double* pMtrElecVolume ,
							double* pPrice1 , double* pPrice2 , short* pEnabled);

typedef long (WINAPI *typeDeleteHose)( long ID );
typedef long (WINAPI *typeGetDeliveriesCount)( long* pCount );
typedef long (WINAPI *typeGetDeliveryByOrdinal)( long Index , long* pID );
typedef long (WINAPI *typeGetAllDeliveriesCount)( long* pCount )  ;
typedef long (WINAPI *typeGetAllDeliveryByOrdinal)( long Index , long* pID );

typedef long (WINAPI *typeAckDeliveryDBLog)( long ID );
typedef long (WINAPI *typeGetDeliveryIDByOrdinalNotLogged)( long Ordinal , long* pID );
typedef long (WINAPI *typeGetDeliveriesCountNotLogged)( long* pCount );
typedef long (WINAPI *typeAckDeliveryVolLog)( long ID );
typedef long (WINAPI *typeGetDeliveryIDByOrdinalNotVolLogged)( long Ordinal , long* pID );
typedef long (WINAPI *typeGetDeliveriesCountNotVolLogged)( long* pCount );

typedef long (WINAPI *typeGetDeliveryProperties)( long ID , long* pHoseID ,short* pState ,short* pType ,double* pVolume ,
								   short* pPriceLevel ,double* pPrice ,double* pValue ,double* pVolume2 ,
								   DATE* pCompletedDT ,long* pLockedBy , long* pReservedBy , long* pAttendantID , long* pAge );
typedef long (WINAPI *typeGetDeliveryPropertiesEx)( long ID , long* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                           double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, long* pReservedBy , long* pAttendantID , long* pAge ,
								   DATE* pClearedDT ,double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag );
typedef long (WINAPI *typeGetDeliveryPropertiesEx2)( long ID , long* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                           double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, long* pReservedBy ,
								   long* pAttendantID , long* pAge , DATE* pClearedDT ,
								   double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
								   double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
								   __int64* pTag , long * pDuration );
typedef long (WINAPI *typeGetDeliveryPropertiesEx3)( long ID , long* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                           double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, long* pReservedBy ,
								   long* pAttendantID , long* pAge , DATE* pClearedDT ,
								   double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
								   double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
								   __int64* pTag , long * pDuration , long* pCardClientID );

typedef long (WINAPI *typeSetDeliveryProperties)( long ID , long HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2, DATE CompletedDT ,long LockedBy, long ReservedBy ,
								   long AttendantID , long Age );
typedef long (WINAPI *typeSetDeliveryPropertiesEx)( long ID , long HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,long LockedBy,
								   long ReservedBy , long AttendantID , long Age , DATE ClearedDT , double VolumeETot , double Volume2ETot , double ValueETot , __int64 Tag );
typedef long (WINAPI *typeSetDeliveryPropertiesEx2)( long ID , long HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,long LockedBy,
								   long ReservedBy , long AttendantID , long Age , DATE ClearedDT ,
								   double OldVolumeETot , double OldVolume2ETot , double OldValueETot ,
								   double NewVolumeETot , double NewVolume2ETot , double NewValueETot ,
								   __int64 Tag , long Duration );


typedef long (WINAPI *typeSetDeliveryPropertiesEx3)( long ID , long HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,long LockedBy,
								   long ReservedBy , long AttendantID , long Age , DATE ClearedDT ,
								   double OldVolumeETot , double OldVolume2ETot , double OldValueETot ,
								   double NewVolumeETot , double NewVolume2ETot , double NewValueETot ,
								   __int64 Tag , long Duration , long CardClientID );

typedef long (WINAPI *typeGetDeliverySummary)( long ID , long* pHoseID ,long* pHoseNumber, long* pHosePhysicalNumber,
	  							long* pPumpID, long* pPumpNumber, PBSTR  pPumpName,
								long* pTankID, long* pTankNumber, PBSTR  pTankName,
								long* pGradeID , long* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
								double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy,
								long* pReservedBy , long* pAttendantID , long* pAge ,DATE* pClearedDT ,
								double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag);
typedef long (WINAPI *typeGetDeliverySummaryEx)( long ID , long* pHoseID ,long* pHoseNumber, long* pHosePhysicalNumber,
	  							long* pPumpID, long* pPumpNumber, PBSTR  pPumpName,
								long* pTankID, long* pTankNumber, PBSTR  pTankName,
								long* pGradeID , long* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                        double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy,
								long* pReservedBy , long* pAttendantID , long* pAge ,DATE* pClearedDT ,
								double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
								double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
								__int64* pTag , long * pDuration );
typedef long (WINAPI *typeGetDeliverySummaryEx2)( long ID , long* pHoseID ,long* pHoseNumber, long* pHosePhysicalNumber,
	  							long* pPumpID, long* pPumpNumber, PBSTR  pPumpName,
								long* pTankID, long* pTankNumber, PBSTR  pTankName,
								long* pGradeID , long* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                        double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy,
								long* pReservedBy , long* pAttendantID , long* pAge ,DATE* pClearedDT ,
								double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
								double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
								__int64* pTag , long * pDuration , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
								long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag );
typedef long (WINAPI *typeLockDelivery)( long ID );
typedef long (WINAPI *typeUnlockDelivery)( long ID );
typedef long (WINAPI *typeClearDelivery)( long ID , short Type );
typedef long (WINAPI *typeLockAndClearDelivery)( long ID , short Type );
typedef long (WINAPI *typeGetDuration)( long ID , long* pDuration );
typedef long (WINAPI *typeGetGradesCount)( long* pCount );
typedef long (WINAPI *typeGetGradeByNumber)( long Number , long* pID );
typedef long (WINAPI *typeGetGradeByName)( BSTR Name , long* pID );
typedef long (WINAPI *typeGetGradeByOrdinal)( long Index , long* pID );
typedef long (WINAPI *typeGetGradeProperties)(long ID , long* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pCode );
typedef long (WINAPI *typeSetGradeProperties)(long ID , long Number, BSTR Name , BSTR ShortName , BSTR Code  );
typedef long (WINAPI *typeDeleteGrade)( long ID );
typedef long (WINAPI *typeSetGradePrice)( long ID , short Level , double Price );
typedef long (WINAPI *typeGetGradePrice)( long ID , short Level , double* pPrice );
typedef long (WINAPI *typeGetTanksCount)( long* pCount );
typedef long (WINAPI *typeGetTankByNumber)( long Number , long* pID );
typedef long (WINAPI *typeGetTankByName)( BSTR Name , long* pID );
typedef long (WINAPI *typeGetTankByOrdinal)( long Index , long* pID );
typedef long (WINAPI *typeGetTankProperties)(long ID , long* pNumber, PBSTR pName , long* pGradeID , short* pType , double* pCapacity , double* pDiameter ,
							  double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature ,
							  double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, long* pGaugeID, short* pProbeNo );
typedef long (WINAPI *typeSetTankProperties)(long ID , long Number, BSTR Name , long GradeID , short Type , double Capacity , double Diameter , double TheoVolume ,
		                      double GaugeVolume , double GaugeTCVolume ,double GaugeUllage ,double GaugeTemperature , double GaugeLevel ,
							  double GaugeWaterVolume, double GaugeWaterLevel, long GaugeID , short ProbeNo );
typedef long (WINAPI *typeSetTankPropertiesEx)(long ID , long Number, BSTR Name , long GradeID , short Type , double Capacity , double Diameter , double TheoVolume ,
		                      double GaugeVolume , double GaugeTCVolume ,double GaugeUllage ,double GaugeTemperature , double GaugeLevel ,
							  double GaugeWaterVolume, double GaugeWaterLevel, long GaugeID , short ProbeNo, long GaugeAlarmsMask);
typedef long (WINAPI *typeGetTankSummary)(long ID , long* pNumber, PBSTR pName , long* pGradeID ,
						   long* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
						   short* pType , double* pCapacity , double* pDiameter ,
						   double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature ,
						   double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, long* pGaugeID, short* pProbeNo );
typedef long (WINAPI *typeTankDrop)( long ID , double Volume , DATE DropDT , BSTR Terminal , BSTR DocumentType , DATE DocumentDT  , BSTR DocumentFolio , double PEMEXVolume );
typedef long (WINAPI *typeDeleteTank)( long ID );
typedef long (WINAPI *typeGetPortsCount)( long* pCount );
typedef long (WINAPI *typeGetPortByNumber)( long Number , long* pID );
typedef long (WINAPI *typeGetPortByName)( BSTR Name , long* pID );
typedef long (WINAPI *typeGetPortByOrdinal)( long Index , long* pID );
typedef long (WINAPI *typeGetPortProperties)(long ID , long* pNumber, PBSTR pName , long* pProtocolID , short* pDeviceType , PBSTR pSerialNo );
typedef long (WINAPI *typeSetPortProperties)(long ID , long Number, BSTR Name, long ProtocolID , short DeviceType , BSTR SerialNo );
typedef long (WINAPI *typeGetAttendantsCount)( long* pCount );
typedef long (WINAPI *typeGetAttendantByNumber)( long Number , long* pID );
typedef long (WINAPI *typeGetAttendantByName)( BSTR Name , long* pID );
typedef long (WINAPI *typeGetAttendantByOrdinal)( long Index , long* pID );
typedef long (WINAPI *typeGetAttendantProperties)(long ID , long* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pPassword , PBSTR pTag );
typedef long (WINAPI *typeSetAttendantProperties)(long ID , long Number, BSTR Name , BSTR ShortName , BSTR Password , BSTR Tag );
typedef long (WINAPI *typeGetAttendantPropertiesEx)(long ID , long* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pPassword , PBSTR pTag ,
									 short* pShiftAStart , short* pShiftAEnd , short* pShiftBStart , short* pShiftBEnd , short* pEnabled )  ;
typedef long (WINAPI *typeSetAttendantPropertiesEx)(long ID , long Number, BSTR Name , BSTR ShortName , BSTR Password , BSTR Tag,
									 short ShiftAStart , short ShiftAEnd , short ShiftBStart , short ShiftBEnd , short Enabled )  ;
typedef long (WINAPI *typeDeleteAttendant)( long ID );
typedef long (WINAPI *typeAttendantLogon)( long ID , long PumpID );
typedef long (WINAPI *typeAttendantLogoff)( long ID );

typedef long (WINAPI *typeGetCardReadsCount)( long* pCount );
typedef long (WINAPI *typeGetCardReadByNumber)( long Number , long* pID );
typedef long (WINAPI *typeGetCardReadByName)( BSTR Name , long* pID );
typedef long (WINAPI *typeGetCardReadByOrdinal)( long Index , long* pID );
typedef long (WINAPI *typeGetCardReadProperties)(long ID , long* pNumber, PBSTR pName , long* pPumpID , short* pType , long* pParentID , __int64* pTag , DATE* pTimeStamp )  ;
typedef long (WINAPI *typeSetCardReadProperties)(long ID , long Number, BSTR Name , long PumpID , short Type , long ParentID , __int64 Tag , DATE TimeStamp)  ;
typedef long (WINAPI *typeDeleteCardRead)( long ID );
typedef long (WINAPI *typeGetCardClientsCount)( long* pCount );
typedef long (WINAPI *typeGetCardClientByNumber)( long Number , long* pID );
typedef long (WINAPI *typeGetCardClientByName)( BSTR Name , long* pID );
typedef long (WINAPI *typeGetCardClientByOrdinal)( long Index , long* pID );
typedef long (WINAPI *typeGetCardClientProperties)(long ID , long* pNumber, PBSTR pName , PBSTR pTag , short* pEnabled )  ;
typedef long (WINAPI *typeSetCardClientProperties)(long ID , long Number, BSTR Name , BSTR Tag , short Enabled )  ;
typedef long (WINAPI *typeDeleteCardClient)( long ID );

typedef long (WINAPI *typeAllStop)();
typedef long (WINAPI *typeAllAuthorise)();
typedef long (WINAPI *typeAllReAuthorise)();
typedef long (WINAPI *typeAllStopIfIdle)();
typedef long (WINAPI *typeReadAllTanks)();
typedef long (WINAPI *typeGetAllPumpStatuses)( PBSTR pStates , PBSTR pCurrentHoses , PBSTR pDeliveriesCount );
typedef long (WINAPI *typeGetIniValue)( BSTR Section , BSTR Key , PBSTR pValue );
typedef long (WINAPI *typeSetIniValue)( BSTR Section , BSTR Key , BSTR Value );
typedef long (WINAPI *typeSetNextDeliveryID)( long ID );
typedef long (WINAPI *typeRemovePort)( long ID );
typedef long (WINAPI *typeLicenseStatus)();
typedef long (WINAPI *typeCheckSocketClosed)( LPARAM lParam );

typedef BSTR (WINAPI *typeResultString)( long Res );
typedef BSTR (WINAPI *typePumpStateString)( short State );
typedef BSTR (WINAPI *typeDeliveryStateString)( short State );
typedef BSTR (WINAPI *typeDeliveryTypeString)( short Type );
typedef BSTR (WINAPI *typeReserveTypeString)( short Type );

// *** new APIS
typedef long (WINAPI *typeGetNextPumpEventEx)( long* pPumpID, short* pPumpNumber, short* pState, short* pReservedFor, long* pReservedBy, long* pHoseID ,
							    short* pHoseNumber,long* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume,
							    double* pValue, short* pStackSize , PBSTR pPumpName , short* pPhysicalNumber , short* pSide , short* pAddress,
								short* pPriceLevel1 , short* pPriceLevel2 , short* pType , long* pPortID , short* pAuthMode , short* pStackMode ,  short* pPrepayAllowed,
								short* pPreauthAllowed ,  short* pPriceFormat , short* pValueFormat , short* pVolumeFormat  );

typedef long (WINAPI *typeGetNextPumpEventEx2)( long* pPumpID, long* pPumpNumber, short* pState, short* pReservedFor, long* pReservedBy, long* pHoseID ,
							    long* pHoseNumber,long* pHosePhysicalNumber,long* pGradeID,long* pGradeNumber, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume,
							    double* pValue, short* pStackSize , PBSTR pPumpName , long* pPhysicalNumber , short* pSide , short* pAddress,
								short* pPriceLevel1 , short* pPriceLevel2 , short* pType , long* pPortID , short* pAuthMode , short* pStackMode ,  short* pPrepayAllowed,
								short* pPreauthAllowed ,  short* pPriceFormat , short* pValueFormat , short* pVolumeFormat , __int64* pTag ,
							    long* pAttendantID , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							    long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag  );

typedef long (WINAPI *typeGetNextDeliveryEventEx)( long* pDeliveryID , long* pPumpID, short* pPumpNumber, long* pHoseID, short* pHoseNumber ,
								    long* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel, double* pPrice,
									double* pVolume, double* pValue, short* pDeliveryState ,
								    short* pDeliveryType, long* pLockedBy, long* pReservedBy, long* pAge , DATE* pCompletedDT ,
									long* pAttendantID, double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag);
typedef long (WINAPI *typeGetNextDeliveryEventEx2)( long* pDeliveryID , long* pPumpID, short* pPumpNumber, long* pHoseID, short* pHoseNumber ,
								     long* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel, double* pPrice,
									 double* pVolume, double* pValue, short* pDeliveryState ,
								     short* pDeliveryType, long* pLockedBy, long* pReservedBy, long* pAge , DATE* pCompletedDT ,
									 long* pAttendantID,
									 double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot ,
									 double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot ,
									 __int64* pTag , long* pDuration );
typedef long (WINAPI *typeGetNextDeliveryEventEx3)( long* pDeliveryID, long* pHoseID ,long* pHoseNumber, long* pHosePhysicalNumber,
	  									long* pPumpID, long* pPumpNumber, PBSTR pPumpName,
										long* pTankID, long* pTankNumber, PBSTR pTankName,
										long* pGradeID , long* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
										short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT , long* pLockedBy,
										long* pReservedBy , long* pAttendantID , long* pAge , DATE* pClearedDT ,
										double* pOldVolumeETot, double* pOldVolume2ETot, double* pOldValueETot ,
										double* pNewVolumeETot, double* pNewVolume2ETot, double* pNewValueETot ,
										__int64* pTag , long* pDuration , long* pAttendantNumber , PBSTR AttendantName, __int64* pAttendantTag ,
										long* pCardClientID , long* pCardClientNumber , PBSTR CardClientName, __int64* pCardClientTag );
typedef long (WINAPI *typeGetNextCardReadEvent)( long* pCardReadID , long* pNumber, PBSTR pName , long* pPumpID , short* pType , long* pParentID , __int64* pTag , DATE* pTimeStamp);
typedef long (WINAPI *typeGetNextDBHoseETotalsEventEx)( long* pHoseID , double* pVolume , double* pValue , double* pVolumeETot , double* pValueETot ,
										 long* pHoseNumber , long* pHosePhysicalNumber , long* pPumpID , long* pPumpNumber , PBSTR pPumpName ,
										 long* pTankID , long* pTankNumber , PBSTR pTankName , long* pGradeID , PBSTR pGradeName );
typedef long (WINAPI *typeGetNextDBTankStatusEventEx)( long* pTankID , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage,
									    double* pGaugeTemperature , double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel ,
									    long* pTankNumber , PBSTR pTankName , long* pGradeID , PBSTR pGradeName , short*pType  ,
										double* pCapacity , double* pDiameter , long* pGaugeID , short* pProbeNo);
typedef long (WINAPI *typeGetZigBeeCount)( long* pCount );
typedef long (WINAPI *typeGetZigBeeByNumber)( long Number , long* pID );
typedef long (WINAPI *typeGetZigBeeByName)( BSTR Name , long* pID );
typedef long (WINAPI *typeGetZigBeeByOrdinal)( long Index , long* pID );
typedef long (WINAPI *typeGetZigBeeProperties)(long ID , long* pNumber, PBSTR pName , short* pDeviceType , PBSTR pSerialNumber , PBSTR pNodeIdentifier , long* pPortID );
typedef long (WINAPI *typeSetZigBeeProperties)(long ID , long Number, BSTR Name , short DeviceType , BSTR SerialNumber , BSTR NodeIdentifier , long PortID );
typedef long (WINAPI *typeDeleteZigBee)( long ID );
typedef long (WINAPI *typeGetHosePropertiesEx)(long ID , long* pNumber, long* pPumpID ,long* pTankID , long* pPhysicalNumber,
		                      double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue ,
				              double* pMtrElecVolume , short* pUVEAntenna );
typedef long (WINAPI *typeSetHosePropertiesEx)(long ID , long Number,long PumpID, long TankID , long PhysicalNumber,
		                      double MtrTheoValue , double MtrTheoVolume ,double MtrElecValue ,
				              double MtrElecVolume , short UVEAntenna );
typedef long (WINAPI *typeGetHosePropertiesEx2)(long ID , long* pNumber, long* pPumpID ,long* pTankID , long* pPhysicalNumber,
		                      double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue ,
				              double* pMtrElecVolume , short* pUVEAntenna , double* pPrice1 , double* pPrice2 , short* pEnabled );
typedef long (WINAPI *typeSetHosePropertiesEx2)(long ID , long Number,long PumpID, long TankID , long PhysicalNumber,
		                      double MtrTheoValue , double MtrTheoVolume ,double MtrElecValue ,
				              double MtrElecVolume , short UVEAntenna , double Price1 , double Price2 , short Enabled );
typedef long (WINAPI *typeSetPumpPropertiesEx)(long ID , long Number, BSTR Name, short PhysicalNumber, short Side, short Address, short PriceLevel1,
						        short PriceLevel2, short PriceDspFormat, short VolumeDspFormat, short ValueDspFormat, short Type,
						        long PortID, long AttendantID, short AuthMode, short StackMode, short PrepayAllowed, short PreauthAllowed ,
								long SlotZigBeeID , long MuxSlotZigBeeID , short PriceControl , short HasPreset );
typedef long (WINAPI *typeGetPumpPropertiesEx)(long ID , long* pNumber, PBSTR pName, short* pPhysicalNumber, short* pSide, short* pAddress, short* pPriceLevel1,
						      short* pPriceLevel2, short* pPriceDspFormat, short* pVolumeDspFormat, short* pValueDspFormat, short* pType,
						      long* pPortID, long* pAttendantID, short* pAuthMode, short* pStackMode, short* pPrepayAllowed, short* pPreauthAllowed ,
							  long* pSlotZigBeeID , long* pMuxSlotZigBeeID , short* pPriceControl , short* pHasPreset);
typedef long (WINAPI *typeGetSerialNo)( long ID , PBSTR pSerialNo );
typedef long (WINAPI *typeGetDeviceDetails)( long ID , long ZBID , PBSTR pSerialNo , PBSTR pBootVersion , PBSTR pFirmwareVersion );
typedef long (WINAPI *typeResetDevice)( long ID , long ZBID );
typedef long (WINAPI *typeRequestVersion)( long ID , long ZBID );
typedef long (WINAPI *typeSetHoseETotals)( long ID , double Volume , double Value );
typedef long (WINAPI *typeGetNextZBStatusEvent)( long* pPortID , long* pZBID , __int64* pZBAddress, short* pCondition , short* pCount , short* pStrength );
typedef long (WINAPI *typeGetNextZBPanIDEvent)( long* pPortID , __int64* pZBPanID );
typedef long (WINAPI *typeGetNextZeroDeliveryEvent)( long* pPumpID , long* pPumpNumber , long* pHoseID , long* pHoseNumber );
typedef long (WINAPI *typeSetHosePrices)( long ID , short DurationType , short PriceType , double Price1 , double Price2 );
typedef long (WINAPI *typeGetHosePrices)( long ID , short* pDurationType , short* pPriceType , double* pPrice1 , double* pPrice2 );
typedef long (WINAPI *typeSetPumpDefaultPriceLevel)( long ID , short Level );
typedef long (WINAPI *typeSetDateTime)( DATE DateTime );
typedef long (WINAPI *typeGetSensorsCount)(long* pCount);
typedef long (WINAPI *typeGetSensorByOrdinal)(long Index, long* ID);
typedef long (WINAPI *typeGetSensorProperties)(long ID, long* Number, PBSTR Name, long* PortID, short* Type, short* Address, short* SensorNo);
typedef long (WINAPI *typeSetGradePropertiesEx)(long GradeID, long GradeNumber, PBSTR GradeName, PBSTR GradeShortName, PBSTR GradeCode, short GradeType);
typedef long (WINAPI *typeGetClientsCount)( long* pCount );
typedef long (WINAPI *typeGetPumpStatusEx2)( long ID , long* pPumpNumber, PBSTR pPumpName, long* pPhysicalNumber, short* pState, short* pReservedFor, long* pReservedBy, long* pHoseID, long* pHoseNumber , long* pHosePhysicalNumber , long* pGradeID , 
							  long* pGradeNumber , PBSTR pGradeName, PBSTR pShortGradeName, short* pPriceLevel , double* pPrice , double* pVolume , double* pValue , short* pStackSize , __int64* pTag , 
							  long* pAttendantID , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							  long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag , 
							  double* pCurFlowRate , double* pPeakFlowRate );
typedef long (WINAPI *typeCheckforManagementFtn)();
typedef long (WINAPI *typeFireEvents)();
typedef long (WINAPI *typePaymentReserve)( long ID , long TermID , BSTR TermHash );
typedef long (WINAPI *typePaymentCancel)( long ID , long TermID , BSTR TermHash );
typedef long (WINAPI *typePaymentAuthorise)( long ID , long TermID , BSTR TermHash ,
							  long AttendantID , __int64 AttendantTag , 
							  long CardClientID , __int64 CardClientTag , 
							  short AuthType , __int64 ExtTag ,
							  short GradeType , short PriceType  , short PriceLevel , double Price , 
							  short PresetType , double Value , short Hose ,
							  double Odometer , double Odometer2 , BSTR Plate , 
							  BSTR ExtTransactionID , BSTR DriverID , BSTR AuthorisationID );
typedef long (WINAPI *typeDeliveriesCountFiltered)(long* pCount, long PumpID, long HoseID, 
	                          long GradeID, long TankID, long LockedBy, long ReservedBy, short State, 
	                          short Type, __int64 Tag, long AttendantID, long CardClientID);
typedef long (WINAPI *typeGetDeliveryIDByOrdinalFiletered)(long Ordinal, long* pID, long PumpID, 
	                          long HoseID, long GradeID, long TankID, long LockedBy, long ReservedBy, 
	                          short State, short Type, __int64 Tag, long AttendantID, long CardClientID);
typedef long (WINAPI *typeGetDeliveryPropertiesEx4)( long ID , long* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, long* pReservedBy , 
										long* pAttendantID , long* pAge , DATE* pClearedDT ,
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , long * pDuration , long* pCardClientID , double* pPeakFlowRate ) ;
typedef long (WINAPI *typeSetDeliveryPropertiesEx4)( long ID , long HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,long LockedBy, 
								   long ReservedBy , long AttendantID , long Age , DATE ClearedDT , 
								   double OldVolumeETot , double OldVolume2ETot , double OldValueETot , 
								   double NewVolumeETot , double NewVolume2ETot , double NewValueETot , 
								   __int64 Tag , long Duration , long CardClientID, double PeakFlowRate ) ;
typedef long (WINAPI *typeGetPumpDeliveryPropertiesEx4)( long ID , short Index , long* pDeliveryID , short* pType , short* pState, long* pHoseID, short* pHoseNum, long* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName , 
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , long* pLockedBy , 
									    long* pReservedBy , long* pAge , DATE* pCompletedDT , long* pAttendantID , 
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , long * pDuration , long* pCardClientID , double* pPeakFlowRate  ) ;
typedef long (WINAPI *typeGetDeliverySummaryEx3)( long ID , long* pHoseID ,long* pHoseNumber, long* pHosePhysicalNumber,
	  							long* pPumpID, long* pPumpNumber, PBSTR  pPumpName,
								long* pTankID, long* pTankNumber, PBSTR  pTankName,
								long* pGradeID , long* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                        double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, 
								long* pReservedBy , long* pAttendantID , long* pAge ,DATE* pClearedDT ,
								double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
								double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
								__int64* pTag , long * pDuration , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
								long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag  , double* pPeakFlowRate ) ;
typedef long (WINAPI *typeGetDeliverySummaryEx4)(long ID, long* pHoseID, long* pHoseNumber, long* pHosePhysicalNumber,
								long* pPumpID, long* pPumpNumber, PBSTR  pPumpName,
								long* pTankID, long* pTankNumber, PBSTR  pTankName,
								long* pGradeID, long* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
								short* pState, short* pType, double* pVolume, short* pPriceLevel,
								double* pPrice, double* pValue, double* pVolume2, DATE* pCompletedDT, long* pLockedBy,
								long* pReservedBy, long* pAttendantID, long* pAge, DATE* pClearedDT,
								double* pOldVolumeETot, double* pOldVolume2ETot, double* pOldValueETot,
								double* pNewVolumeETot, double* pNewVolume2ETot, double* pNewValueETot,
								__int64* pTag, long * pDuration, long* pAttendantNumber, PBSTR pAttendantName, __int64* pAttendantTag, PBSTR pAttendantIDNumber,
								long* pCardClientID, long* pCardClientNumber, PBSTR pCardClientName, __int64* pCardClientTag, PBSTR pCardClientIDNumber, double* pPeakFlowRate);
typedef long (WINAPI *typeSetDeliveryExt)( long ID , BSTR Plate , double Odometer , double Odometer2 , BSTR ExtTransactionID ,
                                BSTR DriverID , BSTR AuthID, short AuthType ) ;
typedef long (WINAPI *typeGetDeliveryExt)( long ID , PBSTR pPlate , double* pOdometer , double* pOdometer2 , PBSTR pExtTransactionID ,
                                PBSTR pDriverID , PBSTR pAuthID, short* pAuthType ) ;
typedef long (WINAPI *typeGetGradePropertiesEx)(long ID , long* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pCode , 
	                            short* pType );
typedef long (WINAPI *typeGetTankPropertiesEx)(long ID , long* pNumber, PBSTR pName , long* pGradeID , short* pType , double* pCapacity , double* pDiameter , 
							  double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
							  double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, long* pGaugeID, short* pProbeNo , long* pGaugeAlarmsMask );
typedef long (WINAPI *typeGetTankSummaryEx)(long ID , long* pNumber, PBSTR pName , long* pGradeID , 
						      long* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode, 
						      short* pType , double* pCapacity , double* pDiameter , 
						      double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
						      double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, long* pGaugeID, short* pProbeNo , 
						      short* pState , long* pGaugeAlarmsMask);
typedef long (WINAPI *typeGetAttendantPropertiesEx2)(long ID, long* pNumber, PBSTR pName, PBSTR pShortName, PBSTR pPassword, 
	                          PBSTR pTag, PBSTR pIDNumber,short* pShiftAStart, short* pShiftAEnd, short* pShiftBStart, 
	                          short* pShiftBEnd, short* pType);
typedef long (WINAPI *typeSetAttendantPropertiesEx2)(long ID, long Number, BSTR Name, BSTR ShortName, BSTR Password, BSTR Tag, 
	                          BSTR IDNumber,short ShiftAStart, short ShiftAEnd, short ShiftBStart, short ShiftBEnd, short Type);
typedef long (WINAPI *typeGetAttendantState)( long ID , short* pType , short* pLoggedOn ) ;
typedef long (WINAPI *typeGetCardClientPropertiesEx)(long ID , long* pNumber, PBSTR pName , PBSTR pTag , short* pEnabled , 
	                          short* pPriceLevel, PBSTR pPlate  ) ;
typedef long (WINAPI *typeSetCardClientPropertiesEx)(long ID , long Number, BSTR Name , BSTR Tag , short Enabled , short PriceLevel , BSTR Plate );
typedef long (WINAPI *typeSetCardClientPropertiesEx2)(long ID , long Number, BSTR Name , BSTR Tag , short Enabled , short PriceLevel ,
                              BSTR Plate , short GradeType, short CardType, short LimitType, double Limit, short EntryType,
                              DATE ExpirationDate, long ParentID ) ;
typedef long (WINAPI *typeGetCardClientPropertiesEx2)(long ID , long* pNumber, PBSTR pName , PBSTR pTag , short* pEnabled , 
	                          short* pPriceLevel , PBSTR pPlate , short* pGradeType, short* pCardType, short* pLimitType, 
	                          double* pLimit, short* pEntryType, DATE* pExpirationDate, long* pParentID ) ;
typedef long (WINAPI *typeGetCardClientPropertiesEx3)(long ID, long* pNumber, PBSTR pName, PBSTR pTag, short* pEnabled, 
	                          short* pPriceLevel, PBSTR pPlate, PBSTR pIDNumber, PBSTR pShortName, PBSTR pPassword,
	                          short* pGradeType, short* pCardType, short* pLimitType, double* pLimit, short* pEntryType,
	                          DATE* pExpirationDate, long* pParentID);
typedef long (WINAPI *typeSetCardClientPropertiesEx3)(long ID, long Number, BSTR Name, BSTR Tag, short Enabled, short PriceLevel,
							  BSTR Plate, BSTR IDNumber, BSTR ShortName, BSTR Password, short GradeType, short CardType, 
							  short LimitType, double Limit, short EntryType, DATE ExpirationDate, long ParentID);
typedef long (WINAPI *typeScheduleBeep)( long ID , short Pitch1 , short Duration1 , short Pitch2 , short Duration2,
                              short Pitch3 , short Duration3, short Pitch4 , short Duration4, short Pitch5 , short Duration5 );
typedef long (WINAPI *typeFlashLEDS)( long ID , short Side , short PeriodMs , short Cycles );
typedef long (WINAPI *typeGetIniValueEx)( BSTR FileName , BSTR Section , BSTR Key , PBSTR pValue );
typedef long (WINAPI *typeSetIniValueEx)( BSTR FileName , BSTR Section , BSTR Key , BSTR Value );
typedef long (WINAPI *typeGetCardType)( BSTR Tag , short* pTagType , long* pID, PBSTR pName, long* pNumber  );
typedef long (WINAPI *typeFindCard)(BSTR Tag, short* pCardType, short* pTagType, long* pID, PBSTR pName, long* pNumber);
typedef long (WINAPI *typeGetNextPumpEventEx3)( long* pPumpID, long* pPumpNumber, short* pState, short* pReservedFor, long* pReservedBy, long* pHoseID ,
							    long* pHoseNumber,long* pHosePhysicalNumber,long* pGradeID,long* pGradeNumber, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume, 
							    double* pValue, short* pStackSize , PBSTR pPumpName , long* pPhysicalNumber , short* pSide , short* pAddress, 
								short* pPriceLevel1 , short* pPriceLevel2 , short* pType , long* pPortID , short* pAuthMode , short* pStackMode ,  short* pPrepayAllowed, 
								short* pPreauthAllowed ,  short* pPriceFormat , short* pValueFormat , short* pVolumeFormat , __int64* pTag , 
							    long* pAttendantID , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							    long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag , 
								double* pCurFlowRate , double* pPeakFlowRate );
typedef long (WINAPI *typeGetNextDeliveryEventEx4)( long* pDeliveryID, long* pHoseID ,long* pHoseNumber, long* pHosePhysicalNumber,
	  									long* pPumpID, long* pPumpNumber, PBSTR pPumpName,
										long* pTankID, long* pTankNumber, PBSTR pTankName,
										long* pGradeID , long* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
										short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT , long* pLockedBy, 
										long* pReservedBy , long* pAttendantID , long* pAge , DATE* pClearedDT , 
										double* pOldVolumeETot, double* pOldVolume2ETot, double* pOldValueETot , 
										double* pNewVolumeETot, double* pNewVolume2ETot, double* pNewValueETot , 
										__int64* pTag , long* pDuration , long* pAttendantNumber , PBSTR AttendantName, __int64* pAttendantTag ,
										long* pCardClientID , long* pCardClientNumber , PBSTR CardClientName, __int64* pCardClientTag , double* pPeakFlowRate) ;
typedef long (WINAPI *typeGetNextDBTankStatusEventEx2)( long* pTankID , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, 
									    double* pGaugeTemperature , double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel , 
									    long* pTankNumber , PBSTR pTankName , long* pGradeID , PBSTR pGradeName , short*pType  , double* pCapacity , 
										double* pDiameter , long* pGaugeID , short* pProbeNo , short* pState , long* pAlarmsMask ) ;
typedef long (WINAPI *typeGetNextSerialPortEvent)( long* pPortID , long* pZBID , short* pSlot , short* pResult , PBSTR pRxMsg ) ;
typedef long (WINAPI *typeGetNextZBEvent)( long* pPortID , long* pZBID , __int64* pZBAddress, short* pResult , short* pMsgType , PBSTR pRxMsg ) ;
typedef long (WINAPI *typeGetNextUVEEvent)( long* pPumpID , long* pPumpNumber , long* pHoseID , long* pHoseNumber , PBSTR pUVE ) ;
typedef long (WINAPI *typeSetZBCoordPan)( long ID , __int64 Pan ) ;
typedef long (WINAPI *typeGetZBCoordPan)( long ID ) ;
typedef long (WINAPI *typeSetLineMode)( long ID , long ZBID , short Mode ) ;
typedef long (WINAPI *typeGetDateTime)( DATE* pDateTime ) ;
typedef long (WINAPI *typeGetNextZB2GStatusEvent)( long* pPortID , __int64* pZBAddress, short* pLQI , short* pRSSI , __int64*  pParZBAddress, short* pZBChannel , short* pMemBlocks , short* pMemFree ) ;
typedef long (WINAPI *typeGetZB2GConfig)( long ID , __int64* pPanID , long* pChannels , __int64* pKeyA , __int64* pKeyB );
typedef long (WINAPI *typeGetLogEventCount)( long* pCount , short DeviceType , long DeviceID , short EventLevel , short EventType , long ClearedBy, long  AckedBy ) ;
typedef long (WINAPI *typeGetLogEventByOrdinal)( long Index , long* pID , short DeviceType , long DeviceID , short EventLevel , short EventType ,long  ClearedBy, long  AckedBy ) ;
typedef long (WINAPI *typeGetLogEventProperties)(long ID , short* pDeviceType , long* pDeviceID , long* pDeviceNumber ,	PBSTR pDeviceName , short* pEventLevel ,
								        short* pEventType , PBSTR pEventDesc , DATE* pGeneratedDT , DATE* pClearedDT , long* pClearedBy , long* pAckedBy , double* pVolume ,
								        double* pValue , double* pProductVolume , double* pProductLevel , double* pWaterLevel , double* pTemperature);
typedef long (WINAPI *typeSetLogEventProperties)(long ID , short DeviceType , long DeviceID , long DeviceNumber , BSTR DeviceName , short EventLevel ,
									short EventType , BSTR  EventDesc , DATE GeneratedDT , DATE ClearedDT , long  ClearedBy , long AckedBy , double  Volume ,
									double  Value , double  ProductVolume ,	double  ProductLevel , double  WaterLevel , double  Temperature );
typedef long (WINAPI *typeDeleteLogEvent)( long ID );
typedef long (WINAPI *typeGetNextLogEventEvent)(long* pLogEventID , short* pDeviceType , long* pDeviceID , long* pDeviceNumber ,	PBSTR pDeviceName , short* pEventLevel ,
								     short* pEventType , PBSTR pEventDesc , DATE* pGeneratedDT , DATE* pClearedDT , long* pClearedBy , long* pAckedBy , double* pVolume ,
								     double* pValue , double* pProductVolume , double* pProductLevel , double* pWaterLevel , double* pTemperature);
typedef long (WINAPI *typeClearLogEvent)( long ID  , long ClientID );
typedef long (WINAPI *typeAckLogEvent)( long ID  , long ClientID );
typedef long (WINAPI *typeGetSensorByNumber)( long Number , long* pID );
typedef long (WINAPI *typeGetSensorByName)( BSTR Name , long* pID ) ;
typedef long (WINAPI *typeSetSensorProperties)(long ID , long Number, BSTR Name , long PortID , short Type, short Address , short SensorNo );
typedef long (WINAPI *typeSetSensorStatus)(long ID , short State , short IsResponding );
typedef long (WINAPI *typeGetSensorStatus)(long ID , short* pState , short* pIsResponding );
typedef long (WINAPI *typeDeleteSensor)( long ID ) ;
typedef long (WINAPI *typeSetLogPath)(BSTR Path);
typedef long (WINAPI *typeLog)(BSTR Text);
typedef long (WINAPI *typeSetClientType)( long ClientKey ) ;
typedef long (WINAPI *typeGetNextSaleItemEvent)(long* pSaleItemID, long* pProductID, long* pProductNumber, PBSTR pProductName, __int64* pProductTag, long* pProductGroup, PBSTR pProductGroupName, PBSTR pBarcode,
								 long* pPumpID, long* pPumpNumber, PBSTR pPumpName,
								 long* pAttendantID, long* pAttendantNumber, PBSTR pAttendantName, __int64* pAttendantTag,
								 long* pCardClientID, long* pCardClientNumber, PBSTR pCardClientName, __int64* pCardClientTag,
								 short* pPriceLevel, double* pPrice, double* pQuantity, DATE* pAddedDT, DATE* pClearedDT,
								 long* pLockedBy, long* pClearedBy, short* pLoggedDB, short* pLoggedVolumetric,
								 PBSTR pPlate, PBSTR pDriverID, PBSTR pExtTransactionID, PBSTR pAuthID, short* pAuthType);
typedef long (WINAPI *typeGetProductByNumber)(long Number, long* pID);
typedef long (WINAPI *typeGetProductByName)(BSTR Name, long* pID);
typedef long (WINAPI *typeGetProductProperties)(long ID, long* pNumber, PBSTR pName, PBSTR pTag, short* pEnabled, PBSTR pShortName,
                                 PBSTR pBarcode, double* pPrice1, double* pPrice2, long* pProductGroup);
typedef long (WINAPI *typeSetProductProperties)(long ID, long Number, BSTR Name, BSTR Tag, short Enabled, BSTR ShortName, 
	                             BSTR Barcode, double Price1, double Price2, long ProductGroup);
typedef long (WINAPI *typeDeleteProduct)(long ID);
typedef long (WINAPI *typeGetProductsCount)(long* pCount, long Number, BSTR Name, BSTR ShortName, BSTR Tag, BSTR Barcode, long ProductGroup);
typedef long (WINAPI *typeGetProductByOrdinal)(long Index, long* pID, long Number, BSTR Name, BSTR ShortName, BSTR Tag, BSTR Barcode, long ProductGroup);
typedef long (WINAPI *typeDeleteSaleItem)(long ID);

//--------------------------------------- Métodos MT ----------------------------------------//


typedef long (WINAPI *typeServerVersionMT)(CEZCLProcess* pCLProcess ,  PBSTR pName ) ;
typedef long (WINAPI *typeClientLogonMT)(CEZCLProcess** ppCLProcess ,  long ClientID , short ClientType , HANDLE Event , HWND hWnd, unsigned int wMsg) ;
typedef long (WINAPI *typeClientLogonExMT)(CEZCLProcess** ppCLProcess ,  long ClientID , short ClientType , BSTR ServerName , unsigned short CallPortNo , unsigned short EventsPortNo , long CallTimeout, HANDLE Event , HWND hWnd, unsigned int wMsg) ;
typedef long (WINAPI *typeClientLogoffMT)(CEZCLProcess** ppCLProcess ) ;
typedef long (WINAPI *typeClientStatusMT)(CEZCLProcess* pCLProcess ,  short* pPumpsReserved , short* pdeliveriesLocked ) ;
typedef long (WINAPI *typeGetLicenseTypeMT)(CEZCLProcess* pCLProcess ,  short* pLicenseType ) ;
typedef long (WINAPI *typeFireClientEventMT)(CEZCLProcess* pCLProcess ,  long EventID , BSTR EventStr ) ;
typedef long (WINAPI *typeCheckForManagementFtnMT)(CEZCLProcess** ppCLProcess);
typedef long (WINAPI *typeTestConnectionMT)(CEZCLProcess* pCLProcess ) ;
typedef long (WINAPI *typeFireEventsMT)(CEZCLProcess* pCLProcess);
typedef long (WINAPI *typeProcessEventsMT)(CEZCLProcess* pCLProcess ) ;
typedef long (WINAPI *typeGetEventsCountMT)(CEZCLProcess* pCLProcess ,  long* pCount ) ;
typedef long (WINAPI *typeGetNextEventTypeMT)(CEZCLProcess* pCLProcess ,  short* pType ) ;
typedef long (WINAPI *typeDiscardNextEventMT)(CEZCLProcess* pCLProcess ) ;
typedef long (WINAPI *typeGetNextPumpEventMT)(CEZCLProcess* pCLProcess ,  long* pPumpID, short* pPumpNumber, short* pState, short* pReservedFor, long* pReservedBy, long* pHoseID ,
							   short* pHoseNumber, long* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume, 
							   double* pValue, short* pStackSize ) ;
typedef long (WINAPI *typeGetNextDeliveryEventMT)(CEZCLProcess* pCLProcess ,  long* pDeliveryID , long* pPumpID, short* pPumpNumber, long* pHoseID, short* pHoseNumber , 
								long* pGradeID, PBSTR pGradeName ,PBSTR pShortGradeName, short* pPriceLevel, double* pPrice, double* pVolume, double* pValue, 
								short* pDeliveryState , short* pDeliveryType, long* pLockedBy, long* pReservedBy, long* pAge , DATE* pCompletedDT , long* pAttendantID ) ;
typedef long (WINAPI *typeGetNextServerEventMT)(CEZCLProcess* pCLProcess ,  long* pEventID, PBSTR pEventText ) ;
typedef long (WINAPI *typeGetNextClientEventMT)(CEZCLProcess* pCLProcess ,  long* pClientID, long* pEventID, PBSTR pEventText ) ;
typedef long (WINAPI *typeGetNextDBLogEventMT)(CEZCLProcess* pCLProcess ,  long* pEventType , long* pDeviceID , DATE* pEventDT , PBSTR pEventText ) ;
typedef long (WINAPI *typeGetNextDBLogDeliveryEventMT)(CEZCLProcess* pCLProcess ,  long* pDeliveryID, long* pHoseID, short* pDeliveryState, short* pDeliveryType, double* pVolume, short* pPriceLevel, 
							 double* pPrice, double* pValue, double* pVolume2, long* pReservedBy , long* pAttendantID, DATE* pDeliveryDT ) ;
typedef long (WINAPI *typeGetNextDBClearDeliveryEventMT)(CEZCLProcess* pCLProcess ,  long* pDeliveryID, short* pDeliveryType, long* pClearedBY, DATE* pClearedDT, long* pAttendantID ) ;
typedef long (WINAPI *typeGetNextDBStackDeliveryEventMT)(CEZCLProcess* pCLProcess ,  long* pDeliveryID ) ;
typedef long (WINAPI *typeGetNextDBHoseETotalsEventMT)(CEZCLProcess* pCLProcess ,  long* pHoseID , double* pVolume , double* pValue , double* pVolumeETot , double* pValueETot ) ;
typedef long (WINAPI *typeGetNextDBTriggerEventMT)(CEZCLProcess* pCLProcess ,  long* pTableID ,long* pRowID ) ;
typedef long (WINAPI *typeGetNextDBAttendantLogonEventMT)(CEZCLProcess* pCLProcess ,  long* pAttendantID ,long* pPumpID ) ;
typedef long (WINAPI *typeGetNextDBAttendantLogoffEventMT)(CEZCLProcess* pCLProcess ,  long* pAttendantID ) ;
typedef long (WINAPI *typeGetNextDBTankStatusEventMT)(CEZCLProcess* pCLProcess ,  long* pTankID , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
							          double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel ) ;
typedef long (WINAPI *typeGetClientsCountMT)( CEZCLProcess* pCLProcess , long* pCount ) ;
typedef long (WINAPI *typeGetPumpsCountMT)(CEZCLProcess* pCLProcess ,  long* pCount ) ;
typedef long (WINAPI *typeGetPumpByNumberMT)(CEZCLProcess* pCLProcess ,  long Number , long* pID ) ;
typedef long (WINAPI *typeGetPumpByNameMT)(CEZCLProcess* pCLProcess ,  BSTR Name , long* pID ) ;
typedef long (WINAPI *typeGetPumpByOrdinalMT)(CEZCLProcess* pCLProcess ,  long Index , long* pID ) ;
typedef long (WINAPI *typeGetPumpPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName, short* pPhysicalNumber, short* pSide, short* pAddress, short* pPriceLevel1,
						      short* pPriceLevel2, short* pPriceDspFormat, short* pVolumeDspFormat, short* pValueDspFormat, short* pType,  
						      long* pPortID, long* pAttendantID, short* pAuthMode, short* pStackMode, short* pPrepayAllowed, short* pPreauthAllowed ) ;
typedef long (WINAPI *typeSetPumpPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name, short PhysicalNumber, short Side, short Address, short PriceLevel1,
						      short PriceLevel2, short PriceDspFormat, short VolumeDspFormat, short ValueDspFormat, short Type, 
						      long PortID, long AttendantID, short AuthMode, short StackMode, short PrepayAllowed, short PreauthAllowed ) ;
typedef long (WINAPI *typeDeletePumpMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeGetPumpHosesCountMT)(CEZCLProcess* pCLProcess ,  long ID , long* pCount ) ;
typedef long (WINAPI *typeGetPumpHoseByNumberMT)(CEZCLProcess* pCLProcess ,  long ID , long Number , long* pHoseID ) ;
typedef long (WINAPI *typeGetPumpStatusMT)(CEZCLProcess* pCLProcess ,  long ID , short* pState, short* pReservedFor, long* pReservedBy, long* pHoseID, short* pHoseNumber , 
						   long* pGradeID, PBSTR pGradeName ,PBSTR pShortGradeName, short* pPriceLevel , double* pPrice , double* pVolume , double* pValue , 
						   short* pStackSize ) ;
typedef long (WINAPI *typeGetPumpStatusExMT)( CEZCLProcess* pCLProcess , long ID , long* pPumpNumber, PBSTR pPumpName, long* pPhysicalNumber, 
							   short* pState, short* pReservedFor, long* pReservedBy, 
							   long* pHoseID, long* pHoseNumber , long* pHosePhysicalNumber , 
							   long* pGradeID , long* pGradeNumber , PBSTR pGradeName, PBSTR pShortGradeName, 
							   short* pPriceLevel , double* pPrice , double* pVolume , double* pValue , short* pStackSize , __int64* pTag , 
							   long* pAttendantID , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							   long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag ) ;

typedef long (WINAPI *typeGetPumpStatusEx2MT)( CEZCLProcess* pCLProcess , long ID , long* pPumpNumber, PBSTR pPumpName, long* pPhysicalNumber, 
							  short* pState, short* pReservedFor, long* pReservedBy, 
							  long* pHoseID, long* pHoseNumber , long* pHosePhysicalNumber , 
							  long* pGradeID , long* pGradeNumber , PBSTR pGradeName, PBSTR pShortGradeName, 
							  short* pPriceLevel , double* pPrice , double* pVolume , double* pValue , short* pStackSize , __int64* pTag , 
							  long* pAttendantID , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							  long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag , 
							  double* pCurFlowRate , double* pPeakFlowRate ) ;

typedef long (WINAPI *typeGetPumpDeliveryPropertiesMT)(CEZCLProcess* pCLProcess ,  long ID , short Index , long* pDeliveryID , short* pType , short* pState, long* pHoseID, 
									   short* pHoseNum, long* pGradeID , PBSTR pGradeName ,PBSTR pShortGradeName, short* pPriceLevel, double* pPrice , double* pVolume , 
									   double* pValue , long* pLockedBy , long* pReservedBy , long* pAge , DATE* pCompletedDT , long* pAttendantID  ) ;
typedef long (WINAPI *typeGetPumpDeliveryPropertiesExMT)(CEZCLProcess* pCLProcess ,  long ID , short Index , long* pDeliveryID , short* pType , short* pState, long* pHoseID, short* pHoseNum, long* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName , 
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , long* pLockedBy , 
									    long* pReservedBy , long* pAge , DATE* pCompletedDT , long* pAttendantID , double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag ) ;
typedef long (WINAPI *typeGetPumpDeliveryPropertiesEx2MT)( CEZCLProcess* pCLProcess , long ID , short Index , long* pDeliveryID , short* pType , short* pState, long* pHoseID, short* pHoseNum, long* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName , 
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , long* pLockedBy , 
									    long* pReservedBy , long* pAge , DATE* pCompletedDT , long* pAttendantID , 
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , long * pDuration ) ;
typedef long (WINAPI *typeGetPumpDeliveryPropertiesEx3MT)( CEZCLProcess* pCLProcess , long ID , short Index , long* pDeliveryID , short* pType , short* pState, 
										   long* pHoseID, short* pHoseNum, 
										   long* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName , 
											short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , long* pLockedBy , 
											long* pReservedBy , long* pAge , DATE* pCompletedDT , long* pAttendantID , 
											double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
											double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
											__int64* pTag , long * pDuration , long* pCardClientID ) ;
typedef long (WINAPI *typePrepayReserveMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typePrepayCancelMT)(CEZCLProcess* pCLProcess ,  long ID  ) ;
typedef long (WINAPI *typePrepayAuthoriseMT)(CEZCLProcess* pCLProcess ,  long ID , short LimitType , double Value , short Hose , short PriceLevel ) ;
typedef long (WINAPI *typePreauthReserveMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typePreauthCancelMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typePreauthAuthoriseMT)(CEZCLProcess* pCLProcess ,  long ID , short LimitType , double Value , short Hose , short PriceLevel ) ;
typedef long (WINAPI *typeLoadPresetMT)(CEZCLProcess* pCLProcess ,  long ID , short LimitType , double Value , short Hose , short PriceLevel ) ;
typedef long (WINAPI *typeLoadPresetWithPriceMT)(CEZCLProcess* pCLProcess ,  long ID , short LimitType , double Value , short Hose , short PriceLevel , double Price ) ;
typedef long (WINAPI *typeTagAuthoriseMT)(CEZCLProcess* pCLProcess ,  long ID , __int64 Tag , short LimitType , double Value , short Hose , short PriceLevel ) ;
typedef long (WINAPI *typePaymentReserveMT)( CEZCLProcess* pCLProcess , long ID , long TermID , BSTR TermHash ) ;
typedef long (WINAPI *typePaymentCancelMT)( CEZCLProcess* pCLProcess , long ID , long TermID , BSTR TermHash ) ;
typedef long (WINAPI *typePaymentAuthoriseMT)( CEZCLProcess* pCLProcess , long ID , long TermID , BSTR TermHash ,
							  long AttendantID , __int64 AttendantTag , 
							  long CardClientID , __int64 CardClientTag , 
							  short AuthType , __int64 ExtTag ,
							  short GradeType , short PriceType  , short PriceLevel , double Price , 
							  short PresetType , double Value , short Hose ,
							  double Odometer , double Odometer2 , BSTR Plate , 
							  BSTR ExtTransactionID , BSTR DriverID , BSTR AuthorisationID ) ;
typedef long (WINAPI *typeAttendantAuthoriseMT)(CEZCLProcess* pCLProcess ,  long ID , long AttendantID ) ;
typedef long (WINAPI *typeAuthoriseMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeCancelAuthoriseMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeTempStopMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeReAuthoriseMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeTerminateDeliveryMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeStackCurrentDeliveryMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeGetDensityMT)( CEZCLProcess* pCLProcess , long ID , double* pDensity ) ;
typedef long (WINAPI *typeEnablePumpMT)( CEZCLProcess* pCLProcess , long ID ) ;
typedef long (WINAPI *typeDisablePumpMT)( CEZCLProcess* pCLProcess , long ID ) ;
typedef long (WINAPI *typeGetHosesCountMT)(CEZCLProcess* pCLProcess ,  long* pCount ) ;
typedef long (WINAPI *typeGetHoseByOrdinalMT)(CEZCLProcess* pCLProcess ,  long Index , long* pID ) ;
typedef long (WINAPI *typeGetHosePropertiesMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, long* pPumpID ,long* pTankID , long* pPhysicalNumber, 
		                      double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue ,
				              double* pMtrElecVolume ) ;
typedef long (WINAPI *typeSetHosePropertiesMT)(CEZCLProcess* pCLProcess , long ID , long Number,long PumpID, long TankID , long PhysicalNumber, 
		                      double MtrTheoValue , double MtrTheoVolume ,double MtrElecValue ,
				              double MtrElecVolume ) ;
typedef long (WINAPI *typeGetHoseSummaryMT)(CEZCLProcess* pCLProcess , 	long ID , long* pNumber, long* pPhysicalNumber,
							long* pPumpID, long* pPumpNumber, PBSTR pPumpName,
							long* pTankID, long* pTankNumber, PBSTR pTankName,
							long* pGradeID , long* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
		                    double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue , double* pMtrElecVolume ) ;
typedef long (WINAPI *typeGetHoseSummaryExMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, long* pPhysicalNumber,
							long* pPumpID, long* pPumpNumber, PBSTR pPumpName,
							long* pTankID, long* pTankNumber, PBSTR pTankName,
							long* pGradeID , long* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
		                    double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue , double* pMtrElecVolume ,
							double* pPrice1 , double* pPrice2 , short* pEnabled ) ;
typedef long (WINAPI *typeDeleteHoseMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeGetDeliveriesCountMT)(CEZCLProcess* pCLProcess ,  long* pCount ) ;
typedef long (WINAPI *typeGetDeliveryByOrdinalMT)(CEZCLProcess* pCLProcess ,  long Index , long* pID ) ;
typedef long (WINAPI *typeGetAllDeliveriesCountMT)(CEZCLProcess* pCLProcess ,  long* pCount )  ;
typedef long (WINAPI *typeGetAllDeliveryByOrdinalMT)(CEZCLProcess* pCLProcess ,  long Index , long* pID ) ;

typedef long (WINAPI *typeAckDeliveryDBLogMT)(CEZCLProcess* pCLProcess , long ID ) ; 
typedef long (WINAPI *typeGetDeliveryIDByOrdinalNotLoggedMT)(CEZCLProcess* pCLProcess , long Ordinal , long* pID ) ;
typedef long (WINAPI *typeGetDeliveriesCountNotLoggedMT)(CEZCLProcess* pCLProcess , long* pCount ) ;

typedef long (WINAPI *typeDeliveriesCountFilteredMT)(CEZCLProcess* pCLProcess, long* pCount, long PumpID, long HoseID, long GradeID, long TankID, long LockedBy, long ReservedBy, short State, short Type, __int64 Tag, long AttendantID, long CardClientID);
typedef long (WINAPI *typeGetDeliveryIDByOrdinalFileteredMT)(CEZCLProcess* pCLProcess, long Ordinal, long* pID, long PumpID, long HoseID, long GradeID, long TankID, long LockedBy, long ReservedBy, short State, short Type, __int64 Tag, long AttendantID, long CardClientID);

typedef long (WINAPI *typeAckDeliveryVolLogMT)(CEZCLProcess* pCLProcess , long ID ) ; 
typedef long (WINAPI *typeGetDeliveryIDByOrdinalNotVolLoggedMT)(CEZCLProcess* pCLProcess , long Ordinal , long* pID ) ;
typedef long (WINAPI *typeGetDeliveriesCountNotVolLoggedMT)(CEZCLProcess* pCLProcess , long* pCount ) ;

typedef long (WINAPI *typeGetDeliveryPropertiesMT)(CEZCLProcess* pCLProcess ,  long ID , long* pHoseID ,short* pState ,short* pType ,double* pVolume ,
								   short* pPriceLevel ,double* pPrice ,double* pValue ,double* pVolume2 , 
								   DATE* pCompletedDT ,long* pLockedBy , long* pReservedBy , long* pAttendantID , long* pAge ) ;
typedef long (WINAPI *typeGetDeliveryPropertiesExMT)(CEZCLProcess* pCLProcess ,  long ID , long* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                           double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, long* pReservedBy , long* pAttendantID , long* pAge , 
								   DATE* pClearedDT ,double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag ) ;
typedef long (WINAPI *typeGetDeliveryPropertiesEx2MT)( CEZCLProcess* pCLProcess , long ID , long* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, long* pReservedBy , 
										long* pAttendantID , long* pAge , DATE* pClearedDT ,
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , long * pDuration ) ;
typedef long (WINAPI *typeGetDeliveryPropertiesEx3MT)( CEZCLProcess* pCLProcess , long ID , long* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, long* pReservedBy , 
										long* pAttendantID , long* pAge , DATE* pClearedDT ,
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , long * pDuration , long* pCardClientID ) ;
typedef long (WINAPI *typeGetDeliveryPropertiesEx4MT)( CEZCLProcess* pCLProcess , long ID , long* pHoseID ,short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, long* pReservedBy , 
										long* pAttendantID , long* pAge , DATE* pClearedDT ,
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , long * pDuration , long* pCardClientID , double* pPeakFlowRate ) ;

typedef long (WINAPI *typeSetDeliveryPropertiesEx4MT)( CEZCLProcess* pCLProcess , long ID , long HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,long LockedBy, 
								   long ReservedBy , long AttendantID , long Age , DATE ClearedDT , 
								   double OldVolumeETot , double OldVolume2ETot , double OldValueETot , 
								   double NewVolumeETot , double NewVolume2ETot , double NewValueETot , 
								   __int64 Tag , long Duration , long CardClientID, double PeakFlowRate ) ;
typedef long (WINAPI *typeGetPumpDeliveryPropertiesEx4MT)( CEZCLProcess* pCLProcess , long ID , short Index , long* pDeliveryID , short* pType , short* pState, 
										   long* pHoseID, short* pHoseNum, 
										   long* pGradeID, PBSTR pGradeName, PBSTR pShortGradeName , 
								        short* pPriceLevel, double* pPrice , double* pVolume , double* pValue , long* pLockedBy , 
									    long* pReservedBy , long* pAge , DATE* pCompletedDT , long* pAttendantID , 
										double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
										double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
										__int64* pTag , long * pDuration , long* pCardClientID , double* pPeakFlowRate ) ;
typedef long (WINAPI *typeSetDeliveryPropertiesMT)(CEZCLProcess* pCLProcess ,  long ID , long HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2, DATE CompletedDT ,long LockedBy, long ReservedBy , 
								   long AttendantID , long Age ) ;
typedef long (WINAPI *typeSetDeliveryPropertiesExMT)(CEZCLProcess* pCLProcess ,  long ID , long HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,long LockedBy, 
								   long ReservedBy , long AttendantID , long Age , DATE ClearedDT , double VolumeETot , double Volume2ETot , double ValueETot , __int64 Tag ) ;
typedef long (WINAPI *typeSetDeliveryPropertiesEx2MT)( CEZCLProcess* pCLProcess , long ID , long HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,long LockedBy, 
								   long ReservedBy , long AttendantID , long Age , DATE ClearedDT , 
								   double OldVolumeETot , double OldVolume2ETot , double OldValueETot , 
								   double NewVolumeETot , double NewVolume2ETot , double NewValueETot , 
								   __int64 Tag , long Duration ) ;
typedef long (WINAPI *typeSetDeliveryPropertiesEx3MT)( CEZCLProcess* pCLProcess , long ID , long HoseID ,short State ,short Type ,double Volume ,short PriceLevel ,
								   double Price ,double Value ,double Volume2 , DATE CompletedDT ,long LockedBy, 
								   long ReservedBy , long AttendantID , long Age , DATE ClearedDT , 
								   double OldVolumeETot , double OldVolume2ETot , double OldValueETot , 
								   double NewVolumeETot , double NewVolume2ETot , double NewValueETot , 
								   __int64 Tag , long Duration , long CardClientID ) ;
typedef long (WINAPI *typeGetDeliverySummaryMT)(CEZCLProcess* pCLProcess ,  long ID , long* pHoseID ,long* pHoseNumber, long* pHosePhysicalNumber,
	  							long* pPumpID, long* pPumpNumber, PBSTR  pPumpName,
								long* pTankID, long* pTankNumber, PBSTR  pTankName,
								long* pGradeID , long* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
								short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
								double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, 
								long* pReservedBy , long* pAttendantID , long* pAge ,DATE* pClearedDT ,
								double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag) ;
typedef long (WINAPI *typeGetDeliverySummaryExMT)( CEZCLProcess* pCLProcess , long ID , long* pHoseID ,long* pHoseNumber, long* pHosePhysicalNumber,
	  							long* pPumpID, long* pPumpNumber, PBSTR  pPumpName,
								long* pTankID, long* pTankNumber, PBSTR  pTankName,
								long* pGradeID , long* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                        double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, 
								long* pReservedBy , long* pAttendantID , long* pAge ,DATE* pClearedDT ,
								double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
								double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
								__int64* pTag , long * pDuration ) ;
typedef long (WINAPI *typeGetDeliverySummaryEx2MT)( CEZCLProcess* pCLProcess , long ID , long* pHoseID ,long* pHoseNumber, long* pHosePhysicalNumber,
	  							long* pPumpID, long* pPumpNumber, PBSTR  pPumpName,
								long* pTankID, long* pTankNumber, PBSTR  pTankName,
								long* pGradeID , long* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                        double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, 
								long* pReservedBy , long* pAttendantID , long* pAge ,DATE* pClearedDT ,
								double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
								double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
								__int64* pTag , long * pDuration , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
								long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag ) ;

typedef long (WINAPI *typeGetDeliverySummaryEx3MT)( CEZCLProcess* pCLProcess , long ID , long* pHoseID ,long* pHoseNumber, long* pHosePhysicalNumber,
	  							long* pPumpID, long* pPumpNumber, PBSTR  pPumpName,
								long* pTankID, long* pTankNumber, PBSTR  pTankName,
								long* pGradeID , long* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
							    short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
		                        double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT ,long* pLockedBy, 
								long* pReservedBy , long* pAttendantID , long* pAge ,DATE* pClearedDT ,
								double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
								double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
								__int64* pTag , long * pDuration , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
								long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag , double* pPeakFlowRate ) ;

typedef long (WINAPI *typeGetDeliverySummaryEx4MT)(CEZCLProcess* pCLProcess, long ID, long* pHoseID, long* pHoseNumber, long* pHosePhysicalNumber,
								long* pPumpID, long* pPumpNumber, PBSTR  pPumpName,
								long* pTankID, long* pTankNumber, PBSTR  pTankName,
								long* pGradeID, long* pGradeNumber, PBSTR  pGradeName, PBSTR  pGradeShortName, PBSTR  pGradeCode,
								short* pState, short* pType, double* pVolume, short* pPriceLevel,
								double* pPrice, double* pValue, double* pVolume2, DATE* pCompletedDT, long* pLockedBy,
								long* pReservedBy, long* pAttendantID, long* pAge, DATE* pClearedDT,
								double* pOldVolumeETot, double* pOldVolume2ETot, double* pOldValueETot,
								double* pNewVolumeETot, double* pNewVolume2ETot, double* pNewValueETot,
								__int64* pTag, long * pDuration, long* pAttendantNumber, PBSTR pAttendantName, __int64* pAttendantTag, PBSTR pAttendantIDNumber,
								long* pCardClientID, long* pCardClientNumber, PBSTR pCardClientName, __int64* pCardClientTag, PBSTR pCardClientIDNumber, double* pPeakFlowRate);


typedef long (WINAPI *typeLockDeliveryMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeUnlockDeliveryMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeClearDeliveryMT)(CEZCLProcess* pCLProcess ,  long ID , short Type ) ;
typedef long (WINAPI *typeLockAndClearDeliveryMT)(CEZCLProcess* pCLProcess ,  long ID , short Type ) ;
typedef long (WINAPI *typeGetDurationMT)( CEZCLProcess* pCLProcess , long ID , long* pDuration ) ;
typedef long (WINAPI *typeSetDeliveryExtMT)( CEZCLProcess* pCLProcess , long ID , BSTR Plate , double Odometer , double Odometer2 , BSTR ExtTransactionID , BSTR DriverID , BSTR AuthID, short AuthType ) ;
typedef long (WINAPI *typeGetDeliveryExtMT)( CEZCLProcess* pCLProcess , long ID , PBSTR pPlate , double* pOdometer , double* pOdometer2 , PBSTR pExtTransactionID , PBSTR pDriverID , PBSTR pAuthID, short* pAuthType) ;
typedef long (WINAPI *typeGetGradesCountMT)(CEZCLProcess* pCLProcess ,  long* pCount ) ;
typedef long (WINAPI *typeGetGradeByNumberMT)(CEZCLProcess* pCLProcess ,  long Number , long* pID ) ;
typedef long (WINAPI *typeGetGradeByNameMT)(CEZCLProcess* pCLProcess ,  BSTR Name , long* pID ) ;
typedef long (WINAPI *typeGetGradeByOrdinalMT)(CEZCLProcess* pCLProcess ,  long Index , long* pID ) ;
typedef long (WINAPI *typeGetGradePropertiesMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pCode ) ;
typedef long (WINAPI *typeSetGradePropertiesMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name , BSTR ShortName , BSTR Code  ) ;
typedef long (WINAPI *typeGetGradePropertiesExMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pCode , short* pType ) ;
typedef long (WINAPI *typeSetGradePropertiesExMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name , BSTR ShortName , BSTR Code , short Type  ) ;
typedef long (WINAPI *typeDeleteGradeMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeSetGradePriceMT)(CEZCLProcess* pCLProcess ,  long ID , short Level , double Price ) ;
typedef long (WINAPI *typeGetGradePriceMT)(CEZCLProcess* pCLProcess ,  long ID , short Level , double* pPrice ) ;
typedef long (WINAPI *typeGetTanksCountMT)(CEZCLProcess* pCLProcess ,  long* pCount ) ;
typedef long (WINAPI *typeGetTankByNumberMT)(CEZCLProcess* pCLProcess ,  long Number , long* pID ) ;
typedef long (WINAPI *typeGetTankByNameMT)(CEZCLProcess* pCLProcess ,  BSTR Name , long* pID ) ;
typedef long (WINAPI *typeGetTankByOrdinalMT)(CEZCLProcess* pCLProcess ,  long Index , long* pID ) ;



typedef long (WINAPI *typeGetTankPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , long* pGradeID , short* pType , double* pCapacity , double* pDiameter , 
							  double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
							  double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, long* pGaugeID, short* pProbeNo ) ;
typedef long (WINAPI *typeSetTankPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name , long GradeID , short Type , double Capacity , double Diameter , double TheoVolume , 
		                      double GaugeVolume , double GaugeTCVolume ,double GaugeUllage ,double GaugeTemperature , double GaugeLevel , 
							  double GaugeWaterVolume, double GaugeWaterLevel, long GaugeID , short ProbeNo ) ;

typedef long (WINAPI *typeGetTankPropertiesExMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , long* pGradeID , short* pType , double* pCapacity , double* pDiameter , 
							  double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
							  double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, long* pGaugeID, short* pProbeNo , long* pGaugeAlarmsMask ) ;
typedef long (WINAPI *typeSetTankPropertiesExMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name , long GradeID , short Type , double Capacity , double Diameter , double TheoVolume , 
		                      double GaugeVolume , double GaugeTCVolume ,double GaugeUllage ,double GaugeTemperature , double GaugeLevel , 
							  double GaugeWaterVolume, double GaugeWaterLevel, long GaugeID , short ProbeNo , long GaugeAlarmsMask ) ;

typedef long (WINAPI *typeGetTankSummaryMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , long* pGradeID , 
						   long* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode, 
						   short* pType , double* pCapacity , double* pDiameter , 
						   double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
						   double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, long* pGaugeID, short* pProbeNo ) ;

typedef long (WINAPI *typeGetTankSummaryExMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , long* pGradeID , 
						   long* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode, 
						   short* pType , double* pCapacity , double* pDiameter , 
						   double* pTheoVolume , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, double* pGaugeTemperature , 
						   double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel, long* pGaugeID, short* pProbeNo , 
						   short* pState , long* pGaugeAlarmsMask ) ;

typedef long (WINAPI *typeTankDropMT)(CEZCLProcess* pCLProcess ,  long ID , double Volume , DATE DropDT , BSTR Terminal , BSTR DocumentType , DATE DocumentDT  , BSTR DocumentFolio , double PEMEXVolume ) ;
typedef long (WINAPI *typeDeleteTankMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeGetPortsCountMT)(CEZCLProcess* pCLProcess ,  long* pCount ) ;
typedef long (WINAPI *typeGetPortByNumberMT)(CEZCLProcess* pCLProcess ,  long Number , long* pID ) ;
typedef long (WINAPI *typeGetPortByNameMT)(CEZCLProcess* pCLProcess ,  BSTR Name , long* pID ) ;
typedef long (WINAPI *typeGetPortByOrdinalMT)(CEZCLProcess* pCLProcess ,  long Index , long* pID ) ;
typedef long (WINAPI *typeGetPortPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , long* pProtocolID , short* pDeviceType , PBSTR pSerialNo ) ;
typedef long (WINAPI *typeSetPortPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name, long ProtocolID , short DeviceType , BSTR SerialNo ) ;
typedef long (WINAPI *typeDeletePortMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeGetAttendantsCountMT)(CEZCLProcess* pCLProcess ,  long* pCount ) ;
typedef long (WINAPI *typeGetAttendantByNumberMT)(CEZCLProcess* pCLProcess ,  long Number , long* pID ) ;
typedef long (WINAPI *typeGetAttendantByNameMT)(CEZCLProcess* pCLProcess ,  BSTR Name , long* pID ) ;
typedef long (WINAPI *typeGetAttendantByOrdinalMT)(CEZCLProcess* pCLProcess ,  long Index , long* pID ) ;
typedef long (WINAPI *typeGetAttendantPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pPassword , PBSTR pTag ) ; 
typedef long (WINAPI *typeSetAttendantPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name , BSTR ShortName , BSTR Password , BSTR Tag) ; 
typedef long (WINAPI *typeSetAttendantPropertiesExMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name , BSTR ShortName , BSTR Password , BSTR Tag , short ShiftAStart , short ShiftAEnd , short ShiftBStart , short ShiftBEnd , short Type )  ;
typedef long (WINAPI *typeGetAttendantPropertiesExMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , PBSTR pShortName , PBSTR pPassword , PBSTR pTag , short* pShiftAStart , short* pShiftAEnd , short* pShiftBStart , short* pShiftBEnd , short* pType ) ; 
typedef long (WINAPI *typeGetAttendantPropertiesEx2MT)(CEZCLProcess* pCLProcess, long ID, long* pNumber, PBSTR pName, PBSTR pShortName, PBSTR pPassword, PBSTR pTag, PBSTR pIDNumber, short* pShiftAStart, short* pShiftAEnd, short* pShiftBStart, short* pShiftBEnd, short* pType);
typedef long (WINAPI *typeSetAttendantPropertiesEx2MT)(CEZCLProcess* pCLProcess, long ID, long Number, BSTR Name, BSTR ShortName, BSTR Password, BSTR Tag, BSTR IDNumber, short ShiftAStart, short ShiftAEnd, short ShiftBStart, short ShiftBEnd, short Type);


typedef long (WINAPI *typeGetAttendantStateMT)(CEZCLProcess* pCLProcess , long ID , short* pType , short* pLoggedOn ) ;
typedef long (WINAPI *typeDeleteAttendantMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeAttendantLogonMT)(CEZCLProcess* pCLProcess ,  long ID , long PumpID ) ;
typedef long (WINAPI *typeAttendantLogoffMT)(CEZCLProcess* pCLProcess ,  long ID ) ;

typedef long (WINAPI *typeGetCardReadsCountMT)( CEZCLProcess* pCLProcess , long* pCount ) ;
typedef long (WINAPI *typeGetCardReadByNumberMT)( CEZCLProcess* pCLProcess , long Number , long* pID ) ;
typedef long (WINAPI *typeGetCardReadByNameMT)( CEZCLProcess* pCLProcess , BSTR Name , long* pID ) ;
typedef long (WINAPI *typeGetCardReadByOrdinalMT)( CEZCLProcess* pCLProcess , long Index , long* pID ) ;
typedef long (WINAPI *typeGetCardReadPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , long* pPumpID , short* pType , long* pParentID , __int64* pTag , DATE* pTimeStamp  )  ;
typedef long (WINAPI *typeSetCardReadPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name , long PumpID , short Type , long ParentID , __int64 Tag , DATE TimeStamp )  ;
typedef long (WINAPI *typeDeleteCardReadMT)( CEZCLProcess* pCLProcess , long ID ) ;
typedef long (WINAPI *typeGetCardClientsCountMT)( CEZCLProcess* pCLProcess , long* pCount ) ;
typedef long (WINAPI *typeGetCardClientByNumberMT)( CEZCLProcess* pCLProcess , long Number , long* pID ) ;
typedef long (WINAPI *typeGetCardClientByNameMT)( CEZCLProcess* pCLProcess , BSTR Name , long* pID ) ;
typedef long (WINAPI *typeGetCardClientByOrdinalMT)( CEZCLProcess* pCLProcess , long Index , long* pID ) ;
typedef long (WINAPI *typeGetCardClientPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , PBSTR pTag , short* pEnabled  )  ;
typedef long (WINAPI *typeSetCardClientPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name , BSTR Tag , short Enabled  )  ;
typedef long (WINAPI *typeSetCardClientPropertiesExMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name , BSTR Tag , short Enabled , short PriceLevel , BSTR Plate )  ;
typedef long (WINAPI *typeGetCardClientPropertiesExMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , PBSTR pTag , short* pEnabled , short* pPriceLevel , PBSTR pPlate )  ;
typedef long (WINAPI *typeSetCardClientPropertiesEx2MT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name , BSTR Tag , short Enabled , short PriceLevel , BSTR Plate , short GradeType, short CardType, short LimitType, double Limit, short EntryType, DATE ExpirationDate, long ParentID )  ;
typedef long (WINAPI *typeGetCardClientPropertiesEx2MT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , PBSTR pTag , short* pEnabled , short* pPriceLevel , PBSTR pPlate , short* pGradeType, short* pCardType, short* pLimitType, double* pLimit, short* pEntryType, DATE* pExpirationDate, long* pParentID )  ;
typedef long (WINAPI *typeGetCardClientPropertiesEx3MT)(CEZCLProcess* pCLProcess, long ID, long* pNumber, PBSTR pName, PBSTR pTag, short* pEnabled, short* pPriceLevel, PBSTR pPlate, PBSTR pIDNumber, PBSTR pShortName, PBSTR pPassword, short* pGradeType, short* pCardType, short* pLimitType, double* pLimit, short* pEntryType, DATE* pExpirationDate, long* pParentID);
typedef long (WINAPI *typeSetCardClientPropertiesEx3MT)(CEZCLProcess* pCLProcess, long ID, long Number, BSTR Name, BSTR Tag, short Enabled, short PriceLevel, BSTR Plate, BSTR IDNumber, BSTR ShortName, BSTR Password, short GradeType, short CardType, short LimitType, double Limit, short EntryType, DATE ExpirationDate, long ParentID);
typedef long (WINAPI *typeDeleteCardClientMT)( CEZCLProcess* pCLProcess , long ID ) ;

typedef long (WINAPI *typeAllStopMT)(CEZCLProcess* pCLProcess ) ;
typedef long (WINAPI *typeAllAuthoriseMT)(CEZCLProcess* pCLProcess ) ;
typedef long (WINAPI *typeAllReAuthoriseMT)(CEZCLProcess* pCLProcess ) ;
typedef long (WINAPI *typeAllStopIfIdleMT)(CEZCLProcess* pCLProcess ) ;
typedef long (WINAPI *typeReadAllTanksMT)(CEZCLProcess* pCLProcess ) ;
typedef long (WINAPI *typeGetAllPumpStatusesMT)(CEZCLProcess* pCLProcess ,  PBSTR pStates , PBSTR pCurrentHoses , PBSTR pDeliveriesCount ) ; 
typedef long (WINAPI *typeGetIniValueMT)(CEZCLProcess* pCLProcess ,  BSTR Section , BSTR Key , PBSTR pValue ) ; 
typedef long (WINAPI *typeSetIniValueMT)(CEZCLProcess* pCLProcess ,  BSTR Section , BSTR Key , BSTR Value ) ; 
typedef long (WINAPI *typeGetIniValueExMT)( CEZCLProcess* pCLProcess , BSTR FileName , BSTR Section , BSTR Key , PBSTR pValue ) ; 
typedef long (WINAPI *typeSetIniValueExMT)( CEZCLProcess* pCLProcess , BSTR FileName , BSTR Section , BSTR Key , BSTR Value ) ; 
typedef long (WINAPI *typeSetNextDeliveryIDMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeRemovePortMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeLicenseStatusMT)(CEZCLProcess* pCLProcess ) ;
typedef long (WINAPI *typeCheckSocketClosedMT)(CEZCLProcess* pCLProcess ,  LPARAM lParam ) ;

typedef long (WINAPI *typeGetCardTypeMT)( CEZCLProcess* pCLProcess , BSTR Tag , short* pTagType , long* pID, PBSTR pName, long* pNumber  ) ;
typedef long (WINAPI *typeFindCardMT)(CEZCLProcess* pCLProcess, BSTR Tag, short* pCardType, short* pTagType, long* pID, PBSTR pName, long* pNumber);


// *** new APIS
typedef long (WINAPI *typeGetNextPumpEventExMT)(CEZCLProcess* pCLProcess ,  long* pPumpID, short* pPumpNumber, short* pState, short* pReservedFor, long* pReservedBy, long* pHoseID ,
							    short* pHoseNumber,long* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume, 
							    double* pValue, short* pStackSize , PBSTR pPumpName , short* pPhysicalNumber , short* pSide , short* pAddress, 
								short* pPriceLevel1 , short* pPriceLevel2 , short* pType , long* pPortID , short* pAuthMode , short* pStackMode ,  short* pPrepayAllowed, 
								short* pPreauthAllowed ,  short* pPriceFormat , short* pValueFormat , short* pVolumeFormat  ) ;

typedef long (WINAPI *typeGetNextDeliveryEventExMT)(CEZCLProcess* pCLProcess ,  long* pDeliveryID , long* pPumpID, short* pPumpNumber, long* pHoseID, short* pHoseNumber , 
								    long* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel, double* pPrice, 
									double* pVolume, double* pValue, short* pDeliveryState , 
								    short* pDeliveryType, long* pLockedBy, long* pReservedBy, long* pAge , DATE* pCompletedDT , 
									long* pAttendantID, double* pVolumeETot , double* pVolume2ETot , double* pValueETot , __int64* pTag) ;

typedef long (WINAPI *typeGetNextPumpEventEx2MT)( CEZCLProcess* pCLProcess , long* pPumpID, long* pPumpNumber, short* pState, short* pReservedFor, long* pReservedBy, long* pHoseID ,
							    long* pHoseNumber, long* pHosePhysicalNumber,long* pGradeID,long* pGradeNumber, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume, 
							    double* pValue, short* pStackSize , PBSTR pPumpName , long* pPhysicalNumber , short* pSide , short* pAddress, 
								short* pPriceLevel1 , short* pPriceLevel2 , short* pType , long* pPortID , short* pAuthMode , short* pStackMode ,  short* pPrepayAllowed, 
								short* pPreauthAllowed ,  short* pPriceFormat , short* pValueFormat , short* pVolumeFormat , __int64* pTag , 
							    long* pAttendantID , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							    long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag ) ;

typedef long (WINAPI *typeGetNextPumpEventEx3MT)( CEZCLProcess* pCLProcess , long* pPumpID, long* pPumpNumber, short* pState, short* pReservedFor, long* pReservedBy, long* pHoseID ,
							    long* pHoseNumber, long* pHosePhysicalNumber,long* pGradeID,long* pGradeNumber, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel , double* pPrice, double* pVolume, 
							    double* pValue, short* pStackSize , PBSTR pPumpName , long* pPhysicalNumber , short* pSide , short* pAddress, 
								short* pPriceLevel1 , short* pPriceLevel2 , short* pType , long* pPortID , short* pAuthMode , short* pStackMode ,  short* pPrepayAllowed, 
								short* pPreauthAllowed ,  short* pPriceFormat , short* pValueFormat , short* pVolumeFormat , __int64* pTag , 
							    long* pAttendantID , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
							    long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag , 
								double* pCurFlowRate , double* pPeakFlowRate ) ;


typedef long (WINAPI *typeGetNextDeliveryEventEx2MT)( CEZCLProcess* pCLProcess , long* pDeliveryID , long* pPumpID, short* pPumpNumber, long* pHoseID, short* pHoseNumber , 
								     long* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel, double* pPrice, 
									 double* pVolume, double* pValue, short* pDeliveryState , 
								     short* pDeliveryType, long* pLockedBy, long* pReservedBy, long* pAge , DATE* pCompletedDT , 
									 long* pAttendantID, double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
									 double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
									 __int64* pTag , long* pDuration ) ;

typedef long (WINAPI *typeGetNextDeliveryEventEx3MT)( CEZCLProcess* pCLProcess , long* pDeliveryID , long* pPumpID, short* pPumpNumber, long* pHoseID, short* pHoseNumber , 
								     long* pGradeID, PBSTR pGradeName , PBSTR pShortGradeName, short* pPriceLevel, double* pPrice, 
									 double* pVolume, double* pValue, short* pDeliveryState , 
								     short* pDeliveryType, long* pLockedBy, long* pReservedBy, long* pAge , DATE* pCompletedDT , 
									 long* pAttendantID, 
									 double* pOldVolumeETot , double* pOldVolume2ETot , double* pOldValueETot , 
									 double* pNewVolumeETot , double* pNewVolume2ETot , double* pNewValueETot , 
									 __int64* pTag , long* pDuration , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
									 long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag ) ;

typedef long (WINAPI *typeGetNextDeliveryEventEx4MT)( CEZCLProcess* pCLProcess , 
									    long* pDeliveryID, long* pHoseID ,long* pHoseNumber, long* pHosePhysicalNumber,
	  									long* pPumpID, long* pPumpNumber, PBSTR pPumpName,
										long* pTankID, long* pTankNumber, PBSTR pTankName,
										long* pGradeID , long* pGradeNumber, PBSTR pGradeName, PBSTR pGradeShortName, PBSTR pGradeCode,
										short* pState ,short* pType ,double* pVolume ,short* pPriceLevel ,
										double* pPrice ,double* pValue ,double* pVolume2 , DATE* pCompletedDT , long* pLockedBy, 
										long* pReservedBy , long* pAttendantID , long* pAge , DATE* pClearedDT , 
										double* pOldVolumeETot, double* pOldVolume2ETot, double* pOldValueETot , 
										double* pNewVolumeETot, double* pNewVolume2ETot, double* pNewValueETot , 
										__int64* pTag , long* pDuration , long* pAttendantNumber , PBSTR pAttendantName, __int64* pAttendantTag ,
										long* pCardClientID , long* pCardClientNumber , PBSTR pCardClientName, __int64* pCardClientTag , double* pPeakFlowRate ) ;

typedef long (WINAPI *typeGetNextCardReadEventMT)( CEZCLProcess* pCLProcess , long* pCardReadID , long* pNumber, PBSTR pName , long* pPumpID , short* pType , long* pParentID , __int64* pTag , DATE* pTimeStamp ) ;
typedef long (WINAPI *typeGetNextDBHoseETotalsEventExMT)(CEZCLProcess* pCLProcess ,  long* pHoseID , double* pVolume , double* pValue , double* pVolumeETot , double* pValueETot , 
										 long* pHoseNumber , long* pHosePhysicalNumber , long* pPumpID , long* pPumpNumber , PBSTR pPumpName , 
										 long* pTankID , long* pTankNumber , PBSTR pTankName , long* pGradeID , PBSTR pGradeName ) ;
typedef long (WINAPI *typeGetNextDBTankStatusEventExMT)(CEZCLProcess* pCLProcess ,  long* pTankID , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, 
									    double* pGaugeTemperature , double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel , 
									    long* pTankNumber , PBSTR pTankName , long* pGradeID , PBSTR pGradeName , short*pType  , 
										double* pCapacity , double* pDiameter , long* pGaugeID , short* pProbeNo) ;

typedef long (WINAPI *typeGetNextDBTankStatusEventEx2MT)( CEZCLProcess* pCLProcess , long* pTankID , double* pGaugeVolume , double* pGaugeTCVolume, double* pGaugeUllage, 
									    double* pGaugeTemperature , double* pGaugeLevel , double* pGaugeWaterVolume, double* pGaugeWaterLevel , 
									    long* pTankNumber , PBSTR pTankName , long* pGradeID , PBSTR pGradeName , short*pType  , double* pCapacity , 
										double* pDiameter , long* pGaugeID , short* pProbeNo, short* pState , long* pAlarmsMask ) ;

typedef long (WINAPI *typeGetNextSerialPortEventMT)(CEZCLProcess* pCLProcess ,  long* pPortID , long* pZBID , short* pSlot , short* pResult , PBSTR pRxMsg ) ; 
typedef long (WINAPI *typeGetNextZBEventMT)(CEZCLProcess* pCLProcess ,  long* pPortID , long* pZBID , __int64* pZBAddress, short* pResult , short* pMsgType , PBSTR pRxMsg ) ; 
typedef long (WINAPI *typeGetNextUVEEventMT)(CEZCLProcess* pCLProcess ,  long* pPumpID , long* pPumpNumber , long* pHoseID , long* pHoseNumber , PBSTR pUVE ) ;
typedef long (WINAPI *typeGetZigBeeCountMT)(CEZCLProcess* pCLProcess ,  long* pCount ) ;
typedef long (WINAPI *typeGetZigBeeByNumberMT)(CEZCLProcess* pCLProcess ,  long Number , long* pID ) ;
typedef long (WINAPI *typeGetZigBeeByNameMT)(CEZCLProcess* pCLProcess ,  BSTR Name , long* pID ) ;
typedef long (WINAPI *typeGetZigBeeByOrdinalMT)(CEZCLProcess* pCLProcess ,  long Index , long* pID ) ;
typedef long (WINAPI *typeGetZigBeePropertiesMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , short* pDeviceType , PBSTR pSerialNumber , PBSTR pNodeIdentifier , long* pPortID ) ;
typedef long (WINAPI *typeSetZigBeePropertiesMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name , short DeviceType , BSTR SerialNumber , BSTR NodeIdentifier , long PortID ) ;
typedef long (WINAPI *typeDeleteZigBeeMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeGetHosePropertiesExMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, long* pPumpID ,long* pTankID , long* pPhysicalNumber, 
		                      double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue ,
				              double* pMtrElecVolume , short* pUVEAntenna ) ;

typedef long (WINAPI *typeSetHosePropertiesExMT)(CEZCLProcess* pCLProcess , long ID , long Number,long PumpID, long TankID , long PhysicalNumber, 
		                      double MtrTheoValue , double MtrTheoVolume ,double MtrElecValue ,
				              double MtrElecVolume , short UVEAntenna );

typedef long (WINAPI *typeSetHosePropertiesEx2MT)(CEZCLProcess* pCLProcess , long ID , long Number,long PumpID, long TankID , long PhysicalNumber, 
		                      double MtrTheoValue , double MtrTheoVolume ,double MtrElecValue ,
				              double MtrElecVolume , short UVEAntenna , double Price1 , double Price2 , short Enabled ) ;

typedef long (WINAPI *typeGetHosePropertiesEx2MT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, long* pPumpID ,long* pTankID , long* pPhysicalNumber, 
		                      double* pMtrTheoValue , double* pMtrTheoVolume ,double* pMtrElecValue ,
				              double* pMtrElecVolume , short* pUVEAntenna , double* pPrice1 , double* pPrice2 , short* pEnabled ) ;


typedef long (WINAPI *typeSetPumpPropertiesExMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name, short PhysicalNumber, short Side, short Address, short PriceLevel1,
						        short PriceLevel2, short PriceDspFormat, short VolumeDspFormat, short ValueDspFormat, short Type, 
						        long PortID, long AttendantID, short AuthMode, short StackMode, short PrepayAllowed, short PreauthAllowed , 
								long SlotZigBeeID , long MuxSlotZigBeeID , short PriceControl , short HasPreset ) ;
typedef long (WINAPI *typeGetPumpPropertiesExMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName, short* pPhysicalNumber, short* pSide, short* pAddress, short* pPriceLevel1,
						      short* pPriceLevel2, short* pPriceDspFormat, short* pVolumeDspFormat, short* pValueDspFormat, short* pType, 
						      long* pPortID, long* pAttendantID, short* pAuthMode, short* pStackMode, short* pPrepayAllowed, short* pPreauthAllowed ,
							  long* pSlotZigBeeID , long* pMuxSlotZigBeeID , short* pPriceControl , short* pHasPreset) ;
typedef long (WINAPI *typeCTFReserveMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeCTFCancelMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeCTFAuthoriseMT)(CEZCLProcess* pCLProcess ,  long ID , short LimitType , double Value , double Value2 , short Hose , short PriceLevel , BSTR UVE , short UVEType , short UVETimeout, short IBMPulserTimeout, short StopDelay ) ;
typedef long (WINAPI *typeGetSerialNoMT)(CEZCLProcess* pCLProcess ,  long ID , PBSTR pSerialNo ) ; 
typedef long (WINAPI *typeGetDeviceDetailsMT)(CEZCLProcess* pCLProcess ,  long ID , long ZBID , PBSTR pSerialNo , PBSTR pBootVersion , PBSTR pFirmwareVersion ) ;
typedef long (WINAPI *typeResetDeviceMT)(CEZCLProcess* pCLProcess ,  long ID , long ZBID ) ;
typedef long (WINAPI *typeRequestVersionMT)(CEZCLProcess* pCLProcess ,  long ID , long ZBID ) ;
typedef long (WINAPI *typeZBRegisterInterestMT)(CEZCLProcess* pCLProcess ,  long ID , long ZBID ) ; 
typedef long (WINAPI *typeZBExceptionRegisterInterestMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeZBHeartBeatRegisterInterestMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeSerialPortSendMT)(CEZCLProcess* pCLProcess ,  long ID , long ZBID , short Slot , short Type , BSTR TxMsg ) ;
typedef long (WINAPI *typeSerialPortConfigMT)(CEZCLProcess* pCLProcess ,  long ID , long ZBID , short Slot , short COMPort , long BPS , short DataBits , short Parity , short StopBits , short ResponseMaxLen , short ResponseTimeout , short ResponseInterCharTimeout ) ;
typedef long (WINAPI *typeZBSendMT)(CEZCLProcess* pCLProcess ,  long ID , long ZBID, __int64 ZBAddress, short MsgType , BSTR TxMsg ) ; 
typedef long (WINAPI *typeGetDeviceDetailsMT)(CEZCLProcess* pCLProcess ,  long ID , long ZBID , PBSTR pSerialNo , PBSTR pBootVersion , PBSTR pFirmwareVersion ) ;
typedef long (WINAPI *typeSetZBCoordPanMT)(CEZCLProcess* pCLProcess ,  long ID , __int64 Pan ) ;
typedef long (WINAPI *typeGetZBCoordPanMT)(CEZCLProcess* pCLProcess ,  long ID ) ;
typedef long (WINAPI *typeReadUVEMT)(CEZCLProcess* pCLProcess ,  long ID , long ZBID , short Antenna ) ; 
typedef long (WINAPI *typeSetHoseETotalsMT)(CEZCLProcess* pCLProcess ,  long ID , double Volume , double Value ) ;
typedef long (WINAPI *typeGetNextZBStatusEventMT)(CEZCLProcess* pCLProcess , long* pPortID , long* pZBID , __int64* pZBAddress, short* pCondition , short* pCount , short* pStrength ) ;
typedef long (WINAPI *typeGetNextZBPanIDEventMT)(CEZCLProcess* pCLProcess , long* pPortID , __int64* pZBPanID ) ;
typedef long (WINAPI *typeGetNextZeroDeliveryEventMT)(CEZCLProcess* pCLProcess ,  long* pPumpID , long* pPumpNumber , long* pHoseID , long* pHoseNumber ) ;
typedef long (WINAPI *typeSetIOPinMT)(CEZCLProcess* pCLProcess ,  long ID , long ZBID , short Slot , short IOPin , short Value ) ;
typedef long (WINAPI *typeSetHosePricesMT)(CEZCLProcess* pCLProcess ,  long ID , short DurationType , short PriceType , double Price1 , double Price2 ) ;
typedef long (WINAPI *typeGetHosePricesMT)( CEZCLProcess* pCLProcess , long ID , short* pDurationType , short* pPriceType , double* pPrice1 , double* pPrice2 ) ;
typedef long (WINAPI *typeSetPumpDefaultPriceLevelMT)(CEZCLProcess* pCLProcess ,  long ID , short Level ) ;
typedef long (WINAPI *typeSetDateTimeMT)( CEZCLProcess* pCLProcess , DATE DateTime ) ;
typedef long (WINAPI *typeGetDateTimeMT)( CEZCLProcess* pCLProcess , DATE* pDateTime ) ;
typedef long (WINAPI *typeGetNextZBCmdEventMT)(CEZCLProcess* pCLProcess , long* pPortID , long* pZBID , __int64* pZBAddress, PBSTR pRxMsg ) ;
typedef long (WINAPI *typeGetNextZBRawEventMT)(CEZCLProcess* pCLProcess , long* pPortID , long* pZBID , __int64* pZBAddress, PBSTR pRxMsg ) ;
typedef long (WINAPI *typeGetNextZB2GStatusEventMT)( CEZCLProcess* pCLProcess , long* pPortID , __int64* pZBAddress, short* pLQI , short* pRSSI , __int64*  pParZBAddress, short* pZBChannel , short* pMemBlocks , short* pMemFree ) ;
typedef long (WINAPI *typeZBSendRawMT)(CEZCLProcess* pCLProcess ,  long ID , long ZBID , __int64 ZBAddress , BSTR TxMsg ) ;
typedef long (WINAPI *typeZBSendCmdMT)(CEZCLProcess* pCLProcess ,long ID , long ZBID , __int64 ZBAddress , BSTR TxMsg ) ;
typedef long (WINAPI *typeZBCmdRegisterInterestMT)(CEZCLProcess* pCLProcess , long ID , long ZBID ) ;
typedef long (WINAPI *typeZBRawRegisterInterestMT)(CEZCLProcess* pCLProcess , long ID , long ZBID ) ;
typedef long (WINAPI *typeGetZB2GConfigMT)(CEZCLProcess* pCLProcess , long ID , __int64* pPanID , long* pChannels , __int64* pKeyA , __int64* pKeyB ) ;
typedef long (WINAPI *typeScheduleBeepMT)( CEZCLProcess* pCLProcess , long ID , short Pitch1 , short Duration1 , short Pitch2 , short Duration2, short Pitch3 , short Duration3, short Pitch4 , short Duration4, short Pitch5 , short Duration5 ) ;
typedef long (WINAPI *typeFlashLEDSMT)( CEZCLProcess* pCLProcess , long ID , short Side , short PeriodMs , short Cycles ) ;

// Version 3 APIs 

typedef long (WINAPI *typeGetLogEventCountMT)( CEZCLProcess* pCLProcess , long* pCount , short DeviceType , long DeviceID , short EventLevel , short EventType ,long  ClearedBy ,long  AckedBy)  ;
typedef long (WINAPI *typeGetLogEventByOrdinalMT)( CEZCLProcess* pCLProcess , long Index , long* pID , short DeviceType , long DeviceID , short EventLevel , short EventType ,long  ClearedBy ,long  AckedBy) ;
typedef long (WINAPI *typeGetLogEventPropertiesMT)(CEZCLProcess* pCLProcess , long ID , short* pDeviceType , long* pDeviceID , long* pDeviceNumber ,	PBSTR pDeviceName , short* pEventLevel ,
									short* pEventType , PBSTR pEventDesc , DATE* pGeneratedDT , DATE* pClearedDT , long* pClearedBy , long* pAckedBy , double* pVolume ,
									double* pValue , double* pProductVolume , double* pProductLevel , double* pWaterLevel , double* pTemperature );
typedef long (WINAPI *typeSetLogEventPropertiesMT)(CEZCLProcess* pCLProcess , long ID , short DeviceType , long DeviceID , long DeviceNumber , BSTR DeviceName , short EventLevel ,
									short EventType , BSTR  EventDesc , DATE GeneratedDT , DATE ClearedDT , long  ClearedBy , long  AckedBy , double  Volume ,
									double  Value , double  ProductVolume ,	double  ProductLevel , double  WaterLevel , double  Temperature  );
typedef long (WINAPI *typeDeleteLogEventMT)( CEZCLProcess* pCLProcess , long ID ) ;
typedef long (WINAPI *typeGetNextLogEventEventMT)( CEZCLProcess* pCLProcess , long* pLogEventID , short* pDeviceType , long* pDeviceID , long* pDeviceNumber ,	PBSTR pDeviceName , short* pEventLevel ,
								     short* pEventType , PBSTR pEventDesc , DATE* pGeneratedDT , DATE* pClearedDT , long* pClearedBy , long* pAckedBy , double* pVolume ,
								     double* pValue , double* pProductVolume , double* pProductLevel , double* pWaterLevel , double* pTemperature) ;
typedef long (WINAPI *typeClearLogEventMT)( CEZCLProcess* pCLProcess , long ID , long ClientID ) ;
typedef long (WINAPI *typeAckLogEventMT)( CEZCLProcess* pCLProcess , long ID , long ClientID ) ;


typedef long (WINAPI *typeGetSensorsCountMT)( CEZCLProcess* pCLProcess , long* pCount ) ;
typedef long (WINAPI *typeGetSensorByNumberMT)( CEZCLProcess* pCLProcess , long Number , long* pID ) ;
typedef long (WINAPI *typeGetSensorByNameMT)( CEZCLProcess* pCLProcess , BSTR Name , long* pID ) ;
typedef long (WINAPI *typeGetSensorByOrdinalMT)( CEZCLProcess* pCLProcess , long Index , long* pID ) ;
typedef long (WINAPI *typeGetSensorPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long* pNumber, PBSTR pName , long* pPortID , short* pType , short* pAddress , short* pSensorNo )  ;
typedef long (WINAPI *typeSetSensorPropertiesMT)(CEZCLProcess* pCLProcess , long ID , long Number, BSTR Name , long PortID , short Type , short Address , short SensorNo )  ;
typedef long (WINAPI *typeSetSensorStatusMT)(CEZCLProcess* pCLProcess , long ID , short State , short IsResponding )  ;
typedef long (WINAPI *typeGetSensorStatusMT)(CEZCLProcess* pCLProcess , long ID , short* pState , short* pIsResponding) ; 
typedef long (WINAPI *typeDeleteSensorMT)( CEZCLProcess* pCLProcess , long ID ) ;

typedef long (WINAPI *typeSetLogPathMT)(CEZCLProcess* pCLProcess, BSTR Path);
typedef long (WINAPI *typeLogMT)(CEZCLProcess* pCLProcess, BSTR Text);
typedef long (WINAPI *typeSetClientTypeMT)( CEZCLProcess* pCLProcess, long ClientKey ) ; 
typedef long (WINAPI *typeGetNextSaleItemEventMT)(CEZCLProcess* pCLProcess,
									long* pSaleItemID, long* pProductID, long* pProductNumber, PBSTR pProductName, __int64* pProductTag, long* pProductGroup, PBSTR pProductGroupName, PBSTR pBarcode,
									long* pPumpID, long* pPumpNumber, PBSTR pPumpName,
									long* pAttendantID, long* pAttendantNumber, PBSTR pAttendantName, __int64* pAttendantTag,
									long* pCardClientID, long* pCardClientNumber, PBSTR pCardClientName, __int64* pCardClientTag,
									short* pPriceLevel, double* pPrice, double* pQuantity, DATE* pAddedDT, DATE* pClearedDT,
									long* pLockedBy, long* pClearedBy, short* pLoggedDB, short* pLoggedVolumetric,
									PBSTR pPlate, PBSTR pDriverID, PBSTR pExtTransactionID, PBSTR pAuthID, short* pAuthType);

typedef long (WINAPI *typeGetProductByNumberMT)(CEZCLProcess* pCLProcess, long Number, long* pID);
typedef long (WINAPI *typeMT)(CEZCLProcess* pCLProcess, BSTR Name, long* pID);
typedef long (WINAPI *typeGetProductPropertiesMT)(CEZCLProcess* pCLProcess, long ID, long* pNumber, PBSTR pName, PBSTR pTag, short* pEnabled, PBSTR pShortName, PBSTR pBarcode, double* pPrice1, double* pPrice2, long* pProductGroup);
typedef long (WINAPI *typeSetProductPropertiesMT)(CEZCLProcess* pCLProcess, long ID, long Number, BSTR Name, BSTR Tag, short Enabled, BSTR ShortName, BSTR Barcode, double Price1, double Price2, long ProductGroup);
typedef long (WINAPI *typeDeleteProductMT)(CEZCLProcess* pCLProcess, long ID);
typedef long (WINAPI *typeGetProductsCountMT)(CEZCLProcess* pCLProcess, long* pCount, long Number, BSTR Name, BSTR ShortName, BSTR Tag, BSTR Barcode, long ProductGroup);
typedef long (WINAPI *typeGetProductByOrdinalMT)(CEZCLProcess* pCLProcess, long Index, long* pID, long Number, BSTR Name, BSTR ShortName, BSTR Tag, BSTR Barcode, long ProductGroup);

typedef long (WINAPI *typeGetSaleItemPropertiesMT)(CEZCLProcess* pCLProcess, long ID, long* pProductID, long* pPumpID, long* pAttendantID, long* pCardClientID, short* pPriceLevel, double* pPrice,
	double* pQuantity, DATE* pAddedDT, DATE* pClearedDT, long* pLockedBy, long* pClearedBy, short* pLoggedDB, short* pLoggedVolumetric,
	PBSTR pPlate, PBSTR pDriverID, PBSTR pExtTransactionID, PBSTR pAuthID, short* pAuthType);
typedef long (WINAPI *typeSetSaleItemPropertiesMT)(CEZCLProcess* pCLProcess, long ID, long ProductID, long PumpID, long AttendantID, long CardClientID, short PriceLevel, double Price,
	double Quantity, DATE AddedDT, DATE ClearedDT, long LockedBy, long ClearedBy, short LoggedDB, short LoggedVolumetric,
	BSTR Plate, BSTR DriverID, BSTR ExtTransactionID, BSTR AuthID, short AuthType);
typedef long (WINAPI *typeDeleteSaleItemMT)(CEZCLProcess* pCLProcess, long ID);
typedef long (WINAPI *typeGetSaleItemsCountMT)(CEZCLProcess* pCLProcess, long* pCount, long ProductID, long PumpID, long AttendantID, long CardClientID, long LockedBy, long ClearedBy, short LoggedDB, short LoggedVolumetric);
typedef long (WINAPI *typeGetSaleItemByOrdinalMT)(CEZCLProcess* pCLProcess, long Index, long* pID, long ProductID, long PumpID, long AttendantID, long CardClientID, long LockedBy, long ClearedBy, short LoggedDB, short LoggedVolumetric);

typedef long (WINAPI *typeSaleItemLockMT)(CEZCLProcess* pCLProcess, long ID);
typedef long (WINAPI *typeSaleItemUnlockMT)(CEZCLProcess* pCLProcess, long ID);
typedef long (WINAPI *typeSaleItemClearMT)(CEZCLProcess* pCLProcess, long ID);
typedef long (WINAPI *typeSaleItemLockAndClearMT)(CEZCLProcess* pCLProcess, long ID);
typedef long (WINAPI *typeSaleItemAckDBLogMT)(CEZCLProcess* pCLProcess, long ID);
typedef long (WINAPI *typeSaleItemAckVolLogMT)(CEZCLProcess* pCLProcess, long ID);
typedef long (WINAPI *typeGetSaleItemSummaryMT)(CEZCLProcess* pCLProcess, long ID, long* pProductID, long* pProductNumber, PBSTR pProductName, __int64* pProductTag, long* pProductGroup, PBSTR pProductGroupName, PBSTR pBarcode,
	long* pPumpID, long* pPumpNumber, PBSTR pPumpName,
	long* pAttendantID, long* pAttendantNumber, PBSTR pAttendantName, __int64* pAttendantTag,
	long* pCardClientID, long* pCardClientNumber, PBSTR pCardClientName, __int64* pCardClientTag,
	short* pPriceLevel, double* pPrice, double* pQuantity, DATE* pAddedDT, DATE* pClearedDT,
	long* pLockedBy, long* pClearedBy, short* pLoggedDB, short* pLoggedVolumetric,
	PBSTR pPlate, PBSTR pDriverID, PBSTR pExtTransactionID, PBSTR pAuthID, short* pAuthType);

typedef long (WINAPI *typeGetPriceSignElementMT)(CEZCLProcess* pCLProcess, short Element , short* pElementType , long* pLinkID  , short* pDecimals , double* pPrice, short* pState , short* pOnTime, short* pOffTime ) ;
typedef long (WINAPI *typeSetPriceSignElementMT)(CEZCLProcess* pCLProcess, short Element , short ElementType , long LinkID , short Decimals  , double Price , short State , short OnTime, short OffTime );
typedef long (WINAPI *typeGetStappingTableDataMT)(CEZCLProcess* pCLProcess, long ID, double* pStepSize, double* pDiameter, double* pOffset, double* pCapacity, long* pAlarms);
typedef long (WINAPI *typeSetStappingTableDataMT)(CEZCLProcess* pCLProcess, long ID, double StepSize, double Diameter, double Offset, double Capacity, long Alarms);
typedef long (WINAPI *typeGetStappingTableElementMT)(CEZCLProcess* pCLProcess, long ID, long Element, short* pPasses, double* pHeight, double* pStartDelta, double* pCurDelta, double* pStartVolume, double* pCurVolume);
typedef long (WINAPI *typeSetStappingTableElementMT)(CEZCLProcess* pCLProcess, long ID, long Element, short Passes, double StartDelta, double CurDelta);


// not valid for CE
//typedef long (*typeIsValidMACLicense)( BSTR LicenseKey );

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

	       //-------------Métodos MT --------------//


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