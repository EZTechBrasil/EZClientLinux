//-----------------------------------------------------------------------------
//
//  Empresa     : EzTech Tecnologia e Automação Ltda
//        				 http://www.eztech.ind.br/
//
//	Created     : 24/08/2012
//
//  Descricao   : Classe para carga e acesso da biblioteca EZClient.dll
//
//  Observacoes :
//
//		*. para compilacao com GCC em ambiente Windows e necessario a instalacao
//		   do pacote MinGW (http://www.mingw.org/)
//
//		*. para compilar com GCC para Windows ou Linux utilize o script Makefile
//		   utilize os seguintes comandos:
//
//				> make clean   (limpa objetos antigos)
//				> make linux   (plataforma LINUX 32bits)
//				> make windows (plataforma WIN32)
//
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>

#if defined(_WIN32)

#include <conio.h>
#include <windows.h>

#elif defined(__linux__)

#include <unistd.h>
#include <termios.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/signal.h>

#endif

#include "EZDefinitions.h"
#include "EZClient.h"
#include "version.h"
#include "ClientMain.h"

#define	USB1	1
#define ALLGRADE 
//#define FREE_SYS_STR( b ) { if( b != NULL ) { SysFreeString( b ) ; b = NULL ; } ; }

using namespace std;

//-----------------------------------------------------------------------------
// License Modules Enabled
bool	isEZServerModule = false ;
bool	isEZHOModule = false ;
bool	isZigBeeModule = false ;
bool	isEZMonitorModule = false ;
bool	isTankManagementModule = false ;
bool	isDevelopmentModule = false ;

bool runEvents   = false;					// Processando por Pooling
bool isConnected = false;					// Não conectado ao Servidor
TCHAR EZServerAddr[MAX_PATH] = "EZServerCE";	// Endereco padrao do servidor
// BSTR	AttEZServerAddr ;
int  appPump = 1;								// Bomba em uso
int  lastStatus[MAX_PATH];	
TCHAR	versionCompatible[MAX_PATH] = "2,5,1,8" ;				// Status atual das bombas


//-----------------------------------------------------------------------------
CEZClient EZInterface;

//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	int ct;

	memset(lastStatus, 0, sizeof(lastStatus));

	WriteMessage("\nEZForecourt - EZClient.so.1 - C\\C++ Demonstracao!\n");

	CreateAcess();

	if(argc>=2)
	{
		for(ct=1; ct<argc; ct++)
		{
			if( !stricmp(argv[ct], "/events") )
			{
				// Configura processamento por Eventos
				runEvents = true;
			}
			else if( !stricmp(argv[ct], "/server") )
			{
				ct++; //  pega o proximo parametro da lista
				if( STRLEN(argv[ct])>0 )
					strcpy(EZServerAddr, argv[ct]);
				else
				{
					HelpText(0);
					exit(0);
				}
			}
			else if( !stricmp(argv[ct], "/?") )
			{
				HelpText(0);
				exit(0);
			}
			else
			{
				WriteMessage("\n*** Parametro desconhecido: %s\n", argv[ct]);
				exit(-1);
			}
		}
	}
	MainLoop();

	return(0);
}

void CreateAcess()
{
	WriteMessage("\n Enter the EZServer access IP number: ") ;
	fflush(stdin) ;
	scanf ("%s", EZServerAddr ) ;
}

//-----------------------------------------------------------------------------
void MainLoop()
{
	bool ExitLoop = false;
	char chosenType = '?';

	if( runEvents )
		WriteMessage("\nProcessando Eventos!\n");

	while( !ExitLoop )
	{
		CheckLogin();

		if( isConnected )
		{

			if( !runEvents )
				PumpsStatus();
			else
				CheckEvents();

			chosenType = ShowMenu(1);

			switch( chosenType )
			{
				case 'A': case 'a':
					BasicGoodPractice() ;
					break ;

				case 'B': case 'b':
					DeliveriesReading() ;
					break ;

				case 'C': case 'c':
					PumpBasicControl() ;
					break ;

				case 'D': case 'd':
					PumpControlExtended() ;
					break ;

				case 'E': case 'e':
					PumpPriceControl() ;
					break ;

				case 'F': case 'f':
					//ReadingCards() ;
					break ;

				case 'G': case 'g':
					RegisterAttendant() ;
					break ;

				case 'H': case 'h': 
					RegisterClient() ;
					break ;

				case 'I': case 'i': 
					TanksSensorsReading() ;
					break ;

				case 'J': case 'j': 
					GeneralConfigurationFacility() ;
					break ;

				case 'X' :	case 'x' :// exit
				case '\033':	// ESC
					WriteMessage( "\n Shutdown!\n" ) ;
					ExitLoop = true ;
					break ;

				default:		// Unknown Commands
					WriteMessage("\nUnknown command!") ;
					break ;
			}
		} 
		else if( EZInterface.KBhit() )
			chosenType = EZInterface.KBget();
		else
			chosenType = 0;
	}

	WriteMessage("\nBye!!\n");

	if ( isConnected )
	{
		EZInterface.ClientLogoff();
		isConnected = false ;
	}

}

char ShowMenu( int menuLevel )
{
	char chosenType;

	switch( menuLevel )
	{
		case MAIN_MENU:
			WriteMessage( "\nEZForecourt - EZClient.so.1 - C\\C++ Demo!         Version: %s", VERSION ) ;
			WriteMessage( "\n" ) ;
			WriteMessage( "\n\t	A - Basic Good Practice") ;
			WriteMessage( "\n\t	B - Deliveries Reading") ;
			WriteMessage( "\n\t	C - Pump Basic Control") ;
			WriteMessage( "\n\t	D - Pump Control Extended") ;
			WriteMessage( "\n\t	E - Pump Price Control" ) ;
			WriteMessage( "\n\t	F - Reading Cards" ) ;
			WriteMessage( "\n\t	G - Register Attendant") ;
			WriteMessage( "\n\t	H - Register Client") ;
			WriteMessage( "\n\t	I - Tanks and Sensors Reading") ;
			WriteMessage( "\n\t	J - General Configuration Facility") ;
			WriteMessage( "\n\t	X - Exit") ;
			break ;

		case BASIC_GOOD_PRATICE_MENU: 
			WriteMessage( "\n\n Which function would you like to test?") ;
			WriteMessage( "\n\t	A - Date / Time Update") ;
			WriteMessage( "\n\t	B - Version Compatibility") ;
			WriteMessage( "\n\t	C - License Verification") ;
			WriteMessage( "\n\t	D - Disconnection with EZTech") ;
			break ;

		case DELIVERY_READING_MENU: 
			WriteMessage( "\n\n Which function would you like to test?") ;
			WriteMessage( "\n\t	A - Read all Deliveries") ;
			WriteMessage( "\n\t	B - Read Pending Deliveries") ;
			break ;

		case PUMP_BASIC_CONTROL_MENU:  
			WriteMessage( "\n\n Which function would you like to test?") ;
			WriteMessage( "\n\t	A - Temporary Stop") ;
			WriteMessage( "\n\t	B - Reauthorize Delivery") ;
			WriteMessage( "\n\t	C - Disable Hose") ;
			WriteMessage( "\n\t	D - Activation Hose") ;
			WriteMessage( "\n\t	E - Pumps Status") ;
			WriteMessage( "\n\t F - Authorize Delivery" ) ;
			WriteMessage( "\n\t G - Cancel Authorize" ) ;			
			break ;

		case PUMP_CONTROL_EXTENDED_MENU: 
			WriteMessage( "\n\n Which function would you like to test?") ;
			WriteMessage( "\n\t	A - Scheduled Delivery") ;
			WriteMessage( "\n\t	B - Preset Delivery") ;			
			break ;

		case PUMP_PRICE_CONTROL_MENU:
			WriteMessage( "\n\n Which function would you like to test?") ;
			WriteMessage( "\n\t	A - Price Change per Hose") ;
			WriteMessage( "\n\t	B - Price Change per Grade") ;	
			break ;

		case REGISTER_ATTENDANT_MENU: 
			WriteMessage( "\n\n Which function would you like to test?") ;
			WriteMessage( "\n\t	A - Attendant Registration") ;
			WriteMessage( "\n\t	B - Delete Attendant") ;	
			WriteMessage( "\n\t	C - Change of Attendant's time");
			break ;

		case REGISTER_CLIENT_MENU: 
			WriteMessage( "\n\n Which function would you like to test?") ;
			WriteMessage( "\n\t	A - Client Registration") ;
			WriteMessage( "\n\t	B - Delete Client") ;	
			break ;

		case TANKS_SENSORS_READING_MENU: 
			WriteMessage( "\n\n Which function would you like to test?") ;
			WriteMessage( "\n\t	A - Tank Reading") ;
			WriteMessage( "\n\t	B - Monitoring Alarm") ;	
			break ;

		case GENERAL_CONFIGURATION_FACILITY_MENU: 
			WriteMessage( "\n\n Which function would you like to test?") ;
			WriteMessage( "\n\t	A - Delivery Position Register") ;
			WriteMessage( "\n\t	B - Delete of Delivery Position") ;	
			WriteMessage( "\n\t	C - Hose Registration") ;
			WriteMessage( "\n\t	D - Delete Hose") ;
			WriteMessage( "\n\t	E - Grade Register") ;
			WriteMessage( "\n\t	F - Delete Grade") ;
			WriteMessage( "\n\t	G - Tank Registration") ;
			WriteMessage( "\n\t	H - Delete Tank") ;
			WriteMessage( "\n\t	I - Zigbee Device Registration") ;
			WriteMessage( "\n\t	J - Delete Zigbee Device") ;
			break ;
	}

	WriteMessage( "\n\nSelect Option Test: ") ;

	fflush(stdin);
	scanf ("\n%c", &chosenType ) ;
	//system("clear") ;	

	return chosenType;
}

void EndMessage()
{
	WriteMessage("\n\n");
	//system("PAUSE");
	//system("clear") ;
}

// ------------------------ GoodResult ----------------------------------------//

bool GoodResult( int result )
{
	if( result == OK_RESULT )	
		return true ;

	WriteMessage( "\nError: %d\n", result ) ;

	//BSTR resultString = EZInterface.ResultString(result);

	//WriteMessage( "\nError: %d %s", result, resultString ) ;

	//FREE_SYS_STR( resultString ) ;

	if( ( result < OK_RESULT && result != INVALID_OBJECT_ID ) || result == NOT_LOGGED_ON_RESULT )
	{
		if ( isConnected )
		{
			EZInterface.ClientLogoff();
			isConnected = false ;
		}
	}
	return false ;
}

//------------------------- Basic Good Praticte ------------------------------//


void BasicGoodPractice()
{
	char chosenType ;
		
	chosenType = ShowMenu( BASIC_GOOD_PRATICE_MENU ) ;

	CheckLogin(); 
	if( ! isConnected )
		return ;

	switch ( chosenType )
	{
		case 'A': case 'a':
			//SetDateTime() ;
			break ;
		case 'B': case 'b':
			CheckServerVersion() ;
			break ;
		case 'C': case 'c':
			CheckLicenseStatus() ;
			break ;
		case 'D': case 'd':
			ClientLogoff() ;
			break ;
		default:
			WriteMessage("\n Unknown command!") ;
	}
}
/*
void SetDateTime()
{
	SYSTEMTIME st ;
	GetLocalTime( & st ) ;
	COleDateTime eztime( st ) ;

	if( st.wHour <= 24 &&
		st.wMinute <= 60 &&
		st.wSecond <= 60 &&
		GoodResult( EZInterface.SetDateTime( eztime ) ) )
	{
		WriteMessage( "\nDateTime EZServer Updated: %04d-%02d-%02d %02d:%02d:%02d", st.wYear, 
																 st.wMonth, 
																 st.wDay, 
																 st.wHour, 
																 st.wMinute, 
																 st.wSecond ) ;
	}

	EndMessage() ;
}
*/
void CheckServerVersion()
{

    int stringLength = 0 ;
	int index = 0 ;

#if defined( _WIN32 )
    BSTR   ezserverVersion = NULL ;
    if( ! GoodResult( EZInterface.ServerVersion( &ezserverVersion ) ) ) 
    	return;
 
	stringLength = ( int ) SysStringLen( ezserverVersion ) ;

#elif defined( __linux__)

    TCHAR   ezserverVersion[MAX_PATH] ;
    TCHAR   soVersion[MAX_PATH] ;

	if( ! GoodResult( EZInterface.ServerVersion( MakeBSTR(ezserverVersion, MAX_PATH ) ) ) )
		return;

	if( ! GoodResult( EZInterface.DllVersion( MakeBSTR(soVersion, MAX_PATH ) ) ) )
		return;

	WriteMessage("\nSO Version: %s", soVersion ) ;

	stringLength = (int)STRLEN( ezserverVersion );

#endif
	
	TCHAR versionPart[MAX_PATH] = "" ;

	for ( int i = stringLength - 7 ; i >= 0 && i < stringLength ; i++ )
	{
		versionPart[ index++ ] = ezserverVersion[ i ] ;
	}

	versionPart[ index++ ] = 0 ; 

	WriteMessage("\nEZServer Version: %s -> %s", ezserverVersion , versionPart ) ;

	if ( ( strcmp ( versionPart , versionCompatible ) >= 0 ) )
	{		
		WriteMessage("\n\nVersion Compatible " ) ;
	}
	else 
	{
		WriteMessage("\nIncompatible Version " ) ;
	}

	EndMessage() ;
}

void CheckLicenseStatus()
{
	short licenseType = 0 ;

	if( GoodResult( EZInterface.GetLicenseType( &licenseType ) ) )
	{
		WriteMessage("\nActive License Modules: " ) ;

		if ( licenseType & EZSERVER_LICENSE_MASK )
		{
			WriteMessage("\nEZSERVER ENABLED " ) ;
			isEZServerModule = true ;
		}

		if ( licenseType & EZHO_LICENSE_MASK )
		{
			WriteMessage("\nEZHO ENABLED " ) ;
			isEZHOModule = true ;
		}

		if ( ( licenseType & ZIGBEE_LICENSE_MASK ) == 0 )
		{
			WriteMessage("\nZIGBEE ENABLED " ) ;
			isZigBeeModule = true ;
		}

		if ( ( licenseType & EZMONITOR_LICENSE_MASK ) == 0 )
		{
			WriteMessage("\nEZMONITOR ENABLED " ) ;
			isEZMonitorModule = true ;
		}

		if ( licenseType & TANK_MANAGEMENT_LICENSE_MASK )
		{
			WriteMessage("\nTANK MANAGEMENT ENABLED " ) ;
			isTankManagementModule = true ;
		}

		if ( licenseType & DEVELOPMENT_LICENSE_MASK )
		{
			WriteMessage("\nDEVELOPMENT ENABLED " ) ;
			isDevelopmentModule = true ;
		}

	}

	EndMessage() ;
}

