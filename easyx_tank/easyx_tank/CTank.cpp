#include "CTank.h"
#include "GameConst.h"
#include "CGameUI.h"
#include <iostream>
#include <string>
#include "CThread.h"
#include <time.h>

void CTank::init()
{
  //当前移动距离
  m_nMoveDis = 0;
  //子弹计数
  m_nCountBullet = 0;
  //动画状态
  bAnimeFlag = false;
  bMoveFlag = false;
  bFrameFlag = false;
  bAnimeDieFlag = false;
  nFrameTime = 0;
  nAnimeFrameNum = 0;
  ::memset(m_aryBulletBuf, 0, sizeof(m_aryBulletBuf));
  /*
  数据拷贝
  生命值,伤害,移动速度,子弹速度
  */
  SetHP(g_aryTankInfo[m_emType][0]); //生命值
  m_nPower = g_aryTankInfo[m_emType][1];//伤害
  m_nMoveSpeed = g_aryTankInfo[m_emType][2];//移动速度
  m_nBulletSpeed = g_aryTankInfo[m_emType][3];//子弹速度
  m_nMagazine = g_aryTankInfo[m_emType][4];; //默认弹夹数
}

/*
  坦克
*/
CTank::CTank(std::string strTankName,
  emTankType emType, 
  CPosition pos, 
  emTankCamp camp)
  : m_strTankName(strTankName), CLifeEntity(pos, CLifeEntity::LF_TANK, 0)//父类构造
{
  //类型
  m_emType = emType;
  //阵营
  m_emCamp = camp;
  //方向
  m_emDir = DR_UP;
  //显示位置
  PrevPos = pos;

  //初始化数据
  init();
  
}

CTank::~CTank()
{
  for (int i = 0; i < 5; i++)
  {
    if (m_aryBulletBuf[i] != nullptr)
    {
      delete m_aryBulletBuf[i];
      m_aryBulletBuf[i] = nullptr;
    }
  }
}

bool CTank::move(emTankDirection emDir)
{
  if (isAlive() == false)
  {
    return false;
  }

  if (m_emTankStatus == STATUS_ENEMYINIT || m_emTankStatus == STATUS_PLAYERINIT || m_emTankStatus == STATUS_DIE)
  {
    return false;
  }

  //声音
  /*g_Game->Sound.PlayMoveSound();*/

  //移动状态
  bMoveFlag = true;

  //速度
  m_nMoveDis = m_nMoveSpeed;
  //方向
  m_emDir = emDir;
  //保存上次位置
  PrevPos = m_pos;

  switch (emDir)
  {
  case CTank::DR_UP:
  {
    m_pos.toUp(m_nMoveDis);
  }
    break;
  case CTank::DR_RIGHT:
  {
    m_pos.toRight(m_nMoveDis);
  }
    break;
  case CTank::DR_DOWN:
  {
    m_pos.toDown(m_nMoveDis);
  }
    break;
  case CTank::DR_LEFT:
  {
    m_pos.toLeft(m_nMoveDis);
  }
    break;
  }

  //显示
  show();
  return false;
}

bool CTank::fire()
{
  if (isAlive() == false)
  {
    return false;
  }

  //判断弹夹是否已满
  if (m_nCountBullet < m_nMagazine && m_nCountBullet < MAX_BULLET)
  {
    for (int i = 0; i < 5; i++)
    {
      if (m_aryBulletBuf[i] == nullptr)
      {
        CPosition pos = m_pos;
        //计算初始坐标
        switch (m_emDir)
        {
        case CTank::DR_UP:
          pos.toRight((TANK_SIZE - BULLET_SIZE) / 2);
          break;
        case CTank::DR_RIGHT:
          pos.toRight(TANK_SIZE);
          pos.toDown((TANK_SIZE - BULLET_SIZE) / 2);
          break;
        case CTank::DR_DOWN:
          pos.toDown(TANK_SIZE);
          pos.toRight((TANK_SIZE - BULLET_SIZE) / 2);
          break;
        case CTank::DR_LEFT:
          pos.toDown((TANK_SIZE - BULLET_SIZE) / 2);
          break;
        }
        //玩家播放声音
        if (m_emCamp == CAMP_PLAYER)
        {
          //播放声音
          g_Game->Sound.PlayFireSound();
        }
        //创建子弹
        m_aryBulletBuf[i] = new CBullet(*this, i, pos, m_nBulletSpeed, m_emDir, m_nPower);
        //计数++
        m_nCountBullet++;
        //跳出
        break;
      }

    }
  }

  return false;
}

void CTank::onHitEnemy(CLifeEntity& life)
{
  if (isAlive() == false)
  {
    return;
  }
}

void CTank::onKillEnemy(CLifeEntity & life)
{
  if (isAlive() == false)
  {
    return ;
  }
}

bool CTank::onHitBy(int nDamage)
{
  if (isAlive() == false)
  {
    return false;
  }

  return false;
}

