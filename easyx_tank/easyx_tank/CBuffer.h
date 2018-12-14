#pragma once
#include "CPosition.h"
#include "CTank.h"

#define TYPE_PROTECT_TIME 10000 //10秒保护时间
#define TYPE_STOPROBOT_TIME 10000 //10秒暂停时间

class CBuffer : public CPosition
{
public:
  enum emBufferType
  {
    TYPE_ADDLIFE,
    TYPE_STOPTIME,
    TYPE_IRONHOME,
    TYPE_BOMB,
    TYPE_ADDBULLET,
    TYPE_PROTECT
  };

public:
  //构造
  CBuffer(emBufferType type);
  ~CBuffer();

  //显示
  void show();

  //清除显示
  void clear();

  //被触发
  void onTouch(CTank &tank);

  //设置坐标
  void setPos(int x, int y);

  //设置显示状态
  void setVisible(bool bFlag);

  //是否显示
  bool isShow();

public:
  //buffer类型
  emBufferType m_emBufferType;
  //是否显示
  bool m_bShowFlag;
};

