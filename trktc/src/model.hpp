//
// Created by Gleb Dolgich on 04/01/2020.
//

#ifndef TRKTC_MODEL_HPP
#define TRKTC_MODEL_HPP

#include <chrono>
#include <string>
#include <unordered_map>
#include <unordered_set>

// https://trakt.docs.apiary.io/#reference/episodes/summary/get-a-single-episode-for-a-show
struct episode
{
  int season{0};
  int number{0};
  std::string title;
  std::unordered_map<std::string, std::string> ids;
  std::string overview;
  std::chrono::year_month_day first_aired_date;
  int rating{0};
  int vote_count{0};
  int comment_count{0};
  std::unordered_set<std::string> translations;
  int runtime{0};
};

#endif // TRKTC_MODEL_HPP
