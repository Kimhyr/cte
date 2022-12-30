#ifndef CE_MACROS_HPP
#define CE_MACROS_HPP

#include <stdlib.h>

#define $log(MESSAGE)                                                           \
        printf("[\e[1;32mLOG\e[0m] " __FILE__ ":%s:%i"                         \
               "\n\t" MESSAGE "\n",                                            \
               __FUNCTION__, __LINE__)

#define $task(DESCRIPTION)                                                      \
        do {                                                                   \
                printf("[\e[1;33mTASK\e[0m] " __FILE__ ":%s:%i"                \
                       "\n\t" DESCRIPTION "\n",                                \
                       __FUNCTION__, __LINE__);                                \
                exit(1);                                                       \
        } while (0)

#endif // CE_MACROS_HPP
