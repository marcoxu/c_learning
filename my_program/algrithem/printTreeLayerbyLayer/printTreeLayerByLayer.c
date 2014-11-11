#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode{
  int value;
  struct treeNode* left;
  struct treeNode* right;
} node;

typedef struct listNode {
  node* node;
  struct listNode* next;
} ListNode;

ListNode* buildNewNode(node* node) {
  ListNode* tmp = (ListNode*) malloc(sizeof(ListNode));
  tmp->node = node;
  tmp->next = NULL;
}

void printTree(node* root) {
  if(root == NULL) {
    return;
  }
  
  node* changeLine = NULL;
  ListNode* head = (ListNode*) malloc(sizeof(ListNode));
  ListNode* tail = head;
  head->node = root;
  head->next = NULL;
  changeLine = root;

  while(head) {
    if(head->node->left != NULL) {
      ListNode* tmp = buildNewNode(head->node->left);
      tail->next = tmp;
      tail = tmp;
    }
    if(head->node->right != NULL) {
      ListNode* tmp = buildNewNode(head->node->right);
      tail->next = tmp;
      tail = tmp;
    }
    printf(" %d", head->node->value);
    if(head->node == changeLine) {
      printf("\n");
      changeLine = tail->node;
    }
    
    ListNode* tmpHead = head;
    head = head->next;
    free(tmpHead);    
  }  
}

node* buildTree(int depth) {
  if(depth == 0) {
    return NULL;
  }

  node* root = (node*) malloc(sizeof(node));
  root->value = depth;
  root->left = buildTree(depth-1);
  root->right = buildTree(depth-1);
  return root;
}

void freeTree(node* root) {
  if(root == NULL) {
    return;
  }
  
  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

int main() {
  node* root1 = buildTree(5);
  printTree(root1);
  freeTree(root1);
}


