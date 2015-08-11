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
#include "MainTask.h"
#include "Config.h"
#include "Setting.h"
#include "SystemConfig.h"


/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)

#define ID_TEXT_0 (GUI_ID_USER + 0x01)
#define ID_TEXT_1 (GUI_ID_USER + 0x02)
#define ID_TEXT_2 (GUI_ID_USER + 0x03)
#define ID_TEXT_3 (GUI_ID_USER + 0x04)
#define ID_TEXT_4 (GUI_ID_USER + 0x05)
#define ID_TEXT_5 (GUI_ID_USER + 0x06)
#define ID_TEXT_6 (GUI_ID_USER + 0x07)
#define ID_TEXT_7 (GUI_ID_USER + 0x08)
#define ID_TEXT_8 (GUI_ID_USER + 0x09)
#define ID_TEXT_9 (GUI_ID_USER + 0x0a)

#define ID_EDIT_0 (GUI_ID_USER + 0x10)
#define ID_EDIT_1 (GUI_ID_USER + 0x11)
#define ID_EDIT_2 (GUI_ID_USER + 0x12)
#define ID_EDIT_3 (GUI_ID_USER + 0x13)
#define ID_EDIT_4 (GUI_ID_USER + 0x14)
#define ID_EDIT_5 (GUI_ID_USER + 0x15)
#define ID_EDIT_6 (GUI_ID_USER + 0x16)


/*------------------- external variables ------------------------*/
extern char * pStrBuf;

extern WM_HWIN subWins[4];
extern WM_HWIN confirmWin;
extern WM_HWIN menuWin;

extern MNT_BOAT MNT_Boats[BOAT_LIST_SIZE_MAX];
extern short N_monitedBoat;

extern CONF_SYS  SysConf;



/*------------------- external functions ------------------------*/


/*------------------- local    variables -------------------------*/
WM_HWIN etWin ;
WM_HWIN hEts[7];

static int fdDist  = 0;
static int zmDist  = 0;
static void myEditListener(WM_MESSAGE* pMsg);
static void myEditAddKeyEx(EDIT_Handle hObj, int key);
static void EtReset(WM_HWIN thisWin);

MNT_SETTING mntSetting;
/*------------------- local    functions -------------------------*/
//void printMoniteSetting(void);
//void printSetting(MNT_SETTING * p_setting);
//extern void mntSetting_init(void);



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
  { WINDOW_CreateIndirect, "ETWin", ID_WINDOW_0, ETWin_X, SubWin_Y+40, ETWin_WIDHT, ETWin_HEIGHT-40, 0, 0x0, 0 },
	
	{ TEXT_CreateIndirect, "监控设置项:",   ID_TEXT_0, 0,    0,                  ETWin_WIDHT,30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "1.消失报警:",   ID_TEXT_1, 0,    LV_MoniteSet_Y,     160,        30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "2.防盗报警:",   ID_TEXT_2, 0,    LV_MoniteSet_Y+40,  200,        30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "报警距离:",     ID_TEXT_3, 30,   LV_MoniteSet_Y+80,  200,         0, 0, 0x0, 0},
 { TEXT_CreateIndirect, "nm",             ID_TEXT_8, 240,  LV_MoniteSet_Y+80,   50,        30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "报警声音:",     ID_TEXT_4, 30,   LV_MoniteSet_Y+120, 200,        30, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "3.走锚报警:",   ID_TEXT_5, 0,    LV_MoniteSet_Y+160, 200,        40, 0, 0x0, 0},
	{ TEXT_CreateIndirect, "报警距离:",     ID_TEXT_6, 30,   LV_MoniteSet_Y+200, 200,        40,  0, 0x0, 0},
 { TEXT_CreateIndirect, "nm",             ID_TEXT_9, 240,  LV_MoniteSet_Y+200, 50,         40,  0, 0x0,0},
 { TEXT_CreateIndirect, "报警声音:",     ID_TEXT_7, 30,   LV_MoniteSet_Y+240, 200,        40,  0, 0x0, 0},

 
 { EDIT_CreateIndirect, "et_0", ID_EDIT_0, 160, LV_MoniteSet_Y,     80, 30, 0, 0xa,  0 },
 { EDIT_CreateIndirect, "et_1", ID_EDIT_1, 160, LV_MoniteSet_Y+40,  80, 30, 0, 0x64, 0 },
 { EDIT_CreateIndirect, "et_2", ID_EDIT_2, 160, LV_MoniteSet_Y+80,  80, 30, 0, 0x64, 0 },
 { EDIT_CreateIndirect, "et_3", ID_EDIT_3, 160, LV_MoniteSet_Y+120, 80, 30, 0, 0x64, 0 },
 { EDIT_CreateIndirect, "et_4", ID_EDIT_4, 160, LV_MoniteSet_Y+160, 80, 30, 0, 0x64, 0 },
 { EDIT_CreateIndirect, "et_5", ID_EDIT_5, 160, LV_MoniteSet_Y+200, 80, 30, 0, 0x64, 0},
	{ EDIT_CreateIndirect, "et_6", ID_EDIT_6, 160, LV_MoniteSet_Y+240, 80, 30, 0, 0x64, 0}
	
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
EditWin_COLOR EditWinSkins[2]  = {
///                                      bkColor         etLabel     etBkEnable       etText          etTxBk
                                        { GUI_DARKGRAY,  GUI_BLACK,  GUI_DARKGREEN,   GUI_LIGHTGRAY, GUI_BLACK},
                                        { GUI_GRAY,      GUI_GRAY,   GUI_LIGHTGREEN,  GUI_DARKGRAY,  GUI_LIGHTMAGENTA} 
                                       };