void ClientLogoff()
{
	if ( isConnected )
	{
		WriteMessage("\nLogging off\n" ) ;
		EZInterface.ClientLogoff() ;
		isConnected = false ; 
	}
}

//----------------- DeliveriesReading ----------------------//

void DeliveriesReading() 
{
	char chosenType ;
	
	chosenType = ShowMenu( DELIVERY_READING_MENU ) ;

	CheckLogin();
	if( ! isConnected )
		return ;

	switch ( chosenType )
	{
		case 'A': case 'a':
			ReadAllDeliveries( true ) ;
			break ;

		case 'B': case 'b':
			ReadAllDeliveries( false ) ;
			break ;


		default:
			WriteMessage("\n Unknown command!") ;
	}

}

void ReadAllDeliveries( bool ReadAll )
{
    int		idx ;
    LONG	deliveryCount ;
    LONG	deliveryID ;
    LONG	hoseID ;
    short	deliveryState ;
    short	deliveryType ;
    double	volume ;
    short	priceLevel ;
    double	price ;
    double	value ;
    double	volume2 ;
    DATE	completedDate ;
    LONG	lockedBy ;
    LONG	reservedBy ;
    LONG	attendantID ;
    LONG	age ;
    DATE	clearedDate ;
    double	oldVolumeETot ;
    double	oldVolume2ETot ;
    double	oldvalueETot ;
    double	newVolumeETot ;
    double	newVolume2ETot ;
    double	newvalueETot ;
    INT64	tag ;
    LONG	duration ;
    LONG	clientID ;
	double	peakFlowRate ;

    //COleDateTime *oleCompletedDate = NULL ;
	//COleDateTime *oleClearedDate = NULL ;

	if ( ReadAll )
	{
		if( !GoodResult( EZInterface.GetAllDeliveriesCount( &deliveryCount ) ) )
			return ;
		WriteMessage( "\n [ Count All Deliveries %03d ] ----------------------------------------------- ", deliveryCount ) ;
	}
	else 
	{
		if( !GoodResult( EZInterface.GetDeliveriesCount( &deliveryCount ) ) )
			return ;
		WriteMessage( "\n [ Count pending Deliveries %03d ] ------------------------------------------- ", deliveryCount ) ;
	}


    for( idx = deliveryCount ; idx > 0 ; idx-- )
	{

		if ( ReadAll )
		{
			if( !GoodResult( EZInterface.GetAllDeliveryByOrdinal( idx, &deliveryID ) ) )
				return;
		}
		else 
		{
			if( !GoodResult( EZInterface.GetDeliveryByOrdinal( idx, &deliveryID ) ) )
				return;
		}

       WriteMessage( "\n------ Delivery: (%03d) %d",    idx, deliveryID ) ;


       if( GoodResult( EZInterface.GetDeliveryPropertiesEx4(	deliveryID, &hoseID, &deliveryState, &deliveryType,
                                                                &volume, &priceLevel, &price,
                                                                &value, &volume2, &completedDate,
                                                                &lockedBy, &reservedBy, &attendantID,
                                                                &age, &clearedDate, &oldVolumeETot,
                                                                &oldVolume2ETot, &oldvalueETot,
                                                                &newVolumeETot, &newVolume2ETot,
                                                                &newvalueETot, &tag, &duration, &clientID, &peakFlowRate ) ) )
	   {


		  //oleCompletedDate = new COleDateTime( completedDate ) ;
		  //oleClearedDate = new COleDateTime( clearedDate ) ;


		  WriteMessage( "\nHose ID: %d  Delivery State: %d  Type: %d",
										hoseID, deliveryState, deliveryType ) ;

		  WriteMessage( "\nVolume: %.03f  Price Level: %d  Price: %.03f  Value: %.03f",
										volume, priceLevel, price, value ) ;

		//  WriteMessage( "\nVolume2: %.03f  Complete DaTe: %04d-%02d-%02d %02d:%02d:%02d ",
		//								volume2, oleCompletedDate->GetYear(), oleCompletedDate->GetMonth(), 
		//								oleCompletedDate->GetDay(), oleCompletedDate->GetHour(), oleCompletedDate->GetMinute(), 
		//								oleCompletedDate->GetSecond()  ) ;

		//  WriteMessage( "\nAttendant ID: %d  Age: %d  Cleared Date: %04d-%02d-%02d %02d:%02d:%02d ",
		//								attendantID, age, oleClearedDate->GetYear(), oleClearedDate->GetMonth(), 
		//								oleClearedDate->GetDay(), oleClearedDate->GetHour(), oleClearedDate->GetMinute(), 
		//								oleClearedDate->GetSecond() ) ;

		  WriteMessage( "\nOld Volume ETotal: %.03f  Old Volume2 ETotal: %.03f  Old Value ETotal: %.03f",
										oldVolumeETot, oldVolume2ETot, oldvalueETot) ;

		  WriteMessage( "\nNew Volume ETotal: %.03f  New Volume2 ETotal: %.03f  New Value ETotal: %.03f",
										newVolumeETot, newVolume2ETot, newvalueETot) ;

		  WriteMessage( "\nTAG: %d Duraction: %d ", tag, duration ) ;

		  WriteMessage( "\n" ) ;

          if( lockedBy != NULL_ID )
			continue ;

          if( GoodResult( EZInterface.LockDelivery( deliveryID ) ) )
			lockedBy = LOGIN_ID ;

          else
            continue ;

          if( ( lockedBy == LOGIN_ID ) && ( deliveryState != CLEARED ) )
            GoodResult( EZInterface.ClearDelivery( deliveryID , deliveryType ) ) ;

	   }
	}

	WriteMessage("\n------------------------------------------------------------------------") ;

	EndMessage() ;
}



// ----------------------------- PumpBasicControl -------------------------------//

void PumpBasicControl()
{
	char chosenType ;
		
	chosenType = ShowMenu( PUMP_BASIC_CONTROL_MENU ) ;

	CheckLogin(); 
	if( ! isConnected )
		return ;

	switch ( chosenType )
	{
		case 'A': case 'a':
			TemporaryStop() ;
			break ;
		case 'B': case 'b':
			ReAuthoriseDelivery() ;
			break ;
		case 'C': case 'c':
			DisablePump() ;
			break ;
		case 'D': case 'd':
			EnablePump() ;
			break ;
		case 'E': case 'e':
			PumpsStatus() ;
			break ;
		case 'F': case 'f':
			AuthoriseDelivery() ;
			break ;
		case 'G': case 'g':
			CancelAuthorise() ;
			break ;
		default:
			WriteMessage("\n Unknown command!") ;
	}
}

void TemporaryStop()
{
	LONG	pumpID ;
	LONG	pumpNumber ;
	
	WriteMessage("\n Enter the number of the pump you want block: ") ;
	fflush(stdin) ;
	scanf ("%d", &pumpNumber ) ;

	if( !GoodResult( EZInterface.GetPumpByNumber( pumpNumber, &pumpID ) ) )
		return ;

	if( GoodResult( EZInterface.TempStop( pumpID ) ) ) 
		return ;

	WriteMessage( "\n Pump %d Temp Stoped", pumpNumber ) ;

	EndMessage() ;
}

void ReAuthoriseDelivery()
{
	LONG	pumpID ;
	LONG	pumpNumber ;
	
	WriteMessage("\n Enter the number of the pump you want reauthorize: ") ;
	fflush(stdin) ;
	scanf ("%d", &pumpNumber ) ;

	if( !GoodResult( EZInterface.GetPumpByNumber( pumpNumber, &pumpID ) ) )
		return ;

	if( GoodResult( EZInterface.ReAuthorise( pumpID ) ) ) 
		return ;

	WriteMessage( "\n Pump %d Temp Stoped", pumpNumber ) ;

	EndMessage() ;
}


void DisablePump()
{
	LONG	pumpID ;
	LONG	pumpNumber ;
	
	WriteMessage("\n Enter the number of the pump you want disable: ") ;
	fflush(stdin) ;
	scanf ("%d", &pumpNumber ) ;

	if( !GoodResult( EZInterface.GetPumpByNumber( pumpNumber, &pumpID ) ) )
		return ;

	if( GoodResult( EZInterface.DisablePump( pumpID ) ) ) 
		return ;

	WriteMessage( "\n Pump %d Disable Pump", pumpNumber ) ;

	EndMessage() ;
}


void EnablePump()
{
	LONG	pumpID ;
	LONG	pumpNumber ;
	
	WriteMessage("\n Enter the number of the pump you want enable: ") ;
	fflush(stdin) ;
	scanf ("%d", &pumpNumber ) ;

	if( !GoodResult( EZInterface.GetPumpByNumber( pumpNumber, &pumpID ) ) )
		return ;

	if( GoodResult( EZInterface.EnablePump( pumpID ) ) ) 
		return ;

	WriteMessage( "\n Pump %d Enable Pump", pumpNumber ) ;

	EndMessage() ;
}

// Le o esta das bombas usando GetAllPumpStatuses
void PumpsStatus()
{
#if defined(_WIN32)
	BSTR    PumpStates;
	BSTR    CurrentHose;
	BSTR    DeliveriesCount;
#elif defined(__linux__)
	TCHAR    PumpStates[MAX_PATH];
	TCHAR    CurrentHose[MAX_PATH];
	TCHAR    DeliveriesCount[MAX_PATH];
#endif

	LONG    PumpsCount;
	int     Idx;
	int     CurStatus;
	int     CurHose;
	int     CurDelv;
	char    StrStatus[MAX_PATH];
	//char    stmp[MAX_PATH];

	// Verifica se esta conectado ao servidor
	if( isConnected )
	{
	  // Verifica se esta conectado ao servidor
	  if( !GoodResult( EZInterface.GetPumpsCount(&PumpsCount)) )
		  return;

	  // Le o estado de todas as bombas configuradas
#if defined(_WIN32)
	  if( !GoodResult( EZInterface.GetAllPumpStatuses( &PumpStates, &CurrentHose, &DeliveriesCount ) ) )
#elif defined(__linux__)
	  if( !GoodResult( EZInterface.GetAllPumpStatuses(
										  MakeBSTR(PumpStates,      MAX_PATH),
										  MakeBSTR(CurrentHose,     MAX_PATH),
										  MakeBSTR(DeliveriesCount, MAX_PATH) ) ) )
#endif
		  return;

	  for( Idx=0; Idx<PumpsCount; Idx++ )
	  {
		CurStatus = PumpStates[Idx]-'0';
		CurHose   = CurrentHose[Idx]-'0';
		CurDelv   = CurrentHose[Idx]-'0';

		switch( CurStatus ) 																											// PAM1000
		{
    		case INVALID_PUMP_STATE           : strcpy( StrStatus, "estado invalido.");											break;	// 0 - OFFLINE
    		case NOT_INSTALLED_PUMP_STATE     : strcpy( StrStatus, "nao instalada.");											break;	// 6 - CLOSE
    		case NOT_RESPONDING_1_PUMP_STATE  : strcpy( StrStatus, "Bomba nao responde.");										break;	// 0 - OFFLINE
    		case IDLE_PUMP_STATE              : strcpy( StrStatus, "em espera (desocupada).");									break;	// 1 - IDLE
    		case PRICE_CHANGE_STATE           : strcpy( StrStatus, "troca de preco.");											break;	// 1 - IDLE
    		case AUTHED_PUMP_STATE            : strcpy( StrStatus, "Bomba Autorizada");											break;	// 9 - AUTHORIZED
    		case CALLING_PUMP_STATE           : strcpy( StrStatus, "esperando autorizacao.");									break;	// 5 - CALL
    		case DELIVERY_STARTING_PUMP_STATE : strcpy( StrStatus, "abastecimeneto iniciando.");								break;	// 2 - BUSY
    		case DELIVERING_PUMP_STATE        : strcpy( StrStatus, "abastecendo.");												break;	// 2 - BUSY
    		case TEMP_STOPPED_PUMP_STATE      : strcpy( StrStatus, "parada temporaria (no meio de uma abastecimento) (STOP).");	break;	// 8 - STOP
    		case DELIVERY_FINISHING_PUMP_STATE: strcpy( StrStatus, "abastecimento finalizando (fluxo de produto diminuindo).");	break;	// 2 - BUSY
    		case DELIVERY_FINISHED_PUMP_STATE : strcpy( StrStatus, "abastecimento finalizado (parou de sair combustivel).");	break;	// 2 - BUSY
    		case DELIVERY_TIMEOUT_PUMP_STATE  : strcpy( StrStatus, "abastecimento excedeu tempo maximo.");						break;	// 1 - IDLE
    		case HOSE_OUT_PUMP_STATE          : strcpy( StrStatus, "bico fora do guarda-bico (CALL)");							break;	// 5 - CALL
    		case PREPAY_REFUND_TIMEOUT_STATE  : strcpy( StrStatus, "prazo de pre-determinacao esgotado.");						break;	// 1 - IDLE
    		case DELIVERY_TERMINATED_STATE    : strcpy( StrStatus, "abastecimento terminado (EOT)");							break;	// 3 - EOT
    		case ERROR_PUMP_STATE             : strcpy( StrStatus, "Erro (resposta de erro da bomba)");							break;	// 0 - OFFLINE
    		case NOT_RESPONDING_2_PUMP_STATE  : strcpy( StrStatus, "EZID nao responde");										break;
			case LAST_PUMP_STATE              : strcpy( StrStatus, "Ultimo estado da bomba?");									break;
			default							  : sprintf(StrStatus, "estado desconhecido = %d", CurStatus);						break;
		}

		if( lastStatus[Idx] != CurStatus )
		{
		  WriteMessage("\n Bomba %02d, Bico %02d, Pendentes %d, Status(%02d): %s", Idx+1, CurHose, CurDelv, CurStatus, StrStatus);
		  lastStatus[Idx] = CurStatus;
		}
	  }
	}
}


void AuthoriseDelivery()
{
	LONG	pumpID ;
	LONG	pumpNumber ;
	
	WriteMessage("\n Enter the number of the pump you want Authorise: ") ;
	fflush(stdin) ;
	scanf ("%d", &pumpNumber ) ;

	if( !GoodResult( EZInterface.GetPumpByNumber( pumpNumber, &pumpID ) ) )
		return ;

	if( GoodResult( EZInterface.Authorise( pumpID ) ) ) 
		return ;

	WriteMessage( "\n Pump %d Authorise Pump", pumpNumber ) ;

	EndMessage() ;
}


