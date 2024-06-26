cmake_minimum_required(VERSION 3.1.1)

set (CMAKE_CXX_STANDARD 11)

set(PROJECT_NAME 3daudio-producer)
project (${PROJECT_NAME} LANGUAGES C CXX)


#-DCMAKE_BUILD_TYPE=Release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -DDATADIR=${DATAPATH} -g -Wall -fPIE")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -DDATADIR=${DATAPATH} -Wall -fPIE")


# Let CMake search for a raylib-config.cmake
find_package(raylib 3.5 QUIET) 

#for serial data stuff
set(BOOST_LIBS date_time system)
find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
find_package(Threads REQUIRED)


#Pugi XML parsing
find_path(pugixml_INCLUDE_DIRS pugixml.hpp)
find_library(pugixml_LIBRARIES NAMES pugixml)


#For the shared library:

set ( PROJECT_LINK_LIBS  raylib openal sndfile ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${pugixml_LIBRARIES})
#where to find library files .so 
link_directories( /usr/lib /usr/local/lib ) 

if (MINGW)
    # need to link with mingw32 before SDL2
    list(APPEND _link_libraries mingw32)
endif ()

if(WIN32)
	set ( PROJECT_LINK_LIBS  ${PROJECT_LINK_LIBS} opengl32 gdi32 winmm)
endif()

set ( PROJECT_INCLUDE_DIR ./src)

#for where to find header files for source and library
include_directories(/usr/include /usr/local/include ./include ./src/timeline-track-editor/include ${PROJECT_INCLUDE_DIR} )

set(SOURCES src/main.cpp
			src/global_variables.cpp
			src/main_gui_editor.cpp
			src/timeline.cpp
			src/SaveSystem.cpp src/LoadSystem.cpp src/XMLCreator.cpp src/XMLReader.cpp
			src/CreateStandardReverbZoneDialog.cpp src/EditMultipleStandardReverbZonesDialog.cpp 
			src/CreateEAXReverbZoneDialog.cpp src/EditMultipleEAXReverbZonesDialog.cpp 
			src/CreateEchoZoneDialog.cpp src/EditMultipleEchoZonesDialog.cpp
			src/echo-zone.cpp
			src/reverb-zone.cpp
			src/effect-zone.cpp
			src/effects-manager.cpp
			#src/soundproducer-track-manager.cpp
			#src/soundproducer-track.cpp
			#src/listener-track.cpp
			src/soundproducer-registry.cpp
			src/immediate_mode_sound_player.cpp src/sound_bank.cpp
			src/CreateSoundProducerDialog.cpp src/EditMultipleSoundProducersDialog.cpp 
			src/Change-HRTF-Dialog.cpp src/HRTF-Test-Dialog.cpp 
			src/EditListenerDialog.cpp
			#src/setup-serial-dialog.cpp
			#src/listener-external.cpp
			src/openalsoftaudioengine.cpp src/soundproducer.cpp src/listener.cpp
			#src/external-orientation-device-serial.cpp

			#src/timeline-track-editor/src/timeline-frame.cpp
			#src/timeline-track-editor/src/timeline-window.cpp
			#src/timeline-track-editor/src/playback-controls.cpp
			#src/timeline-track-editor/src/stereo-audio-track.cpp
			#src/timeline-track-editor/src/mono-audio-track.cpp
			#src/timeline-track-editor/src/audio-track.cpp
			#src/timeline-track-editor/src/audio-graph.cpp
			src/timeline-track-editor/src/audio-stream-container.cpp
			src/timeline-track-editor/src/openalsoft-player.cpp
			#src/timeline-track-editor/src/double-track.cpp
			#src/timeline-track-editor/src/editor-graph.cpp
			#src/timeline-track-editor/src/track.cpp
			 )

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

#make executable sphere from simple-sphere.cpp 
add_executable(${PROJECT_NAME} ${SOURCES})
#link libraries
target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS})

#make install ops
install(TARGETS 3daudio-producer DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

