#include "ELSystem.h"


ELSystem::ELSystem() // default constructor

{
	// initialize the member variable m_axiom, m_Maxiterat, and m_rules  

	// note that the indices of the character in the m_Abet and the corresponding 
	// replacement production in array m_rules are equal, each rule is initialized 
	// to the corresponding letter itself

	m_len_of_albet = m_Abet.Len();

	m_rules = new string[m_len_of_albet];

	for ( int i=0; i<m_len_of_albet; i++ )
	{
		m_rules[i].append(1, m_Abet.Get(i));

	}

	m_axiom = 'F';

    m_Maxiterat = 0;

}

ELSystem::ELSystem(string a, string r, int o)

{
	if( (!a.empty()) && (!r.empty()) )
	{
		m_axiom     = a;
		m_ruleStr   = r; 
		m_Maxiterat = o;
	}
}

ELSystem::~ELSystem()

{

}


void ELSystem::Update(string a, string r, int o)
{
	if( (!a.empty()) && (!r.empty()) )
	{
		m_axiom     = a;
		m_ruleStr   = r; 
		m_Maxiterat = o;
	}
	
}

int ELSystem::ReportLen()
{
	if( !m_Tree.empty() )
		return m_Tree.length();
	else
		return 0;

}

int ELSystem::Pick()
{

	int comma[6];    // due to six symbols A~F

	int num_of_comma = 0; // number of commas

	// go through the whole m_ruleStr to find how many commas there are
	// and put them into comma[]
    
	int len_rulstr = m_ruleStr.length();

    for ( int pos=0; pos<len_rulstr; pos++ )
	{
		if ( m_ruleStr[pos] == ',' )
		{
			num_of_comma++;
			comma[num_of_comma-1] = pos;
		}
	}

	// split m_ruleStr into rule strings, extract the productions and 
	// put them into m_rules array

	int crt_comma_pos = -1; // current position of symbol ','

	char temp_letter; // 

	int pos_in_alph; // the position of the temp_letter in alphabet

	int crt_equ_pos; // current position of symbol '='
	
    for ( int i=0; i<num_of_comma; i++ )  // note that if num_of_comma is greater than 0, this for loop 
		                                  // will be executed
	{
		temp_letter = m_ruleStr[crt_comma_pos+1];

		crt_comma_pos++;

		crt_equ_pos = m_ruleStr.find('=', crt_comma_pos); // find the position of symbol '=' from current comma's position

        pos_in_alph = m_Abet.Position(temp_letter); 

        // extract the substring from the letter immediately after the current equal mark until the letter before
		// the next comma and put it into the m_rules in the correspanding position 

		m_rules[pos_in_alph] = m_ruleStr.substr(crt_equ_pos+1, comma[i]-crt_equ_pos-1); 
                                                                                        //   

		crt_comma_pos = comma[i];

	}

	// if the number of comma is 0, the above loop will be skipped

	temp_letter = m_ruleStr[crt_comma_pos+1];

    crt_comma_pos++;

	crt_equ_pos = m_ruleStr.find('=', crt_comma_pos);

    pos_in_alph = m_Abet.Position(temp_letter);

    m_rules[pos_in_alph] = m_ruleStr.substr(crt_equ_pos+1, len_rulstr-crt_equ_pos);


	return num_of_comma+1;

}


void ELSystem::Gentree()
{

	m_Tree = m_axiom;

	for ( int iter=0; iter<m_Maxiterat; iter++)
	{

		int len_of_crt_tree = m_Tree.length();

		string buf_Tree;

        for ( int pos=0; pos<len_of_crt_tree; pos++) // go through the whole m_Tree
		{
			char temp_letter = m_Tree[pos];

			int pos_in_alph = m_Abet.Position(temp_letter);
			buf_Tree += m_rules[pos_in_alph];
		}

		m_Tree = buf_Tree;
	}
	  

}