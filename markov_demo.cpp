// (c) Copyright 2016 Josh Wright

#include "markov_chain.h"

int main(int argc, char const *argv[]) {
  markov_chain chain;
//  chain.parse_book("../TomSawyer.txt");
//  chain.parse_book("../KingJamesBible.txt");
//  chain.parse_book("../gop_debate_all.txt");
  chain.parse_book("../trump.txt");
//  chain.write_to("test.txt");
  for (int i=0; i<10; i++) {
    std::cout << chain.get_sentence() << std::endl;
//    std::cout << chain.get_sentence() << std::endl;
  }
  std::cout << chain.get_sentence() << std::endl;

  return 0;
}
