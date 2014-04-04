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

#include "ParaValidator.h"

ParaValidator::ParaValidator(char * aCon, char * rCon, int oCon)
{
	Alphabet temp_alp;

	m_albet = temp_alp.ReturnAlph() + ',' + '=';

	m_axmContl = aCon;

	m_rulContl = rCon;

	m_orderContl = oCon;
}

ParaValidator::~ParaValidator()
{

}



void ParaValidator::Update(char * aCon, char * rCon, int oCon)
{
	if( aCon!=NULL && rCon!=NULL)
	{	
		m_axmContl = aCon;
	
		m_rulContl = rCon;
	
		m_orderContl = oCon;
	}

}


void ParaValidator::AxmStrFilter()

{

	if( !m_rulContl.empty() )
	{
		Alphabet temp_alp;
		string alph_temp = temp_alp.ReturnAlph();

		string strbuf = _strupr(_strdup(m_axmContl.c_str()));

		if (strbuf.find_first_not_of(alph_temp, 0)==-1)  // there is no invalid symbol
	
		{
		
			m_outputAxm = strbuf;
	
		}

		
		else // // there are invalid symbol exiting
	
		{		
			int start = 0, end = 0;
		
			while( (end=strbuf.find_first_not_of(alph_temp, start)) != -1 )  // found if there are any letter out of alphabet
                                                                       // if there is, then go into the loop
	
			{
		
				string tempStr(&strbuf[start], &strbuf[end]);

				m_outputAxm.append(tempStr);

				start = end+1;
	
	
			}  // end while

		
			end = strbuf.length();

		
			string tempStr(&strbuf[start], &strbuf[end]);

	
			m_outputAxm.append(tempStr);

    
		}  // end else
		
	} // end if

}


void ParaValidator::RulStrFilter()
{

	if ( !m_rulContl.empty() )
	{
	
		// toggle all the lower case letter to upper case letter
	    // note that the m_rulContl should be changed

		string strbuf = _strupr(_strdup(m_rulContl.c_str()));
			
		if (strbuf.find_first_not_of(m_albet, 0)==-1)  // there is no invalid symbol
	
		{
		
			m_outputRul = strbuf;
	
		}

		
		else // // there are invalid symbol exiting
	
		{		
			int start = 0, end = 0;
		
			while( (end=strbuf.find_first_not_of(m_albet, start)) != -1 )  // found if there are any letter out of alphabet
                                                                       // if there is, then go into the loop
	
			{
		
				string tempStr(&strbuf[start], &strbuf[end]);

				m_outputRul.append(tempStr);

				start = end+1;
	
	
			}  // end while

		
			end = strbuf.length();

		
			string tempStr(&strbuf[start], &strbuf[end]);

	
			m_outputRul.append(tempStr);

    
		}  // end else

	} // end the first if

}

bool ParaValidator::IsValid()
{
	bool f = true;
	return f; 
}


