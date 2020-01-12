# CMakeList.txt: DataStructure 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project(tree VERSION 1.0)

#add_subdirectory("AVLTree" "BinarySearchTree")

add_library(tree STATIC
"AVLTree/avl_tree.c"
"AVLTree/avl_tree.h"
"BinarySearchTree/binary_search_tree.c"
"BinarySearchTree/binary_search_tree.h")

install (TARGETS tree DESTINATION $(PROJECT_SOURCE_DIR))
install (FILES AVLTree/*.h DESTINATION $(PROJECT_SOURCE_DIR)/include)
install (FILES BinarySearchTree/*.h DESTINATION $(PROJECT_SOURCE_DIR)/include)