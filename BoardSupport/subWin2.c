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
#include "Config.h"
#include "MainTask.h"


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


/*---------------- external variables ---------------------------*/
extern _boat* boat_list_p[BOAT_LIST_SIZE_MAX];
extern _boat  boat_list[BOAT_LIST_SIZE_MAX];


extern short N_boat;
extern short N_monitedBoat;
extern unsigned char* pStrBuf;

extern WM_HWIN menuWin;
extern WM_HWIN subWins[4];






/*---------------- external functions --------------------------*/
extern void myftoa(unsigned char * str, float num);



/*---------------- loacal variables ----------------------------*/



/*---------------- local functions -----------------------------*/
static void myListViewListener(WM_MESSAGE* pMsg);
static void updateListViewContent(WM_HWIN thisHandle);
static void showSelectedBoatInfo(WM_HWIN thisHandle);
int getSelectedBoatIndex(WM_HWIN thisHandle, int col, int row);



/*---------------- static variables ----------------------------*/
static int Index  = -1; //模块变量
static int SelRow  = 0;
static int TotalRows  = 0;
static WM_HTIMER allListRefshTimer;

static GUI_RECT infoRect  = {LV_AllList_WIDTH,LV_AllList_Y,Win_Main_WIDTH-MenuLabel_WIDTH,480};
static GUI_RECT lvIndicate  ={LV_AllList_WIDTH-200,LV_AllList_Y-40,Win_Main_WIDTH-MenuLabel_WIDTH,480};
static GUI_RECT lvRect   = {0,LV_AllList_Y,LV_AllList_WIDTH,LV_AllList_HEIGHT};






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
	
	{ TEXT_CreateIndirect,     "All List",        ID_TEXT_0,     LV_AllList_X,     LV_AllList_Y-30,  200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "All boats info",  ID_TEXT_1,     LV_AllList_WIDTH, LV_AllList_Y-40,  200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "Name:",           ID_TEXT_2,     LV_AllList_WIDTH, LV_AllList_Y+40,  200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "N:",              ID_TEXT_3,     LV_AllList_WIDTH, LV_AllList_Y+80,  200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "E:",              ID_TEXT_4,     LV_AllList_WIDTH, LV_AllList_Y+120, 200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "SOG:",            ID_TEXT_5,     LV_AllList_WIDTH, LV_AllList_Y+160, 200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "XSAlarm:",        ID_TEXT_6,     LV_AllList_WIDTH, LV_AllList_Y+200, 200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "FDAlarm:",        ID_TEXT_7,     LV_AllList_WIDTH, LV_AllList_Y+240, 200,  30, 0, 0x0, 0},
	{ TEXT_CreateIndirect,     "ZMAlarm:",        ID_TEXT_8,     LV_AllList_WIDTH, LV_AllList_Y+280, 200,  30, 0, 0x0, 0}
  // USER START (Optionally insert additional widgets)
  // USER END
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
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {	
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Window'
    //
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, 0x00FFFF00);
    //
    // Initialization of 'Listview'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
	   WM_SetCallback(hItem, &myListViewListener);
	  
	   LISTVIEW_SetFont(hItem, &GUI_Font28);
    LISTVIEW_AddColumn(hItem, LV_AllList_Col_0_WIDTH, "Dis", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, LV_AllList_Col_1_WIDTH, "Ang", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, LV_AllList_Col_2_WIDTH, "MMSI", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, LV_AllList_Col_3_WIDTH, "State", GUI_TA_HCENTER | GUI_TA_VCENTER);	
    LISTVIEW_AddRow(hItem, NULL);
    LISTVIEW_SetGridVis(hItem, 1);
	   LISTVIEW_SetHeaderHeight(hItem,LV_MoniteList_Header_HEIGHT);
	   LISTVIEW_SetRowHeight(hItem,LV_MoniteList_Row_HEIGHT);
	
    LISTVIEW_SetFont(hItem, &GUI_Font24B_1);
    LISTVIEW_SetTextColor(hItem, LISTVIEW_CI_UNSEL,GUI_WHITE);
    LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_UNSEL,DEEPBLUE);
    LISTVIEW_SetTextColor(hItem, LISTVIEW_CI_SELFOCUS,GUI_BLACK);
    LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_SELFOCUS, GUI_WHITE);
    LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_SEL, DEEPBLUE);
    LISTVIEW_SetAutoScrollV(hItem,1);
    
//   LISTVIEW_SetCompareFunc(hItem,2,LISTVIEW_CompareDec);
//   LISTVIEW_SetSort(hItem,2,1);
//   LISTVIEW_EnableSort(hItem);
   
   updateListViewContent(hItem);
    
    allListRefshTimer  = WM_CreateTimer(pMsg->hWin, 1, 5000, 0);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
