### 2022-06-01 K.OHWADA
### reference: https://gammalab.net/blog/3rgve9rdw2kt5/
### https://github.com/brenns10/tetris/blob/master/Makefile

PROG := hello

SRCS=$(shell find src/ -type f -name "*.cpp")
OBJS=$(patsubst src/%.cpp,obj/%.o,$(SRCS))
DEPS=$(patsubst src/%.cpp,deps/%.d,$(SRCS))

CC := g++
CCFLAGS := -std=c++11  -Wall
INCLUDEPATH := -I/usr/local/include
LIBPATH := -L/usr/local/lib
# LIBS

DIR_GUARD=@mkdir -p $(@D)

# Main targets
.PHONY: all clean clean_all

all: $(DEPENDS) bin/$(PROG)

# --- Link Rule
bin/$(PROG): $(OBJS)
	$(DIR_GUARD)
	$(CC) $(CCFLAGS) $(LIBPATH) $(LIBS) $(OBJS) $(LFLAGS) -o bin/$(PROG)

# --- Compile Rule
obj/%.o: src/%.cpp
	$(DIR_GUARD)
	$(CC) -c $(CCFLAGS) $< -o $@

# --- Dependency Rule
deps/%.d: src/%.cpp
	$(DIR_GUARD)
	$(CC) $(CFLAGS) -MM $< | sed -e 's/~\(.*\)\.o:/\1.d \1.o:/' > $@

clean:
	rm -rf $(PROG) $(OBJS) $(DEPS)

clean_all:
	rm -rf bin/* obj/* deps/*
	rmdir bin obj deps

 -include $(DEPS)
