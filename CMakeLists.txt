# CMakeList.txt: проект CMake для FuzzyLogic

cmake_minimum_required (VERSION 3.8)

project ("FuzzyLogic")

# Указать путь до библиотеки boost (ublas)
# set(BOOST_DIR "")

set(INCLUDE_DIR "./include")
set(SRC_DIR "./src")

set(SRC_FILES 
		"${SRC_DIR}/main.cpp" )

set(HEADER_FILES
		"${INCLUDE_DIR}/main.h"
        "${INCLUDE_DIR}/FuzzyLogic.h"
        "${INCLUDE_DIR}/FuzzySet.h"
        "${INCLUDE_DIR}/FuzzyRules.h")

include_directories(${BOOST_DIR})

add_executable (FuzzyLogic ${SRC_FILES} ${HEADER_FILES})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FuzzyLogic PROPERTY CXX_STANDARD 20)
endif()
