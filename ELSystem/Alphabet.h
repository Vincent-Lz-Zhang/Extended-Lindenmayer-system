/////////////
// it is not necessary to make alphabet a class so far,
//however, it may be extended later, so I make it as a
// class, with respect of scalability

#ifndef ALPHABET_H_
#define ALPHABET_H_

#include <string>
using namespace std;

class Alphabet

{

private:

	string al;

public:

	Alphabet(char * ptr="+-[]ABCDEFG") ;
	~Alphabet();
    char Get(int);
	int Len();

};


#endif