#include <stdio.h>
#include "timerFunc.h"


/**
* @brief タイマハンドラ
*
* @param arg
*/
void dummyHandler(int arg) {
	printf("--|");	
}

//***************************************
int main(int arc, char *argv[])
{

	int duration=500; //500msec interval
	int n=1;
	setTimer(100, dummyHandler);

	while(n<200){
		timerCount(duration);
		printf("%d %fsec\n",n, (float)n*duration/1000);
		n++;
	}
	quitTimer();

}

