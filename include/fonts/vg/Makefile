#
# Makefile
#

%.h: %.ttf
	./font2openvg $< $@ $(*F)

font2openvg: font2openvg.cpp
	g++ -I /usr/include/freetype2 -o font2openvg font2openvg.cpp -lfreetype

clean:
	rm -f font2openvg
