//
// Created by אחיקם לוי on 31/12/2022.
//

#include "RecommenderSystemLoader.h"

/// check header file
recommendation_system RecommenderSystemLoader::create_rs_from_movies_file
    (const string &movies_file_path) noexcept (false)
{
  recommendation_system attributes_system =
      std::make_unique<RecommenderSystem> ();

  // parse the text
  std::fstream movies_file;
  movies_file.open (movies_file_path, std::ios::in);
  if (movies_file.is_open ()) // check file is opened
  {
    string cur_line;

    while (getline (movies_file, cur_line))
    {
      std::istringstream cur_tok (cur_line);
      string movie_name;
      getline (cur_tok, movie_name, '-');
      int year;
      (cur_tok >> year);
      double attribute;
      std::vector<double> attributes_vec;
      while (cur_tok >> attribute) // insert all attributes
      {
        // checks if attribute is (1 <= int <= 10 )
        if ((MIN_RATE <= attribute) && (attribute <= MAX_RATE))
        {
          (attributes_vec).push_back (attribute);
        }
        else
        {
          throw std::runtime_error ("attribute must be an (1 <= int < 10 )");
        }
      }
      (*attributes_system).add_movie (movie_name, year, attributes_vec);
      attributes_vec.clear ();
    }
  }
  else
  {
    throw std::runtime_error ("error open file");
  }
  return attributes_system;
}
