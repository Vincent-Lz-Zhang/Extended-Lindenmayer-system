#ifndef FRAME_H_
#define FRAME_H_
#include <windows.h>
#include <algorithm>   
#include <map>   
using namespace std;

typedef struct FRAMEINFOtag
{
    int len_Ratio;      // parameters within this frame
    int angle;          //
	FRAMEINFOtag()
	{
		len_Ratio = 20;
		angle = 0;
	}

}
FRAMEINFO;

typedef map<unsigned int,FRAMEINFO> FRAMEMAP;

class Frame
{
private:

    FRAMEINFO frminfo;
	FRAMEMAP FrmMap;
	FRAMEMAP::const_iterator curpos;

public:

    Frame();
    ~Frame();
    const FRAMEINFO * GetFrame(unsigned int) const;
    void RemoveFrame(unsigned int);
    void AddFrame(unsigned int, FRAMEINFO &);
    void FillStateArr(int idx, int *a) const;
    void UpdateFrmInfo(unsigned int, FRAMEINFO &);
	void PrintAll();
	void Show(unsigned int);
	bool IsMapEmpty(){ return FrmMap.empty();}
	int MapSize(){return FrmMap.size();}
	void RemoveALL(){ FrmMap.clear();}

};

#endif
