cmake_minimum_required(VERSION 3.1)
project(myproj)

find_package(OpenSSL REQUIRED)

# One of two lines present depending on if output is a library (shared or static) or an executable
#add_library(mytarget)
add_executable(mytarget)

target_include_directories(mytarget
    PUBLIC
		${OPENSSL_INCLUDE_DIR}
)

# Both all source and header files (.cpp and .h) should be listed in target_sources
# (So basically all files in 'src' directory and recursivley in all subdirectories)
target_sources(mytarget
	PRIVATE
		mytarget.cpp
)

# Incase there are any shared or static libraries that we are linking to
target_link_libraries(mytarget
	${OPENSSL_LIBRARIES}
)
set(CMAKE_BUILD_TYPE Debug)
