﻿#include "stdafx.h"
#include <ddraw.h>
#include <Io.h>
#include "Hangul.h"
#include "dragon.h"
#include "SmallMenuSet.h"
#include "Menu.h"
#include "SmallMenu.h"
#include "Hong_Sub.h"
#include "Hong_Sprite.h"
#include "stdio.h"
#include "directsound.h"
#include "directinput.h"
#include "Char.h"
#include "Effect.h"
#include "map.h"
#include "tool.h"
#include "MenuSet.h"
#include "convert565to555.h"
#include "Math.h"
#include "MenuNetwork.h"
#include "GameProc.h"
#include "CharDataTable.h"
#include "object.h"
#include "Item.h"
#include <direct.h>
#include "linecommand.h"
#include "word.h"
#include "kh_cpp.h"




//扁夯汲沥 
//努贰胶 
#define LOW			200
#define C_GENERAL	300
#define HIGH		400
#define SUPERIOR	500
#define C_GREAT		600
#define CRUSADER	700

//流诀 
#define J_GENERAL	200
#define PRECISE		300
#define GOOD		400
#define TRUST		500
#define HONORABLE	600
#define J_GREAT		700

//窃荐 
void	Func_Division(void);	//蔼惑铰俊蝶扼 Division 函荐狼 蔼阑 函版窍咯 利侩虐 困茄... 
//函荐 
int		Class_Division;				//努贰胶 疙己摹 蔼惑铰俊蝶弗 备盒阑困茄 函荐 	
int		Job_Division;				//流诀 疙己摹 蔼惑铰俊蝶弗 备盒阑困茄 函荐 	
int		QUEST_GIVE;
int		QUEST_COUNT;

int		quest_num[QUEST_MAX] ; 
//SCharacterData.nCharacterData[SPELL]
void IncreaseFamous( int class_plus, int job_plus )
{
	SCharacterData.class_famous += class_plus;
	//
	// 努饭胶 疙己捞 惑铰沁阑 锭 绢恫 贸府啊 乐促搁...
	//

	SCharacterData.job_famous += job_plus;
	Func_Division();
	//
	// 流诀 疙己捞 惑铰沁阑锭...
	//
}

void DecreaseFamous( int class_plus, int job_plus )
{
	SCharacterData.class_famous -= class_plus;
	if( SCharacterData.class_famous < 0 ) SCharacterData.class_famous = 0;
	//dik窍遏沁阑 锭, 贸府秦具且 何盒捞 乐促搁 咯扁俊...
	//
	
	SCharacterData.job_famous -= job_plus;
	if( SCharacterData.job_famous < 0 ) SCharacterData.job_famous = 0;
	Func_Division();
}

void Func_Division(){
	//努贰胶 疙己摹 
	if(SCharacterData.class_famous > 0 && SCharacterData.class_famous < LOW)					Class_Division = 1;
	else if(SCharacterData.class_famous > LOW && SCharacterData.class_famous < C_GENERAL)			Class_Division = 2;
	else if(SCharacterData.class_famous > C_GENERAL && SCharacterData.class_famous < HIGH)		Class_Division = 3;
	else if(SCharacterData.class_famous > HIGH && SCharacterData.class_famous < SUPERIOR)		Class_Division = 4;
	else if(SCharacterData.class_famous > SUPERIOR && SCharacterData.class_famous < C_GREAT)	Class_Division = 5;
	else if(SCharacterData.class_famous > C_GREAT && SCharacterData.class_famous < CRUSADER)	Class_Division = 6;
	//流诀 疙己摹 
	if(SCharacterData.job_famous > 0 && SCharacterData.job_famous < J_GENERAL)					Job_Division = 1;
	else if(SCharacterData.job_famous > J_GENERAL && SCharacterData.job_famous < PRECISE)			Job_Division = 2;
	else if(SCharacterData.job_famous > PRECISE && SCharacterData.job_famous < GOOD)			Job_Division = 3;
	else if(SCharacterData.job_famous > GOOD && SCharacterData.job_famous < TRUST)				Job_Division = 4;
	else if(SCharacterData.job_famous > TRUST && SCharacterData.job_famous < HONORABLE)			Job_Division = 5;
	else if(SCharacterData.job_famous > HONORABLE && SCharacterData.job_famous < J_GREAT)		Job_Division = 6;
	
}


