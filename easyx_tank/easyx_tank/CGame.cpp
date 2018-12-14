#include "CGame.h"
#include "GameConst.h"
#include <iostream>
#include "CRobot.h"
#include <string>
#include <time.h>
#pragma warning(disable:4996)

CGame::CGame(CPlayer & player1, CPlayer & player2) : Player1(player1), Player2(player2)
{
  //初始化buff
  InitBuffer();
  TankArys.container_tank = nullptr;
  BarArys.container_barrier = nullptr;
  //当前关卡
  nLevelNum = 2;
  //关卡总数
  if (MapFile.isInit())
  {
    nTotolLevelNum = MapFile.getMapNum();
    int nSpeed = MapFile.getGameSpeed();
    if (nSpeed == 0)
    {
      nSpeed = 5;
    }
    nGameSpeed = nSpeed;
  }
  srand((unsigned int)time(NULL));
}

CGame::~CGame()
{
  //障碍物容器
  if (BarArys.container_barrier != nullptr)
  {
    delete[] BarArys.container_barrier;
  }
  //坦克容器
  if (BarArys.container_barrier != nullptr)
  {
    delete[] TankArys.container_tank;
  }
  //Buffer
  for (int i = 0; i < 6; i++)
  {
    if (BufferArys[i] != nullptr)
    {
      delete BufferArys[i];
    }
  }
  //释放
  if (GameUi != nullptr)
  {
    delete GameUi;
  }
}

bool CGame::Init()
{
  nDieRobotNum = 0;
  isInit = false;
  bGameOverFlag = false;
  bPlayerWinFlag = false;
  
  //地图读取类
  if (MapFile.isInit() == false)
  {
    printf(">>> 读取地图文件失败...\r\n");
    return false;
  }
  return true;
}

void CGame::InitData()
{
  //初始化障碍物
  InitBarrier();
  //初始化玩家
  InitPlayer();
  //初始化机器人
  InitRobot();
  //初始化完成
  isInit = true;
  bGameOverFlag = false;
}

bool CGame::isGameOver()
{
  return bGameOverFlag;
}

void CGame::GameOver()
{
  bGameOverFlag = true;
  std::cout << "GameOver!" << std::endl;
}

bool CGame::isPlayerWin()
{
  return bPlayerWinFlag;
}

void CGame::ReleaseData()
{
  //机器人数据
  for (int i = 0; i < 5; i++)
  {
    //机器人
    CRobot *robot = (CRobot *)TankArys.container_tank[2 + i];
    if (robot != nullptr)
    {
      delete robot;
      TankArys.container_tank[2 + i] = nullptr;
    }
  }

  if (emGameMode == MODE_SINGLE)
  {
    Player1.toDie();
  }
  else if (emGameMode == MODE_DOUBLE)
  {
    Player1.toDie();
    Player2.toDie();
  }
}

void CGame::ShowGameOver()
{
  int x = (ui->getBattleWidth() - T_SIZE * 2) / 2;
  int y = (ui->getBattleHeight() - T_SIZE) / 2;
  ui->DrawGameOver(x, y);
}

void CGame::MotionAllRobot()
{
  if (isGameOver()) return;

  for (int i = 0; i < 5; i++)
  {
    //机器人
    CRobot *robot = (CRobot *)TankArys.container_tank[2 + i];

    //机器人存活
    if (robot->isAlive())
    {
      //调用机器人的运动函数
      robot->motion();
    }
  }
}

/*
  刷新所有坦克
*/
void CGame::FlushAllTank()
{
  //游戏结束不显示
  if (isGameOver()) return;

  int nTankCount = TankArys.nLength;
  //坦克
  CTank **ppTank = TankArys.container_tank;
  //遍历坦克
  for (int i = 0; i < nTankCount; i++)
  {
    //坦克
    CTank *tank = ppTank[i];
    if (tank == nullptr) continue;
    tank->show();
  }
}

void CGame::FlushAllBullet()
{
  //游戏结束不显示
  if (isGameOver()) return;
  //坦克数量
  int nTankCount = TankArys.nLength;
  //坦克
  CTank **ppTank = TankArys.container_tank;
  //遍历坦克
  for (int i = 0; i < nTankCount; i++)
  {
    //坦克
    CTank *tank = ppTank[i];
    if (tank == nullptr) continue;
    //飞行所有子弹
    for (int i = 0; i < 5; i++)
    {
      CBullet *bul = tank->m_aryBulletBuf[i];
      if (bul != nullptr)
      {
        bul->fly();
      }
    }
  }
  
}

