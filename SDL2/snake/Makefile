### 2022-06-01 K.OHWADA
### for Linux and Mac

PROG := snake

SRCS=$(shell find src/ -type f -name "*.c")
OBJS=$(patsubst src/%.c,obj/%.o,$(SRCS))
DEPS=$(patsubst src/%.c,deps/%.d,$(SRCS))

CC :=gcc
CCFLAGS :=-Wall
INCLUDEPATH := -I/usr/local/include
LIBPATH := -L/usr/local/lib
LIBS := -lSDL2 -lSDL2_ttf

DIR_GUARD=@mkdir -p $(@D)

# Main targets
.PHONY: all clean clean_all

all: $(DEPENDS) bin/$(PROG)

# --- Link Rule
bin/$(PROG): $(OBJS)
	$(DIR_GUARD)
	$(CC) $(CCFLAGS) $(LIBPATH) $(LIBS) $(OBJS) $(LFLAGS) -o bin/$(PROG)

# --- Compile Rule
obj/%.o: src/%.c
	$(DIR_GUARD)
	$(CC) -c $(CCFLAGS) $< -o $@

# --- Dependency Rule
deps/%.d: src/%.c
	$(DIR_GUARD)
	$(CC) $(CFLAGS) -MM $< | sed -e 's/~\(.*\)\.o:/\1.d \1.o:/' > $@

clean:
	rm -rf $(PROG) $(OBJS) $(DEPS)

clean_all:
	rm -rf bin/* obj/* deps/*
	rmdir bin obj deps

 -include $(DEPS)
