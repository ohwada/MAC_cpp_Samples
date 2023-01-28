### 2022-10-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
YAML_FLAGS=`pkg-config --cflags --libs  yaml-0.1`

TARGET=parser
SRCS=yaml_parser.c


$(TARGET): $(SRCS)
	$(CC) $< $(CFLAGS) $(YAML_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 
