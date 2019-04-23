CC = gcc-8
CFLAGS = -fopenmp -lcurl

TARGET = concurrent-count

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean: 
	$(RM) $(TARGET)