void CancelAuthorise()
{
	LONG	pumpID ;
	LONG	pumpNumber ;
	
	WriteMessage("\n Enter the number of the pump you want Cancel Authorise: ") ;
	fflush(stdin) ;
	scanf ("%d", &pumpNumber ) ;

	if( !GoodResult( EZInterface.GetPumpByNumber( pumpNumber, &pumpID ) ) )
		return ;

	if( !GoodResult( EZInterface.CancelAuthorise( pumpID ) ) ) 
		return ;

	WriteMessage( "\n Pump %d Cancel Authorise Pump", pumpNumber ) ;

	EndMessage() ;
}

// ----------------- Pump Control Extended ---------------------------//

void PumpControlExtended()
{
	char chosenType ;
		
	chosenType = ShowMenu( PUMP_CONTROL_EXTENDED_MENU ) ;

	CheckLogin();
	if( ! isConnected )
		return ;

	switch ( chosenType )
	{
		case 'A': case 'a':
			/*ScheduledDelivery() ;*/
			break ;
		case 'B': case 'b':
			PresetDelivery() ;
			break ;
		default:
			WriteMessage("\n Unknown command!") ;
	}
}

#if 0 

void ScheduledDelivery()
{
    LONG	pumpID = NULL_ID ;
	LONG	pumpNumber = 0 ;
    LONG	termID = LOGIN_ID ;
    LONG	attendantID = NULL_ID ;
	INT64	attendantTag = -1 ;
	LONG	cardClientID = NULL_ID ;
	INT64	cardClientTag = -1 ;
	short	authType = 0;
	INT64	extTag = -1 ;
	short	priceLevel = UNKNOWN_PRICE_CONTROL;
	double	price = 0 ;
	short	gradeType = ALLGRADE ;
	short	priceType = FIXED_PRICE_TYPE ;
	short	presetType = DOLLAR_LIMIT_TYPE ;
	double	value = 0 ;
	short	hose = ALL_HOSES ;
	double	odometer = 0 ;
	double	odometer2 = 0 ;

	// GetAttendantProperties
	LONG	attendantNumber = 0 ;
	short	shiftAStart = 0 ;
	short	shiftAEnd  = 0 ;
	short	shiftBStart  = 0 ;
	short	shiftBEnd  = 0 ;
	short	attendantType  = 0 ;

#if defined( _WIN32 )
	BSTR    termHash = NULL ;
	BSTR    plate = NULL ;
	BSTR    extTransactionID = NULL ;
	BSTR	driverID = NULL ;
	BSTR	authorisation = NULL ;

	// GetAttendantProperties
	BSTR	name = NULL ;
	BSTR	shortName = NULL ;
	BSTR	password = NULL ;
	BSTR	tag = NULL ;


#elif defined(__linux__)
	TCHAR    termHash[MAX_PATH];
	TCHAR    plate[MAX_PATH];
	TCHAR    extTransactionID[MAX_PATH];
	TCHAR	driverID[MAX_PATH];
	TCHAR	authorisation[MAX_PATH];

	// GetAttendantProperties
	TCHAR	name[MAX_PATH];
	TCHAR	shortName[MAX_PATH];
	TCHAR	password[MAX_PATH];
	TCHAR	tag[MAX_PATH];

#endif

	WriteMessage( "\n In this example we will make an authorization with a choice of pump, attendant, price and limit." ) ;
	WriteMessage( "\n" ) ;
	
	WriteMessage( "\n Enter the Pump Number you wish to authorize: " ) ;
    fflush(stdin) ;
    scanf ("%d", &pumpNumber ) ;

	if( !GoodResult( EZInterface.GetPortByNumber(	pumpNumber, &pumpID ) ) )
		return ;

	WriteMessage( "\n Enter the Attendant number that can authorize: " ) ;
    fflush(stdin) ;
    scanf ("%d", &attendantNumber ) ;

	if( !GoodResult( EZInterface.GetAttendantByNumber(	attendantNumber, &attendantID ) ) )
		return ;

#if defined( _WIN32 )
	if( !GoodResult( EZInterface.GetAttendantPropertiesEx(	attendantID, &attendantNumber, &name, &shortName, &password, 
															&tag, &shiftAStart, &shiftAEnd, &shiftBStart, &shiftBEnd, &attendantType ) ) )
		return ;

#endif

	attendantTag = ( INT64 ) tag ;

	WriteMessage( "\n Enter the Price ( Double ) which will be used ( Example 1.98 ): " ) ;
    fflush(stdin) ;
    scanf ("%lf", &price ) ;

	WriteMessage( "\n Enter the volume limit ( Double ) which will be used: " ) ;
    fflush(stdin) ;
    scanf ("%lf", &value ) ;

#if defined( _WIN32 )

	if( !GoodResult( EZInterface.PaymentReserve( pumpID, termID, termHash ) ) )
		return ;

	if( !GoodResult( EZInterface.PaymentAuthorise(	pumpID, termID, termHash, attendantID,
													attendantTag, cardClientID, cardClientTag,
													authType, extTag, gradeType, priceType,
													priceLevel, price, presetType, value,
													hose, odometer, odometer2, plate,
													extTransactionID, driverID, authorisation ) ) )
		return ;

#endif

	/*FREE_SYS_STR( termHash ) ;
	FREE_SYS_STR( plate ) ;
	FREE_SYS_STR( extTransactionID ) ;
	FREE_SYS_STR( driverID ) ;
	FREE_SYS_STR( authorisation ) ;
	FREE_SYS_STR( name ) ;
	FREE_SYS_STR( shortName ) ;
	FREE_SYS_STR( password ) ;
	FREE_SYS_STR( tag ) ;
	*/

	WriteMessage( "\n Pump Reserved " ) ;

	EndMessage() ;
}


#endif 

void PresetDelivery()
{
    int    Bomba;
    int    Bico;
    LONG   IdBomba;
    LONG   IdBico;
    short  LType;
    double PsValue;

    Bomba        = appPump;   // Le o numero da bomba

	WriteMessage("\n Bomba %02d - Preset", Bomba);

	WriteMessage("\n\t               Bico (1 a 6): "); 
	if(scanf("%d",  &Bico)==1){printf("sucess\n");}else{printf("Input Failed\n");}
	WriteMessage("\n\t Tipo (1=Dinheiro 2=Volume): "); 
	if(scanf("%hi", &LType)==1){printf("sucess\n");}else{printf("Input Failed\n");}
	WriteMessage("\n\t                      Valor: ");
	if(scanf("%lf", &PsValue)==1){printf("sucess\n");}else{printf("Input Failed\n");}

	LType = (LType==1?DOLLAR_PRESET_TYPE:VOLUME_PRESET_TYPE);

    // Verifica conexao
    if( !isConnected )
      return;

    // Pega Id da Bomba escolhida
    if( !GoodResult( EZInterface.GetPumpByOrdinal(Bomba, &IdBomba) ) )
      return;

    IdBico = (1<<(Bico-1));  // Calcula ID do bico escolhido

    // Envia preset para bomba
    if( GoodResult( EZInterface.LoadPreset(IdBomba, LType, PsValue, IdBico, 1) ) )
	{
		WriteMessage("\n\t Preset Enviado: Bomba %02d Bico %02d Tipo %d Valor %.03f Nivel 1",
							Bomba, Bico, LType, PsValue);
	}
}

// ----------------- Pump Price Control ------------------------------//

void PumpPriceControl()
{
	char chosenType ;
		
	chosenType = ShowMenu( PUMP_PRICE_CONTROL_MENU ) ;

	CheckLogin();
	if( ! isConnected )
		return ;

	switch ( chosenType )
	{
		case 'A': case 'a':
			ChangeHosePrice() ;
			break ;
		case 'B': case 'b':
			ChangeGradePrice() ;
			break ;
		default:
			WriteMessage("\n Unknown command!") ;
	}
}

