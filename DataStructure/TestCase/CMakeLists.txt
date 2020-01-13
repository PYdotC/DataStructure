
add_executable (BinarySearchTest "BinarySearchTreeTest/binary_search_tree_test.c" "BinarySearchTreeTest/binary_search_tree_test.h")
target_link_libraries(BinarySearchTest tree)

add_executable (AVLTreeTest "AVLTreeTest/avl_tree_test.c" "AVLTreeTest/avl_tree_test.h")
target_link_libraries(AVLTreeTest tree)