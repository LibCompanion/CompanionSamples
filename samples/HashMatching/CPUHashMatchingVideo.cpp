/*
 * This program is an usage example for libCompanion.
 * Copyright (C) 2016-2017 Andreas Sekulski
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
#include <companion/algo/2D/ShapeDetection.h>
#include <companion/processing/2D/HashDetection.h>
#include <companion/algo/2D/FeatureMatching.h>
#include <companion/input/Video.h>

#include "../util.h"
#include "ressources.h"

 /**
  * This example show an setup for an CPU based hash matching companion configuration. Following features will be shown
  * in this example.
  *   - Video file handling
  *   - Model handling to search in video
  *   - CPU based hash matching
  *   - Callback handler example are implemented in util.h
  */
int main() 
{

	// Sample objects to search as an image list.
	std::vector<std::string> images;
	images.push_back(OBJECT_LEFT); // ID 0
	images.push_back(OBJECT_RIGHT); // ID 1
	// Sample video to search objects.
	std::string testVideo = VIDEO_EXAMPLE_PATH;

	// -------------- Setup used processing algo. --------------
	Companion::Configuration *companion = new Companion::Configuration();


	// -------------- Image Processing Setup with shape detection --------------
	Companion::Algorithm::ShapeDetection* shapeDetection = new Companion::Algorithm::ShapeDetection();
	Companion::Processing::HashDetection* detection = new Companion::Processing::HashDetection(cv::Size(50, 70), shapeDetection);
	companion->setProcessing(detection);

	companion->setSkipFrame(0);
	companion->setImageBuffer(20);
	companion->setResultHandler(resultHandler);
	companion->setErrorHandler(errorHandler);

	// Setup video source to obtain images.
	Companion::Input::Stream *stream = new Companion::Input::Video(testVideo);

	// Set input source
	companion->setSource(stream);

	// Store all searched data models
	for (int i = 0; i < images.size(); i++) 
	{
		if (!detection->addModel(i, cv::imread(images[i], cv::IMREAD_GRAYSCALE)))
		{
			std::cout << "Model not added";
		}
	}

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
