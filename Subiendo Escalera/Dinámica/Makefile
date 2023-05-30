CC = g++
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -fopenmp
SOURCES = solucionDinamica.cpp
EXECUTABLE = prog2

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)

