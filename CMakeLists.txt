#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.12...3.20)

project(Brachy)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available Vis drivers by default
# You can set WITH_GEANT4_VIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" OFF)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})
# Setup of ROOT ANALYSIS : optional. 
#option(WITH_ANALYSIS_USE "Build example with analysis objects" OFF)
#if(WITH_ANALYSIS_USE)
#add_definitions(-DUSEROOT)
#else()
#endif()

#----------------------------------------------------------------------------
# Find ROOT (required package)
#
#find_package(ROOT REQUIRED)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include  
                     ${Geant4_INCLUDE_DIR})


#if(WITH_ANALYSIS_USE)
#	EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
#	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")
#endif(WITH_ANALYSIS_USE) 

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(brachy-ir Brachy.cc ${sources} ${headers})

#if(WITH_ANALYSIS_USE)
#	EXECUTE_PROCESS(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
#	set(CMAKE_EXE_LINKER_FLAGS ${ROOT_LD_FLAGS})
#endif(WITH_ANALYSIS_USE)
#target_link_libraries(brachy-ir ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
target_link_libraries(brachy-ir ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build basic_brachy. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#

set(brachy_SCRIPTS
   IodineSourceMacro.mac  LeipzigSourceMacro.mac VisualisationMacro.mac
   macro.C iridium_source_primary.mac iodine_source_primary.mac iridium_source_leipzig_primary.mac
   plot_primary.C  iodine_decay.mac FlexiSourceMacro.mac 
   TG186SourceMacro.mac TG186_iridium_decay.mac OncuraIodineSourceMacro.mac
  )

foreach(_script ${brachy_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS brachy-ir DESTINATION bin)

