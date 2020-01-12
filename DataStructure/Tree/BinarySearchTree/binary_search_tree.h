#ifndef DATASTRUCTURE_BINARY_SEARCH_TREE_H
#define DATASTRUCTURE_BINARY_SEARCH_TREE_H

typedef struct BSTTreeRoot BSTTreeRoot;
typedef struct BSTTreeNode BSTTreeNode;
typedef enum TreeType TreeType;

enum TreeType {
	TREE_TYPE_INVALID,
	TREE_TYPE_INT,
	TREE_TYPE_POINTER
};

struct BSTTreeNode {
	union {
		void* pointValue;
		int intValue;
	} value;

	struct BSTTreeNode* left;
	struct BSTTreeNode* right;
	enum TreeType type;
};

struct BSTTreeRoot {
	struct BSTTreeNode* root;
	int(*compare) (BSTTreeNode* node1, BSTTreeNode* node2);
};

#define TREE_VALUE(node) ((node)->value.intValue)
#define TREE_LEFT_VALUE(node) ((node)->left->value.intValue)
#define TREE_RIGHT_VALUE(node) ((node)->right->value.intValue)

#define LEFT_NODE(node) ((node)->left)
#define RIGHT_NODE(node) ((node)->right)

BSTTreeRoot* createBSTTree(int(*compareFunc)(BSTTreeNode* node1, BSTTreeNode* node2));
void insertBSTTreeNode(BSTTreeRoot* root, BSTTreeNode* node);
BSTTreeNode* searchBSTTreeParentNode(BSTTreeRoot* root, int value);
BSTTreeNode* searchBSTTreePrevNode(BSTTreeNode* node);
BSTTreeNode* searchBSTTreeNextNode(BSTTreeNode* node);
BSTTreeNode* searchBSTTreeNode(BSTTreeRoot* root, int value);
BSTTreeNode* deleteBSTTreeNode(BSTTreeRoot* root, int value);
void destroyBSTTree(BSTTreeRoot *treeRoot);
void printBSTTree(BSTTreeRoot* treeRoot);

#endif
