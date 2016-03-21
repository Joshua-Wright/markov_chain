//
// Created by j0sh on 3/20/16.
//
#include <fstream>
#include <sstream>
//#include <random>
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


void markov_chain::parse_book(const std::string &path) {
  std::unordered_map<std::pair<size_t, size_t>, size_t> counter_map;

  std::ifstream input_file(path);
  std::string word, prev_word;

  /*need to process two words at a time, so process the first word specially*/
  size_t max_idx = words.size();
  input_file >> prev_word;
  if (words_to_indexes.find(prev_word) == words_to_indexes.end()) {
    words_to_indexes[prev_word] = max_idx;
    words.push_back(prev_word);
    ++max_idx;
  }

  while (input_file >> word) {
    if (words_to_indexes.find(word) == words_to_indexes.end()) {
      words_to_indexes[word] = max_idx;
      words.push_back(word);
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
//  edges = std::vector<std::unordered_map<size_t, size_t>>(max_idx);
  edges = std::vector<std::vector<std::pair<size_t, size_t>>>(max_idx);
  for (auto &p : counter_map) {
//    edges[p.first.first][p.first.second] = p.second;
    edges[p.first.first].push_back(std::make_pair(p.first.second, p.second));
//    edges[p.first.first][p.first.second] = p.second * p.second;
  }
  for (auto &node : edges) {
//    node.rehash(node.size() + 1);
    node.shrink_to_fit();
  }

}

markov_chain::markov_chain() {
  prng.seed((unsigned long) time(nullptr));
}

size_t markov_chain::pick_next(
    const std::vector<std::pair<size_t, size_t>> &node_edges) {
  size_t total = 0;
  /*get the total*/
  for (auto &p : node_edges) {
    total += p.second;
  }
  auto gen = std::uniform_int_distribution<size_t>(0, total - 1);
  size_t random_number = gen(prng);
  /*incrementally find where this random value lies in the probability*/
  for (auto &p : node_edges) {
    if (random_number < p.second) {
      /*if less than, it lies within this range*/
//      std::cout << 1.0 * p.second / total << std::endl;
      return p.first;
    } else {
      /*if greater than, it lies beyond this range*/
      random_number -= p.second;
    }
  }
  /*fail-safe*/
  throw std::runtime_error("something happened, invalid node?");
}

std::string markov_chain::get_words(const size_t n_words,
                                    const std::string &starting_word) {
  std::stringstream output;
  /*randomly select the first word*/
  size_t current;
  if (starting_word.empty()) {
    auto gen = std::uniform_int_distribution<size_t>(0,
                                                     words_to_indexes.size());
    current = gen(prng);
  } else {
    current = words_to_indexes[starting_word];
  }
  for (size_t i = 0; i < n_words; i++) {
    /*append the current word and a space*/
    output << words[current] << " ";

    if (edges[current].size() == 0) {
      /*we're out of places to go*/
      return output.str();
    }

    /*select the next word*/
    current = pick_next(edges[current]);
  }
  return output.str();
}

void markov_chain::write_to(const std::string &path) {
  std::ofstream output_file(path);

  for (int i = 0; i < words.size(); i++) {
    /*each line starts wtih the word*/
    output_file << words[i];

    /*followed by the list of edges and counts*/
    for (auto &edge : edges[i]) {
      /*write the space first so that the trailing newline immediately follows
       * the final number*/
      output_file << " " << edge.first << " " << edge.second;
    }
    /*separate nodes using newline*/
    output_file << std::endl;
  }
}

void markov_chain::read_from(const std::string &path) {
  /*clear all the previous stuff*/
  edges.clear();
  words.clear();
  words_to_indexes.clear();

  std::ifstream input(path);
  size_t max_index = 0;
  while (true) { /*while not end of file*/
    /*input the word*/
    std::string word;
    input >> word;
    if (word.empty()) {
      break;
    }
    words.push_back(word);
    words_to_indexes[word] = max_index;
    ++max_index;

    /*input the word's edges*/
    edges.emplace_back(); /*add a new empty vector*/
    while (input.peek() != '\n') {
      size_t index;
      input >> index;
      size_t count;
      input >> count;
      /*1 * index to make IDE not complain*/
      edges.back().emplace_back(1 * index, count);
    }
    /*ignore the trailing newline*/
    input.ignore();
  }
}
