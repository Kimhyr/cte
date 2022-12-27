NAME=text_buffer

# Directories
SRCD=./source
BLDD=./build
OBJD=$(BLDD)/objects
DIRS=.

# Files
SRCS=$(foreach D,$(DIRS),$(wildcard $(SRCD)/$(D)/*.cpp))
OBJS=$(patsubst $(SRCD)/%.cpp,$(OBJD)/%.obj,$(SRCS))
BIN=$(BLDD)/$(NAME).exe

# Build
CC=clang++
CFLGS=-std=c++11 -O3
WFLGS=-Wall -Wextra
FLGS=$(CFLGS) $(WFLGS) $(IFLGS)

all:$(BIN)

r:$(BIN)
	clear
	$(BIN)

$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(LFLGS)

$(OBJD)/%.obj:$(SRCD)/%.cpp
	$(CC) -c $^ -o $@ $(FLGS)

c:$(BLDD)
	rm -rf $(OBJS) $(BIN)

f:
	clang-format -i $(SRCS) $(foreach D,$(DIRS),$(wildcard $(SRCD)/$(D)/*.hpp))

.PHONY:all r c f