void CGame::FlushAllBuff()
{
  for (int i = 0; i < 6; i++)
  {
    CBuffer* buff = BufferArys[i];
    if (buff != nullptr && buff->isShow())
    {
      //显示
      buff->show();
    }
  }
}

void CGame::StopAllRobot(int nTime)
{
  for (int i = 0; i < 5; i++)
  {
    //机器人
    CRobot *robot = (CRobot *)TankArys.container_tank[2 + i];
    //存活判断
    if (robot->isAlive())
    {
      //暂停机器人
      robot->SetStopTime(nTime);
    }
    
  }
}

void CGame::GenerateBuff()
{
  //全部关闭
  for (int i = 0; i < 6; i++)
  {
    CBuffer* buff = BufferArys[i];
    if (buff != nullptr)
    {
      if (buff->isShow())
      {
        //清除显示
        buff->clear();
        //不可显示
        buff->setVisible(false);
      }
    }
  }

  int x = rand() % (ui->getBattleWidth() - TANK_SIZE);
  int y = rand() % (ui->getBattleHeight() - TANK_SIZE);
  int option = rand() % 6;
  BufferArys[option]->setPos(x, y);
  BufferArys[option]->setVisible(true);
  //printf(">>> 天降buff [X = %d,Y = %d]\r\n", x, y);
}

void CGame::KillAllRobot()
{
  //播放音效
  g_Game->Sound.PlayTankCrackSound();

  for (int i = 0; i < 5; i++)
  {
    //机器人
    CRobot *robot = (CRobot *)TankArys.container_tank[2 + i];
    //存活判断
    if (robot->isAlive())
    {
      //死亡
      robot->toDie();
    }
  }
}

void CGame::ToIronHome()
{
  //障碍物
  CBarrier **pBar = BarArys.container_barrier;
  int nCount = BarArys.nLength;

  int hX = m_HomePos.getX();
  int hY = m_HomePos.getY();

  //遍历
  for (int i = 0; i < nCount; i++)
  {
    if (pBar[i] != nullptr)
    {
      //基地跳过
      if (pBar[i]->getType() == CBarrier::BAR_HOME) continue;

      //坐标
      CPosition barPos = pBar[i]->m_pos;

      //基地旁边的围墙
      if (barPos.getX() >= (hX - TANK_SIZE) &&
        barPos.getX() <= (hX + TANK_SIZE * 2) &&
        barPos.getY() >= (hY - TANK_SIZE) &&
        barPos.getY() <= (hY + TANK_SIZE * 2))
      {
        pBar[i]->SetHP(99);
        pBar[i]->setType(CBarrier::BAR_IRON);
        pBar[i]->toAlive();
      }
    }
  }

  //画地图
  ui->DrawMap();
}

void CGame::InitBarrier()
{
  //敌人出生坐标计数
  int nEmPosCount = 0;
  //障碍物数量
  int nBarrierCount = 0;
  //xy坐标
  int x = 0;
  int y = 0;

  for (int i = 0; i < 26; i++)
  {
    for (int j = 0; j < 26; j++)
    {
      //获取类型
      int nType = g_CurMapData[i][j];

      //敌人出生点
      if (nType == 'E')
      {
        if (nEmPosCount < 3)
        {
          x = j * BARRIER_SIZE;
          y = i * BARRIER_SIZE;
          EnemyPosArys[nEmPosCount++].setPos(x, y);
        }
      }
      else if (nType != 0)
      {
        nBarrierCount++;
      }
    }
  }

  //分配空间
  if (BarArys.container_barrier == nullptr)
  {
    BarArys.container_barrier = new CBarrier *[nBarrierCount] { 0 };
  }
  else
  {
    CBarrier **pBar = BarArys.container_barrier;
    int nCount = BarArys.nLength;

    for (int i = 0; i < nCount; i++)
    {
      if (pBar[i] != nullptr)
      {
        delete pBar[i];
      }
    }
    delete[] BarArys.container_barrier;
    BarArys.container_barrier = new CBarrier *[nBarrierCount] { 0 };
  }
  BarArys.nLength = nBarrierCount;

  nBarrierCount = 0;
  CBarrier **pBar = BarArys.container_barrier;

  //数据读取
  for (int i = 0; i < 26; i++)
  {
    for (int j = 0; j < 26; j++)
    {
      //获取类型
      int nType = g_CurMapData[i][j];
      //XY 边缘空地空间 + 1
      x = j * BARRIER_SIZE;
      y = i * BARRIER_SIZE;

      switch (nType)
      {
      case 1:
      {
        //添加墙
        pBar[nBarrierCount++] = new CBarrier(CBarrier::BAR_WALL, { x, y }, WALL_LIFE);
        break;
      }
      case 2:
      {
        //添加铁
        pBar[nBarrierCount++] = new CBarrier(CBarrier::BAR_IRON, { x, y }, 999);
        break;
      }
      case 3:
      {
        //添加布
        pBar[nBarrierCount++] = new CBarrier(CBarrier::BAR_CLOTH, { x, y }, 2);
        break;
      }
      case 4:
      {
        //添加水
        pBar[nBarrierCount++] = new CBarrier(CBarrier::BAR_WATER, { x, y }, 2);
        break;
      }
      case 5:
      {
        //添加草
        pBar[nBarrierCount++] = new CBarrier(CBarrier::BAR_GRASS, { x, y }, 2);
        break;
      }
      case 6:
      {
        //添加基地
        pBar[nBarrierCount++] = new CBarrier(CBarrier::BAR_HOME, { x, y }, 1);
        m_HomePos.setPos(x, y);
        break;
      }
      }//switch

    }//forj
  }//fori
}

