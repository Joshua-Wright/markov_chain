//
// Created by j0sh on 3/20/16.
//

#ifndef MARKOV_MARKOV_CHAIN_H
#define MARKOV_MARKOV_CHAIN_H

#include <string>
#include <utility>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>

class markov_chain {

  std::unordered_map<std::string, size_t> words_to_indexes;
  std::vector<std::string> words;

  /*the map maps node indexes to counts*/
  std::vector<std::vector<std::pair<size_t, size_t>>> edges;

  size_t pick_next(const std::vector<std::pair<size_t, size_t>> &node_edges);

  std::mt19937_64 prng;

public:
  markov_chain();

  void parse_book(const std::string &path);

  std::string get_words(const size_t n_words, const std::string &starting_word = "");

  void write_to(const std::string &path);

  void read_from(const std::string &path);

};


#endif //MARKOV_MARKOV_CHAIN_H
