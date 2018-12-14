#include "CGameUI.h"
#include <iostream>
#include <time.h>
#include <graphics.h>
#include "GameConst.h"
#pragma warning(disable:4996)

CGameUI::CGameUI(int nWidth, int nHeight)
  :m_nHeight(nHeight), m_nWidth(nWidth)
{
  m_nBattleWidth = BARRIER_SIZE * 26;
  m_nBattleHeight = BARRIER_SIZE * 26;
  //创建窗口
  initgraph(nWidth, nHeight, SHOWCONSOLE | NOCLOSE);
  //加载图片数据
  LoadImgData();
  //加载坐标数据
  LoadPosData();
}

CGameUI::~CGameUI()
{
  closegraph();
}

bool CGameUI::LoadImgData()
{
  loadimage(&ImgObject, IMG_OBJECT_PATH);
  loadimage(&ImgMenu, IMG_MENU_PATH);

  //屏幕交换
  putimage(0, 0, TANK_SIZE, TANK_SIZE, &ImgObject, T_SIZE * 5, T_SIZE * 3, SRCPAINT);
  putimage(0, TANK_SIZE, TANK_SIZE, TANK_SIZE, &ImgObject, T_SIZE * 5, T_SIZE * 4, SRCPAINT);
  //读取数据
  getimage(&ImgProtect[0], 0, 0, TANK_SIZE, TANK_SIZE);
  getimage(&ImgProtect[1], 0, TANK_SIZE, TANK_SIZE, TANK_SIZE);

  //清屏
  ClearRect(0, 0, T_SIZE, T_SIZE * 2);

  return true;
}

void CGameUI::LoadPosData()
{
  int x = 0;
  int y = 0;

  //第一种
  for (int i = 0; i < 4; i++)
  {
    x = TANK_SIZE * i;
    y = 0;
    aryTankpos[0][i].setX(x);
    aryTankpos[0][i].setY(y);
  }
  
  //第二种
  for (int i = 0; i < 4; i++)
  {
    x = TANK_SIZE * (i + 4);
    y = 0;
    aryTankpos[1][i].setX(x);
    aryTankpos[1][i].setY(y);
  }

  //第三种
  for (int i = 0; i < 4; i++)
  {
    x = TANK_SIZE * i;
    y = T_SIZE * 1;
    aryTankpos[2][i].setX(x);
    aryTankpos[2][i].setY(y);
  }

  //第四种
  for (int i = 0; i < 4; i++)
  {
    x = TANK_SIZE * (i + 4);
    y = T_SIZE * 1;
    aryTankpos[3][i].setX(x);
    aryTankpos[3][i].setY(y);
  }

  //第五种
  for (int i = 0; i < 4; i++)
  {
    x = TANK_SIZE * i;
    y = T_SIZE * 2;
    aryTankpos[4][i].setX(x);
    aryTankpos[4][i].setY(y);
  }

  //第六种
  for (int i = 0; i < 4; i++)
  {
    x = TANK_SIZE * (i + 4);
    y = T_SIZE * 2;
    aryTankpos[5][i].setX(x);
    aryTankpos[5][i].setY(y);
  }

  //第七种
  for (int i = 0; i < 4; i++)
  {
    x = TANK_SIZE * (i + 8);
    y = T_SIZE * 2;
    aryTankpos[6][i].setX(x);
    aryTankpos[6][i].setY(y);
  }

  isInit = true;
}

void CGameUI::DrawMenu()
{
  if (isInit == false) return;

  int x = (m_nWidth - ImgMenu.getwidth()) / 2;
  int y = (m_nHeight - ImgMenu.getheight()) / 2;

  //画菜单图片
  putimage(x, y, &ImgMenu);

  ChoosePos.setPos(x + 128, y + 250);

  nFrameTime = 0;
  nAnimeFrameNum = false;
}

void CGameUI::DrawTank(int x, int y, int type, int nDir)
{
  if (isInit == false) return;

  CPosition pos = aryTankpos[type][nDir];

  putimage(x, y, TANK_SIZE, TANK_SIZE, &ImgObject, pos.getX(), pos.getY());

}

void CGameUI::DrawElement(int x, int y, int nType)
{
  if (isInit == false) return;

  putimage(x, y, BARRIER_SIZE, BARRIER_SIZE, &ImgObject, BARRIER_SIZE * (nType - 1), T_SIZE * 3);
}

void CGameUI::DrawGameOver(int x, int y)
{
  putimage(x, y, T_SIZE * 2, T_SIZE, &ImgObject, T_SIZE * 12, T_SIZE * 2);
}

void CGameUI::DrawHomeBase(int x, int y)
{
  putimage(x, y, T_SIZE, T_SIZE, &ImgObject, T_SIZE * 8, 0);
}

void CGameUI::DrawHomeBaseDie(int x, int y)
{
  putimage(x, y, T_SIZE, T_SIZE, &ImgObject, T_SIZE * 9, 0);
}

