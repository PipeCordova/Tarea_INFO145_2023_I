CC = g++
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -fopenmp
SOURCES = solucionGrafos.cpp
EXECUTABLE = prog3

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)

