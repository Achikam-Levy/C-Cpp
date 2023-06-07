

#include "ProductBST.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>

/**
 * check if line is valid
 * @param line line from the file
 * @return 1 or 0 according to the line
 */
int check_line (const char *line)
{
  const int minus = 45;
  const int space = 32;
  if ((line[0] != space))
  {
    return 1;
  }
  if (!isdigit (line[1]))
  {
    if (line[1] != minus)
    {
      return 1;
    }
  }
  int i = 2;
  while ((line[i] != '\n') && (line[i] != '\0') && (line[i] != '\r'))
  {
    if (!isdigit (line[i]))
    {
      return 1;
    }
    i += 1;
  }
  return 0;
}

/**
 * allocate memory and create node
 * @param name name of the new product
 * @param quantity quantity of the new product
 * @return
 */
Node *creat_node (char *name, int quantity)
{
  if( name == NULL)
  {
    fprintf (stderr, "%s%s",ERROR, INVALID_POINTER);
    return NULL;
  }
  Node *cur_node = malloc (sizeof (Node));
  if (!cur_node)
  {
    fprintf (stderr,  "%s%s",ERROR,ALLOCATION_FAILED);
    return NULL;
  }
  char *new_product_name = malloc (strlen (name) + 1);
  if (!new_product_name)
  {
    fprintf (stderr, "%s%s",ERROR,ALLOCATION_FAILED);
    free (cur_node);
    return NULL;
  }
  strcpy(new_product_name, name);
  cur_node->product.name = new_product_name;
  cur_node->product.quantity = quantity;
  cur_node->right_child = NULL;
  cur_node->left_child = NULL;
  return cur_node;
}


/**
 * add product in the right place
 * @param root root of the tree
 * @param name name of the product to add
 * @param quantity quantity of the product to add
 * @return root of the updated tree
 */
Node *add_product (Node *root, char *name, int quantity)
{
  if( name == NULL)
  {
    fprintf (stderr, "%s%s",ERROR,INVALID_POINTER);
    return root;
  }
  if (quantity <= 0)
  {
    fprintf (stderr, "%s%s",ERROR,INVALID_QUANTITY);
    return root;
  }
  if (root == NULL)
  {
    root = creat_node (name, quantity);
    if (!root)
    {
      return NULL;
    }
    return root;
  }
  else
  {
    if (0 == strcmp (root->product.name, name))
    {
      fprintf (stderr, "%s%s",ERROR,PRODUCT_EXISTS);
      return root;
    }
    if (0 > strcmp (name, root->product.name))
    {
      root->left_child = (add_product (root->left_child, name, quantity));
    }
    if (0 < strcmp (name, root->product.name))
    {
      root->right_child = (add_product (root->right_child, name, quantity));
    }
    return root;
  }
}

/**
 * build bst
 * @param filename file with list of all the products
 * @return root to the builed tree
 */
Node *build_bst (const char *filename)
{
  FILE *protucts_file = fopen (filename, "r");
  if (!protucts_file)
  {
    fprintf (stderr, "%s%s",ERROR,FILE_OPEN_FAILED);
    return NULL;
  }
  char input[MAX_LINE_LENGTH];
  Node *head = NULL;
  while (fgets (input, MAX_LINE_LENGTH, protucts_file))
  {
    if(input[0] == '\n')
    {
      continue;
    }
    char *cur_name = NULL;
    cur_name = strtok (input, ":");
    if (!cur_name)
    {
      return NULL;
    }
    char *tok = strtok (NULL, "\0");
    if (check_line (tok) == 1)
    {
      fprintf (stderr, "%s%s",ERROR,INVALID_LINE);
      continue;
    }
    int quantity = (int) strtol (tok, NULL, 10);
    if (quantity <= 0)
    {
      fprintf (stderr, "%s%s",ERROR,INVALID_QUANTITY);
      continue;
    }
    head = add_product (head, cur_name, quantity);
    if(!head)
    {
      delete_tree (head);
      fprintf (stderr, "%s%s",ERROR,ALLOCATION_FAILED);
      fclose (protucts_file);
      return NULL;
    }
  }
  fclose (protucts_file);
  return head;
}

