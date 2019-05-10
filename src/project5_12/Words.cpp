#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <iterator>


int main(int argv, char **argc)
{
   std::string str;
   std::vector<std::string> words;
   std::unordered_set<std::string> wordsHash;
   std::set<std::string> wordsSet;

   while (std::cin >> str && str != "Quit") {
      if (wordsHash.find(str) == wordsHash.end()) {
       words.push_back(str);
       wordsHash.insert(str);
      }
   }

   std::copy(words.begin(), words.end(),
         std::ostream_iterator<std::string>(std::cout, " "));
   std::cout << std::endl;


   while (std::cin >> str && str != "Quit") {
      wordsSet.insert(str);
   }

   std::copy(wordsSet.begin(), wordsSet.end(),
         std::ostream_iterator<std::string>(std::cout, " "));
   std::cout << std::endl;

   return 0;
}