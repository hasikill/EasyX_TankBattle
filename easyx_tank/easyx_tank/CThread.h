#pragma once
#include <process.h>
#include "CTank.h"

class CThread
{
public:
  CThread();
  ~CThread();

  void startTankProtectAnime(CTank *tank);

  void start(_beginthread_proc_type _StartAddress, void *arg);

};

