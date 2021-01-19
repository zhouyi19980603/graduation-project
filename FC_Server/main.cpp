#include <iostream>
#include "fc_server.h"
using namespace std;

#define FC_TCP_PORT 56781
#define FC_THREAD_NUM 4
int main()
{
    FC_Server fc(FC_THREAD_NUM,FC_TCP_PORT);
    return 0;
}
