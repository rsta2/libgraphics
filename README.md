libgraphics
===========

Accelerated graphics support library for Circle

Status
------

Far from complete

Features
--------

* Unified rendering context initialization for OpenVG and  OpenGL ES
* Text display and font handling for OpenVG
* Unified graphics thread handling

Getting
-------

Normally you need a *git* client to get the libgraphics source code. Go to the directory where you want to place libgraphics on your hard disk and enter:

	git clone https://github.com/rsta2/libgraphics.git libgraphics
	cd libgraphics
	git submodule update --init

This will place the source code in the subdirectory *libgraphics/* and clones the submodule *circle* into the *libgraphics/circle/* subdirectory.

Building
--------

libgraphics uses the Circle bare metal build environment for the Raspberry Pi. You need an appropriate compiler toolchain for ARM processors to build it. Have a look at the Circle *README.md* file (in *circle/*) for further information on this (section *Building*). The build information herein is for Linux hosts only. For building on other hosts you have to adapt some script files.

When the toolchain is installed on your computer you can build libgraphics using the following commands:

	./configure 2 arm-none-eabi-
	./makeall clean
	./makeall

The `configure` command writes a *Config.mk* file for Circle. "2" is the major revision number of your Raspberry Pi (1, 2 or 3). The second (optional) parameter is the prefix of the commands of your toolchain and can be preceded with a path. Do not forget the dash at the end of the prefix!

If the build was successful, you find the library file of libgraphics in the *lib/* subdirectory with the name *libgraphics.a*.

Samples
-------

If you wnat to try one of the provided sample programs, now go its subdirectory in *sample/* and do:

	make clean
	make

The built kernel image can be installed as described in the main Circle *README.md* file.
