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

#include "util.h"

void resultHandler(CALLBACK_RESULT results, cv::Mat source)
{
    Companion::Draw::Frame *frame;
    Companion::Model::Result::Result *result;

    for (size_t i = 0; i < results.size(); i++)
    {
        // Mark the detected or recognized object
        result = results.at(i);
        result->getDrawable()->draw(source);

        // Draw the id of the detected or recognized object
        frame = dynamic_cast<Companion::Draw::Frame*>(result->getDrawable());
        if (frame != nullptr)
        {
            cv::putText(source,
                result->getDescription(),
                frame->getTopRight(),
                cv::FONT_HERSHEY_DUPLEX,
                2.0,
                frame->getColor(),
                frame->getThickness()
            );
        }
    }

    cv::imshow("Companion", source);
    cv::waitKey(1);
    source.release();
    results.clear();
}

void errorHandler(Companion::Error::Code code)
{
    // Obtain detailed error message from code
    std::cout << Companion::Error::getError(code) << std::endl;
}
