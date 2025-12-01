CC = gcc
CFLAGS = -Iincludes
TARGET = main
SRC = src/*.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -f $(TARGET).exe
