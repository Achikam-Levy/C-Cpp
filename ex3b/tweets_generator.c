
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "markov_chain.h"


void initialize_markov_chain(MarkovChain *markov_chain, LinkedList *list);

/**
 * compare between to tweets words
 * @param a_ptr pointer to first markov node
 * @param b_ptr pointer to second markov node
 * @return result of compare
 */
static int cmp_func_tweets(void * a_ptr, void * b_ptr)
{
  char * a = a_ptr;
  char * b = b_ptr;
  return strcmp (a, b);
}

/**
 * free node memory
 * @param node pointer to a node
 */
static void free_func_tweets(void * node)
{
  free(node);
}

/**
 * copy function for the tweets nodes
 * @param data_ptr pinter to node to copy
 * @return pointer to new copied node
 */
static void * copy_func_tweets(void * data_ptr)
{
  char * dst = malloc (sizeof(char)*MAX_WORD_SIZE);
  if(dst == NULL)
  {
    return NULL;
  }
  strcpy(dst, data_ptr);
  return dst;
}

/**
 * checks if node data is an and of a tweet
 * @param first_node node
 * @return  bool value
 */
static bool node_in_counter_last (void * node)
{
    char *last_word = node;
    int word_length = (int) strlen (last_word);
    if (strcmp (&last_word[word_length - 1], ".") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * print the words of the tweets
 * @param data_ptr
 */
static void print_func_tweets(void * data_ptr)
{
    char * data = data_ptr;

    if (node_in_counter_last(data_ptr))
    {
        printf ("%s", data);
    }
    else
    {
        printf ("%s ", data);
    }
}

/**
 * building a markov chain from given file
 * @param fp file to parse
 * @param words_to_read number of word to read from the file
 * @param markov_chain node to build markov chain from
 * @return Exit success/failure
 */
static int fill_database(FILE *fp,int words_to_read,MarkovChain*markov_chain)
{
  FILE *products_file = fopen ((const char *) fp, "r");
  if (!products_file)
  {
    fprintf (stdout, "%s%s", ERROR, FILE_OPEN_FAILED);
    return EXIT_FAILURE;
  }
  char input[MAX_LINE_LENGTH];
  while ((fgets (input, MAX_LINE_LENGTH, products_file) != NULL) &&
         (words_to_read > 0 || words_to_read < 0))
  {
    char *current_word = NULL;
    MarkovNode *word_before = NULL;
    while (words_to_read > 0 || words_to_read < 0)
    {
      if (word_before == NULL)
      {
        current_word = strtok (input, " \n");
      }
      else
      {
        current_word = strtok (NULL, " \n");
      }
      if (current_word == NULL)
      {
          break;
      }
      words_to_read--;
      if  (0 != markov_chain->comp_func(current_word, "\n"))
      {
        Node *cur_markove_node = add_to_database
            (markov_chain, current_word);
          if (cur_markove_node == NULL)
          {
              fprintf (stdout, "%s%s", ERROR, ALLOCATION_ERROR_MASSAGE);
              return EXIT_FAILURE;
          }
          if (word_before != NULL && !markov_chain->is_last(word_before))
          {
              if (!add_node_to_counter_list(word_before,
                        cur_markove_node->data, markov_chain))
              {
                  fprintf (stdout, "%s%s", ERROR, ALLOCATION_ERROR_MASSAGE);
                  return EXIT_FAILURE;
              }
          }

        word_before = cur_markove_node->data;
      }
    }
  }
  fclose (products_file);
  return EXIT_SUCCESS;
}

/**
 * initial feilds of the markov chain
 * @param markov_chain markov_chain struct
 * @param list LinkedList struct
 */
void initialize_markov_chain(MarkovChain *markov_chain, LinkedList *list) {
    markov_chain->database = list;
    markov_chain->comp_func = cmp_func_tweets;
    markov_chain->free_data = free_func_tweets;
    markov_chain->copy_func = copy_func_tweets;
    markov_chain->is_last = node_in_counter_last;
    markov_chain->print_func = print_func_tweets;
}


/**
 * the main function
 * @param argc
 * @param argv
 * @return none
 */
int main (int argc, char *argv[])
{
  if (ARGS2 < argc || argc < ARGS1)
  {
    fprintf (stdout, "%s", WRONG_PAREMTER_NUMBER);
    return EXIT_FAILURE;
  }
  MarkovChain *markov_chain = malloc (sizeof (MarkovChain));
  if (NULL == markov_chain)
  {
    fprintf (stdout, "%s%s", ERROR, ALLOCATION_ERROR_MASSAGE);
    return EXIT_FAILURE;
  }
  LinkedList *list = malloc (sizeof (LinkedList));
  if (NULL == list)
  {
    fprintf (stdout, "%s%s", ERROR, ALLOCATION_ERROR_MASSAGE);
    free (markov_chain);
    return EXIT_FAILURE;
  }
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
  initialize_markov_chain(markov_chain, list);
    if (argc == ARGS2)
  {
    int word_to_parse = (int) strtol (argv[ARGS1], NULL, BASE);
    fill_database ((FILE *) argv[3], word_to_parse, markov_chain);
  }
  if (argc == ARGS1)
  {
    fill_database ((FILE *) argv[3], NO_LIMIT, markov_chain);
  }
  unsigned int seed = (int) strtol (argv[1], NULL, BASE);
  int num_of_tweets = (int) strtol (argv[2], NULL, BASE);
  srand (seed);
  int i = 1;
  while (i <= num_of_tweets)
  {
    fprintf (stdout, "Tweet %d: ", i);
    generate_random_sequence (markov_chain, NULL, MAX_TWEETS);
    fprintf (stdout, "%s", "\n");
    i++;
  }
  free_markov_chain (&markov_chain);
  return EXIT_SUCCESS;
}





