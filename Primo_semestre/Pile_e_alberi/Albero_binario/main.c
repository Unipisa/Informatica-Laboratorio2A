#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* t_new(int v){
    TreeNode *n = malloc(sizeof(TreeNode)); 
    n->value=v; 
	n->left=n->right=NULL; 
	return n;
}
void t_free(TreeNode *r){
    if(!r) return; 
	t_free(r->left); 
	t_free(r->right); 
	free(r);
}

int main(void){
    //      8
    //    /   \
    //   4     12
    //  / \   /  \
    // 2  6  10  14

    TreeNode *r = t_new(8);
    r->left = t_new(4);  r->right = t_new(12);
    r->left->left  = t_new(2);  r->left->right  = t_new(6);
    r->right->left = t_new(10); r->right->right = t_new(14);

    printf("Root=%d, L=%d, R=%d\n", r->value, r->left->value, r->right->value);

    t_free(r);
    return 0;
}