void CGame::InitPlayer()
{
  if (emGameMode == MODE_SINGLE)
  {
    //初始化数据
    Player1.init();

    //坦克数量
    int nLength = 7;
    //空间
    if (TankArys.container_tank == nullptr)
    {
      TankArys.container_tank = new CTank *[nLength] { 0 };
    }
    //第一项是Player1的坦克
    TankArys.container_tank[0] = &Player1;

    TankArys.nLength = 1;
    nTankNum = nLength;
  }
  else if(emGameMode == MODE_DOUBLE)
  {
    //初始化数据
    Player1.init();
    Player2.init();

    //坦克数量
    int nLength = 7;
    //空间
    if (TankArys.container_tank == nullptr)
    {
      TankArys.container_tank = new CTank *[nLength] { 0 };
    }
    //第一项是Player1的坦克
    TankArys.container_tank[0] = &Player1;
    //第二项是Player2的坦克
    TankArys.container_tank[1] = &Player2;

    TankArys.nLength = 2;
    nTankNum = nLength;
  }

  nCurRobotNum = 0;
}

/*
  初始五个电脑人,初始化时置为死亡状态
  在游戏过程中,每一个时钟周期让机器人复活即可
*/
void CGame::InitRobot()
{
  //初始化名字
  std::string str = "Robot";
  //第一个
  (TankArys.container_tank[2] = new CRobot(str, CTank::TANK3, EnemyPosArys[0], CTank::CAMP_ENEMY))->create();
  //第二个
  (TankArys.container_tank[3] = new CRobot(str, CTank::TANK4, EnemyPosArys[1], CTank::CAMP_ENEMY))->create();
  //第三个
  (TankArys.container_tank[4] = new CRobot(str, CTank::TANK5, EnemyPosArys[2], CTank::CAMP_ENEMY))->create();
  //第四个
  (TankArys.container_tank[5] = new CRobot(str, CTank::TANK6, EnemyPosArys[0], CTank::CAMP_ENEMY))->create();
  //第五个
  (TankArys.container_tank[6] = new CRobot(str, CTank::TANK7, EnemyPosArys[1], CTank::CAMP_ENEMY))->create();
  //两个玩家加五个初始Robot
  TankArys.nLength = 7;
}

void CGame::InitBuffer()
{
  //添加buff
  for (int i = 0; i < 6; i++)
  {
    //添加所有buff
    BufferArys[i] = new CBuffer((CBuffer::emBufferType)i);
  }
}

bool CGame::LoadMapData()
{
  //读取地图数据
  return MapFile.getMap(nLevelNum, g_CurMapData);
}

