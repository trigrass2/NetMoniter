/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.24                          *
*        Compiled Jan 27 2014, 11:28:24                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include <UCOS_II.h>
#include "Config.h"
#include "MainTask.h"
#include "Setting.h"
#include "sysConf.h"
#include "GUI_ARRAY.h"
#include <stdlib.h>
#include <string.h>
#include "HEADER.h"
#include "WIDGET.h"
#include "SCROLLBAR.h"
#include "WM_Intern.h"
#include "dlg.h"
#include "skinColor.h"
#include "str.h"
#include "28.h"


#define LV_PAGE_SIZE  9

/*--- external variables ---*/
extern SIMP_BERTH SimpBerthes[BOAT_NUM_MAX];
extern int N_boat;

unsigned char isSub2Inited  = 0;

/*--- local functions ---*/
static void updateListViewContent(WM_HWIN thisHandle);
static void LV_turnPage(WM_HWIN thisListView, int page);
static void myListViewListener(WM_MESSAGE* pMsg);


/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0     (GUI_ID_USER + 0x00)
#define ID_LISTVIEW_0   (GUI_ID_USER + 0x01)

#define ID_TEXT_0     (GUI_ID_USER + 0x02)
#define ID_TEXT_1     (GUI_ID_USER + 0x03)
#define ID_TEXT_2     (GUI_ID_USER + 0x04)
#define ID_TEXT_3     (GUI_ID_USER + 0x05)
#define ID_TEXT_4     (GUI_ID_USER + 0x06)
#define ID_TEXT_5     (GUI_ID_USER + 0x07)
#define ID_TEXT_6     (GUI_ID_USER + 0x08)
#define ID_TEXT_7     (GUI_ID_USER + 0x09)
#define ID_TEXT_8     (GUI_ID_USER + 0x0a)



/*---------------- static variables ----------------------------*/
 ///模块变量
static int         LV_Page              = 0;

static long        MMSI                 = 0;

static const GUI_RECT infoRect  =   {LV_AllList_WIDTH+10,LV_AllList_Y,Win_Main_WIDTH-MenuLabel_WIDTH,LV_AllList_HEIGHT+40};
static const GUI_RECT lvIndicate  = {LV_AllList_WIDTH-200,LV_AllList_Y-40,Win_Main_WIDTH-MenuLabel_WIDTH,480};
static const GUI_RECT lvRect   =    {0,LV_AllList_Y,LV_AllList_WIDTH,LV_AllList_HEIGHT};

static const LVWin_COLOR * pSkin  = &lvWinSkins[0];

MENU_Handle hObj;


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect,   "Window",          ID_WINDOW_0,   SubWin_X,         SubWin_Y,        SubWin_WIDTH, SubWin_HEIGHT, 0, 0x0, 0},
  { LISTVIEW_CreateIndirect, "Listview",        ID_LISTVIEW_0, LV_AllList_X,     LV_AllList_Y,    LV_AllList_WIDTH, LV_AllList_HEIGHT, 0, 0x0, 0 },
	
	{ TEXT_CreateIndirect,     "AIS船舶列表",     ID_TEXT_0,     100,     LV_AllList_Y-30,  200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "当前船舶信息",    ID_TEXT_1,     LV_MoniteList_WIDTH+100, LV_AllList_Y-30,  200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "船名:",            ID_TEXT_2,     LV_AllList_WIDTH+20, LV_AllList_Y+40,  200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "北纬:",            ID_TEXT_3,     LV_AllList_WIDTH+20, LV_AllList_Y+80,  200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "东经:",            ID_TEXT_4,     LV_AllList_WIDTH+20, LV_AllList_Y+120, 200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "航速:",            ID_TEXT_5,     LV_AllList_WIDTH+20, LV_AllList_Y+160, 200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "航向:",            ID_TEXT_6,     LV_AllList_WIDTH+20, LV_AllList_Y+200, 200,  30, 0, 0x0, 0}
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/




// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;

  int     SelectedRow  = -1;
  long    SelectedMMSI = 0;
  int     i;
 
  switch (pMsg->MsgId) {	
  case USER_MSG_LV_UPDATE:
       updateListViewContent(WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0));      
       break;
  
  case USER_MSG_SKIN: 
       pSkin  = &(lvWinSkins[pMsg->Data.v]);
       
       WINDOW_SetBkColor(pMsg->hWin,pSkin->bkColor);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
       TEXT_SetTextColor(hItem, pSkin->ttl_Text);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
       TEXT_SetTextColor(hItem, pSkin->ttl_Text);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
       TEXT_SetTextColor(hItem, pSkin->inf_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
       TEXT_SetTextColor(hItem, pSkin->inf_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
       TEXT_SetTextColor(hItem, pSkin->inf_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
       TEXT_SetTextColor(hItem, pSkin->inf_Label);       
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
       TEXT_SetTextColor(hItem, pSkin->inf_Label);
       
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
       LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_UNSEL, pSkin->itm_bkUnsel);
       LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_SEL,   pSkin->itm_bkSel);
       LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_SELFOCUS, pSkin->itm_bkFocus);
       
       LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_UNSEL, pSkin->itm_txUnsel);
       LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_SEL,   pSkin->itm_txSel);
       LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_SELFOCUS, pSkin->itm_txFocus);
       
       hItem  = LISTVIEW_GetHeader(hItem);
       HEADER_SetBkColor(hItem,pSkin->Header_Bk);
       HEADER_SetTextColor(hItem,pSkin->Header_Text);
       break; 
  
  case WM_INIT_DIALOG:
       pSkin  = &(lvWinSkins[SysConf.Skin]);

       hItem = pMsg->hWin;
       WINDOW_SetBkColor(hItem, pSkin->bkColor);

       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
       TEXT_SetTextColor(hItem, pSkin->ttl_Text);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
       TEXT_SetTextColor(hItem, pSkin->ttl_Text);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
       TEXT_SetTextColor(hItem, pSkin->inf_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
       TEXT_SetTextColor(hItem, pSkin->inf_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
       TEXT_SetTextColor(hItem, pSkin->inf_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
       TEXT_SetTextColor(hItem, pSkin->inf_Label);       
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
       TEXT_SetTextColor(hItem, pSkin->inf_Label);  

       hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
       WM_SetCallback(hItem, &myListViewListener);
      
       LISTVIEW_AddColumn(hItem, LV_AllList_Col_0_WIDTH, "距离", GUI_TA_HCENTER | GUI_TA_VCENTER);
       LISTVIEW_AddColumn(hItem, LV_AllList_Col_2_WIDTH, "MMSI", GUI_TA_HCENTER | GUI_TA_VCENTER);
       LISTVIEW_AddColumn(hItem, LV_AllList_Col_3_WIDTH, "State", GUI_TA_HCENTER | GUI_TA_VCENTER);	
       LISTVIEW_AddRow(hItem, NULL);
       LISTVIEW_SetGridVis(hItem, 1);
       LISTVIEW_SetHeaderHeight(hItem,LV_MoniteList_Header_HEIGHT);
       LISTVIEW_SetRowHeight(hItem,LV_MoniteList_Row_HEIGHT);
       LISTVIEW_SetFont(hItem,&GUI_Font30);
       LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_UNSEL, pSkin->itm_bkUnsel);
       LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_SEL,   pSkin->itm_bkSel);
       LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_SELFOCUS, pSkin->itm_bkFocus);
       
       LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_UNSEL, pSkin->itm_txUnsel);
       LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_SEL,   pSkin->itm_txSel);
       LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_SELFOCUS, pSkin->itm_txFocus);
       
       for(i=LV_PAGE_SIZE; i>0; i--)
       {
          LISTVIEW_AddRow(hItem, NULL);       
       }
       
       LISTVIEW_SetSel(hItem, 0);
       
       hItem  = LISTVIEW_GetHeader(hItem);
       HEADER_SetBkColor(hItem,pSkin->Header_Bk);
       HEADER_SetTextColor(hItem,pSkin->Header_Text);
       
       isSub2Inited  = 1;
       break;
         
		
  case WM_PAINT:
       GUI_SetColor(pSkin->inf_bkColor);
       GUI_FillRectEx(&infoRect);

       GUI_SetFont(&GUI_Font24_1);
       GUI_SetColor(pSkin->inf_txColor);
       
       if( N_boat <= 0 )
          break;  
          
       GUI_SetTextMode(GUI_TM_TRANS);
           
       SelectedRow  = LISTVIEW_GetSel(WM_GetDialogItem(pMsg->hWin,ID_LISTVIEW_0)); 
            
       LISTVIEW_GetItemText(WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0),  LV_AllList_Col_MMSI, SelectedRow, pStrBuf, 11);
       SelectedMMSI  = strtoi(pStrBuf);     
       if(SelectedMMSI <= 0)
       {
          sprintf(pStrBuf,"%3d/%3d",0, N_boat);
          GUI_DispStringAt(pStrBuf,LV_AllList_WIDTH-80,LV_AllList_Y-20);    
          break;          
       }         
       
       for(i=0; i<N_boat ; i++)   
       {
          if(SimpBerthes[i].pBerth->Boat.user_id == SelectedMMSI)
          {
             break;
          }
       }
       if(i<N_boat)
       {
          sprintf(pStrBuf,"%3d/%3d", i+1 ,N_boat);

          GUI_DispStringAt(pStrBuf,LV_AllList_WIDTH-80,LV_AllList_Y-20);
         
          GUI_DispStringAt(SimpBerthes[i].pBerth->Boat.name,LV_AllList_WIDTH+80,85);       
         
          lltostr(SimpBerthes[i].latitude,pStrBuf);    
          GUI_DispStringAt(pStrBuf,LV_AllList_WIDTH+80,125);
          
          lltostr(SimpBerthes[i].longitude,pStrBuf);  
          GUI_DispStringAt(pStrBuf,LV_AllList_WIDTH+80,165);
          
          if(SysConf.Unit == UNIT_km)
          {
             int sog  = SimpBerthes[i].pBerth->Boat.SOG *18;
             sprintf(pStrBuf, "%3d.%02dkm",sog/100, sog%100);
          }
          else 
          {
             sprintf(pStrBuf, "%2d.%dkt", SimpBerthes[i].pBerth->Boat.SOG/10,
                                          SimpBerthes[i].pBerth->Boat.SOG%10);
          }
          GUI_DispStringAt(pStrBuf, LV_AllList_WIDTH+80,205);
                  
          sprintf(pStrBuf, "%3d", SimpBerthes[i].pBerth->Boat.COG/10);
          pStrBuf[3]  = 194;
          pStrBuf[4]  = 176;
          pStrBuf[5]  = '\0';
          GUI_DispStringAt(pStrBuf,LV_AllList_WIDTH+80,245); 
       }      
       break;		
       
  default:
       WM_DefaultProc(pMsg);
       break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN sub2WinCreate(void) {
  WM_HWIN hWin;
	

//  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, menuWin, 0, 0);
  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END


static void myListViewListener(WM_MESSAGE* pMsg)
{
	const WM_KEY_INFO* pInfo;
	WM_HWIN thisListView  = pMsg->hWin;
 
 WM_MESSAGE myMsg;
 
 int selectedRow  = -1;
 long selectedMMSI  = 0;
	int i  = 0;
 Bool isAdded  = FALSE;
	switch(pMsg->MsgId)
	{  
    case WM_SET_FOCUS:
         if(pMsg->Data.v)
         {
            LV_Page  = 0;
            LV_turnPage(thisListView, LV_Page);
            LISTVIEW_SetSel(thisListView, 0);
            WM_InvalidateRect(subWins[2], &lvIndicate); 
         }
         LISTVIEW_Callback(pMsg);
         break;
    case WM_KEY:
			 pInfo  = (WM_KEY_INFO*)pMsg->Data.p; 
		  switch(pInfo->Key)
		 	{            
				   case GUI_KEY_UP:
            selectedRow  = LISTVIEW_GetSel(thisListView);
            if(selectedRow == 0)
            {
               if(LV_Page)
               {
                  LV_Page--;
                  LV_turnPage(thisListView, LV_Page);   
                  LISTVIEW_SetSel(thisListView, LV_PAGE_SIZE-1);               
               }
            }
            else
            {
               LISTVIEW_SetSel(thisListView, selectedRow-1);
            }
            WM_InvalidateRect(subWins[2],&lvRect);
            WM_InvalidateRect(subWins[2],&lvIndicate);          
            break;
         
		 		case GUI_KEY_DOWN:
				      selectedRow  = LISTVIEW_GetSel(thisListView);       
          if(selectedRow == LV_PAGE_SIZE-1)
          {
             if(LV_Page < (N_boat-1)/LV_PAGE_SIZE)
             {
               LV_Page++;
               LV_turnPage(thisListView, LV_Page);
               LISTVIEW_SetSel(thisListView, 0);
             }
          }
          else if(LV_Page*LV_PAGE_SIZE+selectedRow+1 < N_boat)
          {
             LISTVIEW_SetSel(thisListView, selectedRow+1);
          }
          WM_InvalidateRect(subWins[2],&lvRect);
          WM_InvalidateRect(subWins[2],&lvIndicate);          
          break;
				
    case GUI_KEY_RIGHT:
         if(LV_Page < (N_boat-1)/LV_PAGE_SIZE)
         {
           LV_Page++;
           LV_turnPage(thisListView, LV_Page);
           LISTVIEW_SetSel(thisListView, 0);
         }
         WM_InvalidateRect(subWins[2],&lvRect);
         WM_InvalidateRect(subWins[2],&lvIndicate);          
         break;
         
    case GUI_KEY_LEFT:
         if(LV_Page > 0)
         {
            LV_Page--;
            LV_turnPage(thisListView, LV_Page);
            LISTVIEW_SetSel(thisListView, 0);
         }
         WM_InvalidateRect(subWins[2],&lvRect);
         WM_InvalidateRect(subWins[2],&lvIndicate);          
         break;
    
				case GUI_KEY_BACKSPACE:             
         for(i=N_boat-1;i>=0;i--) 
         {
            if(MNTState_Choosen == SimpBerthes[i].pBerth->mntState)
            {     
               isAdded  = MNT_add(SimpBerthes[i].pBerth);
               if( isAdded )
               {         
                  SimpBerthes[i].pBerth->mntState  = MNTState_Monitored ;   
               }
               else
               {
                  break;
               }
            }            
         }
         myMsg.hWin  = WM_GetClientWindow(menuWin);
         myMsg.MsgId  = USER_MSG_DFULT_CNT;
         myMsg.Data.v  = MNT_getDefaultNum(); 
//INFO("default num:%d",myMsg.Data.v);   
         WM_SendMessage(myMsg.hWin, &myMsg);      
         WM_SetFocus(menuWin);
         break;
         
    case GUI_KEY_MONITORING:
         selectedRow  = LISTVIEW_GetSel(thisListView);
         
         LISTVIEW_GetItemText(thisListView, LV_AllList_Col_MMSI, selectedRow, pStrBuf, 11);
         selectedMMSI  = strtoi(pStrBuf);
         
         if(selectedMMSI <= 0)
            break;
         
         for(i=N_boat;i>0;i--)
         {
     
            if(SimpBerthes[i-1].pBerth->Boat.user_id == selectedMMSI)
            {          
               break;
            }
         }
         
         if(i)
            i--;
         else
         {
            INFO("Err!");
            break;
         }
              
         if(SimpBerthes[i].pBerth->mntState == MNTState_None)     
         {
            SimpBerthes[i].pBerth->mntState  = MNTState_Choosen;
            LISTVIEW_SetItemText(thisListView, LV_AllList_Col_STT, selectedRow, "吖");
         }
         break;
         
    case GUI_KEY_CANCEL:
         selectedRow  = LISTVIEW_GetSel(thisListView);
         
         LISTVIEW_GetItemText(thisListView, LV_AllList_Col_MMSI, selectedRow, pStrBuf, 11);
         selectedMMSI  = strtoi(pStrBuf);
         
         if(selectedMMSI <= 0)
            break;
         
         for(i=N_boat;i>0;i--)
         {
            if(SimpBerthes[i-1].pBerth->Boat.user_id == selectedMMSI)
            {          
               break;
            }
         }
         
         if(i)
            i--;
         else 
         {
            INFO("Err!");
            break;
         }

         if(MNTState_Choosen  == SimpBerthes[i].pBerth->mntState)
         {
     
            SimpBerthes[i].pBerth->mntState  = MNTState_None;
            LISTVIEW_SetItemText(thisListView, LV_AllList_Col_STT, selectedRow, "啊");
         }
         
         else if(MNTState_Monitored  <= SimpBerthes[i].pBerth->mntState)
         {  
            MMSI  = SimpBerthes[i].pBerth->Boat.user_id;
            myMsg.hWin     = WM_GetClientWindow(confirmWin);
            myMsg.hWinSrc  = thisListView;
            myMsg.MsgId    = USER_MSG_CHOOSE;
            myMsg.Data.v   = CANCEL_MONITED;
            WM_SendMessage(myMsg.hWin, &myMsg); 
           	WM_BringToTop(confirmWin);
				        WM_SetFocus(WM_GetDialogItem (confirmWin,GUI_ID_BUTTON0));  
         }               
         break;    
     
    case GUI_KEY_ENTER:
         selectedRow  = LISTVIEW_GetSel(thisListView);
        
         LISTVIEW_GetItemText(thisListView, LV_AllList_Col_MMSI, selectedRow, pStrBuf, 11);
         selectedMMSI  = strtoi(pStrBuf);
         
         if(selectedMMSI <= 0)
            break;
            
         for(i=N_boat-1;i>=0;i--)
         {
     
            if(SimpBerthes[i].pBerth->Boat.user_id == selectedMMSI)
            {          
               break;
            }
         }
                 
         
         if(MNTState_None == SimpBerthes[i].pBerth->mntState)
         {
       
            SimpBerthes[i].pBerth->mntState  = MNTState_Choosen;
            LISTVIEW_SetItemText(thisListView, LV_AllList_Col_STT, selectedRow, "吖");
         }
         else if(MNTState_Choosen  == SimpBerthes[i].pBerth->mntState)
         {
     
            SimpBerthes[i].pBerth->mntState  = MNTState_None;
            LISTVIEW_SetItemText(thisListView, LV_AllList_Col_STT, selectedRow, "啊");
         }
         
         else if(MNTState_Monitored  == SimpBerthes[i].pBerth->mntState)
         {  
            MMSI  = SimpBerthes[i].pBerth->Boat.user_id;
            myMsg.hWin     = WM_GetClientWindow(confirmWin);
            myMsg.hWinSrc  = thisListView;
            myMsg.MsgId    = USER_MSG_CHOOSE;
            myMsg.Data.v   = CANCEL_MONITED;
            WM_SendMessage(myMsg.hWin, &myMsg); 
           	WM_BringToTop(confirmWin);
				        WM_SetFocus(WM_GetDialogItem (confirmWin,GUI_ID_BUTTON0));  
         }
         break;

         
				default:
      LISTVIEW_Callback(pMsg);
      break;
			}
			break;
			
   case USER_MSG_REPLY:
       switch(pMsg->Data.v)
       {
          case REPLY_OK:
               LISTVIEW_SetItemText(thisListView, LV_AllList_Col_STT, LISTVIEW_GetSel(thisListView), "啊");
               if(MNT_removeById(MMSI))
               {
                  for(i=N_boat-1;i>=0;i--)
                  {
                     if(SimpBerthes[i].pBerth->Boat.user_id == MMSI)
                     {
                        SimpBerthes[i].pBerth->mntState  = MNTState_None;
                        break;
                     }
                  }
                                 
                 WM_SetFocus(subWins[2]);
               }
               else 
               {
INFO("Error!"); 
                  WM_SetFocus(menuWin);                
               }
               break;
          case REPLY_CANCEL:         
               WM_SetFocus(pMsg->hWin);
               break;
               
           default:
INFO("Something err!");           
           break;
       }
  break;

				default:
					LISTVIEW_Callback(pMsg);
					break;
	}
}


static void LV_turnPage(WM_HWIN thisListView, int page)
{
   int viewNumRows  = 0;
   int orgIndex     = 0;
   int i            = 0;
   
   if( (N_boat-1)/LV_PAGE_SIZE == page)
   {
      viewNumRows  = (N_boat-1) % LV_PAGE_SIZE + 1;
   }
   else
   {
      viewNumRows  = LV_PAGE_SIZE;
   }
   
   orgIndex  = page * LV_PAGE_SIZE;
   
   for(i=0; i<viewNumRows; i++)
   {
      disttostr(pStrBuf, SimpBerthes[orgIndex+i].Dist);
      LISTVIEW_SetItemText(thisListView, LV_AllList_Col_DIST,  i, pStrBuf);
      
      sprintf(pStrBuf, "%09ld", SimpBerthes[orgIndex+i].pBerth->Boat.user_id);
      LISTVIEW_SetItemText(thisListView, LV_AllList_Col_MMSI,  i, pStrBuf);
      
      if(MNTState_None == SimpBerthes[orgIndex+i].pBerth->mntState)
      {
         LISTVIEW_SetItemText(thisListView, LV_AllList_Col_STT, i, "啊");
      }
      else
      {
         LISTVIEW_SetItemText(thisListView, LV_AllList_Col_STT, i, "吖");
      }      
   }
   
   for(; i<LV_PAGE_SIZE; i++)
   {
      LISTVIEW_SetItemText(thisListView, LV_AllList_Col_DIST, i, "");
      LISTVIEW_SetItemText(thisListView, LV_AllList_Col_MMSI, i, "");
      LISTVIEW_SetItemText(thisListView, LV_AllList_Col_STT,  i, "");
   }
}


static void updateListViewContent(WM_HWIN thisHandle)
{
   WM_HWIN thisListView  = thisHandle;
   int  i             = 0;
   int  selRow        = -1;
   long selectedMMSI  = 0;
   
   if(N_boat <= 0)
   {
      return ;
   } 
   selRow  = LISTVIEW_GetSel(thisListView);  
   LISTVIEW_GetItemText(thisListView, LV_AllList_Col_MMSI, selRow, pStrBuf, 11); 
   selectedMMSI  = strtoi(pStrBuf);  
   if(selectedMMSI)
   {
      for(i=N_boat; i>=0; i--)
      {
         if(SimpBerthes[i].pBerth->Boat.user_id == selectedMMSI)
         {
            LV_Page  = i/LV_PAGE_SIZE;
            selRow  = i%LV_PAGE_SIZE;
            break;
         }
      }
   }
   else 
   {
      LV_Page  = (N_boat-1) / LV_PAGE_SIZE;
      selRow  = (N_boat-1) % LV_PAGE_SIZE;
   }
   
   LV_turnPage(thisListView, LV_Page);
   
   LISTVIEW_SetSel(thisListView, selRow);
   
   WM_InvalidateRect(subWins[2], &lvIndicate);  
}