/***
 * helper function to fined product
 * @param cur_node current node
 * @param name name of node product
 * @return node to the searched node
 */
Node *search_product_helper (Node *cur_node, char *name)
{
  if (cur_node == NULL)
  {
    return NULL;
  }
  int cmp_res = strcmp (cur_node->product.name, name);
  if (0 == cmp_res)
  {
    return (cur_node);
  }
  if (0 < cmp_res)
  {
    return (search_product_helper (cur_node->left_child,
                                    name));
  }
  else
  {
    return (search_product_helper (cur_node->right_child,
                                    name));
  }
}

/***
 * helper function to fined product parent
 * @param cur_node current node
 * @param root root of the tree
 * @param name name of node product
 * @return node to the parent
 */
Node *search_parent_product (Node *cur_node, Node *root, char *name)
{
  if (cur_node == NULL)
  {
    return NULL;
  }
  int cmp_res = strcmp (cur_node->product.name, name);
  if (0 == cmp_res)
  {
    return (root);
  }
  if (0 < cmp_res)
  {
    return (search_parent_product (cur_node->left_child,
                                   cur_node, name));
  }
  else
  {
    return (search_parent_product (cur_node->right_child,
                                   cur_node, name));
  }
}

/**
 * delete node and free memory
 * @param parent parent of the node to delete
 * @param node node to delete
 */
void delete_node ( Node *parent, Node *node)
{
  if (parent == NULL)
  {
    node->right_child = NULL;
    node->left_child = NULL;
    free (node->product.name);
    free (node);
    return;
  }
  if (parent->right_child != NULL)
  {
    if (0 == strcmp (parent->right_child->product.name, node->product.name))
    {
      node->right_child = NULL;
      node->left_child = NULL;
      free (node->product.name);
      free (node);
      parent->right_child = NULL;
      return;
    }
  }
  if (parent->left_child != NULL)
  {
    if (0 == strcmp (parent->left_child->product.name, node->product.name))
    {
      node->right_child = NULL;
      node->left_child = NULL;
      free (node->product.name);
      free (node);
      parent->left_child = NULL;
      return;
    }
  }
}

/**
 * function update product detales
 * @param node_dst node to copy to
 * @param node_src node copy from
 */
void update_product (Node *node_dst, Node *node_src)
{
  char *new_product_name = malloc (strlen (node_src->product.name) + 1);
  if (!new_product_name){
    return;
  }
  strcpy(new_product_name, node_src->product.name);
  free (node_dst->product.name);
  free (node_src->product.name);
  node_dst->product.name = new_product_name;
  node_dst->product.quantity = node_src->product.quantity;
  node_dst->left_child = node_src->left_child;
  node_dst->right_child = node_src->right_child;
  free (node_src);
}

/**
 *
 * @param root root of the tree
 * @param cur_node the current node according to location
 * @param dest_node parent of the deleted node
 * @param name name of the product to delete
 */
void delete_product_helper(Node*root, Node*cur_node, Node*dest_node,
                           char *name)
{
  if(cur_node == NULL)
  {
    return;
  }
  if (cur_node->left_child == NULL)
  {
    char *new_product_name = malloc (strlen (cur_node->product.name) + 1);
    if (!new_product_name)
    {
      return;
    }
    strcpy(new_product_name, cur_node->product.name);
    free (dest_node->product.name);
    int tmp_qnt = cur_node->product.quantity;
    delete_product (root, cur_node->product.name);
    dest_node->product.name = new_product_name;
    dest_node->product.quantity = tmp_qnt;
    return;
  }
  delete_product_helper(root, cur_node->left_child, dest_node,  name);
}
/**
 *
 * @param root root of the tree
 * @param name of the protuct to delete
 * @return node to the root of the updated tree
 */
