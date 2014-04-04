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
  Fixed by Zhang Lingzhang at 12th Apr
  Revised by ZHANG Lingzhang at 16th Apr
  Revised by ZHANG Lingzhang at 22th Apr
**********************************************/

#ifndef PARAIO_H_
#define PARAIO_H_

#include <windows.h>
#include <cstring>

#include "ELSystem.h"
#include "BezierLine.h"
#include "DrawGraph.h"
#include "Frame.h"    
/*-------------------------------------------------------
This class is only for FILEIO, it copy all the necessary
current values of parameers to itself's memebers, and 
then main function write its object to file in binary format.
-------------------------------------------------------*/

class ParaIO
{

private:

	COLOR m_cA,
		  m_cB, 
		  m_cC, 
		  m_cD, 
		  m_cE, 
		  m_cF;

    POINT m_lA[4], 
		  m_lB[4], 
		  m_lC[4], 
		  m_lD[4], 
		  m_lE[4], 
		  m_lF[4]; 

    int m_order, m_angleL, m_angleR;
    char m_axiom[16];
    char m_rules[62]; 
	char m_name[20];

	unsigned int m_frameIndex[10];

	FRAMEINFO m_frameInfo[10];

	int m_count;

public:
    ParaIO();
    ~ParaIO();
    void CopyFromClass(ELSystem &,DrawGraph &, Frame &, int, int);

	const char * GetNameFromFile();
	void GetNameFromInput(const char *);
	void RecoverFromFile();
	void CopyToClass(ELSystem &, DrawGraph &, Frame &) const;
	const char * ReturnRules() const;
	int ReturnOrder() const;
	int ReturnAngleL() const;
    int ReturnAngleR() const;
	const char * ReturnAxiom() const;
};
#endif