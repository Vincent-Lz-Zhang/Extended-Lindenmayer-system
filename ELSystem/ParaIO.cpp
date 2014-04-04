
#include "ParaIO.h"

ParaIO::ParaIO()
{
}

ParaIO::~ParaIO()
{
}

void ParaIO::CopyFromClass(ELSystem & e,DrawGraph & d, Frame & f, int l, int r)
{	
	if(!e.m_ruleStr.empty())
	{
		strcpy(m_rules, e.m_ruleStr.c_str());
	}

	if(!e.m_axiom.empty())
	{
		strcpy(m_axiom, e.m_axiom.c_str());
	}

	m_order = e.m_Maxiterat;
	m_angleL = l;
	m_angleR = r;

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


	if( !f.FrmMap.empty() )
	{
		m_count = min( f.FrmMap.size(), 10 );
		FRAMEMAP::const_iterator pos;
	    int i;
		for(i=0,pos=f.FrmMap.begin();i<m_count;pos++,i++)
	
		{
			m_frameIndex[i] = pos->first;
		    m_frameInfo[i].len_Ratio  = pos->second.len_Ratio;
			m_frameInfo[i].angleL = pos->second.angleL;
			m_frameInfo[i].angleR = pos->second.angleR;
		}
	
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

	
void ParaIO::CopyToClass(ELSystem & e,DrawGraph & d, Frame & f) const
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

	// clear frame information firstly, before fill in the data
	if( !f.FrmMap.empty() )
	{
		f.FrmMap.clear();
	}

	if(m_count!=0)
	{
		for(int i=0; i<m_count; i++)
		{
			FRAMEINFO temp = m_frameInfo[i];
			f.FrmMap[(m_frameIndex[i])] = temp;
		}
	}

}
	
const char * ParaIO::ReturnRules() const
{
	return m_rules;
}

	
int ParaIO::ReturnOrder() const
{
	return m_order;
}
	
int ParaIO::ReturnAngleL() const
{
	return m_angleL;
}

int ParaIO::ReturnAngleR() const
{
	return m_angleR;
}
	
const char * ParaIO::ReturnAxiom() const
{
	return m_axiom;
}

