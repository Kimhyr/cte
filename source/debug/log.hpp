#ifndef CE_DEBUG_LOG_HPP
#define CE_DEBUG_LOG_HPP

#include "../definitions.hpp"

#include <stdio.h>

#define LOG(MESSAGE)                                                           \
        printf("[\e[1;32mLOG\e[0m] " __FILE__ ":%s:%i"                         \
               "\n\t" MESSAGE "\n",                                            \
               __FUNCTION__, __LINE__)

namespace CE::Debug {

// struct Log {
//         enum struct Severity {
//                 VERBOSE,
//                 NOTE,
//                 WARNING,
//                 ERROR,
//         } severity;
//         const Sym *message;
// 
// public:
//         Log(Severity severity, const Sym *message);
// 
// public:
//         Void send();
// };

}

#endif // CE_DEBUG_LOG_HPP
