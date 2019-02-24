//
// vgfont.cpp
//
// This is based on:
//	libshapes: high-level OpenVG API
//		https://github.com/ajstarks/openvg
//		by Anthony Starks (ajstarks@gmail.com)
//	Additional outline / windowing functions
//		by Paeryn (github.com/paeryn),
// which is based itself on:
// 	http://web.archive.org/web/20070808195131/
//		http://developer.hybrid.fi/font2openvg/renderFont.cpp.txt
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
#include <graphics/vgfont.h>
#include <assert.h>

CVgFont::CVgFont (const int *pPoints, const int *pPointIndices, const unsigned char *pInstructions,
		  const int *pInstructionIndices, const int *pInstructionCounts,
		  const int *pAdvances, const short *pCharacterMap, int nCount,
		  int nDescenderHeight, int nFontHeight, float fPointSize)
:	m_pCharacterMap (pCharacterMap),
	m_pGlyphAdvances (pAdvances),
	m_nCount (nCount),
	m_nDescenderHeight (nDescenderHeight),
	m_nFontHeight (nFontHeight),
	m_fPointSize (fPointSize),
	m_Font (VG_INVALID_HANDLE)
{
	assert (m_nCount <= MAXFONTPATH);
	assert (m_fPointSize >= 4.0f);

	m_Font = vgCreateFont (m_nCount);
	assert (m_Font != VG_INVALID_HANDLE);

	for (int nGlyph = 0; nGlyph < m_nCount; nGlyph++)
	{
		VGPath Path = VG_INVALID_HANDLE;
		if (pInstructionCounts[nGlyph] > 0)
		{
			Path = vgCreatePath (VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_S_32,
					     m_fPointSize / 65536.0f, 0.0f, 0, 0,
					     VG_PATH_CAPABILITY_ALL);
			assert (Path != VG_INVALID_HANDLE);

			vgAppendPathData (Path, pInstructionCounts[nGlyph],
					  &pInstructions[pInstructionIndices[nGlyph]],
					  &pPoints[pPointIndices[nGlyph] * 2]);
			assert (vgGetError () == VG_NO_ERROR);
		}

		VGfloat Origin[2] = {0.0f, 0.0f};
		VGfloat Escape[2] = {m_fPointSize * pAdvances[nGlyph] / 65536.0f, 0.0f};

		vgSetGlyphToPath (m_Font, (VGuint) nGlyph, Path, VG_FALSE, Origin, Escape);
		assert (vgGetError () == VG_NO_ERROR);

		if (Path != VG_INVALID_HANDLE)
		{
			vgDestroyPath (Path);
		}
	}
}

CVgFont::~CVgFont (void)
{
	assert (m_Font != VG_INVALID_HANDLE);

	for (int nGlyph = 0; nGlyph < m_nCount; nGlyph++)
	{
		vgClearGlyph (m_Font, (VGuint) nGlyph);
		assert (vgGetError () == VG_NO_ERROR);
	}

	vgDestroyFont (m_Font);
	assert (vgGetError () == VG_NO_ERROR);
}

VGfloat CVgFont::GetTextHeight (void) const
{
	return (m_nFontHeight * m_fPointSize) / 65536.0f;
}

VGfloat CVgFont::GetTextDepth (void) const
{
	return -(m_nDescenderHeight * m_fPointSize) / 65536.0f;
}

VGfloat CVgFont::GetTextWidth (const char *pString)
{
	assert (pString != 0);

	VGfloat fResult = 0.0f;

	VGuint nChar;
	const unsigned char *p = (unsigned char *) pString;
	while ((nChar = *p++) != 0)
	{
		assert (nChar < MAXFONTPATH);
		int nGlyph = m_pCharacterMap[nChar];
		if (nGlyph != -1)
		{
			fResult += m_fPointSize * m_pGlyphAdvances[nGlyph] / 65536.0f;
		}
	}

	return fResult;
}

VGfloat CVgFont::TextLeft (VGfloat X, VGfloat Y, const char *pString, VGbitfield PaintModes)
{
	assert (pString != 0);
	if (*pString == '\0')
	{
		return 0.0f;
	}

	VGfloat Origin[2] = {X, Y};
	vgSetfv (VG_GLYPH_ORIGIN, 2, Origin);
	assert (vgGetError () == VG_NO_ERROR);

	const int MaxCount = 500;
	VGuint Indices[MaxCount];
	VGint nCount = 0;

	VGuint nChar;
	const unsigned char *p = (unsigned char *) pString;
	while (   (nChar = *p++) != 0
	       && nCount < MaxCount)
	{
		assert (nChar < MAXFONTPATH);
		int nGlyph = m_pCharacterMap[nChar];
		if (nGlyph != -1)
		{
			Indices[nCount++] = (VGuint) nGlyph;
		}
	}

	vgDrawGlyphs (m_Font, nCount, Indices, 0, 0, PaintModes, VG_TRUE);
	assert (vgGetError () == VG_NO_ERROR);

	vgGetfv (VG_GLYPH_ORIGIN, 2, Origin);
	assert (vgGetError () == VG_NO_ERROR);

	return Origin[0];
}

VGfloat CVgFont::TextCenter (VGfloat X, VGfloat Y, const char *pString, VGbitfield PaintModes)
{
	return TextLeft (X - (GetTextWidth (pString) / 2.0f), Y, pString, PaintModes);
}

VGfloat CVgFont::TextRight (VGfloat X, VGfloat Y, const char *pString, VGbitfield PaintModes)
{
	return TextLeft (X - GetTextWidth (pString), Y, pString, PaintModes);
}