case WM_TIMER:
   WM_InvalidateRect(subWins[2],&lvRect);
   WM_InvalidateRect(subWins[2],&lvIndicate);
   WM_RestartTimer(allListRefshTimer,5000);
break;    
		
case WM_PAINT:

    updateListViewContent(WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0));

		GUI_SetFont(&GUI_Font24_1);
		GUI_SetColor(GUI_YELLOW);
		GUI_SetTextMode(GUI_TM_TRANS);
	  
	  if(Index >= 0)
		{
     
     sprintf(pStrBuf,"%3d/%3d",Index+1,TotalRows);
     GUI_DispStringAt(pStrBuf,LV_AllList_WIDTH-200,LV_AllList_Y-40);
//      if(boat_list_p[Index]->name[0] != '\0')
			  GUI_DispStringAt(boat_list_p[Index]->name,LV_AllList_WIDTH+50,80);       
     
     lltostr(boat_list_p[Index]->latitude,pStrBuf);
     GUI_DispStringExAt(pStrBuf,LV_AllList_WIDTH+20,120);	
     
     lltostr(boat_list_p[Index]->longitude,pStrBuf);
     GUI_DispStringExAt(pStrBuf,LV_AllList_WIDTH+20,160);
     
     GUI_DispDecAt(boat_list_p[Index]->SOG,LV_AllList_WIDTH+80,200,3);
//INFO("at %d name:%s",Index,boat_list_p[Index]->name);     
//INFO("at %d id: %ld",Index,boat_list_p[Index]->user_id);
//INFO("at %d lg: %ld",Index,boat_list_p[Index]->longitude);      
//INFO("at %d lt: %ld",Index,boat_list_p[Index]->latitude);

  	}

		break;		
		
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_LISTVIEW_0: // Notifications sent by 'Listview'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
			  // WM_InvalidateRect(pMsg->hWin,&infoRect);		// 可以,但逻辑不对			
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
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
WM_HWIN sub2WinCreate(void);
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
 
 int selectedRow  = -1;
 int totalRows  = 0;
	int i  = 0;
 
	switch(pMsg->MsgId)
	{
		case WM_SET_FOCUS:

      if(LISTVIEW_GetNumRows(pMsg->hWin) && (LISTVIEW_GetSel(pMsg->hWin)<0))
         LISTVIEW_SetSel(pMsg->hWin, 0);
      showSelectedBoatInfo(pMsg->hWin);
      LISTVIEW_Callback(pMsg);
      break;	    
    
    case WM_KEY:
			pInfo  = (WM_KEY_INFO*)pMsg->Data.p;
		  
		  switch(pInfo->Key)
			{
				case GUI_KEY_UP:
				case GUI_KEY_DOWN:
				  LISTVIEW_Callback(pMsg);
  				showSelectedBoatInfo(thisListView);
				 	break;
				
    case GUI_KEY_RIGHT:
    
         selectedRow  = LISTVIEW_GetSel(thisListView);
         totalRows    = LISTVIEW_GetNumRows(thisListView);
         LISTVIEW_SetSel(thisListView, totalRows);
         if(selectedRow/10 < totalRows/10)
            LISTVIEW_SetSel(thisListView,selectedRow-selectedRow%10+10);
         showSelectedBoatInfo(thisListView);
         break;
         
    case GUI_KEY_LEFT:
         selectedRow  = LISTVIEW_GetSel(thisListView);
         totalRows    = LISTVIEW_GetNumRows(thisListView);
         if(selectedRow >9 )
         {
            LISTVIEW_SetSel(thisListView, totalRows);
            LISTVIEW_SetSel(thisListView,selectedRow-selectedRow%10-10);
         }
            

            
         showSelectedBoatInfo(thisListView);
         break;
    
				case GUI_KEY_BACKSPACE:
//      for(i=0;i<N_boat;i++)
//      {
//         if( MNTState_Choosen == boat_list_p[i]->mntState)
//         {
//            
//            boat_list_p[i]->mntState  = MNTState_Monite;
//            selectedRow  = MNT_insert(mntBoats,boat_list_p[i]->user_id, boat_list_p[i]->name);
////printf("\r\nendIndex:%d:\r\n",selectedRow);
////printf("\r\nN_moniteBoat:%d\r\n",N_monitedBoat);            
//         }
//      }
      WM_SetFocus(menuWin);
      break;
/*----------------------------------------------------------------------     
				case GUI_KEY_ENTER:
      selectedRow  = LISTVIEW_GetSel(thisListView);
      LISTVIEW_GetItemText(thisListView, 3, selectedRow, pStrBuf, 10);
      
      ///
      if('o' == pStrBuf[0])
      {
         boat_list_p[selectedRow]->isVisible  = 0;
         LISTVIEW_SetItemText(thisListView, 3, selectedRow, "x");
      }
      else
      {
         boat_list_p[selectedRow]->isVisible  = 1;
         LISTVIEW_SetItemText(thisListView, 3, selectedRow, "o");
      }
      break;
----------------------------------------------------------------------*/    
//    case GUI_KEY_ENTER:
//         selectedRow  = LISTVIEW_GetSel(thisListView);
//   
//         if(MNTState_None == boat_list_p[Index]->mntState)
//         {
//       
//            boat_list_p[Index]->mntState  = MNTState_Choosen;
//            LISTVIEW_SetItemText(thisListView, 3, selectedRow, "o");
//         }
//         else if(MNTState_Choosen  == boat_list_p[Index]->mntState)
//         {
//     
//            boat_list_p[Index]->mntState  = MNTState_None;
//            LISTVIEW_SetItemText(thisListView, 3, selectedRow, "x");
//         }
//         break;

         
				default:
      LISTVIEW_Callback(pMsg);
      break;
			}
			break;
			
				default:
					LISTVIEW_Callback(pMsg);
					break;
	}
}



