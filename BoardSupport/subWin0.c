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
#include "Drawinformation.h"
#include "Setting.h"
#include "SystemConfig.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0   (GUI_ID_USER + 0x10)
#define ID_LISTVIEW_0 (GUI_ID_USER + 0x11)
#define ID_TEXT_0     (GUI_ID_USER + 0x12)
#define ID_TEXT_1     (GUI_ID_USER + 0x13)
#define ID_TEXT_2     (GUI_ID_USER + 0x14)
#define ID_TEXT_3     (GUI_ID_USER + 0x15)
#define ID_TEXT_4     (GUI_ID_USER + 0x16)
#define ID_TEXT_5     (GUI_ID_USER + 0x17)
#define ID_TEXT_6     (GUI_ID_USER + 0x18)
#define ID_TEXT_7     (GUI_ID_USER + 0x19)
#define ID_TEXT_8     (GUI_ID_USER + 0x1a)


/*----------------- external variables ---------------------*/
extern char * pStrBuf;
extern WM_HWIN hDlg_FishMap;
extern WM_HWIN menuWin;
extern WM_HWIN subWins[4];
extern int N_monitedBoat;
extern MNT_BOAT MNT_Boats[MNT_NUM_MAX];
extern MNT_BERTH * pMntHeader;
/*----------------- externa   function ---------------------*/
extern void disttostr( char * str, int num);


/*----------------- local    variables ---------------------*/
static int index  = -1;


/*----------------- local     function ---------------------*/
static void myListViewListener(WM_MESSAGE* pMsg);
static void showSelectedBoatInfo(WM_HWIN thisListView);
static void updateListViewContent(WM_HWIN thisHandle);


/*----------------- static & const --------------------------*/

/* Rect 为监控船舶信息所占的区域 
* @ Attention: 矩形坐标是相对于窗口 subWins[0] 左上角点的坐标
*/
static GUI_RECT infoRect={LV_MoniteList_WIDTH+1,LV_MoniteList_Y,Win_Main_WIDTH-MenuLabel_WIDTH,480};
static GUI_RECT lvIndicate  = {LV_MoniteList_WIDTH-100,LV_MoniteList_Y-40,Win_Main_WIDTH-MenuLabel_WIDTH,LV_MoniteList_Y};
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
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, SubWin_X, SubWin_Y, SubWin_WIDTH, SubWin_HEIGHT, 0, 0x0, 0 },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, LV_MoniteList_X, LV_MoniteList_Y, LV_MoniteList_WIDTH, LV_MoniteList_HEIGHT, 0, 0x0, 0 },
	
	{ TEXT_CreateIndirect, "监控列表",        ID_TEXT_0, LV_MoniteList_X,       LV_MoniteList_Y-30,  200, 30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "监控船舶信息",    ID_TEXT_1, LV_MoniteList_WIDTH+2, LV_MoniteList_Y-40,  200, 30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "船名:",           ID_TEXT_2, LV_MoniteList_WIDTH+2, LV_MoniteList_Y+40,  200, 30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "北纬:",           ID_TEXT_3, LV_MoniteList_WIDTH+2, LV_MoniteList_Y+80,  200, 30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "东经:",           ID_TEXT_4, LV_MoniteList_WIDTH+2, LV_MoniteList_Y+120, 200, 30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "航速:",           ID_TEXT_5, LV_MoniteList_WIDTH+2, LV_MoniteList_Y+160, 200, 30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "DSPAlarm:",        ID_TEXT_6, LV_MoniteList_WIDTH+2, LV_MoniteList_Y+200, 200, 30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "BGLAlarm:",        ID_TEXT_7, LV_MoniteList_WIDTH+2, LV_MoniteList_Y+240, 200, 30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "DRGAlarm:",        ID_TEXT_8, LV_MoniteList_WIDTH+2, LV_MoniteList_Y+280, 200, 30, 0, 0x0, 0}
  // USER START (Optionally insert additional widgets)
  // USER END
};

