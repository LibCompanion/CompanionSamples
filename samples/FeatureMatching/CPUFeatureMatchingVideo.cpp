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

#include "util.h"
#include "ressources.h"

/**
 * This example show an setup for an CPU based feature matching companion configuration. Following features will be shown
 * in this example.
 *   - Video file handling
 *   - Model handling to search in video
 *   - CPU based feature matching with OpenCV 3.X (BRISK algorithm will be used)
 *   - Callback handler example are implemented in util.h
 */
int main() {
	
	// Sample objects to search as an image list.
    std::vector<std::string> images;
    images.push_back(OBJECT_LEFT);
    images.push_back(OBJECT_RIGHT);
    // Sample video to search objects.
    std::string testVideo = VIDEO_EXAMPLE_PATH;

    // -------------- Setup used processing algo. --------------
    Companion::Configuration *companion = new Companion::Configuration();
    int type = cv::DescriptorMatcher::BRUTEFORCE_HAMMING;
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(type);

    // -------------- BRISK CPU FM --------------
    cv::Ptr<cv::BRISK> feature = cv::BRISK::create(60);
    Companion::Algorithm::ImageRecognition *recognition = new Companion::Algorithm::FeatureMatching(feature, feature, matcher, type, 10, 40, true);

    // -------------- Image Processing Setup --------------
    companion->setProcessing(new Companion::Processing::ObjectDetection(companion, recognition, 0.25));
    companion->setSkipFrame(0);
	companion->setImageBuffer(20);
    companion->setResultHandler(resultHandler);
    companion->setErrorHandler(errorHandler);

    // Setup video source to obtain images.
    Companion::Input::Stream *stream = new Companion::Input::Video(testVideo); // Load an video

    // Set input source
    companion->setSource(stream);

    // Store all searched data models
    Companion::Model::Processing::FeatureMatchingModel *model;
    for (int i = 0; i < images.size(); i++) {

        model = new Companion::Model::Processing::FeatureMatchingModel();
        model->setID(i);
        model->setImage(cv::imread(images[i], cv::IMREAD_GRAYSCALE));

        if(!companion->addModel(model)) {
            std::cout << "Model not added";
        }
    }

    try {
        // Execute companion
        companion->run();
    } catch (Companion::Error::Code errorCode) {
        errorHandler(errorCode);
    }

    return 0;
}
