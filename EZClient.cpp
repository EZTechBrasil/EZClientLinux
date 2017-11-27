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
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#if defined(_WIN32)

#include <windows.h>
#include <tchar.h>
#include <conio.h>

#elif defined(__linux__)

#include <unistd.h>
#include <termios.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/signal.h>

#include <dlfcn.h>

#endif

#include "EZDefinitions.h"
#include "EZClient.h"

//-----------------------------------------------------------------------------
// Construtor padrao
CEZClient::CEZClient()
{
	int  ret;
	char ezpath[MAX_PATH];

	Initializer();

#if defined(_WIN32)
	strcpy(ezpath, "c:\\EZForecourt");
#elif defined(__linux__)
	strcpy(ezpath, "./");
#endif

	if( (ret=LoadAPIs(ezpath))!=0 )
		printf("\n*** %s - Erro %d carregando %s", __FUNCTION__, ret, EZ_LIB_NAME);
}

//-----------------------------------------------------------------------------
// Construtor de refencia
CEZClient::CEZClient(char* dllpath)
{
	int ret;

	Initializer();

	if( (ret=LoadAPIs(dllpath))!=0 )
		printf("\n*** %s - Erro %d carregando %s", __FUNCTION__, ret, EZ_LIB_NAME);
}

//-----------------------------------------------------------------------------
// Destrutor
CEZClient::~CEZClient()
{
	if( dllHandle!=NULL )
	{
		FreeLibrary(dllHandle);
		Initializer();
	}

#if defined(__linux__)

	if( oldTerm.c_lflag!=0 )
		tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);

#endif

}

//-----------------------------------------------------------------------------
bool CEZClient::isLoaded()
{
	return dllLoaded;
}

