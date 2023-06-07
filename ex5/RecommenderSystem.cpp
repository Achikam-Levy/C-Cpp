//
// Created by אחיקם לוי on 31/12/2022.
//
#include "RecommenderSystem.h"

// implement your cpp code here
///RecommenderSystem
RecommenderSystem::RecommenderSystem () = default;

/// check the header file
sp_movie RecommenderSystem::add_movie (const std::string &name, int year,
                                       const std::vector<double> &features)
{
  sp_movie movie = std::make_shared<Movie> (name, year);
  _attributes.insert (std::make_pair (movie, features));
  string str_year;
  str_year = std::to_string (year);
  _get_movie_map[name + str_year] = movie;
  return movie;
}

/// check the header file
sp_movie RecommenderSystem::recommend_by_content (const RSUser &user)
{
  // phase_1: create an average vector
  double sum_of_ranks = 0;
  double num_of_seen = 0;
  for (auto &movie: _attributes)
  {
    sum_of_ranks += user.get_ranks ()[movie.first];
    if (user.get_ranks ()[movie.first] != 0)
    { num_of_seen++; }
  }
  double average = sum_of_ranks / num_of_seen;

  // phase_2: create a preferences vector
  std::vector<double> preference_vec;
  preference_vec.resize (_attributes.begin ()->second.size ());
  for (unsigned long int i = 0; i < preference_vec.size (); i++)
  {
    double sum_row = 0;
    for (auto const &movie: _attributes)//calculate sum for each row
    {
      if (user.get_ranks ()[movie.first] != 0)//if movie has rate
      {

        sum_row += (movie.second[i]
                    * (user.get_ranks ()[movie.first] - average));
      }
    }
    preference_vec[i] = sum_row;
  }

  // phase_3: fined the similar vector in attributes_map
  sp_movie recommend_movie = user.get_ranks ().begin ()->first;
  double angle = MIN_ANGLE;
  for (auto const &movie: _attributes)
  {
    // check only unseen movies
    if (user.get_ranks ()[movie.first] == 0
        || user.get_ranks ().count (movie.first) == 0)
    {
      double cur_angle = fined_angle (preference_vec, movie.second);
      if (cur_angle > angle)
      {
        recommend_movie = movie.first;
        angle = cur_angle;
      }
    }
  }
  return recommend_movie;
}

/// check the header file
double RecommenderSystem::predict_movie_score
    (const RSUser &user, const sp_movie &movie, int k)
{
  similarity_map movie_similarity_map;
  similarity_map::iterator it;
  double predict_product = 0;
  double predict_dem = 0;

  //insert all movie sorted by similarity to map<doable similarity, sp movie>
  int seen = 0;
  int un_seen = 0;
  for (auto const &cur_movie: _attributes)
  {
    seen++;
    // check if the movie has seen and have a rate
    if (user.get_ranks ().count (cur_movie.first) == 1
        && user.get_ranks ()[cur_movie.first] != 0)
    {
      double angle = fined_angle (cur_movie.second, _attributes[movie]);
      movie_similarity_map[angle] = cur_movie.first;
      un_seen++;
    }
  }

  // calculate predict by given k
  int c = 0;
  for (auto const &rate: movie_similarity_map)
  {
    if ((un_seen - c) <= k) // reach to the k last values(at the end)
    {
      predict_product += ((rate.first) * user.get_ranks ()[rate.second]);
      predict_dem += rate.first;
    }
    c++;
  }
  return (predict_product / predict_dem);
}

/// check the header file
sp_movie RecommenderSystem::recommend_by_cf (const RSUser &user, int k)
{
  double angle = 0;
  sp_movie rec_movie;
  similarity_map movie_rate_map;
  // predict the rate for all unseen movies
  for (auto const &movie: _attributes)
  {
    // check if the movie for predict unseen yet
    if (user.get_ranks ().count (movie.first) == 0 || user.get_ranks ()
                                                      [movie.first] == 0)
    {
      double cur_angle = predict_movie_score (user, movie.first, k);
      if (cur_angle > angle)
      {
        rec_movie = movie.first;
        angle = cur_angle;
      }
    }
  }
  return rec_movie;
}

/// check the header file
sp_movie RecommenderSystem::get_movie (const std::string &name, int year)
{
  string str_year;
  str_year = std::to_string (year);
  //check if the movie is in the system
  if (_get_movie_map.find (name + str_year) == _get_movie_map.end ())
  {
    return nullptr;
  }
  else
  {
    return (_get_movie_map[name + str_year]);
  }
}

/// check the header file
double RecommenderSystem::vec_mult (const std::vector<double> &vec_1,
                                    const std::vector<double> &vec_2)
{
  double product = 0;
  for (size_t i = 0; i < vec_1.size (); i++)
  {
    product += vec_1[i] * vec_2[i];
  }
  return product;
}

/// check the header file
double RecommenderSystem::fined_angle (const std::vector<double> &vec_1, const
std::vector<double> &
vec_2)
{
  double angle;
  double norm_v1 = sqrt (vec_mult (vec_1, vec_1));
  double norm_v2 = sqrt (vec_mult (vec_2, vec_2));
  angle = (vec_mult (vec_1, vec_2) / (norm_v1 * norm_v2));
  return angle;
}

/// check the header file
std::ostream &operator<< (std::ostream &stream, const RecommenderSystem &rs)
{
  for (auto const &movie: rs._attributes)
  {
    stream << *(movie.first) << endl;
  }
  return stream;
}



