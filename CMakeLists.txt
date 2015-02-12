project(Variant)
cmake_minimum_required(VERSION 2.8)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-elide-constructors -fno-implement-inlines -fno-implicit-inline-templates -fno-default-inline -fno-inline")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -std=c++11 -Wno-reorder -Werror=return-type")
endif()

set(SRC_LIST
    main.cpp
    variant.h
    README.md
)
add_executable(${PROJECT_NAME} ${SRC_LIST})
