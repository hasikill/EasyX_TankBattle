#pragma once
#include "CLifeEntity.h"
#include <string>
#include "CBullet.h"

//最大弹夹数
#define MAX_BULLET 5

class CTank : public CLifeEntity
{
public:
  enum emTankType
  {
    TANK1,
    TANK2,
    TANK3,
    TANK4,
    TANK5,
    TANK6,
    TANK7,
    TANK_COUNT = 7
  };

  enum emTankCamp
  {
    CAMP_PLAYER, //玩家
    CAMP_ENEMY   //敌人
  };

  enum emTankStatus
  {
    STATUS_NONE = 0,        //无状态
    STATUS_PLAYERINIT = 5,  //玩家初始化状态
    STATUS_ENEMYINIT,       //敌人初始化状态
    STATUS_PROTECT,         //坦克保护状态
    STATUS_DIE              //死亡状态
  };

  enum emTankDirection
  {
    DR_UP,
    DR_DOWN,
    DR_LEFT,
    DR_RIGHT
  };
public:
  CTank(std::string m_strTankName, emTankType emType, CPosition pos, emTankCamp camp = emTankCamp::CAMP_ENEMY);
  ~CTank();

  //初始化数据
  virtual void init();

  //移动
  bool move(emTankDirection emDir);

  //开火
  bool fire();

  //击中敌人事件
  virtual void onHitEnemy(CLifeEntity& life);

  //击杀敌人
  virtual void onKillEnemy(CLifeEntity& life);

  //被击中
  virtual bool onHitBy(int nDamage);

  //显示
  virtual void show();

  //清除上次图形
  void clearPrevPos();

  //清除当前图形
  void clearCurPos();

  //按键被按下

  //geter and seter

  //获取类型
  emTankType getType();

  //获取阵营
  emTankCamp getCamp();

  //获取方向
  emTankDirection getDirection();

  //获取移动速度
  int getMoveSpeed();
  
  //获取子弹速度
  int getBulletSpeed();

  //获取名字
  std::string getTankName();

  //设置名字
  void setTankName(const char *pszName);
  void setTankName(std::string strName);

  //设置状态
  void setTankStatus(emTankStatus status, int time);

  //获取状态时间
  int getStatusTime();

  void toUp();
  void toDown();
  void toRight();
  void toLeft();

  //死亡
  virtual void toDie();

  //复活
  virtual void revive();

  //创建状态
  virtual void create();

protected:
  //坦克名称
  std::string m_strTankName;
  //坦克类型
  emTankType m_emType;
  //坦克郑营
  emTankCamp m_emCamp;

  //方向
  emTankDirection m_emDir;
  //移动速度
  int m_nMoveSpeed;
  //子弹速度
  int m_nBulletSpeed;
  //伤害,火力
  int m_nPower;
  //坦克状态
  emTankStatus m_emTankStatus;
  //状态时长
  int m_nStatusTime;
  //当前弹夹
  int m_nMagazine;

public:
  //显示坐标
  CPosition PrevPos;
  //当前移动距离/
  int m_nMoveDis;
  //动画状态
  bool bAnimeFlag;
  //死亡动画状态
  bool bAnimeDieFlag;
  //移动状态
  bool bMoveFlag;
  //保护动画帧
  bool bFrameFlag;
  //帧时间
  unsigned int nFrameTime;

  //动画帧控制
  int nAnimeFrameNum;

  CBullet* m_aryBulletBuf[MAX_BULLET];//子弹
  
  int m_nCountBullet;//当前开火子弹数量
};
