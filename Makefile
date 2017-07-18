TARGET = snake
CC = g++
CCFLAGS = -Wall
LDFLAGS = -lpthread

.PHONY: all clean install uninstall
all: $(TARGET)

$(TARGET): snake.h snake.cpp source.cpp gui.cpp gui.h
	$(CC) $(CCFLAGS) snake.cpp source.cpp gui.cpp $(LDFLAGS) -o $(TARGET) 

install:
	sudo cp -f $(TARGET) /usr/bin/

uninstall:
	sudo rm -f /usr/bin/$(TARGET)
clean:
	rm -f *.o $(TARGET)
