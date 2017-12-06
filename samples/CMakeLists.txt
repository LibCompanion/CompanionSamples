#
# This program is an image recognition library written with OpenCV.
# Copyright (C) 2016-2017 Andreas Sekulski
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++11")
endif(MSVC)

set(VIDEO_EXAMPLE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Data/video/lab.mov")
set(OBJECT_LEFT "${CMAKE_CURRENT_SOURCE_DIR}/Data/models/poster_left.jpg")
set(OBJECT_RIGHT "${CMAKE_CURRENT_SOURCE_DIR}/Data/models/poster_right.jpg")
set(OBJECT_IMAGES_RAW "${CMAKE_CURRENT_SOURCE_DIR}/Data/images/lab")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ressources.h.in ${CMAKE_CURRENT_BINARY_DIR}/FeatureMatching/ressources.h @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ressources.h.in ${CMAKE_CURRENT_BINARY_DIR}/HashMatching/ressources.h @ONLY)

add_subdirectory(FeatureMatching)
add_subdirectory(HashMatching)