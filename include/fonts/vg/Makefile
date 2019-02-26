#
# Makefile
#

GZ_FONTS  := $(wildcard *.gz)
TTF_FONTS := $(wildcard *.ttf)

all: $(subst .gz,.h,$(GZ_FONTS)) $(subst .ttf,.h,$(TTF_FONTS))

%.h: %.gz
	@echo "  UNZIP $@"
	@gunzip -c $< > $@

%.h: %.ttf font2openvg
	@echo "  FONT  $@"
	@./font2openvg $< $@ $(*F) > /dev/null

font2openvg: font2openvg.cpp
	@echo "  TOOL  $@"
	@g++ -I /usr/include/freetype2 -o font2openvg font2openvg.cpp -lfreetype

clean:
	rm -f *.h font2openvg
