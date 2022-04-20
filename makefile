OBJFILES = helpers.o main.o
TARGET   = ccsh

all: $(TARGET)

$(TARGET): $(OBJFILES)
	gcc -Wall -g -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
