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
#include <vector>

class markov_chain {

  std::unordered_map<std::string, size_t> words_to_indexes;
  std::vector<std::string> indexed_words;

  /*the map maps node indexes to counts*/
  std::vector<std::unordered_map<size_t, size_t>> edges;

  static size_t pick_next(const std::unordered_map<size_t, size_t>&node_edges);

public:
  markov_chain(std::string path);

  std::string get_words(size_t n_words);

};


#endif //MARKOV_MARKOV_CHAIN_H
