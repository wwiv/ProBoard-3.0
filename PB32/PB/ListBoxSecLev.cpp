// ListBoxSecLev.cpp : implementation file
//

#include "stdafx.h"
#include "PB.h"
#include "ListBoxSecLev.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListBoxSecLev

CListBoxSecLev::CListBoxSecLev()
{
}

CListBoxSecLev::~CListBoxSecLev()
{
}


BEGIN_MESSAGE_MAP(CListBoxSecLev, CListBox)
	//{{AFX_MSG_MAP(CListBoxSecLev)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListBoxSecLev message handlers

void CListBoxSecLev::DrawItem(LPDRAWITEMSTRUCT draw) 
{
   CDC dc;
   CBrush selbrush(GetSysColor(COLOR_HIGHLIGHT));
   CBrush norbrush(GetSysColor(COLOR_WINDOW));
   CPen   selpen  (PS_NULL,0,GetSysColor(COLOR_HIGHLIGHT));

   CBrush *br;

   dc.Attach(draw->hDC);

   if(draw->itemState & ODS_SELECTED)
   {          
      br = &selbrush;

      dc.SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
      dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
   }
   else
   {
      br = &norbrush;

      dc.SetBkColor(GetSysColor(COLOR_WINDOW));
      dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
   }

   CBrush *oldbrush = dc.SelectObject(br);
   CPen   *oldpen   = dc.SelectObject(&selpen);

   dc.Rectangle(&draw->rcItem);
                                      
   if(draw->itemID >= 0 && int(draw->itemID) < GetCount())
   {
      char *s = new char[GetTextLen(draw->itemID)+1];
      
      GetText(draw->itemID,s);

      char *p = strtok(s,"\t");
   
      if(p)
      {
         dc.SetTextAlign(TA_RIGHT);
         dc.TextOut(50,draw->rcItem.top,p);

         p = strtok(NULL,"\t");
      }

      if(p)
      {
         dc.SetTextAlign(TA_LEFT);
         dc.TextOut(60,draw->rcItem.top,p);
      }

      delete [] s;
   }

   dc.SelectObject(oldbrush);

   dc.Detach();
}

void CListBoxSecLev::MeasureItem(LPMEASUREITEMSTRUCT measure) 
{
   //measure->itemHeight = 10;
   
	// TODO: Add your code to determine the size of specified item
	
}
