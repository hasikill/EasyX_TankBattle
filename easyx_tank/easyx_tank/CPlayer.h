#pragma once
#include "CTank.h"

class CPlayer : public CTank
{
public:
  CPlayer(const char *name, CPosition pos, int nLifeNum);
  ~CPlayer();

  //初始化
  void init();

  //增加积分
  void addScore(int nScore);

  //增加杀敌数
  void addKillNum(int nKillNum);

  //获取积分
  int getScore();

  //获取杀敌数
  int getKillNum();

  //方向事件
  void onDown();
  void onUp();
  void onRight();
  void onLeft();
  void onFire();

  //被击中
  bool onHitBy(int nDamage);

  //击杀敌人
  void onKillEnemy(CLifeEntity& life);

  //复活
  void revive();

  //添加玩家生命数
  void addLifeNum(int num);

  //添加
  void addMagazine(int num);

  //设置子弹速度
  void setBulletSpeed(int speed);

private:
  //积分
  int m_nScore;
  //杀敌数
  int m_nKillNum;
  //生命数量
  int m_nLifeNum;
  //初始坐标
  CPosition init_pos;
  //初始生命值
  int init_lifenum;
};

