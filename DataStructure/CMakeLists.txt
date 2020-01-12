# CMakeList.txt: DataStructure 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

set (DS_VERSION_MAJOR 1)
set (DS_VERSION_MINOR 0)

configure_file (
	"config.h.in"
	"config.h"
)

include_directories (
.
./Tree/AVLTree
./Tree/BinarySearchTree
./TreeCase/BinarySearchTreeTest)

link_directories(./Tree ./Tree/Debug)

# 包含子项目。
add_subdirectory ("Tree")
add_subdirectory ("TestCase")

# 将源代码添加到此项目的可执行文件。
add_executable (DataStructure "DataStructure.cpp" "DataStructure.h")

target_link_libraries(DataStructure)

# TODO: 如有需要，请添加测试并安装目标。
