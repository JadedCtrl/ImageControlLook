/*
 * Copyright 2009-2021 Haiku, Inc.
 * Copyright 2022, Jaidyn Levesque <jadedctrl@teknik.io>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef IMAGE_CONTROL_LOOK_H
#define IMAGE_CONTROL_LOOK_H

#include <array>

#include <Bitmap.h>
#include <ControlLook.h>
#include <HaikuControlLook.h>
#include <Path.h>

class BControl;
class BGradientLinear;
class BView;


using BPrivate::HaikuControlLook;

enum icl_orient {
	ICL_HORIZONTAL,
	ICL_VERTICAL
};

enum icl_side {
	ICL_MIDDLE,
	ICL_LEFT,
	ICL_RIGHT,
	ICL_NO_SIDE
};

enum icl_state {
	ICL_NORMAL,
	ICL_INACTIVE,
	ICL_HOVER,
	ICL_DISABLED,
	ICL_ACTIVATED
};


const char* kStates[] = { "Normal", "Inactive", "Hover", "Disabled", "Activated" };
const char* kSides[] = { "Middle", "Left", "Right", "" };


typedef std::array<std::array<std::array<BBitmap*, 5>, 3>, 2> SidedImages;
typedef std::array<std::array<BBitmap*, 5>, 2> UnsidedImages;


class ImageControlLook : public HaikuControlLook {
public:
								ImageControlLook(image_id id);
	virtual						~ImageControlLook();

	virtual	void				DrawButtonFrame(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base,
									const rgb_color& background,
									uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS);
	virtual	void				DrawButtonFrame(BView* view, BRect& rect,
									const BRect& updateRect,
									float radius,
									const rgb_color& base,
									const rgb_color& background,
									uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS);
	virtual	void				DrawButtonFrame(BView* view, BRect& rect,
									const BRect& updateRect,
									float leftTopRadius,
									float rightTopRadius,
									float leftBottomRadius,
									float rightBottomRadius,
									const rgb_color& base,
									const rgb_color& background,
									uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS);

	virtual	void				DrawButtonBackground(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base,
									uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS,
									orientation orientation = B_HORIZONTAL);
	virtual	void				DrawButtonBackground(BView* view, BRect& rect,
									const BRect& updateRect,
									float radius,
									const rgb_color& base,
									uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS,
									orientation orientation = B_HORIZONTAL);
	virtual	void				DrawButtonBackground(BView* view, BRect& rect,
									const BRect& updateRect,
									float leftTopRadius,
									float rightTopRadius,
									float leftBottomRadius,
									float rightBottomRadius,
									const rgb_color& base,
									uint32 flags = 0,
									uint32 borders = B_ALL_BORDERS,
									orientation orientation = B_HORIZONTAL);

	virtual	void				DrawCheckBox(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base,
									uint32 flags = 0);

	virtual	void				DrawRadioButton(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base,
									uint32 flags = 0);

	virtual	void				DrawSliderThumb(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base, uint32 flags,
									orientation orientation);

	virtual	void				DrawSliderTriangle(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base, uint32 flags,
									orientation orientation);
	virtual	void				DrawSliderTriangle(BView* view, BRect& rect,
									const BRect& updateRect,
									const rgb_color& base,
									const rgb_color& fill, uint32 flags,
									orientation orientation);

private:
	bool						_DrawImage(const char* type, icl_state state, BView* view, BRect rect,
									icl_orient orientation = ICL_HORIZONTAL);
	bool						_DrawImage(const char* type, uint32 flags, BView* view, BRect rect,
									orientation orientation = B_HORIZONTAL);

	bool						_DrawTiledImage(const char* type, icl_state state, BView* view,
									BRect rect, BRect updateRect,
									icl_orient orientation = ICL_HORIZONTAL);
	bool						_DrawTiledImage(const char* type, uint32 flags, BView* view,
									BRect rect, BRect updateRect,
									orientation orientation = B_HORIZONTAL);

	BBitmap*					_Image(const char* type, icl_state state,
									icl_side side = ICL_NO_SIDE,
									icl_orient orientation = ICL_HORIZONTAL);
	const char*					_ImagePath(const char* type, icl_state state,
									icl_side side = ICL_NO_SIDE,
									icl_orient orientation = ICL_HORIZONTAL);

	icl_state					_FlagsToState(uint32 flags);
	icl_orient					_ICLOrientation(orientation orientation);

	BPath fImageRoot;

	SidedImages   fButton;
	UnsidedImages fCheckBox_Checked;
	UnsidedImages fCheckBox_Unchecked;
	UnsidedImages fRadioButton_Checked;
	UnsidedImages fRadioButton_Unchecked;
	UnsidedImages fSliderThumb;
	UnsidedImages fSliderTriangle;
};

#endif	// IMAGE_CONTROL_LOOK_H
