//////////////////////////////////////////////////////////////////////////////////////////////
/// thesw functions are only for debugging purpose////////////////////////////////////////
#include <windows.h>

void g_PrintPoints(POINT* pts, LPCTSTR lpTitle)
{

        TCHAR szFormatpts[] = TEXT ("%-04i %-04i %-04i %-04i %-04i %-04i %-04i %-04i"),
              szBufferpts[50];

        wsprintf (szBufferpts, szFormatpts, pts[0].x, pts[0].y,
                                            pts[1].x, pts[1].y,
									        pts[2].x, pts[2].y,
								        	pts[3].x, pts[3].y);
		MessageBox (NULL, szBufferpts,
                      lpTitle, MB_ICONINFORMATION);

}

void g_PrintRect(RECT & f_rect, LPCTSTR lpTitle)
{

        TCHAR szFormatrec[] = TEXT ("%-04i %-04i %-04i %-04i"),
              szBufferrec[30];

        wsprintf (szBufferrec, szFormatrec, f_rect.top,    f_rect.left,
			                                f_rect.bottom, f_rect.right);

		MessageBox (NULL, szBufferrec,
                      lpTitle, MB_ICONINFORMATION);

}

void g_PrintWH(int Width, int Height, LPCTSTR lpTitle)
{

        TCHAR szFormatWH[] = TEXT ("%-04i %-04i"),
              szBufferWH[30];

        wsprintf (szBufferWH, szFormatWH, Width, Height);

		MessageBox (NULL, szBufferWH,
                      lpTitle, MB_ICONINFORMATION);

}

//////////////////////////////////////////////////////////////////////////////////////////////