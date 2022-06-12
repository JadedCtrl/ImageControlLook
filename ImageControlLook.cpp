/*
 * Copyright 2021 Haiku, Inc.
 * Copyright 2022, Jaidyn Levesque <jadedctrl@teknik.io>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 * Authors:
 *		Stephan Aßmus, superstippi@gmx.de
 *		John Scipione, jscipione@gmail.com
 *		Nahuel Tello, ntello@unarix.com.ar
 */

#include "ImageControlLook.h"

#include <cstdio>

#include <TranslationUtils.h>


ImageControlLook::ImageControlLook(image_id id)
	:
	HaikuControlLook()
{
	for (int i = 0; i < 3; i++)
		fButton[i].fill(NULL);
	fImageRoot = BPath("/boot/home/Desktop/projects/haiku/ImageControlLook/data/ImageThemes/OS-X-Leopard/");
}



ImageControlLook::~ImageControlLook()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 6; j++)
			delete fButton[i][j];
}


// No need to draw button frames (since the button images should include them)
void
ImageControlLook::DrawButtonFrame(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, const rgb_color& background, uint32 flags, uint32 borders)
{
	if (_Image("Button", ICL_MIDDLE, ICL_ACTIVE) == NULL)
		HaikuControlLook::DrawButtonFrame(view, rect, updateRect, base, background, flags, borders);
}


void
ImageControlLook::DrawButtonFrame(BView* view, BRect& rect, const BRect& updateRect, float radius,
	const rgb_color& base, const rgb_color& background, uint32 flags, uint32 borders)
{
	if (_Image("Button", ICL_MIDDLE, ICL_ACTIVE) == NULL)
		HaikuControlLook::DrawButtonFrame(view, rect, updateRect, radius, base, background, flags,
			borders);
}


void
ImageControlLook::DrawButtonFrame(BView* view, BRect& rect, const BRect& updateRect,
	float leftTopRadius, float rightTopRadius, float leftBottomRadius, float rightBottomRadius,
	const rgb_color& base, const rgb_color& background, uint32 flags, uint32 borders)
{
	if (_Image("Button", ICL_MIDDLE, ICL_ACTIVE) == NULL)
		HaikuControlLook::DrawButtonFrame(view, rect, updateRect, leftTopRadius, rightTopRadius,
			leftBottomRadius, rightBottomRadius, base, background, flags, borders);
}


void
ImageControlLook::DrawButtonBackground(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, uint32 flags, uint32 borders, orientation orientation)
{
	if (!_DrawButtonBackground(view, rect, updateRect, false, flags, orientation))
		HaikuControlLook::DrawButtonBackground(view, rect, updateRect, base, flags, borders,
			orientation);
}


void
ImageControlLook::DrawButtonBackground(BView* view, BRect& rect, const BRect& updateRect,
	float radius, const rgb_color& base, uint32 flags, uint32 borders, orientation orientation)
{
	if (!_DrawButtonBackground(view, rect, updateRect, false, flags, orientation))
		HaikuControlLook::DrawButtonBackground(view, rect, updateRect, radius, base, flags, borders,
			orientation);
}


void
ImageControlLook::DrawButtonBackground(BView* view, BRect& rect, const BRect& updateRect,
	float leftTopRadius, float rightTopRadius, float leftBottomRadius, float rightBottomRadius,
	const rgb_color& base, uint32 flags, uint32 borders, orientation orientation)
{
	if (!_DrawButtonBackground(view, rect, updateRect, false, flags, orientation))
		HaikuControlLook::DrawButtonBackground(view, rect, updateRect, leftTopRadius,
			rightTopRadius,leftBottomRadius, rightBottomRadius, base, flags, borders, orientation);
}


bool
ImageControlLook::_DrawButtonBackground(BView* view, BRect& rect, const BRect& updateRect,
	bool popupIndicator, uint32 flags, orientation orientation)
{
	uint32 state = ICL_ACTIVE;
	if (flags & B_DISABLED)
		state = ICL_DISABLED;
	else if (flags & B_ACTIVATED)
		state = ICL_ACTIVATED;
	else if (flags & B_HOVER)
		state = ICL_HOVER;

	BBitmap* tile = _Image("Button", ICL_MIDDLE, state);
	BBitmap* left = _Image("Button", ICL_LEFT, state);
	BBitmap* right = _Image("Button", ICL_RIGHT, state);

	if (orientation == B_VERTICAL || tile == NULL)
		return false;

	float minX = 0;
	float maxX = rect.Width();
	if (left != NULL)
		minX = left->Bounds().Width();
	if (right != NULL)
		maxX = rect.Width() - right->Bounds().Width();

	float heightRatio = rect.Height() / tile->Bounds().Height();
	float sliceWidth = heightRatio * tile->Bounds().Width();

	view->SetDrawingMode(B_OP_ALPHA);

	BRect tileRect;
	tileRect.top = 0;
	tileRect.bottom = rect.Height();
	for (float left = minX; left + sliceWidth < maxX; left += sliceWidth) {
		tileRect.left = left;
		tileRect.right = left + sliceWidth;
		view->DrawBitmap(tile, tileRect);
	}
	tileRect.right = maxX;
	tileRect.left = maxX - sliceWidth;
	view->DrawBitmap(tile, tileRect);

	BRect sideRect(0, 0, minX, rect.Height());
	if (left != NULL)
		view->DrawBitmap(left, sideRect);

	sideRect.left = maxX;
	sideRect.right = view->Bounds().right;
	if (right != NULL)
		view->DrawBitmap(right, sideRect);

	return true;
}


BBitmap*
ImageControlLook::_Image(const char* type, uint32 side, uint32 state)
{
	if (fButton[side][state] == NULL)
		fButton[side][state] = BTranslationUtils::GetBitmapFile(_ImagePath(type, side, state));
	return fButton[side][state];
}


const char*
ImageControlLook::_ImagePath(const char* type, uint32 side, uint32 state)
{
	BString leaf = kStates[state];
	leaf << kSides[side];

	BPath imgPath(fImageRoot.Path());
	imgPath.Append(type);
	imgPath.Append(leaf);
	printf("[ImageControlLook] Loaded %s\n", imgPath.Path());
	return imgPath.Path();
}


extern "C" BControlLook* (instantiate_control_look)(image_id id)
{
	return new (std::nothrow)ImageControlLook(id);
}
