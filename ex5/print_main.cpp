//
// Created by 24565 on 6/1/2022.
//

#include "RecommenderSystemLoader.h"
#include "RSUsersLoader.h"

int main(){
    Movie m1("A",1998);
    Movie m4("D",1998);

    Movie m2("B",1996);
    Movie m3("C",1999);
    std::cout << (m1 < m2) << endl;
    std::cout << (m2 < m1) << endl;
    std::cout << (m1 < m3) << endl;
    std::cout << (m3 < m1) << endl;
    std::cout << (m4 < m1) << endl;


//    std::cout << m << std::endl;
//    auto rs = RecommenderSystemLoader::create_rs_from_movies_file("/Users/hyqmlwy/Desktop/university/year_2_sem_1/c_cpp/ex5-aaa997/RecommenderSystemLoader_input.txt");
//    std::cout << *rs << std::endl;
//    std::cout << (*(rs-> get_movie ("Twilight", 2008))) << std::endl;
//    auto users = RSUsersLoader::create_users_from_file("/Users/hyqmlwy/Desktop/university/year_2_sem_1/c_cpp/ex5-aaa997/RSUsersLoader_input.txt",std::move(rs));
//    std::cout << users[0] << std::endl;
}