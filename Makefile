GTKMM=-mms-bitfields -Ic:/gtkmm/include/gtkmm-2.4 -Ic:/gtkmm/lib/gtkmm-2.4/include -Ic:/gtkmm/include/atkmm-1.6 -Ic:/gtkmm/include/giomm-2.4 -Ic:/gtkmm/lib/giomm-2.4/include -Ic:/gtkmm/include/pangomm-1.4 -Ic:/gtkmm/lib/pangomm-1.4/include -Ic:/gtkmm/include/gtk-2.0 -Ic:/gtkmm/include/gdkmm-2.4 -Ic:/gtkmm/lib/gdkmm-2.4/include -Ic:/gtkmm/include/atk-1.0 -Ic:/gtkmm/include/glibmm-2.4 -Ic:/gtkmm/lib/glibmm-2.4/include -Ic:/gtkmm/include/glib-2.0 -Ic:/gtkmm/lib/glib-2.0/include -Ic:/gtkmm/include/sigc++-2.0 -Ic:/gtkmm/lib/sigc++-2.0/include -Ic:/gtkmm/include/cairomm-1.0 -Ic:/gtkmm/lib/cairomm-1.0/include -Ic:/gtkmm/include/pango-1.0 -Ic:/gtkmm/include/cairo -Ic:/gtkmm/include -Ic:/gtkmm/include/freetype2 -Ic:/gtkmm/include/libpng14 -Ic:/gtkmm/lib/gtk-2.0/include -Ic:/gtkmm/include/gdk-pixbuf-2.0  -Lc:/gtkmm/lib -Lc:/devel/dist/win32/libpng-1.4.3-1/lib -lgtkmm-2.4 -latkmm-1.6 -lgdkmm-2.4 -lgiomm-2.4 -lpangomm-1.4 -lgtk-win32-2.0 -lglibmm-2.4 -lcairomm-1.0 -lsigc-2.0 -lgdk-win32-2.0 -latk-1.0 -lgio-2.0 -lpangowin32-1.0 -lgdi32 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lpng14 -lpango-1.0 -lcairo -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lglib-2.0 -lintl  

all: reset interface 

interface: interface.cpp Dessin.o ControleurAffichage.o
	g++ interface.cpp Dessin.o ControleurAffichage.o -o interface.exe $(GTKMM)
	
Dessin.o: Dessin.cpp
	g++ -c Dessin.cpp $(GTKMM)

reset:
	rm *.o
	
ControleurAffichage.o: ControleurAffichage.cpp
	g++ -c ControleurAffichage.cpp $(GTKMM)