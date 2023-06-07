#include "Movie.h"
#include "assert.h"
#include "RecommenderSystemLoader.h"
#include "RSUsersLoader.h"
#include "string"

static std::string BASE_PATH = "";

void check_geters ()
{
  Movie m1 ("Twilight", 2008);
  Movie m2 ("Titanic", 1997);
  Movie m3 ("Batman", 2022);
  int x = m3.get_name ().std::string::compare ("Batman");
  assert(m3.get_year () == 2022);
  assert(x == 0);
  assert(m1.get_year () == 2008);
};

void check_op ()
{
  Movie m1 ("Twilight", 1997);
  Movie m2 ("Titanic", 1997);
  Movie m3 ("Batman", 2022);
  Movie m4 ("Batman", 1099);

  assert((m4 < m3));
  assert(!(m3 < m4));
  assert(m2 < m1);
}

void check_getters_rs ()
{
  Movie m1 ("Twilight", 2008);
  Movie m2 ("Titanic", 1997);
  Movie m3 ("Batman", 2022);
  auto p = RecommenderSystemLoader::create_rs_from_movies_file ("RecommenderSystemLoader_input.txt");
  auto temp1 = p->get_movie ("Titanic", 1997);
  assert(temp1->get_year () == 1997);
  auto temp2 = p->get_movie ("Asd", 2005);
  assert(!temp2);
  auto temp3 = p->get_movie ("Batman", 2024);
  assert(!temp3);

}

void check_add_rs ()
{
  std::vector<double> v1 = {4, 5, 6, 8};
  Movie m1 ("Twilight", 2008);
  Movie m2 ("Titanic", 1997);
  Movie m3 ("Batman", 2022);
  auto p = RecommenderSystemLoader::create_rs_from_movies_file ("RecommenderSystemLoader_input.txt");
  p->add_movie ("Dorf", 2021, v1);
  auto temp1 = p->get_movie ("Dorf", 2021);
  assert(temp1->get_year () == 2021);
}

void check_users_names ()
{
  std::string rs_point = "RecommenderSystemLoader_input.txt";
  std::vector<RSUser> users = RSUsersLoader::create_users_from_file ("RSUsersLoader_input.txt", RecommenderSystemLoader::create_rs_from_movies_file (rs_point));
  assert(users[0].get_name () == "Sofia");
  assert(users[1].get_name () == "Michael");
  assert(users[2].get_name () == "Nicole");
  assert(users[3].get_name () == "Arik");
  assert(users.size () == 4);

};

void check_users_func ()
{
  std::string rs_point = "RecommenderSystemLoader_input.txt";
  std::vector<RSUser> users = RSUsersLoader::create_users_from_file
      ("RSUsersLoader_input.txt",
       std::move(RecommenderSystemLoader::create_rs_from_movies_file)
       (rs_point));
  assert(users[2].get_recommendation_by_cf (2)->get_name () == "Titanic");
  assert(users[0].get_recommendation_by_content ()->get_name () == "Batman");
//    std::cout << users[2].get_prediction_score_for_movie ("Titanic", 1997, 2) << endl;
  assert(5.4 < users[2].get_prediction_score_for_movie ("Titanic", 1997, 2)
         && users[2].get_prediction_score_for_movie ("Titanic", 1997, 2)
            < 5.5);
  assert(users[2].get_prediction_score_for_movie ("Titanic", 1997, 1) == 5);
//  std::cout << users[2].get_prediction_score_for_movie ("Titanic", 1997, 2)
//   << endl;
  assert(3.5 < users[2].get_prediction_score_for_movie ("Twilight", 2008, 2) &&
         users[2].get_prediction_score_for_movie ("Twilight", 2008, 2) < 3.6);

}

int main ()
{
  check_geters ();
  check_op ();
  check_getters_rs ();
  check_add_rs ();
  check_users_names ();
  check_users_func ();

  std::string rs_point = "RecommenderSystemLoader_input.txt";
  std::vector<RSUser> users = RSUsersLoader::create_users_from_file ("RSUsersLoader_input.txt", RecommenderSystemLoader::create_rs_from_movies_file (rs_point));
  std::cout << users[0];
}
//  int status = 0;
//
//  try
//  {
//    // check all function for RS exist
//    RecommenderSystem rec;
//    sp_movie a = rec.add_movie ("Batman", 2022, {1, 2, 3, 4});
//    sp_movie b = rec.add_movie ("StarWars", 1977, {1, 2, 3, 5});
//    sp_movie c = rec.add_movie ("ForestGump", 1994, {1, 2, 3, 4});
//
//    // check all functions for user and UsersLoader exist and movie
//    auto rs1 = RecommenderSystemLoader::create_rs_from_movies_file (
//        BASE_PATH + "presubmit.in_m");
//    std::vector<RSUser> users = RSUsersLoader::create_users_from_file (
//        BASE_PATH + "presubmit.in_u", std::move (rs1));
//    sp_movie movie = users[0].get_recommendation_by_content ();
//    double s = users[0].get_prediction_score_for_movie ("Titanic", 1997, 2);
//    sp_movie m2 = users[0].get_recommendation_by_cf (2);
//    if (s < 0)
//    {
//      std::cerr << "a score should be larger or equal to 0" << std::endl;
//      status = 1;
//    }
//
//    // check movie functions and some results
//    if (movie->get_name () != "Batman" || movie->get_year () != 2022)
//    {
//      status = 1;
//      std::cerr
//          << "Recommend by content with username=Sofia failed! Received="
//          << *movie << " Expected=Batman (2022)" << std::endl;
//    }
//    double y = users[2].get_prediction_score_for_movie ("Twilight", 2008, 2);
//    if (std::abs (y - 3.5244) > 0.01)
//    {
//      status = 1;
//      std::cerr
//          << "Predict movie score for moviename=Twilight , username=Nicole, k=2 failed! Received="
//          << y << " Expected=3.5244" << std::endl;
//    }
//    double z = users[2].get_prediction_score_for_movie ("Titanic", 1997, 2);
//    if (std::abs (z - 5.46432) > 0.01)
//    {
//      status = 1;
//      std::cerr
//          << "Predict movie score for moviename=Titanic, username=Nicole, k=2 failed! Received="
//          << z << " Expected=5.46432" << std::endl;
//    }
//    if (status != 0)
//    {
//      std::cerr << "Failed presubmit tests, you have errors" << std::endl;
//      return 1;
//    }
//  }
//  catch (const std::exception &e)
//  {
//    std::cerr
//        << "Your program crashed by arised exception - presubmit tests failed"
//        << std::endl;
//    return 2;
//  }
//}
//
