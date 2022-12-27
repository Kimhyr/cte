#ifndef _BUFFER_HPP
#define _BUFFER_HPP

#include "space.hpp"

class Buffer {
        Dimension dimension;
        enum class Flag : Nat8 {
                WRITEABLE = 'w',
                SAVEABLE,
        } flags;
        const char *source;
        struct Segment {
        public:
                enum {
                        SPACE = 80
                };

        public:
                Bool edited;
                Sym data[SPACE];
                Sym *back;
                Segment *next;
                Segment *prev;

        public:
                Segment(Segment *prev = nil);
        } * first;
        Segment *last;
        struct Cursor {
        public:
                Location location;
                Nat16 index;
                Segment *segment;
        
        public:
                Cursor(Segment *segment);
        } cursor;

public:
        Buffer(Flag flags, const Sym *source = nil);

        ~Buffer();

private:
        Void loadFile();
};

#endif // _BUFFER_HPP
