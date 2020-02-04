#
# Rules.mk
#

LIBGRAPHICSHOME ?= ../..

-include $(LIBGRAPHICSHOME)/Config.mk

CIRCLEHOME ?= $(LIBGRAPHICSHOME)/circle

INCLUDE += -I $(LIBGRAPHICSHOME)/include

include $(CIRCLEHOME)/Rules.mk

-include $(DEPS)
