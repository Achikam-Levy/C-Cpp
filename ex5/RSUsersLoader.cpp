//
// Created by אחיקם לוי on 31/12/2022.
//
#include "RSUsersLoader.h"
#include "RSUser.h"

///check header file
std::vector<RSUser> RSUsersLoader::create_users_from_file (const std::string &
users_file_path, recommendation_system attributes_system) noexcept (false)
{
  std::vector<RSUser> users_vec;
  std::vector<sp_movie> movies_vec;
  std::shared_ptr<RecommenderSystem> features_system = std::move
      (attributes_system);
  // parse the text
  int line_counter = 0, size = 0;
  double int_rate = 0;
  string cur_line;
  sp_movie cur_movie;
  std::fstream users_file;
  users_file.open (users_file_path, std::ios::in);
  if (!users_file.good ())
  { throw std::runtime_error ("error open file"); }
  while (getline (users_file, cur_line))
  {
    // parse only the first line - line of movies names
    if (line_counter == 0)
    {
      std::replace (cur_line.begin (), cur_line.end (), '-', ' ');
      int names_counter = 0;
      std::istringstream iss (cur_line);
      sp_movie movie;
      while (iss)
      {
        string movie_name;
        int year;
        if ((names_counter % 2) == 0) // mange the movie year queue
        {
          (iss >> movie_name);
          if (!movie_name.empty ())
          {
            (iss >> year);
            cur_movie = std::make_shared<Movie> (movie_name, year);
            movies_vec.push_back (cur_movie);
            size++;
          }
        }
        names_counter++;
      }
      line_counter++;
    }
    else
    {
      pharse_user (users_vec, movies_vec, features_system,
                   size, int_rate, cur_line);
    }
  }
  return users_vec;
}

///check header file
void RSUsersLoader::pharse_user (std::vector<RSUser> &users_vec, const
std::vector<sp_movie> &movies_vec, std::shared_ptr<RecommenderSystem>
    &features_system, int size, double int_rate, const string &cur_line)
{
  std::istringstream iss (cur_line);
  int c = 0;
  string user_name, rate;
  while (iss)
  {
    // parse the current username
    if (c == 0)
    {
      (iss >> user_name);
    }
      // parse the given rates
    else
    {
      int i = 0;
      rank_map user_rankings (0, sp_movie_hash, sp_movie_equal);
      while (iss >> rate && i < size)
      {
        if (rate == "NA"){ user_rankings[movies_vec[i]] = 0; }//movie not rated
        else
        {
          int_rate = std::stod (rate);
          user_rankings[movies_vec[i]] = int_rate;
        }
        if ((int_rate < MIN_RATE && rate != "NA") || int_rate > MAX_RATE)
        {
          throw std::runtime_error ("rate must be between 1 and 10");
        }
        i++;
      }
      RSUser cur_user (user_name, features_system, user_rankings);
      users_vec.push_back (cur_user);
    }
    c++;
  }
}
