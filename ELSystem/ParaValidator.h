

#ifndef PARAVALIDATOR_H_
#define PARAVALIDATOR_H_


#include <string>

using namespace std;

#include <string.h>
#include <stdio.h>

#include "Alphabet.h"

class ParaValidator

{

private:

    string m_albet;         // should be Alphabet plus comma ','

	string m_axmContl;      // get the raw input string for axiom

	string m_rulContl;      // and rules string

	int m_orderContl;

	string m_outputAxm;     // processed string for axiom

	string m_outputRul;     // and rules string

public:

	ParaValidator(char * aCon="F", char * rCon="F=F", int oCon=0);

	~ParaValidator();

	void Update(char *, char *, int);

    void RulStrFilter(); // this function is for making the axiom string and rules string valid,
	                     // if the inputed axiom string is more than one character or contain 
	                     // any character that is not in alphabet or both, it will find the first
	                     // valid letter and assign it to m_axmContl, and the inputed rules string
	                     // is treated in the similar way, all the invalid charachers will be 
	                     // filtered out
	void AxmStrFilter(); //


	bool IsValid(); // firstly, it check that the filtered m_axmContl and m_rulContl are not
	                // null, 
	                // secondly, it check that the m_rulContl string contains '[' and ']'
	                // equally and there is a symbol '=' before each comma ',',
                    // and then, it check the axiom(m_axmContl) appear in the rules(m_axmContl)
                    // and then, it check m_orderContl is not less than 0;
	                // in any above case, the return value should be false

	                // well, sill need many more checks to make this program robust

	string ReturnAxm() { return m_outputAxm; } // return m_axmContl
	string ReturnRul() { return m_outputRul; } // return m_axmContl
	int ReturnOrd() { return m_orderContl;}    // return m_orderContl

};

#endif