ReadQuestTable  quest_text[QUEST_MAX];
// 富弊措肺 涅胶飘 抛捞喉阑 阂矾 柯促. 
void LoadQuestTable( char *filename,char* filename2, char *filename_bin)
{
	
	char text[1024];
	char text1[1024];
	FILE *fp;
	
	if(fp = Fopen( filename, "rt" ))
	{
		int count = 0;
		while( fgets( text, 1024, fp) != NULL )
		{
			if( text[0] == '#' || text[0] == ';' ) continue;
			quest_text[count].LoadTable( text );
			count++;
		}
		fclose( fp );
		count = 0;
		fp = Fopen( filename2, "rt" );	
		while( fgets( text1, 1024, fp) != NULL )
		{
			if( text1[0] == '#' || text1[0] == ';' ) continue;
			quest_text[count].LoadPicture( text1 );
			count++;
		}
		fclose( fp );
				
		
		if( Fopen ( filename_bin, "wb" ))
		{
			char* tt = (char*)quest_text;
			char crc = 0;
			while(fgets( text, 1024, fp) != NULL){
				crc += *tt;
				tt++;
			}
			fwrite( &crc, 1, 1, fp);
			fwrite( quest_text, sizeof(ReadQuestTable), QUEST_MAX, fp);
			fwrite( &crc, 1, 1, fp);
			fclose(fp);
		}
	}
	else
	{
		
		if( fp = Fopen( filename_bin, "rb" ))
		{
			char* tt = (char*) quest_text;
			char crc = 0,crc1,crc2;
			fread( &crc1, 1, 1, fp);
			fread( quest_text, sizeof(ReadQuestTable), QUEST_MAX, fp );
			fread( &crc2, 1, 1, fp);
			fclose(fp );

			for( int i=0; i<QUEST_MAX; i++ )
			{
				quest_text[i].SaveTable();
			}
		}
		else return;
	}
	return ;
	
}




// 涅胶飘 抛捞喉捞尔 持坷档 登绰单 抛捞喉捞 沥府啊 登绢乐瘤 臼酒辑 
// 蝶肺 父甸绢初篮 颇老阑 阂矾柯促. 
void ReadQuestTable::LoadPicture( char *text )	{
	
	char *token = strtok(text,",\t\n");
	if( !token ) return;
	picnum = atoi(token);
		
	token= strtok(NULL, ",\t\n") ;
	if( !token ) return;
	strcpy( picture, token );
}



void ReadQuestTable::SaveTable()
{
	return;
	FILE *fp;
	fp = fopen( "quest.txt", "at+" );
	if( !fp ) return;

	fprintf( fp, "%d	%d	%s	%d	%s	", num, code, name, place, ch );
	for( int i=0; i<QUEST_IF_COUNT; i++ )
	{
		fprintf(fp, "%d	", quest_if[i] );
	}
	for(int i=0; i<QUEST_TAKE_COUNT; i++ )
	{
		fprintf(fp, "%d	", quest_take[i] );		
	}
	fprintf( fp, "\n" );
	fclose( fp );

	fp = fopen( "questpic.txt", "at+" );
	if( !fp ) return;

	fprintf( fp, "%d	%s\n", picnum, picture );
	fclose( fp );
	return;

}

void ReadQuestTable::LoadTable( char *text )	// 巩磊凯俊辑 单捞鸥甫 盒府
{
	char *token = strtok(text,",\t\n");
	if( !token ) return;
	num = atoi( token );

	token= strtok(NULL, ",\t\n") ;
	if( !token ) return;
	code = atoi(token);
	
	token = strtok(NULL,",\t\n");
	if( !token ) return;
	strcpy( name, token );
	
	token= strtok(NULL, ",\t\n") ;
	if( !token ) return;
	place = atoi(token);
	
	token = strtok(NULL,",\t\n");
	if( !token ) return;
	strcpy( ch, token );
	
	for(int i = 0 ; i < QUEST_IF_COUNT; i++){
		token= strtok(NULL, ",\t\n") ;
		if( !token ) return;
		quest_if[i] = atoi(token);
	}

	for(int i = 0 ; i < QUEST_TAKE_COUNT; i++){
		token= strtok(NULL, ",\t\n") ;
		if( !token ) return;
		quest_take[i] = atoi(token);
	}
	
	///////////////////////////
	// 亲格 眠啊
}

