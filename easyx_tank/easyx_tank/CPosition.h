#pragma once
class CPosition
{
public:
  CPosition();
  CPosition(int x,int y);
  ~CPosition();

  //左
  bool toLeft(int nStep);
  //右
  bool toRight(int nStep);
  //上
  bool toUp(int nStep);
  //下
  bool toDown(int nStep);

  //设置光标
  void setPos(int x, int y);

  //设置X
  void setX(int x);

  //获取X
  int getX();
  
  //设置Y
  void setY(int y);

  //获取X
  int getY();

private:
  int x;
  int y;
};

