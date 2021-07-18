CC = gcc
CFLAGS	:= -Wall -Werror -Wextra -g -std=c17

OUTPUT	:= Output
SRC		:= Src
INCLUDE	:= Include
TEST 	:= Test
UNITY	:= Unity

ifeq ($(OS),Windows_NT)
MAIN	:= LinkedListTests.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
TESTDIRS	:= $(TEST)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
MAIN	:= LinkedListTests
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
TESTDIRS	:= $(shell find $(TEST) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
TESTS		:= $(wildcard $(patsubst %,%/*.c, $(TESTDIRS)))

OBJECTS		:= $(SOURCES:.c=.o) \
			   $(TESTS:.c=.o)

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) $(MAIN)

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(UNITY)/unity.c

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))

run: all
	./$(OUTPUTMAIN)