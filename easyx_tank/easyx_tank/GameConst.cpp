#include "GameConst.h"
#include "CGameUI.h"

//游戏所有数据全局指针
CGame *g_Game;

//屏幕
CGameUI *ui;

unsigned char g_CurMapData[26][26];

//坦克信息数据
int g_aryTankInfo[7][5] = 
{
  //生命值,伤害,移动速度,子弹速度,弹夹数
  {  5, 2, 2, 2 ,1},
  {  4, 2, 2, 2 ,1},
  {  2, 8, 3, 5 ,2},
  {  4, 1, 2, 4 ,1},
  {  8, 1, 1, 4 ,4},
  {  10,2, 1, 4 ,3},
  {  4, 2, 3, 4 ,2}
};