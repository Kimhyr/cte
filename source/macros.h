#ifndef CTE_MACROS_H
#define CTE_MACROS_H

#include <stdlib.h>

#ifdef CTE_USE_MACRO_NAMESPACE
#define CTE_log$(MESSAGE)                                                      \
        printf("[\e[1;32mLOG\e[0m] " __FILE__ ":%s:%i"                         \
               "\n\t" MESSAGE "\n",                                            \
               __FUNCTION__, __LINE__)
#define CTE_task$(DESCRIPTION)                                                 \
        do {                                                                   \
                printf("[\e[1;33mTASK\e[0m] " __FILE__ ":%s:%i"                \
                       "\n\t" DESCRIPTION "\n",                                \
                       __FUNCTION__, __LINE__);                                \
                exit(1);                                                       \
        } while (0)
#else // CTE_USE_MACRO_NAMESPACE
#define log$(MESSAGE)                                                          \
        printf("[\e[1;32mLOG\e[0m] " __FILE__ ":%s:%i"                         \
               "\n\t" MESSAGE "\n",                                            \
               __FUNCTION__, __LINE__)
#define task$(DESCRIPTION)                                                     \
        do {                                                                   \
                printf("[\e[1;33mTASK\e[0m] " __FILE__ ":%s:%i"                \
                       "\n\t" DESCRIPTION "\n",                                \
                       __FUNCTION__, __LINE__);                                \
                exit(1);                                                       \
        } while (0)
#endif // CTE_USE_MACRO_NAMESPACE

#endif // CTE_MACROS_H
