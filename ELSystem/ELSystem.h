



#ifndef ELSYSTEM_H_
#define ELSYSTEM_H_

#include "Alphabet.h"
#include <string>
using namespace std;

class ELSystem

{

private:

	Alphabet m_Abet; // alphabet

	int m_Maxiterat; // number of iterations

	//string m_rules[11]; // A B C D E F G + - [ ], 11 in total

	string * m_rules; // this is a pointer for implementing a dynamic array of rules
	                  // it's size should depend on the length of alphabet m_Abet

	string m_ruleStr;

	string m_axiom; 

	int m_len_of_albet;

	string m_Tree; // the string after subtitution

public:

	ELSystem();
	ELSystem(char *, char *, int);
	~ELSystem();

    string Report() { return m_Tree; } // return m_tree

    void Update(char *, char *, int);  // 

	int Pick(); // split the string of rules into rules which are unique for each letter,
		             // then put them into the rules array ,the return value indicate the number 
					 // of valid rules
    void Gentree(); // apply the replacement rules to generate m_tree

//	bool Validate(); // validate the strings do not contain any other letter or invalid symble and 
	                 // the number of '[' equals to that of ']'

 //   void Filter(); 

	// for testing
	string * ReturnRules() { return m_rules; }

	int ReturnRulesLeng() { return m_Abet.Len(); }

};

#endif