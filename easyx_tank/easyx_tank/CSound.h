#pragma once
#include <Windows.h>
#include <MMSystem.h>

class CSound
{
public:
  CSound();
  ~CSound();

  //播放开始的音乐
  void PlayStartSound();

  //播放坦克爆炸声音
  void PlayTankCrackSound();

  //播放开火声音
  void PlayFireSound();

  //播放子弹爆炸声音
  void PlayBulletCrackSound();

  //播放坦克移动声音
  void PlayMoveSound();

  //播放玩家坦克爆炸声音
  void PlayPlayerCrackSound();
  
  //播放捡到补给声音
  void PlayPropSound();

  MCIDEVICEID dev[20];
  MCI_OPEN_PARMS mciOpen;
  MCI_PLAY_PARMS mciPlay;

};

void SoundPlayer(void *p);