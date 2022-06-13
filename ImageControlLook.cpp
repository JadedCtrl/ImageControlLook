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
	for (int orient = 0; orient < 2; orient++) {
		for (int side = 0; side < 3; side++)
			fButton[orient][side].fill(NULL);

		fCheckBox_Checked[orient].fill(NULL);
		fCheckBox_Unchecked[orient].fill(NULL);
		fRadioButton_Checked[orient].fill(NULL);
		fRadioButton_Unchecked[orient].fill(NULL);
		fSliderThumb[orient].fill(NULL);
		fSliderTriangle[orient].fill(NULL);
	}

	fImageRoot = BPath("/boot/home/Desktop/projects/haiku/ImageControlLook/data/ImageThemes/Akva/");
}



ImageControlLook::~ImageControlLook()
{
	for (int orient = 0; orient < 2; orient++)
		for (int state = 0; state < 5; state++) {
			for (int side = 0; side < 3; side++)
				delete fButton[orient][side][state];

			delete fCheckBox_Checked[orient][state];
			delete fCheckBox_Unchecked[orient][state];
			delete fRadioButton_Checked[orient][state];
			delete fRadioButton_Unchecked[orient][state];
			delete fSliderThumb[orient][state];
			delete fSliderTriangle[orient][state];
		}
}


// No need to draw button frames (since the button images should include them)
void
ImageControlLook::DrawButtonFrame(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, const rgb_color& background, uint32 flags, uint32 borders)
{
	if (_Image("Button", ICL_NORMAL, ICL_MIDDLE) == NULL)
		HaikuControlLook::DrawButtonFrame(view, rect, updateRect, base, background, flags, borders);
}


void
ImageControlLook::DrawButtonFrame(BView* view, BRect& rect, const BRect& updateRect, float radius,
	const rgb_color& base, const rgb_color& background, uint32 flags, uint32 borders)
{
	if (_Image("Button", ICL_NORMAL, ICL_MIDDLE) == NULL)
		HaikuControlLook::DrawButtonFrame(view, rect, updateRect, radius, base, background, flags,
			borders);
}


void
ImageControlLook::DrawButtonFrame(BView* view, BRect& rect, const BRect& updateRect,
	float leftTopRadius, float rightTopRadius, float leftBottomRadius, float rightBottomRadius,
	const rgb_color& base, const rgb_color& background, uint32 flags, uint32 borders)
{
	if (_Image("Button", ICL_NORMAL, ICL_MIDDLE) == NULL)
		HaikuControlLook::DrawButtonFrame(view, rect, updateRect, leftTopRadius, rightTopRadius,
			leftBottomRadius, rightBottomRadius, base, background, flags, borders);
}


void
ImageControlLook::DrawButtonBackground(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, uint32 flags, uint32 borders, orientation orientation)
{
	if (!_DrawTiledImage("Button", flags, view, rect, updateRect, orientation))
		HaikuControlLook::DrawButtonBackground(view, rect, updateRect, base, flags, borders,
			orientation);
}


void
ImageControlLook::DrawButtonBackground(BView* view, BRect& rect, const BRect& updateRect,
	float radius, const rgb_color& base, uint32 flags, uint32 borders, orientation orientation)
{
	if (!_DrawTiledImage("Button", flags, view, rect, updateRect, orientation))
		HaikuControlLook::DrawButtonBackground(view, rect, updateRect, radius, base, flags, borders,
			orientation);
}


void
ImageControlLook::DrawButtonBackground(BView* view, BRect& rect, const BRect& updateRect,
	float leftTopRadius, float rightTopRadius, float leftBottomRadius, float rightBottomRadius,
	const rgb_color& base, uint32 flags, uint32 borders, orientation orientation)
{
	if (!_DrawTiledImage("Button", flags, view, rect, updateRect, orientation))
		HaikuControlLook::DrawButtonBackground(view, rect, updateRect, leftTopRadius,
			rightTopRadius,leftBottomRadius, rightBottomRadius, base, flags, borders, orientation);
}


