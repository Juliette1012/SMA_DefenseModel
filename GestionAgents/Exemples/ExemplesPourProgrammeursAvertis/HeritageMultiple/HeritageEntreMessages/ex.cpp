#include <iostream>
#include <unistd.h>

#include "MAS.h"

#include "MA.h"
#include "MB.h"
#include "MAB.h"

using namespace std;

int main(void)
{
 Scheduler sched;

 Agent a1;
 Agent a2;

#if 0

 MAB m;

 a1.sendMessageTo(reinterpret_cast<Message&>(m),&a2);

 Message *nm = a2.getNextMessage();

 cout << m << endl;

 cout << "--------------" << endl;

 cout << *nm << endl;

 delete nm;

#else

 Message *m = reinterpret_cast<Message*>(new MAB);

 a1.sendMessageTo(*m,&a2);

 Message *nm = a2.getNextMessage();

 cout << *m << endl;

 cout << "--------------" << endl;

 cout << *nm << endl;

 delete nm;

 delete m;

#endif
 
 return 0;
}
