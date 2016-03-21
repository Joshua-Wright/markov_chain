#include <string>
#include <utility>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;


int main() {
  using std::unordered_map;
  using std::string;
  using std::cout;
  using std::endl;
  using std::size_t;

  string input("/home/j0sh/Dropbox/code/Cpp/markov/KingJamesBible.txt");
  ifstream input_file(input);
  string word;
  size_t index = 0;
  unordered_map<string, size_t> all_words;
  while (input_file >> word) {
//    if (word.back() == '.' || word.back() == '!' || word.back() == '?') {
//      word.erase(--word.end());
//    }
    if (all_words.find(word) == all_words.end()) {
      all_words[word] = index;
      ++index;
    }
  }
  std::vector<string> words(index);
  for (const std::pair<const string, size_t> &pair : all_words) {
    words[pair.second] = pair.first;
  }
  cout << "unique word count: " << index << endl;

  /*here lies the classic "can I really use this much ram? Wow, I can!" test*/
//  double *array = new double[29538*29538];
//  for (int i=0; i<29538*29538; i++) {
//    array[i] = i*i;
//  }
//  cout << array << endl;
//  char c;
//  cin >> c;

  return 0;
}