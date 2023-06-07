#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include "linked_list.h"
#include <stdio.h>  // For printf(), sscanf()
#include <stdlib.h> // For exit(), malloc()
#include <stdbool.h> // for bool

#define EXIT_FAILURE 1
#define MAX_LINE_LENGTH 1025
#define ARGS1  4
#define ARGS2  5
#define BASE  10
#define MAX_TWEETS  20
#define NO_LIMIT  (-1)
#define MAX_WORD_SIZE  101
#define WRONG_PAREMTER_NUMBER "Usage: the parameters needed is seed, "\
      "tweets num, text path, nums of word to read(optional)\n"
#define WRONG_NUMBER_OF_PARAMETERS_S  \
"Usage: the parameters needed is seed and walks num"


#define ERROR "ERROR: "
#define FILE_OPEN_FAILED "invalid file"
#define ALLOCATION_ERROR_MASSAGE \
"Allocation failure: Failed to allocate new memory\n"


/***************************/
/*   insert typedefs here  */
/***************************/

typedef void ( * print_func)( void *);

typedef int ( * cmp_func)( void * a,  void * b);

typedef void ( * free_func)( void *);

typedef void * ( * copy_func)( void *);

typedef bool ( * check_is_last)( void *);

/***************************/


/***************************/
/*        STRUCTS          */
/***************************/

typedef struct MarkovNode {
    void *data;
    struct NextNodeCounter *counter_list;
    int capacity;
    int sum_of_followed_words;
} MarkovNode;

typedef struct NextNodeCounter {
    MarkovNode *markov_node;
    int frequency;
} NextNodeCounter;

/* DO NOT ADD or CHANGE variable names in this struct */
typedef struct MarkovChain {
    LinkedList *database;

    // pointer to a func that receives data from a generic type and prints it
    // returns void.
    print_func print_func;

    // pointer to a func that gets 2 pointers of generic data type(same one)
    // and compare between them */
    // returns: - a positive value if the first is bigger
    //          - a negative value if the second is bigger
    //          - 0 if equal
    cmp_func comp_func;

    // a pointer to a function that gets a pointer of generic data type and frees it.
    // returns void.
    free_func free_data;

    // a pointer to a function that  gets a pointer of generic data type
    // and returns a newly allocated copy of it
    // returns a generic pointer.
    copy_func copy_func;

    //  a pointer to function that gets a pointer of generic data type and returns:
    //      - true if it's the last state.
    //      - false otherwise.
    check_is_last is_last;
} MarkovChain;

/**
 * Get one random state from the given markov_chain's database.
 * @param markov_chain
 * @return
 */
MarkovNode* get_first_random_node(MarkovChain *markov_chain);

/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param state_struct_ptr MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode* get_next_random_node(MarkovNode *state_struct_ptr);

/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with, if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_random_sequence(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length);

/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free
 */
void free_markov_chain(MarkovChain **markov_chain);

/**
 * Add the second markov_node to the counter list of the first markov_node.
 * If already in list, update it's counter value.
 * @param first_node
 * @param second_node
 * @param markov_chain
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */
bool add_node_to_counter_list(MarkovNode *first_node, MarkovNode
*second_node, MarkovChain *markov_chain);

/**
* Check if data_ptr is in database. If so, return the markov_node wrapping it in
 * the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node* get_node_from_database(MarkovChain *markov_chain, void *data_ptr);

/**
* If data_ptr in markov_chain, return it's node. Otherwise, create new
 * node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return node wrapping given data_ptr in given chain's database
 */
Node* add_to_database(MarkovChain *markov_chain, void *data_ptr);

#endif /* MARKOV_CHAIN_H */
