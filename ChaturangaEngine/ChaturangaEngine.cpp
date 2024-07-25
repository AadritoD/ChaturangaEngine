#include "types.h"
#include "UCI.cpp"
#include <iostream>

int main()
{
    init();
    UCI uci(DEFAULT);
    uci.loop();
}