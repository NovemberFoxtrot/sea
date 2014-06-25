CFLAGS=-g -Wall -Wextra -Wformat=2 -Wno-format-nonliteral -Wshadow -Wpointer-arith -Wcast-qual -Wmissing-prototypes -Wno-missing-braces -std=c99 -O2 -pedantic

LIBS=-ldl -lJudy $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c src/*.h)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TARGET=build/sea

all: build $(TARGET)

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIBS)

clean:
	rm -rf $(OBJECTS)

rebuild: clean build

.phony: test
test:
	./build/sea
