

#ifndef PARAVALIDATOR_H_
#define PARAVALIDATOR_H_


#include <string>

using namespace std;

#include "Alphabet.h"

class ParaValidator

{

private:

    Alphabet m_albet;

	string m_axmContl;

	string m_rulContl;

	int m_orderContl;


public:

	ParaValidator(char *,char *,int);
	~ParaValidator();

    void Filter();// this function is for making the axiom string and rules string valid,
	              // if the inputed axiom string is more than one character or contain 
	              // any character that is not in alphabet or both, it will find the first
	              // valid letter and assign it to m_axmContl, and the inputed rules string
	              // is treated in the similar way, all the invalid charachers will be 
	              // filtered out

	bool IsValid(); // firstly, it check that the filtered m_axmContl and m_rulContl are not
	                // null, 
	                // secondly, it check that the m_rulContl string contains '[' and ']'
	                // equally and there is a symbol '=' before each comma ',',
                    // and then, it check the axiom(m_axmContl) appear in the rules(m_axmContl)
                    // and then, it check m_orderContl is not less than 0;
	                // in any above case, the return value should be false

	                // well, sill need many more checks to make this program robust

	string ReturnAxm() { return m_axmContl; } // return m_axmContl
	string ReturnRul() { return m_rulContl; } // return m_axmContl
	int ReturnOrd() { return m_orderContl;}  // return m_orderContl

};

#endif
