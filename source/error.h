#ifndef CTE_ERROR_H
#define CTE_ERROR_H

namespace CTE {

enum class Error {
        FPUTS,  // fputs
        FCLOSE, // fclose
        FOPEN,  // fopen

        END_OF_TEXT,   // Buffer::Cursor::moveRight
        START_OF_TEXT, // Buffer::Cursor::moveLeft
        OUT_OF_RANGE,  // Utilities::Dynamic::pop
};

};

#endif // CTE_ERROR_H
