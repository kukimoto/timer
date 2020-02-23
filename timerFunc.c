#include "timerFunc.h"

/**                                                                                                                     
* @brief タイマーの設定。msec間隔でfuncを実行
*
* @param msecInterval　間隔の時間。msecで設定
* @param func　実行する関数
*
* @return
*/
int setTimer(int msecInterval, void (*func)(int)) {
  int i;

  memset(&act, 0, sizeof(struct sigaction));
  memset(&oldact, 0, sizeof(struct sigaction));

  // シグナルハンドラの登録
  act.sa_handler = func;
  act.sa_flags = SA_RESTART;
  if (sigaction(SIGALRM, &act, &oldact) < 0) {
    perror("sigaction()");
    return -1;
  }

  // タイマ割り込みを発生させる
  itval.it_value.tv_sec = 0;
  itval.it_value.tv_nsec = 1000 * 1000 * msecInterval;
  itval.it_interval.tv_sec = 0;
  itval.it_interval.tv_nsec = 1000 * 1000 * msecInterval;

  // タイマの作成
  if (timer_create(CLOCK_REALTIME, NULL, &tid) < 0) {
    perror("timer_create");
    return -1;
  }

  //  タイマのセット
  if (timer_settime(tid, 0, &itval, NULL) < 0) {
    perror("timer_settime");
    return -1;
  }
  return 0;
}

/**
* @brief 引数（msec)の時間の間回り続ける
*
* @param cnt　msecで設定
*/
void timerCount(int cnt) {
	static int restCnt;
  int i = 0;
  while (i < (int)(cnt / 100)) {
    // シグナル(タイマ割り込み)が発生するまでサスペンドする
    pause();
    restCnt = cnt / 100 - i;
    i++;
  }
}

/**
* @brief タイマーの終了
*
* @return
*/
int quitTimer() {
  // タイマの解除
  timer_delete(tid);
  // シグナルハンドラの解除
  sigaction(SIGALRM, &oldact, NULL);

  return 0;
}
