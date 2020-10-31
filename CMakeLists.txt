# CMakeList.txt : CMake project for DSA, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 17)

project ("DSA")

# Add source to this project's executable.
#add_executable (DSA "insertionSort.cpp" "header.h")
#add_executable(DSA "BinarySum.cpp" "header.h")
#add_executable(DSA "MaximumSumArray.cpp" "header.h" "cpp.hint" "HeapSort.cpp")
#add_executable(DSA "header.h" "cpp.hint" "HeapSort.cpp" "QuickSort.cpp")
#add_executable(DSA "header.h" "cpp.hint" "QuickSort.cpp")
#add_executable(DSA "header.h" "cpp.hint" "BST.cpp")
#add_executable(DSA "header.h" "cpp.hint" "RBTree.cpp")
add_executable(DSA "header.h" "cpp.hint" "AVL.cpp")

# TODO: Add tests and install targets if needed.
