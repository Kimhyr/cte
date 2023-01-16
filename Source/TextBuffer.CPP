#include "TextBuffer.H"

#include "Error.H"

namespace CTE {

TextBuffer::TextBuffer(Flag flags, const Sym *source)
	: flags_(flags) {
	this->loadSource(source);
}

TextBuffer::~TextBuffer() {
	for (Segment *current; this->root_; this->root_ = current) {
		current = this->root_->above_;
		delete this->root_;
	}
}

Void TextBuffer::flush(const Sym *path)
const {
	File file(File::Permission::WRITE, path);
	Segment *segment = this->root_;
	Nat8 segmentI = 0;
	for (Nat64 i = 0; file.current() != neg; file.advance()) {
		if (!segment->isModified_)
			goto Next_Segment;
		if (i < segment->span_.start)
			continue;
		if (i >= segment->span_.end)
			file.write(segment->data_[segmentI]);
		else file.replace(segment->data_[segmentI]);
	Next_Segment:
		segment = segment->above_;
		if (!segment)
			break;
	}
}

Void TextBuffer::loadSource(const Sym *source) {
	FILE *file = this->openFile(source);
	Segment *segment;
	for (segment = this->root_;; segment = segment->above_ = new Segment(segment)) {
		for (Int datum = fgetc(file); segment->size_ < Segment::SPACE; datum = fgetc(file)) {
			if (datum == EOF)
				goto Epilogue;
			if (datum == '\n')
				segment->newLines_.put(segment->size_);
			segment->data_[segment->size_] = datum;
			++segment->size_;
		}
	}

Epilogue:
	segment->data_[segment->size_ - 1] = 0;
	this->head_ = segment;
	if (fclose(file) == -1)
		throw Error::FCLOSE;
}

FILE *TextBuffer::openFile(const Sym *source)
const {
	Sym flags[3] = {'r', 0, 0};
	if (!(Bool)~(this->flags_ | ~Flag::WRITEABLE))
		flags[1] = 'w';
	FILE *file = fopen(source, flags);
	if (!file)
		throw Error::FOPEN;
	return file;
}



}
