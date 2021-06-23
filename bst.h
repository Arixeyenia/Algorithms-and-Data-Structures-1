//A node in the binary search tree
struct bstNode {
    char *puDateTime;
    struct bstNode *left;
    struct bstNode *right;
    struct LinkedList *next;
    struct record *tripRecord;
};

//Inserts a record into binary search tree
struct bstNode *bstInsert(struct bstNode *parent, struct record *tripRecord);

//Searches the BST for the search key specified, returns the results of search
struct record **bstSearch(struct bstNode *parent, int search, char *keys, struct record **results, int *counter, int *noOfResults);

//Frees memory allocated to each node
void freeTree(struct bstNode *parent);