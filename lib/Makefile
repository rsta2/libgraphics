#
# Makefile
#

LIBGRAPHICSHOME = ..

OBJS	= bcmdisplay.o bcmdisplayelement.o eglrenderingcontext.o \
	  vgsimpledrawing.o vgdrawingcontext.o vgpath.o vgpaint.o vgfont.o \
	  graphicsthread.o

libgraphics.a: $(OBJS)
	@echo "  AR    $@"
	@rm -f $@
	@$(AR) cr $@ $(OBJS)

include $(LIBGRAPHICSHOME)/Rules.mk
