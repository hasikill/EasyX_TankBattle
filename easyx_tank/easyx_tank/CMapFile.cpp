#include "CMapFile.h"
#pragma warning(disable:4996)

CMapFile::CMapFile()
{
  FILE *fp = fopen(MAP_FILE_CONFIG, "rb+");
  char buf[8] = { 0 };
  m_nMapNum = 0;

  if (fp == NULL)
  {
    m_bInitFlag = false;
    goto EXIT;
  }

  //读一行
  fgets(buf, 8, fp);
  //读出地图数
  m_nMapNum = atoi(buf);

  //再读一行
  fgets(buf, 8, fp);
  //游戏速度
  m_nGameSpeed = atoi(buf);

  if (m_nMapNum == 0)
  {
    m_bInitFlag = false;
  }
  else
  {
    m_bInitFlag = true;
  }

EXIT:
  if (fp != NULL)
  {
    fclose(fp);
  }
  //初始化
  m_fp = NULL;
}


CMapFile::~CMapFile()
{
}

bool CMapFile::isInit()
{
  return m_bInitFlag;
}

bool CMapFile::open(const char * pszFileName, emMode mode)
{
  close();
  if (mode == MD_READ)
  {
    m_fp = fopen(pszFileName, "rb");
  }
  else if (mode == MD_WRITE)
  {
    m_fp = fopen(pszFileName, "wb");
  }
  return m_fp != NULL;
}

void CMapFile::close()
{
  if (m_fp != NULL)
  {
    fclose(m_fp);
    m_fp = NULL;
  }
}

bool CMapFile::getMap(int level, unsigned char mapdate[26][26])
{
  bool ret = false;
  //名字
  char szName[100] = { 0 };
  //关卡判断
  if (level <= m_nMapNum)
  {
    //拼接地图文件名称
    sprintf(szName, MAP_FILE_FORMAT, level);
    //打开文件
    if (open(szName, MD_READ))
    {
      //读取数据
      if (fread(mapdate, 26 * 26, 1, m_fp) == 1)
      {
        ret = true;
      }
    }
    //关闭文件
    close();
  }
  return ret;
}

bool CMapFile::setMap(int level, unsigned char mapdate[26][26])
{
  bool ret = false;
  //名字
  char szName[100] = { 0 };
  //拼接地图文件名称
  sprintf(szName, MAP_FILE_FORMAT, level);
  //打开文件
  if (open(szName, MD_WRITE))
  {
    //读取数据
    if (fwrite(mapdate, 26 * 26, 1, m_fp) == 1)
    {
      ret = true;
    }
  }
  //关闭文件
  close();
  return ret;
}

int CMapFile::getMapNum()
{
  return m_nMapNum;
}

int CMapFile::getGameSpeed()
{
  return m_nGameSpeed;
}
