/**********************************************************************
 * main.cpp - CSCI251/851 - Ass4 - main() driver for text word stats program
 * <Your name> <your login> <date last modified>
 **********************************************************************/
 
#include <iostream>
#include "wordstats.h"
using namespace std;

char Menu();

int main(){
   WordStats ws;
   cout << "Welcome to the Text File Analyser\n\n";
   ws.ReadDictionary();
   for(;;){
      switch(Menu()){
         case '1': ws.ReadDictionary();      break;
         case '2': ws.DisplayDictionary();      break;
         case '3': ws.ReadTxtFile();      break;
         case '4': ws.DisplayKnownWordStats();   break;
         case '5': ws.DisplayUnknownWordStats();   break;
         case '6': ws.DisplayMostFreqKnownWords(); break;
         case '7': ws.DisplayMostFreqUnknownWords(); break;
         case '8': ws.DisplayOriginalText(); break;
         case 'q': cout << "Thanks for using Text File Word Counter\n";
                   return(0);
         default: cout << "Invalid command!\n";
      }
   }
   return 0;
}


char Menu(){
	char Cmd[20];
	cout << endl;
	cout << "(1) Read dictionary\n";
	cout << "(2) Display dictionary\n";
	cout << "(3) Read text file\n";
	cout << "(4) Display known word stats\n";
	cout << "(5) Display unknown word stats\n";
	cout << "(6) Display most frequent known words\n";
	cout << "(7) Display most freqequent unknown words\n";
	cout << "(8) Display original text\n";
	cout << "(q) Quit\n";
	cout << "Command > ";
	cin.getline(Cmd,20);
	cout<<endl;
	return Cmd[0];
}

