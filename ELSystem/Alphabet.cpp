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

#include "Alphabet.h"

Alphabet::Alphabet(char * ptr)
{
	m_al = ptr;
}

char Alphabet::Get(int i) const
{
	return m_al.at(i);

}

int Alphabet::Len() const
{
	return m_al.length();
}

int Alphabet::Position(char c) const
{
	return m_al.find(c,0);
}

string Alphabet::ReturnAlph() const
{
	return m_al;
}

Alphabet::~Alphabet()
{

}