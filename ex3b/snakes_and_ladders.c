#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60

#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20




/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

void initialze_markovchain(MarkovChain *markov_chain, LinkedList *list);

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell {
    int number; // Cell number 1-100
    int ladder_to;  // ladder_to represents the jump of the ladder in case
    // there is one from this square
    int snake_to;  // snake_to represents the jump of the snake in
    // case there is one from this square
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

/**
 * print the cells of the game
 * @param data_ptr pointer to cell to print
 */
static void print_func_snakes(void * data_ptr)
{
  Cell * cur_cell = data_ptr;
  if (cur_cell->number == BOARD_SIZE)
  {
    printf ("%s%d%s", "[", cur_cell->number, "]");
    return;
  }
  if (cur_cell->ladder_to == -1 && cur_cell->snake_to == -1)
  {
    printf ("%s%d%s", "[", cur_cell->number, "] -> ");
  }
  else if( cur_cell->ladder_to != -1)
  {
    printf ("%s%d%s%d%s", "[", cur_cell->number, "]-ladder to ",
            cur_cell->ladder_to, " -> ");
  }
  else if( cur_cell->snake_to != -1)
  {
    printf ("%s%d%s%d%s", "[", cur_cell->number, "]-snake to ",
            cur_cell->snake_to, " -> ");
  }
}

/**
 *
 * @param a_ptr pointer to cell a
 * @param b_ptr pointer to cell b
 * @return
 */
static int cmp_func_snakes(void * a_ptr, void * b_ptr)
{
  Cell * a = a_ptr;
  Cell * b = b_ptr;
  return (a->number - b->number);
}

/**
 * free function for cell pointers
 * @param node pointer to a cell
 */
static void free_func_snakes(void * node)
{
  Cell *cell = node;
  free(cell);
}

/**
 * copy function for snakes and ladders game
 * @param cell_ptr pointer to data needed to copy
 * @return Cell pointer to the new copy
 */
static void * copy_func_snakes(void * cell_ptr)
{
  Cell * src = cell_ptr;
  Cell * dst = malloc (sizeof(Cell));
  if(dst == NULL)
  {
    return NULL;
  }
  dst->snake_to = src->snake_to;
  dst->ladder_to = src->ladder_to;
  dst->number = src->number;
  return dst;
}

/**
 * checks if node data is an and of a tweet
 * @param first_node node
 * @return  bool value
 */
static bool cell_is_last (void * node)
{
  Cell *cell = node;
  if (cell->number == BOARD_SIZE)
  {
    return true;
  }
  return false;
}




/** Error handler **/
static int handle_error(char *error_msg, MarkovChain **database)
{
    printf("%s", error_msg);
    if (database != NULL)
    {
        free_markov_chain(database);
    }
    return EXIT_FAILURE;
}


static int create_board(Cell *cells[BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cells[i] = malloc(sizeof(Cell));
        if (cells[i] == NULL)
        {
            for (int j = 0; j < i; j++) {
                free(cells[j]);
            }
            handle_error(ALLOCATION_ERROR_MASSAGE,NULL);
            return EXIT_FAILURE;
        }
        *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
    }

    for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
    {
        int from = transitions[i][0];
        int to = transitions[i][1];
        if (from < to)
        {
            cells[from - 1]->ladder_to = to;
        }
        else
        {
            cells[from - 1]->snake_to = to;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int fill_database(MarkovChain *markov_chain)
{
    Cell* cells[BOARD_SIZE];
    if(create_board(cells) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    MarkovNode *from_node = NULL, *to_node = NULL;
    size_t index_to;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        add_to_database(markov_chain, cells[i]);
    }

    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        from_node = get_node_from_database(markov_chain,cells[i])->data;

        if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
        {
            index_to = MAX(cells[i]->snake_to,cells[i]->ladder_to) - 1;
            to_node = get_node_from_database(markov_chain, cells[index_to])
                    ->data;
            add_node_to_counter_list(from_node, to_node, markov_chain);
        }
        else
        {
            for (int j = 1; j <= DICE_MAX; j++)
            {
                index_to = ((Cell*) (from_node->data))->number + j - 1;
                if (index_to >= BOARD_SIZE)
                {
                    break;
                }
                to_node = get_node_from_database(markov_chain, cells[index_to])
                        ->data;
                add_node_to_counter_list(from_node, to_node, markov_chain);
            }
        }
    }
    // free temp arr
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        free(cells[i]);
    }
    return EXIT_SUCCESS;
}

/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    fprintf (stdout, "%s", WRONG_NUMBER_OF_PARAMETERS_S);
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
    free_markov_chain (&markov_chain);
    return EXIT_FAILURE;
  }
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
  initialze_markovchain(markov_chain, list);
  unsigned int seed = (int) strtol (argv[1], NULL, BASE);
  srand (seed);
  int path_num = (int) strtol (argv[2], NULL, BASE);
  fill_database (markov_chain);
  int i = 1;
  while (i <= path_num)
  {
    printf("%s%d%s", "Random Walk ", i,": ");
    generate_random_sequence (markov_chain, (MarkovNode *)
    markov_chain->database->first->data,
                              MAX_GENERATION_LENGTH);
    printf ("%s", "\n");
    i++;
  }
  free_markov_chain (&markov_chain);
  return EXIT_SUCCESS;
}

/**
 * initialize markovchain for snake and ladders
 * @param markov_chain markovchain
 * @param list database
 */
void initialze_markovchain(MarkovChain *markov_chain, LinkedList *list) {
    markov_chain->database = list;
    markov_chain->free_data = free_func_snakes;
    markov_chain->comp_func = cmp_func_snakes;
    markov_chain->copy_func = copy_func_snakes;
    markov_chain->is_last = cell_is_last;
    markov_chain->print_func = print_func_snakes;
}
