TARGET=FalloutHackingGame
FLAGS=-std=gnu99

.PHONY: all clean

all: $(TARGET)

$(TARGET):
	gcc $(TARGET).c -o $(TARGET) $(FLAGS)

clean:
	rm -f $(TARGET)
	rm -f $(TARGET).exe.stackdump

rebuild: clean all