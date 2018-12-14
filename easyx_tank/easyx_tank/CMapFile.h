#pragma once
#include <iostream>

#define MAP_FILE_CONFIG   "./map/map.ini"
#define MAP_FILE_FORMAT   "./map/level%d.dat"

class CMapFile
{
public:
  CMapFile();
  ~CMapFile();

  //模式
  enum emMode
  {
    MD_READ,
    MD_WRITE
  };

  //是否初始化
  bool isInit();

  //打开文件
  bool open(const char* pszFileName, emMode mode);

  //关闭文件
  void close();

  //读取地图关卡数据
  bool getMap(int level, unsigned char mapdate[26][26]);

  //写地图数据
  bool setMap(int level, unsigned char mapdate[26][26]);

  //获取关卡数
  int getMapNum();
  
  //读取游戏速度
  int getGameSpeed();

private:
  FILE * m_fp;
  int m_nMapNum;
  int m_nGameSpeed;
  bool m_bInitFlag;
};