//-----------------------------------------------------------------------------
int CEZClient::LoadAPIs(char* dllpath)
{
	char buffer[MAX_PATH];

#if defined(_WIN32)

	char serror[MAX_PATH];

	sprintf(buffer, "%s\\%s", dllpath, EZ_LIB_NAME);

#elif defined(__linux__)

	char *serror;

	sprintf(buffer, "%s/%s", dllpath, EZ_LIB_NAME);

#endif

	dllHandle=LoadLibrary(buffer);
	if( dllHandle==NULL)
	{

#if defined(_WIN32)
		GetLastErrorText(GetLastError(), serror, sizeof(serror)-1);
#elif defined(__linux__)
		serror=dlerror();
#endif
		printf("\n*** %s - Erro carregando libEZClient: %s", __FUNCTION__, serror);
		return -1001;
	}

	DllVersion=(typeDllVersion) GetProcAddress(dllHandle,"DllVersion");
	if(DllVersion==NULL) return -1002;

	ServerVersion=(typeServerVersion) GetProcAddress(dllHandle,"ServerVersion");
	if(ServerVersion==NULL) return -1003;

	ClientLogon=(typeClientLogon) GetProcAddress(dllHandle,"ClientLogon");
	if(ClientLogon==NULL) return -1004;

	ClientLogonEx=(typeClientLogonEx) GetProcAddress(dllHandle,"ClientLogonEx");
	if(ClientLogonEx==NULL) return -1005;

	ClientLogoff=(typeClientLogoff) GetProcAddress(dllHandle,"ClientLogoff");
	if(ClientLogoff==NULL) return -1006;

	ClientStatus=(typeClientStatus) GetProcAddress(dllHandle,"ClientStatus");
	if(ClientStatus==NULL) return -1007;

	GetLicenseType=(typeGetLicenseType) GetProcAddress(dllHandle,"GetLicenseType");
	if(GetLicenseType==NULL) return -1008;

	FireClientEvent=(typeFireClientEvent) GetProcAddress(dllHandle,"FireClientEvent");
	if(FireClientEvent==NULL) return -1009;

	TestConnection=(typeTestConnection) GetProcAddress(dllHandle,"TestConnection");
	if(TestConnection==NULL) return -1010;

	ProcessEvents=(typeProcessEvents) GetProcAddress(dllHandle,"ProcessEvents");
	if(ProcessEvents==NULL) return -1011;

	GetEventsCount=(typeGetEventsCount) GetProcAddress(dllHandle,"GetEventsCount");
	if(GetEventsCount==NULL) return -1012;

	GetNextEventType=(typeGetNextEventType) GetProcAddress(dllHandle,"GetNextEventType");
	if(GetNextEventType==NULL) return -1013;

	DiscardNextEvent=(typeDiscardNextEvent) GetProcAddress(dllHandle,"DiscardNextEvent");
	if(DiscardNextEvent==NULL) return -1014;

	GetNextPumpEvent=(typeGetNextPumpEvent) GetProcAddress(dllHandle,"GetNextPumpEvent");
	if(GetNextPumpEvent==NULL) return -1015;

	GetNextDeliveryEvent=(typeGetNextDeliveryEvent) GetProcAddress(dllHandle,"GetNextDeliveryEvent");
	if(GetNextDeliveryEvent==NULL) return -1016;

	GetNextServerEvent=(typeGetNextServerEvent) GetProcAddress(dllHandle,"GetNextServerEvent");
	if(GetNextServerEvent==NULL) return -1017;

	GetNextClientEvent=(typeGetNextClientEvent) GetProcAddress(dllHandle,"GetNextClientEvent");
	if(GetNextClientEvent==NULL) return -1018;

	GetNextDBLogEvent=(typeGetNextDBLogEvent) GetProcAddress(dllHandle,"GetNextDBLogEvent");
	if(GetNextDBLogEvent==NULL) return -1019;

	GetNextDBLogDeliveryEvent=(typeGetNextDBLogDeliveryEvent) GetProcAddress(dllHandle,"GetNextDBLogDeliveryEvent");
	if(GetNextDBLogDeliveryEvent==NULL) return -1020;

	GetNextDBClearDeliveryEvent=(typeGetNextDBClearDeliveryEvent) GetProcAddress(dllHandle,"GetNextDBClearDeliveryEvent");
	if(GetNextDBClearDeliveryEvent==NULL) return -1021;

	GetNextDBStackDeliveryEvent=(typeGetNextDBStackDeliveryEvent) GetProcAddress(dllHandle,"GetNextDBStackDeliveryEvent");
	if(GetNextDBStackDeliveryEvent==NULL) return -1022;

	GetNextDBHoseETotalsEvent=(typeGetNextDBHoseETotalsEvent) GetProcAddress(dllHandle,"GetNextDBHoseETotalsEvent");
	if(GetNextDBHoseETotalsEvent==NULL) return -1023;

	GetNextDBTriggerEvent=(typeGetNextDBTriggerEvent) GetProcAddress(dllHandle,"GetNextDBTriggerEvent");
	if(GetNextDBTriggerEvent==NULL) return -1024;

	GetNextDBAttendantLogonEvent=(typeGetNextDBAttendantLogonEvent) GetProcAddress(dllHandle,"GetNextDBAttendantLogonEvent");
	if(GetNextDBAttendantLogonEvent==NULL) return -1025;

	GetNextDBAttendantLogoffEvent=(typeGetNextDBAttendantLogoffEvent) GetProcAddress(dllHandle,"GetNextDBAttendantLogoffEvent");
	if(GetNextDBAttendantLogoffEvent==NULL) return -1026;

	GetNextDBTankStatusEvent=(typeGetNextDBTankStatusEvent) GetProcAddress(dllHandle,"GetNextDBTankStatusEvent");
	if(GetNextDBTankStatusEvent==NULL) return -1027;

	GetPumpsCount=(typeGetPumpsCount) GetProcAddress(dllHandle,"GetPumpsCount");
	if(GetPumpsCount==NULL) return -1028;

	GetPumpByNumber=(typeGetPumpByNumber) GetProcAddress(dllHandle,"GetPumpByNumber");
	if(GetPumpByNumber==NULL) return -1029;

	GetPumpByName=(typeGetPumpByName) GetProcAddress(dllHandle,"GetPumpByName");
	if(GetPumpByName==NULL) return -1030;

	GetPumpByOrdinal=(typeGetPumpByOrdinal) GetProcAddress(dllHandle,"GetPumpByOrdinal");
	if(GetPumpByOrdinal==NULL) return -1031;

	GetPumpProperties=(typeGetPumpProperties) GetProcAddress(dllHandle,"GetPumpProperties");
	if(GetPumpProperties==NULL) return -1032;

	SetPumpProperties=(typeSetPumpProperties) GetProcAddress(dllHandle,"SetPumpProperties");
	if(SetPumpProperties==NULL) return -1033;

	DeletePump=(typeDeletePump) GetProcAddress(dllHandle,"DeletePump");
	if(DeletePump==NULL) return -1034;

	GetPumpHosesCount=(typeGetPumpHosesCount) GetProcAddress(dllHandle,"GetPumpHosesCount");
	if(GetPumpHosesCount==NULL) return -1035;

	GetPumpHoseByNumber=(typeGetPumpHoseByNumber) GetProcAddress(dllHandle,"GetPumpHoseByNumber");
	if(GetPumpHoseByNumber==NULL) return -1036;

	GetPumpStatus=(typeGetPumpStatus) GetProcAddress(dllHandle,"GetPumpStatus");
	if(GetPumpStatus==NULL) return -1037;

	GetPumpStatusEx=(typeGetPumpStatusEx) GetProcAddress(dllHandle,"GetPumpStatusEx");
	if(GetPumpStatusEx==NULL) return -1038;

	GetPumpDeliveryProperties=(typeGetPumpDeliveryProperties) GetProcAddress(dllHandle,"GetPumpDeliveryProperties");
	if(GetPumpDeliveryProperties==NULL) return -1039;

	GetPumpDeliveryPropertiesEx=(typeGetPumpDeliveryPropertiesEx) GetProcAddress(dllHandle,"GetPumpDeliveryPropertiesEx");
	if(GetPumpDeliveryPropertiesEx==NULL) return -1040;

	GetPumpDeliveryPropertiesEx2=(typeGetPumpDeliveryPropertiesEx2) GetProcAddress(dllHandle,"GetPumpDeliveryPropertiesEx2");
	if(GetPumpDeliveryPropertiesEx2==NULL) return -1041;

	GetPumpDeliveryPropertiesEx3=(typeGetPumpDeliveryPropertiesEx3) GetProcAddress(dllHandle,"GetPumpDeliveryPropertiesEx3");
	if(GetPumpDeliveryPropertiesEx3==NULL) return -1042;

	PrepayReserve=(typePrepayReserve) GetProcAddress(dllHandle,"PrepayReserve");
	if(PrepayReserve==NULL) return -1043;

	PrepayCancel=(typePrepayCancel) GetProcAddress(dllHandle,"PrepayCancel");
	if(PrepayCancel==NULL) return -1044;

	PrepayAuthorise=(typePrepayAuthorise) GetProcAddress(dllHandle,"PrepayAuthorise");
	if(PrepayAuthorise==NULL) return -1045;

	PreauthReserve=(typePreauthReserve) GetProcAddress(dllHandle,"PreauthReserve");
	if(PreauthReserve==NULL) return -1046;

	PreauthCancel=(typePreauthCancel) GetProcAddress(dllHandle,"PreauthCancel");
	if(PreauthCancel==NULL) return -1047;

	PreauthAuthorise=(typePreauthAuthorise) GetProcAddress(dllHandle,"PreauthAuthorise");
	if(PreauthAuthorise==NULL) return -1048;

	LoadPreset=(typeLoadPreset) GetProcAddress(dllHandle,"LoadPreset");
	if(LoadPreset==NULL) return -1049;

	LoadPresetWithPrice=(typeLoadPresetWithPrice) GetProcAddress(dllHandle,"LoadPresetWithPrice");
	if(LoadPresetWithPrice==NULL) return -1050;

	TagAuthorise=(typeTagAuthorise) GetProcAddress(dllHandle,"TagAuthorise");
	if(TagAuthorise==NULL) return -1051;

	AttendantAuthorise=(typeAttendantAuthorise) GetProcAddress(dllHandle,"AttendantAuthorise");
	if(AttendantAuthorise==NULL) return -1052;

	Authorise=(typeAuthorise) GetProcAddress(dllHandle,"Authorise");
	if(Authorise==NULL) return -1053;

	CancelAuthorise=(typeCancelAuthorise) GetProcAddress(dllHandle,"CancelAuthorise");
	if(CancelAuthorise==NULL) return -1054;

	TempStop=(typeTempStop) GetProcAddress(dllHandle,"TempStop");
	if(TempStop==NULL) return -1055;

	ReAuthorise=(typeReAuthorise) GetProcAddress(dllHandle,"ReAuthorise");
	if(ReAuthorise==NULL) return -1056;

	TerminateDelivery=(typeTerminateDelivery) GetProcAddress(dllHandle,"TerminateDelivery");
	if(TerminateDelivery==NULL) return -1057;

	StackCurrentDelivery=(typeStackCurrentDelivery) GetProcAddress(dllHandle,"StackCurrentDelivery");
	if(StackCurrentDelivery==NULL) return -1058;

	GetDensity=(typeGetDensity) GetProcAddress(dllHandle,"GetDensity");
	if(GetDensity==NULL) return -1059;

	EnablePump=(typeEnablePump) GetProcAddress(dllHandle,"EnablePump");
	if(EnablePump==NULL) return -1060;

	DisablePump=(typeDisablePump) GetProcAddress(dllHandle,"DisablePump");
	if(DisablePump==NULL) return -1061;

	GetHosesCount=(typeGetHosesCount) GetProcAddress(dllHandle,"GetHosesCount");
	if(GetHosesCount==NULL) return -1062;

	GetHoseByOrdinal=(typeGetHoseByOrdinal) GetProcAddress(dllHandle,"GetHoseByOrdinal");
	if(GetHoseByOrdinal==NULL) return -1063;

	GetHoseProperties=(typeGetHoseProperties) GetProcAddress(dllHandle,"GetHoseProperties");
	if(GetHoseProperties==NULL) return -1064;

	SetHoseProperties=(typeSetHoseProperties) GetProcAddress(dllHandle,"SetHoseProperties");
	if(SetHoseProperties==NULL) return -1065;

	GetHoseSummary=(typeGetHoseSummary) GetProcAddress(dllHandle,"GetHoseSummary");
	if(GetHoseSummary==NULL) return -1066;

	GetHoseSummaryEx=(typeGetHoseSummaryEx) GetProcAddress(dllHandle,"GetHoseSummaryEx");
	if(GetHoseSummaryEx==NULL) return -1067;

	DeleteHose=(typeDeleteHose) GetProcAddress(dllHandle,"DeleteHose");
	if(DeleteHose==NULL) return -1068;

	GetDeliveriesCount=(typeGetDeliveriesCount) GetProcAddress(dllHandle,"GetDeliveriesCount");
	if(GetDeliveriesCount==NULL) return -1069;

	GetDeliveryByOrdinal=(typeGetDeliveryByOrdinal) GetProcAddress(dllHandle,"GetDeliveryByOrdinal");
	if(GetDeliveryByOrdinal==NULL) return -1070;

	GetAllDeliveriesCount=(typeGetAllDeliveriesCount) GetProcAddress(dllHandle,"GetAllDeliveriesCount");
	if(GetAllDeliveriesCount==NULL) return -1071;

	GetAllDeliveryByOrdinal=(typeGetAllDeliveryByOrdinal) GetProcAddress(dllHandle,"GetAllDeliveryByOrdinal");
	if(GetAllDeliveryByOrdinal==NULL) return -1072;

	AckDeliveryDBLog=(typeAckDeliveryDBLog) GetProcAddress(dllHandle,"AckDeliveryDBLog");
	if(AckDeliveryDBLog==NULL) return -1073;

	GetDeliveryIDByOrdinalNotLogged=(typeGetDeliveryIDByOrdinalNotLogged) GetProcAddress(dllHandle,"GetDeliveryIDByOrdinalNotLogged");
	if(GetDeliveryIDByOrdinalNotLogged==NULL) return -1074;

	GetDeliveriesCountNotLogged=(typeGetDeliveriesCountNotLogged) GetProcAddress(dllHandle,"GetDeliveriesCountNotLogged");
	if(GetDeliveriesCountNotLogged==NULL) return -1075;

	AckDeliveryVolLog=(typeAckDeliveryVolLog) GetProcAddress(dllHandle,"AckDeliveryVolLog");
	if(AckDeliveryVolLog==NULL) return -1076;

	GetDeliveryIDByOrdinalNotVolLogged=(typeGetDeliveryIDByOrdinalNotVolLogged) GetProcAddress(dllHandle,"GetDeliveryIDByOrdinalNotVolLogged");
	if(GetDeliveryIDByOrdinalNotVolLogged==NULL) return -1077;

	GetDeliveriesCountNotVolLogged=(typeGetDeliveriesCountNotVolLogged) GetProcAddress(dllHandle,"GetDeliveriesCountNotVolLogged");
	if(GetDeliveriesCountNotVolLogged==NULL) return -1078;

	GetDeliveryProperties=(typeGetDeliveryProperties) GetProcAddress(dllHandle,"GetDeliveryProperties");
	if(GetDeliveryProperties==NULL) return -1079;

	GetDeliveryPropertiesEx=(typeGetDeliveryPropertiesEx) GetProcAddress(dllHandle,"GetDeliveryPropertiesEx");
	if(GetDeliveryPropertiesEx==NULL) return -1080;

	GetDeliveryPropertiesEx2=(typeGetDeliveryPropertiesEx2) GetProcAddress(dllHandle,"GetDeliveryPropertiesEx2");
	if(GetDeliveryPropertiesEx2==NULL) return -1081;

	GetDeliveryPropertiesEx3=(typeGetDeliveryPropertiesEx3) GetProcAddress(dllHandle,"GetDeliveryPropertiesEx3");
	if(GetDeliveryPropertiesEx3==NULL) return -1082;

	SetDeliveryProperties=(typeSetDeliveryProperties) GetProcAddress(dllHandle,"SetDeliveryProperties");
	if(SetDeliveryProperties==NULL) return -1083;

	SetDeliveryPropertiesEx=(typeSetDeliveryPropertiesEx) GetProcAddress(dllHandle,"SetDeliveryPropertiesEx");
	if(SetDeliveryPropertiesEx==NULL) return -1084;

	SetDeliveryPropertiesEx2=(typeSetDeliveryPropertiesEx2) GetProcAddress(dllHandle,"SetDeliveryPropertiesEx2");
	if(SetDeliveryPropertiesEx2==NULL) return -1085;

	SetDeliveryPropertiesEx3=(typeSetDeliveryPropertiesEx3) GetProcAddress(dllHandle,"SetDeliveryPropertiesEx3");
	if(SetDeliveryPropertiesEx3==NULL) return -1086;

	GetDeliverySummary=(typeGetDeliverySummary) GetProcAddress(dllHandle,"GetDeliverySummary");
	if(GetDeliverySummary==NULL) return -1087;

	GetDeliverySummaryEx=(typeGetDeliverySummaryEx) GetProcAddress(dllHandle,"GetDeliverySummaryEx");
	if(GetDeliverySummaryEx==NULL) return -1088;

	GetDeliverySummaryEx2=(typeGetDeliverySummaryEx2) GetProcAddress(dllHandle,"GetDeliverySummaryEx2");
	if(GetDeliverySummaryEx2==NULL) return -1089;

	LockDelivery=(typeLockDelivery) GetProcAddress(dllHandle,"LockDelivery");
	if(LockDelivery==NULL) return -1090;

	UnlockDelivery=(typeUnlockDelivery) GetProcAddress(dllHandle,"UnlockDelivery");
	if(UnlockDelivery==NULL) return -1091;

	ClearDelivery=(typeClearDelivery) GetProcAddress(dllHandle,"ClearDelivery");
	if(ClearDelivery==NULL) return -1092;

	LockAndClearDelivery=(typeLockAndClearDelivery) GetProcAddress(dllHandle,"LockAndClearDelivery");
	if(LockAndClearDelivery==NULL) return -1093;

	GetDuration=(typeGetDuration) GetProcAddress(dllHandle,"GetDuration");
	if(GetDuration==NULL) return -1094;

	GetGradesCount=(typeGetGradesCount) GetProcAddress(dllHandle,"GetGradesCount");
	if(GetGradesCount==NULL) return -1095;

	GetGradeByNumber=(typeGetGradeByNumber) GetProcAddress(dllHandle,"GetGradeByNumber");
	if(GetGradeByNumber==NULL) return -1096;

	GetGradeByName=(typeGetGradeByName) GetProcAddress(dllHandle,"GetGradeByName");
	if(GetGradeByName==NULL) return -1097;

	GetGradeByOrdinal=(typeGetGradeByOrdinal) GetProcAddress(dllHandle,"GetGradeByOrdinal");
	if(GetGradeByOrdinal==NULL) return -1098;

	GetGradeProperties=(typeGetGradeProperties) GetProcAddress(dllHandle,"GetGradeProperties");
	if(GetGradeProperties==NULL) return -1099;

	SetGradeProperties=(typeSetGradeProperties) GetProcAddress(dllHandle,"SetGradeProperties");
	if(SetGradeProperties==NULL) return -1100;

	DeleteGrade=(typeDeleteGrade) GetProcAddress(dllHandle,"DeleteGrade");
	if(DeleteGrade==NULL) return -1101;

	SetGradePrice=(typeSetGradePrice) GetProcAddress(dllHandle,"SetGradePrice");
	if(SetGradePrice==NULL) return -1102;

	GetGradePrice=(typeGetGradePrice) GetProcAddress(dllHandle,"GetGradePrice");
	if(GetGradePrice==NULL) return -1103;

	GetTanksCount=(typeGetTanksCount) GetProcAddress(dllHandle,"GetTanksCount");
	if(GetTanksCount==NULL) return -1104;

	GetTankByNumber=(typeGetTankByNumber) GetProcAddress(dllHandle,"GetTankByNumber");
	if(GetTankByNumber==NULL) return -1105;

	GetTankByName=(typeGetTankByName) GetProcAddress(dllHandle,"GetTankByName");
	if(GetTankByName==NULL) return -1106;

	GetTankByOrdinal=(typeGetTankByOrdinal) GetProcAddress(dllHandle,"GetTankByOrdinal");
	if(GetTankByOrdinal==NULL) return -1107;

	GetTankProperties=(typeGetTankProperties) GetProcAddress(dllHandle,"GetTankProperties");
	if(GetTankProperties==NULL) return -1108;

	SetTankProperties=(typeSetTankProperties) GetProcAddress(dllHandle,"SetTankProperties");
	if(SetTankProperties==NULL) return -1109;

	GetTankSummary=(typeGetTankSummary) GetProcAddress(dllHandle,"GetTankSummary");
	if(GetTankSummary==NULL) return -1110;

	TankDrop=(typeTankDrop) GetProcAddress(dllHandle,"TankDrop");
	if(TankDrop==NULL) return -1111;

	DeleteTank=(typeDeleteTank) GetProcAddress(dllHandle,"DeleteTank");
	if(DeleteTank==NULL) return -1112;

	GetPortsCount=(typeGetPortsCount) GetProcAddress(dllHandle,"GetPortsCount");
	if(GetPortsCount==NULL) return -1113;

	GetPortByNumber=(typeGetPortByNumber) GetProcAddress(dllHandle,"GetPortByNumber");
	if(GetPortByNumber==NULL) return -1114;

	GetPortByName=(typeGetPortByName) GetProcAddress(dllHandle,"GetPortByName");
	if(GetPortByName==NULL) return -1115;

	GetPortByOrdinal=(typeGetPortByOrdinal) GetProcAddress(dllHandle,"GetPortByOrdinal");
	if(GetPortByOrdinal==NULL) return -1116;

	GetPortProperties=(typeGetPortProperties) GetProcAddress(dllHandle,"GetPortProperties");
	if(GetPortProperties==NULL) return -1117;

	SetPortProperties=(typeSetPortProperties) GetProcAddress(dllHandle,"SetPortProperties");
	if(SetPortProperties==NULL) return -1118;

	GetAttendantsCount=(typeGetAttendantsCount) GetProcAddress(dllHandle,"GetAttendantsCount");
	if(GetAttendantsCount==NULL) return -1119;

	GetAttendantByNumber=(typeGetAttendantByNumber) GetProcAddress(dllHandle,"GetAttendantByNumber");
	if(GetAttendantByNumber==NULL) return -1120;

	GetAttendantByName=(typeGetAttendantByName) GetProcAddress(dllHandle,"GetAttendantByName");
	if(GetAttendantByName==NULL) return -1121;

	GetAttendantByOrdinal=(typeGetAttendantByOrdinal) GetProcAddress(dllHandle,"GetAttendantByOrdinal");
	if(GetAttendantByOrdinal==NULL) return -1122;

	GetAttendantProperties=(typeGetAttendantProperties) GetProcAddress(dllHandle,"GetAttendantProperties");
	if(GetAttendantProperties==NULL) return -1123;

	SetAttendantProperties=(typeSetAttendantProperties) GetProcAddress(dllHandle,"SetAttendantProperties");
	if(SetAttendantProperties==NULL) return -1124;

	GetAttendantPropertiesEx=(typeGetAttendantPropertiesEx) GetProcAddress(dllHandle,"GetAttendantPropertiesEx");
	if(GetAttendantPropertiesEx==NULL) return -1125;

	SetAttendantPropertiesEx=(typeSetAttendantPropertiesEx) GetProcAddress(dllHandle,"SetAttendantPropertiesEx");
	if(SetAttendantPropertiesEx==NULL) return -1126;

	DeleteAttendant=(typeDeleteAttendant) GetProcAddress(dllHandle,"DeleteAttendant");
	if(DeleteAttendant==NULL) return -1127;

	AttendantLogon=(typeAttendantLogon) GetProcAddress(dllHandle,"AttendantLogon");
	if(AttendantLogon==NULL) return -1128;

	AttendantLogoff=(typeAttendantLogoff) GetProcAddress(dllHandle,"AttendantLogoff");
	if(AttendantLogoff==NULL) return -1129;

	GetCardReadsCount=(typeGetCardReadsCount) GetProcAddress(dllHandle,"GetCardReadsCount");
	if(GetCardReadsCount==NULL) return -1130;

	GetCardReadByNumber=(typeGetCardReadByNumber) GetProcAddress(dllHandle,"GetCardReadByNumber");
	if(GetCardReadByNumber==NULL) return -1131;

	GetCardReadByName=(typeGetCardReadByName) GetProcAddress(dllHandle,"GetCardReadByName");
	if(GetCardReadByName==NULL) return -1132;

	GetCardReadByOrdinal=(typeGetCardReadByOrdinal) GetProcAddress(dllHandle,"GetCardReadByOrdinal");
	if(GetCardReadByOrdinal==NULL) return -1133;

	GetCardReadProperties=(typeGetCardReadProperties) GetProcAddress(dllHandle,"GetCardReadProperties");
	if(GetCardReadProperties==NULL) return -1134;

	SetCardReadProperties=(typeSetCardReadProperties) GetProcAddress(dllHandle,"SetCardReadProperties");
	if(SetCardReadProperties==NULL) return -1135;

	DeleteCardRead=(typeDeleteCardRead) GetProcAddress(dllHandle,"DeleteCardRead");
	if(DeleteCardRead==NULL) return -1136;

	GetCardClientsCount=(typeGetCardClientsCount) GetProcAddress(dllHandle,"GetCardClientsCount");
	if(GetCardClientsCount==NULL) return -1137;

	GetCardClientByNumber=(typeGetCardClientByNumber) GetProcAddress(dllHandle,"GetCardClientByNumber");
	if(GetCardClientByNumber==NULL) return -1138;

	GetCardClientByName=(typeGetCardClientByName) GetProcAddress(dllHandle,"GetCardClientByName");
	if(GetCardClientByName==NULL) return -1139;

	GetCardClientByOrdinal=(typeGetCardClientByOrdinal) GetProcAddress(dllHandle,"GetCardClientByOrdinal");
	if(GetCardClientByOrdinal==NULL) return -1140;

	GetCardClientProperties=(typeGetCardClientProperties) GetProcAddress(dllHandle,"GetCardClientProperties");
	if(GetCardClientProperties==NULL) return -1141;

	SetCardClientProperties=(typeSetCardClientProperties) GetProcAddress(dllHandle,"SetCardClientProperties");
	if(SetCardClientProperties==NULL) return -1142;

	DeleteCardClient=(typeDeleteCardClient) GetProcAddress(dllHandle,"DeleteCardClient");
	if(DeleteCardClient==NULL) return -1143;

	AllStop=(typeAllStop) GetProcAddress(dllHandle,"AllStop");
	if(AllStop==NULL) return -1144;

	AllAuthorise=(typeAllAuthorise) GetProcAddress(dllHandle,"AllAuthorise");
	if(AllAuthorise==NULL) return -1145;

	AllReAuthorise=(typeAllReAuthorise) GetProcAddress(dllHandle,"AllReAuthorise");
	if(AllReAuthorise==NULL) return -1146;

	AllStopIfIdle=(typeAllStopIfIdle) GetProcAddress(dllHandle,"AllStopIfIdle");
	if(AllStopIfIdle==NULL) return -1147;

	ReadAllTanks=(typeReadAllTanks) GetProcAddress(dllHandle,"ReadAllTanks");
	if(ReadAllTanks==NULL) return -1148;

	GetAllPumpStatuses=(typeGetAllPumpStatuses) GetProcAddress(dllHandle,"GetAllPumpStatuses");
	if(GetAllPumpStatuses==NULL) return -1149;

	GetIniValue=(typeGetIniValue) GetProcAddress(dllHandle,"GetIniValue");
	if(GetIniValue==NULL) return -1150;

	SetIniValue=(typeSetIniValue) GetProcAddress(dllHandle,"SetIniValue");
	if(SetIniValue==NULL) return -1151;

	SetNextDeliveryID=(typeSetNextDeliveryID) GetProcAddress(dllHandle,"SetNextDeliveryID");
	if(SetNextDeliveryID==NULL) return -1152;

	RemovePort=(typeRemovePort) GetProcAddress(dllHandle,"RemovePort");
	if(RemovePort==NULL) return -1153;

	LicenseStatus=(typeLicenseStatus) GetProcAddress(dllHandle,"LicenseStatus");
	if(LicenseStatus==NULL) return -1154;

#if defined(_WIN32)
	CheckSocketClosed=(typeCheckSocketClosed) GetProcAddress(dllHandle,"CheckSocketClosed");
	if(CheckSocketClosed==NULL) return -1155;
#endif

	ResultString=(typeResultString) GetProcAddress(dllHandle,"ResultString");
	if(ResultString==NULL) return -1156;

	PumpStateString=(typePumpStateString) GetProcAddress(dllHandle,"PumpStateString");
	if(PumpStateString==NULL) return -1157;

	DeliveryStateString=(typeDeliveryStateString) GetProcAddress(dllHandle,"DeliveryStateString");
	if(DeliveryStateString==NULL) return -1158;

	DeliveryTypeString=(typeDeliveryTypeString) GetProcAddress(dllHandle,"DeliveryTypeString");
	if(DeliveryTypeString==NULL) return -1159;

	ReserveTypeString=(typeReserveTypeString) GetProcAddress(dllHandle,"ReserveTypeString");
	if(ReserveTypeString==NULL) return -1160;

	GetNextPumpEventEx=(typeGetNextPumpEventEx) GetProcAddress(dllHandle,"GetNextPumpEventEx");
	if(GetNextPumpEventEx==NULL) return -1161;

	GetNextPumpEventEx2=(typeGetNextPumpEventEx2) GetProcAddress(dllHandle,"GetNextPumpEventEx2");
	if(GetNextPumpEventEx2==NULL) return -1162;

	GetNextDeliveryEventEx=(typeGetNextDeliveryEventEx) GetProcAddress(dllHandle,"GetNextDeliveryEventEx");
	if(GetNextDeliveryEventEx==NULL) return -1163;

	GetNextDeliveryEventEx2=(typeGetNextDeliveryEventEx2) GetProcAddress(dllHandle,"GetNextDeliveryEventEx2");
	if( GetNextDeliveryEventEx2==NULL) return -1164;

	GetNextDeliveryEventEx3=(typeGetNextDeliveryEventEx3) GetProcAddress(dllHandle,"GetNextDeliveryEventEx3");
	if( GetNextDeliveryEventEx3==NULL) return -1165;

	GetNextCardReadEvent=(typeGetNextCardReadEvent) GetProcAddress(dllHandle,"GetNextCardReadEvent");
	if(GetNextCardReadEvent==NULL) return -1166;

	GetNextDBHoseETotalsEventEx=(typeGetNextDBHoseETotalsEventEx) GetProcAddress(dllHandle,"GetNextDBHoseETotalsEventEx");
	if(GetNextDBHoseETotalsEventEx==NULL) return -1167;

	GetNextDBTankStatusEventEx=(typeGetNextDBTankStatusEventEx) GetProcAddress(dllHandle,"GetNextDBTankStatusEventEx");
	if(GetNextDBTankStatusEventEx==NULL) return -1168;

	GetZigBeeCount=(typeGetZigBeeCount) GetProcAddress(dllHandle,"GetZigBeeCount");
	if(GetZigBeeCount==NULL) return -1172;

	GetZigBeeByNumber=(typeGetZigBeeByNumber) GetProcAddress(dllHandle,"GetZigBeeByNumber");
	if(GetZigBeeByNumber==NULL) return -1173;

	GetZigBeeByName=(typeGetZigBeeByName) GetProcAddress(dllHandle,"GetZigBeeByName");
	if(GetZigBeeByName==NULL) return -1174;

	GetZigBeeByOrdinal=(typeGetZigBeeByOrdinal) GetProcAddress(dllHandle,"GetZigBeeByOrdinal");
	if(GetZigBeeByOrdinal==NULL) return -1175;

	GetZigBeeProperties=(typeGetZigBeeProperties) GetProcAddress(dllHandle,"GetZigBeeProperties");
	if(GetZigBeeProperties==NULL) return -1176;

	SetZigBeeProperties=(typeSetZigBeeProperties) GetProcAddress(dllHandle,"SetZigBeeProperties");
	if(SetZigBeeProperties==NULL) return -1177;

	DeleteZigBee=(typeDeleteZigBee) GetProcAddress(dllHandle,"DeleteZigBee");
	if(DeleteZigBee==NULL) return -1178;

	GetHosePropertiesEx=(typeGetHosePropertiesEx) GetProcAddress(dllHandle,"GetHosePropertiesEx");
	if(GetHosePropertiesEx==NULL) return -1179;

	SetHosePropertiesEx=(typeSetHosePropertiesEx) GetProcAddress(dllHandle,"SetHosePropertiesEx");
	if(SetHosePropertiesEx==NULL) return -1180;

	GetHosePropertiesEx2=(typeGetHosePropertiesEx2) GetProcAddress(dllHandle,"GetHosePropertiesEx2");
	if(GetHosePropertiesEx2==NULL) return -1181;

	SetHosePropertiesEx2=(typeSetHosePropertiesEx2) GetProcAddress(dllHandle,"SetHosePropertiesEx2");
	if(SetHosePropertiesEx2==NULL) return -1182;

	SetPumpPropertiesEx=(typeSetPumpPropertiesEx) GetProcAddress(dllHandle,"SetPumpPropertiesEx");
	if(SetPumpPropertiesEx==NULL) return -1183;

	GetPumpPropertiesEx=(typeGetPumpPropertiesEx) GetProcAddress(dllHandle,"GetPumpPropertiesEx");
	if(GetPumpPropertiesEx==NULL) return -1184;

	GetSerialNo=(typeGetSerialNo) GetProcAddress(dllHandle,"GetSerialNo");
	if(GetSerialNo==NULL) return -1188;

	GetDeviceDetails=(typeGetDeviceDetails) GetProcAddress(dllHandle,"GetDeviceDetails");
	if(GetDeviceDetails==NULL) return -1189;

	ResetDevice=(typeResetDevice) GetProcAddress(dllHandle,"ResetDevice");
	if(ResetDevice==NULL) return -1190;

	RequestVersion=(typeRequestVersion) GetProcAddress(dllHandle,"RequestVersion");
	if(RequestVersion==NULL) return -1191;

	GetDeviceDetails=(typeGetDeviceDetails) GetProcAddress(dllHandle,"GetDeviceDetails");
	if(GetDeviceDetails==NULL) return -1199;

	SetHoseETotals=(typeSetHoseETotals) GetProcAddress(dllHandle,"SetHoseETotals");
	if(SetHoseETotals==NULL) return -1203;

	GetNextZBPanIDEvent=(typeGetNextZBPanIDEvent) GetProcAddress(dllHandle,"GetNextZBPanIDEvent");
	if(GetNextZBPanIDEvent==NULL) return -1205;

	GetNextZeroDeliveryEvent=(typeGetNextZeroDeliveryEvent) GetProcAddress(dllHandle,"GetNextZeroDeliveryEvent");
	if(GetNextZeroDeliveryEvent==NULL) return -1206;

	SetHosePrices=(typeSetHosePrices) GetProcAddress(dllHandle,"SetHosePrices");
	if(SetHosePrices==NULL) return -1209;

	GetHosePrices=(typeGetHosePrices) GetProcAddress(dllHandle,"GetHosePrices");
	if(GetHosePrices==NULL) return -1210;

	SetPumpDefaultPriceLevel=(typeSetPumpDefaultPriceLevel) GetProcAddress(dllHandle,"SetPumpDefaultPriceLevel");
	if(SetPumpDefaultPriceLevel==NULL) return -1211;

	SetDateTime=(typeSetDateTime) GetProcAddress(dllHandle,"SetDateTime");
	if(SetDateTime==NULL) return -1212;

	dllLoaded =	true;

	return 0;
}

