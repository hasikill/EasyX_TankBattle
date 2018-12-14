#include <iostream>
#include "CGameUI.h"
#include "GameConst.h"
#include "CTank.h"

int main()
{
  //创建游戏UI
  ui = new CGameUI(SCR_WIDTH, SCR_HEIGHT);
  //创建玩家1
  CPlayer player1 = CPlayer("Player1", { 140,385 }, PLAYER1_LIFE_NUM);
  //创建玩家2
  CPlayer player2 = CPlayer("Player2", { 244,385 }, PLAYER2_LIFE_NUM);
  //创建游戏
  g_Game = new CGame(player1, player2);

  while (1)
  {
    //初始化
    if (g_Game->Init() == false)
    {
      break;
    }

    //显示菜单
    ui->DrawMenu();

    //选择游戏模式
    CGameUI::emChoose choose = ui->MenuChoose();

    //单人模式
    if (choose == CGameUI::CHO_SINGLE)
    {
      //单人模式
      g_Game->SetGameMode(CGame::MODE_SINGLE);
    }
    else if (choose == CGameUI::CHO_DOUBLE)
    {
      //双人模式
      g_Game->SetGameMode(CGame::MODE_DOUBLE);
    }

    //读取地图关卡数据
    if (g_Game->LoadMapData() == false)
    {
      printf(">>> 读取关卡数据出错...\r\n");
      break;
    }

    //初始化数据
    g_Game->InitData();

    //开始游戏
    g_Game->start();

  }//玩家死亡又回到菜单

  printf("exit!!\r\n");
  getchar();
  return 0;
}