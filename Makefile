NAME = buhlmann
VERSION = 0
PATCHLEVEL = 1
SUBLEVEL = 
EXTRAVERSION = 

FULLVERSION = $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)

EXECUTABLE = $(NAME)-$(FULLVERSION)

all: $(EXECUTABLE)

SOURCES=$(shell find . -type f -name "*.c")
OBJECTS=$(SOURCES:.c=.o)

CFLAGS = -g -Wall -Wextra
CLIBS = -lrt -lm

include .config

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(CLIBS)

clean:
	$(RM) $(OBJECTS) $(NAME)-*
