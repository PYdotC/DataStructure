#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct AVLTreeRoot AVLTreeRoot;
typedef struct AVLTreeNode AVLTreeNode;

struct AVLTreeNode {
	union {
		void* pointValue;
		int intValue;
	} value;

	int height;
	struct AVLTreeNode* left;
	struct AVLTreeNode* right;
	struct AVLTreeNode* parent;
};

struct AVLTreeRoot {
	struct AVLTreeNode* root;
	int(*compare) (AVLTreeNode* node1, AVLTreeNode* node2);
};

#define TREE_VALUE(node) ((node)->value.intValue)
#define TREE_LEFT_VALUE(node) ((node)->left->value.intValue)
#define TREE_RIGHT_VALUE(node) ((node)->right->value.intValue))
#define TREE_HEIGHT(node) ((node)->height)
#define LEFT_NODE(node) ((node)->left)
#define RIGHT_NODE(node) ((node)->right)
#define PARENT_NODE(node) ((node)->parent)

AVLTreeRoot* createAVLTree(int(*comapreFunc) (AVLTreeNode* node1, AVLTreeNode* node2));
void insertAVLTreeNode(AVLTreeRoot* root, AVLTreeNode* node);
AVLTreeNode* searchAVLTreeParentNode(AVLTreeRoot *root, int value);
AVLTreeNode* searchAVLTreePrevNode(AVLTreeRoot *root);
AVLTreeNode* searchAVLTreeNextNode(AVLTreeRoot *root);
AVLTreeNode* searchAVLTreeNode(AVLTreeRoot *root, int value);
AVLTreeNode* deleteAVLTreeNode(AVLTreeRoot *root, int value);
void destroyAVLTree(AVLTreeRoot *treeRoot);
void printAVLTree(AVLTreeRoot *treeRoot);



#endif