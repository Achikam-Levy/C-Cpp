//
// Created on 2/21/2022.
//

#ifndef USERFACTORY_H
#define USERFACTORY_H
#include "RecommenderSystem.h"
#include "RecommenderSystemLoader.h"
#include <fstream>
#include "RSUser.h"
#include "memory"
#include <sstream>
#include <algorithm>
#include <string>




//typedef std::unique_ptr<RSUser> RSUsers_system;

class RSUsersLoader
{
 private:

 public:
  RSUsersLoader () = delete;
  /**
   *
   * loads users by the given format with their movie's ranks
   * @param users_file_path a path to the file of the
   * users and their movie ranks
   * @param rs RecommendingSystem for the Users
   * @return vector of the users created according to the file
   */
  static std::vector<RSUser>
  create_users_from_file (const std::string &users_file_path,
                          recommendation_system attributes_system)
  noexcept (false);

  /**
   * a helper function that parse a line of a user, after the movies line
   * parsed.
   * @param users_vec vector of users
   * @param movies_vec vector of movies
   * @param features_system pointer to the recommendation system
   * @param size var of the attributes number
   * @param int_rate var of the current rate to parse
   * @param cur_line current line to parse
   */
  static void pharse_user (std::vector<RSUser> &users_vec, const
  std::vector<sp_movie> &movies_vec, std::shared_ptr<RecommenderSystem>
                           &features_system, int size, double int_rate,
                           const string &cur_line);
};

#endif //USERFACTORY_H
