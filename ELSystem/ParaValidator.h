

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
    void Filter();
	bool IsValid();
	string ReturnAxm();
	string ReturnRul();
	int ReturnOrd();

};

#endif
