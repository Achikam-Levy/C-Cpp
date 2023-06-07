//
// Created by אחיקם לוי on 21/11/2022.
//
#include "markov_chain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool node_in_counter_last (MarkovNode *first_node);
bool node_in_counter_list (MarkovNode *first_node, MarkovNode *second_node);

/***
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number max_number maximal number to return (not including)
 * @return Random number
 */
int get_random_number (int max_number)
{
  return rand () % max_number;
}

/**
 * Get one random state from the given markov_chain's database.
 * @param markov_chain
 * @return
 */
MarkovNode *get_first_random_node (MarkovChain *markov_chain)
{
  int number = get_random_number ((markov_chain->database->size));
  int i = 0;
  Node *cur = markov_chain->database->first;
  if (cur == NULL)
  {
    return NULL;
  }
  while (i < number && cur != NULL)
  {
    cur = cur->next;
    i++;
  }
  if (node_in_counter_last (cur->data))
  {
    return NULL;
  }
  else
  {
    return cur->data;
  }
}

/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param state_struct_ptr MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode *get_next_random_node (MarkovNode *state_struct_ptr)
{
  if (node_in_counter_last (state_struct_ptr))
  {
    return state_struct_ptr;
  }
  int number = get_random_number (state_struct_ptr->sum_of_followed_words);
  for (int i = 0; i < state_struct_ptr->capacity; ++i)
  {
    number -= state_struct_ptr->counter_list[i].frequency;
    if (number < 0)
    {
      return state_struct_ptr->counter_list[i].markov_node;
    }
  }
  return state_struct_ptr->counter_list[0].markov_node;
}

/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with,
 *                   if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_random_sequence (MarkovChain *markov_chain,
                               MarkovNode *first_node, int max_length)
{
  int i = 1;
  while (first_node == NULL)
  {
    first_node = get_first_random_node (markov_chain);
  }
  MarkovNode *cur_node = first_node;
  while (i < max_length && cur_node != NULL)
  {
    i++;
    if (node_in_counter_last (cur_node) || cur_node->counter_list == NULL)
    {
      fprintf (stdout, " %s", cur_node->data);
      break;
    }
    fprintf (stdout, " %s", cur_node->data);
    cur_node = get_next_random_node (cur_node);
  }
}

/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free
 */
void free_markov_chain (MarkovChain **ptr_chain)
{
  int i = 0;
  MarkovChain *markov_chain = *ptr_chain;
  Node *cur = markov_chain->database->first;
  while (i < markov_chain->database->size)
  {
    Node *tmp = cur->next;
    if (cur->data->counter_list != NULL)
    {
      free (cur->data->counter_list);
    }
    if( cur->data->data != NULL)
    {
      free (cur->data->data);
    }
    if( cur->data != NULL)
    {
      free (cur->data);
    }
    if( cur != NULL)
    {
      free (cur);
    }
    cur = tmp;
    i++;
  }
  free (markov_chain->database);
  free (*ptr_chain);
}

/**
 * checks if node data is an and of a tweet
 * @param first_node node
 * @return  bool value
 */
bool node_in_counter_last (MarkovNode *first_node)
{
  if (first_node == NULL)
  {
    return true;
  }
  if (first_node->data == NULL)
  {
    return true;
  }
  if ((first_node->data[(strlen (first_node->data)) - 1]) == POINT)
  {
    return true;
  }
  return false;
}


/**
 * checks if node is already in the counter list
 * @param first_node the node in the database chain
 * @param second_node the node to check for
 * @return bool value
 */
bool node_in_counter_list (MarkovNode *first_node, MarkovNode *second_node)
{
  int i = 0;
  while (i < first_node->capacity)
  {
    if (strcmp ((first_node->counter_list + i)->markov_node->data,
                second_node->data) == 0)
    {
      ((first_node->counter_list) + i)->frequency += 1;
      first_node->sum_of_followed_words += 1;
      return true;
    }
    i++;
  }
  return false;
}


/**
 * Add the second markov_node to the counter list of the first markov_node.
 * If already in list, update it's counter value.
 * @param first_node
 * @param second_node
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */
bool add_node_to_counter_list (MarkovNode *first_node, MarkovNode *second_node)
{
  if (node_in_counter_last (first_node))
  {
    first_node->counter_list = NULL;
    return true;
  }
  if (node_in_counter_list (first_node, second_node))
  {
    return true;
  }
  else
  {
    first_node->capacity += 1;
    first_node->sum_of_followed_words += 1;
    NextNodeCounter *temp = realloc (first_node->counter_list,
                                     sizeof (NextNodeCounter)
                                     * (first_node->capacity));
    if (!temp)
    {
      fprintf (stdout, "%s%s", ERROR, ALLOCATION_ERROR_MASSAGE);
      return false;
    }
    first_node->counter_list = temp;
    first_node->counter_list[first_node->capacity
                             - 1].markov_node = second_node;
    first_node->counter_list[first_node->capacity - 1].frequency = 1;
    return false;
  }
}

/**
 * Check if data_ptr is in database. If so, return the markov_node wrapping
 * it in
 * the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node *get_node_from_database (MarkovChain *markov_chain, char *data_ptr)
{
  int i = 0;
  Node *cur = markov_chain->database->first;
  while (i < markov_chain->database->size && cur->data->data != NULL)
  {
    if (strcmp (data_ptr, cur->data->data) == 0)
    {
      return (Node *) cur->data;
    }
    cur = cur->next;
    i++;
  }
  return NULL;
}

/**
* If data_ptr in markov_chain, return it's markov_node. Otherwise, create new
 * markov_node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return markov_node wrapping given data_ptr in given chain's database,
 * returns NULL in case of memory allocation failure.
 */
Node *add_to_database (MarkovChain *markov_chain, char *data_ptr)
{
  MarkovNode *node_in =
      (MarkovNode *) get_node_from_database (markov_chain, data_ptr);
  if (node_in != NULL)
  {
    return (Node *) node_in;
  }
  char *word_cpy = malloc (MAX_WORD_SIZE);
  if (word_cpy == NULL)
  {
    fprintf (stdout, "%s%s", ERROR, ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  strcpy (word_cpy, data_ptr);
  MarkovNode *markov_node = malloc (sizeof (MarkovNode));
  if (markov_node == NULL)
  {
    fprintf (stdout, "%s%s", ERROR, ALLOCATION_ERROR_MASSAGE);
    free (word_cpy);
    return NULL;
  }
  markov_node->data = word_cpy;
  markov_node->counter_list = NULL;
  markov_node->sum_of_followed_words = 0;
  markov_node->capacity = 0;
  add (markov_chain->database, markov_node);
  return (Node *) markov_node;
}