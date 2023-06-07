#include "HashMap.hpp"
#include <iterator>

/**
@brief Exception class for invalid keys in the HashMap.
This class is derived from the standard invalid_argument
exception and is thrown when an invalid key is used in the HashMap,
such as when trying to retrieve a value for a non-existing key.
@brief Constructor for the InvalidKey exception.
@param error An error message to be passed to the invalid_argument constructor.
*/
class InvalidKey : public std::invalid_argument
{
 public:
  explicit InvalidKey (const std::string &error = "")
      : std::invalid_argument (error)
  {}
};

/**
@brief Dictionary class that is derived from the HashMap class.
The Dictionary class is a specialized version of the HashMap class that
uses string keys and string values.
*/
class Dictionary : public HashMap<std::string, std::string>
{
 public:
  /**
   * default constructor
   */
  Dictionary () = default;

  /**
  @brief Constructor for the Dictionary class that initializes the dictionary
  with keys and values from two vectors.
  @param vec_1 A vector containing the keys for the dictionary.
  @param vec_2 A vector containing the values for the dictionary.
  */
  Dictionary (const std::vector<std::string> &vec_1, const
  std::vector<std::string> &vec_2) :
      HashMap<std::string, std::string> (vec_1, vec_2)
  {}

  /**
   * erase that override the hashmap erase method and throw an error if
   * key doesnt exist in the dictionary
   * @param key key of the value to erase
   * @return true if the erase succeed
   */
  bool erase (const std::string &key) override
  {
    int hashed_key, idx;
    hashed_key = (int)_key_hash (key);
    idx = hashed_key & (_capacity - 1);
    int i = 0;
    while (i < (int) _values_map[idx].size ())
    {
      if (_values_map[idx][i].first == key)
      {
        _values_map[idx].erase (_values_map[idx].begin () + i);
        _size -= 1;
        resize_map ();
        return true;
      }
      else
      {
        i++;
      }
    }
    throw InvalidKey ("key doesnt exist");
  }

  /**
   * updates the dictionary from iterator of pairs of keys and values
   * @tparam T_iterator type of the iterator
   * @param begin iterator
   * @param end iterator
   */
  template<class TIterator>
  void update (TIterator begin, TIterator end)
  {
    for (auto it = begin; it != end; ++it)
    {
      int hashed_key, idx;
      if (this->contains_key (it->first))
      {
        for (auto &pair: _values_map[bucket_index (it->first)])
        {
          if (pair.first == it->first)
          {
            pair = make_pair (it->first, it->second);
          }
        }
      }
      else
      {
        hashed_key = _key_hash (it->first);
        idx = hashed_key & (_capacity - 1);
        _values_map[idx].emplace_back (it->first, it->second);
        _size += 1;
        resize_map ();
      }
    }
  }
  /**
   * default destructor
   */
  ~Dictionary () override = default;
};