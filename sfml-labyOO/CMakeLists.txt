
cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME sfml-labyOO)
set(SFMLFINAL_SOURCE_DIR src)
set(SFMLFINAL_SOURCE ${TEMPLATEC_SOURCE_DIR}/main.cpp)

project(${PROJECT_NAME} VERSION 0.1.0)

#set(CMAKE_CXX_COMPILER "C:\\Devc++\\mingw64\\bin\\g++.exe")
#set(CMAKE_C_COMPILER "C:\\Devc++\\mingw64\\bin\\gcc.exe")

## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)

include(CTest)
enable_testing()

# I../includes
include_directories(/include)

# set(SFML_INCLUDE_DIR "C:\\Devc++\\SFML-2.5.1\\include")
# set(SFML_LIBRARY_DIR "C:\\Devc++\\SFML-2.5.1\\lib")

# include_directories(${SFML_INCLUDE_DIR})
# link_directories(${SFML_LIBRARY_DIR})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# puts all .cpp files inside src to the SRC_FILES variable
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# compiles the files defined by SRC_FILES to generante the executable defined by EXEC
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/lib)

# option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# set the C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

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

# include(InstallRequiredSystemLibraries)
include(CPack)
