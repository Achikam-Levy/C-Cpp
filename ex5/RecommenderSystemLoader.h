
#ifndef RECOMMENDERSYSTEMLOADER_H
#define RECOMMENDERSYSTEMLOADER_H


#include "memory"
#include <sstream>
#include "RecommenderSystem.h"
#include <fstream>

#define MAX_RATE 10
#define MIN_RATE 1



typedef std::unique_ptr<RecommenderSystem> recommendation_system;
typedef std::unique_ptr<std::vector<double>> attributes_vec_p;


class RecommenderSystemLoader {
 private:

 public:

  RecommenderSystemLoader () = delete;
  /**
   * loads movies by the given format for movies with their feature's score
   * @param movies_file_path a path to the file of the movies
   * @return smart pointer to a RecommenderSystem which was created with
   * those movies
   */
  static recommendation_system  create_rs_from_movies_file(const std::string
  &movies_file_path) noexcept (false);

};

#endif //RECOMMENDERSYSTEMLOADER_H
