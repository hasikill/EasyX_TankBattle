#pragma once
#include <graphics.h>
#include "CPosition.h"

#define T_SIZE        32
#define TANK_SIZE     30
#define BARRIER_SIZE  16
#define BULLET_SIZE   6

//坦克初始化动画帧数
#define ANIME_INIT_FRAME_NUM 7
//坦克死亡动画帧数
#define ANIME_DIE_FRAME_NUM 4
//子弹爆炸动画帧数
#define ANIME_BULLET_BOOM_FRAME_NUM 4

class CGameUI
{
public:
  enum emChoose
  {
    CHO_SINGLE,
    CHO_DOUBLE
  };
public:
  CGameUI(int nWidth, int nHeight);
  ~CGameUI();

  //加载图片数据
  bool LoadImgData();

  //加载坐标数据
  void LoadPosData();

  //绘制菜单
  void DrawMenu();
  
  //绘制坦克
  void DrawTank(int x, int y, int type, int nDir);

  //绘制基本元素， nType = 1 表示砖  2 铁 3 浅蓝方块 4 深蓝方块 5 草 
  void DrawElement(int x, int y, int nType);

  //绘制GameOver
  void DrawGameOver(int x, int y);

  //绘制老巢
  void DrawHomeBase(int x, int y);
  
  //绘制老巢死亡
  void DrawHomeBaseDie(int x, int y);

  //绘制子弹 nDir 4个方向 上下左右
  void DrawBullet(int x, int y, int nDir);

  //绘制子弹爆炸 1 2 3 三张图片
  void DrawBulletBoom(int x, int y, int nType);

  //画保护图片 nType 0第一帧 1第二帧
  void DrawProtect(int x, int y, int nType);
  
  //画保护图片 nType 总共7帧
  void DrawTankInit(int x, int y, int nFrame);

  //画保护图片 nType 总共7帧
  void DrawTankDie(int x, int y, int nFrame);

  //绘制地图
  void DrawMap();

  //绘制选择指针
  void DrawChoose(int x, int y, int nFrame);

  //绘制补给 0 - 5 总共6种
  void DrawBuffer(int x, int y, int nType);

  //播放选择动画
  void PlayChooseAnime();

  //刷新绘制
  void flush();

  //相当于sleep
  void Wait(int time);

  //清除矩形
  void ClearRect(int x, int y, int width, int height);

  //清除整个屏幕
  void Clear();

  //获取指定区域
  void GetRect(int x, int y, int width, int height);

  //还原到指定区域
  void RestoreRect(int x, int y);

  //获取战场宽高
  int getBattleWidth();
  int getBattleHeight();

  //菜单选择
  emChoose MenuChoose();

  //选择指针
  CPosition ChoosePos;

  int nFrameTime;
  bool nAnimeFrameNum;

public:
  //窗口宽高
  int m_nWidth;
  int m_nHeight;

private:
  //图片数据
  IMAGE ImgMenu;
  IMAGE ImgObject;
  IMAGE ImgProtect[2];

  //临时缓冲区
  IMAGE ImgTemp;

  //战场宽高
  int m_nBattleWidth;
  int m_nBattleHeight;

  //七种坦克,每种4个方向
  CPosition aryTankpos[7][4];

  bool isInit;
};

