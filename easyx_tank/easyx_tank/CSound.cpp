#include "CSound.h"
#include <windows.h>
#include <mmsystem.h>
#include "GameConst.h"

#pragma comment(lib,"winmm.lib")

CSound::CSound()
{
}

CSound::~CSound()
{
}

void SoundPlayer(void *p)
{
  PlaySound((LPCSTR)p, NULL,
    SND_FILENAME | SND_ASYNC | SND_NOSTOP);
}

void CSound::PlayStartSound()
{
  g_Game->Thread.start(SoundPlayer, (void*)TEXT("sound/start.wav"));
}

void CSound::PlayTankCrackSound()
{
  g_Game->Thread.start(SoundPlayer, (void*)TEXT("sound/tankCrack.wav"));
}

void CSound::PlayFireSound()
{
  mciOpen.lpstrElementName = "./sound/attack.wav";
  if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&mciOpen) == 0)
    dev[0] = mciOpen.wDeviceID;
  else
    mciOpen.wDeviceID = dev[0];
  mciPlay.dwFrom = 0;
  mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_FROM, (DWORD)&mciPlay);
  //g_Game->Thread.start(SoundPlayer, (void*)TEXT("sound/attack.wav"));
}

void CSound::PlayBulletCrackSound()
{
  mciOpen.lpstrElementName = "./sound/bulletCrack.wav";
  if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&mciOpen) == 0)
    dev[1] = mciOpen.wDeviceID;
  else
    mciOpen.wDeviceID = dev[1];
  mciPlay.dwFrom = 0;
  mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_FROM, (DWORD)&mciPlay);
  //g_Game->Thread.start(SoundPlayer, (void*)TEXT("sound/bulletCrack.wav"));
}

void CSound::PlayMoveSound()
{
  g_Game->Thread.start(SoundPlayer, (void*)TEXT("sound/move.wav"));
}

void CSound::PlayPlayerCrackSound()
{
  mciOpen.lpstrElementName = "./sound/playerCrack.wav";
  if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&mciOpen) == 0)
    dev[3] = mciOpen.wDeviceID;
  else
    mciOpen.wDeviceID = dev[3];
  mciPlay.dwFrom = 0;
  mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_FROM, (DWORD)&mciPlay);
  //g_Game->Thread.start(SoundPlayer, (void*)TEXT("sound/playerCrack.wav"));
}

void CSound::PlayPropSound()
{
  mciOpen.lpstrElementName = "./sound/prop.wav";
  if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&mciOpen) == 0)
    dev[2] = mciOpen.wDeviceID;
  else
    mciOpen.wDeviceID = dev[2];
  mciPlay.dwFrom = 0;
  mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_FROM, (DWORD)&mciPlay);
  //g_Game->Thread.start(SoundPlayer, (void*)TEXT("sound/prop.wav"));
}
