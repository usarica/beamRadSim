cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
############ Make your changes here ############ 
#set(CMAKE_INSTALL_RPATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_STANDARD 17)

string(TIMESTAMP timeVar)
string(REPLACE ":" "_" time ${timeVar})
EXECUTE_PROCESS(COMMAND "date" "+%d_%m_%Y" ${date})
set(name    BeamRad)      # equivalent to "name := exampleN01" in G4 GNUmakefiles
set(useROOT true)        # use true or false

############ What's below should not need to be changed ############ 

# http://www.cmake.org/cmake/help/cmake_tutorial.html
# http://www.cmake.org/cmake/help/cmake2.6docs.html
# http://www.cmake.org/Wiki/CMake_FAQ

set(mymain ${name}.cc )
set(myexe  ${name}${time}${date} )
set(myproj ${name}_   )  # any name as long as it is different from myexe

project(${myproj})


#----------------------------------------------------------------------------
# CMakeModules
#----------------------------------------------------------------------------


set(CMAKE_PREFIX_PATH "$ENV{ROOTSYS}")
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
 include(${Geant4_USE_FILE})
 
set(Geant4_INCLUDE_DIRS "${_use_geant4_dir}/../../include/Geant4")
# find ROOT6 cling
find_package(ROOT 6.00 COMPONENTS Cling)
include(${ROOT_USE_FILE})
# find ROOT5 cint
#find_package(ROOT 5.30 COMPONENTS Cintex)

#set(Boost_INCLUDE_DIRS "/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/boost/1.67.0/include")

option(ANALYSIS_HH_ "Build with ROOT" 1)
add_definitions(-DG4UI_USE -DG4VIS_USE -DANALYSIS_HH_) 

message("ROOTSYS: " $ENV{ROOTSYS})
message("GEANT4 INCLUDE DIRS: " ${Geant4_INCLUDE_DIRS})
message("BOOST INCLUDE DIRS: " ${Boost_INCLUDE_DIRS})
message("PROJECT DIRECTORY: " ${CMAKE_CURRENT_SOURCE_DIR})

#----------------------------------------------------------------------------
# Setup include directories and compile definitions
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# ROOTIO
#----------------------------------------------------------------------------

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIRS}
                    ${ROOT_INCLUDE_DIRS}
		    ${Boost_INCLUDE_DIRS}	
		    )

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

#include files for ROOT dictionary
set(INCLUDE_DICT ${CMAKE_CURRENT_SOURCE_DIR}/include/brGammaTrack.hh 
	${CMAKE_CURRENT_SOURCE_DIR}/include/brNeutronTrack.hh 
	${CMAKE_CURRENT_SOURCE_DIR}/include/brMuonTrack.hh 
#	${CMAKE_CURRENT_SOURCE_DIR}/include/brElectronTrack.hh 
	${CMAKE_CURRENT_SOURCE_DIR}/include/brPhotonTrack.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/brPMTRHit.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/brScintRHit.hh
	${CMAKE_CURRENT_SOURCE_DIR}/include/brROOTEvent.hh
	)

#source files for ROOT dictionary
set(SRC_DICT ${CMAKE_CURRENT_SOURCE_DIR}/src/brGammaTrack.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/src/brNeutronTrack.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/src/brMuonTrack.cc 
#	${CMAKE_CURRENT_SOURCE_DIR}/src/brElectronTrack.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/src/brPhotonTrack.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/brPMTRHit.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/brScintRHit.cc
	${CMAKE_CURRENT_SOURCE_DIR}/src/brROOTEvent.cc
	)

#----------------------------------------------------------------------------
# Use this for ROOT Linkdef 
#----------------------------------------------------------------------------

ROOT_GENERATE_DICTIONARY(BeamRadDict ${INCLUDE_DICT} LINKDEF include/EventLinkDef.hh)

add_library(${name}Core SHARED ${SRC_DICT} ${CMAKE_CURRENT_BINARY_DIR}/BeamRadDict.cxx)

add_executable(${name}${time}${date} ${name}.cc ${sources})

target_link_libraries(${name}${time}${date} ${name}Core ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${ROOT_COMPONENT_LIBRARIES} )

#----------------------------------------------------------------------------
# Use this for reflex 
#----------------------------------------------------------------------------
#REFLEX_GENERATE_DICTIONARY(Classes include/Classes.hh SELECTION xml/selection.xml)
#
#add_library(ClassesDict SHARED ${sources} Classes.cpp)
#
#target_link_libraries(ClassesDict  ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} Cintex Reflex)
#
#set(libsuffix .so)
#
#set(ROOT_LIBRARY_PROPERTIES ${ROOT_LIBRARY_PROPERTIES} SUFFIX ${libsuffix})
#
#add_executable(readEventInformation readEventInformation.C )
#
#target_link_libraries(readEventInformation ClassesDict ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} Cintex)
#----------------------------------------------------------------------------


#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this example standalone
#----------------------------------------------------------------------------

add_custom_target(${myproj} DEPENDS ${myexe})

#----------------------------------------------------------------------------
# OPTIONAL: Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#----------------------------------------------------------------------------

#install(TARGETS ${myexe} DESTINATION bin)
