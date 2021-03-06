﻿#ifndef __SCRP_EXE_H__
#define __SCRP_EXE_H__

#define QUEST_SPY						56			// 스파이 퀘스트 번호
#define QUEST_SPY_END_STEP				200			// 종료 조건

#define _SCRIPT_VARABLE_POINT_			300
#define _SCRIPT_FUNCTION_POINT_			150
#define MAX_STRING_						512

#define EVENT_TYPE_NPC					0
#define EVENT_TYPE_MAPTILE				1

#define SCRIPT_START_SETTING			0
#define SCRIPT_BULLETIN_BOARD			1

#define EVENT_SYSTEM_FUNCTION_TOTAL		10
#define EVENT_NPC_FUNCTION_TOTAL		50
#define EVENT_BOX_FUNCTION_TOTAL		10

#define EVENT_SYSTEM_FUNCTION_START		0
#define EVENT_NPC_FUCTION_START			( EVENT_SYSTEM_FUNCTION_TOTAL)
#define EVENT_MAPTILE_FUCTION_START		( EVENT_SYSTEM_FUNCTION_TOTAL+EVENT_NPC_FUNCTION_TOTAL)

#define sYES									(var[EventPC][0])
#define sRECALL_SCRP_NO							(var[EventPC][1])
#define sRECALL_CURTIME							(var[EventPC][2])
#define sRECALL_AFTTIME							(var[EventPC][3])
#define sRECALL_SCRIPT_COUNT					(var[EventPC][4])

#define s_RandomNumber							(var[EventPC][5])
#define s_PcMoney								(var[EventPC][6])
#define s_Nation								(var[EventPC][7])		// 010530 YGI

#define s_SymBol_Get_NPC_Check_WARRIOR			(var[EventPC][24])		// add by taniey, value: 205
#define s_SymBol_Get_NPC_Check_THIEF			(var[EventPC][25])		// add by taniey, value: 255
#define s_SymBol_Get_NPC_Check_ARCHER			(var[EventPC][26])		// add by taniey, value: 500
#define s_SymBol_Get_NPC_Check_WIZARD			(var[EventPC][27])		// add by taniey, value: 400
#define s_SymBol_Get_NPC_Check_PRIEST			(var[EventPC][28])		// add by taniey, value: 400

#define s_SymBol_Upgrade_NPC_Check				(var[EventPC][30])		// add by taniey, value: 3995

#define s_Dual_NPC_Check						(var[EventPC][182])		// add by taniey, value: 2. 601; 3. 602; 4. 603; 5. 604; 6.605;

#define DUAL_FAME_FIELD							10 // 스파이게임 스크립트 변수 
#define s_GhostLvDef							64
#define s_GhostEndCountDef						65
#define VAR_RESET								47 // DB Demon에서 캐릭터데이터 초기화으로 사용 

struct QT
{
	DWORD Tick;
	void(*Func)(void);

	int ExtInt;
	char ExtChar[255];
};

extern void(*TimerFunc[_SCRIPT_FUNCTION_POINT_])(void);
extern QT QTickData[DRAGON_MAX_CONNECTIONS_];
extern DWORD QTemp;
extern DWORD QTick;
extern void RecvEvent(t_client_event *pEvent, short int cn);

extern void(*SFunction[_SCRIPT_FUNCTION_POINT_])(void);
extern int var[DRAGON_MAX_CONNECTIONS_][_SCRIPT_VARABLE_POINT_];
extern int EventPC, EventNPC[DRAGON_MAX_CONNECTIONS_];
extern void ReCallScript(void);
extern void Recv_CMD_QUEST_JOB_FINISH(int cn, int type);
extern void QuestSecond();
extern int MapMove(int idUser, const char* pMapName, int nX, int nY);
extern int GotoMap(int cn, int nMapPort, int nMoveX, int nMoveY);
extern int SearchItemByInv(int item_no, CHARLIST *ch);
extern int SearchItemByInv(int item_no, CHARLIST *ch, int &a, int &b, int &c);
extern int SendDial(short int cn, int npc_index, char *msg, int length);// npc에게 대화를 보낸다.

enum eLDF_TYPE //enum Log Dual Fame
{
	LDF_LOCALWAR = 0,			// 국지전
	LDF_QUEST = 1,			// 퀘스트
	LDF_NEOWAR = 2,			// LTH-040226-KO 1.4 이후 신규국가전용
};

//040719_KJHuNs g_pLogManager로 이동(정리 목적)
//extern void SaveLogChange_DualFame(CHARLIST *ch, const int nOldDualFame, const int nNewDualFame, eLDF_TYPE type); //030226 lsw
//

extern int var[DRAGON_MAX_CONNECTIONS_][_SCRIPT_VARABLE_POINT_];

#endif




