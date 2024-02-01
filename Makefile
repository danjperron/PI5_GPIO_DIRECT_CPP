CC := g++
CFLAGS := -Wall -g
TARGET := gpioTest

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))



all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ 
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o


