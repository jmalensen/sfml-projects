cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME sfml-labyOO)
set(SFMLFINAL_SOURCE_DIR src)
set(SFMLFINAL_SOURCE ${TEMPLATEC_SOURCE_DIR}/main.cpp)

project(${PROJECT_NAME} VERSION 0.1.0)

include(CTest)
enable_testing()

# I../includes
include_directories(/include)

set(SFML_INCLUDE_DIR "/opt/homebrew/Cellar/sfml/2.5.1_2/include")
set(SFML_LIBRARY_DIR "/opt/homebrew/Cellar/sfml/2.5.1_2/lib")

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# puts all .cpp files inside src to the SRC_FILES variable
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# compiles the files defined by SRC_FILES to generante the executable defined by EXEC
add_executable(${PROJECT_NAME} ${SRC_FILES})


# set the C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# message(${CMAKE_SYSTEM})
# message(${CMAKE_SYSTEM_NAME})
# message(${CMAKE_SYSTEM_VERSION})
# message(${CMAKE_SYSTEM_PROCESSOR})
# message(${CMAKE_HOST_SYSTEM_NAME})

# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by default system
if(UNIX)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(WIN32)
    message("This is a Windows System")
endif()# or use MATCHES to see if actual system name 

# Darwin is Apple's system name
if(${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(${CMAKE_SYSTEM_NAME} MATCHES Windows)
    message("This is a Windows System")
endif()

include(CPack)
