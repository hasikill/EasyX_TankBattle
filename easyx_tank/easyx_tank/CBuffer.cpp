#include "CBuffer.h"
#include "GameConst.h"

CBuffer::CBuffer(emBufferType type)
{
  setPos(0, 0);
  m_emBufferType = type;
  m_bShowFlag = false;
}

CBuffer::~CBuffer()
{

}

void CBuffer::show()
{
  if (m_bShowFlag)
  {
    ui->DrawBuffer(getX(), getY(), m_emBufferType);
  }
}

void CBuffer::clear()
{
  ui->ClearRect(getX(), getY(), 30, 28);
  ui->DrawMap();
}

void CBuffer::onTouch(CTank &tank)
{
  //播放声音
  g_Game->Sound.PlayPropSound();

  switch (m_emBufferType)
  {
  case CBuffer::TYPE_ADDLIFE: //添加生命数量
  {
    if (tank.getCamp() == CTank::CAMP_PLAYER)
    {
      //添加生命数
      CPlayer *player = (CPlayer *) &tank;

      //添加生命数值
      player->addLifeNum(1);
    }
  }
    break;
  case CBuffer::TYPE_STOPTIME://停止机器人
  {
    //暂停所有机器人活动10秒钟
    g_Game->StopAllRobot(TYPE_STOPROBOT_TIME);
  }
    break;
  case CBuffer::TYPE_IRONHOME://家变铁
  {
    //家变铁
    g_Game->ToIronHome();
  }
    break;
  case CBuffer::TYPE_BOMB:    //杀掉所有活着的机器人
  {
    //杀死所有机器人
    g_Game->KillAllRobot();
  }
    break;
  case CBuffer::TYPE_ADDBULLET://添加弹夹
  {
    if (tank.getCamp() == CTank::CAMP_PLAYER)
    {
      CPlayer *player = (CPlayer *)&tank;
      //添加弹夹
      player->addMagazine(1);
      //更改子弹速度
      player->setBulletSpeed(4);
    }
  }
    break;
  case CBuffer::TYPE_PROTECT: //保护罩
  {
    if (tank.getCamp() == CTank::CAMP_PLAYER)
    {
      //添加保护罩
      tank.setTankStatus(CTank::STATUS_PROTECT, TYPE_PROTECT_TIME);
    }
  }
    break;
  }

  //隐藏自身
  setVisible(false);
  //清除自己
  this->clear();
}

void CBuffer::setPos(int x, int y)
{
  __super::setPos(x, y);
}

void CBuffer::setVisible(bool bFlag)
{
  m_bShowFlag = bFlag;
}

bool CBuffer::isShow()
{
  return m_bShowFlag;
}