//-----------------------------------------------------------------------------
void CEZClient::Initializer()
{
#if defined(__linux__)
	memset(&oldTerm, 0, sizeof(oldTerm));
#endif 

	dllLoaded							=	false;
	dllHandle							=	NULL;

	DllVersion							=	NULL;
	ServerVersion						=	NULL;
	ClientLogon							=	NULL;
	ClientLogonEx						=	NULL;
	ClientLogoff						=	NULL;
	ClientStatus						=	NULL;
	GetLicenseType						=	NULL;
	FireClientEvent						=	NULL;
	TestConnection						=	NULL;
	ProcessEvents						=	NULL;
	GetEventsCount						=	NULL;
	GetNextEventType					=	NULL;
	DiscardNextEvent					=	NULL;
	GetNextPumpEvent					=	NULL;
	GetNextDeliveryEvent				=	NULL;
	GetNextServerEvent					=	NULL;
	GetNextClientEvent					=	NULL;
	GetNextDBLogEvent					=	NULL;
	GetNextDBLogDeliveryEvent			=	NULL;
	GetNextDBClearDeliveryEvent			=	NULL;
	GetNextDBStackDeliveryEvent			=	NULL;
	GetNextDBHoseETotalsEvent			=	NULL;
	GetNextDBTriggerEvent				=	NULL;
	GetNextDBAttendantLogonEvent		=	NULL;
	GetNextDBAttendantLogoffEvent		=	NULL;
	GetNextDBTankStatusEvent			=	NULL;
	GetPumpsCount						=	NULL;
	GetPumpByNumber						=	NULL;
	GetPumpByName						=	NULL;
	GetPumpByOrdinal					=	NULL;
	GetPumpProperties					=	NULL;
	SetPumpProperties					=	NULL;
	DeletePump							=	NULL;
	GetPumpHosesCount					=	NULL;
	GetPumpHoseByNumber					=	NULL;
	GetPumpStatus						=	NULL;
	GetPumpStatusEx						=	NULL;
	GetPumpDeliveryProperties			=	NULL;
	GetPumpDeliveryPropertiesEx			=	NULL;
	GetPumpDeliveryPropertiesEx2		=	NULL;
	GetPumpDeliveryPropertiesEx3		=	NULL;
	PrepayReserve						=	NULL;
	PrepayCancel						=	NULL;
	PrepayAuthorise						=	NULL;
	PreauthReserve						=	NULL;
	PreauthCancel						=	NULL;
	PreauthAuthorise					=	NULL;
	LoadPreset							=	NULL;
	LoadPresetWithPrice					=	NULL;
	TagAuthorise						=	NULL;
	AttendantAuthorise					=	NULL;
	Authorise							=	NULL;
	CancelAuthorise						=	NULL;
	TempStop							=	NULL;
	ReAuthorise							=	NULL;
	TerminateDelivery					=	NULL;
	StackCurrentDelivery				=	NULL;
	GetDensity							=	NULL;
	EnablePump							=	NULL;
	DisablePump							=	NULL;
	GetHosesCount						=	NULL;
	GetHoseByOrdinal					=	NULL;
	GetHoseProperties					=	NULL;
	SetHoseProperties					=	NULL;
	GetHoseSummary						=	NULL;
	GetHoseSummaryEx					=	NULL;
	DeleteHose							=	NULL;
	GetDeliveriesCount					=	NULL;
	GetDeliveryByOrdinal				=	NULL;
	GetAllDeliveriesCount				=	NULL;
	GetAllDeliveryByOrdinal				=	NULL;
	AckDeliveryDBLog					=	NULL;
	GetDeliveryIDByOrdinalNotLogged		=	NULL;
	GetDeliveriesCountNotLogged			=	NULL;
	AckDeliveryVolLog					=	NULL;
	GetDeliveryIDByOrdinalNotVolLogged	=	NULL;
	GetDeliveriesCountNotVolLogged		=	NULL;
	GetDeliveryProperties				=	NULL;
	GetDeliveryPropertiesEx				=	NULL;
	GetDeliveryPropertiesEx2			=	NULL;
	GetDeliveryPropertiesEx3			=	NULL;
	SetDeliveryProperties				=	NULL;
	SetDeliveryPropertiesEx				=	NULL;
	SetDeliveryPropertiesEx2			=	NULL;
	SetDeliveryPropertiesEx3			=	NULL;
	GetDeliverySummary					=	NULL;
	GetDeliverySummaryEx				=	NULL;
	GetDeliverySummaryEx2				=	NULL;
	LockDelivery						=	NULL;
	UnlockDelivery						=	NULL;
	ClearDelivery						=	NULL;
	LockAndClearDelivery				=	NULL;
	GetDuration							=	NULL;
	GetGradesCount						=	NULL;
	GetGradeByNumber					=	NULL;
	GetGradeByName						=	NULL;
	GetGradeByOrdinal					=	NULL;
	GetGradeProperties					=	NULL;
	SetGradeProperties					=	NULL;
	DeleteGrade							=	NULL;
	SetGradePrice						=	NULL;
	GetGradePrice						=	NULL;
	GetTanksCount						=	NULL;
	GetTankByNumber						=	NULL;
	GetTankByName						=	NULL;
	GetTankByOrdinal					=	NULL;
	GetTankProperties					=	NULL;
	SetTankProperties					=	NULL;
	GetTankSummary						=	NULL;
	TankDrop							=	NULL;
	DeleteTank							=	NULL;
	GetPortsCount						=	NULL;
	GetPortByNumber						=	NULL;
	GetPortByName						=	NULL;
	GetPortByOrdinal					=	NULL;
	GetPortProperties					=	NULL;
	SetPortProperties					=	NULL;
	GetAttendantsCount					=	NULL;
	GetAttendantByNumber				=	NULL;
	GetAttendantByName					=	NULL;
	GetAttendantByOrdinal				=	NULL;
	GetAttendantProperties				=	NULL;
	SetAttendantProperties				=	NULL;
	GetAttendantPropertiesEx			=	NULL;
	SetAttendantPropertiesEx			=	NULL;
	DeleteAttendant						=	NULL;
	AttendantLogon						=	NULL;
	AttendantLogoff						=	NULL;
	GetCardReadsCount					=	NULL;
	GetCardReadByNumber					=	NULL;
	GetCardReadByName					=	NULL;
	GetCardReadByOrdinal				=	NULL;
	GetCardReadProperties				=	NULL;
	SetCardReadProperties				=	NULL;
	DeleteCardRead						=	NULL;
	GetCardClientsCount					=	NULL;
	GetCardClientByNumber				=	NULL;
	GetCardClientByName					=	NULL;
	GetCardClientByOrdinal				=	NULL;
	GetCardClientProperties				=	NULL;
	SetCardClientProperties				=	NULL;
	DeleteCardClient					=	NULL;
	AllStop								=	NULL;
	AllAuthorise						=	NULL;
	AllReAuthorise						=	NULL;
	AllStopIfIdle						=	NULL;
	ReadAllTanks						=	NULL;
	GetAllPumpStatuses					=	NULL;
	GetIniValue							=	NULL;
	SetIniValue							=	NULL;
	SetNextDeliveryID					=	NULL;
	RemovePort							=	NULL;
	LicenseStatus						=	NULL;
	CheckSocketClosed					=	NULL;
	ResultString						=	NULL;
	PumpStateString						=	NULL;
	DeliveryStateString					=	NULL;
	DeliveryTypeString					=	NULL;
	ReserveTypeString					=	NULL;
	GetNextPumpEventEx					=	NULL;
	GetNextPumpEventEx2					=	NULL;
	GetNextDeliveryEventEx				=	NULL;
	GetNextDeliveryEventEx2				=	NULL;
	GetNextDeliveryEventEx3				=	NULL;
	GetNextCardReadEvent				=	NULL;
	GetNextDBHoseETotalsEventEx			=	NULL;
	GetNextDBTankStatusEventEx			=	NULL;
	GetZigBeeCount						=	NULL;
	GetZigBeeByNumber					=	NULL;
	GetZigBeeByName						=	NULL;
	GetZigBeeByOrdinal					=	NULL;
	GetZigBeeProperties					=	NULL;
	SetZigBeeProperties					=	NULL;
	DeleteZigBee						=	NULL;
	GetHosePropertiesEx					=	NULL;
	SetHosePropertiesEx					=	NULL;
	GetHosePropertiesEx2				=	NULL;
	SetHosePropertiesEx2				=	NULL;
	SetPumpPropertiesEx					=	NULL;
	GetPumpPropertiesEx					=	NULL;
	GetSerialNo							=	NULL;
	GetDeviceDetails					=	NULL;
	ResetDevice							=	NULL;
	RequestVersion						=	NULL;
	SetHoseETotals						=	NULL;
	GetNextZeroDeliveryEvent			=	NULL;
	SetHosePrices						=	NULL;
	GetHosePrices						=	NULL;
	SetPumpDefaultPriceLevel			=	NULL;
	SetDateTime							=	NULL;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Retorna apontador para mensagem referente ao codigo de erro
//   * no Windows atraves GetLastError()
//   * no Linux usando errno
//
// parametros:
//		erro      : codigo de erro
//		lpszBuffer: ponteiro para buffer de armazenamento da mensagem
//		dwSize    : comprimento do buffer
//
// retorna o ponteiro para buffer de mensagem.
//
void CEZClient::GetLastErrorText(DWORD erro, LPTSTR lpszBuffer, DWORD dwSize)
{
#ifdef _WIN32 // no Windows
  DWORD   dwRet, dwFlags;
  LPTSTR  lpszTemp = NULL;

    dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY;
    dwRet = FormatMessage(dwFlags, NULL, erro, LANG_NEUTRAL,(LPTSTR)&lpszTemp, 0, NULL);

    if( !dwRet || ((long)dwSize<(long)dwRet+14) )
      lpszBuffer[0] = TEXT('\0');
    else
    {
      lpszTemp[lstrlen(lpszTemp)-2] = TEXT('\0');
      _stprintf(lpszBuffer, TEXT("%s (0x%x)"), lpszTemp, GetLastError() );
    }

    if( lpszTemp )
      LocalFree((HLOCAL)lpszTemp);

#endif // _WIN32

#ifdef __linux__ // no Linux
    strcpy(lpszBuffer, strerror(erro));
#endif  // __linux__
}

//---------------------------------------------------------------------------------------
// Le uma tecla a partir do console (STDIN) sem a necessidade de um ENTER para final
//    * Similar a funcao "getch()"
// retorna a tecla pressionada ou 0 (zero)
char CEZClient::KBget()
{
	char   key = 0;        // buffer

#if defined(__linux__)
	struct termio old_tty; // Configuracao atual
	struct termio new_tty; // configuracao nova

	// le configuracao atual
	if (ioctl(STDIN_FILENO, TCGETA, &old_tty) < 0)
		return(0);

	new_tty	= old_tty;

	new_tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	new_tty.c_oflag &= ~OPOST;
	new_tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	new_tty.c_cflag &= ~(CSIZE | PARENB);
	new_tty.c_cc[4]  = 01;

	// ajusta os parametros para o nova
	if (ioctl(STDIN_FILENO, TCSETA, &new_tty) < 0)
		return(0);

	// le 1 byte (tecla)
	if(read(STDIN_FILENO, &key, sizeof(key)) < 0)
		return(0);

	// volta a configuracao original
	if (ioctl(STDIN_FILENO, TCSETA, &old_tty) < 0)
		return(0);

#elif defined(_WIN32)

	key = getch();

#endif

	return(key);
}

//------------------------------------------------------------------------------
// Detecta se uma tecla foi pressionada no teclado (equivalente a funcao kbhit)
// Nao para o aplicativo para esperar o pressionamento da tecla.
// Retorna 1 (um) se uma tecla foi pressiona ou 0 (zero) se nada ocorre.
int CEZClient::KBhit()
{
	int hkey = 0;

#if defined(__linux__)
    static const int STDIN = 0;
    termios term;

	if( !oldTerm.c_lflag )
	{
		tcgetattr(STDIN_FILENO, &term);
		tcgetattr(STDIN_FILENO, &oldTerm);

		term.c_lflag &= ~(ECHO | ICANON);

		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}

    setbuf(stdin, NULL);

    ioctl(STDIN_FILENO, FIONREAD, &hkey);

#elif defined(_WIN32)

	hkey = kbhit();

#endif

    return(hkey);
}

