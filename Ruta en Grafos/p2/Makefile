CC = g++
CFLAGS = -std=c++17 -O3

SOURCES = Funciona.cpp
EXECUTABLE = prog3

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)
