### 2022-06-01 K.OHWADA

PROG=libhttpxx.a

SRCS=$(shell find src/ -type f -name "*.cpp")
OBJS=$(patsubst src/%.cpp,obj/%.o,$(SRCS))
DEPS=$(patsubst src/%.cpp,deps/%.d,$(SRCS))

CC := g++
CCFLAGS=-std=c++11  -Wall  -fpic -Iinclude

DIR_GUARD=@mkdir -p $(@D)

# Main targets
.PHONY: all clean clean_all

all: $(DEPENDS) bin/$(PROG)

# --- Link Rule
# https://stackoverflow.com/questions/34595766/object-files-not-properly-added-to-archive-on-mac/34617478#34617478

bin/$(PROG): $(OBJS)
	$(DIR_GUARD)
#	$(CC) $(CCFLAGS) -static $(OBJS)  -o bin/$(PROG)
	libtool -c -static $(OBJS) -o bin/$(PROG)


# --- Compile Rule
obj/%.o: src/%.cpp
	$(DIR_GUARD)
	$(CC) -c $(CCFLAGS) $< -o $@

# --- Dependency Rule
deps/%.d: src/%.cpp
	$(DIR_GUARD)
	$(CC) $(CCFLAGS) -MM $< | sed -e 's/~\(.*\)\.o:/\1.d \1.o:/' > $@

clean:
	rm -rf $(PROG) $(OBJS) $(DEPS)

clean_all:
	rm -rf bin/* obj/* deps/*
	rmdir bin obj deps

 -include $(DEPS)
