

// don't change those includes
#include "RSUser.h"
#include "RecommenderSystem.h"

//RSUser
/// check header file
RSUser::RSUser (const string &user_name,
                std::shared_ptr<RecommenderSystem> &recommender_system,
                rank_map &user_rankings)
{
  _user_name = user_name;
  _recommender_system = recommender_system;
  _user_rankings = user_rankings;
}

/// check header file
string RSUser::get_name () const
{
  return _user_name;
}

/// check header file
void
RSUser::add_movie_to_rs(const std::string &name,int year,
                        const std::vector<double> &features, double rate)
{
  sp_movie movie = (*_recommender_system).add_movie (name, year, features);
  _user_rankings.insert (std::make_pair (movie, rate));
}

/// check header file
rank_map RSUser::get_ranks () const
{
  return _user_rankings;
}

/// check header file
sp_movie RSUser::get_recommendation_by_content ()
{
  return _recommender_system->recommend_by_content (*this);
}

/// check header file
sp_movie RSUser::get_recommendation_by_cf (int k) const
{
  auto x = _recommender_system->recommend_by_cf (*this, k);
  return x;
}

/// check header file
double
RSUser::get_prediction_score_for_movie (const std::string &name, int year,
                                        int k)
{
  sp_movie movie = _recommender_system->get_movie (name, year);
  double result = _recommender_system->predict_movie_score (*this, movie, k);
  return result;
}

/// check header file
std::ostream &operator<< (std::ostream &stream, const RSUser &rs_user)
{
  stream << "name: " << rs_user.get_name () << endl;
  stream << *(rs_user._recommender_system);
  return stream;
}
