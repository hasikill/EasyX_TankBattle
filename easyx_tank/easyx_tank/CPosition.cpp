#include "CPosition.h"

CPosition::CPosition()
{
  x = 0;
  y = 0;
}

CPosition::CPosition(int x, int y)
  : x(x), y(y)
{
}

CPosition::~CPosition()
{
}

bool CPosition::toLeft(int nStep = 1)
{
  int nX = x - nStep; //×ó
  if (nX < 0)
  {
    x = 0;
  }
  else
  {
    x = nX;
  }
  return true;
}

bool CPosition::toRight(int nStep = 1)
{
  x = x + nStep;
  return true;
}

bool CPosition::toDown(int nStep = 1)
{
  y = y + nStep; //ÏÂ
  return true;
}

void CPosition::setPos(int x, int y)
{
  setX(x);
  setY(y);
}

void CPosition::setX(int x)
{
  this->x = x;
}

int CPosition::getX()
{
  return x;
}

void CPosition::setY(int y)
{
  this->y = y;
}

int CPosition::getY()
{
  return y;
}

bool CPosition::toUp(int nStep = 1)
{
  int nY = y - nStep;
  if (nY < 0)
  {
    y = 0;
  }
  else
  {
    y = nY;
  }

  return true;
}