//
// Created by אחיקם לוי on 21/11/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "markov_chain.h"

/**
 * building a markov chain from given file
 * @param fp file to parse
 * @param words_to_read number of word to read from the file
 * @param markov_chain node to build markov chain from
 * @return Exit success/failure
 */
int fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain)
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
        current_word = strtok (input, " \n\r");
      }
      else
      {
        current_word = strtok (NULL, " \n\r");
      }
      words_to_read--;
      if ((current_word != NULL) && (0 != strcmp (current_word, "\n")))
      {
        MarkovNode *cur_markove_node = (MarkovNode *)
            add_to_database (markov_chain, current_word);
        if (word_before != NULL && cur_markove_node != NULL)
        {
          add_node_to_counter_list (word_before, cur_markove_node);
        }
        word_before = cur_markove_node;
      }
      else
      {
        break;
      }
    }
  }
  fclose (products_file);
  return EXIT_SUCCESS;
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
    fprintf (stdout, "%s", "Usage: the parameters needed is seed, tweets num, "
                           "text path, nums of word to read(optional)");
    return EXIT_FAILURE;
  }
  MarkovChain *markov_chain = malloc (sizeof (MarkovChain));
  if (NULL == markov_chain)
  {
    fprintf (stdout, "%s%s", ERROR, FILE_OPEN_FAILED);
    return EXIT_FAILURE;
  }
  LinkedList *list = malloc (sizeof (LinkedList));
  if (NULL == list)
  {
    fprintf (stdout, "%s%s", ERROR, FILE_OPEN_FAILED);
    free (markov_chain);
    return EXIT_FAILURE;
  }
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
  markov_chain->database = list;
  if (argc == ARGS2)
  {
    int word_to_parse = (int) strtol (argv[ARGS1], NULL, BASE);
    fill_database ((FILE *) argv[3], word_to_parse, markov_chain);
  }
  if (argc == ARGS1)
  {
    fill_database ((FILE *) argv[3], NO_LIMIT, markov_chain);
  }
  int seed = (int) strtol (argv[1], NULL, BASE);
  int num_of_tweets = (int) strtol (argv[2], NULL, BASE);
  srand (seed);
  int i = 1;
  while (i <= num_of_tweets)
  {
    fprintf (stdout, "Tweet %d:", i);
    generate_random_sequence (markov_chain, NULL, MAX_TWEETS);
    printf ("%s", "\n");
    i++;
  }
  free_markov_chain (&markov_chain);
}






