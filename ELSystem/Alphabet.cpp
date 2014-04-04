#include "Alphabet.h"



Alphabet::Alphabet(char * ptr)
{
	m_al = ptr;
}

char Alphabet::Get(int i)
{
	return m_al.at(i);

}

int Alphabet::Len()
{
	return m_al.length();
}

int Alphabet::Position(char c)
{
	return m_al.find(c,0);
}

string Alphabet::ReturnAlph()
{
	return m_al;
}

Alphabet::~Alphabet()
{

}