#include <stdlib.h>
#include <stdio.h>
#include "ProductBST.h"

#define ARGC_ERROR_MSG "ERROR: Wrong number of arguments.\nUsage: main <path2to file>\n"

#define COUNT 10

void print2DUtil(struct Node* root, int space)
{

  if (root == NULL)
    return;
  space += COUNT;
  print2DUtil(root->right_child, space);

  printf("\n");
  for (int i = COUNT; i < space; i++)
    printf(" ");
  printf("%s:%d\n", root->product.name,root->product.quantity);
  print2DUtil(root->left_child, space);
}


void print2D(struct Node* root)
{
  print2DUtil(root, 1);
}
/**
 * main to run functions from Ex2
 */

typedef struct Stack
{
    size_t stackCapacity; /* number of elements the stack can contain */
    size_t numOfElems; /* number of elements are currently in the stack */
    int *data;
} Stack;

void printStack(Stack *myStack)
{
  if (myStack == NULL)
  {
    return;
  }

  for(size_t i = 0; i < myStack->numOfElems; ++i)
  {
    printf("%d, ", myStack->data[i]);
  }

  printf("\n");

  printf("numOfElems: %lu, stackCapacity: %lu\n",
         myStack->numOfElems, myStack->stackCapacity);
}

void deleteStack(Stack **myStack)
{
  if (*myStack == NULL)
  {
    return;
  }

  if ((*myStack)->data != NULL)
  {
    free((*myStack)->data);
  }
  free(*myStack);
  *myStack = NULL;
}

Stack *newStack(void)
{
  Stack *myStack = (Stack *) malloc(sizeof(Stack));
  myStack->data = (int *) malloc(sizeof(int));
  myStack->stackCapacity = 1;
  myStack->numOfElems = 0;
  return myStack;
}

void push (Stack *s, int n)
{
  size_t p = s->numOfElems;
  if (s->numOfElems+1 == s->stackCapacity)
  {
    s=realloc (s, sizeof (s) * 2);
    s->data =realloc (s->data, sizeof (s->data) * 2);
    s->stackCapacity *= 2;
  }
  s->numOfElems += 1;
  s->data[p] = n;
}


int pop(Stack *stack)
{
  size_t p = stack->numOfElems;
  if ((stack->numOfElems)*4 <= stack->stackCapacity)
  {
    stack = realloc (stack, sizeof (stack) / 2);
    stack->data = realloc (stack->data, sizeof (stack->data) / 2);
    stack->stackCapacity /= 2;
  }
  stack->numOfElems -= 1;
//  stack->data[p] = 0;
  return stack->data[p];
}




int main (int argc, char *argv[])
{
  if (argc < 2)
    {
      fprintf (stderr, ARGC_ERROR_MSG);
      return EXIT_FAILURE;  // EXIT_FAILURE is a macro for 1. Only to be used as return value from main or
      // parameter to exit()! Don't use it to replace 1 in function return value etc.
    }
//   parse from file products BST
  Node *root = build_bst (argv[1]);
//   add new product to the tree, search and delete it
//  root = add_product (root, "New Laptop", 80);
//  Product *new_laptop = search_product (root, "Dell Alienware");
//  print2D(root);
//  delete_product(root, "HP Elitebook");
//  root = update_quantity(root, "Lenovo Yoga", -139);
//   add another new product, and update it
//  root = add_product (root, NULL, 20);
//  root = add_product (root, "z", 2);
//  root = update_quantity (root, "z", -92);
//  root = delete_product(root, "f");
//  Product *i = search_product (root, "i");
//
//  printf ("%s", "\n\n\n\n\n\n\n\n");
//
//  delete_tree (root);
//  root = delete_product (root,"Dell Alienware");
//  root = delete_product (root,"G");
//  root = delete_product (root,"L");
  print2D(root);

  return EXIT_SUCCESS; // macro for 0. Like EXIT_FAILURE, not to be used for function return values!!
}
