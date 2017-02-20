cmake_minimum_required(VERSION 3.6)

project(demo-python-embedded-qt-app--with-cmake)


# load user's configuration file... if any
set(with-user-config "${CMAKE_CURRENT_SOURCE_DIR}/config.cmake" CACHE PATH "You have a user-specific configuration file? Where is it?")
if(EXISTS ${with-user-config})
   include(${with-user-config})
endif()

# get cidco-cmake-tools
find_package(CCT)
if(NOT CCT_FOUND)
   message(FATAL_ERROR "UNABLE TO FIND CIDCO CMAKE TOOLS (CTT)\nFor more information, see: http://github.com/jvtrudel/cidco-cmake-tools")
endif()



# Qt library
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE(Qt5 COMPONENTS Core Widgets REQUIRED)


# example library
add_library(mLib src/embeddedPy.cpp src/config.h)
target_include_directories(mLib PUBLIC ${PYTHON_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin)
target_link_libraries(mLib ${PYTHON_LIBRARY})



# example application
add_executable(mApp src/qt-app.cpp ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(mApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mApp mLib Qt5::Widgets Qt5::Core)


# install system libraries
include(InstallRequiredSystemLibraries)
INSTALL(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
    DESTINATION bin
    )

# install li and app
install(TARGETS mLib mApp
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
    )


# copy python at build time
get_filename_component(PYTHON_DIR ${PYTHON_EXECUTABLE} DIRECTORY)
add_custom_command(TARGET mLib PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_SOURCE_DIR}/src/config.h ${CMAKE_BINARY_DIR}/bin/config.h
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/scripts ${CMAKE_BINARY_DIR}/scripts
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PYTHON_DIR}/libs ${CMAKE_BINARY_DIR}/lib
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PYTHON_DIR}/Libs ${CMAKE_BINARY_DIR}/lib
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PYTHON_DIR}/include ${CMAKE_BINARY_DIR}/include
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${PYTHON_DIR}/python36.dll ${CMAKE_BINARY_DIR}/bin/python36.dll
                       )


# copy python at install time
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/config.h
        DESTINATION bin)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts
        DESTINATION scripts
        FILES_MATCHING PATTERN "*.py")
    install(FILES ${PYTHON_DIR}/python3.dll ${PYTHON_DIR}/python36.dll
        DESTINATION bin)
    install(DIRECTORY ${PYTHON_DIR}/libs/
        DESTINATION lib)
    install(DIRECTORY ${PYTHON_DIR}/Lib/
        DESTINATION lib)
    install(DIRECTORY ${PYTHON_DIR}/include/
        DESTINATION include)



# install QT   # copied/modified from... somewhere on the net
get_filename_component (QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
find_program (QT_WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_BIN_DIR}")
message("QT_WINDEPLOYQT_EXECUTABLE... ${QT_BIN_DIR}")
if (QT_WINDEPLOYQT_EXECUTABLE)
   file (TO_NATIVE_PATH "${QT_BIN_DIR}" QT_BIN_DIR_NATIVE)

   # It's safer to use `\` separateors in the Path, but we need to escape them
   string (REPLACE "\\" "\\\\" QT_BIN_DIR_NATIVE "${QT_BIN_DIR_NATIVE}")
   # Get the name of the executable
   get_target_property(appName mApp OUTPUT_NAME)
   message("appName ${CMAKE_INSTALL_PREFIX}/bin/mApp.exe")
   install (CODE "
       message (STATUS \"Running Qt Deploy Tool...\")
       execute_process (COMMAND
           \"${CMAKE_COMMAND}\" -E env
           \"Path=${QT_BIN_DIR_NATIVE};\$ENV{SystemRoot}\\\\System32;\$ENV{SystemRoot}\"
           \"${QT_WINDEPLOYQT_EXECUTABLE}\"
           \"\${CMAKE_INSTALL_PREFIX}/bin/mApp.exe\"
           --verbose 1)
   ")
endif ()




# PACKAGING

set(CPACK_GENERATOR NSIS)
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CPACK_PACKAGE_NAME "demo-python-embedded-qt-app--with-cmake")
set(CPACK_PACKAGE_VENDOR "cidco.ca")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Demonstration of python embedded c++ Qt Application")
set(CPACK_PACKAGE_VERSION "0.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "demo-python-embedded-qt-app--with-cmake")
SET(CPACK_NSIS_MODIFY_PATH ON)
set(CPACK_NSIS_DEFINES "RequestExecutionLevel user")

INCLUDE(CPack)
