# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND Research_sources
    new_qpsk_demod_cb_impl.cc
    rotation_cc_impl.cc
    rotation_cc_impl.cc
    multiply_c_ff_impl.cc
    soqpsk_demod_impl.cc
    soqpsk_det_filter_cc_impl.cc )

set(Research_sources "${Research_sources}" PARENT_SCOPE)
if(NOT Research_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT Research_sources)

add_library(gnuradio-Research SHARED ${Research_sources})
target_link_libraries(gnuradio-Research ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-Research PROPERTIES DEFINE_SYMBOL "gnuradio_Research_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-Research PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-Research
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})
list(APPEND test_Research_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_Research.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_Research.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_soqpsk_det_filter_cc.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_soqpsk_demod.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_multiply_c_ff.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_rotation_cc.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_rotation_cc.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_new_qpsk_demod_cb.cc
)

add_executable(test-Research ${test_Research_sources})

target_link_libraries(
  test-Research
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-Research
)

GR_ADD_TEST(test_Research test-Research)
