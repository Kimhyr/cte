#ifndef CTE_BUFFER_HPP
#define CTE_BUFFER_HPP

#include "space.hpp"

#include <stdio.h>

namespace CTE {

class Buffer {
public:
        enum class Flag : Nat8 {
                WRITEABLE = 0x01,
                SAVEABLE  = 0x02,
        };

        struct Segment {
        public:
                static constexpr
                const Nat8 SPACE = 80;
        public:
                Bool edited;
                Sym data[SPACE];
                Nat8 size;
                Nat8 newLineIndex;
                Segment *next;
                Segment *prev;
        public:
                Segment();
                Segment(Segment *prev);
                Segment(Sym datum, Segment *prev);
                Segment(Sym *data, Segment *prev);
        public:
                Void insert(Segment *segment);
        };

        struct Cursor {
        public:
                Coordinate location;
                Segment *segment; // The segment that the cursor is on.
                Nat8 dataIndex;
        public:
                Cursor(Segment *segment);

                Void moveUp();

                Void moveDown();

                Void moveRight();
                
                Void moveLeft();
        };

public:
        Buffer(Flag flags, const Sym *sourceFilePath);

        ~Buffer();

public: // Operations

public:
        Void printData();
private:
        Dimension dimension;
        Flag flags;
        const Sym *sourceFilePath;
        Segment *first;
        Segment *last;
        Cursor cursor;
private:
        inline
        Void loadSource();
        
        inline
        FILE *openFile();

        inline
        Void insertSegment();

        inline
        Void deleteSegment();
};

}

 #endif // CTE_BUFFER_HPP
