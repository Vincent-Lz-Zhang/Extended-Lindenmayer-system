/**********************************************
  CSIT691 Independent Project 
  Extended L-System
  ZHANG Lingzhang 5th Mar 2009 
  Supervisor: Prof. Rossiter
  HKUST
  Revised at 19th Mar by ZHANG Lingzhang
  Revised at 21th Mar by ZHANG Lingzhang
  Revised at 23th Mar by ZHANG Lingzhang
  Revised at 30th Mar by ZHANG Lingzhang
  Fixed by Zhang Lingzhang at 12 Apr
**********************************************/
#ifndef ELSYSTEM_H_
#define ELSYSTEM_H_

#include "Alphabet.h"
#include <string>
using namespace std;
class ParaIO;
class ELSystem

{

private:

	Alphabet m_Abet;       // alphabet

	int m_Maxiterat;       // number of iterations

	string * m_rules;      // this is a pointer for implementing a dynamic array of rules
	                       // it's size should depend on the length of alphabet m_Abet

	string m_ruleStr;      // this is the raw string for rules

	string m_axiom;        // axiom 

	int m_len_of_albet;    // length of Alphabet

	string m_Tree;         // the string after subtitution

public:

	friend class ParaIO;

	ELSystem();                             // default constructor

	ELSystem(string, string, int);          // constructor, set m_axiom, m_ruleStr and m_Maxiterat (namely the order)   

	~ELSystem();                            //

    string Report() { return m_Tree; }      // return m_tree

    void Update(string &, string &, int);   // reset m_axiom, m_ruleStr and m_Maxiterat (namely the order)

	int Pick();                             // split the string of rules into rules which are unique for each letter,
		                                    // then put them into the rules array ,the return value indicate the number 
					                        // of valid rules
    void Gentree();                         // apply the replacement rules to generate m_tree

	void FreshRules();                      // clear the rules

    int ReportLen();                        // return length of m_Tree

	int CountLetter();                      // return number of letters 'A' ~ 'F'
	int CountSymbol();                      // return number of '+' and '-'

	// for testing and debugging only//////////////

	string * ReturnRules() { return m_rules; }     //

	int ReturnRulesLeng() { return m_Abet.Len(); } //
    ////////////////////////////////////////////////
};

#endif