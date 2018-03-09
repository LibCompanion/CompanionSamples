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
  * This example show an setup for an CPU based shape detection companion configuration. Following features will be shown
  * in this example.
  *   - Video file handling
  *   - CPU based simple quadrangular shape detection
  *   - Callback handler example are implemented in util.h
  */
int main() 
{
	// Sample video to search objects.
	std::string testVideo = VIDEO_EXAMPLE_PATH;

	// -------------- Setup used processing algo. --------------
	Companion::Configuration *companion = new Companion::Configuration();

	// -------------- Image Processing Setup --------------
    Companion::Algorithm::Detection::ShapeDetection *shapeDetection = new Companion::Algorithm::Detection::ShapeDetection();
	Companion::Processing::Detection::ObjectDetection *detection = new Companion::Processing::Detection::ObjectDetection(shapeDetection);
	companion->setProcessing(detection);

	companion->setSkipFrame(0);
	companion->setImageBuffer(20);
	companion->setResultHandler(resultHandler);
	companion->setErrorHandler(errorHandler);

	// Setup video source to obtain images.
	Companion::Input::Stream *stream = new Companion::Input::Video(testVideo);

	// Set input source
	companion->setSource(stream);

	// Execute companion
	try 
	{
		companion->run();
	}
	catch (Companion::Error::Code errorCode) 
	{
		errorHandler(errorCode);
	}

	return 0;
}
