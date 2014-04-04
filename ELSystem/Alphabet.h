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

	string m_al;

public:

	Alphabet(char * ptr="~+-[]ABCDEFGWXYZ") ;
	~Alphabet();
    char Get(int) const;
	int Len() const;
	int Position(char) const;
	string ReturnAlph() const;
};


#endif