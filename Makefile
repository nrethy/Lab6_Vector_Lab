CC=gcc
CFLAGS= -c -Wall -Wextra -g
LDFLAGS= -lm
SOURCES=main.c newlogic.c vector.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=exe

all: $(EXECUTABLE)

-include $(OBJECTS:.o=.d)

$(EXECUTABLE):$(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d
