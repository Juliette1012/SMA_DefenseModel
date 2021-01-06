#include <iostream>
#include <unistd.h>

#include "MAS.h"

#include "AgtRcv.h"
#include "AgtSnd.h"

using namespace std;

int main(void)
{
 Scheduler sched;
 sched.setRandomMode(false);

 new AgtRcv;
 new AgtSnd;

 int t = 1;
 while(t<=10)
 {
 sleep(1);
 cout << "**********************************************************" << endl;
 sched.cycle();
 cout << "**********************************************************" << endl;

 t++;
 }

 cout << endl;

 return 0;
}
