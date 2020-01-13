#include<stdio.h>
#include<stdlib.h>
#include"../../Tree/BinarySearchTree/binary_search_tree.h"
#include"binary_search_tree_test.h"

int compareBSTTreeNode(BSTTreeNode* node1, BSTTreeNode* node2) {
	return node1->value.intValue - node2->value.intValue;
}

int main() {
	BSTTest1();
}

void BSTTest1() {
	int numbers[] = { 10, 4, 2, 7, 1, 3, 6, 8, 15, 13, 18, 12, 14, 16, 20 };
	BSTTreeRoot* treeRoot = createBSTTree(compareBSTTreeNode);
	int i = 0;
	for (i = 0; i < sizeof(numbers) / sizeof(int); i++) {
		BSTTreeNode* node = (BSTTreeNode*)malloc(sizeof(BSTTreeNode));
		node->value.intValue = numbers[i];
		node->left = NULL;
		node->right = NULL;
		node->type = TREE_TYPE_INT;
		insertBSTTreeNode(treeRoot, node);
	}

	printBSTTree(treeRoot);

	BSTTreeNode* node1 = searchBSTTreeNode(treeRoot, 9);
	if (node1 != NULL) {
		printf("find node %d;\n", TREE_VALUE(node1));
	}
	else {
		printf("not find node %d;\n", 9);
	}

	BSTTreeNode* node2 = searchBSTTreeParentNode(treeRoot, 6);
	if (node2 != NULL) {
		printf("find node %d parent node %d\n", 6, TREE_VALUE(node2));
	}
	else {
		printf("not find node %d parent node\n", 6);
	}

	BSTTreeNode* node3 = searchBSTTreeParentNode(treeRoot, 4);
	if (node3 != NULL) {
		printf("find node %d parent node is %d\n", 4, TREE_VALUE(node3));
	}
	else {
		printf("not find node %d parent node\n", 4);
	}

	BSTTreeNode* node8 = searchBSTTreeParentNode(treeRoot, 8);
	if (node8 != NULL) {
		printf("find node %d parent node is %d\n", 8, TREE_VALUE(node8));
	}
	else {
		printf("not find node %d parent node\n", 8);
	}

	BSTTreeNode* node4 = searchBSTTreeParentNode(treeRoot, TREE_VALUE(treeRoot->root));
	if (node4 != NULL) {
		printf("find node %d parent node is %d;\n", TREE_VALUE(treeRoot->root), TREE_VALUE(node4));
	}
	else {
		printf("not find node %d parent node;\n", TREE_VALUE(treeRoot->root));
	}

	BSTTreeNode* node5 = searchBSTTreeNextNode(treeRoot->root);
	if (node5 != NULL) {
		printf("find node %d next node is %d;\n", TREE_VALUE(treeRoot->root), TREE_VALUE(node5));
	}
	else {
		printf("not find node %d next node;\n", TREE_VALUE(treeRoot->root));
	}

	BSTTreeNode* node6 = deleteBSTTreeNode(treeRoot, 15);
	if (node6 != NULL) {
		printf("delete node %d\n", TREE_VALUE(node6));
		free(node6);
	}
	else {
		printf("node %d not exists\n", 15);
	}

	printf("after delete node %d\n", 15);
	printBSTTree(treeRoot);

	BSTTreeNode* node7 = searchBSTTreePrevNode(searchBSTTreeNode(treeRoot, 16));
	if (node7 != NULL) {
		printf("node %d prev node is %d\n", 16, TREE_VALUE(node7));
	}
	else {
		printf("node %d prev node is NULL\n", 16);
	}

	destroyBSTTree(treeRoot);

	system("pause");
}