Node *delete_product (Node *root, char *name)
{
  if(root == NULL)
  {
    fprintf (stderr, "%s%s",ERROR,PRODUCT_NOT_FOUND);
    return root;
  }
  if(name == NULL)
  {
    fprintf (stderr, "%s%s",ERROR,INVALID_POINTER);
    return root;
  }
  Node *cur = search_product_helper (root, name);
  if (cur == NULL)
  {
    fprintf (stderr, "%s%s",ERROR,PRODUCT_NOT_FOUND);
    return root;
  }
  Node *parent = search_parent_product (root, NULL, name);
//  case 1
  if ((cur->right_child == NULL) && (cur->left_child == NULL))
  {

    delete_node (parent, cur);
    return root;
  }
//  case 2
  else if ((cur->right_child == NULL) && (cur->left_child != NULL))
  {
    update_product (cur, cur->left_child);
    return root;
  }
  else if ((cur->right_child != NULL) && (cur->left_child == NULL))
  {
    update_product (cur, cur->right_child);
    return root;
  }
//  case 3
  else
  {
    delete_product_helper (root, cur->right_child, cur, name);
  }
  return root;
}

/**
 *
 * @param root root of the tree
 * @param name name of the product to fined
 * @return Node to searched product
 */
Product *search_product (Node *root, char *name)
{
  if(name == NULL)
  {
    fprintf (stderr, "%s%s",ERROR,INVALID_POINTER);
    return NULL;
  }
  if(root == NULL)
  {
    return NULL;
  }
  Node *searched_product = search_product_helper (root,  name);
  if (searched_product == NULL)
  {
    return NULL;
  }
  return &(searched_product->product);
}


/**
 *
 * @param root root of thw tree
 * @param name name of the product to update
 * @param amount_to_update amount to add to the product
 * @return the root of the updated tree
 */
Node *update_quantity (Node *root, char *name, int amount_to_update)
{
  if((root == NULL) || (name == NULL))
  {
    fprintf (stderr, "%s%s",ERROR,INVALID_POINTER);
    return root;
  }
  Node *cur = search_product_helper (root,  name);
  if (cur == NULL)
  {
    fprintf (stderr, "%s%s",ERROR, PRODUCT_NOT_FOUND);
    return root;
  }
  if ((cur->product.quantity + amount_to_update) < 0)
  {
    fprintf (stderr, "%s%s",ERROR,INVALID_QUANTITY);
    return root;
  }
  else
  {
    cur->product.quantity += amount_to_update;
    if (cur->product.quantity == 0)
    {
      delete_product (root, name);
      return root;
    }
  }
  return root;
}


/**
 * the function call recursively and delete all the tree node
 * @param root root of the tree
 * @param cur_node current node according the location
 */
void delete_tree_helper (Node *root, Node *cur_node)
{
  if ((root->right_child == NULL) && (root->left_child == NULL))
  {
    free (root->product.name);
    free (root);
    return;
  }
  if (cur_node == NULL)
  {
    return;
  }
  if ((cur_node->right_child == NULL) && (cur_node->left_child == NULL))
  {
    delete_product (root, cur_node->product.name);
    return;
  }
  if (cur_node->left_child)
  {
    delete_tree_helper (root, cur_node->left_child);
  }
  if (cur_node->right_child)
  {
    delete_tree_helper (root, cur_node->right_child);
  }
}

void delete_tree (Node *root)
/**
 * the function delete all the tree and free all memory
 * @param root root of the trre
 */
{
  if( root == NULL)
  {
    fprintf (stderr, "ERROR :"INVALID_POINTER);
    return;
  }
  while ((root->right_child) || (root->left_child))
  {
    delete_tree_helper (root, root);
  }
  if ((root->right_child == NULL) && (root->left_child == NULL))
  {
    free (root->product.name);
    free (root);
    return;
  }
}