LVWin_COLOR lvWinSkins[2]  = {
///                              bkColor     winLabel    lv_bkHeader   lv_txHeader  lv_gdHeader      lv_bkUnsel    lv_bkSel   lv_bkFocus      lv_txUnsel      lv_txSel    lv_txFocus      lv_string
                               { GUI_BLACK,  GUI_LIGHTGRAY,  GUI_DARKGREEN, GUI_WHITE,   GUI_LIGHTBLUE,   GUI_DARKGRAY, GUI_GRAY,  GUI_LIGHTBLUE,  GUI_LIGHTGRAY,  GUI_WHITE,  GUI_BLACK, GUI_DARKYELLOW },
                               { GUI_WHITE,  GUI_BLACK,  GUI_DARKGREEN,  GUI_BLACK,   GUI_DARKBLUE,    GUI_LIGHTGRAY,GUI_BLACK, GUI_LIGHTBLUE , GUI_DARKGRAY,   GUI_BLACK,  GUI_DARKYELLOW, GUI_DARKMAGENTA}
                              };

LVWin_COLOR * pLVSkin  = lvWinSkins;

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
  WM_MESSAGE myMsg;
  int     NCode;
  long  Id;
  int  SelectedRow  = -1;
  int i  = 0;
  int TotalRows  = 0;
  MNT_BERTH * pIterator  = NULL;
  
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case USER_MSG_BRING:
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
       updateListViewContent(hItem);
       WM_InvalidateRect(hItem, &lvIndicate);
       break;
  
  case USER_MSG_SKIN:
       pLVSkin  = &(lvWinSkins[pMsg->Data.v]);
       
       WINDOW_SetBkColor(pMsg->hWin,pLVSkin->BackGround);
       
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
       TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
       TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
       TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
       TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
       TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
       TEXT_SetTextColor(hItem, pLVSkin->Win_Label);       
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
       TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
       TEXT_SetTextColor(hItem, pLVSkin->Win_Label); 
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
       TEXT_SetTextColor(hItem, pLVSkin->Win_Label);       
       
       
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
       LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_UNSEL, pLVSkin->LV_bkUnsel);
       LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_SEL,   pLVSkin->LV_bkSel);
       LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_SELFOCUS, pLVSkin->LV_bkFocus);
       
       LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_UNSEL, pLVSkin->LV_tx_Unsel);
       LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_SEL,   pLVSkin->LV_tx_Sel);
       LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_SELFOCUS, pLVSkin->LV_tx_Focus);
       
       hItem  = LISTVIEW_GetHeader(hItem);
       HEADER_SetBkColor(hItem,pLVSkin->LV_Header_Bk);
       HEADER_SetTextColor(hItem,pLVSkin->LV_Header_Text);
       break;
  
  case WM_INIT_DIALOG:	
    //
    // Initialization of 'Window'
    //
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, pLVSkin->BackGround);
    //
    // Initializaton fo 'Text'
    //
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextColor(hItem, pLVSkin->Win_Label); 
    
        
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetFont(hItem,  &GUI_Font24_1);
    TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetFont(hItem,  &GUI_Font24_1);
    TEXT_SetTextColor(hItem, pLVSkin->Win_Label); 
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetFont(hItem,  &GUI_Font24_1);
    TEXT_SetTextColor(hItem, pLVSkin->Win_Label);
    
    //
    // Initialization of 'Listview'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
	   WM_SetCallback(hItem, &myListViewListener);
	  
    LISTVIEW_AddColumn(hItem, LV_MoniteList_Col_0_WIDTH, "距离", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, LV_MoniteList_Col_1_WIDTH, "MMSI", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, LV_MoniteList_Col_2_WIDTH, "S      ", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddRow(hItem, NULL);
    LISTVIEW_SetGridVis(hItem, 1);
	   LISTVIEW_SetHeaderHeight(hItem,LV_MoniteList_Header_HEIGHT);
	   LISTVIEW_SetRowHeight(hItem,LV_MoniteList_Row_HEIGHT);
	  
	   LISTVIEW_SetFont(hItem, &GUI_Font24_1);	  
    LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_UNSEL, pLVSkin->LV_bkUnsel);
    LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_SEL,   pLVSkin->LV_bkSel);
    LISTVIEW_SetBkColor(hItem, LISTVIEW_CI_SELFOCUS, pLVSkin->LV_bkFocus);
    
    LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_UNSEL, pLVSkin->LV_tx_Unsel);
    LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_SEL,   pLVSkin->LV_tx_Sel);
    LISTVIEW_SetTextColor(hItem,LISTVIEW_CI_SELFOCUS, pLVSkin->LV_tx_Focus);

	  	updateListViewContent(hItem); 
    
    hItem  = LISTVIEW_GetHeader(hItem);
    HEADER_SetBkColor(hItem,pLVSkin->LV_Header_Bk);
    HEADER_SetTextColor(hItem,pLVSkin->LV_Header_Text);

    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
		
	case WM_PAINT:
