#ifndef CE_BUFFER_HPP
#define CE_BUFFER_HPP

#include "space.hpp"

#include <stdio.h>

namespace CE {

class Buffer {
public:
        enum class Flag : Nat8 {
                WRITEABLE = 'w',
                SAVEABLE,
        };

        struct Segment {
        public:
                enum {
                        DATA_SPACE = 80
                };

        public:
                Bool edited;
                Sym data[DATA_SPACE];
                Nat8 dataSize;
                Segment *nextSegment;
                Segment *prevSegment;

        public:
                Segment(Segment *prevSegment = nil);
                Segment(Sym datum);
        
        public:
                Void insertAfter(Segment *segment);
        };

        struct Cursor {
        public:
                Location location;
                Segment *segment; // The segment that the cursor is on.
                Nat8 segmentDataIndex;

        public:
                Cursor(Segment *segment);
        };

public:
        Buffer(Flag flags, const Sym *sourceFilePath);

        ~Buffer();

public:
        Void insert(Sym datum);
        
        Void printData();

private:
        Dimension dimension;
        Flag flags;
        const Sym *sourceFilePath;
        Segment *firstSegment;
        Segment *lastSegment;
        Cursor cursor;

private:
        inline Void loadSourceFile();
        inline FILE *openSourceFile();
};

}

 #endif // CE_BUFFER_HPP
