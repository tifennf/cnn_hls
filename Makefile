CC = gcc
CFLAGS = -O2 -g
LDLIBS = -lm
TARGET = build/cnn
SOURCES = src/main.c src/fonctions_ES.c src/timers_b.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
