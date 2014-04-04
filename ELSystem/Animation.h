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
  Revised by ZHANG Lingzhang at 16th Apr 
**********************************************/

/***********************************************************************************
Basicly, this class is just a animation
version of DrawGraph class, so it is a friend class of DrawGraph, then we don't 
need two copies of color informations or Bezier line informations, it just accass
DraeGraph's
***********************************************************************************/

#ifndef ANIMATION_H_
#define ANIMATION_H_

#define ANI_STEP 50  // due to the control windows' size in Bezier line panel

#include "DrawGraph.h"

class Animation
{

private:

	STATE m_pst;
	
	stack<STATE> m_sta_stat;  // stack of current states

public:

	Animation();
	~Animation();
	void DrawAni(HWND, double, double, DrawGraph &);
	void ClearState();
};

#endif