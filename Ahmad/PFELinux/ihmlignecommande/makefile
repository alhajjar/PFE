# source files.
SRC = $(wildcard *.cpp)

OBJ = $(SRC:.cpp=.o)

OUT = executable

# include directories
INCLUDES = -IIncludes/ -I/usr/local/include

# C++ compiler flags
CCFLAGS = -g -O3 


# compiler
CCC = g++

# library paths
LIBS = -L.  -lpfe
 
all: $(OUT)
.SUFFIXES: .cpp

default: dep $(OUT)

.cpp.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@
	@echo " "
$(OUT): $(OBJ)
	g++  *.o -o executable $(CCFLAGS) -L. -lpfe
	@echo " "
	@echo "executable successfully created"
	@echo " "

depend: dep

dep:
	makedepend -- $(CFLAGS) -- $(INCLUDES) $(SRC) $(LIBS)

clean:
	rm -f $(OBJ) Makefile.bak 






	