//     updateListViewContent(WM_GetDialogItem(pMsg->hWin,ID_LISTVIEW_0));

    GUI_SetColor(GUI_DARKGRAY);
    GUI_FillRectEx(&infoRect);

     GUI_SetFont(&GUI_Font24_1);
     GUI_SetColor(pLVSkin->String);
     GUI_SetTextMode(GUI_TM_TRANS);
	  
     hItem  = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
     SelectedRow  = LISTVIEW_GetSel(hItem);
     if(SelectedRow < 0)
        break;
     TotalRows  = LISTVIEW_GetNumRows(hItem);     
     sprintf(pStrBuf,"%3d/%3d",SelectedRow+1, TotalRows);
     GUI_DispStringAt(pStrBuf, LV_MoniteList_WIDTH-100, LV_MoniteList_Y-30);
     
     pIterator  = pMntHeader;
     for(i=0;i<SelectedRow;i++)
     {
        pIterator  = pIterator->pNext;
     }  
  
     GUI_DispStringAt(pIterator->mntBoat.name, LV_MoniteList_WIDTH+80, 80);         
     
     if(pIterator->mntBoat.pBoat)
     {
        lltostr(pIterator->mntBoat.pBoat->latitude, pStrBuf);
        GUI_DispStringAt(pStrBuf, LV_MoniteList_WIDTH+100, 120);
        
        lltostr(pIterator->mntBoat.pBoat->longitude, pStrBuf);
        GUI_DispStringAt(pStrBuf, LV_MoniteList_WIDTH+100, 160);
        
        GUI_DispDecAt(pIterator->mntBoat.pBoat->SOG, LV_MoniteList_WIDTH+80, 200, 3);
        GUI_DispDecAt(pIterator->mntBoat.pBoat->COG, LV_MoniteList_WIDTH+300, 200, 3);
     }
     
     if(pIterator->mntBoat.mntSetting.DSP_Setting.isEnable == DISABLE)
        GUI_DispStringAt("关闭", LV_MoniteList_WIDTH+60,240);
     else
        GUI_DispStringAt("开启",  LV_MoniteList_WIDTH+60,240);
        
     GUI_DispDecAt(pIterator->mntBoat.mntSetting.BGL_Setting.Dist,
               LV_MoniteList_WIDTH+110,280,3);
     GUI_DispDecAt(pIterator->mntBoat.mntSetting.DRG_Setting.Dist,
                 LV_MoniteList_WIDTH+110,320,3);   
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
WM_HWIN sub0WinCreate(void);
WM_HWIN sub0WinCreate(void) {
  WM_HWIN hWin;
	
	
//  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, menuWin, 0, 0);
  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END


/**监控列表 LISTVIEW 的监听器（回调函数）
*
*/
static void myListViewListener(WM_MESSAGE* pMsg)
{
  int selectedRow  = -1;
  int lastRow  = 0;
	 const WM_KEY_INFO * pInfo;
	 WM_HWIN thisListView  = pMsg->hWin; 
  WM_MESSAGE myMsg;
	switch(pMsg->MsgId)
	{
		case WM_SET_FOCUS:
       if(pMsg->Data.v)
       {
          myMsg.hWin  = menuWin;
          myMsg.hWinSrc  = thisListView;
          myMsg.MsgId  = USER_MSG_BRING;
          myMsg.Data.v  = 0;
          WM_SendMessage(myMsg.hWin, &myMsg);  
       }
     
       
       if(LISTVIEW_GetNumRows(pMsg->hWin))
          LISTVIEW_SetSel(pMsg->hWin, 0);
          
       LISTVIEW_Callback(pMsg);
       WM_InvalidateRect(subWins[0], &infoRect);
       WM_InvalidateRect(subWins[0], &lvIndicate);
       break;
       
		case WM_KEY:
			pInfo  = (WM_KEY_INFO*)pMsg->Data.p;
		
		  switch(pInfo->Key)
			{
				case GUI_KEY_UP:
				case GUI_KEY_DOWN:
       LISTVIEW_Callback(pMsg);
       WM_InvalidateRect(subWins[0], &infoRect);    
       WM_InvalidateRect(subWins[0], &lvIndicate);       
//       showSelectedBoatInfo(thisListView);	
       break;
				case GUI_KEY_BACKSPACE:				
					WM_SetFocus(menuWin);
					break;
    case GUI_KEY_RIGHT:
         selectedRow  = LISTVIEW_GetSel(thisListView);
         lastRow      = LISTVIEW_GetNumRows(thisListView);
         

         
         if(selectedRow/10 < lastRow/10)
         {
            LISTVIEW_SetSel(thisListView, lastRow);         
            LISTVIEW_SetSel(thisListView, selectedRow-selectedRow%10+10);
         }
         WM_InvalidateRect(subWins[0], &lvIndicate);
         break;
    case GUI_KEY_LEFT:
         selectedRow  = LISTVIEW_GetSel(thisListView);
         lastRow      = LISTVIEW_GetNumRows(thisListView);
         
         if(selectedRow > 9)
         {
            LISTVIEW_SetSel(thisListView, lastRow);
            LISTVIEW_SetSel(thisListView, selectedRow-selectedRow%10-10);
         }
         WM_InvalidateRect(subWins[0], &lvIndicate);         
         break;
				case GUI_KEY_MENU:
//         WM_BringToBottom(thisListView);
					WM_BringToTop(hDlg_FishMap);
				  WM_SetFocus(hDlg_FishMap);
					break;
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


/**监控列表 LISTVIEW 条目更新
*
*/
static void updateListViewContent(WM_HWIN thisHandle)
{
	WM_HWIN  thisListView  = thisHandle;
	int i  = 0;
	int Cnt  = 0;
 int NumOfRows  = 0;
 MNT_BERTH * pIterator  = NULL;
 
	NumOfRows  = LISTVIEW_GetNumRows(thisListView);

 pIterator  = pMntHeader;
 while(pIterator)
 {
    Cnt++;
    if(Cnt > NumOfRows)
    {
       LISTVIEW_AddRow(thisListView, NULL);
       NumOfRows  = LISTVIEW_GetNumRows(thisListView);
    }
    
    if(pIterator->mntBoat.pBoat)
    {
       disttostr(pStrBuf, pIterator->mntBoat.pBoat->dist);
       LISTVIEW_SetItemText(thisListView, 0, Cnt-1, pStrBuf);     
    }      
    else
    {
       LISTVIEW_SetItemText(thisListView, 0, Cnt-1, "????");
    }

    
    sprintf(pStrBuf, "%09ld", pIterator->mntBoat.mmsi);
    LISTVIEW_SetItemText(thisListView, 1, Cnt-1, pStrBuf);
    
    
    pIterator  = pIterator->pNext;
 }

	while(NumOfRows > Cnt)
	{
		LISTVIEW_DeleteRow(thisListView, NumOfRows-1);
		NumOfRows  = LISTVIEW_GetNumRows(thisListView);
	}
}



/*************************** End of file ****************************/
