#include "proj5.h"
#include "MyPriorityQueue.h"
#include <string>
#include <sstream>
#include <unordered_set>
#include <string>
#include <iterator>
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

// You should not need to change this function.
void loadWordsIntoTable(std::unordered_set<std::string>& words, std::istream& in)
{
	std::string line, word;
	std::stringstream ss;

	while (getline(in, line))
	{
		ss.clear();
		ss << line;
		while (ss >> word)
		{
			words.insert(word);
		}
	}

}

unsigned checkLetterDifferences(std::string s2, std::string str)
{
	unsigned count = 0;
	for (unsigned i = 0; i < s2.size(); i++) {
		if (s2[i] != str[i]) {
			count++;
		}
	}
	return count;
}

void DijkstraAlgorithm(std::string s1, std::string s2, std::unordered_map<std::string, std::string>& tree, const std::unordered_set<std::string>& words)
{
	MyPriorityQueue<pair<unsigned, string>> pq;
	unordered_map<string, unsigned> distanceFromStart;
	map<string, string> mapOfStringPath;
	distanceFromStart.emplace(s1, 0);
	pq.insert(make_pair(0, s1));
	string prevWord = s1;
	while (!pq.isEmpty()) {
		string currentWord = pq.min().second;
		unsigned currPathNum = pq.min().first;
		pq.extractMin();
		for (unsigned i = 0; i < currentWord.size(); i++) {
			string temp = currentWord;
			for (char ch = 'a'; ch <= 'z'; ch++) {
				temp[i] = ch;
				if (temp == s1) {
					continue;
				}
				if (tree.find(temp) != tree.end() || tree.find(s2) != tree.end()) {
					continue;
				}
				if (words.find(temp) != words.end()) {
					if (distanceFromStart.find(temp) == distanceFromStart.end()) {
						distanceFromStart.emplace(temp, distanceFromStart[currentWord] + 1);
					}
					mapOfStringPath.emplace(temp, currentWord);
					unsigned minSum = distanceFromStart[temp] + checkLetterDifferences(s2, temp) + currPathNum;;
					pq.insert(make_pair(minSum, temp));
				}
			}
		}
		if (tree.find(currentWord) == tree.end()) {
			//cout << currentWord << " " << prevWord << endl;
			prevWord = mapOfStringPath[currentWord];
			tree.emplace(currentWord, prevWord);
		}
	}

}

// You probably want to change this function.
std::vector< std::string > convert(const std::string& s1, const std::string& s2, const std::unordered_set<std::string>& words)
{

	std::vector< std::string > ret;

	if (s1.size() != s2.size()) {                        //if the two strings' size are not the same, return empty vector
		return ret;
	}
	if (words.find(s1) == words.end() || words.find(s2) == words.end()) {    //if the words are not in the dictionary, return empty vector
		return ret;
	}
	if (s1 == s2) {                                      //if the words are the same, return empty vector
		return ret;
	}

	unordered_map<string, string> list;
	DijkstraAlgorithm(s1, s2, list, words);
	unordered_map<string, string>::iterator it = list.begin();
	string key = s2;
	while (it != list.end()) {
		if (list.find(key) != list.end()) {
			string value = list[key];
			ret.insert(ret.begin(), 1, value);
			if (value == s1) {
				ret.push_back(s2);
			}
			key = value;
			//cout << "INSIDE OF THE VECTOR: " << value << endl;
		}
		it++;
	}

	return ret;  // stub obviously 
}

