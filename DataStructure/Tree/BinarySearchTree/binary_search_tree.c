#include<stdlib.h>
#include<stdio.h>
#include"binary_search_tree.h"
#include"../../common.h"

BSTTreeRoot* createBSTTree(int(*compareFunc)(BSTTreeNode* node1, BSTTreeNode* node2)) {
	BSTTreeRoot* root = (BSTTreeRoot*)malloc(sizeof(BSTTreeRoot));
	root->root = NULL;
	root->compare = compareFunc;

	return root;
}

void addBSTNode(BSTTreeRoot* root, BSTTreeNode* rootNode, BSTTreeNode* node) {
	if (root->compare(node, rootNode) > 0) {
		if (RIGHT_NODE(rootNode) == NULL) {
			RIGHT_NODE(rootNode) = node;
		}
		else {
			addBSTNode(root, RIGHT_NODE(rootNode), node);
		}
	}
	else {
		if (LEFT_NODE(rootNode) == NULL) {
			LEFT_NODE(rootNode) = node;
		}
		else {
			addBSTNode(root, LEFT_NODE(rootNode), node);
		}
	}
}

void insertBSTTreeNode(BSTTreeRoot *root, BSTTreeNode *node) {
	if (root->root == NULL) {
		root->root = node;
		return;
	}

	addBSTNode(root, root->root, node);
}

void deleteBSTNode(BSTTreeNode* node) {
	if (LEFT_NODE(node) != NULL) {
		deleteBSTNode(LEFT_NODE(node));
		LEFT_NODE(node) = NULL;
	}

	if (RIGHT_NODE(node) != NULL) {
		deleteBSTNode(RIGHT_NODE(node));
		RIGHT_NODE(node) = NULL;
	}

#ifdef _DEBUG_
	printf("delete node:%d\n", TREE_VALUE(node));
#endif
	free(node);
}

void destroyBSTTree(BSTTreeRoot *treeRoot) {
	deleteBSTNode(treeRoot->root);
}

void printBSTTreeNode(BSTTreeNode* node, int depth) {
	if (RIGHT_NODE(node) != NULL) {
		printBSTTreeNode(RIGHT_NODE(node), depth + DELT_DEPTH);
	}
	int i = 0;
	for (i = 0; i < depth; i++) {
		printf(" ");
	}
	printf("%d\n", TREE_VALUE(node));
	if (LEFT_NODE(node) != NULL) {
		printBSTTreeNode(LEFT_NODE(node), depth + DELT_DEPTH);
	}
}

void printBSTTree(BSTTreeRoot *treeRoot) {
	printBSTTreeNode(treeRoot->root, 0);
}

BSTTreeNode* findBSTNode(BSTTreeNode* node, int value) {
	if (TREE_VALUE(node) == value) {
		return node;
	}

	if (value < TREE_VALUE(node)) {
		return findBSTNode(LEFT_NODE(node), value);
	}
	else {
		return findBSTNode(RIGHT_NODE(node), value);
	}
}

BSTTreeNode* searchBSTTreeNode(BSTTreeRoot* root, int value) {
	return findBSTNode(root->root, value);
}

BSTTreeNode* findParentNode(BSTTreeNode* node, int value) {
	if (LEFT_NODE(node) != NULL) {
		if (TREE_LEFT_VALUE(node) == value)
			return node;
		BSTTreeNode* n = findParentNode(LEFT_NODE(node), value);
		if (n != NULL) {
			return n;
		}
	}

	if (RIGHT_NODE(node) != NULL) {
		if (TREE_RIGHT_VALUE(node) == value)
			return node;
		BSTTreeNode* n = findParentNode(RIGHT_NODE(node), value);
		if (n != NULL) {
			return n;
		}
	}

	return NULL;
}

BSTTreeNode* searchBSTTreeParentNode(BSTTreeRoot* root, int value) {
	if (TREE_VALUE(root->root) == value) {
		return NULL;
	}

	return findParentNode(root->root, value);
}

BSTTreeNode* searchBSTTreeNextNode(BSTTreeNode* node) {
	if (RIGHT_NODE(node) == NULL) {
		return NULL;
	}

	BSTTreeNode* nextNode = RIGHT_NODE(node);
	while (LEFT_NODE(nextNode) != NULL) {
		nextNode = LEFT_NODE(nextNode);
	}
	return nextNode;
}

BSTTreeNode* searchBSTTreePrevNode(BSTTreeNode* node) {
	if (LEFT_NODE(node) == NULL) {
		return NULL;
	}

	BSTTreeNode* prevNode = LEFT_NODE(node);
	while (RIGHT_NODE(prevNode) != NULL) {
		prevNode = RIGHT_NODE(prevNode);
	}
	return prevNode;
}

BSTTreeNode* deleteBSTTreeNode(BSTTreeRoot* root, int value) {
	BSTTreeNode* deleteNode = searchBSTTreeNode(root, value);
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