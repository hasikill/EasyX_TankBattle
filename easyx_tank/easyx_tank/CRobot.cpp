#include "CRobot.h"
#include <iostream>
#include "GameConst.h"
#include <time.h>

CRobot::CRobot(std::string strTankName, emTankType emType, CPosition pos, emTankCamp camp) : CTank(strTankName, emType, pos, camp)
{
  //初始坐标
  init_pos = pos;
}

CRobot::~CRobot()
{
}

void CRobot::init()
{
  //初始化父类
  __super::init();
  //设置状态
  setTankStatus(CTank::STATUS_ENEMYINIT, 0);
  //位置复位
  m_pos = init_pos;
  //时间
  m_nStopTime = 0;
  //起始时间
  startTime = 0;
}

//复活
void CRobot::revive()
{
  //存活
  __super::toAlive();
  //置状态
  init();
}

bool CRobot::moveLeft()
{
  //获取速度
  int nSpeed = getMoveSpeed();
  CPosition pos = m_pos;

  //改变方向
  toLeft();

  if (pos.toLeft(nSpeed))
  {
    if (pos.getX() <= 0)
    {
      return false;
    }
    //碰撞检测
    if (g_Game->CheckTankCrash(*this, pos) == false)
    {
      move(CTank::DR_LEFT);
      return true;
    }
  }
  return false;
}

bool CRobot::moveDown()
{
  //获取速度
  int nSpeed = getMoveSpeed();
  CPosition pos = m_pos;

  //改变方向
  toDown();

  if (pos.toDown(nSpeed))
  {
    //碰撞检测
    if (g_Game->CheckTankCrash(*this, pos) == false)
    {
      move(CTank::DR_DOWN);
      return true;
    }
  }
  return false;
}

bool CRobot::moveUp()
{
  //获取速度
  int nSpeed = getMoveSpeed();
  CPosition pos = m_pos;

  //改变方向
  toUp();

  if (pos.toUp(nSpeed))
  {
    if (pos.getY() <= 0)
    {
      return false;
    }
    //碰撞检测
    if (g_Game->CheckTankCrash(*this, pos) == false)
    {
      move(CTank::DR_UP);
      return true;
    }
  }
  return false;
}

bool CRobot::moveRight()
{

  //获取速度
  int nSpeed = getMoveSpeed();
  CPosition pos = m_pos;

  //改变方向
  toRight();

  if (pos.toRight(nSpeed))
  {
    //碰撞检测
    if (g_Game->CheckTankCrash(*this, pos) == false)
    {
      move(CTank::DR_RIGHT);
      return true;
    }
  }
  return false;
}

bool CRobot::onHitBy(int nDamage)
{
  if (SubHp(nDamage) == false)
  {
    //声音
    g_Game->Sound.PlayTankCrackSound();
    //清除显示
    clearCurPos();
    //调用死亡
    toDie();
    return true;
  }
  return false;
}

void CRobot::create()
{
  bAnimeDieFlag = true;
  __super::toDie();
}

void CRobot::onKillEnemy(CLifeEntity & life)
{
}

void CRobot::motion()
{
  //机器人停止控制
  if (m_nStopTime > 0)
  {
    if (startTime == 0)
    {
      startTime = clock();
    }
    clock_t endTime = clock();
    if (endTime - startTime < m_nStopTime)
    {
      return;
    }
    else
    {
      m_nStopTime = 0;
      startTime = 0;
    }
  }

  int nProb = rand() % 200;

  //中途转向的几率 %2
  if (nProb <= 4)
  {
    m_emDir = (emTankDirection)(rand() % 4);
  }

  switch (m_emDir)
  {
  case CTank::DR_UP:
  {
    if (moveUp() == false)
    {
      if (nProb < 15)
      {
        m_emDir = (emTankDirection)(2 + rand() % 2);
      }
    }
  }
    break;
  case CTank::DR_DOWN:
  {
    if (moveDown() == false)
    {
      if (nProb < 15)
      {
        m_emDir = (emTankDirection)(2 + rand() % 2);
      }
    }
  }
    break;
  case CTank::DR_LEFT:
  {
    if (moveLeft() == false)
    {
      if (nProb < 20)
      {
        m_emDir = (emTankDirection)(rand() % 2);
      }
    }
  }
    break;
  case CTank::DR_RIGHT:
  {
    if (moveRight() == false)
    {
      if (nProb < 20)
      {
        m_emDir = (emTankDirection)(rand() % 2);
      }
    }
  }
    break;
  }

  //开火的几率
  if (nProb < ENEMY_LEVEL)
  {
    fire();
  }
}

void CRobot::SetStopTime(int nTime)
{
  m_nStopTime = nTime;
}

void CRobot::toDie()
{
  __super::toDie();
  //机器人死亡数量
  g_Game->nDieRobotNum++;
  //玩家胜利
  if (g_Game->nDieRobotNum >= ROBOT_NUMBER)
  {
    std::cout << "玩家胜利!\r\n" << std::endl;
    ui->Wait(1000);
    g_Game->PlayerWin();
  }
}
