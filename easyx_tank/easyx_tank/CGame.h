#pragma once
#include "CBarrier.h" //障碍物类
#include "CTank.h"
#include "CGameUI.h"
#include "CPlayer.h"
#include "CThread.h"
#include "CSound.h"
#include "CBuffer.h"
#include "CMapFile.h"

class CGame
{
public:
  //游戏模式
  enum emMode
  {
    MODE_SINGLE,
    MODE_DOUBLE
  };

  //障碍物容器
  struct tagBarrierContainer
  {
    CBarrier** container_barrier;
    int nLength;
  };

  //坦克容器
  struct tagTankContainer
  {
    CTank** container_tank;
    int nLength;
  };

public:
  //构造
  CGame(CPlayer &player1, CPlayer &player2);
  //析构
  ~CGame();
  
  //初始化数据
  bool Init();
  void InitData();
  void InitBarrier();
  void InitPlayer();
  void InitRobot();
  void InitBuffer();

  //读取地图关卡数据
  bool LoadMapData();

  //添加机器人
  void AddRobot();

  //设置游戏模式
  void SetGameMode(emMode emGameMode);

  //开始游戏
  void start();

  //游戏主循环
  void GameLoop();

  //玩家胜利
  void PlayerWin();

  //检测碰撞
  bool CheckTankCrash(CTank& refTank, CPosition pos);
  bool CheckBulletCrash(CBullet& bullet);
  bool isGameOver();
  void GameOver();
  bool isPlayerWin();
  void ReleaseData();
  void ShowGameOver();

  //运动所有Robot
  void MotionAllRobot();

  //刷新所有坦克
  void FlushAllTank();

  //刷新所有子弹
  void FlushAllBullet();

  //刷新buff显示
  void FlushAllBuff();

  //暂停所有机器人活动
  void StopAllRobot(int nTime);

  //随机添加buff
  void GenerateBuff();

  //杀死所有机器人
  void KillAllRobot();

  //基地围墙变铁
  void ToIronHome();

//全局游戏数据
public:
  //障碍物容器
  tagBarrierContainer BarArys; 
  //坦克容器
  tagTankContainer TankArys;
  //全局buffer容器
  CBuffer *BufferArys[6];
  //敌人出生点
  CPosition EnemyPosArys[3];
  //玩家1
  CPlayer& Player1;
  //玩家2
  CPlayer& Player2;

  //游戏ui
  CGameUI *GameUi;
  //线程类
  CThread Thread;
  //声音类
  CSound Sound;

  //游戏速度
  int nGameSpeed;
  //当前关卡
  int nLevelNum;
  //总关卡数
  int nTotolLevelNum;
  //坦克总数
  int nTankNum;
  //当前机器人数量
  int nCurRobotNum;
  //机器人死亡数量
  int nDieRobotNum;
  //游戏模式
  emMode emGameMode;
  //游戏是否结束
  bool bGameOverFlag;
  //玩家是否胜利
  bool bPlayerWinFlag;
  //基地坐标
  CPosition m_HomePos;
  //地图文件操作类
  CMapFile MapFile;
private:
  bool isInit;
};

