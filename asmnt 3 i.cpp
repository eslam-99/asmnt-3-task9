#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> sub_words;
void EmbeddedWords (string, string="");
void find_word (string, string="");
string to_lower(string);
void print_vec();

int main()
{
	string word;
	cout << "Enter starting word : ";
	cin >> word;
	word = to_lower(word);
	EmbeddedWords(word);
	sort(sub_words.begin(), sub_words.end()); //sort all subwords
	sub_words.erase(unique(sub_words.begin(), sub_words.end()), sub_words.end()); //remove all dublicated subwords
	cout << "The embedded words are :" << endl;
	print_vec();
	return 0;
}

//recursive function to find all possible subwords
void EmbeddedWords (string word, string rest)
{
	find_word(word, rest);
	if ( word.length() > 2 )
	{
		for ( int i=0 ; i<word.length() ; i++ )
		{
			rest = word[i];
			string next = word; //take a copy
			next = next.erase(i,1); //then remove i element
			EmbeddedWords(next, rest);
		}
	}
	return;
}

//compare all subwords with words in a dictionary
void find_word (string word, string rest)
{
	fstream dict;
	string line;
	bool is_found1 = 0, is_found2 = 0;
	dict.open("dictionary.txt",ios::in); //open dictionary file
	if ( dict.is_open() ) 
	{
		while ( getline(dict,line) ) //read every single word in the dictionary
		{
			if ( word == line && is_found1 == 0)
			{
				sub_words.push_back(word);
				is_found1 = 1;
			}
			if ( rest == line && is_found2 == 0)
			{
				sub_words.push_back(rest);
				is_found2 = 1;
			}
			if ( is_found1 == 1 && is_found2 == 1 )
				break; //stop if the 2 words found
		}
	}
	else
		cout << "No file found.";
	dict.close();
	return;
}

//convert all letters of main word to lower case
string to_lower(string word)
{
	for ( int i=0 ; i<word.length() ; i++ )
	{
		if (word[i]>='A' && word[i]<='Z' )
			word[i]=word[i]+32;
	}
	return word;
}

//print the vector containing valid subwords
void print_vec()
{
	for ( int i=0 ; i<sub_words.size() ; i++ )
	{
		cout << sub_words[i] << endl;
	}
}
