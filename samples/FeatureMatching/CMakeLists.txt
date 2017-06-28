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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Create executable and set linked libraries
add_executable(CPUFeatureMatchingVideo CPUFeatureMatchingVideo.cpp util.cpp util.h)
target_link_libraries(CPUFeatureMatchingVideo Companion)
# Add target properties
set_property(TARGET CPUFeatureMatchingVideo PROPERTY FOLDER "libCompanion")
# add install instructions (also add debug postfix for differentiation)
set_property(TARGET CPUFeatureMatchingVideo PROPERTY DEBUG_POSTFIX "D")
install(TARGETS CPUFeatureMatchingVideo DESTINATION "${PROJECT_BINARY_DIR}/install/bin" OPTIONAL)

# Create executable and set linked libraries
add_executable(CPUFeatureMatchingRealtime CPUFeatureMatchingRealtime.cpp util.cpp util.h)
target_link_libraries(CPUFeatureMatchingRealtime Companion)
# Add target properties
set_property(TARGET CPUFeatureMatchingRealtime PROPERTY FOLDER "libCompanion")
# add install instructions (also add debug postfix for differentiation)
set_property(TARGET CPUFeatureMatchingRealtime PROPERTY DEBUG_POSTFIX "D")
install(TARGETS CPUFeatureMatchingRealtime DESTINATION "${PROJECT_BINARY_DIR}/install/bin" OPTIONAL)

# Create executable and set linked libraries
add_executable(CPUFeatureMatchingImageStream CPUFeatureMatchingImageStream.cpp util.cpp util.h)
target_link_libraries(CPUFeatureMatchingImageStream Companion)
# Add target properties
set_property(TARGET CPUFeatureMatchingImageStream PROPERTY FOLDER "libCompanion")
# add install instructions (also add debug postfix for differentiation)
set_property(TARGET CPUFeatureMatchingImageStream PROPERTY DEBUG_POSTFIX "D")
install(TARGETS CPUFeatureMatchingImageStream DESTINATION "${PROJECT_BINARY_DIR}/install/bin" OPTIONAL)

if(Companion_USE_CUDA)
    # Create executable and set linked libraries
    add_executable(CudaFeatureMatchingVideo CudaFeatureMatchingVideo.cpp util.cpp util.h)
    target_link_libraries(CudaFeatureMatchingVideo Companion)
    # Add target properties
    set_property(TARGET CudaFeatureMatchingVideo PROPERTY FOLDER "libCompanion")
    # add install instructions (also add debug postfix for differentiation)
    set_property(TARGET CudaFeatureMatchingVideo PROPERTY DEBUG_POSTFIX "D")
    install(TARGETS CudaFeatureMatchingVideo DESTINATION "${PROJECT_BINARY_DIR}/install/bin" OPTIONAL)
endif()

# Ressource files
INCLUDE_DIRECTORIES(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)

SET(VIDEO_EXAMPLE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/video/lab.mov")
SET(OBJECT_LEFT "${CMAKE_CURRENT_SOURCE_DIR}/models/poster_left.jpg")
SET(OBJECT_RIGHT "${CMAKE_CURRENT_SOURCE_DIR}/models/poster_right.jpg")
SET(OBJECT_IMAGES_RAW "${CMAKE_CURRENT_SOURCE_DIR}/images/lab")
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/ressources.h.in ${CMAKE_CURRENT_BINARY_DIR}/ressources.h @ONLY)