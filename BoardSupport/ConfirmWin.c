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

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_1 (GUI_ID_USER + 0x02)
#define ID_TEXT_0 (GUI_ID_USER + 0x03)

extern short N_monitedBoat;


extern WM_HWIN menuWin;
extern WM_HWIN subWins[4];
extern WM_HWIN confirmWin;

void printMoniteSetting(void);
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
  { FRAMEWIN_CreateIndirect, "Frm_Confirm", ID_FRAMEWIN_0, 200, 120, 400, 240, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "OK", GUI_ID_OK, 40, 100, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Cancel", GUI_ID_CANCEL, 280, 100, 80, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 40, 20, 319, 45, 0, 0x64, 0 },
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
	
	const WM_KEY_INFO* pInfo;
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  int i  = 0;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Frm_Confirm'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetText(hItem, " Confirm?");
    FRAMEWIN_SetTitleHeight(hItem, 20);
    //
    // Initialization of 'bt_OK'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_OK);
    BUTTON_SetText(hItem, "OK");
	  BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'bt_Cancle'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_CANCEL);
    BUTTON_SetText(hItem, "Cancle");
	  BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetText(hItem, "Confirm the changes?");
    TEXT_SetFont(hItem, GUI_FONT_16_1);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
		
	case WM_KEY:
		pInfo  = (WM_KEY_INFO*)pMsg->Data.p;
	
	  switch(pInfo->Key)
		{
			case GUI_KEY_LEFT:
			case GUI_KEY_RIGHT:
				GUI_StoreKeyMsg(GUI_KEY_TAB,1);
			break;

			
			default:
				break;
		}
		break;
		
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case GUI_ID_OK: // Notifications sent by 'bt_OK'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:

        // USER START (Optionally insert code for reacting on notification message)
printf("\r\n");

//         for(i=0;i<N_monitedBoat;i++)
//         {
//            if(   (mntBoats[i].MNTState == MNTState_Choosen)
//                ||(mntBoats[i].MNTState == MNTState_Default)   )
//            {
////               if(mntBoats[i].MNTState == MNTState_Choosen)
//                  mntBoats[i].MNTState  = MNTState_Monite;
//               mntBoats[i].MNTSetting.DSP_Setting  = mntSetting.DSP_Setting;

//               mntBoats[i].MNTSetting.BGL_Setting.isEnable  = 
//                           mntSetting.BGL_Setting.isEnable;
//               mntBoats[i].MNTSetting.BGL_Setting.isSndEnable  = 
//                           mntSetting.BGL_Setting.isSndEnable;
//               mntBoats[i].MNTSetting.BGL_Setting.dist  = 
//                           mntSetting.BGL_Setting.dist;   
//               
//               mntBoats[i].MNTSetting.DRG_Setting.isEnable  = 
//                           mntSetting.DRG_Setting.isEnable;
//               mntBoats[i].MNTSetting.DRG_Setting.isSndEnable  = 
//                           mntSetting.DRG_Setting.isSndEnable;
//               mntBoats[i].MNTSetting.DRG_Setting.dist  = 
//                           mntSetting.DRG_Setting.dist;                 
//            }
//         }
//         

//         mntSetting_init();
//         printMoniteSetting();
//         
					WM_BringToBottom(pMsg->hWin);
					WM_SetFocus(menuWin);


        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case GUI_ID_CANCEL: // Notifications sent by 'bt_Cancle'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
	
					WM_BringToBottom(pMsg->hWin);
					WM_SetFocus(subWins[1]);
					/// Action cancel

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
*       CreateFrm_Confirm
*/
WM_HWIN confirmWinCreate(void);
WM_HWIN confirmWinCreate(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END




//static void myButtonListener(WM_MESSAGE* pMsg)
//{
//	const WM_KEY_INFO* pInfo;
//	WM_MESSAGE msg;
//	WM_HWIN thisButton = pMsg->hWin;
//	
//	msg.hWin  = WM_GetParent(thisButton);
//	msg.hWinSrc  = thisButton;
//	msg.MsgId  = WM_NOTIFY_PARENT;
//	msg.Data.v = GUI_ID_OK;
//	switch(pMsg->MsgId)
//	{
//		case WM_KEY:
//			pInfo  = (WM_KEY_INFO*)pMsg->Data.p;
//		
//		  switch(pInfo->Key)
//			{
//				case GUI_KEY_ENTER:
//					WM_SendToParent(thisButton,&msg);
//					break;
//			}
//	}
//}

/*************************** End of file ****************************/
/*
void printMoniteSetting()
{
   int i  = 0;
   int cnt  = 0;
   for(i=0;i<N_monitedBoat;i++)
   {
      if(mntBoats[i].MNTState == MNTState_None)
         cnt++;
      printf("\r\n");
      printf("%d-mmsi %ld\r\n",i,mntBoats[i].mmsi);
      printf("%d-name %s\r\n", i,mntBoats[i].name);
//      printf("   DSP     %s\r\n",mntBoats[i].MNTSetting.DSP_Setting.isEnable>DISABLE?"Enable":"Disable");
//      printf("   BGL     %s\r\n",mntBoats[i].MNTSetting.BGL_Setting.isEnable>DISABLE?"Enable":"Disable");
//      printf("       snd %s\r\n",mntBoats[i].MNTSetting.BGL_Setting.isSndEnable>DISABLE?"Enable":"Disable");
//      printf("      dist %d\r\n",mntBoats[i].MNTSetting.BGL_Setting.dist);
//      printf("   DRG     %s\r\n",mntBoats[i].MNTSetting.DRG_Setting.isEnable>DISABLE?"Enable":"Disable");
//      printf("       snd %s\r\n",mntBoats[i].MNTSetting.DRG_Setting.isSndEnable>DISABLE?"Enable":"Disable");
//      printf("      dist %d\r\n",mntBoats[i].MNTSetting.DRG_Setting.dist);
      printSetting(&(mntBoats[i].MNTSetting));
      printf("still hava %d is default\r\n",cnt);
   } 
}

void printSetting(MNT_SETTING * p_setting)
{
      printf("   DSP     %s\r\n",p_setting->DSP_Setting.isEnable>DISABLE?"Enable":"Disable");
      printf("   BGL     %s\r\n",p_setting->BGL_Setting.isEnable>DISABLE?"Enable":"Disable");
      printf("       snd %s\r\n",p_setting->BGL_Setting.isSndEnable>DISABLE?"Enable":"Disable");
      printf("      dist %d\r\n",p_setting->BGL_Setting.dist);
      printf("   DRG     %s\r\n",p_setting->DRG_Setting.isEnable>DISABLE?"Enable":"Disable");
      printf("       snd %s\r\n",p_setting->DRG_Setting.isSndEnable>DISABLE?"Enable":"Disable");
      printf("      dist %d\r\n",p_setting->DRG_Setting.dist);
}

*/