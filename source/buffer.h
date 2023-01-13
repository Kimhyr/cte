#ifndef CTE_BUFFER_H_
#define CTE_BUFFER_H_

#include <stdio.h>

#include "utilities/dynamic.h"
#include "space.h"

namespace CTE {

using namespace Utilities;

class Buffer {
public:
        enum class Flag : Nat8 {
                WRITEABLE = 0x01,
                SAVEABLE  = 0x02,
        };

        class Segment {
        public:
                constant SPACE = 80;

        public:
                Segment();
                Segment(Segment *prev);
                Segment(Sym datum, Segment *prev);
                Segment(Sym *data, Segment *prev);

        public:
                property edited() constnox -> Bool { return this->edited_; }
                property data() constnox->const Sym * { return this->data_; }
                property size() constnox -> Nat64 { return this->size_; }
                property newLines() constnox -> const Dynamic<Nat8> *{ return &this->newLines_; }
                property next() noexcept -> Segment *{ return this->next_; }
                property prev() noexcept -> Segment *{ return this->prev_; }

        public:
                function insert(Segment *segment) -> Void;
        
        private:
                Bool edited_;
                Sym data_[SPACE];
                Nat8 size_;
                Dynamic<Nat8> newLines_;
                Segment *next_;
                Segment *prev_;
        };

        class Cursor {
        public:
                Cursor(Segment *segment);

                ~Cursor() = default;

        public:
                property location() constnox -> const Coordinate *{ return &this->location_; }
                property segment() noexcept -> Segment *{ return this->segment_; }
                property dataIndex() constnox -> Nat8 { return this->dataIndex_; }

        private:
                function moveUp() -> Void;
                function moveDown() -> Void;
                function moveRight() -> Void;
                function moveLeft() -> Void;
        
        private:
                Coordinate location_;
                Segment *segment_; // The segment that the cursor is on.
                Nat8 dataIndex_;
        };

public:
        Buffer(Dimension dimension, Flag flags, const Sym *sourceFilePath);

        ~Buffer();

public:
        property dimension() -> const Dimension *{ return &this->dimension_; }
        property flags() -> Flag { return this->flags_; }
        property sourcePath() -> const Sym *{ return this->sourcePath_; }
        property root() -> const Segment *{ return this->root_; }
        property head() -> const Segment *{ return this->head_; }
        property cursor() -> const Cursor *{ return &this->cursor_; }

public:
        function printData() -> Void;

private:
        Dimension dimension_;
        Flag flags_;
        const Sym *sourcePath_;
        Segment *root_;
        Segment *head_;
        Cursor cursor_;

private:
        function loadSource() -> Void;
        function openFile() -> FILE *;
};

}

 #endif // CTE_BUFFER_H_
