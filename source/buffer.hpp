#ifndef CE_BUFFER_HPP
#define CE_BUFFER_HPP

#include "space.hpp"

#include <stdio.h>

namespace CE {

class Buffer {
public:
        enum class Flag : Nat8 {
                WRITEABLE = 0x01,
                SAVEABLE  = 0x02,
        };

        struct Segment {
        public:
                static constexpr
                const Nat8 DATA_SPACE = 0;

        public:
                Bool edited;
                Sym data[DATA_SPACE];
                Nat8 dataSize;
                Nat8 newLineIndex;
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

public: // Operations
        Void write(Sym datum);

        Void erase();

public:
        Void printData();

private:
        Dimension dimension;
        Flag flags;
        const Sym *sourceFilePath;
        Segment *firstSegment;
        Segment *lastSegment;
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

 #endif // CE_BUFFER_HPP