EditWin_COLOR * pEtWinSkin  = EditWinSkins;
// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
	
	const WM_KEY_INFO* pInfo;
 WM_HWIN  hItem  = 0;
 
  int     i  = 0;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END
  switch (pMsg->MsgId) {
  
  case USER_MSG_SKIN: 
       pEtWinSkin  = &(EditWinSkins[pMsg->Data.v]);
       
       WINDOW_SetBkColor(pMsg->hWin, pEtWinSkin->EditWin_BackGround);
       
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
       TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
       TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
       TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label); 
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
       TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
       TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
       TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
       TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
       TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
       TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
       hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
       TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);  

       for(i=0;i<7;i++)
       {
          EDIT_SetBkColor(hEts[i], EDIT_CI_ENABLED, pEtWinSkin->EditWin_Text);
          EDIT_SetTextColor(hEts[i], 0, pEtWinSkin->EditWin_Text);
       }       
  case WM_INIT_DIALOG:
    //
    // Initialization of 'text'
    //    
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label); 
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
    hItem  = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
    TEXT_SetTextColor(hItem, pEtWinSkin->EditWin_Label);    
  
    //
    // Initialization of 'et_0'
    //
    hEts[0] = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    EDIT_SetText(hEts[0], mntSetting.DSP_Setting.isEnable>DISABLE?"开启":"关闭");   
	   WM_SetCallback(hEts[0],&myEditListener);
    EDIT_SetpfAddKeyEx(hEts[0],myEditAddKeyEx);
    
    //
    // Initialization of 'et_1'
    //
    hEts[1] = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
    EDIT_SetText(hEts[1], mntSetting.BGL_Setting.isEnable>DISABLE?"开启":"关闭"); 
	   WM_SetCallback(hEts[1],&myEditListener);
    EDIT_SetpfAddKeyEx(hEts[1], myEditAddKeyEx);    
    //
    // Initialization of 'et_2'
    //
    hEts[2] = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
	  	sprintf(pStrBuf, "%d",mntSetting.BGL_Setting.Dist);
	  	EDIT_SetText(hEts[2], pStrBuf);  
	   WM_SetCallback(hEts[2],&myEditListener);	
    EDIT_SetpfAddKeyEx(hEts[2], myEditAddKeyEx);
    //
    // Initialization of 'et_3'
    //
    hEts[3] = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
    EDIT_SetText(hEts[3], mntSetting.BGL_Setting.isSndEnable>DISABLE?"开启":"关闭");
	   WM_SetCallback(hEts[3] ,&myEditListener);	
    EDIT_SetpfAddKeyEx(hEts[3], myEditAddKeyEx);    
    //
    // Initialization of 'et_4'
    //
    hEts[4]  = WM_GetDialogItem(pMsg->hWin, ID_EDIT_4);
    EDIT_SetText(hEts[4], mntSetting.DRG_Setting.isEnable>DISABLE?"开启":"关闭");
	   WM_SetCallback(hEts[4],&myEditListener);
    EDIT_SetpfAddKeyEx(hEts[4], myEditAddKeyEx);    
   
    //
    // Initialization of 'et_5'
    //
    hEts[5]  = WM_GetDialogItem(pMsg->hWin, ID_EDIT_5);   
    sprintf(pStrBuf, "%d",mntSetting.DRG_Setting.Dist);
    EDIT_SetText(hEts[5], pStrBuf);     
    WM_SetCallback(hEts[5],&myEditListener);
    EDIT_SetpfAddKeyEx(hEts[5], myEditAddKeyEx);
    
    
    hEts[6]  = WM_GetDialogItem(pMsg->hWin, ID_EDIT_6);
    EDIT_SetText(hEts[6], mntSetting.DRG_Setting.isSndEnable>DISABLE?"开启":"关闭");
    WM_SetCallback(hEts[6], &myEditListener);
    EDIT_SetpfAddKeyEx(hEts[6], myEditAddKeyEx);
    
    for(i=0;i<7;i++)
    {
       EDIT_SetBkColor(hEts[i], EDIT_CI_ENABLED, pEtWinSkin->EditWin_Text);
       EDIT_SetTextColor(hEts[i], 0, pEtWinSkin->EditWin_Text);
    }
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;

	
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_EDIT_0: // Notifications sent by 'et_0'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_1: // Notifications sent by 'et_1'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_2: // Notifications sent by 'et_2'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_3: // Notifications sent by 'et_3'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_4: // Notifications sent by 'et_4'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
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
*       CreateETWin
*/
WM_HWIN etWinCreate(void);
WM_HWIN etWinCreate(void) {

  etWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, subWins[1], 0, 0);
//etWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return etWin;
}

// USER START (Optionally insert additional public code)

static void myEditListener(WM_MESSAGE* pMsg)
{
	const WM_KEY_INFO* pInfo;
	WM_MESSAGE myMsg;
	WM_HWIN thisEdit = pMsg->hWin;
	
	WM_HWIN focussedEdit  = 0;
	
	int i  = 0;
	int Step  = 0;

	
	switch(pMsg->MsgId)
	{
		case WM_KEY:
			pInfo  = (WM_KEY_INFO*)pMsg->Data.p;
		
		  switch(pInfo->Key)
			{
				case GUI_KEY_UP:
					GUI_StoreKeyMsg(GUI_KEY_BACKTAB,1);
					break;
				
				case GUI_KEY_DOWN:
					GUI_StoreKeyMsg(GUI_KEY_TAB,1);
					break;
		
    case GUI_KEY_RIGHT:
         Step  = 10;
    case GUI_KEY_LEFT:
         Step  = (Step>5)?5:-5;
         focussedEdit  = WM_GetFocussedWindow();
         while( (focussedEdit != hEts[i])  &&  (i<7) )
              i++;

         switch(i)
         {
            case 0:
                 if(mntSetting.DSP_Setting.isEnable)
                 {
                    mntSetting.DSP_Setting.isEnable  = DISABLE;
                    EDIT_SetText(hEts[0], "关闭");
                 }
                 else
                 {
                    mntSetting.DSP_Setting.isEnable  = ENABLE;
                    EDIT_SetText(hEts[0], "开启");
                 }
                 break;
                 
            case 1:
                 if(mntSetting.BGL_Setting.isEnable)
                 {
                    mntSetting.BGL_Setting.isEnable  = DISABLE;
                    EDIT_SetText(hEts[1], "关闭");
                 }
                 else
                 {
                    mntSetting.BGL_Setting.isEnable  = ENABLE;
                    EDIT_SetText(hEts[1], "开启");
                 }
                 break;
                 
            case 2:
                 mntSetting.BGL_Setting.Dist  += Step;
                 mntSetting.BGL_Setting.Dist  = (mntSetting.BGL_Setting.Dist+105)%105;
                 
                 sprintf(pStrBuf, "%d.%02d", mntSetting.BGL_Setting.Dist/100, mntSetting.BGL_Setting.Dist%100);
                 EDIT_SetText(hEts[2], pStrBuf);
                 break;
                 
            case 3:
                 if(mntSetting.BGL_Setting.isSndEnable) 
                 {                 
                    mntSetting.BGL_Setting.isSndEnable = DISABLE;
                    EDIT_SetText(hEts[3], "关闭");
                 } 
                 else
                 {                
                    mntSetting.BGL_Setting.isSndEnable  = ENABLE;
                    EDIT_SetText(hEts[3], "开启");
                 }                   
                 break;  
            case 4:
                 if(mntSetting.DRG_Setting.isEnable)
                 { 
                    mntSetting.DRG_Setting.isEnable  = DISABLE;
                    EDIT_SetText(hEts[4], "关闭");
                 }
                 else
                 {
                    mntSetting.DRG_Setting.isEnable  = ENABLE;
                    EDIT_SetText(hEts[4], "开启");
                 }
                 break;            
                 
            case 5:
                 mntSetting.DRG_Setting.Dist  += Step;
                 mntSetting.DRG_Setting.Dist  = (mntSetting.DRG_Setting.Dist+105)%105;
                 
                 sprintf(pStrBuf, "%d.%02d", mntSetting.DRG_Setting.Dist/100, mntSetting.DRG_Setting.Dist%100);
                 EDIT_SetText(hEts[5], pStrBuf);
                 break; 
            
            case 6:
                 if(mntSetting.DRG_Setting.isSndEnable)
                 {
                    mntSetting.DRG_Setting.isSndEnable  = DISABLE;
                    EDIT_SetText(hEts[6], "关闭");
                 }
                 else
                 {
                    mntSetting.DRG_Setting.isSndEnable  = ENABLE;
                    EDIT_SetText(hEts[6], "开启");
                 }
                 break;            
                 
         }
         break;
    	
    case GUI_KEY_BACKSPACE:
         myMsg.hWin  = WM_GetClientWindow(confirmWin);
//         myMsg.hWin  = confirmWin;
         myMsg.hWinSrc  = pMsg->hWin;
         myMsg.MsgId  = USER_MSG_ID_CHOOSE;
         myMsg.Data.v = STORE_SETTING;
         WM_SendMessage(myMsg.hWin, &myMsg);
         
         WM_BringToTop(confirmWin);
         WM_SetFocus(confirmWin);
    break; 
         
				default:
					EDIT_Callback(pMsg);
				break;
			}
   break;
			
   case USER_MSG_ID_REPLY:
       switch(pMsg->Data.v)
       {
          case REPLY_OK:
               MNT_makeSettingUp(&mntSetting);  
               MNT_init(&mntSetting);
               EtReset(etWin);
               printMoniteSetting(MNT_Boats);              
               WM_SetFocus(menuWin);
               break;
          case REPLY_CANCEL:         
               WM_SetFocus(subWins[1]);
               break;
               
           default:
INFO("Something err!");           
           break;
       }
 
   break;
       
				default:
					EDIT_Callback(pMsg);
				break;
	}	 
  
}



static void myEditAddKeyEx(EDIT_Handle hObj, int key)
{
   WM_HWIN thisEdit;
   
   switch(key)
   {
      break;
   }
}
// USER END

static void EtReset(WM_HWIN thisWin)
{
   EDIT_SetText(hEts[0], mntSetting.DSP_Setting.isEnable>DISABLE?"开启":"关闭");   
   EDIT_SetText(hEts[1], mntSetting.BGL_Setting.isEnable>DISABLE?"开启":"关闭"); 
   sprintf(pStrBuf, "%d",mntSetting.BGL_Setting.Dist);
   EDIT_SetText(hEts[2], pStrBuf); 
   EDIT_SetText(hEts[3], mntSetting.BGL_Setting.isSndEnable>DISABLE?"开启":"关闭"); 
   EDIT_SetText(hEts[4], mntSetting.DRG_Setting.isEnable>DISABLE?"开启":"关闭"); 
   sprintf(pStrBuf, "%d",mntSetting.DRG_Setting.Dist);
   EDIT_SetText(hEts[5], pStrBuf);  
   EDIT_SetText(hEts[6], mntSetting.DRG_Setting.isSndEnable>DISABLE?"开启":"关闭");    
}





/*************************** End of file ****************************/
