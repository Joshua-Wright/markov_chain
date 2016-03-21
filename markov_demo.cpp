// (c) Copyright 2016 Josh Wright

#include "markov_chain.h"
#include <random>
#include <ctime>

int main(int argc, char const *argv[]) {
  std::srand(std::time(nullptr));
  std::string input("/home/j0sh/Dropbox/code/Cpp/markov/KingJamesBible.txt");
//  std::string input("/home/j0sh/Dropbox/code/Cpp/markov/TomSawyer.txt");
//  std::string input("/home/j0sh/Dropbox/code/Cpp/markov/Shakespeare.txt");
  markov_chain chain(input);
  std::cout << chain.get_words(300) << std::endl;
  return 0;
}
