#include<stdlib.h>
#include<stdio.h>
#include"avl_tree.h"
#include"../../common.h"

#define _DEBUG_

AVLTreeRoot* createAVLTree(int(*compareFunc)(AVLTreeNode* node1, AVLTreeNode* node2)) {
	AVLTreeRoot *root = (AVLTreeRoot*)malloc(sizeof(AVLTreeRoot));
	root->root = NULL;
	root->compare = compareFunc;
	return root;
}

int calculateTreeNodeHeight(AVLTreeNode* root) {
	if (root == NULL) {
		return 0;
	}

	int leftHeight = calculateTreeNodeHeight(LEFT_NODE(root));
	int rightHeight = calculateTreeNodeHeight(RIGHT_NODE(root));
	return rightHeight > leftHeight ? (rightHeight + 1) : (leftHeight + 1);
}

void singleRotateLeft(AVLTreeRoot* root, AVLTreeNode* rootNode) {
	AVLTreeNode* rightNode = RIGHT_NODE(rootNode);
	RIGHT_NODE(rootNode) = LEFT_NODE(rightNode);
	LEFT_NODE(rightNode) = rootNode;
	PARENT_NODE(rightNode) = PARENT_NODE(rootNode);
	PARENT_NODE(rootNode) = rightNode;
	if (PARENT_NODE(rightNode) != NULL) {
		if (RIGHT_NODE(PARENT_NODE(rightNode)) == rootNode) {
			RIGHT_NODE(PARENT_NODE(rightNode)) = rightNode;
		}
		else {
			LEFT_NODE(PARENT_NODE(rightNode)) = rightNode;
		}
	}
	else {
		root->root = rightNode;
	}
	TREE_HEIGHT(rootNode) = calculateTreeNodeHeight(rootNode);
	TREE_HEIGHT(rightNode) = calculateTreeNodeHeight(rightNode);
}

void singleRotateRight(AVLTreeRoot* root, AVLTreeNode* rootNode) {
	AVLTreeNode* leftNode = LEFT_NODE(rootNode);
	LEFT_NODE(rootNode) = RIGHT_NODE(leftNode);
	RIGHT_NODE(leftNode) = rootNode;
	PARENT_NODE(leftNode) = PARENT_NODE(rootNode);
	PARENT_NODE(rootNode) = leftNode;
	if (PARENT_NODE(leftNode) != NULL) {
		if (RIGHT_NODE(PARENT_NODE(leftNode)) == rootNode) {
			RIGHT_NODE(PARENT_NODE(leftNode)) = leftNode;
		}
		else {
			LEFT_NODE(PARENT_NODE(leftNode)) = leftNode;
		}
	}
	else {
		root->root = leftNode;
	}
	TREE_HEIGHT(rootNode) = calculateTreeNodeHeight(rootNode);
	TREE_HEIGHT(leftNode) = calculateTreeNodeHeight(leftNode);
}

void doubleRotateRightLeft(AVLTreeRoot* root, AVLTreeNode* rootNode) {
	singleRotateRight(root, RIGHT_NODE(rootNode));
	singleRotateLeft(root, rootNode);
}

void doubleRotateLeftRight(AVLTreeRoot* root, AVLTreeNode* rootNode) {
	singleRotateLeft(root, LEFT_NODE(rootNode));
	singleRotateRight(root, rootNode);
}

void addAVLTreeNode(AVLTreeRoot* root, AVLTreeNode* rootNode, AVLTreeNode* node) {
	if (root->compare(node, rootNode) > 0) {
		if (RIGHT_NODE(rootNode) == NULL) {
			PARENT_NODE(node) = rootNode;
			RIGHT_NODE(rootNode) = node;
			TREE_HEIGHT(node) = calculateTreeNodeHeight(node);
		}
		else {
			addAVLTreeNode(root, RIGHT_NODE(rootNode), node);
		}
	}
	else {
		if (LEFT_NODE(rootNode) == NULL) {
			PARENT_NODE(node) = rootNode;
			LEFT_NODE(rootNode) = node;
			TREE_HEIGHT(node) = calculateTreeNodeHeight(node);
		}
		else {
			addAVLTreeNode(root, LEFT_NODE(rootNode), node);
		}
	}

	int leftHeight = calculateTreeNodeHeight(LEFT_NODE(rootNode));
	int rightHeight = calculateTreeNodeHeight(RIGHT_NODE(rootNode));
	if (abs(leftHeight - rightHeight) >= 2) {
		if (leftHeight - rightHeight >= 2) {
			if (TREE_VALUE(node) < TREE_VALUE(LEFT_NODE(rootNode))) {
				singleRotateRight(root, rootNode);
			}
			else {
				doubleRotateLeftRight(root, rootNode);
			}
		}
		else {
			if (TREE_VALUE(node) > TREE_VALUE(RIGHT_NODE(rootNode))) {
				singleRotateLeft(root, rootNode);
			}
			else {
				doubleRotateRightLeft(root, rootNode);
			}
		}
	}
	TREE_HEIGHT(rootNode) = calculateTreeNodeHeight(rootNode);
}

void deleteAVLNode(AVLTreeNode* node) {
	if (LEFT_NODE(node) != NULL) {
		deleteAVLNode(LEFT_NODE(node));
		LEFT_NODE(node) = NULL;
	}

	if (RIGHT_NODE(node) != NULL) {
		deleteAVLNode(RIGHT_NODE(node));
		RIGHT_NODE(node) = NULL;
	}

#ifdef _DEBUG_
	printf("delete node:%d\n", TREE_VALUE(node));
#endif
	free(node);
}

void destroyAVLTree(AVLTreeRoot *treeRoot) {
	deleteAVLNode(treeRoot->root);
}

void printAVLTreeNode(AVLTreeNode* node, int depth) {
	if (RIGHT_NODE(node) != NULL) {
		printAVLTreeNode(RIGHT_NODE(node), depth + DELT_DEPTH);
	}
	int i = 0;
	for (i = 0; i < depth; i++) {
		printf(" ");
	}
	printf("%d[%d]\n", TREE_VALUE(node), TREE_HEIGHT(node));
	if (LEFT_NODE(node) != NULL) {
		printAVLTreeNode(LEFT_NODE(node), depth + DELT_DEPTH);
	}
}

void printAVLTree(AVLTreeRoot *treeRoot) {
	printAVLTreeNode(treeRoot->root, 0);
}