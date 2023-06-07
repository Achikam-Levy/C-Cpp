//
// Created on 2/20/2022.
//

#ifndef RECOMMENDERSYSTEM_H
#define RECOMMENDERSYSTEM_H

#include <iostream>
#include <vector>
#include <memory>
#include "RSUser.h"
#include "Movie.h"
#include <functional>

#define MIN_ANGLE (-2)

typedef std::map<sp_movie, const std::vector<double>> attributes_map;
typedef std::map<double, sp_movie> similarity_map;
typedef std::map<string, sp_movie> get_movie_map;

class RecommenderSystem
{
 private:
  attributes_map _attributes; // map a movie to his features
  get_movie_map _get_movie_map; // map a string of movie name to his movie


 public:
  RecommenderSystem ();

  //explicit RecommenderSystem()
  /**
   * adds a new movie to the system
   * @param name name of movie
   * @param year year it was made
   * @param features features for movie
   * @return shared pointer for movie in system
   */
  sp_movie add_movie (const std::string &name, int year, const
  std::vector<double> &features);

  /**
   * a function that calculates the movie with highest
   * score based on movie features
   * @param ranks user ranking to use for algorithm
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_content (const RSUser &user);

  /**
   * a function that calculates the movie with highest
   * predicted score based on ranking of other movies
   * @param ranks user ranking to use for algorithm
   * @param k
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_cf (const RSUser &user, int k);

  /**
   * Predict a user rating for a movie given argument
   * using item cf procedure with k most similar movies.
   * @param user_rankings: ranking to use
   * @param movie: movie to predict
   * @param k:
   * @return score based on algorithm as described in pdf
   */
  double predict_movie_score (const RSUser &user, const sp_movie &movie,
                              int k);

  /**
   * gets a shared pointer to movie in system
   * @param name name of movie
   * @param year year movie was made
   * @return shared pointer to movie in system
   */
  sp_movie get_movie (const std::string &name, int year);

  /**
   *
   * @param vec_1 vector of features
   * @param vec_2 vector of features
   * @return the angle between the vectors (-1 <= angle <= 1)
   */
  static double fined_angle (const std::vector<double> &vec_1,
                             const std::vector<double> &vec_2);

  /**
   *
   * @param vec_1 vector of features
   * @param vec_2 vector of features
   * @return the scalar multiplication product of the vectors
   */
  static double vec_mult (const std::vector<double> &vec_1,
                          const std::vector<double> &vec_2);

  /**
   *
   * @param stream ostream object
   * @param rs RecommenderSystem object
   * @return ostream object for continue
   */
  friend std::ostream &operator<< (std::ostream &stream, const
  RecommenderSystem &rs);

};

#endif //RECOMMENDERSYSTEM_H
