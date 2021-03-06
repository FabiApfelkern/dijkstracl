#
# This is a little bit more sophisticated makefile than the
# one you can find the structure folder. It does more things
# by convention which means less fiddling arround with the
# makefile. It is assumed that tests end with an _test.c
# suffix. All other source files are compiled to a single
# executable, whose main name is given with the TARGET
# macro.
#

# The name of the main executable
TARGET=dijkstracl

# Flags and stuff, change as required
OPTIMIZE=-O3
CFLAGS=-ggdb $(OPTIMIZE) -Wall -Wmissing-prototypes
CPPFLAGS=-ggdb $(OPTIMIZE) -Wall
LDFLAGS=
LDLIBS=-lOpenCL
CC=gcc
CPP=g++

##############################################################
# Normally there shouldn't be a need to modify the following
# lines, expect for bug fixing and new features.

# The sources that make up the main executable. These are
# all files that end with an .c but do not end with _test.c
SRCS=$(filter-out %_test.c,$(wildcard *.c)) 
CPPSRCS=$(filter-out %_test.cpp,$(wildcard *.cpp)) 

# We make up the objects by replacing the .c and .cpp suffixes
# with a .o suffix
OBJS=$(patsubst %.c,%.o,$(SRCS)) $(patsubst %.cpp,%.o,$(CPPSRCS))

# The test sources are assumed to end with _test.c 
TEST_SRCS=$(wildcard *_test.c)

# The test executables (without any suffix)
TESTS=$(patsubst %.c,%,$(TEST_SRCS))

# The dependency files
DEPS=$(SRCS:.c=.d) $(CPPSRCS:.cpp=.d) $(TEST_SRCS:.c=.d)

# If we have any C++ sources, we link with CPP
# For this redfine the internal LINK.o macro
ifneq ($(strip $(CPPSRCS)),)
LINK.o = $(CPP) $(LDFLAGS) $(TARGET_ARCH)
endif

# The first target (all) is allways the default target
.PHONY: all
all: build test

# Our buld target depends on the real target
.PHONY: build
build: $(TARGET)

# Our target is built up from the objects
$(TARGET): $(OBJS)

# Our test target
# 
# Here we instruct make to generate a line with all test
# which are all sequentially executed using the $(foreach)
# macro. We conclude with 'true' because the && construct
# awaits an argument on both sides. The 'true' command
# simply returns a success value
.PHONY: test
test: $(TESTS)
	$(foreach T,$(TESTS), ./$(T) &&) true

# Cleanup all generated files
clean:
	rm -Rf $(TESTS) $(OBJS) $(TARGET) $(DEPS)


# Dependency generation
%.d: %.c
	gcc $< -MM -MP -o$@
%.d: %.cpp
	g++ $< -MM -MP -o$@
	
-include $(DEPS)
