//
// Created by j0sh on 3/20/16.
//
#include <fstream>
#include <sstream>
#include <random>
#include "markov_chain.h"

namespace std {
  template<>
  struct hash<std::pair<size_t, size_t>> {
    inline size_t operator()(const std::pair<size_t, size_t> &v) const {
      std::hash<size_t> size_t_hasher;
      return size_t_hasher(v.first) ^ size_t_hasher(v.second);
    }
  };
}


markov_chain::markov_chain(std::string path) {

  std::unordered_map<std::pair<size_t, size_t>, size_t> counter_map;


  std::ifstream input_file(path);
  std::string word, prev_word;

  /*need to process two words at a time, so process the first word specially*/
  size_t max_idx = 0;
  input_file >> prev_word;
  words_to_indexes[prev_word] = max_idx;
  indexed_words.push_back(prev_word);
  ++max_idx;

  while (input_file >> word) {
    if (!isalpha(word.front())) {
      continue;
    }
    if (words_to_indexes.find(word) == words_to_indexes.end()) {
      words_to_indexes[word] = max_idx;
      indexed_words.push_back(word);
      ++max_idx;
    }
    auto current_pair = std::make_pair(words_to_indexes[prev_word],
                                       words_to_indexes[word]);
    /*increment the counter for this two-word combination*/
    size_t prev_value = counter_map[current_pair];
    counter_map[current_pair] = prev_value + 1;

    prev_word = word;
  }

  /*assign all the default values*/
  /*pre-allocate memory*/
  edges = std::vector<std::unordered_map<size_t, size_t>>(max_idx);
  for (auto &p : counter_map) {
    edges[p.first.first][p.first.second] = p.second;
//    edges[p.first.first][p.first.second] = p.second * p.second;
  }
  for (auto &map : edges) {
    map.rehash(map.size() + 1);
  }
}

size_t markov_chain::pick_next(
    const std::unordered_map<size_t, size_t> &node_edges) {
  size_t total = 0;
  /*get the total*/
  for (auto &p : node_edges) {
    total += p.second;
  }
  /*for informational purposes*/
  size_t random_number = (size_t) std::rand() % total;
  /*incrementally find where this random value lies in the probability*/
  for (auto &p : node_edges) {
    if (random_number < p.second) {
      /*if less than, it lies within this range*/
      std::cout << 1.0 * p.second / total << std::endl;
      return p.first;
    } else {
      /*if greater than, it lies beyond this range*/
      random_number -= p.second;
    }
  }
  /*fail-safe*/
  throw std::runtime_error("something happened, invalid node?");
}

std::string markov_chain::get_words(size_t n_words) {
  std::stringstream output;
  /*randomly select the first word*/
  size_t current = rand() % edges.size();
  for (size_t i = 0; i < n_words; i++) {
    /*append the current word and a space*/
    output << indexed_words[current] << " ";

    if (edges[current].size() == 0) {
      /*we're out of places to go*/
      return output.str();
    }

    /*select the next word*/
    current = pick_next(edges[current]);
  }
  return output.str();
}
