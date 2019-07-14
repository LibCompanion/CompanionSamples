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
#include <companion/processing/recognition/HybridRecognition.h>
#include <companion/algo/recognition/matching/FeatureMatching.h>
#include <companion/input/Video.h>
#include <companion/algo/recognition/hashing/LSH.h>
#include <companion/algo/detection/ShapeDetection.h>
#include <companion/processing/recognition/HashRecognition.h>

#include "../util.h"
#include "ressources.h"

/**
 * This example shows a setup for a CPU based hybrid matching Companion configuration. Following features will be shown
 * in this example:
 *   - Video file handling
 *   - Model handling to search in video
 *   - CPU based feature matching with OpenCV 3.X (BRISK algorithm will be used)
 *   - Callback handler example are implemented in util.h
 */
int main()
{
    // Sample objects to search as an image list.
    std::vector<std::string> images;
    images.emplace_back(OBJECT_LEFT);
    images.emplace_back(OBJECT_RIGHT);
    // Sample video to search objects.
    std::string testVideo = VIDEO_EXAMPLE_PATH;

    int type = cv::DescriptorMatcher::BRUTEFORCE_HAMMING;
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(type);

    // -------------- BRISK CPU FM --------------
    cv::Ptr<cv::BRISK> feature = cv::BRISK::create(40);
	PTR_FEATURE_MATCHING matching = std::make_shared<FEATURE_MATCHING>(feature, feature, matcher, type, 10, 40);

    // -------------- Image Processing Setup --------------
	PTR_SHAPE_DETECTION shapeDetection = std::make_shared<SHAPE_DETECTION>();
	PTR_HASHING_LSH lsh = std::make_shared<HASHING_LSH>();
    // Original Aspect Ration is 397x561
	PTR_HASH_RECOGNITION hashRecognition = std::make_shared<HASH_RECOGNITION>(cv::Size(50, 70), shapeDetection, lsh);
	PTR_HYBRID_RECOGNITION recognition = std::make_shared<HYBRID_RECOGNITION>(hashRecognition, matching, 50);
    
	std::unique_ptr<COMPANION> companion = std::make_unique<COMPANION>();
	companion->Processing(recognition);
    companion->SkipFrame(0);
    companion->ImageBuffer(20);
    companion->ResultCallback(resultHandler);
    companion->ErrorCallback(errorHandler);

	// Setup video source to obtain images.
	PTR_VIDEO_STREAM stream = std::make_shared<VIDEO_STREAM>(testVideo);
    // Set input source
    companion->Source(stream);

    // Store all searched data models
    for (int i = 0; i < images.size(); i++)
    {
        recognition->AddModel(cv::imread(images[i], cv::IMREAD_GRAYSCALE), i);
    }

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
