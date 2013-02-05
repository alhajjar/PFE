# source files.
SRC = $(wildcard *.cpp)

OBJ = $(SRC:.cpp=.o)

OUT = interface

# include directories
INCLUDES = -IIncludes/ -I/usr/local/include

# C++ compiler flags
CCFLAGS = -g -O3 -I/usr/include/gtkmm-2.4 -I/usr/lib/x86_64-linux-gnu/gtkmm-2.4/include -I/usr/include/atkmm-1.6 -I/usr/include/giomm-2.4 -I/usr/lib/x86_64-linux-gnu/giomm-2.4/include -I/usr/include/pangomm-1.4 -I/usr/lib/x86_64-linux-gnu/pangomm-1.4/include -I/usr/include/gtk-2.0 -I/usr/include/gtk-unix-print-2.0 -I/usr/include/gdkmm-2.4 -I/usr/lib/x86_64-linux-gnu/gdkmm-2.4/include -I/usr/include/atk-1.0 -I/usr/include/glibmm-2.4 -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/sigc++-2.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include -I/usr/include/cairomm-1.0 -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0/  -lgtkmm-2.4 -latkmm-1.6 -lgdkmm-2.4 -lgiomm-2.4 -lpangomm-1.4 -lgtk-x11-2.0 -lglibmm-2.4 -lcairomm-1.0 -lsigc-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lglib-2.0  -L/usr/local/lib -lshp -L. -lpfe


# compiler
CCC = g++

# library paths
LIBS = -L.  -lpfe -L/usr/local/lib -ltiff  -lm  -llzma -ljbig -ljpeg -lz 
 
all: $(OUT)
.SUFFIXES: .cpp

default: dep $(OUT)

.cpp.o:
	@$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@
	@echo "Generation de : "$@
	@echo " "
$(OUT): $(OBJ)
	@g++  *.o -o interface $(CCFLAGS) -L/usr/local/lib -lshp -ltiff -L. -lpfe
	@echo " "
	@echo "interface successfully created"
	@echo " "

depend: dep

dep:
	makedepend -- $(CFLAGS) -- $(INCLUDES) $(SRC) $(LIBS)

clean:
	rm -f $(OBJ) Makefile.bak 






	