void
ImageControlLook::DrawCheckBox(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, uint32 flags)
{
	bool drawn = false;
	if (((BControl*)view)->Value() == B_CONTROL_ON)
		drawn = _DrawImage("CheckBox-Checked", flags & ~B_ACTIVATED, view, rect);
	else
		drawn = _DrawImage("CheckBox-Unchecked", flags, view, rect);

	if (!drawn)
		HaikuControlLook::DrawCheckBox(view, rect, updateRect, base, flags);
}


void
ImageControlLook::DrawRadioButton(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, uint32 flags)
{
	bool drawn = false;
	if (((BControl*)view)->Value() == B_CONTROL_ON)
		drawn = _DrawImage("RadioButton-Checked", flags & ~B_ACTIVATED, view, rect);
	else
		drawn = _DrawImage("RadioButton-Unchecked", flags, view, rect);

	if (!drawn)
		HaikuControlLook::DrawRadioButton(view, rect, updateRect, base, flags);
}


void
ImageControlLook::DrawSliderThumb(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, uint32 flags, orientation orientation)
{
	if (!_DrawImage("SliderThumb", flags, view, rect, orientation))
		HaikuControlLook::DrawSliderThumb(view, rect, updateRect, base, flags, orientation);
}


void
ImageControlLook::DrawSliderTriangle(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, uint32 flags, orientation orientation)
{
	if (!_DrawImage("SliderTriangle", flags, view, rect, orientation))
		HaikuControlLook::DrawSliderTriangle(view, rect, updateRect, base, flags, orientation);
}


void
ImageControlLook::DrawSliderTriangle(BView* view, BRect& rect, const BRect& updateRect,
	const rgb_color& base, const rgb_color& fill, uint32 flags, orientation orientation)
{
	if (!_DrawImage("SliderTriangle", flags, view, rect, orientation))
		HaikuControlLook::DrawSliderTriangle(view, rect, updateRect, base, fill, flags,
			orientation);
}


bool
ImageControlLook::_DrawImage(const char* type, icl_state state, BView* view, BRect rect,
	icl_orient orientation)
{
	BBitmap* image = _Image(type, state, ICL_NO_SIDE, orientation);
	if (image != NULL) {
		view->SetDrawingMode(B_OP_ALPHA);
		view->DrawBitmap(image, rect);
		return true;
	}
	return false;
}


bool
ImageControlLook::_DrawImage(const char* type, uint32 flags, BView* view, BRect rect,
	orientation orientation)
{
	return _DrawImage(type, _FlagsToState(flags), view, rect, _ICLOrientation(orientation));
}


bool
ImageControlLook::_DrawTiledImage(const char* type, icl_state state, BView* view, BRect rect,
	BRect updateRect, icl_orient orientation)
{
	BBitmap* tile = _Image(type, state, ICL_MIDDLE, orientation);
	BBitmap* left = _Image(type, state, ICL_LEFT, orientation);
	BBitmap* right = _Image(type, state, ICL_RIGHT, orientation);

	if (tile == NULL)
		return false;

	bool horiz = orientation == ICL_HORIZONTAL;

	float min = 0;
	float max = horiz ? rect.Width() : rect.Height();
	if (left != NULL)
		min = horiz ? left->Bounds().Width() : left->Bounds().Height();
	if (right != NULL)
		if (horiz)
			max = rect.Width() - right->Bounds().Width();
		else
			max = rect.Height() - right->Bounds().Height();

	float sliceRatio = rect.Height() / tile->Bounds().Height();
	float sliceSize = sliceRatio * tile->Bounds().Width();
	if (!horiz) {
		sliceRatio = rect.Width() / tile->Bounds().Width();
		sliceSize = sliceRatio * tile->Bounds().Height();
	}

	view->SetDrawingMode(B_OP_ALPHA);

	// This is repetitive and not done well (the horiz and vert blocks are pretty much identical)
	BRect tileRect;
	if (horiz) {
		tileRect.top = 0;
		tileRect.bottom = rect.Height();
		for (float left = min; left + sliceSize < max; left += sliceSize) {
			tileRect.left = left;
			tileRect.right = left + sliceSize;
			if (tileRect.Intersects(updateRect))
				view->DrawBitmap(tile, tileRect);
		}
		tileRect.right = max;
		tileRect.left = max - sliceSize;
		if (tileRect.Intersects(updateRect))
			view->DrawBitmap(tile, tileRect);
	} else {
		tileRect.left = 0;
		tileRect.right = rect.Width();
		for (float top = min; top + sliceSize < max; top += sliceSize) {
			tileRect.top = top;
			tileRect.bottom = top + sliceSize;
			if (tileRect.Intersects(updateRect))
				view->DrawBitmap(tile, tileRect);
		}
		tileRect.bottom = max;
		tileRect.top = max - sliceSize;
		if (tileRect.Intersects(updateRect))
			view->DrawBitmap(tile, tileRect);
	}

	BRect sideRect = horiz ? BRect(0, 0, min, rect.Height()) : BRect(0, 0, rect.Width(), min);
	if (left != NULL && sideRect.Intersects(updateRect))
		view->DrawBitmap(left, sideRect);

	if (horiz) {
		sideRect.left = max;
		sideRect.right = view->Bounds().right;
	} else {
		sideRect.top = max;
		sideRect.bottom = view->Bounds().bottom;
	}
	if (right != NULL && sideRect.Intersects(updateRect))
		view->DrawBitmap(right, sideRect);

	return true;
}


