
# compiler
CCC = g++

# C++ compiler flags 
CCFLAGS = -g -fPIC -O3 -lm -L./ -lcsparce -pipe -fomit-frame-pointer -msse3
CFLAGS=" -march=native"
CXXFLAGS="${CFLAGS}"
# include directories
INCLUDES = -I. -I/usr/local/include -IIncludes/
CFLAGS=$(DMALLOC)

# library paths
LIBS =$(LIBDMALLOC)  -ltiff  -llzma -ljbig -ljpeg -lz -lm 

# source files.
SRC =  	CSVParser.cpp  simulation.cpp calcul_mat_N.cpp  resolution_systeme.cpp   save_matrice_CSV.cpp Formatgeomatique.cpp Voronoi.cpp Voronoi_fct.cpp

OBJ = $(SRC:.cpp=.o)

OUT = libpfe.a
all: $(OUT)
.SUFFIXES: .cpp

default: dep $(OUT)

.cpp.o:
	$(CCC) -c  $(CFLAGS) $(INCLUDES)   $(CCFLAGS)  $< -o $@ $(LIBS)

$(OUT): $(OBJ)
	ar -x libcsparse.a 
	ar rcs $(OUT) *.o
	rm -f *.o
	mv -f $(OUT) test/
	chmod 777 test/$(OUT)
	
depend: dep

dep:
	$(CCC) $(CFLAGS)  -M $(SRC) $(LIBS) > makedep

clean:
	
	rm -f test/libpfe.a
	
