
#include "ParaValidator.h"

ParaValidator::ParaValidator(char * aCon,char * rCon,int oCon)
{
	m_axmContl = aCon;

	m_rulContl = rCon;

	m_orderContl = oCon;


}

ParaValidator::~ParaValidator()
{

}

void ParaValidator::Filter()
{
	string strbuf;

	int len_albet = m_albet.Len();
	int len = m_axmContl.length();
    

	// find the first letter in alphabet and assign it to strbuf

	for (int i=0; i<len_axm; i++)
	{
		for (int j=0; j<len_albet; j++)
		{
			if ( m_axmContl[i] == m_albet.Get(j) )

				strbuf = m_axmContl[i];
		}
	}
    
	m_axmContl = strbuf;


    
	len = m_rulContl.length();

    // find the first letter in alphabet and assign it to strbuf

	for (int i=0; i<len_axm; i++)
	{
		for (int j=0; j<len_albet; j++)
		{
			if ( m_axmContl[i] == m_albet.Get(j) )

				strbuf += m_axmContl[i];
		}
	}
    
	m_axmContl = strbuf;




}

bool ParaValidator::IsValid()
{

}

string ParaValidator::ReturnAxm()
{

}

string ParaValidator::ReturnRul()
{

}

int ParaValidator::ReturnOrd()
{

}