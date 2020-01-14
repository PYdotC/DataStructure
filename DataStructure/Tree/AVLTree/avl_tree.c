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

void rebalance(AVLTreeRoot* root, AVLTreeNode* rootNode) {
	int leftHeight = calculateTreeNodeHeight(LEFT_NODE(rootNode));
	int rightHeight = calculateTreeNodeHeight(RIGHT_NODE(rootNode));
	if (abs(leftHeight - rightHeight) >= 2) {
		if (leftHeight - rightHeight >= 2) {
			if (TREE_HEIGHT(LEFT_NODE(rootNode)) > TREE_HEIGHT(RIGHT_NODE(rootNode))) {
				singleRotateRight(root, rootNode);
			}
			else {
				doubleRotateLeftRight(root, rootNode);
			}
		}
		else {
			if (TREE_HEIGHT(LEFT_NODE(rootNode)) < TREE_HEIGHT(RIGHT_NODE(rootNode))) {
				singleRotateLeft(root, rootNode);
			}
			else {
				doubleRotateRightLeft(root, rootNode);
			}
		}
	}
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

	rebalance(root, rootNode);

	TREE_HEIGHT(rootNode) = calculateTreeNodeHeight(rootNode);
}

void insertAVLTreeNode(AVLTreeRoot* root, AVLTreeNode* node) {
	if (root->root == NULL) {
		root->root = node;
		TREE_HEIGHT(node) = 1;
		PARENT_NODE(node) = NULL;
		LEFT_NODE(node) = NULL;
		RIGHT_NODE(node) = NULL;
		return;
	}
	addAVLTreeNode(root, root->root, node);
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

AVLTreeNode* findAVLNode(AVLTreeNode* rootNode, int value) {
	if (rootNode == NULL) {
		return NULL;
	}

	if (TREE_VALUE(rootNode) == value) {
		return rootNode;
	}

	if (TREE_VALUE(rootNode) > value) {
		return findAVLNode(LEFT_NODE(rootNode), value);
	}
	else {
		return findAVLNode(RIGHT_NODE(rootNode), value);
	}
}

AVLTreeNode* searchAVLTreeNode(AVLTreeRoot *root, int value) {
	return findAVLNode(root->root, value);
}

AVLTreeNode* searchAVLTreeParentNode(AVLTreeRoot *root, int value) {
	AVLTreeNode* node = findAVLNode(root->root, value);
	if (node != NULL) {
		return PARENT_NODE(node);
	}

	return NULL;
}

AVLTreeNode* searchAVLTreePrevNode(AVLTreeNode* root) {
	AVLTreeNode* node = LEFT_NODE(root);
	if (node != NULL) {
		while (RIGHT_NODE(node) != NULL) {
			node = RIGHT_NODE(node);
		}
	}
	return node;
}

AVLTreeNode* searchAVLTreeNextNode(AVLTreeNode *root) {
	AVLTreeNode* node = RIGHT_NODE(root);
	if (node != NULL) {
		while (LEFT_NODE(node) != NULL) {
			node = LEFT_NODE(node);
		}
	}
	return node;
}

AVLTreeNode* deleteAVLNode(AVLTreeRoot* root, AVLTreeNode* rootNode, int value) {
	if (rootNode == NULL) {
		return NULL;
	}

	if (TREE_VALUE(rootNode) == value) {
		if (LEFT_NODE(rootNode) != NULL && RIGHT_NODE(rootNode) != NULL) {
			if (TREE_HEIGHT(LEFT_NODE(rootNode)) > TREE_HEIGHT(RIGHT_NODE(rootNode))) {
				AVLTreeNode* prevNode = searchAVLTreePrevNode(rootNode);
				if (PARENT_NODE(rootNode) == NULL) {
					root->root = prevNode;
				}
				else {
					if (TREE_LEFT_VALUE(PARENT_NODE(rootNode)) == TREE_VALUE(prevNode))
						LEFT_NODE(PARENT_NODE(rootNode)) = prevNode;
					else
						RIGHT_NODE(PARENT_NODE(rootNode)) = prevNode;
				}
			}
		}

	}
	else if (value < TREE_VALUE(rootNode)) {

	}
	else if (value > TREE_VALUE(rootNode)) {

	}
}

AVLTreeNode* deleteAVLTreeNode(AVLTreeRoot *root, int value) {
	AVLTreeNode* deleteNode = searchAVLTreeNode(root, value);
	if (deleteNode == NULL) {
		return NULL;
	}

	/**
	 * situation1: Both left node and right node are NULL
	 */

	if (LEFT_NODE(deleteNode) == NULL && RIGHT_NODE(deleteNode) == NULL) {
		BSTTreeNode* parentNode = searchBSTTreeParentNode(root, TREE_VALUE(deleteNode));
		if (parentNode != NULL) {
			if (TREE_RIGHT_VALUE(parentNode) == TREE_VALUE(deleteNode))
				RIGHT_NODE(parentNode) = NULL;
			else
				LEFT_NODE(parentNode) = NULL;
		}
		return deleteNode;
	}

	if (LEFT_NODE(deleteNode) == NULL || RIGHT_NODE(deleteNode) == NULL) {
		BSTTreeNode* parentNode = searchBSTTreeParentNode(root, TREE_VALUE(deleteNode));
		if (parentNode != NULL) {
			if (TREE_RIGHT_VALUE(parentNode) == TREE_VALUE(deleteNode))
				RIGHT_NODE(parentNode) = LEFT_NODE(deleteNode) != NULL ? LEFT_NODE(deleteNode) : RIGHT_NODE(deleteNode);
			else
				LEFT_NODE(parentNode) = LEFT_NODE(deleteNode) != NULL ? LEFT_NODE(deleteNode) : RIGHT_NODE(deleteNode);
		}
		else {
			root->root = LEFT_NODE(deleteNode) != NULL ? LEFT_NODE(deleteNode) : RIGHT_NODE(deleteNode);
		}
		return deleteNode;
	}

	BSTTreeNode* parentNode = searchBSTTreeParentNode(root, TREE_VALUE(deleteNode));
	BSTTreeNode* nextNode = searchBSTTreeNextNode(deleteNode);
	BSTTreeNode* nextNodeParent = searchBSTTreeParentNode(root, TREE_VALUE(nextNode));
	if (parentNode != NULL) {
		if (TREE_RIGHT_VALUE(parentNode) == TREE_VALUE(deleteNode))
			RIGHT_NODE(parentNode) = nextNode;
		else
			LEFT_NODE(parentNode) = nextNode;
	}
	else {
		root->root = nextNode;
	}

	if (TREE_VALUE(nextNodeParent) != TREE_VALUE(deleteNode)) {
		LEFT_NODE(nextNodeParent) = RIGHT_NODE(nextNode);
	}

	LEFT_NODE(nextNode) = LEFT_NODE(deleteNode);
	RIGHT_NODE(nextNode) = RIGHT_NODE(deleteNode);

	return deleteNode;
}