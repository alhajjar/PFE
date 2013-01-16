
# compiler
CCC = g++

# C++ compiler flags 
CCFLAGS = -g -fPIC -O3 

# include directories
INCLUDES = -I. -I/usr/local/include -IIncludes/ 

LFLAGS = -L.

# library paths
LIBS = -lcsparce -lm

# source files.
SRC =  	CSVParser.cpp  simulation.cpp calcul_mat_N.cpp  resolution_systeme.cpp   save_matrice_CSV.cpp Ascii.cpp

OBJ = $(SRC:.cpp=.o)

OUT = libpfe.a
all: $(OUT)
.SUFFIXES: .cpp

default: dep $(OUT)

.cpp.o:
	$(CCC) -c   $(INCLUDES)  $(CCFLAGS)  $< -o $@  $(LFLAGS) $(LIBS)

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
	