void CGameUI::DrawBullet(int x, int y, int nDir)
{
  putimage(x, y, BULLET_SIZE, BULLET_SIZE, &ImgObject, (BARRIER_SIZE * 5) + (nDir * BULLET_SIZE), T_SIZE * 3);
}

void CGameUI::DrawBulletBoom(int x, int y, int nType)
{
  putimage(x, y, T_SIZE, T_SIZE, &ImgObject, T_SIZE * (10 + nType), 0, SRCPAINT);
}

void CGameUI::DrawProtect(int x, int y, int nType)
{
  putimage(x, y, &ImgProtect[nType], SRCPAINT);
}

void CGameUI::DrawTankInit(int x, int y, int nFrame)
{
  putimage(x, y, T_SIZE, T_SIZE, &ImgObject, T_SIZE * (8 + nFrame), T_SIZE * 1);
}

void CGameUI::DrawTankDie(int x, int y, int nFrame)
{
  putimage(x, y, T_SIZE * 2, T_SIZE * 2, &ImgObject, (T_SIZE * 2) * nFrame, T_SIZE * 5, SRCPAINT);
}

void CGameUI::DrawMap()
{

  //画障碍物
  int nLen = g_Game->BarArys.nLength;
  //障碍物容器
  CBarrier **pBars = g_Game->BarArys.container_barrier;
  
  for (int i = 0; i < nLen; i++)
  {
    if (pBars[i] != nullptr && pBars[i]->isAlive())
    {
      //坐标
      CPosition pos = pBars[i]->m_pos;
      //类型
      CBarrier::emBarrierType nType = pBars[i]->getType();
      if (nType == CBarrier::BAR_HOME)//基地
      {
        //画基地
        DrawHomeBase(pos.getX(), pos.getY());
      }
      else
      {
        //画元素
        DrawElement(pos.getX(), pos.getY(), nType);
      }
    }

  }

  //战场边框线
  line(m_nBattleWidth + 1, 0, m_nBattleWidth + 1, m_nBattleHeight);
  line(0, m_nBattleHeight, m_nBattleWidth + 1, m_nBattleHeight);
}

void CGameUI::DrawChoose(int x, int y, int nFrame)
{
  putimage(x, y, 27, 27, &ImgObject, T_SIZE * 4, (T_SIZE * 3) + (nFrame * 27));
}

void CGameUI::DrawBuffer(int x, int y, int nType)
{
  putimage(x, y, 30, 28, &ImgObject, (T_SIZE * 8) + (nType * 30), 110, SRCPAINT);
}

void CGameUI::PlayChooseAnime()
{
  DrawChoose(ChoosePos.getX(), ChoosePos.getY(), nAnimeFrameNum);
  //帧切换
  clock_t tFrame = clock();
  if (nFrameTime == 0 || tFrame - nFrameTime > 120)
  {
    nFrameTime = tFrame;
    nAnimeFrameNum = !nAnimeFrameNum;
  }
}

void CGameUI::flush()
{
  FlushBatchDraw();
}

void CGameUI::Wait(int time)
{
  clock_t start = clock();
  clock_t end = start;
  do
  {
    end = clock();
  } while (end - start < time);
}

void CGameUI::ClearRect(int x, int y, int width, int height)
{
  clearrectangle(x, y, x + width, y + height);
}

void CGameUI::Clear()
{
  ClearRect(0, 0, m_nWidth, m_nHeight);
}

void CGameUI::GetRect(int x, int y, int width, int height)
{
  getimage(&ImgTemp, x, y, width, height);
}

void CGameUI::RestoreRect(int x, int y)
{
  putimage(x, y, &ImgTemp);
}

int CGameUI::getBattleWidth()
{
  return m_nBattleWidth;
}

int CGameUI::getBattleHeight()
{
  return m_nBattleHeight;
}

CGameUI::emChoose CGameUI::MenuChoose()
{
  //默认单人
  emChoose choose = CHO_SINGLE;

  int count = 0;

  int n = 1;

  //循环选择
  while (1)
  {
    if (GetAsyncKeyState('W') & 0x8000)
    {
      if (count > 20 && n > 1)
      {
        n--;
        ClearRect(ChoosePos.getX(), ChoosePos.getY(), 27, 27);
        ChoosePos.toUp(30);
        count = 0;
      }
    }
    else if (GetAsyncKeyState('S') & 0x8000)
    {
      if (count > 20 && n < 2)
      {
        n++;
        ClearRect(ChoosePos.getX(), ChoosePos.getY(), 27, 27);
        ChoosePos.toDown(30);
        count = 0;
      }
    }

    if (GetAsyncKeyState(VK_RETURN) & 0x8000)
    {
        choose = (emChoose)(n - 1);
        break;
    }

    PlayChooseAnime();
    count++;
    Wait(10);
  }
  return choose;
}

