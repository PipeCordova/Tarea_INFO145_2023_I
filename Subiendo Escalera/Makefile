CC = g++
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -fopenmp
SOURCES = main.cpp
EXECUTABLE = prog1

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)

