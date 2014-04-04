



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

	string m_rules[11]; // A B C D E F G + - [ ], 11 in total

	string m_ruleStr;

	string m_axiom; 


	string m_Tree; // the string after subtitution

public:

	ELSystem();
	ELSystem(char *, char *, int);
	~ELSystem();

    string Report(); // return m_tree

    void Update(char *, char *, int);  // 

	int Pick(char *); // split the string of rules into rules which is unique for each letter,
		             // then put them into the rules array ,the return value indicate the number 
					 // of valid rules
    void Gentree(); // apply the replacement rules to generate m_tree

	bool Validate(); // validate the strings do not contain any other letter or invalid symble and 
	                 // the number of '[' equals to that of ']'

    void Filter(); 

};

#endif