#include "Frame.h"

Frame::Frame()
{

}

Frame::~Frame()
{

}

const FRAMEINFO * Frame::GetFrame(unsigned int num) const
{
	FRAMEMAP::const_iterator pos = FrmMap.find(num);

	if (pos != FrmMap.end()) 
	{               
		return &(pos->second);
	}	    
	else 
	{
		return NULL;
	}
}

void Frame::AddFrame(unsigned int num, FRAMEINFO & fi)
{
	FRAMEINFO temp = fi;
	FrmMap[num]=temp;
}

void Frame::RemoveFrame(unsigned int num)
{
	FrmMap.erase(num);
}

void Frame::UpdateFrmInfo(unsigned int num, FRAMEINFO & fi)
{
	FrmMap[num]=fi;
}

void Frame::FillStateArr(int idx, int *a) const
{
	const static int distance = 34;

	FRAMEMAP::const_iterator pos;
	for(int i=0; i<= distance; i++)
	{
		a[i] = FALSE;
	}
	for(pos=FrmMap.begin();pos!=FrmMap.end();pos++)
	{
		if( ( (pos->first) >= idx)&&( (pos->first) <= idx+distance) )
		{
			a[(pos->first)-idx] = TRUE;
		}
	}

}

void Frame::FillAniArry(int *f, double *l, double *a) const
{
	FRAMEMAP::const_iterator pos;
	FRAMEMAP::const_iterator pos_later;
	FRAMEMAP::const_iterator end;

	end = FrmMap.end(); end--;

	int i;
	for(i=0,pos=FrmMap.begin();pos!=end;i++,pos++)
	{
		pos_later = pos; pos_later++;

		// use the next frame's length ratio minus the current frame's length ratio
		// then devide it by the difference of two frames' index numbers
		// finally, devide it by 100, because it is ratio, should be in percent

		l[i] = (  double( (pos_later->second.len_Ratio) - (pos->second.len_Ratio) )
			     /double( (pos_later->first)            - (pos->first) ) 
			   ) ;
			   

		// use the next frame's angle minus the current frame's angle
		// then devide it by the difference of two frames' index numbers

        a[i] = double( (pos_later->second.angle) - (pos->second.angle) )
			  /double( (pos_later->first)        - (pos->first) );

		// the next frame's index num

		f[i] = pos_later->first;
	}
}

unsigned int Frame::FrsFrmIndex() const
{
	if(!FrmMap.empty())
	{
		return ( FrmMap.begin() )->first;
	}
	else
	{
		return 0;
	}
}

double Frame::FrsFrmAng() const
{
	if(!FrmMap.empty())
	{
		return ( FrmMap.begin() )->second.angle;
	}
	else
	{
		return 0;
	}
}

double Frame::FrsFrmLen() const
{
	if(!FrmMap.empty())
	{
		return ( FrmMap.begin() )->second.len_Ratio;
	}
	else
	{
		return 0;
	}
}

//----------------------debugging functions-------------------------//

void Frame::Show(unsigned int num)
{
	FRAMEINFO frmi;
        
	TCHAR szFormatWH[] = TEXT ("%-04i %-04i %-04i"),              
		  szBufferWH[30];

	FRAMEMAP::const_iterator pos = FrmMap.find(num);

	if (pos != FrmMap.end()) 
	{               
		frmi = pos->second;
	    wsprintf (szBufferWH, szFormatWH, pos->first, (frmi.len_Ratio), (frmi.angle));

		MessageBox (NULL, szBufferWH,
                      TEXT("Frame show"), MB_ICONINFORMATION);	
	}	    
    
}

void Frame::PrintAll()
{
	FRAMEINFO frmi;
	TCHAR szFormatWH[] = TEXT ("%-04i %-04i %-04i"),              
		  szBufferWH[30];

	FRAMEMAP::const_iterator pos;
	for(pos=FrmMap.begin();pos!=FrmMap.end();pos++)
	{
		frmi = pos->second;
	    wsprintf (szBufferWH, szFormatWH, pos->first, (frmi.len_Ratio), (frmi.angle));

		MessageBox (NULL, szBufferWH,
                      TEXT("Frame show"), MB_ICONINFORMATION);	
	}
}