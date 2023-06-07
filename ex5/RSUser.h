//
// Created on 2/20/2022.
//

#ifndef USER_H
#define USER_H
#include <unordered_map>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include "Movie.h"

class RecommenderSystem;

typedef std::unordered_map<sp_movie, double, hash_func, equal_func> rank_map;

class RSUser
{
 private:
  string _user_name;
  rank_map _user_rankings;
  std::shared_ptr<RecommenderSystem> _recommender_system;
 public:
  /**
   * Constructor for the class
   */
  RSUser (const string &user_name, std::shared_ptr<RecommenderSystem> &
  recommender_system, rank_map &user_rankings);

  /**
   * a getter for the user's name
   * @return the username
   */
  string get_name () const;
  /**
   * function for adding a movie to the DB
   * @param name name of movie
   * @param year year it was made
   * @param features a vector of the movie's features
   * @param rate the user rate for this movie
   */
  void add_movie_to_rs (const std::string &name, int year,
                        const std::vector<double> &features,
                        double rate);

  /**
   * a getter for the ranks map
   * @return
   */
  rank_map get_ranks () const;

  /**
   * returns a recommendation according to the movie's content
   * @return recommendation
   */
  sp_movie get_recommendation_by_content ();

  /**
   * returns a recommendation according to the similarity recommendation method
   * @param k the number of the most similar movies to calculate by
   * @return recommendation
   */
  sp_movie get_recommendation_by_cf (int k) const;

  /**
   * predicts the score for a given movie
   * @param name the name of the movie
   * @param year the year the movie was created
   * @param k the parameter which represents the number of
   * the most similar movies to predict the score by
   * @return predicted score for the given movie
   */
  double
  get_prediction_score_for_movie (const std::string &name, int year, int k);

  /**
   * output stream operator
   * @param os the output stream
   * @param user the user
   * @return output stream
   */
  friend std::ostream &
  operator<< (std::ostream &stream, const RSUser &rs_user);
};

#endif //USER_H
