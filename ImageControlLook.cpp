/*
 * Copyright 2022, Jaidyn Levesque <jadedctrl@teknik.io>
 * All rights reserved. Distributed under the terms of the MIT license.
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
	fCheckBox_Checked.fill(NULL);
	fCheckBox_Unchecked.fill(NULL);
	fSliderThumb.fill(NULL);
	fSliderTriangle.fill(NULL);

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
	if (_Image("Button", ICL_MIDDLE, ICL_NORMAL) == NULL)
		HaikuControlLook::DrawButtonFrame(view, rect, updateRect, base, background, flags, borders);
}


void
ImageControlLook::DrawButtonFrame(BView* view, BRect& rect, const BRect& updateRect, float radius,
	const rgb_color& base, const rgb_color& background, uint32 flags, uint32 borders)
{
	if (_Image("Button", ICL_MIDDLE, ICL_NORMAL) == NULL)
		HaikuControlLook::DrawButtonFrame(view, rect, updateRect, radius, base, background, flags,
			borders);
}


void
ImageControlLook::DrawButtonFrame(BView* view, BRect& rect, const BRect& updateRect,
	float leftTopRadius, float rightTopRadius, float leftBottomRadius, float rightBottomRadius,
	const rgb_color& base, const rgb_color& background, uint32 flags, uint32 borders)
{
	if (_Image("Button", ICL_MIDDLE, ICL_NORMAL) == NULL)
		HaikuControlLook::DrawButtonFrame(view, rect, updateRect, leftTopRadius, rightTopRadius,
			leftBottomRadius, rightBottomRadius, base, background, flags, borders);
}


void
ImageControlLook::DrawButtonBackground(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, uint32 flags, uint32 borders, orientation orientation)
{
	if (!_DrawTiledImage("Button", _FlagsToState(flags), view, rect, updateRect, orientation))
		HaikuControlLook::DrawButtonBackground(view, rect, updateRect, base, flags, borders,
			orientation);
}


void
ImageControlLook::DrawButtonBackground(BView* view, BRect& rect, const BRect& updateRect,
	float radius, const rgb_color& base, uint32 flags, uint32 borders, orientation orientation)
{
	if (!_DrawTiledImage("Button", _FlagsToState(flags), view, rect, updateRect, orientation))
		HaikuControlLook::DrawButtonBackground(view, rect, updateRect, radius, base, flags, borders,
			orientation);
}


void
ImageControlLook::DrawButtonBackground(BView* view, BRect& rect, const BRect& updateRect,
	float leftTopRadius, float rightTopRadius, float leftBottomRadius, float rightBottomRadius,
	const rgb_color& base, uint32 flags, uint32 borders, orientation orientation)
{
	if (!_DrawTiledImage("Button", _FlagsToState(flags), view, rect, updateRect, orientation))
		HaikuControlLook::DrawButtonBackground(view, rect, updateRect, leftTopRadius,
			rightTopRadius,leftBottomRadius, rightBottomRadius, base, flags, borders, orientation);
}


void
ImageControlLook::DrawCheckBox(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, uint32 flags)
{
	bool drawn = false;
	if (((BControl*)view)->Value() == B_CONTROL_ON)
		drawn = _DrawImage("CheckBox-Checked", _FlagsToState(flags & ~B_ACTIVATED), view, rect);
	else
		drawn = _DrawImage("CheckBox-Unchecked", _FlagsToState(flags), view, rect);

	if (!drawn)
		HaikuControlLook::DrawCheckBox(view, rect, updateRect, base, flags);
}


void
ImageControlLook::DrawSliderThumb(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, uint32 flags, orientation orientation)
{
	if (!_DrawImage("SliderThumb", _FlagsToState(flags), view, rect, orientation))
		HaikuControlLook::DrawSliderThumb(view, rect, updateRect, base, flags, orientation);
}


void
ImageControlLook::DrawSliderTriangle(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, uint32 flags, orientation orientation)
{
	if (!_DrawImage("SliderTriangle", _FlagsToState(flags), view, rect, orientation))
		HaikuControlLook::DrawSliderTriangle(view, rect, updateRect, base, flags, orientation);
}


void
ImageControlLook::DrawSliderTriangle(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, const rgb_color& fill, uint32 flags, orientation orientation)
{
	if (!_DrawImage("SliderTriangle", _FlagsToState(flags), view, rect, orientation))
		HaikuControlLook::DrawSliderTriangle(view, rect, updateRect, base, fill, flags,
			orientation);
}


bool
ImageControlLook::_DrawImage(const char* type, uint32 state, BView* view, BRect rect,
	orientation orientation)
{
	BBitmap* image = _Image(type, state);
	if (image != NULL && orientation == B_HORIZONTAL) {
		view->SetDrawingMode(B_OP_ALPHA);
		view->DrawBitmap(image, rect);
		return true;
	}
	return false;
}


bool
ImageControlLook::_DrawTiledImage(const char* type, uint32 state, BView* view, BRect rect,
	BRect updateRect, orientation orientation)
{
	BBitmap* tile = _Image(type, state, ICL_MIDDLE);
	BBitmap* left = _Image(type, state, ICL_LEFT);
	BBitmap* right = _Image(type, state, ICL_RIGHT);

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
		if (tileRect.Intersects(updateRect))
			view->DrawBitmap(tile, tileRect);
	}
	tileRect.right = maxX;
	tileRect.left = maxX - sliceWidth;
	if (tileRect.Intersects(updateRect))
		view->DrawBitmap(tile, tileRect);

	BRect sideRect(0, 0, minX, rect.Height());
	if (left != NULL && sideRect.Intersects(updateRect))
		view->DrawBitmap(left, sideRect);

	sideRect.left = maxX;
	sideRect.right = view->Bounds().right;
	if (right != NULL && sideRect.Intersects(updateRect))
		view->DrawBitmap(right, sideRect);

	return true;
}


BBitmap*
ImageControlLook::_Image(const char* type, uint32 state, uint32 side)
{
	SidedImages* sideList = NULL;
	UnsidedImages* nosideList = NULL;
	BBitmap* image = NULL;

	if (strcmp(type, "Button") == 0)
		sideList = &fButton;
	else if (strcmp(type, "CheckBox-Unchecked") == 0)
		nosideList = &fCheckBox_Unchecked;
	else if (strcmp(type, "CheckBox-Checked") == 0)
		nosideList = &fCheckBox_Checked;
	else if (strcmp(type, "SliderThumb") == 0)
		nosideList = &fSliderThumb;
	else if (strcmp(type, "SliderTriangle") == 0)
		nosideList = &fSliderTriangle;

	if (sideList != NULL && (*sideList)[side][state] == NULL)
		(*sideList)[side][state] = BTranslationUtils::GetBitmapFile(_ImagePath(type, state, side));
	if (sideList != NULL)
		image = (*sideList)[side][state];

	if (nosideList != NULL && (*nosideList)[state] == NULL)
		(*nosideList)[state] = BTranslationUtils::GetBitmapFile(_ImagePath(type, state));
	if (nosideList != NULL)
		image = (*nosideList)[state];

	return image;
}


const char*
ImageControlLook::_ImagePath(const char* type, uint32 state, uint32 side)
{
	BString leaf = kStates[state];
	leaf << kSides[side];

	BPath imgPath(fImageRoot.Path());
	imgPath.Append(type);
	imgPath.Append(leaf);
	printf("[ImageControlLook] Searching for %s…\n", imgPath.Path());
	return imgPath.Path();
}


uint32
ImageControlLook::_FlagsToState(uint32 flags)
{
	uint32 state = ICL_NORMAL;
	if (flags & B_DISABLED)
		state = ICL_DISABLED;
	else if (flags & (B_ACTIVATED | B_PARTIALLY_ACTIVATED | B_CLICKED))
		state = ICL_ACTIVATED;
	else if (flags & (B_HOVER | B_FOCUSED))
		state = ICL_HOVER;
	return state;
}


extern "C" BControlLook* (instantiate_control_look)(image_id id)
{
	return new (std::nothrow)ImageControlLook(id);
}
