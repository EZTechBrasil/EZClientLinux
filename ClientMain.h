//-----------------------------------------------------------------------------
//
//  Empresa     :  EzTech Tecnologia e Automação Ltda
//        				 http://www.eztech.ind.br/
//
//	Created     : 24/08/2012
//
//  Descricao   : Classe para carga e acesso da biblioteca EZClient.dll
//
//  Observacoes :
//
//-----------------------------------------------------------------------------
#ifndef __EZ_CLIENT_MAIN__
#define __EZ_CLIENT_MAIN__

//-----------------------------------------------------------------------------
#define WriteMessage printf

//-----------------------------------------------------------------------------
extern bool runEvents;
extern bool isConnected;
extern char EZServerAddr[MAX_PATH];

extern int  appPump;
extern int  lastStatus[MAX_PATH];

//-----------------------------------------------------------------------------

#define TIME_RECONECT		1500

// Login in EZTech
#define LOGIN_ID		15
#define	EVENT_PORT		5124
#define	CALL_PORT		5123
#define CALL_TIMEOUT	10000
#define EVENT_HANDLE	0
#define HANDLE_WINDOWS	0
#define WINDOWS_MSG		0

// -------------- Menu options ----------------//
typedef enum TMenuType
{
	HELP_MENU,
	MAIN_MENU,
	BASIC_GOOD_PRATICE_MENU,
	DELIVERY_READING_MENU,
	PUMP_BASIC_CONTROL_MENU,
	PUMP_CONTROL_EXTENDED_MENU,
	PUMP_PRICE_CONTROL_MENU,
	REGISTER_ATTENDANT_MENU,
	REGISTER_CLIENT_MENU,
	TANKS_SENSORS_READING_MENU,
	GENERAL_CONFIGURATION_FACILITY_MENU
} TMenuType ;

//-------------- Inicialização das funções ---------------//

bool GoodResult( int result );

void CreateAcess();
void MainLoop();
void HelpText(int level);
char ShowMenu(int menuLevel);

void EndMessage();

void CompanyID(short HoseNumber, short PumpNumber, char *cid);
// static wchar_t* charToWChar(const char* text);
PBSTR MakeBSTR( TCHAR* pStr , int Len );

void CheckLogin();

void PumpAuthorizeCancel();
void ChangePrice();

void ReadTotals();

void ListGrades();
void ListTanks();
void ListPumps();
void ListHoses();

void CheckEvents();

void EventPump();
void EventDelivery();
//void EventDbLogETotals();
void EventServer();
void EventClient();

//---------------------Verificar quais funções acima são necessárias -------------------------//

// Basic Good Practice
void BasicGoodPractice();

void SetDateTime() ;
void CheckServerVersion() ;
void CheckLicenseStatus() ;
void ClientLogoff() ;

// Deliveries Reading
void DeliveriesReading() ;

void ReadAllDeliveries( bool ReadAll ) ;

// Pump Basic Control
void PumpBasicControl() ;

void TemporaryStop() ;
void ReAuthoriseDelivery() ;
void DisablePump() ;
void EnablePump() ;
void PumpsStatus() ;
void AuthoriseDelivery() ;
void CancelAuthorise() ;

// Pump Control Extended
void PumpControlExtended() ;

void ScheduledDelivery() ;
void PresetDelivery() ;

// Pump Price Control
void PumpPriceControl() ;

void ChangeHosePrice() ;
void ChangeGradePrice() ;

// Reading Cards Attendant and(or) Client
//void ReadingCards() ;

// Register Attendant
void RegisterAttendant() ;

void AttendantRegistration() ;
void DeleteAttendant() ;
void ChangeAttendantTime();

// Register Client
void RegisterClient() ;

//void ClientRegistration() ;
void DeleteClient() ;

// Tanks and Sensors Reading
void TanksSensorsReading() ;

void TankReading() ;
void MonitoringSensor() ;

// General Configuration Facility
void GeneralConfigurationFacility() ;

void DeliveryPositionRegister() ;
void DeleteDeliveryPosition() ;
void HoseRegistration() ;
void DeleteHose() ;
void GradeRegister() ;
void DeleteGrade() ;
void TankRegistration() ;
void DeleteTank() ;
void ZigbeeDeviceRegistration() ;
void DeleteZigbeeDevice() ;

//-----------------------------------------------------------------------------
#endif // __EZ_CLIENT_MAIN__

