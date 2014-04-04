#ifndef FRAME_H_
#define FRAME_H_
#include <windows.h>
#include <algorithm>   
#include <map>   
using namespace std;

typedef struct FRAMEINFOtag
{
    int len_Ratio;      // parameters within this frame
    int angleL;          //
    int angleR;          //
	FRAMEINFOtag()
	{
		len_Ratio = 20;
		angleL = 0;
		angleR = 0;
	}

}
FRAMEINFO;

typedef map<unsigned int,FRAMEINFO> FRAMEMAP;

class ParaIO;
class Frame
{
private:

    FRAMEINFO frminfo;
	FRAMEMAP FrmMap;
	FRAMEMAP::const_iterator curpos;

public:

	friend class ParaIO;

    Frame();
    ~Frame();
    const FRAMEINFO * GetFrame(unsigned int) const;
    void RemoveFrame(unsigned int);
    void AddFrame(unsigned int, FRAMEINFO &);
    void FillStateArr(int, int*) const;
    void UpdateFrmInfo(unsigned int, FRAMEINFO &);

	bool IsMapEmpty() const { return FrmMap.empty();}
	unsigned int MapSize() const {return FrmMap.size();}
	void RemoveALL(){ FrmMap.clear();}
	void FillAniArry(int *, double *, double *, double *) const;

	unsigned int FrsFrmIndex() const; 
	double FrsFrmAngL() const;
	double FrsFrmAngR() const;
	double FrsFrmLen() const;

	unsigned int ReturnMaxIndex() const;

	void PrintAll();
	void Show(unsigned int);
};

#endif
