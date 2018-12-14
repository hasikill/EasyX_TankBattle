#pragma once
#include "CTank.h"

//敌人难度
#define ENEMY_LEVEL 10

/*
  机器人AI类 继承tank
*/
class CRobot : public CTank
{
public:
  CRobot(std::string m_strTankName, emTankType emType, CPosition pos, emTankCamp camp = emTankCamp::CAMP_ENEMY);
  ~CRobot();

  //被击中
  virtual bool onHitBy(int nDamage);

  //初始状态
  void create();

  //初始化数据
  void init();

  //复活
  void revive();

  //移动
  bool moveLeft();
  bool moveDown();
  bool moveUp();
  bool moveRight();

  //击杀敌人
  void onKillEnemy(CLifeEntity& life);

  //运动
  void motion();

  //设置停止时间
  void SetStopTime(int nTime);

  //死亡
  void toDie();

private:
  CPosition init_pos;
  unsigned int m_nStopTime;
  unsigned int startTime;
};

