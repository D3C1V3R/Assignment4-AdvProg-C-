/**********************************************************************
 * wordstats.cpp - CSCI251 - Ass4 - Contains WordsStats class definition
 * <your name> <your login> <date last modified>
 **********************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include "wordstats.h"
#include <algorithm>
using namespace std;

WordStats::WordStats(){

}

// Reads dictionary.txt into Dictionary
void WordStats::ReadDictionary() {
	ifstream File("dictionary.txt");
	if (!File.is_open()) {
		cout << "Can't find data file!\n";
		return;
	}

	for (string line; getline(File, line); ) {
		Dictionary.insert(line);
	}

	cout << Dictionary.size() << "words in the dictionary." << endl;
}

// Displays Dictwords 10 at a time
void WordStats::DisplayDictionary(){
	if (Dictionary.size() == 0) {
		cout << "Please load the dictionary first!" << endl;
		return;
	}
	int i = 0;
	while (i<=10){
		for (set<string>::iterator it = Dictionary.begin(); it != Dictionary.end(); ++it) {
			std::cout << *it << endl;
			i++;
			if (i >= 10) {
				string input;
				cout << "Would you like 10 more results? (y/n) \n";
				cin >> input;
				if (input != "y") {
					cin.ignore();
					return;
				}
				else {
					i = 0;
					cout << endl;
				}
			}
		}
	}	
}

// Reads textfile into KnownWords and UnknownWords
void WordStats::ReadTxtFile(){
	cout << "Enter filename: ";
	string input;
	cin >> input;


	ifstream File(input);
	if (!File.is_open()) {
		cout << "Can't find data file!\n";
		cin.ignore();
		return;
	}

	string line;
	int i = 0;
	while (File >> line) {
		if (line == " ") {
			continue;
		}
		line.erase(remove_if(line.begin(), line.end(), ispunct), line.end());
		transform(line.begin(), line.end(), line.begin(), tolower);

		set<string>::iterator it = Dictionary.find(line);;
		WordMapIter itr = KnownWords.find(line);
		WordMapIter itu = UnknownWords.find(line);

		if (it != Dictionary.end()) {		//Exists in Dictionary
			if (itr != KnownWords.end()){	//Exists in KnownWords
				(*itr).second.push_back(i);
			}
			else {
				vector<int> vect(1, i);		//vector with one element
				KnownWords.insert(itr, pair<string, vector<int>>(line, vect));
			}
		}else {
			if (itu != UnknownWords.end()) { //Exists in UnknownWords

				(*itu).second.push_back(i);
			}
			else {
				vector<int> vect(1, i);		//vector with one element
				UnknownWords.insert(itu, pair<string, vector<int>>(line, vect));
			}
		}
		i++;
	}
	//89 known words read.
	//49 unknown words read.
	cout << KnownWords.size() << " known words read." << endl;
	cout << UnknownWords.size() << " unknown words read." << endl;
	cin.ignore();
}

// Displays stats of words in KnownWords
void WordStats::DisplayKnownWordStats(){
	DisplayWordStats(KnownWords);
}

void WordStats::DisplayUnknownWordStats() {
	DisplayWordStats(UnknownWords);
}

// Displays stats of words in Unknownwords
void WordStats::DisplayWordStats(WordMap  &WMap) {
	// print out the map:
	cout << "Ch" << setw(15) << "  Cnt" << setw(4) << "  Indexes\n";
	for (WordMapIter itr = WMap.begin(); itr != WMap.end(); ++itr) {
		string ch = (*itr).first;
		vector<int> vect = (*itr).second;
		int cnt = vect.size();
		cout << left << setw(15) << ch
			<< left << setw(4) << cnt
			<< left << setw(4) << "   ";
		for (int i = 0; i<cnt; i++)
			cout << vect[i] << ' ';
		cout << endl;
	}
}


// Displays 20 most frequent words in KnownWords
void WordStats::DisplayMostFreqKnownWords(){
	DisplayMostFreqWords(KnownWords);
}
// Displays 20 most frequent words in UnknownWords
void WordStats::DisplayMostFreqUnknownWords(){
	DisplayMostFreqWords(UnknownWords);
}

// Displays 20 most frequent words in WordMap
void WordStats::DisplayMostFreqWords(WordMap &Words) {
	multimap<int, string> m; // new map with int as key (multimap because key could occur more than once)
	for (WordMapIter itr = Words.begin(); itr != Words.end(); ++itr) { // iterate map again
		string ch = (*itr).first;
		int cnt = (*itr).second.size();
		m.insert(pair<int, string>(cnt, ch)); // insert with count as the key
	}

	// print out the new map:
	multimap<int, string>::reverse_iterator itx; // iterator for new map
	cout << "Cnt  Ch\n";
	int i = 0;
	for (itx = m.rbegin(); itx != m.rend() && i <= 20; ++itx) {
		i++;
		string ch = (*itx).second;
		int cnt = (*itx).first;
		cout << setw(3) << cnt << "   " << ch << endl;
	}
	cout << endl;
}
// Displays original text from KnownWords & UnknownWords
void WordStats::DisplayOriginalText(){
	WordMap cMap;			//Combine maps into one map
	map<int,string> nMap;			//New Maplist
	cMap.insert(KnownWords.begin(), KnownWords.end());
	cMap.insert(UnknownWords.begin(), UnknownWords.end());

	for (WordMapIter itr = cMap.begin(); itr != cMap.end(); ++itr) {
		vector<int> vect = (*itr).second;
		int cnt = vect.size();
		for (int i = 0; i < cnt; i++) {
			nMap.insert(pair<int,string>(vect[i], (*itr).first));
		}
	}
	
	string output;
	
	for (map<int, string>::iterator it = nMap.begin(); it != nMap.end(); ++it) {
		cout << it->second << " ";
	}
}