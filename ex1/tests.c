#include <string.h>
#include "tests.h"

#define K_1 3
#define K_2 2
#define K_3 (-1)
#define K_4 (-3)
#define K_5 (29)

// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  encode (in, K_1);

  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "ab.y";
  char out[] = "cd.a";
  encode (in, K_2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "b.cd";
  char out[] = "a.bc";
  encode (in, K_3);

  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k ()
{
  char in[] = "ax.y";
  char out[] = "xu.v";
  encode (in, K_4);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k ()
{
  char in[] = "ABC";
  char out[] = "DEF";
  encode (in, K_5);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decode (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "cd.a";
  char out[] = "ab.y";
  decode (in, K_2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "a.bc";
  char out[] = "b.cd";
  decode (in, K_3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k ()
{
  char in[] = "xu.v";
  char out[] = "ax.y";
  decode (in, K_4);//-3
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k ()
{
  char in[] = "DEF";
  char out[] = "ABC";
  decode (in, K_5);
  return strcmp (in, out) != 0;
}

