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
	cout << "Enter filename:" << endl;
	string input;
	cin >> input;


	ifstream File(input);
	if (!File.is_open()) {
		cout << "Can't find data file!\n";
		cin.ignore();
		return;
	}
	int i = 0;
	string line;
	int a = 0;
	int b = 0;
	while (File >> line) {
		line.erase(remove_if(line.begin(), line.end(), ispunct), line.end());
		transform(line.begin(), line.end(), line.begin(), tolower);
		i++;

		set<string>::iterator it = Dictionary.find(line);;
		WordMapIter itr = KnownWords.find(line);
		WordMapIter itu = UnknownWords.find(line);

		if (it != Dictionary.end()) {		//Exists in Dictionary
			if (itr != KnownWords.end()){	//Exists in KnownWords
				(*itr).second.push_back(i);
			}
			else {
				a++;
				vector<int> vect(1, i);		//vector with one element
				KnownWords.insert(itr, pair<string, vector<int>>(line, vect));
			}
		}else {
			cout << line << endl;
			if (itu != UnknownWords.end()) { //Exists in UnknownWords

				(*itu).second.push_back(i);
			}
			else {
				b++;
				vector<int> vect(1, i);		//vector with one element
				UnknownWords.insert(itu, pair<string, vector<int>>(line, vect));
			}
		}

	}
	//89 known words read.
	//49 unknown words read.
	cout << a;
	cout << endl << b << endl;
}

// Displays stats of words in KnownWords
void WordStats::DisplayKnownWordStats(){
	// print out the map:
	cout << "Ch  Cnt  Indexes\n";
	for (WordMapIter itr = KnownWords.begin(); itr != KnownWords.end(); ++itr) {
		string ch = (*itr).first;
		vector<int> vect = (*itr).second;
		int cnt = vect.size();
		cout << ch << "\t\t" << setw(5) << "\t" << cnt << "   ";
		for (int i = 0; i<cnt; i++)
			cout << vect[i] << ' ';
		cout << endl;
	}
}

// Displays stats of words in Unknownwords
void WordStats::DisplayUnknownWordStats(){
	// print out the map:
	cout << "Ch  Cnt  Indexes\n";
	for (WordMapIter itr = UnknownWords.begin(); itr != UnknownWords.end(); ++itr) {
		string ch = (*itr).first;
		vector<int> vect = (*itr).second;
		int cnt = vect.size();
		cout << ch << "\t\t" << setw(5) << "\t" << cnt << "   ";
		for (int i = 0; i<cnt; i++)
			cout << vect[i] << ' ';
		cout << endl;
	}
}

// Displays 20 most frequent words in KnownWords
void WordStats::DisplayMostFreqKnownWords(){
}

// Displays 20 most frequent words in UnknownWords
void WordStats::DisplayMostFreqUnknownWords(){
}

// Displays original text from KnownWords & UnknownWords
void WordStats::DisplayOriginalText(){
}

// ============ Private Fns ========================

// add your private fns here...

