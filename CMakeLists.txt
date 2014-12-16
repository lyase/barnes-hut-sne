#    add_definitions(-std=c++11 -DHAVE_CPP11)
project(fortranc Fortran C)
cmake_minimum_required(VERSION 2.8)
find_package( BLAS REQUIRED )
#find_library(blas NAMES )
# This is the cmake file. It describes how to build our app
# The documentation for how to build these can be found here:
#   http://www.cmake.org/cmake/help/cmake-2-8-docs.html

# CMake likes us to put this here in case someone tries to read this file with an older version of cmake
cmake_minimum_required(VERSION 2.8) # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:cmake_minimum_required

# Sets the name of the project. Additionally this sets the variables <projectName>_BINARY_DIR and <projectName>_SOURCE_DIR to the respective values.
project ("hello world in c++")      # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:project
# g++ -g -Wall quadtree.cpp tsne.cpp makedata.cpp -o makedata -O3 -I./CBLAS/include -L./ -lblas
#g++ -g -Wall quadtree.cpp tsne.cpp -o bh_tsne -O3 -I./CBLAS/include -L./ -lblas
#
# This tells cmake that we want to create an executable called 'hello' and the source files are just 'main.cpp'
#add_executable(hello  quadtree.cpp tsne.cpp makedata.cpp )
add_executable(bh_tsne  quadtree.cpp tsne.cpp vptree.h )
TARGET_LINK_LIBRARIES(bh_tsne  blas  ${blas} ${BLAS_LIBRARIES})
project(makedata )
add_executable(makedata makedata.cpp  )
TARGET_LINK_LIBRARIES(makedata blas  ${blas} ${BLAS_LIBRARIES})
