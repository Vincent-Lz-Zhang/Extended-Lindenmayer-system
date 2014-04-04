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