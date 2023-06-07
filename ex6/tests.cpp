#include "iostream"
#include "assert.h"
#include "HashMap.hpp"


void build_hash_func ()
{
  HashMap<std::string, std::string> h;
  assert(h.empty ());
  h.insert ("Dont", "try");
  assert(!h.empty ());

  std::vector<int> keys1 = {2, 5, 3, 7, 6, 43, 12, 78, 67, 45, 32, 1, 11, 22,
                            34};
  std::vector<int> values1 = {3, 18, 13, 21, 45, 23, 29, 11, 9, 4, 5, 90, 83,
                              25, 67};
  HashMap<int, int> other_h1 (keys1, values1);

  std::vector<int> keys = {2, 5, 3, 7, 6, 43, 12, 78, 67, 45, 32, 1};
  std::vector<int> values = {3, 18, 13, 21, 45, 23, 29, 11, 9, 4, 5, 8};
  HashMap<int, int> other_h (keys, values);

  assert(other_h.capacity () == 16);
  other_h.insert (15, 6);
  assert(other_h1.size () == 15);
  assert(other_h1.capacity () == 32);
  assert(other_h.capacity () == 32);

  HashMap<int, int> other_h2 (other_h1);
  assert(other_h2.capacity () == 32);

  HashMap<int, int> h1;
  h1.insert (18, 7);
  assert(h1 != other_h2);
  h1 = other_h2;
  assert(h1.capacity () == 32);
  assert(h1[2] == 3);
  assert(h1[3] == 13);
  h1[24] = 31;
  assert(h1[24] == 31);

  h1[18]; // TODO: see behavior

}

void getters_hash_map ()
{
  HashMap<int, int> h;
  assert(h.empty ());
  assert(h.capacity () == 16);
  h.insert (12, 10);
  assert(h.size () == 1);
  assert(!(h.insert (12, 7)));
  h.insert (5, 3);
  h.insert (3, 7);
  assert(h.size () == 3);

//  assert(h.get_load_factor () == 0.1875);
  h.insert (4, 8);
//  assert(h.get_load_factor () == 0.25);

  //contains_key

  assert(!(h.contains_key (7)));
  assert(h.contains_key (12));
}

void at_hash_map ()
{
  HashMap<int, int> h;
  h.insert (12, 10);
  h.insert (5, 3);
  h.insert (3, 7);
  assert(h.at (3) == 7);
  assert(h.at (5) == 3);
  assert(h.at (12) == 10);

  int check = 0;
  try
    { h.at (6); }
  catch (std::runtime_error &)
    {
      check = 1;
      assert(check == 1);
    }
}

void erase_hash_map ()
{
  HashMap<int, int> h;
  h.insert (34, 10);
  h.insert (23, 3);
  h.insert (11, 7);
  assert(h.at (11) == 7);
  assert(h.at (23) == 3);
  assert(h.at (34) == 10);

  h.erase (34);
  assert(!h.contains_key (34));

  std::vector<int> keys1 = {2, 5, 3, 7, 6, 43, 12, 78, 67, 45, 32, 1, 11};
  std::vector<int> values1 = {3, 18, 13, 21, 45, 23, 29, 11, 9, 4, 5, 90, 83};
  HashMap<int, int> other_h1 (keys1, values1);

  other_h1.erase (2);
  other_h1.erase (5);
  other_h1.erase (3);
  other_h1.erase (7);
  other_h1.erase (6);
  other_h1.erase (43);
  other_h1.erase (12);
  other_h1.erase (78);
  other_h1.erase (67);
  other_h1.erase (45);

  assert(other_h1.size () == 3);
//  assert(other_h1.capacity () == 16);

}

void bucket_check ()
{
  HashMap<std::string, int> h;
  h.insert ("Hey", 10);
  h.insert ("Ronaldo", 3);
  h.insert ("Messi", 7);
//  assert(h.bucket_size ("Hey") == 1);
  h.insert ("Push", 12);
//  assert(h.bucket_size ("Hey") == 2);
}

void clear_check ()
{
  HashMap<std::string, int> h;
  h.insert ("Hey", 10);
  h.insert ("Push", 3);
  h.insert ("Messi", 7);
  h.insert ("Hey", 12);
  h.clear ();
  assert(h.empty ());
}

void operators_check ()
{
  HashMap<double, double> h;
  HashMap<double, double> h1;
  h.insert (3.01, 4.02);
  h.insert (7.65, 4.23);
  h.insert (32.31, 4.13);
  h1.insert (3.01, 4.02);
  h1.insert (7.65, 4.23);
  h1.insert (32.31, 4.13);
  assert(h1 == h);
  h1.erase (7.65);
  assert(h1 != h);

}

void iterator_check ()
{
  HashMap<double, double> h;
  h.insert (3.01, 4.02);
  h.insert (7.65, 4.23);
  h.insert (32.31, 4.13);
  int index = 0, index1 = 0, index2 = 0;
  std::vector<double> v{7.65, 3.01, 32.31};

//  for (auto i: h)
//    {
//      assert(v[index] == i.first);
//      double x = v[index];
//      double y = i.first;
//      index++;
//    }

  HashMap<double, double> h1;
  for (auto i: h)
    {
    }

  h.insert (67.4, 32.2);
  h.insert (12.3, 17.4);
  std::vector<double> v1{67.4, 12.3, 7.65, 3.01, 32.31};
  for (auto i: h)
    {
//      assert(v1[index1] == i.first);
      index1++;
    }

  h.erase (67.4);
  h.erase (12.3);

  for (auto i: h)
    {
//      assert(v[index2] == i.first);
      index2++;
    }
}

int main ()
{
  build_hash_func ();

  getters_hash_map ();

  at_hash_map ();

  erase_hash_map ();

  bucket_check ();

  clear_check ();

  operators_check ();

  iterator_check ();
}