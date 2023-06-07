#ifndef _HASH_MAP_HPP_
#define _HASH_MAP_HPP_

#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>

#define DEFULT_SIZE 16
#define LOAD_FACTOR 0.75
#define LOWER_LOAD_FACTOR 0.25

/**
@brief HashMap class for storing key-value pairs in a hash table.
The HashMap class uses a hash function to generate a hash value for each key,
which is used to determine the index in the underlying array where
the key-value pair should be stored.
@tparam KeyT The type of the keys in the key-value pairs.
@tparam ValueT The type of the values in the key-value pairs.
*/
template<typename KeyT, typename ValueT>
class HashMap
{
  template<class T>
  class iterator_t;
 public:
  typedef iterator_t<std::pair<KeyT, ValueT>> iterator;
  /**
  * Default constructor for HashMap class
  * It creates a new empty HashMap with a default capacity of 16
  */
  HashMap ()
  {
    _capacity = DEFULT_SIZE;
    _values_map = new std::vector<std::pair<KeyT, ValueT>>[_capacity];
    _size = 0;
  }

  /**
   * Constructor for HashMap class, It creates a new HashMap and insert the
   * keys and values from the given vectors.
   * @param keys : vector<KeyT>& - vector of keys to be inserted into the map
   * @param values : vector<ValueT>& - vector of values to be inserted
   * @throw domain_error if the keys size is not equal to the values size
   */
  HashMap (const std::vector<KeyT> &keys, const std::vector<ValueT> &values)
  {
    if (keys.size () != values.size ())
    {
      throw std::domain_error ("must to be much between values end the keys");
    }
    _capacity = DEFULT_SIZE;
    _values_map = new std::vector<std::pair<KeyT, ValueT>>[_capacity];
    _size = 0;
    int hashed_key, idx;
    for (int i = 0; i < (int) keys.size (); ++i)
    {
      // if key exist, only changes the value
      if (this->contains_key (keys[i]))
      {
        for (auto &pair: _values_map[bucket_index (keys[i])])
        {
          if (pair.first == keys[i])
          {
            pair = std::make_pair (keys[i], values[i]);
          }
        }
      }
      else
      {
        hashed_key = _key_hash (keys[i]);
        idx = hashed_key & (_capacity - 1);
        _values_map[idx].push_back (std::make_pair (keys[i], values[i]));
        _size += 1;
        if (get_load_factor () > LOAD_FACTOR)
        {
          resize_map ();
        }
      }
    }
  }

  /**
   * Copy constructor for HashMap class It creates a new HashMap and copies
   * the key-value pairs from the given HashMap object.
   * @param other : const HashMap<KeyT, ValueT>& -
   * the HashMap object to copy from
   */
  HashMap (const HashMap<KeyT, ValueT> &other)
  {
    _capacity = other._capacity;
    _size = other._size;
    _key_hash = other._key_hash;
    _values_map = new std::vector<std::pair<KeyT, ValueT>>[_capacity];
    for (int i = 0; i < _capacity; ++i)
    {
      _values_map[i] = other._values_map[i];
    }
  }
  /**
   * Destructor for HashMap class
   * It deletes the memory allocated for the values map
   */
  virtual ~HashMap ()
  {
    delete[] _values_map;
  }

  float size () const
  { return _size; };
  int capacity () const
  { return _capacity; };
  bool empty () const
  {
    return _size == 0;
  }
  /**
   * Insert a key-value pair into the HashMap.
   * @param key : const KeyT& - The key to be inserted.
   * @param value : const ValueT& - The value to be associated with the key.
   * @return bool - Returns true if the insertion was successful,
   * false if the key already exists in the map.
   */
  bool insert (const KeyT &key, const ValueT &value)
  {
    int hashed_key, idx;
    hashed_key = _key_hash (key);
    idx = hashed_key & (_capacity - 1);
    for (auto const &pair: _values_map[idx])
    {
      if (pair.first == key)
      {
        return false;
      }
    }
    _values_map[idx].push_back (std::make_pair (key, value));
    _size += 1;
    if (get_load_factor () > LOAD_FACTOR)
    {
      resize_map ();
    }
    return true;
  }

  /**
   * Check if a given key exists in the HashMap.
   * @param key : const KeyT& - The key to be searched for.
   * @return bool - Returns true if the key exists in the map, false otherwise.
   */
  bool contains_key (const KeyT &key) const
  {
    int hashed_key, idx;
    hashed_key = _key_hash (key);
    idx = hashed_key & (_capacity - 1);
    for (auto const &pair: _values_map[idx])
    {
      if (pair.first == key)
      {
        return true;
      }
    }
    return false;
  }

