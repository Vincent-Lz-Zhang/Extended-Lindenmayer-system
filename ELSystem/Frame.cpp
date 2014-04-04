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