//////////////////////////////////////////
// 贸澜 矫累 何福扁
void kh_InitMenu()
{
	//LoadQuestTable("./quest/quest.txt");
}

int end_quest[200];

void SetEndQuest(int num )
{
	//for( int i=0; i<3; i++ )
		end_quest[num] = 1;
		return ;
}

void SetStartQuest(int num){
	QUEST_GIVE = rand()%4;
	quest_num[QUEST_COUNT++] = QUEST_GIVE;
	
	if(QUEST_COUNT > 200 ) QUEST_COUNT = 200;
	return;
}
//if( end_quest[quest_num] ) --> 己傍茄 涅胶飘..


void kh_KeyProc()
{
	if(g_aCurrentKeys[DIK_R] & 0x80)
	{
		CallSmallMenu(MN_CHARACTER_COLOR_CHANGE);		// 涅胶飘 皋春
	}
	if(g_aCurrentKeys[DIK_M] & 0x80)
	{
		if(!SMenu[MN_CHARACTER_COLOR_CHANGE].key){
			SMenu[MN_CHARACTER_COLOR_CHANGE].key = 1;		// 涅胶飘 皋春
		}
		else {
			SMenu[MN_CHARACTER_COLOR_CHANGE].key = 0;
		}
	}// けしさずけい 
	//FAME
	
	if(g_aCurrentKeys[DIK_B] & 0x80)
	{
		
		//SetStartQuest(1);
		//CallSmallMenu(MN_FAME);		// 涅胶飘 皋春
		SendReqQuestIndex( 1 );
	}

	if(g_aCurrentKeys[DIK_X] & 0x80 )
	{	
		kein_kh_key_on = true;
	}
}


void FreeQuest()
{
	for( int i=0; i<QUEST_MAX;i++ )
		if( quest_text[i].sq.img ) FreeSpriteOnlyOne( &quest_text[i].sq );
}

void QestDataFree( )
{
	memset( quest_num, 0, sizeof( int ) *QUEST_MAX );
	memset( end_quest, 0, sizeof( int ) *QUEST_MAX );
	QUEST_COUNT = 0;
}








//////////////////////////////////////1010 kkh 眠啊 //////////////////////////////////////
void CharacterWorkingWater( LPCHARACTER ch )
{
	//1010 kkh 眠啊 
	static bool FIRSTONWATER = TRUE; // 1010 kkh 拱 茄锅父 拌加 嘛绰 弊覆 困秦 
	if( TileMap[ch->x / TILE_SIZE][ch->y / TILE_SIZE].attr_river == 1) {// 父距俊 辑乐绰 镑捞 拱加己牢 镑捞扼搁.. 
		
		static int tempCHtileX = 0,tempCHtileY = 0;
		if( tempCHtileX  > ch->x / TILE_SIZE || tempCHtileX < ch->x / TILE_SIZE \
			|| tempCHtileY > ch->y / TILE_SIZE || tempCHtileY < ch->y / TILE_SIZE){
			{ //
				if(abs(tempCHtileX - (ch->x / TILE_SIZE))+abs(tempCHtileY - (ch->y / TILE_SIZE)) >= 1){
					switch(ch->nCurrentAction){
					case ACTION_BASIC_WALK			:{
							InsertMagic(ch, ch, 490, 0, 0,0,0,0);
							InsertMagic(ch, ch, 491, 0, 0,0,0,0);
							PlayListAutoSounds( rand()%2+1148, 0, 0,0 );
							break;
													 }
					case ACTION_RUN					:{
							InsertMagic(ch, ch, 492, 0, 0,0,0,0);
							InsertMagic(ch, ch, 493, 0, 0,0,0,0);
							PlayListAutoSounds( rand()%2+1145, 0, 0,0 );
							break;
													 }
	 				
					}
					tempCHtileX = ch->x / TILE_SIZE;  // 泅犁 谅钎甫 扁撅 矫难 初绰促.
					tempCHtileY = ch->y / TILE_SIZE;  // 促澜俊 甸绢 吭阑锭 厚背 窍扁 困秦
				}
				
			}	
				//FIRSTONWATER = TRUE;
		}
	}
	
	//////////////////////////////////////1010 kkh 眠啊 场 //////////////////////////////////////
}
						   



