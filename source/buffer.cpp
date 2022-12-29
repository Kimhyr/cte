#include "buffer.hpp"

namespace CE {

Buffer::Segment::Segment(Segment *prevSegment)
        : edited(false), dataSize(0),
          nextSegment(nil), prevSegment(prevSegment) {}

Buffer::Segment::Segment(Sym datum)
        : edited(false), dataSize(1),
          nextSegment(nil), prevSegment(nil) {
        *this->data = datum;
}

Void Buffer::Segment::insertAfter(Segment *segment) {
        segment->prevSegment = this;
        segment->nextSegment = this->nextSegment; 
        this->nextSegment->prevSegment = segment;
        this->nextSegment = segment;
}

Buffer::Cursor::Cursor(Segment *segment)
        : location({.row = 1, .column = 1}),
          segment(segment), segmentDataIndex(0) {
}

Buffer::Buffer(Flag flags, const Sym *sourceFilePath)
        : flags(flags), sourceFilePath(sourceFilePath),
          firstSegment(new Segment), cursor(this->firstSegment) {
        this->loadSource();
}

Buffer::~Buffer() {
        for (Segment *segment; this->firstSegment;
             this->firstSegment = segment) {
                segment = this->firstSegment;
                delete this->firstSegment;
        }
}

Void Buffer::write(Sym datum) {
        Segment *segment = this->cursor.segment;
        if (segment->dataSize + 1 > Buffer::Segment::DATA_SPACE)
                this->insertSegment();
        segment->data[this->cursor.segmentDataIndex++] = datum;
}

Void Buffer::erase() {
        if (this->cursor.segment->dataSize - 1 < 0)
                this->deleteSegment();
}

Void Buffer::printData() {
        for (Segment *segment = this->firstSegment; segment;
             segment = segment->nextSegment)
                if (fputs(segment->data, stdout) == -1)
                        throw Bool(0);
}

Void Buffer::loadSource() {
        FILE *file = this->openFile();
        Segment *segment;
        for (segment = this->firstSegment;;
             segment = segment->nextSegment = new Segment(segment)) {
                for (Int datum = fgetc(file);
                     segment->dataSize < Segment::DATA_SPACE;
                     datum = fgetc(file)) {
                        if (datum == EOF) // https://www.your-mom.com
                                goto Epilogue;
                        segment->data[segment->dataSize++] = datum;
                }
        }

Epilogue:
        segment->data[segment->dataSize - 1]  = 0;
        this->lastSegment = segment;
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
        Segment **segment = &this->cursor.segment;
        (*segment)->insertAfter(new Segment((*segment)->data[
                this->cursor.segmentDataIndex]));
        *segment = (*segment)->nextSegment; // Please, Optimizer, optimize
                                            // this.
        this->cursor.segmentDataIndex = 0;
}

Void Buffer::deleteSegment() {
        Segment *segment = this->cursor.segment;
        this->cursor.segment = segment->nextSegment;
        delete segment;
        this->cursor.segmentDataIndex = this->cursor.segment->dataSize - 1;
}

}
