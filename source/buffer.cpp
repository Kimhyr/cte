#include "buffer.hpp"

#include <stdio.h>

Buffer::Segment::Segment(Segment *prev)
        : edited(false), next(nil), prev(prev) {
        this->back = this->data;
}

Buffer::Cursor::Cursor(Segment *segment)
    : location({.row = 1, .column = 1}), index(0), segment(segment) {}

Buffer::Buffer(Flag flags, const Sym *source)
    : flags(flags), source(source), first(new Segment), cursor(this->first) {
        this->loadFile();
}

Void Buffer::loadFile() {
        Sym rights[3] = {'r', 0, 0};
        if (!Bool(~(this->flags | ~Flag::WRITEABLE)))
                rights[1] = 'w';
        FILE *file = fopen(this->source, rights);
        if (!file)
                throw 1;
        Sym datum = getc(file);
        Segment *segment;
        for (segment = this->first; datum != '\0';
             segment = segment->next = new Segment(segment))
                for (segment->back = segment->data;
                     (segment->back + 1) - segment->data < Segment::SPACE;
                     datum = getc(file)) {
                        *segment->back++ = datum;
                        if (datum == '\n')
                                break;
                }
        this->last = segment;
}
