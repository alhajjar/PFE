
# compiler
CCC = g++

prefix=/usr/local
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir=${prefix}/include

# C++ compiler flags 
CCFLAGS = -g -fPIC -O3  -pipe -fomit-frame-pointer -msse3 
# include directories
INCLUDES = -I. -IIncludes/ -I${includedir}

# library paths
LIBS = -L${libdir} -L./ -L/usr/lib
DEPENDLIBS =  -ltiff -llzma -ljbig -ljpeg -lz -lm

# source files.
SRC =$(wildcard *.cpp)

OBJ = $(SRC:.cpp=.o)

OUT = libpfe.a
all: $(OUT)
.SUFFIXES: .cpp

default: dep $(OUT)

.cpp.o:
	$(CCC) -c  $(INCLUDES)   $(CCFLAGS)  $< -o $@ $(LIBS) $(DEPENDLIBS)

$(OUT): $(OBJ)
	ar -x libcsparse.a 
	ar rcs $(OUT) *.o
	rm -f *.o
	mv -f $(OUT) test/
	chmod 777 test/$(OUT)
	
depend: dep

dep:
	$(CCC) $(OUT)  -M $(SRC)  > makedep

clean:
	
	rm -f test/libpfe.a
install:
	
