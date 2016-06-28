#include <iostream>


#ifndef DEBUG
#define DEBUG 0
#endif
#if DEBUG
#define dout std::cout
#else
#define dout 0 && std::cout
#endif