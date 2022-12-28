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
        this->loadSourceFile();
}

Buffer::~Buffer() {
        for (Segment *segment; this->firstSegment;
             this->firstSegment = segment) {
                segment = this->firstSegment;
                delete this->firstSegment;
        }
}

Void Buffer::insert(Sym datum) {
        if (datum == '\n') {
                this->cursor.segment->insertAfter(new Segment(datum));
                this->cursor.segment = this->cursor.segment->nextSegment;
                return;
        }
        switch (this->cursor.segment->data[this->cursor.segmentDataIndex]) {
        case 0:
                if (this->cursor.segment->dataSize + 1 > Buffer::Segment::DATA_SPACE) {
                        this->cursor.segment->insertAfter(
                                        new Segment(this->cursor.segment->data[
                                                this->cursor.segmentDataIndex]));
                }
                this->cursor.segment->data[this->cursor.segmentDataIndex] = datum;
                break;
        case '\n':
                break;
        default:
                break;
        }
}

Void Buffer::printData() {
        for (Segment *segment = this->firstSegment; segment;
             segment = segment->nextSegment)
                if (fputs(segment->data, stdout) == -1)
                        throw Bool(0);
}

Void Buffer::loadSourceFile() {
        FILE *file = this->openSourceFile();
        Segment *segment;
        for (segment = this->firstSegment;;
             segment = segment->nextSegment = new Segment(segment))
                for (Int datum = fgetc(file);
                     segment->dataSize < Segment::DATA_SPACE;
                     datum = fgetc(file), ++segment->dataSize) {
                        if (datum == EOF) // https://www.your-mom.com
                                goto On_EOF;
                        segment->data[segment->dataSize] = datum;
                        if (datum == '\n')
                                break;
                }
On_EOF:
        segment->data[segment->dataSize - 1]  = 0;
        this->lastSegment = segment;
        if (fclose(file) == -1)
                throw Bool(0);
}

FILE *Buffer::openSourceFile() {
        Sym rights[3] = {'r', 0, 0};
        if (!Bool(~(this->flags | ~Flag::WRITEABLE)))
                rights[1] = 'w';
        FILE *file = fopen(this->sourceFilePath, rights);
        if (!file)
                throw Bool(0);
        return file;
}

}
