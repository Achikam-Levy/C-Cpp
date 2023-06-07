#include "cipher.h"
#include "string.h"

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.

#define SMALL_A 97
#define SMALL_Z 122
#define BIG_A 65
#define BIG_Z 90
#define AZ 26

int set_k(int k)

{
  if (k > AZ)
  {
  k = k % AZ;
  }
  if (k < 0)
  {
    k *= (-1);
    k = k % AZ;
    k *= (-1);
  }
  return k;
}

// See full documentation in header file
void encode (char s[], int k)
{
  k = set_k (k);
  int length = (int)strlen(s);
  for (int i = 0; i < length; i++)
  {
    if ((BIG_A <= s[i]) && (s[i] <= BIG_Z))
    {
      if ((BIG_A <= s[i] + k) && (s[i] + k <= BIG_Z))
      {
        s[i] = (char) (s[i] + k);
        continue;
      }
      if ((s[i] + k) > BIG_Z)
      {
        s[i] = (char) ((BIG_A - 1) + ((s[i] + k) - BIG_Z));
        continue;
      }
      if ((s[i] + k) < BIG_A)
      {
        s[i] = (char) (BIG_Z - ((BIG_A - 1) - (s[i] + k)));
        continue;
      }
    }
    if ((SMALL_A <= s[i]) && (s[i] <= SMALL_Z))
    {
      if ((s[i] + k) > SMALL_Z)
      {
        s[i] = (char) ((SMALL_A - 1) + ((s[i] + k) - SMALL_Z));
        continue;
      }
      if ((s[i] + k) < SMALL_A)
      {
        s[i] = (char) (SMALL_Z - ((SMALL_A - 1) - (s[i] + k)));
        continue;
      }
      else if ((SMALL_A <= s[i] + k) && (s[i] + k <= SMALL_Z))
      {
        s[i] = (char) (s[i] + k);
        continue;
      }
    }
  }
}

// See full documentation in header file

void decode (char s[], int k)
{
  k = set_k (k);
  int length = (int)strlen(s);
  for (int i = 0; i < length; i++)
  {
    if ((BIG_A <= s[i]) && (s[i] <= BIG_Z))
    {
      if ((BIG_A <= (s[i] - k)) && ((s[i] - k) <= BIG_Z))
      {
        s[i] = (char) (s[i] - k);
        continue;
      }
      if ((s[i] - k) > BIG_Z)
      {
        s[i] = (char) ((BIG_A - 2) - ((s[i] - k) + BIG_Z));
        continue;
      }
      if ((s[i] - k) < BIG_A)
      {
        s[i] = (char) (BIG_Z - (BIG_A - (s[i] - k)));
        continue;
      }
    }
    if ((SMALL_A <= s[i]) && (s[i] <= SMALL_Z))
    {
      if ((s[i] - k) > SMALL_Z)
      {
        s[i] = (char) ((SMALL_A - 1) + ((s[i] - k) - SMALL_Z));
        continue;
      }
      if ((s[i] - k) < SMALL_A)
      {
        s[i] = (char) (SMALL_Z - ((SMALL_A - 1) - (s[i] - k)));
        continue;
      }
      else
      {
        s[i] = (char) (s[i] - k);
      }
    }
  }
}