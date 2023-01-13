#include "buffer.h"

#include "macros.h"
#include "error.h"

// NOTES
//         ?segment.prev -> SOT
//         ?segment.next -> EOT
//

namespace CTE {

Buffer::Segment::Segment()
        : edited_(false), size_(0), newLines_(0), next_(nil),
          prev_(nil) {}

Buffer::Segment::Segment(Segment *prev)
        : edited_(false), size_(0), newLines_(0), next_(nil),
          prev_(prev) {}

Buffer::Segment::Segment(Sym datum, Segment *prev)
        : edited_(true), size_(1), newLines_(0), next_(nil),
          prev_(prev) {
        *this->data_ = datum;
}

Buffer::Segment::Segment(Sym *data, Segment *prev)
        : edited_(true), newLines_(0), next_(nil), prev_(prev) {
        for (this->size_ = 0; data[this->size_] && this->size_ <= SPACE;
             ++this->size_)
                this->data_[this->size_] = data[this->size_];
}

function Buffer::Segment::insert(Segment *segment) -> Void {
        segment->prev(this) ;
        segment->next(this->next()); 
        this->next()->prev(segment);
        this->next_ = segment;
}

Buffer::Cursor::Cursor(Segment *segment)
        : location_({.row = 1, .column = 1}), segment_(segment), dataIndex_(0) {
}

Void Buffer::Cursor::moveUp() {
        task$("");     
}

Void Buffer::Cursor::moveDown() {
        task$("");
}

Void Buffer::Cursor::moveRight() {
        if (this->dataIndex() + 1 == this->segment()->size()) {
                if (this->segment()->next()) {
                        auto segment = this->segment();
                        segment = this->segment()->next();
                        this->dataIndex_ = 0;
                } else throw Error::END_OF_TEXT;
        } else ++this->dataIndex_;
        if (this->segment()->newLines()->exists(this->dataIndex())) {
                ++this->location_.row; 
                this->location_.column = 0;
        } else ++this->location_.column;
}



Void Buffer::Cursor::moveLeft() {
        // TODO: Check if there is a more efficient way of handling new lines
        //       without the `newLine` boolean.
        Bool newLine = this->segment()->newLines()->exists(this->dataIndex());
        if (this->dataIndex_ - 1 == -1) {
                if (this->segment_->prev_) {
                        this->segment_ = this->segment()->prev();
                        this->dataIndex_ = 0;
                } else throw Error::START_OF_TEXT;
        } else --this->dataIndex_;
        if (newLine) {
                --this->location_.row;
                this->location_.column = this->dataIndex_ + 1;
        } else --this->location_.column;
        
}

Buffer::Buffer(Dimension dimension, Flag flags, const Sym *sourceFilePath)
        : dimension_(dimension), flags_(flags), sourceFilePath_(sourceFilePath), first_(new Segment),
          cursor_(this->first_) {
        this->loadSource();
}

Buffer::~Buffer() {
        for (Segment *segment; this->first_; this->first_ = segment) {
                segment = this->first_;
                delete this->first_;
        }
}

Void Buffer::printData() {
        for (Segment *segment = this->first_; segment; segment = segment->next_)
                if (fputs(segment->data_, stdout) == -1)
                        throw Error::FPUTS;
}

Void Buffer::loadSource() {
        FILE *file = this->openFile();
        Segment *segment;
        for (segment = this->first_;; segment = segment->next_ = new Segment(segment)) {
                for (Int datum = fgetc(file); segment->size_ < Segment::SPACE; datum = fgetc(file)) {
                        if (datum == EOF) // https://www.your-mom.com
                                goto Epilogue;
                        if (datum == '\n')
                                segment->newLines_.put(segment->size_);
                        segment->data_[segment->size_] = datum;
                        ++segment->size_;
                }
        }

Epilogue:
        segment->data_[segment->size_]  = 0;
        this->last_ = segment;
        if (fclose(file) == -1)
                throw Error::FCLOSE;
}

FILE *Buffer::openFile() {
        Sym rights[3] = {'r', 0, 0};
        if (!(Bool)~(this->flags_ | ~Flag::WRITEABLE))
                rights[1] = 'w';
        FILE *file = fopen(this->sourceFilePath_, rights);
        if (!file)
                throw Error::FOPEN;
        return file;
}

}
