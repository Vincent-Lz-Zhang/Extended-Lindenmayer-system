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

Alphabet::~Alphabet()
{
}