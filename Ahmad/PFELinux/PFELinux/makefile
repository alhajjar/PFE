# source files.
SRC = $(wildcard *.cpp)

OBJ = $(SRC:.cpp=.o)

OUT = ../ihmlignecommande/libpfe.a

# include directories
INCLUDES = -IIncludes/ -I/usr/local/include -I/usr/include

# C++ compiler flags
CCFLAGS = -g -fPIC -O3  -pipe -fomit-frame-pointer -msse3 -Wall

# compiler
CCC = g++

# library paths
LIBS = -L. -L/usr/local/lib -ltiff  -lm  -llzma -ljbig -ljpeg -lz -lcsparse -L/usr/lib/x86_64-linux-gnu -lshp
 
all: $(OUT)
.SUFFIXES: .cpp

default: dep $(OUT)

.cpp.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@
	@echo " "
$(OUT): $(OBJ)
	ar -x libcsparse.a
	ar rcs $(OUT) *.o libtiff.so 
	cp ../ihmlignecommande/libpfe.a ../ihminterface/libpfe.a 
	@echo " "
	@echo "libpfe.a successfully created"
	@echo " "

depend: dep

dep:
	makedepend -- $(CFLAGS) -- $(INCLUDES) $(SRC) $(LIBS)

clean:
	rm -f $(OBJ) *.o Makefile.bak 






	