  /**
   * Get the value associated with a given key in the HashMap.
   * @param key : const KeyT& - The key to search for in the map
   * @return ValueT& - Reference to the value associated with the key
   * @throw runtime_error if the key is not found in the map
   */
  ValueT &at (const KeyT &key) const
  {
    int hashed_key, idx;
    hashed_key = _key_hash (key);
    idx = hashed_key & (_capacity - 1);
    for (auto &pair: _values_map[idx])
    {
      if (pair.first == key)
      {
        return pair.second;
      }
    }
    throw std::runtime_error ("value not found");
  }

  /**
   * Remove a key-value pair from the HashMap.
   * @param key : const KeyT& - The key to be removed
   * @return bool - Returns true if the key was removed, false otherwise
   */
  virtual bool erase (const KeyT &key)
  {
    int hashed_key, idx;
    hashed_key = _key_hash (key);
    idx = hashed_key & (_capacity - 1);
    int i = 0;
    while (i < (int) _values_map[idx].size ())
    {
      if (_values_map[idx][i].first == key)
      {
        _values_map[idx].erase (_values_map[idx].begin () + i);
        _size -= 1;
        if (get_load_factor () < LOWER_LOAD_FACTOR)
        {
          resize_map ();
        }
        return true;
      }
      else
      {
        i++;
      }
    }
    return false;
  }

  /**
   * Get the current load factor of the HashMap
   * @return double - The current load factor of the HashMap ( size / capacity)
   */
  double get_load_factor () const
  { return (_size / _capacity); };

  /**
   * Get the number of key-value pairs in the bucket associated with the key.
   * @param key : const KeyT& - The key to get the bucket size for.
   * @return int - The number of key-value pairs in the bucket.
   * @throw runtime_error if the key is not found in the map
   */
  int bucket_size (const KeyT &key) const
  {
    if (!(this->contains_key (key)))
    {
      throw std::runtime_error ("key doesnt exist");
    }
    int hashed_key, idx;
    hashed_key = _key_hash (key);
    idx = hashed_key & (_capacity - 1);
    return (int) _values_map[idx].size ();
  }

  /**
   * Get the index of the bucket associated with a given key.
   * @param key : const KeyT& - The key to get the bucket index for.
   * @return int - The index of the bucket
   * @throw runtime_error if the key is not found in the map
   */
  int bucket_index (const KeyT &key) const
  {
    if (!(this->contains_key (key)))
    {
      throw std::runtime_error ("key doesnt exist");
    }
    int hashed_key, idx;
    hashed_key = _key_hash (key);
    idx = hashed_key & (_capacity - 1);
    return idx;
  }

  /**
   * Remove all key-value pairs from the HashMap.
   */
  void clear ()
  {
    for (int i = 0; i < _capacity; ++i)
    {
      _values_map[i].clear ();
    }
    _size = 0;
  }

  /**
  Resize the HashMap to the new capacity.
  The new capacity is determined by the current load factor:
  if the load factor is greater than LOAD_FACTOR, capacity is multiplied by 2.
  if the load factor is less than LOWER_LOAD_FACTOR, capacity is divided by 2
  This function is called when the load factor exceeds
   LOAD_FACTOR or is less than LOWER_LOAD_FACTOR
  */
  void resize_map ()
  {
    if (LOAD_FACTOR > get_load_factor () && get_load_factor () >
                                            LOWER_LOAD_FACTOR)
    {
      return;
    }
    else
    {
      int old_capacity = _capacity;
      while (get_load_factor () > LOAD_FACTOR)
      {
        _capacity = 2 * _capacity;
      }
      while (get_load_factor () < LOWER_LOAD_FACTOR && _capacity > 1)
      {
        if (_capacity >= 2)
        {
          _capacity = _capacity / 2;
        }
      }
      auto *tmp = new std::vector<std::pair<KeyT, ValueT>>[_capacity];
      int hashed_key, idx;
      for (int i = 0; i < old_capacity; i++)
      {
        for (auto const &pair: _values_map[i])
        {
          hashed_key = _key_hash (pair.first);
          idx = hashed_key & (_capacity - 1);
          tmp[idx].push_back (std::make_pair (pair.first, pair.second));
        }
      }
      delete[] _values_map;
      _values_map = tmp;
    }
  }

