/*
 * This program is an example for libComapanion.
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

#ifndef COMPANION_UTIL_H_H
#define COMPANION_UTIL_H_H

#include <opencv2/core.hpp>
#include <companion/util/Definitions.h>
#include <companion/util/CompanionError.h>
#include <companion/draw/Frame.h>

 /**
  * Example implementation to handle results from libCompanion.
  * @param results Result from all detected objects.
  * @param source Image source from detected objects.
  */
void resultHandler(CALLBACK_RESULT results, cv::Mat source);

/**
 * Error handler for libCompanion.
 * @param code Error code from companion.
 */
void errorHandler(Companion::Error::Code code);

#endif //COMPANION_UTIL_H_H
