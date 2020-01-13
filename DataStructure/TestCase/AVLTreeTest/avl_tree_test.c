#include<stdio.h>
#include<stdlib.h>
#include"avl_tree_test.h"
#include"../../Tree/AVLTree/avl_tree.h"

int compare(AVLTreeNode* node1, AVLTreeNode* node2) {
	return TREE_VALUE(node1) - TREE_VALUE(node2);
}



void AVLTreeTest() {
	int i;
	int numbersLL[] = { 5, 3, 6, 1, 4, 0, 2 };
	int numbersRR[] = { 5, 4, 7, 6, 9, 8, 10 };
	int numbersLR[] = { 10, 5, 15, 1, 7, 6 };
	int numbersRL[] = { 10, 5, 15, 13, 17, 11, 14 };

	AVLTreeRoot* treeRootLL = createAVLTree(compare);
	for (i = 0; i < (sizeof(numbersLL) / sizeof(int)); i++) {
		AVLTreeNode* node = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
		TREE_VALUE(node) = numbersLL[i];
		TREE_HEIGHT(node) = 0;
		PARENT_NODE(node) = NULL;
		LEFT_NODE(node) = NULL;
		RIGHT_NODE(node) = NULL;
		insertAVLTreeNode(treeRootLL, node);
	}
	printf("LL avl tree:\n");
	printAVLTree(treeRootLL);

	destroyAVLTree(treeRootLL);
}

int main() {
	AVLTreeTest();
	system("parse");
}