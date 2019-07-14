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
#include <companion/processing/recognition/MatchRecognition.h>
#include <companion/algo/recognition/matching/FeatureMatching.h>
#include <companion/input/Video.h>

#include "../util.h"
#include "ressources.h"

/**
 * This example shows a setup for a CPU based feature matching Companion configuration. Following features will be shown
 * in this example:
 *   - Video file handling
 *   - Model handling to search in video
 *   - CPU based feature matching with OpenCV 3.X (BRISK or ORB algorithm will be used)
 *   - Callback handler example are implemented in util.h
 */
int main() 
{
    // Sample objects to search as an image list.
    std::vector<std::string> images;
    images.push_back(OBJECT_LEFT);
    images.push_back(OBJECT_RIGHT);

    // Sample video to search objects.
    std::string testVideo = VIDEO_EXAMPLE_PATH;

    // -------------- BRISK CPU FM --------------
    int type = cv::DescriptorMatcher::BRUTEFORCE_HAMMINGLUT;
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(type);
    cv::Ptr<cv::BRISK> feature = cv::BRISK::create(60);

    // -------------- ORB CPU FM --------------
	PTR_MATCHING_RECOGNITION matching = std::make_shared<FEATURE_MATCHING>(feature, feature, matcher, type, 10, 10, true);
	PTR_MATCH_RECOGNITION recognition = std::make_shared<MATCH_RECOGNITION>(matching, Companion::SCALING::SCALE_640x360);
    
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

    for (int i = 0; i < images.size(); i++) 
    {
		PTR_MODEL_FEATURE_MATCHING model = std::make_shared<MODEL_FEATURE_MATCHING>();
        model->ID(i);
        model->Image(cv::imread(images[i], cv::IMREAD_GRAYSCALE));
        if (!recognition->AddModel(model))
        {
            std::cout << "Model not added";
        }
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
