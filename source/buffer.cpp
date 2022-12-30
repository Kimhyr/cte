#include "buffer.hpp"

#include "macros.hpp"

namespace CE {

///////////////////////////////////////////////////////////////////////////////
// Segment

Buffer::Segment::Segment(Segment *prev)
        : edited(false), size(0),
          next(nil), prev(prev) {}

Buffer::Segment::Segment(Sym datum, Segment *prev)
        : edited(true), size(1),
          next(nil), prev(prev) {
        *this->data = datum;
}

Buffer::Segment::Segment(Sym *data, Segment *prev)
        : edited(true), next(nil),
          prev(prev) {
        for (this->size = 0; data[this->size] && this->size <= SPACE;
             ++this->size)
                this->data[this->size] = data[this->size];
}

Void Buffer::Segment::insert(Segment *segment) {
        segment->prev = this;
        segment->next = this->next; 
        this->next->prev = segment;
        this->next = segment;
}

///////////////////////////////////////////////////////////////////////////////
// Cursor

Buffer::Cursor::Cursor(Segment *segment)
        : location({.row = 1, .column = 1}),
          segment(segment), dataIndex(0) {
}

Void Buffer::Cursor::moveRight() {
        if (!this->segment->size)
                throw Bool(0);
        if (this->dataIndex < this->segment->size) {
                ++this->dataIndex;
                goto Epilogue;
        }
        if (this->dataIndex + 1 > this->segment->newLineIndex) {
                ++this->location.row;
                this->location.column = 0;
        }
        if (this->segment->size < Segment::SPACE) {
                ++this->dataIndex;
                goto Epilogue;
        }
        this->segment->insert(this->segment);
        this->segment = this->segment->next;
        this->dataIndex = 0;
Epilogue:
        ++this->location.column;
}

Void Buffer::Cursor::moveLeft() {

}

///////////////////////////////////////////////////////////////////////////////
// Buffer

Buffer::Buffer(Flag flags, const Sym *sourceFilePath)
        : flags(flags), sourceFilePath(sourceFilePath),
          first(new Segment), cursor(this->first) {
        this->loadSource();
}

Buffer::~Buffer() {
        for (Segment *segment; this->first; this->first = segment) {
                segment = this->first;
                delete this->first;
        }
}

Void Buffer::printData() {
        for (Segment *segment = this->first; segment; segment = segment->next)
                if (fputs(segment->data, stdout) == -1)
                        throw Bool(0);
}

///////////////////////////////////////////////////////////////////////////////
// Utilities

Void Buffer::loadSource() {
        FILE *file = this->openFile();
        Segment *segment;
        for (segment = this->first;;
             segment = segment->next = new Segment(segment)) {
                for (Int datum = fgetc(file);
                     segment->size < Segment::SPACE;
                     datum = fgetc(file)) {
                        if (datum == EOF) // https://www.your-mom.com
                                goto Epilogue;
                        segment->data[segment->size++] = datum;
                }
        }

Epilogue:
        segment->data[segment->size - 1]  = 0;
        this->last = segment;
        if (fclose(file) == -1)
                throw Bool(0);
}

FILE *Buffer::openFile() {
        Sym rights[3] = {'r', 0, 0};
        if (!Bool(~(this->flags | ~Flag::WRITEABLE)))
                rights[1] = 'w';
        FILE *file = fopen(this->sourceFilePath, rights);
        if (!file)
                throw Bool(0);
        return file;
}

Void Buffer::insertSegment() {
        $task("Unimplemented.");
}

Void Buffer::deleteSegment() {
        Segment *segment = this->cursor.segment;
        this->cursor.segment = segment->next;
        delete segment;
        this->cursor.dataIndex = this->cursor.segment->size - 1;
}

}