/*
  添加机器人
*/
void CGame::AddRobot()
{
  if (isGameOver()) return;

  //机器人复活次数不能超过限定次数
  if (nCurRobotNum < ROBOT_NUMBER)
  {
    for (int i = 0; i < 5; i++)
    {
      //机器人
      CRobot *robot = (CRobot *)TankArys.container_tank[2 + i];

      //判断位置是否可以复活
      if (g_Game->CheckTankCrash(*robot, robot->m_pos))
      {
        //不可以就下一个
        continue;
      }

      //如果死亡,就复活
      if (robot->isAlive() == false)
      {
        char szBuf[50] = { 0 };
        //拼接新名字
        std::string strName = "Robot";
        //拼接
        strName = strName + ::itoa(nCurRobotNum + 1, szBuf, 10);
        //赋予新名字
        robot->setTankName(strName);
        //复活机器人
        robot->revive();
        //当前机器人数量+1
        nCurRobotNum++;
        //通知
        printf("[ %s ] 到达了战场!\r\n", strName.c_str());
        break;
      }

    }
      
  }

}

void CGame::PlayerWin()
{
  //升级关卡
  int level = nLevelNum + 1;
  if (level <= nTotolLevelNum)
  {
    nLevelNum = level;
  }

  bPlayerWinFlag = true;
  MessageBox(NULL, _T("You Win!"), _T("Game"), MB_OK);
}

void CGame::SetGameMode(emMode GameMode)
{
  emGameMode = GameMode;
}

/*
  开始
*/
void CGame::start()
{
  //播放音乐
  Sound.PlayStartSound();
  //进入游戏主循环
  GameLoop();
}

//矩形碰撞检测
bool checkRectCrash(int x, int y, int w, int h, 
  int x2, int y2, int w2, int h2)
{
  if (x < x2 + w2 &&
    x + w >= x2 &&
    y < y2 + h2 &&
    h + y >= y2
    )
  {
    return true;
  }
  return false;
}

/*
  坦克碰撞检测
*/
bool CGame::CheckTankCrash(CTank& refTank, CPosition pos)
{
  //边缘碰撞检测
  if ((pos.getX() + TANK_SIZE) >= ui->getBattleWidth() || (pos.getY() + TANK_SIZE) >= ui->getBattleHeight())
  {
    return true;
  }

  //buff校验
  if (refTank.getCamp() == CTank::CAMP_PLAYER)
  {
    for (int i = 0; i < 6; i++)
    {
      CBuffer *buff = BufferArys[i];
      if (buff != nullptr && buff->isShow())
      {
        //捡到buff
        if (checkRectCrash(pos.getX(), pos.getY(), TANK_SIZE, TANK_SIZE, buff->getX(), buff->getY(), 30, 28))
        {
          //添加buff
          buff->onTouch(refTank);
        }
      }
    }
  }

  //障碍物碰撞检测
  CBarrier **pBar = BarArys.container_barrier;
  int nCount = BarArys.nLength;

  for (int i = 0; i < nCount; i++)
  {
    if (pBar[i] != nullptr && pBar[i]->isAlive())
    {
      //获取障碍物类型
      CBarrier::emBarrierType emType = pBar[i]->getType();

      //除掉草和布
      if (emType != CBarrier::BAR_GRASS && emType != CBarrier::BAR_CLOTH)
      {
        CPosition barPos = pBar[i]->m_pos;

        //size
        int nBarW = BARRIER_SIZE;
        int nBarH = BARRIER_SIZE;

        //大小判断
        if (emType == CBarrier::BAR_HOME)
        {
          nBarW = BARRIER_SIZE * 2;
          nBarH = BARRIER_SIZE * 2;
        }

        //矩形碰撞检测
        if (checkRectCrash(pos.getX(), pos.getY(), TANK_SIZE, TANK_SIZE, barPos.getX(), barPos.getY(), nBarW, nBarH))
        {
          return true;
        }
      }
    }

  }

  //坦克碰撞检测
  CTank **ppTank = TankArys.container_tank;
  nCount = TankArys.nLength;

  for (int i = 0; i < nCount; i++)
  {
    //坦克
    CTank *tank = ppTank[i];
    if (tank == nullptr) continue;
    if (tank->isAlive() == false) continue;

    CPosition tankPos = tank->m_pos;

    //获取比较坦克名称
    std::string curName = tank->getTankName();

    //排除自己
    if (curName.compare(refTank.getTankName()) != 0)
    {
      //坦克位置检测
      if (checkRectCrash(pos.getX(), pos.getY(), TANK_SIZE, TANK_SIZE, tankPos.getX(), tankPos.getY(), TANK_SIZE, TANK_SIZE))
      {
        //printf("[ %s ] : 可恶!该死的挡我的路,我要杀了 [ %s ]!\r\n", refTank.getTankName().c_str(), curName.c_str());
        return true;
      }
    }
  }

  return false;
}

