/*
 * Copyright 2022, Jaidyn Levesque <jadedctrl@teknik.io>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "ImageControlLook.h"


ImageControlLook::ImageControlLook(image_id id)
	:
	HaikuControlLook()
{
}



ImageControlLook::~ImageControlLook()
{
}


extern "C" BControlLook* (instantiate_control_look)(image_id id)
{
	return new (std::nothrow)ImageControlLook(id);
}