void CTank::show()
{
  //如果死亡且已播完动画就不在显示
  if (isAlive() == false && bAnimeDieFlag)
  {
    return;
  }

  if (bMoveFlag)
  {
    //先清除上次
    clearPrevPos();
  }

  if (m_emTankStatus == STATUS_NONE)
  {
    //画坦克
    ui->DrawTank(m_pos.getX(), m_pos.getY(), m_emType, m_emDir);
  }
  else if (m_emTankStatus == STATUS_ENEMYINIT || m_emTankStatus == STATUS_PLAYERINIT)
  {
    //初始化动画
    ui->DrawTankInit(m_pos.getX(), m_pos.getY(), nAnimeFrameNum);

    //帧切换
    clock_t tFrame = clock();
    if (nFrameTime == 0 || tFrame - nFrameTime > 80)
    {
      nFrameTime = tFrame;
      //最大帧判断
      if (nAnimeFrameNum < ANIME_INIT_FRAME_NUM)
      {
        nAnimeFrameNum++;
      }
    }

    //动画播放完毕
    if (nAnimeFrameNum >= ANIME_INIT_FRAME_NUM)
    {
      //玩家切换到保护模式
      if (m_emTankStatus == STATUS_PLAYERINIT)
      {
        setTankStatus(CTank::STATUS_PROTECT, 3000);
      }
      else
      {
        setTankStatus(CTank::STATUS_NONE, 0);
      }
      nAnimeFrameNum = 0;
      nFrameTime = 0;
      bFrameFlag = false;
    }

  }
  else if (m_emTankStatus == STATUS_DIE)
  {
    int nX = m_pos.getX() - TANK_SIZE / 2;
    int nY = m_pos.getY() - TANK_SIZE / 2;

    //死亡动画
    ui->DrawTankDie(nX, nY, nAnimeFrameNum);

    //帧切换
    clock_t tFrame = clock();
    if (nFrameTime == 0 || tFrame - nFrameTime > 120)
    {
      nFrameTime = tFrame;
      //最大帧判断
      if (nAnimeFrameNum < ANIME_DIE_FRAME_NUM)
      {
        nAnimeFrameNum++;
      }
    }

    //动画播放完毕
    if (nAnimeFrameNum >= ANIME_DIE_FRAME_NUM)
    {
      //清除尸体
      ui->ClearRect(nX, nY, T_SIZE * 2, T_SIZE * 2);
      //恢复地图
      ui->DrawMap();
      //死亡动画是否播放
      bAnimeDieFlag = true;
      nAnimeFrameNum = 0;
      nFrameTime = 0;
      bFrameFlag = false;
    }
  }
  else if (m_emTankStatus == STATUS_PROTECT)//保护模式
  {
    if (bAnimeFlag == false)
    {
      CThread thread = CThread();
      thread.startTankProtectAnime(this);
    }

    if (bMoveFlag == true)
    {
      clock_t tFrame = clock();

      if (nFrameTime == 0 || tFrame - nFrameTime > 120)
      {
        nFrameTime = tFrame;
        bFrameFlag = !bFrameFlag;
      }

      //画坦克
      ui->DrawTank(m_pos.getX(), m_pos.getY(), m_emType, m_emDir);
      //画保护圈
      ui->DrawProtect(m_pos.getX(), m_pos.getY(), bFrameFlag);
    }
  }
}

//清除上次位置
void CTank::clearPrevPos()
{
  //当前位置跟上次位置相等就不清除
  if (PrevPos.getX() == m_pos.getX() && PrevPos.getY() == m_pos.getY())
  {
    return;
  }
  else
  {
    ui->ClearRect(PrevPos.getX(), PrevPos.getY(), TANK_SIZE, TANK_SIZE);
  }
}

//清除当前位置
void CTank::clearCurPos()
{
    ui->ClearRect(m_pos.getX(), m_pos.getY(), TANK_SIZE, TANK_SIZE);
}

CTank::emTankType CTank::getType()
{
  return m_emType;
}

CTank::emTankCamp CTank::getCamp()
{
  return m_emCamp;
}

CTank::emTankDirection CTank::getDirection()
{
  return m_emDir;
}

int CTank::getMoveSpeed()
{
  return m_nMoveSpeed;
}

int CTank::getBulletSpeed()
{
  return m_nBulletSpeed;
}

std::string CTank::getTankName()
{
  return m_strTankName;
}

void CTank::setTankName(const char * pszName)
{
  m_strTankName = pszName;
}

void CTank::setTankName(std::string strName)
{
  m_strTankName = strName;
}

void CTank::setTankStatus(emTankStatus status, int time)
{
  m_emTankStatus = status;
  m_nStatusTime = time;
}

int CTank::getStatusTime()
{
  return m_nStatusTime;
}

void CTank::toUp()
{
  m_emDir = DR_UP;
}

void CTank::toDown()
{
  m_emDir = DR_DOWN;
}

void CTank::toRight()
{
  m_emDir = DR_RIGHT;
}

void CTank::toLeft()
{
  m_emDir = DR_LEFT;
}

void CTank::toDie()
{
  __super::toDie();
  setTankStatus(CTank::STATUS_DIE, 0);
}

void CTank::revive()
{
  //死亡状态
  toAlive();
  //数据初始化
  init();
}

void CTank::create()
{
}