/*
  子弹碰撞
*/
bool CGame::CheckBulletCrash(CBullet& bullet)
{
  //边缘碰撞检测
  if (bullet.getX() == 0 || bullet.getY() == 0 || (bullet.getX() + BULLET_SIZE) >= ui->getBattleWidth() || (bullet.getY() + BULLET_SIZE) >= ui->getBattleHeight())
  {
    return true;
  }
  
  bool ret = false;

  //障碍物碰撞检测
  CBarrier **pBar = BarArys.container_barrier;
  int nCount = BarArys.nLength;

  for (int i = 0; i < nCount; i++)
  {
    if (pBar[i] == nullptr) continue;
    if (pBar[i]->isAlive() == false) continue;

    //获取障碍物类型
    CBarrier::emBarrierType emType = pBar[i]->getType();

    //除掉草和布
    if (emType != CBarrier::BAR_GRASS && emType != CBarrier::BAR_CLOTH && emType != CBarrier::BAR_WATER)
    {
      CPosition barPos = pBar[i]->m_pos;

      int nBarW = BARRIER_SIZE;
      int nBarH = BARRIER_SIZE;

      //基地
      if (emType == CBarrier::BAR_HOME)
      {
        nBarW = BARRIER_SIZE * 2;
        nBarH = BARRIER_SIZE * 2;

        //矩形碰撞检测
        if (checkRectCrash(bullet.getX(), bullet.getY(), BULLET_SIZE, BULLET_SIZE, barPos.getX(), barPos.getY(), nBarW, nBarH))
        {
          //告知坦克击中敌人
          bullet.m_tank.onHitEnemy(*pBar[i]);
          //调用被击中回调函数
          pBar[i]->onHitBy(bullet.getPower());
          //返回
          return true;
        }
      }
      else
      {
        //矩形碰撞检测
        if (checkRectCrash(bullet.getX(), bullet.getY(), BULLET_SIZE, BULLET_SIZE, barPos.getX(), barPos.getY(), nBarW, nBarH))
        {
          //告知坦克击中敌人
          bullet.m_tank.onHitEnemy(*pBar[i]);
          //调用被击中回调函数
          if (pBar[i]->onHitBy(bullet.getPower()) != false)
          {
            //告知击杀
            bullet.m_tank.onKillEnemy(*pBar[i]);
          }
          //子弹回调
          bullet.onCrash(*pBar[i]);
          //状态
          ret = true;
        }
      }
      
    }

  }

  //坦克碰撞检测
  CTank **ppTank = TankArys.container_tank;
  nCount = TankArys.nLength;

  for (int i = 0; i < nCount; i++)
  {
    //坦克
    CTank *tank = ppTank[i];
    if (tank == nullptr) continue;
    if (tank->isAlive() == false) continue;

    CPosition tankPos = tank->m_pos;

    //坦克阵营
    CTank::emTankCamp tkCamp = bullet.m_tank.getCamp();
    CTank::emTankCamp tCamp = tank->getCamp();

    if (tkCamp != tCamp)//阵营不同则检测
    {
      //坦克位置检测
      if (checkRectCrash(bullet.getX(), bullet.getY(), BULLET_SIZE, BULLET_SIZE, tankPos.getX(), tankPos.getY(), TANK_SIZE, TANK_SIZE))
      {
        //告知坦克击中敌人
        bullet.m_tank.onHitEnemy(*tank);
        //调用被击中回调函数
        if (tank->onHitBy(bullet.getPower()) != false)
        {
          //告知击杀
          bullet.m_tank.onKillEnemy(*tank);
        }
        //子弹回调
        bullet.onCrash(*tank);
        //状态
        ret = true;
      }

      //子弹碰撞检测
      for (int j = 0; j < 5; j++)
      {
        CBullet *bul = tank->m_aryBulletBuf[j];
        if (bul != nullptr)
        {
          //坦克位置检测
          if (checkRectCrash(bullet.getX(), bullet.getY(), BULLET_SIZE, BULLET_SIZE, bul->getX(), bul->getY(), BULLET_SIZE, BULLET_SIZE))
          {
            //状态
            ret = true;
          }
        }
      }

    }

  }

  return ret;
}