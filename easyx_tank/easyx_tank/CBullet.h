#pragma once
#include "CPosition.h"
#include "CLifeEntity.h"
//声明
class CTank;

class CBullet : public CPosition
{
public:
  CBullet() = delete;

  CBullet(CTank& tank, int nId, CPosition pos, int nSpeed, int nDir, int nPower);
  
  ~CBullet();

  //移动
  bool move(int nDistance);

  //死亡
  void onDie();

  //碰撞到物体
  void onCrash(CLifeEntity entity);

  //显示
  void show();

  //子弹飞行
  void fly();

  void clearCurPos();
  void clearPrevPos();

  int getDirection();
  int getSpeed();
  int getPower();
  int getId();
  int getType();

private:
  //子弹Id
  int m_nId;
  //子弹速度
  int m_nSpeed;
  //移动方向
  int m_nDir;
  //伤害
  int m_nPower;
  //类型
  int m_nType;

  //是否爆炸
  bool isBoom;
  bool isAlive;
  bool bSoundFlag;

  int nAnimeFrameNum;
  int nFrameTime;

public:
  //上次坐标
  CPosition PrevPos;
  //归属者
  CTank& m_tank;
};