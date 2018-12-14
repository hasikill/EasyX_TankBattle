#pragma once
#include "CGame.h"
#include "CGameUI.h"

//窗口宽高
#define SCR_WIDTH         (640)
#define SCR_HEIGHT        (416)

//图片素材路径
#define IMG_MENU_PATH    "img\\menu.gif"
#define IMG_OBJECT_PATH  "img\\tankAll.gif"

//墙的生命值
#define WALL_LIFE         2
//敌人到达战场间隔
#define ENEMY_TIME        3   //单位秒
//buff到达战场时间
#define BUFF_TIME         10  //单位秒

//玩家生命数量
#define PLAYER1_LIFE_NUM  3
#define PLAYER2_LIFE_NUM  3

//坦克数量
#define TANK_ENEMEY_NUM   16 //敌军
#define TANK_PLAYER_NUM   2  //玩家

#define TIME_ROBOT_GENERATE 5000
#define ROBOT_NUMBER 16

//二维地图数据
extern unsigned char g_CurMapData[26][26];

//坦克信息数据
extern int g_aryTankInfo[7][5];

//游戏所有数据全局指针
extern CGame *g_Game;

extern CGameUI *ui;