#ifndef MACROS_H
#define MACROS_H

#define DEBUG 0 // Enable to print basic debugging statements.
#define DEBUG_V 0 // Enable to print verbose debugging statements.

#if DEBUG
    #define DEBUG_PRINT(x) std::cout << x << std::endl
#else
    #define DEBUG_PRINT(x)
#endif

#if DEBUG_V
    #define DEBUG_PRINT_V(x) std::cout << x << std::endl
#else
    #define DEBUG_PRINT_V(x)
#endif

#define ERROR 1 // Error logging

#if ERROR
    #define ERROR_LOG(x) std:cerr << x << std::endl
#endif

#endif