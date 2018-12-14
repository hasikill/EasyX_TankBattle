#include "CPlayer.h"
#include "GameConst.h"
#include <iostream>

//构造
CPlayer::CPlayer(const char *name, CPosition pos,int nLifeNum)
  : m_nLifeNum(nLifeNum), CTank(name, CTank::TANK1, pos, CTank::CAMP_PLAYER)
{
  //初始坐标
  init_pos = pos;
  //初始生命值
  init_lifenum = m_nLifeNum;
  //初始化其它数据
  init();
}

CPlayer::~CPlayer()
{
  
}

void CPlayer::init()
{
  //初始化父类
  __super::init();
  //积分
  m_nScore = 0;
  //杀敌数
  m_nKillNum = 0;
  //设置状态
  setTankStatus(CTank::STATUS_PLAYERINIT, 0);
  //初始生命值
  m_nLifeNum = init_lifenum;
  //初始坐标
  m_pos = init_pos;
  //设置方向
  m_emDir = CTank::DR_UP;
  //存活
  toAlive();
}

bool CPlayer::onHitBy(int nDamage)
{
  if (isAlive() == false)
  {
    return false;
  }

  if (m_emTankStatus != STATUS_PROTECT && SubHp(nDamage) == false)
  {
    //声音
    g_Game->Sound.PlayPlayerCrackSound();
    //清除显示
    g_Game->GameUi->ClearRect(m_pos.getX(), m_pos.getY(), TANK_SIZE, TANK_SIZE);
    //调用死亡
    toDie();
    //生命数--
    m_nLifeNum--;
    if (m_nLifeNum > 0)
    {
      //复活
      revive();
    }
    else
    {
      //游戏结束
      g_Game->GameOver();
    }
    return true;
  }

  return false;
}

//击杀敌人调用
void CPlayer::onKillEnemy(CLifeEntity & life)
{
  if (isAlive() == false)
  {
    return ;
  }

  CLifeEntity::emLifeType lfType = life.GetLifeType();
  if (lfType == CLifeEntity::LF_BARRIER)
  {
    //障碍物
    CBarrier *bar = (CBarrier *)&life;
    CBarrier::emBarrierType barType = bar->getType();

    switch (barType)
    {
    case CBarrier::BAR_WALL:
      //printf("玩家[%s] : 哈哈,去你的墙壁,敢挡我的路!\r\n", m_strTankName.c_str());
      break;
    case CBarrier::BAR_IRON:
      printf("玩家[%s] : 铁块很硬吗,我照样干掉你!\r\n", m_strTankName.c_str());
      break;
    case CBarrier::BAR_HOME:
      printf("玩家[%s] : 迟早被敌人打掉,还不如我自己来!\r\n", m_strTankName.c_str());
      break;
    }
  }
  else if (lfType == CLifeEntity::LF_TANK)
  {
    //坦克
    CTank *tank = (CTank *)&life;
    //获取阵营
    //printf("玩家[%s] : 小渣渣们,胆颤了吗,我干掉了你们的[%s]!!\r\n", m_strTankName.c_str(), tank->getTankName().c_str());
    //加分
    m_nScore = m_nScore + 100;
    //杀敌数
    addKillNum(1);
  }
}

void CPlayer::revive()
{
  __super::revive();
  //状态
  setTankStatus(CTank::STATUS_PLAYERINIT, 0);
  //初始坐标
  m_pos = init_pos;
}

void CPlayer::addLifeNum(int num)
{
  m_nLifeNum = m_nLifeNum + num;
}

void CPlayer::addMagazine(int num)
{
  int nMag = m_nMagazine + num;;
  if (nMag < MAX_BULLET)
  {
    m_nMagazine = nMag;
  }
}

void CPlayer::setBulletSpeed(int speed)
{
  m_nBulletSpeed = speed;
}

void CPlayer::addScore(int nScore)
{
  m_nScore = m_nScore + nScore;
}

void CPlayer::addKillNum(int nKillNum)
{
  m_nKillNum = m_nKillNum + nKillNum;
}

int CPlayer::getScore()
{
  return m_nScore;
}

int CPlayer::getKillNum()
{
  return m_nKillNum;
}

void CPlayer::onDown()
{
  if (isAlive() == false)
  {
    return ;
  }

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
    }
  }
}

void CPlayer::onUp()
{
  if (isAlive() == false)
  {
    return ;
  }

  //获取速度
  int nSpeed = getMoveSpeed();
  CPosition pos = m_pos;

  //改变方向
  toUp();

  if (pos.toUp(nSpeed))
  {
    //碰撞检测
    if (g_Game->CheckTankCrash(*this, pos) == false)
    {
      move(CTank::DR_UP);
    }
  }
}

void CPlayer::onRight()
{
  if (isAlive() == false)
  {
    return ;
  }

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
    }
  }
}

void CPlayer::onLeft()
{
  if (isAlive() == false)
  {
    return;
  }

  //获取速度
  int nSpeed = getMoveSpeed();
  CPosition pos = m_pos;

  //改变方向
  toLeft();

  if (pos.toLeft(nSpeed))
  {
    //碰撞检测
    if (g_Game->CheckTankCrash(*this, pos) == false)
    {
      move(CTank::DR_LEFT);
    }
  }
}

void CPlayer::onFire()
{
  //开火
  fire();
}
