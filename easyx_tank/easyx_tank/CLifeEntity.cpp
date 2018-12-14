#include "CLifeEntity.h"

CLifeEntity::CLifeEntity(CPosition pos, emLifeType emType,int nHP)
  : m_pos(pos), m_emType(emType), m_nHP(nHP)
{
  m_bAliveFlag = true;
}

CLifeEntity::~CLifeEntity()
{

}

void CLifeEntity::toDie()
{
  m_bAliveFlag = false;
}

bool CLifeEntity::isAlive()
{
  return m_bAliveFlag;
}

bool CLifeEntity::onHitBy(int nDamage)
{
  return false;
}

void CLifeEntity::show()
{
}

int CLifeEntity::GetHP()
{
  return m_nHP;
}

void CLifeEntity::SetHP(int nHP)
{
  m_nHP = nHP;
}

bool CLifeEntity::SubHp(int nHP)
{
  m_nHP = m_nHP - nHP;
  if (m_nHP <= 0)
  {
    m_nHP = 0;
    return false;
  }
  return true;
}

void CLifeEntity::toAlive()
{
  m_bAliveFlag = true;
}

void CLifeEntity::SetLifeType(emLifeType emType)
{
  m_emType = emType;
}

CLifeEntity::emLifeType CLifeEntity::GetLifeType()
{
  return m_emType;
}
