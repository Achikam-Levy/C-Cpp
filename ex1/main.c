#include "cipher.h"
#include "tests.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>
#include <math.h>

 // your code goes here

#define LINE 1024
#define ZERO 48
#define NINE 57
#define I_1 45
#define ARGSNUM 5
#define ARGTEST 2

int tests()
{
  int t_1 = test_encode_non_cyclic_lower_case_positive_k ();
  int t_2 = test_encode_cyclic_lower_case_special_char_positive_k ();
  int t_3 = test_encode_non_cyclic_lower_case_special_char_negative_k ();
  int t_4 = test_encode_cyclic_lower_case_negative_k ();
  int t_5 = test_encode_cyclic_upper_case_positive_k ();
  int t_6 = test_decode_non_cyclic_lower_case_positive_k ();
  int t_7 = test_decode_cyclic_lower_case_special_char_positive_k ();
  int t_8 = test_decode_non_cyclic_lower_case_special_char_negative_k ();
  int t_9 = test_decode_cyclic_lower_case_negative_k ();
  int t_10 = test_decode_cyclic_upper_case_positive_k ();
  if ((t_1 + t_2 + t_3 + t_4 + t_5 + t_6 + t_7 + t_8 + t_9 + t_10) != 0)
  {
    return EXIT_FAILURE;
  }
  else
  {
    return EXIT_SUCCESS;
  }
}

int check_valid_file( char *argv[])
{
  FILE *in_file = fopen (argv[3], "r");
  if (in_file == NULL)
  {
    fprintf (stderr, "The given file is invalid.\n");
    return EXIT_FAILURE;
  }
  else{
    fclose (in_file);
  }
  FILE *out_file = fopen (argv[4], "w");
  if (out_file == NULL)
  {
    fprintf (stderr, "The given file is invalid.\n");
    fclose (in_file);
    return EXIT_FAILURE;
  }
  else{
    fclose (out_file);
  }
  return EXIT_SUCCESS;
}

int check_valid_k(const char k[])
{
  for (int i = 0; k[i] != '\0' ; ++i)
  {
    if ((NINE < k[i]) || (ZERO > k[i] ))
    {
      if (k[0] != I_1)
      {
        fprintf (stderr, "The given shift value is invalid.\n");
        return EXIT_FAILURE;
      }
    }
  }
  return  EXIT_SUCCESS;
}

int check_valid_args(int argc, char *argv[])
{
  if ((argc != ARGSNUM) && (argc != ARGTEST))
  {
    fprintf (stderr, "The program receives 1 or 4 arguments only.\n");
    return EXIT_FAILURE;
  }
  else if (argc == ARGTEST)
  {
    if (strcmp (argv[1], "test") != 0)
    {
      fprintf (stderr, "Usage: cipher test\n");
      return EXIT_FAILURE;
    }
  }
  else
  {
    if ((strcmp (argv[1], "encode") != 0) && (strcmp (argv[1], "decode") != 0))
    {
      fprintf (stderr, "The given command is invalid.\n");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

void run_cipher(char *argv[])
{
  int k;
  k = (int) strtol (argv[ARGTEST], NULL, 10);
  FILE *in_file = fopen (argv[3], "r");
  FILE *out_file = fopen (argv[4], "w");
  char input[LINE];
  while (fgets (input, LINE, in_file) != NULL)
  {

    if (strcmp (argv[1], "encode") == 0)
    {
      encode (input, (int) k);
    }
    else
    {
      decode (input, (int) k);
    }
    fprintf (out_file, "%s", input);
  }
  fclose (in_file);
  fclose (out_file);
}

void remove_spaces(char s[])
{
  int i = 0, j = 0;
  while (s[i])
  {
    if (s[i] != 32)
    s[j++] = s[i];
    i++;
  }
  s[j] = '\0';
}

int main (int argc, char *argv[])
{
  int valid_args = (check_valid_args(argc, argv));
  if (valid_args != 1)
  {
    if (argc == ARGTEST)
    {
      if (tests () == 0)
      {
        return EXIT_SUCCESS;
      }
      else
      {
        return EXIT_FAILURE;
      }
    }
    else if (argc == ARGSNUM)
    {
      int valid_k = (check_valid_k (argv[ARGTEST]));
      if (valid_k != 1 )
      {
        int valid_file = (check_valid_file(argv));
        if (valid_file != 1 )
        {
          run_cipher(argv);
          return EXIT_SUCCESS;
        }
        else{
          return EXIT_FAILURE;
        }
      }
      else{
        return EXIT_FAILURE;
      }
    }
    else
    {
      return EXIT_FAILURE;
    }
  }
  else{
    return EXIT_FAILURE;
  }
}
