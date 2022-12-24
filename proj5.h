#ifndef __PROJECT5_HPP
#define __PROJECT5_HPP

#include <vector>
#include <unordered_set>
#include <unordered_map>

void loadWordsIntoTable(std::unordered_set<std::string>& words, std::istream& in);


std::vector< std::string > convert(const std::string& s1, const std::string& s2, const std::unordered_set<std::string>& words);
unsigned checkLetterDifferences(std::string s2, std::string str);
void DijkstraAlgorithm(std::string s1, std::string s2, std::unordered_map<std::string, std::string>& tree, const std::unordered_set<std::string>& words);

#endif 
