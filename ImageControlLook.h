/*
 * Copyright 2022, Jaidyn Levesque <jadedctrl@teknik.io>
 * Distributed under the terms of the MIT License.
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef IMAGE_CONTROL_LOOK_H
#define IMAGE_CONTROL_LOOK_H

#include <ControlLook.h>
#include <HaikuControlLook.h>

class BBitmap;
class BControl;
class BGradientLinear;
class BView;


using BPrivate::HaikuControlLook;


class ImageControlLook : public HaikuControlLook {
public:
								ImageControlLook(image_id id);
	virtual						~ImageControlLook();
};

#endif	// IMAGE_CONTROL_LOOK_H
