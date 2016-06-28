#
# 'make depend' uses makedepend to automatically generate dependencies
#               (dependencies are added to end of Makefile)
# 'make'        build executable files
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = g++

# define any compile-time flags
CPPLAGS = -std=c++11 -Wall -O2 -Wstring-compare

# define any directories containing header files other than /usr/include
#
#INCLUDES = -I/home/newhall/include  -I../include

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
#LFLAGS = -L/home/newhall/lib  -L../lib
LDFLAGS =

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lntl -lgmp -lm

# define the C source files
#SRCS = $(wildcard *.cpp)
SRCS1 = prime_math.cpp prime_lib.cpp primecheck.cpp
SRCS2 = prime_math.cpp prime_lib.cpp primegen.cpp
SRCS3 = prime_math.cpp prime_lib.cpp rsa_lib.cpp keygen.cpp
SRCS4 = prime_math.cpp prime_lib.cpp rsa_lib.cpp encrypt.cpp
SRCS5 = prime_math.cpp prime_lib.cpp rsa_lib.cpp decrypt.cpp

# define the C object files
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS1 = $(SRCS1:.cpp=.o)
OBJS2 = $(SRCS2:.cpp=.o)
OBJS3 = $(SRCS3:.cpp=.o)
OBJS4 = $(SRCS4:.cpp=.o)
OBJS5 = $(SRCS5:.cpp=.o)

# define the executable file
PROGRAM1 = primecheck
PROGRAM2 = primegen
PROGRAM3 = keygen
PROGRAM4 = encrypt
PROGRAM5 = decrypt


#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:    $(PROGRAM1) $(PROGRAM2) $(PROGRAM3) $(PROGRAM4) $(PROGRAM5)
		@echo $(PROGRAM1) $(PROGRAM2) $(PROGRAM3) $(PROGRAM4) $(PROGRAM5) have been compiled

$(PROGRAM1): $(OBJS1)
		$(CC) $(CPPLAGS) $(INCLUDES) -o $(PROGRAM1) $(OBJS1) $(LDFLAGS) $(LIBS)

$(PROGRAM2): $(OBJS2)
		$(CC) $(CPPLAGS) $(INCLUDES) -o $(PROGRAM2) $(OBJS2) $(LDFLAGS) $(LIBS)

$(PROGRAM3): $(OBJS3)
		$(CC) $(CPPLAGS) $(INCLUDES) -o $(PROGRAM3) $(OBJS3) $(LDFLAGS) $(LIBS)

$(PROGRAM4): $(OBJS4)
		$(CC) $(CPPLAGS) $(INCLUDES) -o $(PROGRAM4) $(OBJS4) $(LDFLAGS) $(LIBS)

$(PROGRAM5): $(OBJS5)
		$(CC) $(CPPLAGS) $(INCLUDES) -o $(PROGRAM5) $(OBJS5) $(LDFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
.cpp.o:
		$(CC) $(CPPLAGS) $(INCLUDES) -c $<  -o $@

clean:
		$(RM) *.o *~ $(PROGRAM1) $(PROGRAM2) $(PROGRAM3) $(PROGRAM4) $(PROGRAM5)

depend: $(SRCS)
		makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
