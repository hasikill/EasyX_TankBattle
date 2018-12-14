#pragma once
#include "CPosition.h"

/*
  生命体
*/
class CLifeEntity
{
public:
  enum emLifeType
  {
    LF_TANK,   //坦克
    LF_BARRIER //障碍物
  };

public:
  CLifeEntity(CPosition m_pos, emLifeType emType, int HP);

  ~CLifeEntity();

  bool SubHp(int nHP);

  //复活
  void toAlive();

  //死亡
  void toDie();

  //是否还活着
  bool isAlive();

  //被敌人击中
  virtual bool onHitBy(int nDamage);

  //显示
  virtual void show();

  //获取生命值
  int GetHP();
  void SetHP(int nHP);

  //设置类型
  void SetLifeType(emLifeType m_emType);
  emLifeType GetLifeType();

public:
  //坐标
  CPosition m_pos;
private:
  //生命值
  int m_nHP;
  //生命体类型
  emLifeType m_emType;
  //是否还活着
  bool m_bAliveFlag;
};