void ChangeHosePrice()
{
	LONG	hoseID ;
	LONG	hoseNumber ;
	LONG	pumpID ;
	LONG	pumpNumber ;
	LONG	durationType ;
	LONG	priceType ;
	double	price1 ;
	double	price2 ;

	WriteMessage( "\n Enter the Pump number you want to change the price: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &pumpNumber ) ;

	if( !GoodResult( EZInterface.GetPumpByNumber( pumpNumber, &pumpID ) ) ) 
		return ;

	WriteMessage( "\n Enter the Hose number you want to change the price(the hose number this pump): " ) ;
    fflush( stdin ) ;
    scanf ("%d", &hoseNumber ) ;

	if( !GoodResult( EZInterface.GetPumpHoseByNumber( pumpID, hoseNumber, &hoseID ) ) ) 
		return ;

	WriteMessage( "\n 1 - SINGLE DURATION TYPE " ) ;
	WriteMessage( "\n 2 - MULTIPLE DURATION TYPE " ) ;
	WriteMessage( "\n" ) ;
	WriteMessage( "\n Enter the duration type: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &durationType ) ;

	WriteMessage( "\n 1 - FIXED PRICE TYPE " ) ;
	WriteMessage( "\n 2 - DISCOUNT PRICE TYPE " ) ;
	WriteMessage( "\n 3 - SURTCHARGE PRICE TYPE " ) ;
	WriteMessage( "\n" ) ;
	WriteMessage( "\n Enter the price type: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &priceType ) ;

	WriteMessage( "\n The price for level 1 or zero to leave unchanged: " ) ;
    fflush( stdin ) ;
    scanf ("%lf", &price1 ) ;

	WriteMessage( "\n The price for level 2 or zero to leave unchanged: " ) ;
    fflush( stdin ) ;
    scanf ("%lf", &price2 ) ;

	if( !GoodResult( EZInterface.SetHosePrices ( hoseID, ( short ) durationType, ( short ) priceType, price1, price2 ) ) ) 
		return ;

	WriteMessage( "\n Price changed successfully" ) ;

	EndMessage() ;
}

void ChangeGradePrice()
{
	LONG	gradeID ; 
	LONG	gradeNumber ;
	LONG	level ;
	double	price ;

	WriteMessage( "\n Enter the Grade Number you want to change the price: " ) ;
    fflush( stdin ) ;
    scanf ( "%d", &gradeNumber ) ;

	if( !GoodResult( EZInterface.GetGradeByNumber ( gradeNumber, &gradeID ) ) ) 
		return ;

	WriteMessage( "\n Enter the price level you want to change, value between 1 and 8: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &level ) ;

	WriteMessage( "\n Enter the price: " ) ;
    fflush( stdin ) ;
    scanf ("%lf", &price ) ;

	if( !GoodResult( EZInterface.SetGradePrice ( gradeID, ( short ) level, price ) ) ) 
		return ;

	WriteMessage( "\n Price changed successfully" ) ;

	EndMessage() ;
}



// ----------------- Reading Cards Attendant and(or) Client ----------//
/*
void ReadingCards()
{
	LONG	idx ;
	LONG	cardCount ;
	LONG	cardID ;
	LONG	cardNumber ;
	LONG	pumpID ;
	short	cardType ;
	LONG	parentID ;
	INT64	tag ;
	DATE	timeStamp ;

	COleDateTime *oleTimeStamp = NULL ;

#if defined( _WIN32 )
	BSTR    cardName ;

#endif

	if( !GoodResult( EZInterface.GetCardReadsCount( &cardCount ) ) )
		return ;

	WriteMessage( "\n [ Count Card %03d ] --------------------------------------------------- ", cardCount ) ;
	
	for( idx = 0 ; idx < cardCount ; idx++ )
	{
		if( !GoodResult( EZInterface.GetCardReadByOrdinal( idx, &cardID ) ) )
			return ;

#if defined( _WIN32 )
		if( !GoodResult( EZInterface.GetCardReadProperties(	cardID, &cardNumber, &cardName, &pumpID,
															&cardType, &parentID, &tag, &timeStamp ) ) )
			return ;

#endif

		oleTimeStamp = new COleDateTime( timeStamp ) ;

		WriteMessage( "\n------ Card: (%03d) %d",    idx, cardID ) ;

		WriteMessage( "\nCard Number: %d  Card Name: %s  Pump ID: %d",
							cardNumber, cardName, pumpID ) ;

		WriteMessage( "\nCard Type: %d  Parent ID: %d Time Stamp: %04d-%02d-%02d %02d:%02d:%02d  TAG: %ull",
							cardType, parentID, oleTimeStamp->GetYear(), oleTimeStamp->GetMonth(), 
							oleTimeStamp->GetDay(), oleTimeStamp->GetHour(), oleTimeStamp->GetMinute(), 
							oleTimeStamp->GetSecond(), tag  ) ;

		FREE_SYS_STR( cardName ) ;
	}

	WriteMessage("\n------------------------------------------------------------------------") ;

	EndMessage() ;
}
*/

// ----------------- Register Attendant ------------------------------//

void RegisterAttendant() 
{
	char chosenType ;
		
	chosenType = ShowMenu( REGISTER_ATTENDANT_MENU ) ;

	CheckLogin();
	if( ! isConnected )
		return ;

	switch ( chosenType )
	{
		case 'A': case 'a':
			AttendantRegistration() ;
			break ;
		case 'B': case 'b':
			DeleteAttendant() ;
			break ;
		case 'C': case 'c':
			ChangeAttendantTime();
			break;
		default:
			WriteMessage("\n Unknown command!") ;
	}
}

void AttendantRegistration()
{
	LONG	idx ;
	LONG	attendantCount ;
	LONG	attendantID ;
	LONG	newAttendantID = 0 ;
	LONG	attendantNumber ;	
	short	shiftAStart ;
	short	shiftAEnd ;
	short	shiftBStart ;
	short	shiftBEnd ;
	short	attendantType = ENABLED_ATTSTATE ;
	TCHAR	attendantName[MAX_PATH] ;
	TCHAR	attendantShortName[MAX_PATH] ;
	TCHAR	password[MAX_PATH] ;
	TCHAR	tag[MAX_PATH] ;

	WriteMessage( "\n Enter the attendant number: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &attendantNumber ) ;

	WriteMessage( "\n Enter the attendant name: " ) ;
    fflush( stdin ) ;
    scanf ("%s", attendantName ) ;

	WriteMessage( "\n Enter the attendant short name: " ) ;
    fflush( stdin ) ;
    scanf ("%s", attendantShortName ) ;

	WriteMessage( "\n Enter the password: " ) ;
    fflush( stdin ) ;
    scanf ("%s", password ) ;

	WriteMessage( "\n Enter the card tag: " ) ;
    fflush( stdin ) ;
    scanf ("%s", tag ) ;

	//The time that the first shift for this attendant begins, 
	//it is in minutes from midnight, for example, 00:00 am = 0, 12:00pm = 720, 23:59 = 1439.
	WriteMessage( "\n Enter the ShiftAStart: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &shiftAStart ) ;

	WriteMessage( "\n Enter the ShiftAEnd: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &shiftAEnd ) ;

	WriteMessage( "\n Enter the ShiftBStart: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &shiftBStart ) ;

	WriteMessage( "\n Enter the ShiftBEnd: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &shiftBEnd ) ;

	if( !GoodResult( EZInterface.GetAttendantsCount( &attendantCount ) ) )
		return ;

	for( idx = attendantCount ; idx > 0 ; idx-- )
	{
		if( !GoodResult( EZInterface.GetAttendantByOrdinal( idx, &attendantID ) ) )
			return ;

		if( newAttendantID < attendantID )
			newAttendantID = attendantID ;
	}

	newAttendantID++ ;

	// BSTR AttName = (BSTR)charToWChar( attendantName ) ; 
	// BSTR AttShortName = (BSTR)charToWChar( attendantShortName ) ; 
	// BSTR AttPassword = (BSTR)charToWChar( password ) ; 
	// BSTR AttTag = (BSTR)charToWChar( tag ) ; 

	if( !GoodResult( EZInterface.SetAttendantPropertiesEx(	newAttendantID, attendantNumber, attendantName,
															attendantShortName, password, tag,
															( short ) shiftAStart, ( short ) shiftAEnd, ( short ) shiftBStart,
															( short ) shiftBEnd, attendantType ) ) )
		return ;

	//FREE_SYS_STR( AttName ) ; 
	//FREE_SYS_STR( AttShortName ) ; 
	//FREE_SYS_STR( AttPassword ) ; 
	//FREE_SYS_STR( AttTag ) ; 

	WriteMessage( "\n Attendant register successfully" ) ;

	EndMessage() ;
}

void DeleteAttendant()
{
	LONG attendantNumber ;
	LONG attendantID ;

	WriteMessage( "\n Enter the Attdendant Number you wish to delete: " ) ;
	fflush( stdin ) ;
    scanf ("%d", &attendantNumber ) ;

	if( !GoodResult( EZInterface.GetAttendantByNumber( attendantNumber, &attendantID ) ) ) 
		return ;

	if( !GoodResult( EZInterface.DeleteAttendant( attendantID ) ) ) 
		return ;

	WriteMessage( "\n Attendant delete successfully" ) ;

	EndMessage() ;
}

void ChangeAttendantTime()
{
	 //GetAttendantProperties
	LONG	attendantNumber;
	LONG	attendantID;
	short	shiftAStart;
	short	shiftAEnd;
	short	shiftBStart;
	short	shiftBEnd;
	short	attendantType;
	TCHAR	attedantName[ MAX_PATH ];
	TCHAR	attendantShortName[ MAX_PATH ];
	TCHAR	attendantPassword[ MAX_PATH ];
	TCHAR	attedantTag[ MAX_PATH ];
	

	

	WriteMessage( "\n Enter the Attendant Number you want change: " ) ;
	fflush( stdin ) ;
    scanf ("%d", &attendantNumber ) ;

	if (!GoodResult(EZInterface.GetAttendantByNumber(attendantNumber, &attendantID)))
		return;	

	if (!GoodResult(EZInterface.GetAttendantPropertiesEx(attendantID, &attendantNumber, MakeBSTR(attedantName, MAX_PATH ),
		MakeBSTR(attendantShortName, MAX_PATH ) , MakeBSTR(attendantPassword, MAX_PATH ), MakeBSTR(attedantTag, MAX_PATH ) ,
		&shiftAStart, &shiftAEnd, &shiftBStart,
		&shiftBEnd, &attendantType)))
		return;
	
	WriteMessage( "\n Enter the new ShiftAStart[0 - 1439]: " ) ;
    fflush( stdin ) ;
    scanf ("%hu", &shiftAStart ) ;

	WriteMessage( "\n Enter the new ShiftAEnd[0 - 1439]: " ) ;
    fflush( stdin ) ;
    scanf ("%hu", &shiftAEnd ) ;

	WriteMessage( "\n Enter the  new ShiftBStart[0 - 1439]: " ) ;
    fflush( stdin ) ;
    scanf ("%hu", &shiftBStart ) ;

	WriteMessage( "\n Enter the new ShiftBEnd[0 - 1439]: " ) ;
    fflush( stdin ) ;
    scanf ("%hu", &shiftBEnd ) ;

	
	if (GoodResult(EZInterface.SetAttendantPropertiesEx(attendantID, attendantNumber, attedantName,
		attendantShortName, attendantPassword, attedantTag,
		(short) shiftAStart, (short)shiftAEnd, (short)shiftBStart, (short)shiftBEnd, attendantType)))
	{
		WriteMessage("\n The time changed successfully");
	}
	else
	{
		WriteMessage("\n The time cannot to be changed.");
	}
	
	/*FREE_SYS_STR(attedantName);
	FREE_SYS_STR(attendantShortName);
	FREE_SYS_STR(attendantPassword);
	FREE_SYS_STR(attedantTag);
	*/
	EndMessage() ;
}

// ----------------- Register Client ---------------------------------//

void RegisterClient() 
{
	char chosenType ;
		
	chosenType = ShowMenu( REGISTER_CLIENT_MENU ) ;

	CheckLogin();
	if( ! isConnected )
		return ;

	switch ( chosenType )
	{
		case 'A': case 'a':
			//ClientRegistration() ;
			break ;
		case 'B': case 'b':
			DeleteClient() ;
			break ;
		default:
			WriteMessage("\n Unknown command!") ;
	}
}

/*
void ClientRegistration()
{
	SYSTEMTIME st ;
	GetLocalTime( & st ) ;
	st.wYear = st.wYear + 1000 ;
	COleDateTime eztime( st ) ;

	LONG	idx ;
	LONG	clientCount ;
	LONG	clientID ;
	LONG	newClientID = 0 ;
	LONG	clientNumber ;
	char	clientName[MAX_PATH] ;
	char	tag[MAX_PATH] ;
	short	isEnable = true ;
	LONG	priceLevel ;
	short	gradeType = ALLGRADE ;
	short	cardType = ATTENDANT_CARD_TYPE ;
	short	limitType = DOLLAR_PRESET_TYPE ;
	double	limit ;
	short	entryType = NO_ENTRY_TYPE ;
	LONG	parentID = -1 ;

#if defined( _WIN32 )
	BSTR	plate = NULL ;

#endif

	WriteMessage( "\n Enter the client number: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &clientNumber ) ;

	WriteMessage( "\n Enter the client name: " ) ;
    fflush( stdin ) ;
    scanf ("%s", clientName ) ;

	WriteMessage( "\n Enter the card tag: " ) ;
    fflush( stdin ) ;
    scanf ("%s", tag ) ;

	BSTR AttClientName =	CharToBstr( clientName ) ;  
	BSTR AttTag =			CharToBstr( tag ) ;

	WriteMessage( "\n Enter the price level: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &priceLevel ) ;

	WriteMessage( "\n Enter the limit $$ that this card can delivery: " ) ;
    fflush( stdin ) ;
    scanf ("%lf", &limit ) ;

	if( !GoodResult( EZInterface.GetCardClientsCount( &clientCount ) ) )
		return ;

	for( idx = clientCount ; idx > 0 ; idx-- )
	{
		if( !GoodResult( EZInterface.GetCardClientByOrdinal( idx, &clientID ) ) )
			return ;

		if( newClientID < clientID )
			newClientID = clientID ;
	}

	newClientID++ ;

	if( !GoodResult( EZInterface.SetCardClientPropertiesEx2( newClientID, clientNumber, 
															AttClientName, AttTag,
															isEnable, ( short ) priceLevel,
															plate, gradeType, cardType, limitType,
															limit, entryType, eztime, parentID ) ) )
		return ;

	FREE_SYS_STR( AttClientName ) ; 
	FREE_SYS_STR( AttTag ) ; 

	WriteMessage( "\n Client register successfully" ) ;

	EndMessage() ;
}
*/


void DeleteClient()
{
	LONG	clientNumber ;
	LONG	clientID ;

	WriteMessage( "\n Enter the Client Number you wish to delete: " ) ;
	fflush( stdin ) ;
    scanf ("%d", &clientNumber ) ;

	if( !GoodResult( EZInterface.GetCardClientByNumber( clientNumber, &clientID ) ) ) 
		return ;

	if( !GoodResult( EZInterface.DeleteCardClient( clientID ) ) ) 
		return ;

	WriteMessage( "\n Client delete successfully" ) ;

	EndMessage() ;
}


// ----------------- Tanks and Sensors Reading -----------------------//

void TanksSensorsReading() 
{
	char chosenType ;
		
	chosenType = ShowMenu( TANKS_SENSORS_READING_MENU ) ;

	CheckLogin();
	if( ! isConnected )
		return ;

	switch ( chosenType )
	{
		case 'A': case 'a':
			TankReading() ;
			break ;
		case 'B': case 'b':
			MonitoringSensor() ;
			break ;
		default:
			WriteMessage("\n Unknown command!") ;
	}
}

void TankReading()
{
    LONG   Idx;
    LONG   Ct;
    LONG   Id;
    LONG   Number;
    LONG   GradeID;
    short  TType;
    double Capacity;
    double Diameter;
    double TheoVolume;
    double GaugeVolume;
    double GaugeTCVolume;
    double GaugeUllage;
    double GaugeTemperature;
    double GaugeLevel;
    double GaugeWaterVolume;
    double GaugeWaterLevel;
    LONG   GaugeID;
    short  ProbeNo;

#if defined(_WIN32)
    BSTR   Name;
#elif defined(__linux__)
    TCHAR   Name[MAX_PATH];
#endif

    // Verifica conexao
    if( !isConnected)
      return;

    //--------------------------------------------------------------------
    // Le o numero de produtos configurados
    if( !GoodResult( EZInterface.GetTanksCount( &Ct ) ) )
      return;

	WriteMessage("\n[Tanques %ld]---------------------------------------------------", Ct);

    for(Idx=1; Idx<=Ct; Idx++)
	{
       if( EZInterface.GetTankByOrdinal( Idx, &Id )!=0 )
          return;

#if defined(_WIN32)
       if( GoodResult( EZInterface.GetTankProperties(Id, &Number, &Name, &GradeID,
                                                         &TType, &Capacity, &Diameter,
                                                         &TheoVolume, &GaugeVolume,
                                                         &GaugeTCVolume, &GaugeUllage,
                                                         &GaugeTemperature, &GaugeLevel,
                                                         &GaugeWaterVolume, &GaugeWaterLevel,
                                                         &GaugeID, &ProbeNo ) ) )
#elif defined(__linux__)
	   if( GoodResult( EZInterface.GetTankProperties(Id, &Number,
														 MakeBSTR(Name, MAX_PATH ),
														 &GradeID,
														 &TType, &Capacity, &Diameter,
														 &TheoVolume, &GaugeVolume,
														 &GaugeTCVolume, &GaugeUllage,
														 &GaugeTemperature, &GaugeLevel,
														 &GaugeWaterVolume, &GaugeWaterLevel,
														 &GaugeID, &ProbeNo ) ) )
#endif


	   {
          WriteMessage("\n  Tanque: %02ld  Nome: %s  Produto: %02ld  Tipo: %02d",
								Number, Name, GradeID, TType);

          WriteMessage("\n     Capacidade: %.02f  Diametro: %.02f",
								Capacity, Diameter );

          WriteMessage("\n     TheoVolume: %.02f  GaugeVolume: %.02f  GaugeTCVolume: %.02f",
												TheoVolume, GaugeVolume, GaugeTCVolume);

          WriteMessage("\n     GaugeUllage: %.02f  GaugeTemperature:  %.02f  GaugeLevel: %.02f",
												GaugeUllage, GaugeTemperature, GaugeLevel );

          WriteMessage("\n     GaugeWaterVolume: %.02f  GaugeWaterLevel: %.02f  GaugeID: %02ld  ProbeNo: %02d",
								GaugeWaterVolume, GaugeWaterLevel, GaugeID, ProbeNo);
	   }

	}

    WriteMessage("\n");
}

void MonitoringSensor()
{
	LONG	idx ;
	LONG	sensorCount ;
	LONG	sensorID ;
	LONG	sensorNumber ;
	LONG	portID ;
	short	sensorType ;
	short	sensorAddress ;
	short	sensorNo ;

#if defined(_WIN32)
	BSTR	sensorName ;
#elif defined(__linux__)
	TCHAR    sensorName[MAX_PATH];
#endif

	if( !GoodResult( EZInterface.GetSensorsCount( &sensorCount ) ) )
      return ;

	WriteMessage( "\n [ Count Sensors %03d ] ------------------------------ ", sensorCount ) ;

    for( idx = sensorCount ; idx > 0 ; idx-- )
	{

		if( !GoodResult( EZInterface.GetSensorByOrdinal( idx, &sensorID ) ) )
          return;

#if defined( _WIN32 )
		if( GoodResult( EZInterface.GetSensorProperties(		sensorID,			&sensorNumber,		&sensorName,
																&portID,			&sensorType,		&sensorAddress,			
																&sensorNo		) ) )
#elif defined(__linux__)
		if( GoodResult( EZInterface.GetSensorProperties(		sensorID,			&sensorNumber,		MakeBSTR(sensorName, MAX_PATH ),
																&portID,			&sensorType,		&sensorAddress,			
																&sensorNo		) ) )	
#endif

		WriteMessage("\n\n\t SensorID: %d   SensorNumber: %d  SensorName: %s ",
											sensorID, sensorNumber, sensorName );
		WriteMessage("\n\t PortID: %d  SensorType: %d  SensorAddress: %d   ",
											portID, sensorType, sensorAddress );
		WriteMessage("\n\t SensorNo: %d ", sensorNo );

		//FREE_SYS_STR( sensorName ) ; 
	}

	EndMessage() ;
}


// ----------------- General Configuration Facility ------------------//

void GeneralConfigurationFacility() 
{
	char chosenType ;
		
	chosenType = ShowMenu( GENERAL_CONFIGURATION_FACILITY_MENU ) ;

	CheckLogin();
	if( ! isConnected )
		return ;

	switch ( chosenType )
	{
		case 'A': case 'a':
			DeliveryPositionRegister() ;
			break ;
		case 'B': case 'b':
			DeleteDeliveryPosition() ;
			break ;
		case 'C': case 'c':
			HoseRegistration() ;
			break ;
		case 'D': case 'd':
			DeleteHose() ;
			break ;
		case 'E': case 'e':
			//GradeRegister() ;
			break ;
		case 'F': case 'f':
			DeleteGrade() ;
		case 'G': case 'g':
			TankRegistration() ;
			break ;
		case 'H': case 'h':
			DeleteTank() ;
			break ;
		case 'I': case 'i':
			//ZigbeeDeviceRegistration() ;
			break ;
		case 'J': case 'j':
			//DeleteZigbeeDevice() ;
			break ;
		default:
			WriteMessage("\n Unknown command!") ;
	}
}


void DeliveryPositionRegister()
{
	LONG	idx ;
	LONG	pumpCount ;
	LONG	pumpID = NULL_ID ;
	LONG	newPumpID = NULL_ID ;
	LONG	pumpNumber ;
	LONG	pumpPhysicalNumber ;
	LONG	pumpSide ;
	LONG	pumpAddress ;
	LONG	priceLevel1 ;
	LONG	priceLevel2 ;
	short	priceDspFormat = PUMP_DISPLAY_4_2 ;
	short	volumeDspFormat = PUMP_DISPLAY_6_2 ;
	short	valueDspFormat = PUMP_DISPLAY_6_2 ;
	short	pumpType = 0x04 ;					//EZSim, Details, see PumpType of Pumps at EZDrive.ini			        
	LONG	portID = 0x01 ;
	LONG	attendantID = NULL_ID ;
	short	authMode = AUTO_AUTH ;
	short	stackMode = STACK_AUTO ;
	short	prepayAllowed = 0 ;
	short	preauthAllowed = 0 ;
	LONG	slotZigBeeID = NULL_ID ;
	LONG	muxSlotZigBeeID = NULL_ID ;
	short	priceControl = REMOTE_PRICE_CONTROL ;
	short	hasPreset = 0x01 ;
	TCHAR	pumpName[MAX_PATH] ;

	WriteMessage( "\n Enter the PumpNumber: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &pumpNumber ) ;

	WriteMessage( "\n Enter the PumpName: " ) ;
    fflush( stdin ) ;
    scanf ("%s", pumpName ) ;

	//BSTR AttPumpName =	(BSTR)charToWChar( pumpName ) ;  

	WriteMessage( "\n Enter the PhysicalNumber: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &pumpPhysicalNumber ) ;

	WriteMessage( "\n Enter the PumpSide: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &pumpSide ) ;

	WriteMessage( "\n Enter the PumpAddress: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &pumpAddress ) ;

	WriteMessage( "\n Enter the PriceLevel1: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &priceLevel1 ) ;

	WriteMessage( "\n Enter the PriceLevel2: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &priceLevel2 ) ;

	WriteMessage( "\n Enter the Slot ( 1 - 4 ) or ZigBeeID ( 5> ): " ) ;
    fflush( stdin ) ;
    scanf ("%d", &slotZigBeeID ) ;

	if( !GoodResult( EZInterface.GetPumpsCount( &pumpCount ) ) )
		return ;

	for( idx = pumpCount ; idx > 0 ; idx-- )
	{
		if( !GoodResult( EZInterface.GetPumpByOrdinal( idx, &pumpID ) ) )
			return ;

		if( newPumpID < pumpID )
			newPumpID = pumpID ;
	}

	newPumpID++ ;

	if( !GoodResult( EZInterface.SetPumpPropertiesEx(		newPumpID, pumpNumber, pumpName, ( short ) pumpPhysicalNumber,
															( short ) pumpSide, ( short ) pumpAddress, ( short ) priceLevel1, 
															( short ) priceLevel2, ( short ) priceDspFormat, ( short ) volumeDspFormat,
															( short ) valueDspFormat, pumpType, portID, attendantID,
															authMode, stackMode, prepayAllowed, preauthAllowed,
															slotZigBeeID, muxSlotZigBeeID, priceControl, hasPreset ) ) )
		return ;

	//FREE_SYS_STR( AttPumpName ) ; 

	WriteMessage( "\n Pump register successfully" ) ;

	EndMessage() ;
}


void DeleteDeliveryPosition()
{
	LONG	pumpNumber ;
	LONG	pumpID ;

	WriteMessage( "\n Enter the Position Number you wish to delete: " ) ;
	fflush( stdin ) ;
    scanf ("%d", &pumpNumber ) ;

	if( !GoodResult( EZInterface.GetPumpByNumber( pumpNumber, &pumpID ) ) ) 
		return ;

	if( !GoodResult( EZInterface.DeletePump( pumpID ) ) ) 
		return ;

	WriteMessage( "\n Delivery Position delete successfully" ) ;

	EndMessage() ;
}


void HoseRegistration()
{
	LONG	idx ;
	LONG	hoseCount ;
	LONG	hoseID ;
	LONG	newHoseID = 0 ;
	LONG	hoseNumber ;
	LONG	pumpID ;
	LONG	pumpNumber ;
	LONG	tankID ;
	LONG	tankNumber ;
	LONG	hosePhysicalNumber ;
	double	mtrTheoValue = 0 ;
	double	mtrTheoVolume = 0 ;
	double	mtrElecValue = 0 ;
	double	mtrElecVolume = 0 ;
	short	UVEAtenna = FALSE ;
	double	price1 = UNKNOWN_PRICE_CONTROL ;
	double	price2 = UNKNOWN_PRICE_CONTROL ;
	short	isEnabled = TRUE ;

	WriteMessage( "\n Enter the Hose Number: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &hoseNumber ) ;

	WriteMessage( "\n Enter the Pump Number: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &pumpNumber ) ;

	WriteMessage( "\n Enter the Tank Number: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &tankNumber ) ;

	WriteMessage( "\n Enter the Hose Physical Number: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &hosePhysicalNumber ) ;

	if( !GoodResult( EZInterface.GetHosesCount( &hoseCount ) ) )
		return ;

	for( idx = hoseCount ; idx > 0 ; idx-- )
	{
		if( !GoodResult( EZInterface.GetHoseByOrdinal( idx, &hoseID ) ) )
			return ;

		if( newHoseID < hoseID )
			newHoseID = hoseID ;
	}

	newHoseID++ ;

	if( !GoodResult( EZInterface.GetPumpByNumber( pumpNumber, &pumpID ) ) ) 
		return ;

	if( !GoodResult( EZInterface.GetTankByNumber( tankNumber, &tankID ) ) ) 
		return ;

	if( !GoodResult( EZInterface.SetHosePropertiesEx2(		newHoseID, hoseNumber, pumpID, tankID, hosePhysicalNumber,
															mtrTheoValue, mtrTheoVolume, mtrElecValue, mtrElecVolume,
															UVEAtenna, price1, price2, isEnabled ) ) )
		return ;

	WriteMessage( "\n Hose register successfully" ) ;

	EndMessage() ;
}


void DeleteHose()
{
	LONG	hoseNumber ;
	LONG	pumpNumber ;
	LONG	hoseID ;
	LONG	pumpID ;

	WriteMessage( "\n Enter the Pump Number related to the hose: " ) ;
	fflush( stdin ) ;
    scanf ("%d", &pumpNumber ) ;

	WriteMessage( "\n Enter the Hose Number you wish to delete: " ) ;
	fflush( stdin ) ;
    scanf ("%d", &hoseNumber ) ;

	if( !GoodResult( EZInterface.GetPumpByNumber( pumpNumber, &pumpID ) ) ) 
		return ;

	if( !GoodResult( EZInterface.GetPumpHoseByNumber( pumpID, hoseNumber, &hoseID ) ) ) 
		return ;

	if( !GoodResult( EZInterface.DeleteHose( hoseID ) ) ) 
		return ;

	WriteMessage( "\n Hose delete successfully" ) ;

	EndMessage() ;
}


void GradeRegister()
{
	LONG	idx ;
	LONG	gradeCount ;
	LONG	gradeID ;
	LONG	newGradeID = 0 ;
	LONG	gradeNumber ;
	TCHAR	gradeName[MAX_PATH] ;
	TCHAR	gradeShortName[MAX_PATH] ;
	TCHAR	gradeCode[MAX_PATH] ;
	short	gradeType = 0x00 ;					//Other, Details, see GradeType at EZATG.ini file		

	WriteMessage( "\n Enter the Grade Number: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &gradeNumber ) ;

	WriteMessage( "\n Enter the Grade Name: " ) ;
    fflush( stdin ) ;
    scanf ("%s", gradeName ) ;

	WriteMessage( "\n Enter the Grade ShortName: " ) ;
    fflush( stdin ) ;
    scanf ("%s", gradeShortName ) ;

	WriteMessage( "\n Enter the Grade Code: " ) ;
    fflush( stdin ) ;
    scanf ("%s", gradeCode ) ;
//aqui
    #if defined( _WIN32 )

	BSTR	AttGradeName =	(BSTR)charToWChar( gradeName ) ;
	BSTR	AttGradeShortName = (BSTR)charToWChar( gradeShortName ) ;
	BSTR	AttGradeCode =	(BSTR)charToWChar( gradeCode ) ;

	#elif(__linux__)

	
	#endif


	if( !GoodResult( EZInterface.GetGradesCount( &gradeCount ) ) )
		return ;

	for( idx = gradeCount ; idx > 0 ; idx-- )
	{
		if( !GoodResult( EZInterface.GetGradeByOrdinal( idx, &gradeID ) ) )
			return ;

		if( newGradeID < gradeID )
			newGradeID = gradeID ;
	}

	newGradeID++ ;

	if( !GoodResult( EZInterface.SetGradePropertiesEx(		newGradeID , gradeNumber, gradeName , 
															gradeShortName , gradeCode  , gradeType ) ) )
		return ;



	//FREE_SYS_STR( AttGradeName ) ; 
	//FREE_SYS_STR( AttGradeShortName ) ; 
	//FREE_SYS_STR( AttGradeCode ) ; 

	WriteMessage( "\n Grade register successfully" ) ;

	EndMessage() ;
}

void DeleteGrade()
{
	LONG	gradeNumber ;
	LONG	gradeID ;

	WriteMessage( "\n Enter the grade number you wish to delete: " ) ;
	fflush( stdin ) ;
    scanf ("%d", &gradeNumber ) ;

	if( !GoodResult( EZInterface.GetGradeByNumber( gradeNumber, &gradeID ) ) ) 
		return ;

	if( !GoodResult( EZInterface.DeleteGrade( gradeID ) ) ) 
		return ;

	WriteMessage( "\n Grade delete successfully" ) ;

	EndMessage() ;
}


void TankRegistration()
{
	LONG	idx ;
	LONG	tankCount ;
	LONG	tankID ;
	LONG	newTankID = 0 ;
	LONG	tankNumber ;
	char	tankName[MAX_PATH] ;
	LONG	gradeID ;
	LONG	gradeNumber ;
	short	tankType = GAUGED_TANK_TYPE ;
	double  capacity ;
	double	diameter ; 					  
	double  theoVolume = 0 ; 
	double  gaugeVolume = 0 ; 
	double  gaugeTCVolume = 0 ; 
	double  gaugeUllage = 0 ;
	double  gaugeTemperature = 0 ; 			  
	double  gaugeLevel = 0 ;
	double  gaugeWaterVolume = 0 ;
	double  gaugeWaterLevel = 0 ;
	LONG	gaugeID = 5 ;
	LONG	probeNo ; 
	LONG	gaugeAlarmsMask = TANK_RESPONDING_BIT ;

	WriteMessage( "\n Enter the Tank Number: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &tankNumber ) ;

	WriteMessage( "\n Enter the Tank Name: " ) ;
    fflush( stdin ) ;
    scanf ("%s", tankName ) ;

	WriteMessage( "\n Enter the Grade Number: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &gradeNumber ) ;

	WriteMessage( "\n Enter the Capacity: " ) ;
    fflush( stdin ) ;
    scanf ("%lf", &capacity ) ;

	WriteMessage( "\n Enter the Diameter: " ) ;
    fflush( stdin ) ;
    scanf ("%lf", &diameter ) ;

	WriteMessage( "\n Enter the ProbeNo: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &probeNo ) ;

	// BSTR	AttTankName =	(BSTR)charToWChar( tankName ) ;

	if( !GoodResult( EZInterface.GetTanksCount( &tankCount ) ) )
		return ;

	for( idx = tankCount ; idx > 0 ; idx-- )
	{
		if( !GoodResult( EZInterface.GetTankByOrdinal( idx, &tankID ) ) )
			return ;

		if( newTankID < tankID )
			newTankID = tankID ;
	}

	newTankID++ ;

	if( !GoodResult( EZInterface.GetGradeByNumber( gradeNumber, &gradeID ) ) )
		return ;

	if( !GoodResult( EZInterface.SetTankPropertiesEx(		newTankID , tankNumber, tankName, 
															gradeID , tankType , capacity , diameter , 
															theoVolume , gaugeVolume , gaugeTCVolume, 
															gaugeUllage, gaugeTemperature , gaugeLevel ,
															gaugeWaterVolume, gaugeWaterLevel, gaugeID, 
															( short ) probeNo , gaugeAlarmsMask ) ) )
		return ;

	//FREE_SYS_STR( AttTankName ) ; 

	WriteMessage( "\n Tank register successfully" ) ;

	EndMessage() ;
}

void DeleteTank()
{
	LONG	tankNumber ;
	LONG	tankID ;

	WriteMessage( "\n Enter the Tank number you wish to delete: " ) ;
	fflush( stdin ) ;
    scanf ("%d", &tankNumber ) ;

	if( !GoodResult( EZInterface.GetTankByNumber( tankNumber, &tankID ) ) ) 
		return ;

	if( !GoodResult( EZInterface.DeleteGrade( tankID ) ) ) 
		return ;

	WriteMessage( "\n Tank delete successfully" ) ;

	EndMessage() ;
}


void ZigbeeDeviceRegistration() 
{
	LONG	idx ;
	LONG	ZBCount ;
	LONG	ZBID ; 
	LONG	newZBID = 0 ;
	LONG	ZBNumber ;
	char	ZBName[ MAX_PATH ] ;
	LONG	deviceType ;
	char	serialNumber[ MAX_PATH ] ;
	BSTR	nodeIdentifier = NULL ;
	LONG	portID = USB1 ;

	WriteMessage( "\n Enter the ZigBee Device Number: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &ZBNumber ) ;

	WriteMessage( "\n Enter the ZigBee Device Name: " ) ;
    fflush( stdin ) ;
    scanf ("%s", ZBName ) ;

	WriteMessage( "\n 5 - EZRemote connected wirelessly. " ) ;
	WriteMessage( "\n 6 - 9  EZRemote 6(Slot1), 7(Slot2)..." ) ;
	WriteMessage( "\n Enter the ZigBee Device Type: " ) ;
    fflush( stdin ) ;
    scanf ("%d", &deviceType ) ;

	WriteMessage( "\n Enter the ZigBee Device Serial Number: " ) ;
    fflush( stdin ) ;
    scanf ("%s", serialNumber ) ;

	//BSTR	AttZBName =	(BSTR)charToWChar( ZBName ) ;
	//BSTR	AttSerialNumber = (BSTR)charToWChar( serialNumber ) ;

	if( !GoodResult( EZInterface.GetZigBeeCount( &ZBCount ) ) )
		return ;

	for( idx = ZBCount ; idx > 0 ; idx-- )
	{
		if( !GoodResult( EZInterface.GetZigBeeByOrdinal( idx, &ZBID ) ) )
			return ;

		if( newZBID < ZBID )
			newZBID = ZBID ;
	}

	newZBID++ ;

	if( !GoodResult( EZInterface.SetZigBeeProperties(		newZBID , ZBNumber , ZBName , ( short ) deviceType ,
															serialNumber , nodeIdentifier , portID ) ) )
		return ;

	//FREE_SYS_STR( AttSerialNumber ) ;
	//FREE_SYS_STR( AttZBName ) ; 

	WriteMessage( "\n ZigBee Device register successfully" ) ;

	EndMessage() ;
}


void DeleteZigbeeDevice()
{
	LONG	ZBNumber ;
	LONG	ZBID ;

	WriteMessage( "\n Enter the Zigbee Device number you wish to delete: " ) ;
	fflush( stdin ) ;
    scanf ("%d", &ZBNumber ) ;

	if( !GoodResult( EZInterface.GetZigBeeByNumber( ZBNumber, &ZBID ) ) ) 
		return ;

	if( !GoodResult( EZInterface.DeleteZigBee( ZBID ) ) ) 
		return ;

	WriteMessage( "\n Zigbee Device delete successfully" ) ;

	EndMessage() ;
}




// ------------------ Outras funções ---------------------------------//

/*BSTR CharToBstr(  const char* text )
{
    size_t size = STRLEN( text ) + 1;
	BSTR res =  SysAllocStringByteLen( NULL , size * sizeof( wchar_t ) ) ;
    mbstowcs( res , text , size );
	return res ;
}*/
/* --------------------- funções antigas -------------------------------//




                 --------------------------------



                As funções abaixo serão verificadas.




                 --------------------------------



// -----------------------------------------------------------------------/*/
void HelpText(int level)
{

	switch(level)
	{
		case 0:  // ajuda de linha de comando
			WriteMessage("\n\nSintexe:");
			WriteMessage("\n\t/events      - Processamento por eventos.");
			WriteMessage("\n\t/server addr - Ajusta endereco do EZServer.");
			WriteMessage("\n\t/?           - Imprime ajuda.");
			break;

		case 1:  // ajuda para tempo de execucao
			WriteMessage("\nMenu:");
			WriteMessage("\n\t 0 a 9 - Seleciona bomba ( 0 = Bomba 10)");
			WriteMessage("\n\t     A - Autoriza/Desautoriza");
			WriteMessage("\n\t     P - Troca Preco");
			WriteMessage("\n\t     S - Envia Preset");
			WriteMessage("\n\t     T - Le Totalizadores (Encerrantes)");
			WriteMessage("\n\t     U - Le Abastecimentos");
			WriteMessage("\n\t     I - Lista Configuracao");
			WriteMessage("\n\t     ? - Exibe menu;");
			WriteMessage("\n\t   ESC - Sair");
			WriteMessage("\n");
			break;
	}
}

//----------------------------------------------------------------------------
// Avalia retorno das APIS EZForecourt e gera mensagem de erro

//------------------------------------------------------------------------------
// Calcula o codigo referente ao ID do bico nos concentradores CBC da Companytec.
//    HoseNumber: numero fisico do bico na bomba
//    PumpNumber: numero da bomba
//		     cid: condigo do bico HEXA em ASCII
//
void CompanyID(short HoseNumber, short PumpNumber, char *cid)
{
	LONG Offset;

	switch(HoseNumber)
	{
	    case  2: Offset = 0x44;
	    case  3: Offset = 0x84;
	    case  4: Offset = 0xC4;
		default: // Outros valores são tratados como Bico 1
			Offset = 0x04;
			break;
	}
	//aqui - verificar
	sprintf(cid, "%02ld", ((PumpNumber-1)+Offset) );
}

//-----------------------------------------------------------------------------
// Converte char array para Wide-Char
//static wchar_t* charToWChar(const char* text)
//{
//    size_t size = STRLEN(text) + 1;
//	wchar_t* wa = new wchar_t[size];
//
//    mbstowcs(wa,text,size);
//
//    return wa;
//}

//-----------------------------------------------------------------------------
PBSTR MakeBSTR( TCHAR* pStr , int Len )
{
	for ( int i = 0 ; i+1 < Len ; pStr[i++] = ' ' ) ;
	pStr[ Len - 1 ] = 0 ;
	return ( PBSTR ) pStr ;
}

//-----------------------------------------------------------------------------
// Executa Login
void CheckLogin()
{

	if( ! isConnected || ! GoodResult( EZInterface.TestConnection() ) )
	{

		if( GoodResult( EZInterface.ClientLogonEx( 15,
												   (runEvents?7:1),
												   EZServerAddr ,
												   5123, 5124, 10000, 0, 0, 0) ) )
		{
			WriteMessage("Conectado: %s\n", EZServerAddr);
			isConnected = true;
		}
		else
		{
			WriteMessage("ERRO conectando: %s\n", EZServerAddr);
			isConnected = false;
		}
	}
}

//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void PumpAuthorizeCancel()
{
	int  Bomba;
	LONG IdBomba;

	Bomba = appPump;   // Le o numero da bomba no combo

	// Verifica conexao
	if( isConnected )
	{
		// Pega Id da Bomba escolhida
		if( !GoodResult( EZInterface.GetPumpByOrdinal(Bomba, &IdBomba) ) )
		  return;

		switch( lastStatus[Bomba-1] ) 				// PAM1000
		{
    		case AUTHED_PUMP_STATE            :		// 9 - AUTHORIZED

				// Envia bloqueio (desautorizacao) para bomba
				if( !GoodResult( EZInterface.CancelAuthorise(IdBomba) ) )
					WriteMessage("\n Bomba %02d Desautorizada!", Bomba);

				break;

			case IDLE_PUMP_STATE              :		// 1 - IDLE
    		case PRICE_CHANGE_STATE           :		// 1 - IDLE
    		case DELIVERY_TIMEOUT_PUMP_STATE  :		// 1 - IDLE
    		case PREPAY_REFUND_TIMEOUT_STATE  :		// 1 - IDLE
    		case CALLING_PUMP_STATE           :		// 5 - CALL
    		case HOSE_OUT_PUMP_STATE          :		// 5 - CALL
    		case TEMP_STOPPED_PUMP_STATE      :		// 8 - STOP

				// Envia Autorizacao para bomba
				if( !GoodResult( EZInterface.Authorise(IdBomba) ) )
					WriteMessage("\n Bomba %02d Autorizada!", Bomba);

				break;

			case DELIVERY_TERMINATED_STATE    :		// 3 - EOT
    		case DELIVERY_FINISHING_PUMP_STATE:		// 2 - BUSY
    		case DELIVERY_FINISHED_PUMP_STATE :		// 2 - BUSY
    		case DELIVERY_STARTING_PUMP_STATE :		// 2 - BUSY
    		case DELIVERING_PUMP_STATE        :		// 2 - BUSY
			case ERROR_PUMP_STATE             :		// 0 - OFFLINE
    		case NOT_RESPONDING_2_PUMP_STATE  :
			case LAST_PUMP_STATE              :
    		case INVALID_PUMP_STATE           :		// 0 - OFFLINE
    		case NOT_INSTALLED_PUMP_STATE     :		// 6 - CLOSE
    		case NOT_RESPONDING_1_PUMP_STATE  :		// 0 - OFFLINE
			default							  :
				WriteMessage("\n Bomba %02d nao pode mudar de estado!", Bomba);
				break;
		}
	}
}


//----------------------------------------------------------------------------
void ChangePrice()
{
    int    Bomba;
    int    Bico;
    LONG   IdBico;
    short  Duracao;
    short  Tipo;
    double Valor1;
    double Valor2;

    int    Index;
    LONG   Bicos;

    LONG   HNumber;
    LONG   PhysicalNumber;
    LONG   PumpID;
    LONG   PumpNumber;
    LONG   TankID;
    LONG   TankNumber;
    LONG   GradeID;
    LONG   GradeNumber;
    double MtrTheoValue;
    double MtrTheoVolume;
    double trElecValue;
    double MtrElecVolume;
    double Price1;
    double Price2;
    short  HEnabled;

#if defined(_WIN32)
    BSTR   PumpName;
    BSTR   TankName;
    BSTR   GradeName;
    BSTR   GradeShortName;
    BSTR   GradeCode;
#elif defined(__linux__)
    TCHAR   PumpName[MAX_PATH];
    TCHAR   TankName[MAX_PATH];
    TCHAR   GradeName[MAX_PATH];
    TCHAR   GradeShortName[MAX_PATH];
    TCHAR   GradeCode[MAX_PATH];
#endif

    Duracao      = MULTIPLE_DURATION_TYPE; // Duracao do preco (Multipos abastecimentos)
    Tipo         = FIXED_PRICE_TYPE;  // Tipo de preco (Fixo)
    Bomba        = appPump;   // Le o numero da bomba

    // Verifica se esta conectado ao servidor
    if( !isConnected )
      return;

	WriteMessage("\n Bomba %02d - Troca de precos", Bomba);

	WriteMessage("\n\t  Bico (1 a 6): "); if(scanf("%d", &Bico)==1){printf("sucess\n");}else{printf("input failed\n");}
	WriteMessage("\n\t Preco nivel 1:");  if(scanf("%lf", &Valor1)==1){printf("sucess\n");}else{printf("input failed\n");}
	WriteMessage("\n\t Preco nivel 2:");  if(scanf("%lf", &Valor2)==1){printf("sucess\n");}else{printf("input failed\n");}

    // Le o numero de bicos cadastrados
    if( !GoodResult( EZInterface.GetHosesCount(&Bicos) ) )
      return;

    for(Index=1; Index<Bicos; Index++)
	{

      // Pega o ID do bico
      if( !GoodResult( EZInterface.GetHoseByOrdinal(Index, &IdBico) ) )
        return;

#if defined(_WIN32)

      // Pega os dados do bico
      if( GoodResult( EZInterface.GetHoseSummaryEx(IdBico, &HNumber,        &PhysicalNumber,
                                                           &PumpID,         &PumpNumber,  &PumpName,
                                                           &TankID,         &TankNumber,  &TankName,
                                                           &GradeID,        &GradeNumber, &GradeName,
                                                           &GradeShortName, &GradeCode,
                                                           &MtrTheoValue,   &MtrTheoVolume,
                                                           &trElecValue,    &MtrElecVolume, &Price1,
                                                           &Price2,         &HEnabled) ) )

#elif defined(__linux__)

		// Pega os dados do bico
		if( GoodResult( EZInterface.GetHoseSummaryEx(IdBico, &HNumber,        &PhysicalNumber,
															 &PumpID,         &PumpNumber,
															 MakeBSTR(PumpName, MAX_PATH),
															 &TankID,         &TankNumber,
															 MakeBSTR(TankName, MAX_PATH),
															 &GradeID,        &GradeNumber,
															 MakeBSTR(GradeName, MAX_PATH),
															 MakeBSTR(GradeShortName, MAX_PATH),
															 MakeBSTR(GradeCode, MAX_PATH),
															 &MtrTheoValue,   &MtrTheoVolume,
															 &trElecValue,    &MtrElecVolume, &Price1,
															 &Price2,         &HEnabled) ) )
#endif
      {

        // Verifica se o ID co bico pertence o escolhido
        if( (Bomba==PumpNumber) && (Bico==HNumber) )
		{

			WriteMessage("\n\t\t Precos Atual: Bomba %02ld Bico %02ld Preco1 R$%.03f  Preco2 R$%.03f",
																PumpNumber, HNumber, Price1, Price2);

            break;
		}
	  }
	}

    // Faz ajuste do preço na bomba
    if( GoodResult( EZInterface.SetHosePrices( IdBico, Duracao, Tipo, Valor1, Valor2) ) )
	{
		WriteMessage("\n\tPreco Novo: Bomba %02d Bico %02d Preco1 R$%.03f Preco2 R$%.03f (Duraticao %d Tipo %d)",
																		Bomba, Bico, Valor1, Valor2, Duracao, Tipo );
	}
}

//----------------------------------------------------------------------------
void PumpPreset()
{
    int    Bomba;
    int    Bico;
    LONG   IdBomba;
    LONG   IdBico;
    short  LType;
    double PsValue;

    Bomba        = appPump;   // Le o numero da bomba

	WriteMessage("\n Bomba %02d - Preset", Bomba);

	WriteMessage("\n\t               Bico (1 a 6): "); 
	if(scanf("%d",  &Bico)==1){printf("sucess\n");}else{printf("Input Failed\n");}
	WriteMessage("\n\t Tipo (1=Dinheiro 2=Volume): "); 
	if(scanf("%hi", &LType)==1){printf("sucess\n");}else{printf("Input Failed\n");}
	WriteMessage("\n\t                      Valor: ");
	if(scanf("%lf", &PsValue)==1){printf("sucess\n");}else{printf("Input Failed\n");}

	LType = (LType==1?DOLLAR_PRESET_TYPE:VOLUME_PRESET_TYPE);

    // Verifica conexao
    if( !isConnected )
      return;

    // Pega Id da Bomba escolhida
    if( !GoodResult( EZInterface.GetPumpByOrdinal(Bomba, &IdBomba) ) )
      return;

    IdBico = (1<<(Bico-1));  // Calcula ID do bico escolhido

    // Envia preset para bomba
    if( GoodResult( EZInterface.LoadPreset(IdBomba, LType, PsValue, IdBico, 1) ) )
	{
		WriteMessage("\n\t Preset Enviado: Bomba %02d Bico %02d Tipo %d Valor %.03f Nivel 1",
							Bomba, Bico, LType, PsValue);
	}
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------//
void ReadTotals()
{
    LONG   IdBomba;
    LONG   IdBico;

    LONG   Bomba;
    LONG   Bico;

    LONG   Number;
    LONG   PumpID;
    LONG   TankID;
    LONG   PhysicalNumber;
    double MtrTheoValue;
    double MtrTheoVolume;
    double MtrElecValue;
    double MtrElecVolume;
    short  UVEAntenna;
    double Price1;
    double Price2;
    short  Enabled;

    Bomba = appPump;   // Le o numero da bomba
    //Bico         := cbHose.ItemIndex+1;   // Le o numero da bico no combo

    // Verifica conexao
    if( !isConnected )
      return;

    // Pega Id da Bomba escolhida
    if( !GoodResult( EZInterface.GetPumpByOrdinal(Bomba, &IdBomba) ) )
        return;

	WriteMessage("\n Encerrantes:  Bomba %02ld", Bomba);

	for(Bico=1; Bico<7; Bico++)
	{
		// Le Id do Bico (sem GoodResult() para evitar mensagens no final)
		if( EZInterface.GetPumpHoseByNumber(IdBomba, Bico, &IdBico)!=0 )
		  return;

		// Le dados do Bico
		if( GoodResult( EZInterface.GetHosePropertiesEx2(IdBico, &Number, &PumpID, &TankID,
																 &PhysicalNumber, &MtrTheoValue,
																 &MtrTheoVolume, &MtrElecValue,
																 &MtrElecVolume, &UVEAntenna,
																 &Price1, &Price2, &Enabled ) ) )
		{
			WriteMessage("\n    Bico %02ld  EncVolume %.02f  EncDInheiro %.02f  Preco1 %.03f  Preco2 %.03f",
								Bico, MtrElecVolume, MtrElecValue, Price1, Price2 );

			WriteMessage("\n    [ Number %02ld  PumpId %03ld  TankID %03ld  PhisicalNumber %02ld ]",
								Number, PumpID, TankID, PhysicalNumber);

			WriteMessage("\n    [ MtrTheoValue %.02f  MtrTheoVolume %.02f  UVAntenna %02d  Enabled %02d ]",
								MtrTheoValue, MtrTheoVolume, UVEAntenna, Enabled);

			WriteMessage("\n");
		}
	}
}

//----------------------------------------------------------------------------
// Lista configuracao de produtos
void ListGrades()
{
    LONG Idx;
    LONG Ct;
    LONG Id;
    LONG Number;

#if defined(_WIN32)
    BSTR Name;
    BSTR ShortName;
    BSTR Code;
#elif defined(__linux__)
    TCHAR Name[MAX_PATH];
    TCHAR ShortName[MAX_PATH];
    TCHAR Code[MAX_PATH];
#endif

    // Verifica conexao
    if( !isConnected )
      return;

    //--------------------------------------------------------------------
    // Le o numero de produtos configurados
    if( !GoodResult( EZInterface.GetGradesCount( &Ct ) ) )
      return;

    WriteMessage( "\n[Produtos %ld]---------------------------------------------------", Ct);

    for(Idx=1; Idx<=Ct; Idx++ )
	{

       if( EZInterface.GetGradeByOrdinal( Idx, &Id )!=0 )
          return;

#if defined(_WIN32)
       if( GoodResult( EZInterface.GetGradeProperties(Id, &Number, &Name, &ShortName, &Code) ) )
#elif defined(__linux__)
       if( GoodResult( EZInterface.GetGradeProperties(Id, &Number,
    		                                          MakeBSTR(Name,      MAX_PATH),
    		                                          MakeBSTR(ShortName, MAX_PATH),
    		                                          MakeBSTR(Code,      MAX_PATH) )))
#endif
          WriteMessage( "\n  Grade: %ld  Nome: %s  Abreviado: %s  Codigo: %s",
							Number, Name, ShortName, Code);
	}

	WriteMessage( "\n");
}

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void ListPumps()
{
    LONG  Idx;
    LONG  Ct;
    LONG  Id;
    LONG  Number;
    short PhysicalNumber;
    short Side;
    short Address;
    short PriceLevel1;
    short PriceLevel2;
    short PriceDspFormat;
    short VolumeDspFormat;
    short ValueDspFormat;
    short PType;
    LONG  PortID;
    LONG  AttendantID;
    short AuthMode;
    short StackMode;
    short PrepayAllowed;
    short PreauthAllowed;
    LONG  SlotZigBeeID;
    LONG  MuxSlotZigBeeID;
    short PriceControl;
    short HasPreset;

#if defined(_WIN32)
    BSTR   Name;
#elif defined(__linux__)
    TCHAR   Name[MAX_PATH];
#endif

	// Verifica conexao
    if( !isConnected )
      return;

    //--------------------------------------------------------------------
    // Le o numero de produtos configurados
    if( !GoodResult( EZInterface.GetPumpsCount( &Ct ) ) )
      return;

	WriteMessage( "\n[Bombas %ld]---------------------------------------------------", Ct);

    for(Idx=1; Idx<=Ct; Idx++)
	{

       if( EZInterface.GetPumpByOrdinal( Idx, &Id )!=0 )
          return;

#if defined(_WIN32)
       if( GoodResult( EZInterface.GetPumpPropertiesEx(Id, &Number,          &Name,           &PhysicalNumber,
                                                           &Side,            &Address,        &PriceLevel1,
                                                           &PriceLevel2,     &PriceDspFormat, &VolumeDspFormat,
														   &ValueDspFormat,  &PType,          &PortID,
														   &AttendantID,     &AuthMode,       &StackMode,
														   &PrepayAllowed,   &PreauthAllowed, &SlotZigBeeID,
                                                           &MuxSlotZigBeeID, &PriceControl,   &HasPreset) ) )
#elif defined(__linux__)
	   if( GoodResult( EZInterface.GetPumpPropertiesEx(Id, &Number,
														   MakeBSTR(Name, MAX_PATH),
														   &PhysicalNumber,
														   &Side,            &Address,        &PriceLevel1,
														   &PriceLevel2,     &PriceDspFormat, &VolumeDspFormat,
														   &ValueDspFormat,  &PType,          &PortID,
														   &AttendantID,     &AuthMode,       &StackMode,
														   &PrepayAllowed,   &PreauthAllowed, &SlotZigBeeID,
														   &MuxSlotZigBeeID, &PriceControl,   &HasPreset) ) )
#endif
	   {
          WriteMessage("\n  Bomba: %02ld  Nome: %s  PhysicalNumber: %d  Side: %d  Address: %d",
								Number, Name, PhysicalNumber, Side, Address);

          WriteMessage("\n     PriceLevel1: %d  PriceLevel2: %d  PriceDspFormat: %d",
						        PriceLevel1, PriceLevel2, PriceDspFormat);

          WriteMessage("\n     PTipe: %d  PortID: %ld  AttendantID: %ld  AutoMode: %d  StackMode: %d",
 							    PType, PortID, AttendantID, AuthMode, StackMode);

          WriteMessage("\n     PrepayAllwed: %d  PreauthAllowed: %d  SlotZigBeeID: %ld  MuxSlotZigBeeID: %ld",
							    PrepayAllowed, PreauthAllowed, SlotZigBeeID, MuxSlotZigBeeID);

          WriteMessage("\n     VolumeDspFormat: %d  ValueDspFormat: %d  PriceControl: %d  HasPreset: %d",
						        VolumeDspFormat, ValueDspFormat, PriceControl, HasPreset);
	   }
	}

	WriteMessage("\n");
}

//----------------------------------------------------------------------------
void ListHoses()
{
    LONG   Idx;
    LONG   Ct;
    LONG   Id;
    LONG   Number;
    LONG   PumpID;
    LONG   TankID;
    LONG   PhysicalNumber;
    double MtrTheoValue;
    double MtrTheoVolume;
    double MtrElecValue;
    double MtrElecVolume;
    short  UVEAntenna;
    double Price1;
    double Price2;
    short  Enabled;

    // Verifica conexao
    if( !isConnected )
      return;

    //--------------------------------------------------------------------
    // Le o numero de produtos configurados
    if( !GoodResult( EZInterface.GetHosesCount( &Ct ) ) )
      return;

    WriteMessage("\n[Bicos %ld]---------------------------------------------------", Ct);

    for(Idx=1; Idx<=Ct; Idx++)
	{

       if( EZInterface.GetHoseByOrdinal( Idx, &Id )!=0 )
          return;

       if( GoodResult( EZInterface.GetHosePropertiesEx2( Id, &Number, &PumpID, &TankID,
                                                        &PhysicalNumber, &MtrTheoValue,
                                                        &MtrTheoVolume, &MtrElecValue,
                                                        &MtrElecVolume, &UVEAntenna,
                                                        &Price1, &Price2,
                                                        &Enabled ) ) )
	   {
          WriteMessage( "\n    Bico: %02ld  PumpID: %ld  TankID: %ld  PhisicalNumber: %ld",
										Number, PumpID, TankID, PhysicalNumber);

          WriteMessage( "\n        MtrTheoValue: %.03f  MtrTheoVolume: %.03f",
										MtrTheoValue, MtrTheoVolume);

          WriteMessage( "\n        MtrElecValue: %.03f  MtrElecVolume: %.03f",
										MtrElecValue, MtrElecVolume);

          WriteMessage( "\n        UVEAntena: %d  Price1: %.03f  Price2: %.03f  Enables: %d",
										UVEAntenna, Price1, Price2, Enabled);
	   }
	}
}

//-----------------------------------------------------------------------------
void CheckEvents()
{
    LONG  EvtCt;
    short EvtType ;

    // Verifica se esta conectado ao servidor
    if( !isConnected )
      return;

    // Inicia processamento de eventos
    if( !GoodResult( EZInterface.ProcessEvents() ) )
      return;

    // Le numero de eventos disponiveis
    if( !GoodResult( EZInterface.GetEventsCount( &EvtCt ) ) )
      return;

	for(;;) 
	{
		// Le o proximo evento
		if( !GoodResult( EZInterface.GetNextEventType( &EvtType ) ) )
		  return;

		switch( EvtType )
		{
			//---------------------------------------------------------------------
			case PUMP_EVENT :   // Trata Eventos das Bombas
				EventPump();
				break;

			//---------------------------------------------------------------------
			case DELIVERY_EVENT : // Eventos de abastecimento
				EventDelivery();
				break;

			//---------------------------------------------------------------------
			//case CARD_READ_EVENT:  // Eventos de leitores de cartoes
				//EventCardRead();
				//break;

			//---------------------------------------------------------------------
			//case DB_LOG_ETOTALS:   // Evento de mudanca de encerrantes
				//EventDbLogETotals();
			//	break;

			//---------------------------------------------------------------------
			case SERVER_EVENT:  // Eventos do servidor
				EventServer();
				break;

			//---------------------------------------------------------------------
			case CLIENT_EVENT:  // Eventos de POS (client)
				EventClient();
				break;

			//---------------------------------------------------------------------
			case NO_CLIENT_EVENT :  // Trata Eventos do Cliente
				return ;

			default:
				GoodResult( EZInterface.DiscardNextEvent() ) ;
				break;
		}
	}

}

//-----------------------------------------------------------------------------
void EventPump()
{
    LONG   PumpID;
    LONG  PumpNumber;
    short  State;
    short  ReservedFor;
    LONG   ReservedBy;
    LONG   HoseID;
    LONG   HoseNumber;
    LONG   HosePhysicalNumber;
    LONG   GradeID;
    LONG   GradeNumber;
    short  PriceLevel;
    double Price;
    double Volume;
    double Value;
    short  StackSize;
    LONG   PhysicalNumber;
    short  Side;
    short  Address;
    short  PriceLevel1;
    short  PriceLevel2;
    short  PumpType;
    LONG   PortID;
    short  AuthMode;
    short  StackMode;
    short  PrepayAllowed;
    short  PreauthAllowed;
    short  PriceFormat;
    short  ValueFormat;
    short  VolumeFormat;
    INT64  Tag;
    LONG   AttendantID;
    LONG   AttendantNumber;
    INT64  AttendantTag;
    LONG   CardClientID;
    LONG   CardClientNumber;
    INT64  CardClientTag;

	char cbcID[MAX_PATH];

#if defined(_WIN32)
    BSTR   GradeName;
    BSTR   ShortGradeName;
    BSTR   PumpName;
    BSTR   AttendantName;
    BSTR   CardClientName;
#elif defined(__linux__)
    TCHAR   GradeName[MAX_PATH];
    TCHAR   ShortGradeName[MAX_PATH];
    TCHAR   PumpName[MAX_PATH];
    TCHAR   AttendantName[MAX_PATH];
    TCHAR   CardClientName[MAX_PATH];
#endif

    // Verifica se esta conectado ao servidor
    if( !isConnected )
      return;

#if defined(_WIN32)
	if( GoodResult( EZInterface.GetNextPumpEventEx2(&PumpID,           &PumpNumber,         &State,
													&ReservedFor,      &ReservedBy,         &HoseID,
													&HoseNumber,       &HosePhysicalNumber,
													&GradeID,          &GradeNumber,        &GradeName,
													&ShortGradeName,   &PriceLevel,         &Price,
													&Volume,           &Value,              &StackSize,
													&PumpName,         &PhysicalNumber,     &Side,
													&Address,          &PriceLevel1,        &PriceLevel2,
													&PumpType,         &PortID,             &AuthMode,
													&StackMode,        &PrepayAllowed,      &PreauthAllowed,
													&PriceFormat,      &ValueFormat,        &VolumeFormat,
													&Tag,              &AttendantID,        &AttendantNumber,
													&AttendantName,    &AttendantTag,       &CardClientID,
													&CardClientNumber, &CardClientName,		&CardClientTag) ) )
#elif defined(__linux__)
		if( GoodResult( EZInterface.GetNextPumpEventEx2(&PumpID,           &PumpNumber,         &State,
														&ReservedFor,      &ReservedBy,         &HoseID,
														&HoseNumber,       &HosePhysicalNumber,
														&GradeID,          &GradeNumber,
														MakeBSTR(GradeName, MAX_PATH),
														MakeBSTR(ShortGradeName, MAX_PATH),
														&PriceLevel,         &Price,
														&Volume,           &Value,              &StackSize,
														MakeBSTR(PumpName, MAX_PATH),
														&PhysicalNumber,     &Side,
														&Address,          &PriceLevel1,        &PriceLevel2,
														&PumpType,         &PortID,             &AuthMode,
														&StackMode,        &PrepayAllowed,      &PreauthAllowed,
														&PriceFormat,      &ValueFormat,        &VolumeFormat,
														&Tag,              &AttendantID,        &AttendantNumber,
														MakeBSTR(AttendantName, MAX_PATH),
														&AttendantTag,       &CardClientID,
														&CardClientNumber,
														MakeBSTR(CardClientName, MAX_PATH),
														&CardClientTag) ) )
#endif
	{

		WriteMessage("\n------ PumpEvent:  PumpID %ld  PumpNumber %ld  State %d  ReservedFor %d",
									PumpID, PumpNumber, State, ReservedFor);

		WriteMessage("\n           ReservedBy %ld  HoseID %ld  HoseNumber %ld  HosePhisicalNumber %ld  GradeID %ld",
									ReservedBy, HoseID, HoseNumber, HosePhysicalNumber, GradeID);

		WriteMessage("\n           GradeName %s  GradeNumber %ld  ShortGradeName %s  PriceLevel %d",
									GradeName, GradeNumber, ShortGradeName, PriceLevel);

		WriteMessage("\n           Price %.03f  Volume %.03f  Value %.03f  StackSize %d",
									Price, Volume, Value, StackSize);

		WriteMessage("\n           PumpName %s  PhysicalNumber %ld  Side %d Address %d  PriceLevel1 %d  PriceLevel2 %d",
									PumpName, PhysicalNumber, Side, Address, PriceLevel1, PriceLevel2);

		WriteMessage("\n           PumpType %d  PortID %ld  AuthMode %d  StackMode %d  PrepayAllowed %d",
									PumpType, PortID, AuthMode, StackMode, PrepayAllowed);

		WriteMessage("\n           PreauthAllowed %d  PriceFormat %d  ValueFormat %d  VolumeFormat %d  Tag %lld",
								    PreauthAllowed, PriceFormat, ValueFormat, VolumeFormat, Tag);

		WriteMessage("\n           AttendantID %ld  AttendantNumber %ld  AttendantName %s  AttendantTag %lld",
									AttendantID, AttendantNumber, AttendantName, AttendantTag);

		WriteMessage("\n           CardClientID= %ld  CardClientNumber %ld  CardClientName %s  CardClientTag %lld",
									CardClientID, CardClientNumber, CardClientName, CardClientTag);

		CompanyID(HoseNumber, PumpNumber, cbcID);
		WriteMessage("\n           Bico Equivalente CBC: %s", cbcID);
	}
}

//-----------------------------------------------------------------------------
void EventDelivery()
{
	LONG   DeliveryID;
    LONG   HosePhysicalNumber;
    LONG   TankID;
    LONG   TankNumber;
    short  DeliveryState;
    short  DeliveryType;
    double Volume2;
    DATE   CompletedDT;
    LONG   LockedBy;
    LONG   Age;
    DATE   ClearedDT;
    double OldVolumeETot;
    double OldVolume2ETot;
    double OldValueETot;
    double NewVolumeETot;
    double NewVolume2ETot;
    double NewValueETot;
    LONG   Duration;

    LONG   PumpID;
    LONG   PumpNumber;
    LONG   HoseID;
    LONG   HoseNumber;
    //short  HosePhisicalNumber;
    LONG   GradeID;
    LONG   GradeNumber;

	short  PriceLevel;
    double Price;
    double Volume;
    double Value;
	LONG   ReservedBy;

	INT64  Tag;
    LONG   AttendantID;
    LONG   AttendantNumber;
    INT64  AttendantTag;
    LONG   CardClientID;
    LONG   CardClientNumber;
    INT64  CardClientTag;

	char cbcID[MAX_PATH];

#if defined(_WIN32)
    BSTR   TankName;
    BSTR   GradeShortName;
    BSTR   GradeCode;
	BSTR   PumpName;
    BSTR   GradeName;
    BSTR   AttendantName;
    BSTR   CardClientName;
#elif defined(__linux__)
	TCHAR   PumpName[MAX_PATH];
    TCHAR   TankName[MAX_PATH];
    TCHAR   GradeName[MAX_PATH];
    TCHAR   GradeCode[MAX_PATH];
    TCHAR   GradeShortName[MAX_PATH];
    TCHAR   AttendantName[MAX_PATH];
    TCHAR   CardClientName[MAX_PATH];
#endif

    // Verifica se esta conectado ao servidor
    if( !isConnected )
      return;

#if defined(_WIN32)
	if( GoodResult( EZInterface.GetNextDeliveryEventEx3(&DeliveryID,         &HoseID,           &HoseNumber,
													    &HosePhysicalNumber, &PumpID,           &PumpNumber,
													    &PumpName,           &TankID,           &TankNumber,    &TankName,
													    &GradeID,            &GradeNumber,      &GradeName,     &GradeShortName,
													    &GradeCode,          &DeliveryState,    &DeliveryType,  &Volume,
													    &PriceLevel,         &Price,            &Value,         &Volume2, &CompletedDT,
													    &LockedBy,           &ReservedBy,       &AttendantID,   &Age,     &ClearedDT,
													    &OldVolumeETot,      &OldVolume2ETot,   &OldValueETot,
													    &NewVolumeETot,      &NewVolume2ETot,   &NewValueETot,  &Tag,
													    &Duration,           &AttendantNumber,  &AttendantName, &AttendantTag,
													    &CardClientID,       &CardClientNumber, &CardClientName,
													    &CardClientTag) ) )
#elif defined(__linux__)
	if( GoodResult( EZInterface.GetNextDeliveryEventEx3(&DeliveryID,         &HoseID,           &HoseNumber,
														&HosePhysicalNumber, &PumpID,           &PumpNumber,
														MakeBSTR(PumpName, MAX_PATH),
														&TankID,           &TankNumber,
														MakeBSTR(TankName, MAX_PATH),
														&GradeID,            &GradeNumber,
														MakeBSTR(GradeName, MAX_PATH),
														MakeBSTR(GradeShortName, MAX_PATH),
														MakeBSTR(GradeCode, MAX_PATH),
														&DeliveryState,      &DeliveryType,     &Volume,
														&PriceLevel,         &Price,            &Value,         &Volume2, &CompletedDT,
														&LockedBy,           &ReservedBy,       &AttendantID,   &Age,     &ClearedDT,
														&OldVolumeETot,      &OldVolume2ETot,   &OldValueETot,
														&NewVolumeETot,      &NewVolume2ETot,   &NewValueETot,  &Tag,
														&Duration,           &AttendantNumber,
														MakeBSTR(AttendantName, MAX_PATH),
														&AttendantTag,
														&CardClientID,       &CardClientNumber,
														MakeBSTR(CardClientName, MAX_PATH),
														&CardClientTag) ) )
#endif
	{

		// Primeiro abastecimento pode ser invalido
		if( DeliveryID>0 )
		{
			WriteMessage("\n------ DeliveryEvent:  DeliveryID %ld  HoseID %ld  HoseNumber %ld  HosePhysicalNumber %ld",
										DeliveryID, HoseID, HoseNumber, HosePhysicalNumber);

			WriteMessage("\n           PumpID %ld  PumpNumber %ld  PumpName %s  TankID %ld",
										PumpID, PumpNumber,  PumpName, TankID);

			WriteMessage("\n           TankNumber %ld  TankName %s  GradeID %ld  GradeNumber %ld",
										TankNumber, TankName, GradeID, GradeNumber);

			WriteMessage("\n           GradeName %s  GradeShortName %s  GradeCode %s  DeliveryState %d",
										GradeName, GradeShortName, GradeCode, DeliveryState);

			WriteMessage("\n           DeliveryType %d  Volume %.03f  PriceLevel %d  Price %.03f",
										DeliveryType, Volume, PriceLevel, Price);

			WriteMessage("\n           Value %.03f  Volume2 %.30f  CompletedDT %ld  LockedBy %ld",
										Value, Volume2, CompletedDT, LockedBy);

			WriteMessage("\n           ReservedBy %ld  AttendantID %ld  Age %ld  ClearedDT %ld",
										ReservedBy, AttendantID, Age, ClearedDT);

			WriteMessage("\n           OldVolumeETot %.03f  OldVolume2ETot %.03f  OldValueETot %.03f  NewVolumeETot %.03f",
										OldVolumeETot, OldVolume2ETot, OldValueETot, NewVolumeETot);

			WriteMessage("\n           NewVolume2ETot %.03f  NewValueETot %.03f  Tag %lld  Duration %ld",
										NewVolume2ETot, NewValueETot, Tag, Duration);

			WriteMessage("\n           AttendantNumber %ld  AttendantName %s  AttendantTag %lld  CardClientID %ld",
										AttendantNumber, AttendantName, AttendantTag, CardClientID);

			WriteMessage("\n           CardClientNumber %ld  CardClientName %s  CardClientTag %lld",
										CardClientNumber, CardClientName, CardClientTag);

			CompanyID(HoseNumber, PumpNumber, cbcID);
			WriteMessage("\n           Bico Equivalente CBC: %s", cbcID);

			if( LockedBy==-1 )
			{
				if( GoodResult( EZInterface.LockDelivery( DeliveryID ) ) )
					LockedBy=1;

				if( (LockedBy==1) && (DeliveryState!=CLEARED) )
				  GoodResult( EZInterface.ClearDelivery( DeliveryID , DeliveryType ) ) ;

			}
		}
	}
}

//-----------------------------------------------------------------------------
/*void EventCardRead()
{
    LONG  CardReadID;
    LONG  Number;
    short CardType;
    LONG  ParentID;
    DATE  TimeStamp;
	INT64 Tag;
	LONG  PumpID;

#if defined(_WIN32)
	BSTR  Name;
#elif defined(__linux__)	//BSTR EventText[MAX_PATH];
	TCHAR EventText[MAX_PATH];

	TCHAR  Name[MAX_PATH];
#endif

    // Verifica se esta conectado ao servidor
    if( !isConnected )
      return;

#if defined(_WIN32)
	if( GoodResult( EZInterface.GetNextCardReadEvent(&CardReadID, &Number, &Name,
												     &PumpID,     &CardType, &ParentID,
												     &Tag,        &TimeStamp) ) )
#elif defined(__linux__)
	if( GoodResult( EZInterface.GetNextCardReadEvent(&CardReadID, &Number,
													 MakeBSTR(Name, MAX_PATH),
													 &PumpID,     &CardType, &ParentID,
													 &Tag,        &TimeStamp) ) )
#endif
	{

		WriteMessage("\n------ CardReadEvent:  CardReadID %ld  Number %ld  Name %s  PumpID %ld",
									CardReadID, Number, Name, PumpID);

		WriteMessage("\n           CardType %d  ParentID %ld  Tag %lld  TimeStamp %ld",
							        CardType, ParentID, Tag, TimeStamp );

		switch(CardType )
		{
		  case ATTENDANT_TAG_TYPE:
			WriteMessage("\n           Attendant: %s  Tag %lld", Name, Tag);
		    break;

		  case BLOCKED_ATTENDANT_TAG_TYPE:
			WriteMessage("\n           Blocked attendant: %s  Tag %lld", Name, Tag);
		    break;

		  case WRONG_SHIFT_ATTENDANT_TAG_TYPE:
			WriteMessage("\n           Wrong shift attendant: %s  Tag %lld", Name, Tag);
			break;

		  case CLIENT_TAG_TYPE:
		  	WriteMessage("\n           Client: %s  Tag %lld", Name, Tag);
			break;

		  case BLOCKED_CLIENT_TAG_TYPE:
			WriteMessage("\n           Blocked Client: %s  Tag %lld", Name, Tag);
		    break;

		  case UNKNOWN_TAG_TYPE:
			WriteMessage("\n           Unknown Tag read: %lld", Tag);
		    break;

		  default:
			WriteMessage("\n           Unknown Tag type: %d  Tag %lld", CardType, Tag);
			break;
		}

		GoodResult( EZInterface.DeleteCardRead( CardReadID )) ;
	}
}
*/
//-----------------------------------------------------------------------------
void EventDbLogETotals()
{
	LONG   HoseID;
	double Volume;
    double Value;
    double VolumeETot;
    double ValueETot;
    LONG   HoseNumber;
    LONG   HosePhysicalNumber;
    LONG   PumpID;
    LONG   PumpNumber;
	LONG   TankID;
    LONG   TankNumber;
    LONG   GradeID;

#if defined(_WIN32)
    BSTR   PumpName;
    BSTR   TankName;
    BSTR   GradeName;
#elif defined(__linux__)
    TCHAR   PumpName[MAX_PATH];
    TCHAR   TankName[MAX_PATH];
    TCHAR   GradeName[MAX_PATH];
#endif

    // Verifica se esta conectado ao servidor
    if( !isConnected )
      return;

#if defined(_WIN32)
	if( GoodResult( EZInterface.GetNextDBHoseETotalsEventEx(&HoseID,     &Volume,     &Value,
   													        &VolumeETot, &ValueETot,
													        &HoseNumber, &HosePhysicalNumber,
													        &PumpID,     &PumpNumber, &PumpName,
													        &TankID,     &TankNumber, &TankName,
													        &GradeID,    &GradeName) ) )
#elif defined(__linux__)
	if( GoodResult( EZInterface.GetNextDBHoseETotalsEventEx(&HoseID,     &Volume,     &Value,
															&VolumeETot, &ValueETot,
															&HoseNumber, &HosePhysicalNumber,
															&PumpID,     &PumpNumber,
															MakeBSTR(PumpName, MAX_PATH),
															&TankID,     &TankNumber,
															MakeBSTR(TankName, MAX_PATH),
															&GradeID,
															MakeBSTR(TankName, MAX_PATH)) ))
#endif
	{
		WriteMessage("\n------ HoseETotalEvent:  HoseID %ld  Volume %.03f  Value %.03f",
											HoseID, Volume, Value);

		WriteMessage("\n             VolumeETot %.03f  ValueETot %.03f",
							                VolumeETot, ValueETot);

		WriteMessage("\n             HoseNumber %ld  HosePhysicalNumber %ld",
							                HoseNumber, HosePhysicalNumber);

		WriteMessage("\n             PumpID %ld  PumpNumber %ld  PumpName %s",
											PumpID, PumpNumber, PumpName);

		WriteMessage("\n             TankID %ld  TankNumber %ld TankName %s",
											TankID, TankNumber, TankName);

		WriteMessage("\n             GradeID %ld  GradeName %s",
											GradeID, GradeName);

	}
}

//-----------------------------------------------------------------------------
void EventServer()
{
	LONG EventID;

#if defined(_WIN32)
	BSTR EventText;
#elif defined(__linux__)
	TCHAR EventText[MAX_PATH];
#endif

    // Verifica se esta conectado ao servidor
    if( !isConnected )
      return;

#if defined(_WIN32)
	if( GoodResult( EZInterface.GetNextServerEvent(&EventID, &EventText) ) )
#elif defined(__linux__)
	if( GoodResult( EZInterface.GetNextServerEvent(&EventID, MakeBSTR(EventText, MAX_PATH)) ))
#endif
		WriteMessage("\n------ ServerEvent:   EventID %ld  EventText %s",
										EventID, EventText);

}

//-----------------------------------------------------------------------------
void EventClient()
{
	LONG EventID;
	LONG ClientID;

#if defined(_WIN32)
	BSTR EventText;
#elif defined(__linux__)
	TCHAR EventText[MAX_PATH];
#endif

    // Verifica se esta conectado ao servidor
    if( !isConnected )
      return;

#if defined(_WIN32)
	if( GoodResult( EZInterface.GetNextClientEvent(&ClientID, &EventID, &EventText) ) )
#elif defined(__linux__)
	if( GoodResult( EZInterface.GetNextClientEvent(&ClientID, &EventID, MakeBSTR(EventText, MAX_PATH)) ))
#endif
		WriteMessage("\n------ ClientEvent: ClientID %ld  EventID %ld  EventText %s",
								 ClientID, EventID, EventText);

}

//-----------------------------------------------------------------------------


