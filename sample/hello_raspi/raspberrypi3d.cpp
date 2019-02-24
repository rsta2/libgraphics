//
// raspberrypi3d.cpp
//
// libgraphics - Accelerated graphics support library for Circle
// Copyright (C) 2019  R. Stange <rsta2@o2online.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "raspberrypi3d.h"
#include "colorbox3d.h"

#define BLACK		CColorBox3D::BlackColor
#define RED		CColorBox3D::RedColor
#define GREEN		CColorBox3D::GreenColor
#define DGREEN		CColorBox3D::DarkGreenColor
#define SILVER		CColorBox3D::SilverColor
#define GOLD		CColorBox3D::GoldColor

#define ORIGIN_OFFSET_X		(-85.0f / 2.0f)
#define ORIGIN_OFFSET_Y		(-1.55f / 2.0f)
#define ORIGIN_OFFSET_Z		(-56.0f / 2.0f)

const TObjectInfo3D CRaspberryPi3D::s_ObjectList[] =	// for the Raspberry Pi 3 Model B+
{
     // Width,	Height,	Depth,	PosX,	PosY,	PosZ,	Color	 (in millimeters)
	{85.f,	1.55f,	56.f,	0.f,	-1.55f,	0.f,	DGREEN}, // Printed Circuit Board
	{7.f,	3.f,	5.f,	6.5f,	0.f,	-0.75f,	SILVER}, // Power Connector (Micro USB)
	{11.f,	1.25f,	11.5f,	1.f,	-2.8f,	22.f,	SILVER}, // Micro SD Card Socket
	{14.f,	6.5f,	10.f,	25.f,	0.f,	-1.f,	SILVER}, // HDMI Connector
	{16.f,	16.f,	12.5f,	70.f,	0.f,	42.f,	SILVER}, // USB Connectors 1
	{16.f,	16.f,	12.5f,	70.f,	0.f,	23.f,	SILVER}, // USB Connectors 2
	{20.f,	13.5f,	15.f,	66.f,	0.f,	2.f,	SILVER}, // Ethernet Connector
	{6.5f,	6.f,	14.f,	50.f,	0.f,	-2.f,	BLACK},	 // Audio Connector
	{3.5f,	5.5f,	22.f,	1.5f,	0.f,	17.f,	BLACK},	 // DSI Connector (Display)
	{3.5f,	5.5f,	22.f,	43.f,	0.f,	0.f,	BLACK},	 // CSI Connector (Camera)
	{50.f,	2.5f,	4.f,	7.f,	0.f,	51.f,	BLACK},	 // GPIO Headers
	{4.f,	2.5f,	4.f,	61.f,	0.f,	45.f,	BLACK},	 // PoE Headers
	{14.f,	2.f,	14.f,	20.f,	0.f,	25.f,	SILVER}, // BCM2837 SoC
	{12.f,	1.f,	12.f,	37.f,	-2.55f,	27.f,	BLACK},	 // ELPIDA 1 GB SDRAM Chip
	{10.f,	2.25f,	12.f,	6.5f,	0.f,	37.f,	SILVER}, // CYW43455 Wireless Chip
	{9.f,	0.75f,	9.f,	57.f,	0.f,	23.f,	BLACK},	 // LAN7515 USB Chip
	{5.f,	0.85f,	5.f,	10.f,	0.f,	13.f,	BLACK},	 // MxL7704 PMIC Chip
	{1.f,	1.f,	2.f,	1.f,	0.f,	7.f,	RED},	 // Power LED
	{1.f,	1.f,	2.f,	1.f,	0.f,	10.f,	GREEN}	 // Activity LED
};

CRaspberryPi3D::CRaspberryPi3D (void)
:	CObjectModel3D (ORIGIN_OFFSET_X, ORIGIN_OFFSET_Y, ORIGIN_OFFSET_Z)
{
	AddObjects (s_ObjectList, sizeof s_ObjectList / sizeof s_ObjectList[0]);

	AddPins (20, 2, 8.f, 2.5f, 51.25f);	// GPIO Pins
	AddPins (2, 2, 62.f, 2.5f, 45.75f);	// PoE Pins
}

void CRaspberryPi3D::AddPins (unsigned nColumns, unsigned nRows,
			      float fPosX, float fPosY, float fPosZ)
{
	TObjectInfo3D Info = {0.25f, 6.f, 0.25f, 0.f, 0.0f, 0.f, GOLD};

	for (unsigned j = 1; j <= nRows; j++)
	{
		float fPosXTemp = fPosX;

		for (unsigned i = 1; i <= nColumns; i++)
		{
			Info.PosX = fPosXTemp;
			Info.PosY = fPosY;
			Info.PosZ = fPosZ;

			AddObjects (&Info, 1);

			fPosXTemp += 2.5f;
		}

		fPosZ += 2.5f;
	}
}
