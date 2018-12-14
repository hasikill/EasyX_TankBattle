#pragma once
#include "CLifeEntity.h"

/*
  障碍物
*/
class CBarrier : public CLifeEntity
{
public:
  enum emBarrierType
  {
    BAR_WALL  = 1, //墙
    BAR_IRON  = 2, //铁
    BAR_CLOTH = 3, //布
    BAR_WATER = 4, //水
    BAR_GRASS = 5, //草
    BAR_HOME  = 6, //基地
    BAR_COUNT = 5  //基本类型数量
  };

  CBarrier();
  CBarrier(emBarrierType emType, CPosition m_pos, int nHP = 1);
  ~CBarrier();

  //获取
  emBarrierType getType();

  void setType(emBarrierType type);

  bool onHitBy(int nDamage);

  void ClearThis();

  void show();

  void SetBarrier(emBarrierType emType, CPosition m_pos, int nHP);

private:
  emBarrierType m_emType;
};

