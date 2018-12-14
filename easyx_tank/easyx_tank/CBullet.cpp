#include "CBullet.h"
#include "CTank.h"
#include "GameConst.h"
#include <time.h>

CBullet::CBullet(CTank& tank, int nId, CPosition pos, int nSpeed, int nDir, int nPower)
  : m_tank(tank), m_nId(nId), m_nSpeed(nSpeed), m_nDir(nDir), m_nPower(nPower), CPosition(pos)
{
  if (tank.getCamp() == CTank::CAMP_ENEMY)
  {
    m_nType = 1;
  }
  else if (tank.getCamp() == CTank::CAMP_PLAYER)
  {
    m_nType = 0;
  }
  //显示坐标
  PrevPos.setPos(getX(), getY());
  //爆炸状态
  isBoom = false;
  //存活状态
  isAlive = true;
  //播放状态
  bSoundFlag = false;
  nAnimeFrameNum = 0;
  nFrameTime = 0;
}

CBullet::~CBullet()
{
}

bool CBullet::move(int nDistance)
{
  if (isBoom == true)
  {
    return false;
  }

  bool ret = false;

  PrevPos = *this;

  switch (m_nDir)
  {
  case 0://DR_UP,
  {
    ret = toUp(nDistance);
    break;
  }
  case 1://DR_DOWN
  {
    ret = toDown(nDistance);
    break;
  }
  case 2://DR_LEFT
  {
    ret = toLeft(nDistance);
    break;
  }
  case 3:// DR_RIGHT
  {
    ret = toRight(nDistance);
    break;
  }
  }

  show();
  return ret;
}

void CBullet::onDie()
{
  if (bSoundFlag == false)
  {
    bSoundFlag = true;
    if (m_tank.getCamp() == CTank::CAMP_PLAYER)
    {
      //播放子弹消亡的声音
      g_Game->Sound.PlayBulletCrackSound();
    }
    
  }
  
  //纪录爆炸前数据
  //int nX = getX() - (T_SIZE - BULLET_SIZE) / 2;
  //int nY = getY() - (T_SIZE - BULLET_SIZE) / 2;
  //ui->GetRect(nX, nY, T_SIZE, T_SIZE);

  //动画标识
  isBoom = true;
}

void CBullet::onCrash(CLifeEntity entity)
{
}

void CBullet::show()
{
  if (isAlive && isBoom == false)
  {
    //清除上次子弹痕迹
    clearPrevPos();
    //画子弹
    ui->DrawBullet(getX(), getY(), m_nDir);
  }
  
  if (isBoom == true)
  {
    int nX = getX() - (T_SIZE - BULLET_SIZE) / 2;
    int nY = getY() - (T_SIZE - BULLET_SIZE) / 2;

    //
    //死亡动画
    ui->DrawBulletBoom(nX, nY, nAnimeFrameNum);

    //帧切换
    clock_t tFrame = clock();
    if (nFrameTime == 0 || tFrame - nFrameTime > 80)
    {
      nFrameTime = tFrame;
      //最大帧判断
      if (nAnimeFrameNum < ANIME_BULLET_BOOM_FRAME_NUM)
      {
        nAnimeFrameNum++;
      }
    }

    //动画播放完毕
    if (nAnimeFrameNum >= ANIME_BULLET_BOOM_FRAME_NUM)
    {
      //还原场景
      //ui->RestoreRect(nX, nY);
      ui->ClearRect(nX, nY, T_SIZE, T_SIZE);
      //画地图
      ui->DrawMap();
      //死亡动画是否播放
      isBoom = false;
      nAnimeFrameNum = 0;
      nFrameTime = 0;
      //子弹计数--
      m_tank.m_nCountBullet--;
      //置null
      m_tank.m_aryBulletBuf[m_nId] = nullptr;
      //存活状态
      isAlive = false;
      //删除自身
      delete this;
    }
    
  }
}

//清除上次位置
void CBullet::clearPrevPos()
{
  //当前位置跟上次位置相等就不清除
  if (PrevPos.getX() == getX() && PrevPos.getY() == getY())
  {
    return;
  }
  else
  {
    ui->ClearRect(PrevPos.getX(), PrevPos.getY(), BULLET_SIZE, BULLET_SIZE);
  }
}

//清除当前位置
void CBullet::clearCurPos()
{
  ui->ClearRect(getX(), getY(), BULLET_SIZE, BULLET_SIZE);
}

void CBullet::fly()
{
  //爆炸时停止飞行
  if (isBoom == true)
  {
    //显示动画
    show();
    return;
  }

  //假定坐标
  CPosition pos = *this;

  bool ret = false;

  switch (m_nDir)
  {
  case 0://DR_UP,
  {
    ret = pos.toUp(m_nSpeed);
    break;
  }
  case 1://DR_DOWN
  {
    ret = pos.toDown(m_nSpeed);
    break;
  }
  case 2://DR_LEFT
  {
    ret = pos.toLeft(m_nSpeed);
    break;
  }
  case 3:// DR_RIGHT
  {
    ret = pos.toRight(m_nSpeed);
    break;
  }
  }

  if (g_Game->CheckBulletCrash(*this))
  {
    //生命周期死亡
    onDie();
    return;
  }

  move(m_nSpeed);
}

int CBullet::getDirection()
{
  return m_nDir;
}

int CBullet::getSpeed()
{
  return m_nSpeed;
}

int CBullet::getPower()
{
  return m_nPower;
}

int CBullet::getId()
{
  return m_nId;
}

int CBullet::getType()
{
  return m_nType;
}
