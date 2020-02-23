#ifndef __TIMERFUNC_H_
#define __TIMERFUNC_H_

#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


struct sigaction act, oldact;
timer_t tid;
struct itimerspec itval;
//int restCnt=0;
int setTimer(int msecInterval, void (*func)(int));
void timerCount(int cnt);
int quitTimer();

#endif 
