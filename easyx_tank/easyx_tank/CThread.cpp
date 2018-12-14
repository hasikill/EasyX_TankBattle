#include "CThread.h"
#include <iostream>
#include "GameConst.h"

#pragma warning(disable:4996)

//坦克保护动画
void TankProtectAnimeProc(void *p);

CThread::CThread()
{
  
}


CThread::~CThread()
{
}

void CThread::startTankProtectAnime(CTank * tank)
{
  start(TankProtectAnimeProc, tank);
}


void CThread::start(_beginthread_proc_type _StartAddress, void *arg)
{
  //启动线程
  _beginthread(_StartAddress, 0, arg);
}

//坦克保护动画
void TankProtectAnimeProc(void *p)
{
  //坦克
  CTank *tank = (CTank *)p;

  //设置状态
  tank->bAnimeFlag = true;

  //保护时间
  int ProtectTime = tank->getStatusTime();

  for (int i = 0; i < ProtectTime; i+= 150)
  {
    if (tank->bMoveFlag == false && tank->isAlive())
    {
      tank->bFrameFlag = !tank->bFrameFlag;
      ui->DrawTank(tank->m_pos.getX(), tank->m_pos.getY(), tank->getType(), tank->getDirection());
      ui->DrawProtect(tank->m_pos.getX(), tank->m_pos.getY(), tank->bFrameFlag);
    }
      ui->Wait(150);
  }

  if (tank->isAlive())
  {
    ui->Wait(150);
    ui->DrawTank(tank->m_pos.getX(), tank->m_pos.getY(), tank->getType(), tank->getDirection());
    //
    tank->nFrameTime = 0;
    //关闭状态
    tank->setTankStatus(CTank::STATUS_NONE, 0);
    //设置状态
    tank->bAnimeFlag = false;
  }
  
}