  /**
  * Overloads the assignment operator to copy values from another HashMap.
  * @param other : const HashMap<KeyT, ValueT>& -
   * The other HashMap object to copy values from
  * @return HashMap& - A reference to the current object after
   * copying values from the other object
  */
  HashMap &operator= (const HashMap<KeyT, ValueT> &other)
  {
    if (&other == this)
    {
      return *this;
    }

    _capacity = other._capacity;
    _size = other._size;
    _key_hash = other._key_hash;
    auto *tmp = new std::vector<std::pair<KeyT, ValueT>>[_capacity];

    for (int i = 0; i < _capacity; ++i)
    {
      tmp[i] = other._values_map[i];
    }
    delete[] _values_map;
    _values_map = tmp;
    return *this;
  }

  /**
  * Overloads the equality operator to check if the current
  * HashMap object is equal to another HashMap object.
  * @param other : const HashMap<KeyT, ValueT>& - The other HashMap object
  * to compare to the current object
  * @return bool - True if the two objects have the same key-value pairs,
  * false otherwise.
  */
  bool operator== (const HashMap<KeyT, ValueT> &other) const
  {
    if (_size != other._size)
    {
      return false;
    }
    for (auto const &pair: other)
    {
      if (!(this->contains_key (pair.first)))
      {
        return false;
      }
      if (this->contains_key (pair.first))
      {
        if (this->at (pair.first) != pair.second)
        {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!= (const HashMap<KeyT, ValueT> &other) const
  {
    return !(*this == other);
  }

  /**

  operator[] - returns the value associated with the given key
  @param key: the key to search for
  @return ValueT: the value associated with the key,
   or the default value of the type if the key is not found
  */
  ValueT operator[] (const KeyT &key) const
  {
    if (this->contains_key (key))
    {
      int hashed_key, idx;
      hashed_key = _key_hash (key);
      idx = hashed_key & (_capacity - 1);
      for (int i = 0; i < (int) _values_map[idx].size (); ++i)
      {
        if (_values_map[idx][i].first == key)
        {
          return _values_map[idx][i].second;
        }
      }
    }
    return ValueT ();
  }

  /**
  operator[] - Overloaded operator[] to access the value associated with a key.
  If the key does not exist, it will insert the key with a default value.
  @param key - The key to access the value of.
  @return ValueT& - A reference to the value associated with the key.
  */
  ValueT &operator[] (const KeyT &key)
  {
    if (this->contains_key (key))
    {
      int hashed_key, idx;
      hashed_key = _key_hash (key);
      idx = hashed_key & (_capacity - 1);
      for (int i = 0; i < (int) _values_map[idx].size (); ++i)
      {
        if (_values_map[idx][i].first == key)
        {
          return _values_map[idx][i].second;
        }
      }
    }
    else
    {
      this->insert (key, ValueT ());
    }
    return this->at (key);
  }

  /**
  @brief Returns an iterator pointing to the first element in the HashMap.
  @return Iterator pointing to the first element in the HashMap.
  If the HashMap is empty, returns the same as `end()`.
  */
  iterator cbegin () const
  {
    if (_size == 0)
    {
      return this->end ();
    }
    int i = 0;
    while ((_values_map[i].size () == 0) && (i < _capacity))
    {
      i++;
    }
    if (i == _capacity)
    {
      return this->end ();
    }
    return iterator (this, i, 0);
  }

  /**
  @brief Returns an iterator pointing to the first element in the HashMap.
  @return Iterator pointing to the first element in the HashMap.
  If the HashMap is empty, returns the same as `end()`.
  */
  iterator begin () const
  {
    if (_size == 0)
    {
      return this->end ();
    }
    int i = 0;
    while ((_values_map[i].size () == 0) && (i < _capacity))
    {
      i++;
    }
    if (i == _capacity)
    {
      return this->end ();
    }
    return iterator (this, i, 0);
  }

  /**
  @brief Returns an iterator to the element following the last element
  of the HashMap, which is none exist to let the begin know its the end.
  @return An iterator to the element following the last element of the HashMap.
  */
  iterator end () const
  {
    return iterator (this, _capacity + 1, 0);
  }

  /**
  @brief Returns an iterator to the element following the last element
  of the HashMap, which is none exist to let the begin know its the end.
  @return An iterator to the element following the last element of the HashMap.
  */
  iterator cend () const
  {
    return iterator (this, _capacity + 1, 0);
  }

 private:
  /**
  @brief Iterator class for the HashMap.
  Allows for traversal of the key-value pairs stored in the HashMap.
  @tparam T The type of the key-value pairs stored in the HashMap.
  @brief Iterator category for the iterator.
  Specifies that this is a forward iterator.
  */
  template<class T>
  class iterator_t
  {
   public:
    typedef std::forward_iterator_tag iterator_category;
    /**
    @brief The type of the key-value pairs stored in the HashMap.
    */
    typedef std::pair<KeyT, ValueT> value_type;
    /**
    @brief Reference to the current key-value pair of the HashMap.
    */
    typedef std::pair<KeyT, ValueT> &reference;
    /**
    @brief Pointer to the current key-value pair of the HashMap.
    */
    typedef std::pair<KeyT, ValueT> *pointer;
    /**
    @brief The difference type for the iterator.
    */

    typedef std::ptrdiff_t difference_type;
    /**
     * Constructor for the iterator object of the HashMap.
     * @param map Pointer to the HashMap object.
     * @param bucket Current bucket of the HashMap.
     * @param idx Current index within the current bucket.
     */
    explicit iterator_t (const HashMap<KeyT, ValueT> *map, int bucket, int idx)
    {
      bucket_ = (bucket);
      idx_ = (idx);
      map_ = (map);
      if (bucket < map->_capacity && idx < (int) map->_values_map[bucket].size
          ())
      {
        cur_ = map->_values_map[bucket][idx];
      }
    }

    /**
     * Overloaded dereference operator for the iterator object of the HashMap.
     * @return A reference to the current key-value pair of the HashMap.
     */
    reference operator* ()
    { return cur_; }

    /**
     * Overloaded arrow operator for the iterator object of the HashMap.
     * @return A pointer to the current key-value pair of the HashMap.
     */
    pointer operator-> ()
    { return &cur_; }

    /**
     * Overloaded dereference operator for the iterator object of the HashMap.
     * @return A copy of the current key-value pair of the HashMap.
     */
    value_type operator* () const
    { return cur_; }

    /**
     * Overloaded pre-fix operator for the iterator object of the HashMap.
     * This function moves the iterator to the next pair in the HashMap.
     * @return A reference to the updated iterator object.
     */
    const iterator_t &operator++ ()
    {
      if (idx_ + 1 >= (int) map_->_values_map[bucket_].size ())
      {
        bucket_++;
        idx_ = 0;
      }
      else
      {
        idx_++;
      }
      while (bucket_ < ( (map_->_capacity) - 1 ) && map_->_values_map[bucket_].empty())
      {
        bucket_++;
      }
      if (bucket_ < map_->_capacity
          && idx_ < (int) (map_->_values_map[bucket_]).size ())
      {
        cur_ = map_->_values_map[bucket_][idx_];
      }
      else
      {
        bucket_ = map_->_capacity + 1;
      }
      return *this;
    }

    /**
     * Overloaded post-fix operator for the iterator object of the HashMap.
     * This function moves the iterator to the next pair in the HashMap.
     * @return A copy of the iterator object before it is incremented.
     */
    iterator_t operator++ (int)
    {
      iterator_t tmp = (*this);
      ++(*this);
      return tmp;
    }

    /**
     * Overloaded equality operator for the iterator object of the HashMap.
     * @param other The other iterator object to compare with.
     * @return A boolean value indicating whether the two iterator objects
     * are equal.
     */
    bool operator== (const iterator_t &other) const
    {

      return bucket_ == other.bucket_ && idx_ == other.idx_ && this->map_ ==
                                                               other.map_;
    }

    /**
     * Overloaded inequality operator for the iterator object of the HashMap.
     * @param other The other iterator object to compare with.
     * @return A boolean value indicating whether the two iterator objects
     * are not equal.
     */
    bool operator!= (const iterator_t &other) const
    {
      return !(*this == other);
    }

    /**
    * The current bucket of the HashMap being traversed by the iterator.
    */
    int bucket_;
    /**
     * The current index within the current bucket of the HashMap being
     * traversed by the iterator.
     */
    int idx_;
    /**
     * A pointer to the HashMap object being traversed by the iterator.
     */
    const HashMap<KeyT, ValueT> *map_;
    /**
     * The current pair of the HashMap being traversed by the iterator.
     */
    std::pair<KeyT, ValueT> cur_;
  };

 protected:
  /**
  @brief Hash function used to generate a hash value for the keys.
  */
  std::hash<KeyT> _key_hash;
  /**
  @brief Capacity of the map - the maximum number of elements that can be
   stored.
  */
  int _capacity;
  /**
  @brief Array of vectors, used to store the key-value pairs in the map.
  */
  std::vector<std::pair<KeyT, ValueT>> *_values_map;
  /**
  @brief Current size of the map - number of elements currently stored in the
   map.
  */
  float _size;
};

#endif //_HASH_MAP_HPP_
