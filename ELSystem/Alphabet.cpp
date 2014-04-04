#include "Alphabet.h"



Alphabet::Alphabet(char * ptr)
{
	al = ptr;
}

char Alphabet::Get(int i)
{
	return al.at(i);

}

int Alphabet::Len()
{
	return al.length();
}

int Alphabet::Position(char c)
{
	return al.find(c,0);
}


Alphabet::~Alphabet()
{
}