/* 更新所有船舶列表的条目
*
*/
static void updateListViewContent(WM_HWIN thisHandle)
{
	

	
	WM_HWIN thisListView  = thisHandle;
	
	int i  = 0;
	int NumOfRows  = 0;

 
	NumOfRows  = LISTVIEW_GetNumRows(thisListView);
	
	for(i=0;i<N_boat;i++)
	{
		// LISTVIEW 行数小于要显示的船的数量，添加行
		if(i+1 > NumOfRows)
		{		
			LISTVIEW_AddRow(thisListView, NULL);
			NumOfRows  = LISTVIEW_GetNumRows(thisListView);
		}
		

    myftoa(pStrBuf, boat_list_p[i]->dist);
    LISTVIEW_SetItemText(thisListView, 0, i, pStrBuf);
		  sprintf(pStrBuf, "%09ld", boat_list_p[i]->user_id);
		  LISTVIEW_SetItemText(thisListView, 2, i, pStrBuf);

	}

// while(pTmp)
// {
//    i++;
//    if(i>NumOfRows)
//    {
//       LISTVIEW_AddRow(LISTVIEW_GetNumRows(thisListView),NULL);
//       NumOfRows  = LISTVIEW_GetNumRows(thisHandle);
//    }
//    
//    sprintf(pStrBuf, "%09ld", pTmp->boat.user_id);
//    LISTVIEW_SetItemText(thisListView, 2, i, pStrBuf);
//    pTmp  = pTmp->pNext;
// }
//	
	// LISTVIEW 行数大于要显示的船的数量，删除行
	while(NumOfRows > i)
	{
	 	LISTVIEW_DeleteRow(thisListView, NumOfRows-1);
	 	NumOfRows  = LISTVIEW_GetNumRows(thisListView);
	}
	
 NumOfRows  = LISTVIEW_GetNumRows(thisListView);
 TotalRows  = NumOfRows;
 

}


int getSelectedBoatIndex(WM_HWIN thisHandle,int col,int row)
{
   WM_HWIN thisListView  = thisHandle;
   int i  = -1;
   long SelectedId  = 0;
   if(row >= 0)
   {
      LISTVIEW_GetItemText(thisListView, col, row, pStrBuf, 10);
      SelectedId  = strtoi(pStrBuf);
      
      while( (boat_list_p[i]->user_id!=SelectedId)  &&  (i<N_boat) )
      {
          i++;
      }
   }
   
  return i;
}


static void showSelectedBoatInfo(WM_HWIN thisHandle)
{
	
	WM_HWIN thisListView  = thisHandle;
	
	int SelectedRow  = -1;
//	int i  = 0;
//	
//	long SelectedId  = 0;

//	
	SelectedRow  = LISTVIEW_GetSel(thisListView);
//	if(SelectedRow >= 0)
//	{
//    SelRow  = SelectedRow+1;
//    LISTVIEW_GetItemText(thisListView, 2, SelectedRow, pStrBuf, 10);
//    SelectedId  = strtoi(pStrBuf);
//    
//    // 找到 MMSI 对应的船舶索引
//    while((boat_list_p[i]->user_id!=SelectedId) && (i<N_boat))
//    {
//     i++;
//    }
//    
//    if(i<N_boat)
//    {
//     Index  = i;
//    }
    Index  = getSelectedBoatIndex(thisListView, 2, SelectedRow);
    WM_InvalidateRect(subWins[2],&infoRect);
    WM_InvalidateRect(subWins[2],&lvIndicate);
//	}
}


















/*************************** End of file ****************************/
