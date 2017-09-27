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
#include <companion/processing/2D/ObjectDetection.h>
#include <companion/algo/2D/FeatureMatching.h>
#include <companion/input/Video.h>
#include <companion/input/Image.h>

#include "util.h"
#include "ressources.h"

void imageStream(Companion::Input::Image *stream) {

	int i = 1;
	int n = 4 - 1;
	int divider = 10;
	std::string fileNr;
	bool lastImage = false;

	// Setup example for an image stream.
	while (!lastImage) {
		fileNr = "";

		// Only setup to get all files from an folder with an specific name.
		if (i / divider == 1) {
			divider = divider * 10;
			n--;
		}

		// Append zeros to fileNr
		for (int x = 0; x < n; x++) {
			fileNr = fileNr + "0";
		}

		// Add image to stream
		if (!stream->addImage(OBJECT_IMAGES_RAW + fileNr + std::to_string(i) + ".jpg")) {
			lastImage = true;
		}

		// Use this control to adjust the streaming rate
		//std::this_thread::sleep_for(std::chrono::seconds(1));

		i++;
	}

	// Stop this stream after all images are processed.
	stream->finishAfterProcessing();
}

/**
 * This example show an setup for an CPU based feature matching companion configuration. Following features will be shown
 * in this example.
 *   - Image stream video handling. Needed an set of images in an folder. See imageStream thread function.
 *   - Model handling to search in video
 *   - CPU based feature matching with OpenCV 3.X (BRISK algorithm will be used)
 *   - Callback handler example are implemented in util.h
 */
int main() {

	// Sample objects to search as an image list.
	std::vector<std::string> images;
	images.push_back(OBJECT_LEFT);
	images.push_back(OBJECT_RIGHT);

	// -------------- Setup used processing algo. --------------
	Companion::Configuration *companion = new Companion::Configuration();
	int type = cv::DescriptorMatcher::BRUTEFORCE_HAMMING;
	cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(type);

	// -------------- BRISK CPU FM --------------
	cv::Ptr<cv::BRISK> feature = cv::BRISK::create(60);
	Companion::Algorithm::Matching *matching = new Companion::Algorithm::FeatureMatching(feature, feature, matcher, type, 10, 40, true, 3.0, 100);

	// -------------- Image Processing Setup --------------
	companion->setProcessing(new Companion::Processing::ObjectDetection(companion, matching, Companion::SCALING::SCALE_960x540));
	companion->setSkipFrame(0);
	companion->setImageBuffer(10);
	companion->setResultHandler(resultHandler, Companion::ColorFormat::BGR);
	companion->setErrorHandler(errorHandler);

	// Setup example for an streaming data from a set of images.
	Companion::Input::Image *stream = new Companion::Input::Image(50);
	std::thread imgThread = std::thread(&imageStream, stream);

	// Set input source
	companion->setSource(stream);

	// Store all searched data models
	Companion::Model::Processing::FeatureMatchingModel *model;
	for (int i = 0; i < images.size(); i++) {

		model = new Companion::Model::Processing::FeatureMatchingModel();
		model->setID(i);
		model->setImage(cv::imread(images[i], cv::IMREAD_GRAYSCALE));

		if (!companion->addModel(model)) {
			std::cout << "Model not added";
		}
	}

	// Execute companion
	try {
		companion->run();
	}
	catch (Companion::Error::Code errorCode) {
		errorHandler(errorCode);
	}

	// Wait for worker thread that adds images for processing to be finished.
	imgThread.join();

	return 0;
}
