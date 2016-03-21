// (c) Copyright 2016 Josh Wright

#include "markov_chain.h"
#include <random>
#include <ctime>

int main(int argc, char const *argv[]) {
  markov_chain chain;
//  chain.parse_book("../TomSawyer.txt");
//  chain.parse_book("../gop_debate_all.txt");
  chain.parse_book("../trump.txt");
//  chain.write_to("test.txt");
  std::cout << chain.get_words(300) << std::endl;
//  std::cout << chain.get_words(300, "TRUMP:") << std::endl;

//  markov_chain chain2;
//  chain2.read_from("test.txt");
//  std::cout << chain2.get_words(20) << std::endl;

  return 0;
}
