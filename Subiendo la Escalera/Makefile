CC = g++
CFLAGS = -std=c++17 -O3

SOURCES = SubiendoEscalera.cpp
EXECUTABLE = prog1

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)
