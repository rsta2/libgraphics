#
# Makefile
#

LIBGRAPHICSHOME = ../..

OBJS	= main.o kernel.o raspberrypidemo.o raspberrypi3d.o \
	  objectviewer3d.o objectmodel3d.o colorbox3d.o

LIBS	= $(LIBGRAPHICSHOME)/lib/libgraphics.a \
	  $(CIRCLEHOME)/addon/vc4/interface/bcm_host/libbcm_host.a \
	  $(CIRCLEHOME)/addon/vc4/interface/khronos/libkhrn_client.a \
	  $(CIRCLEHOME)/addon/vc4/interface/vmcs_host/libvmcs_host.a \
	  $(CIRCLEHOME)/addon/vc4/interface/vcos/libvcos.a \
	  $(CIRCLEHOME)/addon/vc4/vchiq/libvchiq.a \
	  $(CIRCLEHOME)/addon/linux/liblinuxemu.a \
	  $(CIRCLEHOME)/lib/sched/libsched.a \
	  $(CIRCLEHOME)/lib/libcircle.a

include $(LIBGRAPHICSHOME)/Rules.mk
