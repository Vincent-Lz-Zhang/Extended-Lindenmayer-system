
#include "ParaIO.h"

ParaIO::ParaIO()
{
}

ParaIO::~ParaIO()
{
}

void ParaIO::CopyFromClass(ELSystem & e,DrawGraph & d, int a)
{	
	if(!e.m_ruleStr.empty())
	{
		strcpy(m_rules, e.m_ruleStr.c_str());
	}

	if(!e.m_axiom.empty())
	{
		m_axiom = e.m_axiom[0];
	}

	m_order = e.m_Maxiterat;
	m_angle = a;

	m_cA.index = d.m_col_A.index;
    m_cA.rgb = d.m_col_A.rgb;

	m_cB.index = d.m_col_B.index;
	m_cB.rgb = d.m_col_B.rgb;

	m_cC.index = d.m_col_C.index;
	m_cC.rgb = d.m_col_C.rgb;

	m_cD.index = d.m_col_D.index;
	m_cD.rgb = d.m_col_D.rgb;

	m_cE.index = d.m_col_E.index;
	m_cE.rgb = d.m_col_E.rgb;

	m_cF.index = d.m_col_F.index;
	m_cF.rgb = d.m_col_F.rgb;

	for(int i=0;i<4;i++)
	{
		m_lA[i].x = d.m_bl_A.m_points[i].x;
		m_lA[i].y = d.m_bl_A.m_points[i].y;

		m_lB[i].x = d.m_bl_B.m_points[i].x;
		m_lB[i].y = d.m_bl_B.m_points[i].y;

		m_lC[i].x = d.m_bl_C.m_points[i].x;
		m_lC[i].y = d.m_bl_C.m_points[i].y;

		m_lD[i].x = d.m_bl_D.m_points[i].x;
		m_lD[i].y = d.m_bl_D.m_points[i].y;

		m_lE[i].x = d.m_bl_E.m_points[i].x;
		m_lE[i].y = d.m_bl_E.m_points[i].y;

		m_lF[i].x = d.m_bl_F.m_points[i].x;
		m_lF[i].y = d.m_bl_F.m_points[i].y;

	}

}
void ParaIO::GetNameFromInput(const char * c)
{
	if(c!=NULL)
	{
		strcpy(m_name, c);
	}
}

const char * ParaIO::GetNameFromFile()
{
	return m_name;
}

	
void ParaIO::CopyToClass(ELSystem & e,DrawGraph & d)
{

	d.m_col_A.index = m_cA.index;
    d.m_col_A.rgb   = m_cA.rgb;

	d.m_col_B.index = m_cB.index;
	d.m_col_B.rgb   = m_cB.rgb;

	d.m_col_C.index = m_cC.index;
	d.m_col_C.rgb   = m_cC.rgb;

	d.m_col_D.index = m_cD.index;
	d.m_col_D.rgb   = m_cD.rgb;

	d.m_col_E.index = m_cE.index;
	d.m_col_E.rgb   = m_cE.rgb;

	d.m_col_F.index = m_cF.index;
	d.m_col_F.rgb   = m_cF.rgb;

	for(int i=0;i<4;i++)
	{
		d.m_bl_A.m_points[i].x = m_lA[i].x;
		d.m_bl_A.m_points[i].y = m_lA[i].y;

		d.m_bl_B.m_points[i].x = m_lB[i].x;
		d.m_bl_B.m_points[i].y = m_lB[i].y;

		d.m_bl_C.m_points[i].x = m_lC[i].x;
		d.m_bl_C.m_points[i].y = m_lC[i].y;

		d.m_bl_D.m_points[i].x = m_lD[i].x;
		d.m_bl_D.m_points[i].y = m_lD[i].y;

		d.m_bl_E.m_points[i].x = m_lE[i].x;
		d.m_bl_E.m_points[i].y = m_lE[i].y;

		d.m_bl_F.m_points[i].x = m_lF[i].x;
		d.m_bl_F.m_points[i].y = m_lF[i].y;

	}

}
	
const char * ParaIO::ReturnRules()
{
	return m_rules;
}

	
int ParaIO::ReturnOrder()
{
	return m_order;
}
	
int ParaIO::ReturnAngle()
{
	return m_angle;
}
	
char ParaIO::ReturnAxiom()
{
	return m_axiom;
}

