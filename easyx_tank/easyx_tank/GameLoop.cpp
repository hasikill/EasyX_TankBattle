#include "CGame.h"
#include "GameConst.h"

/*
  游戏主要的循环
*/
void CGame::GameLoop()
{
  //清屏一次
  ui->Clear();

  //显示地图
  ui->DrawMap();

  //按键CD分配
  int count = 0;

  //游戏逻辑循环
  while (!isGameOver() && !isPlayerWin())
  {
    //添加敌人到战场
    if (count % (ENEMY_TIME * 100) == 0)
    {
      AddRobot();
    }
    
    //添加buff到战场
    if (count % (BUFF_TIME * 100) == 0)
    {
      GenerateBuff();
    }

    //AI运动
    MotionAllRobot();

    //刷新buff
    FlushAllBuff();

    //画所有坦克
    FlushAllTank();

    //画所有的子弹
    FlushAllBullet();
    
    //玩家1操作
    if (GetAsyncKeyState('W') & 0x8000)
    {
      Player1.onUp();
    }
    else if (GetAsyncKeyState('S') & 0x8000)
    {
      Player1.onDown();
    }
    else if (GetAsyncKeyState('A') & 0x8000)
    {
      Player1.onLeft();
    }
    else if (GetAsyncKeyState('D') & 0x8000)
    {
      Player1.onRight();
    }
    //玩家1开火键
    if (GetAsyncKeyState('J') & 0x8000)
    {
      if (count % 10 == 0)
      {
        Player1.onFire();
      }
    }

    //玩家2操作
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
      Player2.onUp();
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
      Player2.onDown();
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
      Player2.onLeft();
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
      Player2.onRight();
    }
    //玩家2开火键
    if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
    {
      if (count % 10 == 0)
      {
        Player2.onFire();
      }
    }
  
    //按键弹起
    if (!(GetAsyncKeyState(VK_UP) & 0x8000))//按键弹起
    {
      Player1.bMoveFlag = false;
      Player2.bMoveFlag = false;
    }

    //CD记时
    count++;
    //高CPU
    ui->Wait(nGameSpeed);
    //不占CPU
    //Sleep(nGameSpeed);
  }
  
  //释放数据
  ReleaseData();
  //清除屏幕
  ui->Clear();
}
