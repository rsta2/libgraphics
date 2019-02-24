//
// vgfont.h
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
#ifndef _graphics_vgfont_h
#define _graphics_vgfont_h

#include <VG/openvg.h>

#define MAKE_FONT(prefix, pt)	prefix ## _glyphPoints,			\
				prefix ## _glyphPointIndices,		\
				prefix ## _glyphInstructions,		\
				prefix ## _glyphInstructionIndices,	\
				prefix ## _glyphInstructionCounts,	\
				prefix ## _glyphAdvances,		\
				prefix ## _characterMap,		\
				prefix ## _glyphCount,			\
				prefix ## _descender_height,		\
				prefix ## _font_height,			\
				pt

class CVgFont		/// OpenVG text processing
{
private:
	static const int MAXFONTPATH = 256;

public:
	/// \param fPointSize Point size of the font to be displayed
	/// \note Use MAKE_FONT() to supply font parameters
	CVgFont (const int *pPoints, const int *pPointIndices, const unsigned char *pInstructions,
		 const int *pInstructionIndices, const int *pInstructionCounts,
		 const int *pAdvances, const short *pCharacterMap, int nCount,
		 int nDescenderHeight, int nFontHeight, float fPointSize);
	~CVgFont (void);

	/// \return Font's height
	VGfloat GetTextHeight (void) const;
	/// \return Font's depth (how far under the baseline it goes)
	VGfloat GetTextDepth (void) const;
	/// \return Width of a text string
	VGfloat GetTextWidth (const char *pString);

	/// \brief Renders a string of text at a specified location
	/// \param PaintModes Bit field of VG_FILL_PATH and/or VG_STROKE_PATH
	/// \return Next X position after the rendered text
	VGfloat TextLeft (VGfloat fX, VGfloat fY, const char *pString,
		          VGbitfield PaintModes = VG_FILL_PATH);
	/// \brief Draws text, centered on (x, y)
	/// \param PaintModes Bit field of VG_FILL_PATH and/or VG_STROKE_PATH
	/// \return Next X position after the rendered text
	VGfloat TextCenter (VGfloat fX, VGfloat fY, const char *pString,
		            VGbitfield PaintModes = VG_FILL_PATH);
	/// \brief Draws text, with its end aligned to (x, y)
	/// \param PaintModes Bit field of VG_FILL_PATH and/or VG_STROKE_PATH
	/// \return Next X position after the rendered text
	VGfloat TextRight (VGfloat fX, VGfloat fY, const char *pString,
		           VGbitfield PaintModes = VG_FILL_PATH);

private:
	const short *m_pCharacterMap;
	const int *m_pGlyphAdvances;
	int m_nCount;
	int m_nDescenderHeight;
	int m_nFontHeight;
	float m_fPointSize;

	VGFont m_Font;
};

#endif
