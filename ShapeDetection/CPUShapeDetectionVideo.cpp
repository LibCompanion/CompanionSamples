/*
 * This program is an usage example for Companion.
 * Copyright (C) 2016-2018 Andreas Sekulski, Dimitri Kotlovsky
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <companion/Configuration.h>
#include <companion/processing/detection/ObjectDetection.h>
#include <companion/input/Video.h>

#include "../util.h"
#include "ressources.h"

/**
 * This examples show a setup for a CPU based shape detection Companion configuration. Following features will be shown
 * in this example:
 *   - Video file handling
 *   - CPU based simple quadrangular shape detection
 *   - Callback handler example are implemented in util.h
 */
int main() 
{
    // Sample video to search objects.
    std::string testVideo = VIDEO_EXAMPLE_PATH;

    // -------------- Image Processing Setup --------------
	PTR_SHAPE_DETECTION shapeDetection = std::make_shared<SHAPE_DETECTION>(4, 4, "Quad");
	PTR_OBJECT_DETECTION detection = std::make_shared<OBJECT_DETECTION>(shapeDetection);
    
	std::unique_ptr<COMPANION> companion = std::make_unique<COMPANION>();
	companion->Processing(detection);
    companion->SkipFrame(0);
    companion->ImageBuffer(20);
    companion->ResultCallback(resultHandler);
    companion->ErrorCallback(errorHandler);

    // Setup video source to obtain images.
	PTR_VIDEO_STREAM stream = std::make_shared<VIDEO_STREAM>(testVideo);
    // Set input source
    companion->Source(stream);

    // Execute companion
    try 
    {
        companion->Run();
    }
    catch (Companion::Error::Code errorCode) 
    {
        errorHandler(errorCode);
    }

    return 0;
}
