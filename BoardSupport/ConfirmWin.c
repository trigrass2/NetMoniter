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

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0      (GUI_ID_USER + 0x00)
#define ID_BUTTON_OK     (GUI_ID_USER + 0x01)
#define ID_BUTTON_CANCEL (GUI_ID_USER + 0x02)
#define ID_TEXT_CONTENT  (GUI_ID_USER + 0x03)


/*------------------------- external variables -------------------------*/
extern short N_monitedBoat;
extern WM_HWIN menuWin;
extern WM_HWIN subWins[4];
extern WM_HWIN confirmWin;
extern MNT_BOAT MNT_Boats[MNT_NUM_MAX];
extern MNT_SETTING mntSetting;

extern SIMP_BERTH Simp_Berthes[BOAT_LIST_SIZE_MAX];

/*------------------------- external functions -------------------------*/
//extern int MNT_deleteByIndex(MNT_BOAT * pMNT_Boat,int index, long id);
extern int MNT_deleteById(MNT_BOAT * pMNT_Boat, long id);



/*------------------------- local variables ----------------------------*/
static WM_HWIN dlgFrame;
static WM_HWIN dlgTextContent;
static WM_HWIN dlgBtOk;
static WM_HWIN dlgBtCancel;
static int userMsgChoose  = 0;
static WM_HWIN myHWinSrc;
static long ReceivedDatas[3] = {0};
static int Option  = 0;
static WM_MESSAGE myMsg;

/*------------------------- local functions -----------------------------*/
void mySB(WM_MESSAGE * pMsg);
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
  { WINDOW_CreateIndirect, "Win_Confirm", ID_WINDOW_0, 200, 120, 400, 240, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "OK", ID_BUTTON_OK, 40, 100, 80, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Cancel", ID_BUTTON_CANCEL, 280, 100, 80, 40, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_CONTENT, 40, 20, 319, 45, 0, 0x64, 0 },
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
  WM_HWIN thisFrame  = pMsg->hWin;

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
//    
//    FRAMEWIN_SetText(thisFrame, " Confirm?");
//    FRAMEWIN_SetTitleHeight(thisFrame, 20);
    //
    // Initialization of 'bt_OK'
    //
    dlgBtOk = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_OK);
//    WM_SetCallback(dlgBtOk, &mySB);
    BUTTON_SetText(dlgBtOk, "OK");
	   BUTTON_SetFont(dlgBtOk, GUI_FONT_16_1);
    //
    // Initialization of 'bt_Cancle'
    //
    dlgBtCancel = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_CANCEL);
    BUTTON_SetText(dlgBtCancel, "Cancle");
	   BUTTON_SetFont(dlgBtCancel, GUI_FONT_16_1);
    //
    // Initialization of 'Text'
    //
    dlgTextContent = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CONTENT);
    TEXT_SetText(dlgTextContent, "Confirm the changes?");
    TEXT_SetFont(dlgTextContent, GUI_FONT_16_1);
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
//   case GUI_KEY_ENTER:
//INFO("case enter");   
//        break;
			
			default:
				break;
		}
		break;
		
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);    // Id of widget
    NCode = pMsg->Data.v;               // Notification code
    switch (NCode) {
    
    case WM_NOTIFICATION_RELEASED:      // React only if released
      switch (Id) {
      case ID_BUTTON_OK:
//           switch(Option)
//           {
//              case CANCEL_MONITED:
//INFO("reach");              
//                   i  = MNT_deleteById(MNT_Boats, ReceivedDatas[2]);
//INFO("index:%d",i);                   
//                   MNT_Boats[i].pBoat->mntStates  = MNTState_None;
//                   WM_BringToBottom(pMsg->hWin);
//                   WM_SetFocus(menuWin);
//                   break;
//              
//              case STORE_SETTING:
//                   
//                   break;
//           }
INFO("case BUTTON_OK");
           myMsg.hWin     = myMsg.hWinSrc;
           myMsg.hWinSrc  = pMsg->hWin;
           myMsg.MsgId    = USER_MSG_ID_REPLY;
           myMsg.Data.v   = REPLY_OK;
           WM_SendMessage(myMsg.hWin, &myMsg);
           break;
      case ID_BUTTON_CANCEL:
           WM_SetFocusOnPrevChild(confirmWin);
//           switch(Option)
//           {
//              case CANCEL_MONITED:
//                   WM_BringToBottom(pMsg->hWin);
//                   WM_SetFocus(subWins[2]);
//                   break;
//           }
INFO("case BUTTON_CANCEL");
           myMsg.hWin     = myMsg.hWinSrc;
           myMsg.hWinSrc  = pMsg->hWin;
           myMsg.MsgId    = USER_MSG_ID_REPLY;
           myMsg.Data.v   = REPLY_CANCEL;
           WM_SendMessage(myMsg.hWin, &myMsg);
           break;
      }
      WM_BringToBottom(pMsg->hWin);
      break;
    }
    break;
  // USER START (Optionally insert additional message handling)
  case USER_MSG_ID_CHOOSE:
INFO("case user_msg_id_choose");  
      Option  = pMsg->Data.v;
      
      myMsg.hWinSrc  = pMsg->hWinSrc;
      myMsg.Data.v   = Option;
      
//      ReceivedDatas[2]  = ((long*)pMsg->Data.p)[2];
INFO("Option:%d",Option);      
//      myHWinSrc  = pMsg->hWinSrc;      
      switch(Option)   
      {
         case CANCEL_MONITED:
INFO("case cancel_monited");         
              TEXT_SetText(dlgTextContent, "Confirm cancel monited state?");
              userMsgChoose  = CANCEL_MONITED;
              break;
          
         case STORE_SETTING:
INFO("case store_setting");         
              userMsgChoose  = STORE_SETTING;
              TEXT_SetText(dlgTextContent, "Confirm changes?");         
              break;
              
         default:
INFO("Somethiing error!");         
              break;
      }
      break;
//      
//      WM_BringToTop(confirmWin);
//      WM_SetFocus(confirmWin);
      break;
//   case USER_MSG_ID_CHOOSE:
//        
//        break;
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
//  res = GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
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