bool
ImageControlLook::_DrawTiledImage(const char* type, uint32 flags, BView* view, BRect rect,
	BRect updateRect, orientation orientation)
{
	return _DrawTiledImage(type, _FlagsToState(flags), view, rect, updateRect,
		_ICLOrientation(orientation));
}


BBitmap*
ImageControlLook::_Image(const char* type, icl_state state, icl_side side, icl_orient orientation)
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
	else if (strcmp(type, "RadioButton-Unchecked") == 0)
		nosideList = &fRadioButton_Unchecked;
	else if (strcmp(type, "RadioButton-Checked") == 0)
		nosideList = &fRadioButton_Checked;
	else if (strcmp(type, "SliderThumb") == 0)
		nosideList = &fSliderThumb;
	else if (strcmp(type, "SliderTriangle") == 0)
		nosideList = &fSliderTriangle;

	if (sideList != NULL && (*sideList)[orientation][side][state] == NULL)
		(*sideList)[orientation][side][state]
			= BTranslationUtils::GetBitmapFile(_ImagePath(type, state, side, orientation));
	if (sideList != NULL)
		image = (*sideList)[orientation][side][state];

	if (nosideList != NULL && (*nosideList)[orientation][state] == NULL)
		(*nosideList)[orientation][state]
			= BTranslationUtils::GetBitmapFile(_ImagePath(type, state, ICL_NO_SIDE, orientation));
	if (nosideList != NULL)
		image = (*nosideList)[orientation][state];

	return image;
}


const char*
ImageControlLook::_ImagePath(const char* type, icl_state state, icl_side side, icl_orient orientation)
{
	BString leaf = kStates[state];
	leaf << kSides[side];

	BPath imgPath(fImageRoot.Path());
	if (orientation == ICL_VERTICAL)
		imgPath.Append("Vertical");
	else
		imgPath.Append("Horizontal");
	imgPath.Append(type);
	imgPath.Append(leaf);
	printf("[ImageControlLook] Searching for %s…\n", imgPath.Path());
	return imgPath.Path();
}


icl_state
ImageControlLook::_FlagsToState(uint32 flags)
{
	icl_state state = ICL_NORMAL;
	if (flags & B_DISABLED)
		state = ICL_DISABLED;
	else if (flags & (B_ACTIVATED | B_PARTIALLY_ACTIVATED | B_CLICKED))
		state = ICL_ACTIVATED;
	else if (flags & (B_HOVER | B_FOCUSED))
		state = ICL_HOVER;
	return state;
}


icl_orient
ImageControlLook::_ICLOrientation(orientation orientation)
{
	if (orientation == B_VERTICAL)
		return ICL_VERTICAL;
	return ICL_HORIZONTAL;
}


extern "C" BControlLook* (instantiate_control_look)(image_id id)
{
	return new (std::nothrow)ImageControlLook(id);
}
