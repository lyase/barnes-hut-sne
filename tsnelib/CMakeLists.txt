cmake_minimum_required(VERSION 2.8)
find_package( BLAS REQUIRED )
project ("tsnelib") 

add_library(tsnelib  vptree.h quadtree.h tsne.cpp quadtree.cpp  vptree.cpp)
target_link_libraries(tsnelib blas  ${blas} ${BLAS_LIBRARIES})
