#ifndef CTE_TextBufferSegment_H
#define CTE_TextBufferSegment_H

#include <stdio.h>

#include "Utilities/Space.H"
#include "Utilities/Dynamic.H"
#include "Utilities/Flag.H"
#include "Utilities/File.H"

namespace CTE {

class TextBuffer {
public:
	enum class Flag {
		WRITEABLE,
		SAVEABLE,
	};
	
	class Segment {
	public:
		friend class TextBuffer;

	public:
		static constexpr
		Nat8 SPACE = 80;
	
	public:
		Segment(Segment *under);

		~Segment();

	public:
		constexpr
		const TextBuffer *buffer()
		const noexcept { return this->buffer_; }
		
		constexpr
		const Byte *data()
		const noexcept { return this->data_; }

		constexpr
		Nat8 size()
		const noexcept { return this->size_; }

		constexpr
		const Dynamic<Nat8> *newLines()
		const noexcept { return &this->newLines_; }

		constexpr
		Bool isModified()
		const noexcept { return this->isModified_; }

		constexpr
		const Segment *under()
		const noexcept { return this->under_; }
		
		constexpr
		const Segment *above()
		const noexcept { return this->above_; }
	
	private:
		TextBuffer *buffer_;
		Span span_;
		Byte data_[SPACE];
		Nat8 size_;
		Dynamic<Nat8> newLines_;
		Bool isModified_;
		Segment *under_;
		Segment *above_;
	};

	class Cursor {
	public:
		friend class TextEditor;
	
	public:
		constexpr
		const TextBuffer *buffer()
		const noexcept { return this->buffer_; }

		constexpr
		const Position &position()
		const noexcept { return this->position_; }

		constexpr
		const Segment &segment()
		const noexcept{ return *this->segment_; }

		constexpr
		Nat8 index()
		const noexcept { return this->index_; }
		
	private:
		TextBuffer *buffer_;
		Position position_;
		Segment *segment_;
		Nat8 index_;
	};

public:
	friend class Segment;
	friend class Cursor;

public:
	TextBuffer(Flag flags, const Sym *source);

	~TextBuffer();

public:
	constexpr
	const Dimension *dimension()
	const noexcept { return &this->dimension_; }

	constexpr
	const Cursor *cursor()
	const noexcept { return &this->cursor_; }

	constexpr
	const Segment *root()
	const noexcept { return this->root_; }

	constexpr
	const Segment *head()
	const noexcept { return this->head_; }

public:
	Void flush(const Sym *path)
	const;

private:
	Flag flags_;
	Dimension dimension_;
	Cursor cursor_;
	Segment *root_;
	Segment *head_;

private:
	Void loadSource(const Sym *source);

	FILE *openFile(const Sym *source)
	const;
};

}

#endif // CTE_TextBufferSegment_H
