#include "drawThings.h"
#include "Setting.h"
#include "skinColor.h"
#include "mapWin.h"
#include "str.h"
#include "28.h"
#include "Compass.c"
#include "map.h"

/*--------------------------------- Macro defines -------------------------------------*/
#define MYABS(x)   ((x)>0?(x):(-(x)))


/*-------------------------------- External variables ---------------------------------*/
extern SIMP_BERTH SimpBerthes[BOAT_NUM_MAX];
extern int N_boat;
extern boat mothership;
extern char scale_choose;

/*-------------------------------- Local variables ------------------------------------*/
static GUI_POINT * pPoints  = Points_fish;
static  int PointNum  = 11;

static const MapWin_COLOR * pSkin  = mapSkins;



/** @brief   Draw_ScaleRuler
 *
 *  @dscrp:  Draw scale on map in mapWin.
 *  @input:  Current scale .
 *  @output:
 *  @return:
 */
static void draw_scale(const map_scale * pScale)
{
 uint16_t length  = 0;
 
 if(SysConf.Unit==UNIT_nm)
 {
    length  = pScale->pixel;
 }
 else 
 {
    length  = pScale->pixel * 5 /9;
 }

	GUI_SetColor(pSkin->sclColor);
 GUI_SetPenSize(1);
 GUI_SetLineStyle(GUI_LS_SOLID);
 
 GUI_DrawLine(800-160, 480-10,  800-160+length, 480-10);
 GUI_DrawLine(800-160, 480-10,  800-160, 480-20);
 GUI_DrawLine(800-160+length, 480-10, 800-160+length, 480-20);
 sprintf(pStrBuf, "%ld.%ld%s",pScale->minute/1000,(pScale->minute%1000)/100,SysConf.Unit==UNIT_nm?"nm":"km");
 GUI_DispStringAt(pStrBuf, 800-160+10, 480-10-20);

}

void setBoatSkin(SKINS skin)
{
   pSkin  = &(mapSkins[skin]);
}

void setShape(BOAT_SHAPES shape)
{
   if(shape == SHAPE_Boat)
   {
      pPoints  = Points_boat;
      PointNum  = 3;
   }
   else 
   {
      pPoints  = Points_fish;
      PointNum  = 11;
   }
}

static void fixPos(short * base_x, short * base_y)
{
   if(*base_x + 10  > MAP_RIGHT-180)
   {
      *base_x  = *base_x-10-180;
   }
   else
   {
      *base_x  = *base_x+10;
   }
   
   if(*base_y+10 > MAP_BOTTOM-80)
   {
      *base_y  = *base_y-10-80;
   }
   else
   {
      *base_y  = *base_y+10;
   }
}



static void draw_boatInfo( short base_x, short base_y, boat * pBoat)
{
   if(pBoat == NULL)
      return ;

   fixPos(&base_x, &base_y);

   GUI_SetColor(pSkin->bkColor);

   GUI_ClearRect(base_x, base_y-20, base_x+180,base_y+80);
   
   GUI_SetColor(pSkin->map_tip_Text);
 
   GUI_SetFont(&GUI_Font16_1);
   GUI_DispStringAt(pBoat->name, base_x+10, base_y+1); 
   
   GUI_SetColor(pSkin->map_tip_Text);
   GUI_SetFont(&GUI_Font24_1);
   
   lltostr(pBoat->latitude, pStrBuf);
   GUI_DispStringAt(pStrBuf, base_x+10, base_y+16);
   
   lltostr(pBoat->longitude, pStrBuf);
   GUI_DispStringAt(pStrBuf, base_x+10, base_y+38);
   

   GUI_SetFont(&GUI_Font16_1);
   sprintf(pStrBuf, "%09ld", pBoat->user_id);
   GUI_DispStringAt(pStrBuf, base_x+10, base_y+62);
}



static void draw_boat(boat* pBoat,short basePoint_x,short basePoint_y,  const GUI_POINT * pPoints, const int count){

   GUI_POINT aEnlargedPoints[11];

   if(pBoat == NULL)
      return ;
   
   GUI_RotatePolygon(aEnlargedPoints,pPoints,count,pBoat->COG*3.14/180);

//   if((basePoint_x >=MAP_LEFT)&&(basePoint_x<= MAP_RIGHT)&&(basePoint_y >=MAP_TOP)&&(basePoint_y <= MAP_BOTTOM))
//   {
     GUI_DrawPolygon(aEnlargedPoints,count,basePoint_x,basePoint_y);
//   }
}


//void drawColrofulBoat(boat * pBoat, short basePoint_x, short basePoint_y, const GUI_POINT * pPoints, const int count, GUI_COLOR color)
//{
//	GUI_POINT aEnlargedPoints[11];

// if(pBoat == NULL)
//    return;
// 
// GUI_SetColor(color);
//	GUI_RotatePolygon(aEnlargedPoints,pPoints,count,pBoat->COG*3.14/180);

//	if((basePoint_x >=MAP_LEFT)&&(basePoint_x<= MAP_RIGHT)&&(basePoint_y >=MAP_TOP)&&(basePoint_y <= MAP_BOTTOM))
// {
//	  GUI_DrawPolygon(aEnlargedPoints,count,basePoint_x,basePoint_y);
// }

//}


static void draw_mothership(const long lg, const long lt,const map_scale * pScale)
{
   short basePoint_x  = 0;
   short basePoint_y  = 0;
   
   GUI_POINT aEnlargedPoints[GUI_COUNTOF(bPoints)];
   
   basePoint_x  = (mothership.longitude-lg) * pScale->pixel / pScale->minute;
   basePoint_y  = (mothership.latitude -lt) * pScale->pixel / pScale->minute;
  	
	  basePoint_x  = (MAP_LEFT/2 + MAP_RIGHT/2) + basePoint_x;
	  basePoint_y  = (MAP_TOP/2 + MAP_BOTTOM/2) - basePoint_y;
	
  	GUI_RotatePolygon(aEnlargedPoints,bPoints,GUI_COUNTOF(bPoints),mothership.COG*3.14/180);
	  
	  if(     (basePoint_x>= MAP_LEFT)  &&  (basePoint_x <= MAP_RIGHT) 
						&&  (basePoint_y >= MAP_TOP)  &&  (basePoint_y <= MAP_BOTTOM)  )
		 {
      GUI_SetColor(pSkin->boat_Mom);
      GUI_SetPenSize(MM_BOAT_PENSIZE);
      
      GUI_DrawPolygon(aEnlargedPoints,GUI_COUNTOF(bPoints),basePoint_x, basePoint_y);
      draw_boatInfo(basePoint_x, basePoint_y, &mothership); 
	 	}
}



static void disp_boat(const long lg, const long lt, const map_scale * pScale,short N){
	
	short i=0;
 short base_x = 0;
 short base_y = 0;
 
 GUI_SetColor(BGL_BOAT_COLOR);
	for(i=0;i<N;i++)
	{
    base_x  = pScale->pixel * (SimpBerthes[i].longitude-lg) / pScale->minute;
			 base_y  = pScale->pixel * (SimpBerthes[i].latitude-lt) / pScale->minute;
    
    base_x  = (MAP_LEFT/2 + MAP_RIGHT/2) + base_x;
    base_y  = (MAP_TOP/2 + MAP_BOTTOM/2) - base_y;    

    if(SimpBerthes[i].pBerth->Boat.target)
    {
       if((base_x >=MAP_LEFT)&&(base_x<= MAP_RIGHT)&&(base_y >=MAP_TOP)&&(base_y <= MAP_BOTTOM))
       {
          draw_boat(&SimpBerthes[i].pBerth->Boat, base_x, base_y, Points_boat, 3);
       }        
    }
	}
}





static void disp_mntBoat(const long center_lg,const long center_lt, const map_scale* pScale)
{
   short base_x  = 0;
   short base_y  = 0;

   MNT_BERTH * pIterator  = pMntHeader;
   
   while(pIterator)
   {
      if(pIterator->pBoat)
      {
         base_x  = pScale->pixel * (pIterator->pBoat->longitude - center_lg) / pScale->minute;
         base_y  = pScale->pixel * (pIterator->pBoat->latitude - center_lt) / pScale->minute;
         
         base_x  = (MAP_LEFT/2 + MAP_RIGHT/2) + base_x;
         base_y  = (MAP_TOP/2 + MAP_BOTTOM/2) - base_y;
    
         GUI_SetColor(pSkin->boat_Org);    
         GUI_SetPenSize(2); 
         
///   DSP boat conf.      
         if(pIterator->mntBoat.mntSetting.DSP_Setting.isEnable == ENABLE) 
         {
            GUI_SetColor(pSkin->boat_Dsp);    
         }
         if((base_x >=MAP_LEFT)&&(base_x<= MAP_RIGHT)&&(base_y >=MAP_TOP)&&(base_y <= MAP_BOTTOM))
         {
            draw_boat(pIterator->pBoat, base_x, base_y,pPoints, PointNum);
            draw_boatInfo(base_x, base_y, pIterator->pBoat);
         }         
        
         
///   BGL circle conf.
         if(pIterator->mntBoat.mntSetting.BGL_Setting.isEnable == ENABLE)
         {
            GUI_SetColor(pSkin->boat_Bgl);
            GUI_SetPenSize(1); 
            
            GUI_DrawCircle(base_x, base_y,pIterator->mntBoat.mntSetting.BGL_Setting.Dist*pScale->pixel/pScale->minute);            
         } 
    
///   Drg circle conf. 
         if(pIterator->mntBoat.mntSetting.DRG_Setting.isEnable == ENABLE)
         {
            base_x  = pScale->pixel * (pIterator->mntBoat.lg - center_lg) / pScale->minute;
            base_y  = pScale->pixel * (pIterator->mntBoat.lt - center_lt) / pScale->minute;
            
            base_x  = (MAP_LEFT/2 + MAP_RIGHT/2) + base_x;
            base_y  = (MAP_TOP/2 + MAP_BOTTOM/2) - base_y;
            
            GUI_SetColor(pSkin->boat_Drg);
            GUI_SetPenSize(DRG_PENSIZE);        
            GUI_DrawCircle(base_x, base_y, pIterator->mntBoat.mntSetting.DRG_Setting.Dist*pScale->pixel/pScale->minute);
         }
      }
      else
      {
         base_x  = pScale->pixel * (pIterator->mntBoat.lg - center_lg) / pScale->minute;
         base_y  = pScale->pixel * (pIterator->mntBoat.lt - center_lt) / pScale->minute;
         
         base_x  = (MAP_LEFT/2 + MAP_RIGHT/2) + base_x;
         base_y  = (MAP_TOP/2 + MAP_BOTTOM/2) - base_y; 
      
         GUI_SetColor(GUI_YELLOW);      
         GUI_DrawCircle(base_x, base_y, 20);
      }
      pIterator  = pIterator->pNext;
   }
}



/**@brief 画map中的网格线
*
*
*/
static void draw_map_grid(mapping gridAnchor,const map_scale * pScale)
{
   short x = 0;
   short y = 0;

   x  = gridAnchor.x;
   y  = gridAnchor.y;
   
   GUI_SetLineStyle(GUI_LS_DASH);
   GUI_SetColor(pSkin->map_Grid);
     
   
   while(x<MAP_LEFT)
   {
      x  += pScale->pixel;
   }
   while(x<MAP_RIGHT)
   {
      GUI_DrawLine(x, MAP_TOP, x, MAP_BOTTOM);
      x  += pScale->pixel;
   }
   
   while(y<MAP_TOP)
   {
      y  += pScale->pixel;
   }
   while(y<MAP_BOTTOM)
   {
      GUI_DrawLine(MAP_LEFT, y, MAP_RIGHT, y);
      y  += pScale->pixel;
   }
}





static unsigned int getAreaIdByLL(long lg,  long lt)
{
   int i  = 0;
   int diffCnt  = 0;
   int fishingAreaId  = 0;

   
   if(lg < 6360000 || lg >=7890000 || lt <= 210000 || lt > 2460000)
   {
      return 0;
   }
   
   for(i=0; i<N_areaRecord; i++)
   {
      /// Find record lt of whihc contains lt
      if(lt > fishingAreaRecord[i].lt-29999)
      {  
         if(lt > fishingAreaRecord[i].lt)      
         {
            return 0;
         }
         /// Not on left of org.
         if(lg >= fishingAreaRecord[i].lg)
         {
            diffCnt  = (lg-fishingAreaRecord[i].lg) / 30000 + 1;
            
            /// On org area.
            if(diffCnt <= fishingAreaRecord[i].orgAreaNum)
            {
               fishingAreaId  = fishingAreaRecord[i].bgnId+diffCnt-1;
                     return fishingAreaId;
//               return (fishingAreaRecord[i].bgnId+diffCnt);
            }
            /// On exp area   
            else if(diffCnt <= fishingAreaRecord[i].expAreaNum+fishingAreaRecord[i].orgAreaNum)
            {
               /// In unmasked exp area
               if(   diffCnt > fishingAreaRecord[i].orgAreaNum+fishingAreaRecord[i].expMaskIdR  
                  || diffCnt < fishingAreaRecord[i].orgAreaNum+fishingAreaRecord[i].expMaskIdL )  
               {
                  if(fishingAreaRecord[i].bgnId+fishingAreaRecord[i].orgAreaNum-1 < 99)
                     fishingAreaId  = (fishingAreaRecord[i].bgnId+fishingAreaRecord[i].orgAreaNum-1) * 100 + diffCnt-fishingAreaRecord[i].orgAreaNum;
                  else
                     fishingAreaId  = (fishingAreaRecord[i].bgnId+fishingAreaRecord[i].orgAreaNum-1) * 10 + diffCnt-fishingAreaRecord[i].orgAreaNum;                   
                  return fishingAreaId;
               }
               /// In masked exp area.
               else
               {
                  return 0;
               }
            }
            /*
            else
            {
               continue;
            }
            */
         }
         /// On left of org means out out fishing area.
         else
         {
            return 0;
         }
      }
//      else 
//      {
//         return 0;
//      }
   }
}

/*
static unsigned int getFishingAreaId(long longitude, long latitude )
{
   int index  = 0;
   int counterAreaNum  = 0;
   int originalAreaNum  = 0;
   unsigned int fishingAreaId  = 0;
   unsigned int exp_id  = 0;
   
   int row  = 0;
   int col  = 0;
	
   if(fishing_area[index].latitude_fish < latitude)
      return 0;
	
   for(index=0;index < num_fish;)
   {
      if(fishing_area[index].latitude_fish<latitude)
      {
         index--;
         
         if(longitude < fishing_area[index].longitude_fish)
            return 0;

         ///不含拓展渔区的渔区数量,即原有渔区数量
         counterAreaNum  = (longitude-fishing_area[index].longitude_fish ) / distance;
         originalAreaNum  = fishing_area[index+1].fish_number - fishing_area[index].fish_number;
          
         if(counterAreaNum < originalAreaNum)			
            fishingAreaId = fishing_area[index].fish_number + counterAreaNum;
         else if(counterAreaNum < originalAreaNum+fishing_area[index].exp_num)
            fishingAreaId  = (fishing_area[index].fish_number+originalAreaNum-1)*10 + counterAreaNum-originalAreaNum+1;
         else
            fishingAreaId  = 0;
         
         if( (scale_choose==1) && (fishingAreaId!=0))
         {
            row  = (fishing_area[index].latitude_fish-latitude)/10000 ;
            col  = (longitude-fishing_area[index].longitude_fish)%30000 /10000 + 1;
            exp_id  = row*3+col;
            exp_id  = exp_id<<(sizeof(int)-4);
            fishingAreaId  = fishingAreaId | exp_id<<(8*sizeof(int)-4);
         }
         return fishingAreaId;
      }
      else
      {
         index++;
      }
   }
   
	  return 0;
}
*/


static void disp_map(const long longitude, const long latitude,const map_scale * pScale)
{
   unsigned int exp_id  = 0;   
   int row  = 0;
   int col  = 0;   
    
  
   short tmp_x = 0;
   short tmp_y = 0;
   
   long tmp_lttude  = 0;
   long tmp_lgtude  = 0;
  
   unsigned int fishingAreaId  = 0;
   
  ///画map的锚点
   mapping  anchor;
   
   short shift_x  = (pScale->pixel>>1) - 16;
   short shift_y  = (pScale->pixel>>1)- 8;
   
   anchor.lgtude  = longitude;
   anchor.lttude  = latitude;

   anchor.x  = (MAP_LEFT+MAP_RIGHT)/2 - (anchor.lgtude%pScale->minute) / (pScale->minute/pScale->pixel);
   anchor.y  = (MAP_TOP +MAP_BOTTOM)/2 + (anchor.lttude%pScale->minute) / (pScale->minute/pScale->pixel);
   anchor.lgtude  = anchor.lgtude - (anchor.lgtude%pScale->minute);
   anchor.lttude  = anchor.lttude - (anchor.lttude%pScale->minute);

	  while(anchor.x  >= MAP_LEFT+(pScale->pixel-shift_x))
		 {
			   anchor.x  -= pScale->pixel;
			   anchor.lgtude -= pScale->minute;
		 }
		 while(anchor.y  > MAP_TOP+(pScale->pixel-shift_y))
		 {
			   anchor.y  -= pScale->pixel;
			   anchor.lttude  += pScale->minute;
		 }
		  
		 draw_map_grid(anchor, pScale);
		 
		 tmp_x  = anchor.x;
		 tmp_y  = anchor.y;
		 tmp_lgtude  = anchor.lgtude;
		 tmp_lttude  = anchor.lttude;

		 GUI_SetColor (pSkin->net_lab);  
   GUI_SetFont(&GUI_Font16B_1);
   
   
   for(tmp_y=anchor.y;tmp_y<=MAP_BOTTOM;)			 
		 {				 
      if(scale_choose <=  1)
      {
         tmp_x  = anchor.x;
         tmp_lgtude  = anchor.lgtude ;
         
         for(tmp_x=anchor.x; tmp_x<=MAP_RIGHT-(pScale->pixel - shift_x);)
         {
//            fishingAreaId  = getFishingAreaId(tmp_lgtude, tmp_lttude);         
            fishingAreaId  = getAreaIdByLL(tmp_lgtude, tmp_lttude);         
            if(measuring_scale[1].minute == pScale->minute  && (0 != fishingAreaId))
            {
               if( 1000 > fishingAreaId)
               {
                  GUI_DispDecAt(fishingAreaId, tmp_x+shift_x, tmp_y+shift_y, 3);							 
               }
               else
               {
                  GUI_DispDecAt(fishingAreaId, tmp_x+shift_x, tmp_y+shift_y, 4);
               }
               row  = ((fishingAreaRecord[0].lt - tmp_lttude) % 30000) / 10000;
               col  = (tmp_lgtude % 30000) / 10000;
               exp_id  = row*3+col+1;                                          
               GUI_DispChar('_' );
               GUI_DispDec(exp_id, 1);							 							 
            }
            else if((measuring_scale[0].minute == pScale->minute) && (0 != fishingAreaId))
            {
               if(1000 > fishingAreaId)
               {
                  GUI_DispDecAt(fishingAreaId, tmp_x+shift_x+10, tmp_y+shift_y, 3);							 
               }
               else
               {
                  GUI_DispDecAt(fishingAreaId, tmp_x+shift_x+10, tmp_y+shift_y, 4);
               }
            }
           
            tmp_x  += pScale->pixel;
            tmp_lgtude  += pScale->minute;
         }					 
      }
      if( (tmp_y+latitude_display_y_shift) >= MAP_TOP )
      {
        lltostr(tmp_lttude,pStrBuf);
        GUI_DispStringAt(pStrBuf, MAP_RIGHT+latitude_display_x_shift,tmp_y+latitude_display_y_shift);         
      }		 
      tmp_y  += pScale->pixel;
      tmp_lttude  -= pScale->minute;
			 }
    
    
}



static void getMntWrapPara(long *halfDiff_lg, long* halfDiff_lt, map_scale* pScale)
{  
   long min_lg  = mothership.longitude;
   long max_lg  = mothership.longitude;
   long min_lt  = mothership.latitude;
   long max_lt  = mothership.latitude;
   
   long maxDiff_lg  = 0;
   long maxDiff_lt  = 0;
   
   
   MNT_BERTH * pIterator  = pMntHeader;
   
   
   while(pIterator)
   {
      if( pIterator->pBoat && (pIterator->pBoat->latitude) && (pIterator->pBoat->longitude) )
      {
         if(pIterator->pBoat->latitude < min_lt)
         {
            min_lt  = pIterator->pBoat->latitude;
         }
         else if(pIterator->pBoat->latitude > max_lt)
         {
            max_lt  = pIterator->pBoat->latitude;
         }
         
         if(pIterator->pBoat->longitude < min_lg)
         {
            min_lg  = pIterator->pBoat->longitude;
         }
         else if(pIterator->pBoat->longitude > max_lg)
         {
            max_lg  = pIterator->pBoat->longitude;
         }
      }
      pIterator  = pIterator->pNext;
   }
   
   maxDiff_lg  = max_lg - min_lg + 1000;
   maxDiff_lt  = max_lt - min_lt + 1000;
   
   *halfDiff_lg  = max_lg/2 + min_lg/2;
   *halfDiff_lt  = max_lt/2 + min_lt/2;
   
   
   ///map的宽为800pix，高为400pix，判断在适配上述区域时以map的宽来适配还是高来适配
   
   ///若适配区域的宽度大于高度的两倍，则以map的宽来适配
    if(( maxDiff_lg/2) > maxDiff_lt)
    {
       pScale->minute  = ( maxDiff_lg/(8*100) + 1)*100;  ///这种写法保证所得到的scale.minute为100的整数倍
    }
    ///否则以map的高来适配
    else
    {
       pScale->minute  = ( maxDiff_lt/(4*100) + 1)*100;
    }
}


void setView(const long lg, const long lt, const map_scale* pScale)
{
   disp_map(lg, lt, pScale);
   disp_mntBoat(lg,lt,pScale);
   disp_boat(lg,lt,pScale, N_boat);  
   draw_mothership(lg,lt, pScale);
   draw_scale(pScale);
}



void setAutoView()
{
   long lg  = 0;
   long lt  = 0;
   map_scale autoScale;
   
   autoScale.pixel  = 100;
   getMntWrapPara(&lg, &lt, &autoScale); 
   
   disp_map(lg, lt, &autoScale);
   disp_mntBoat(lg, lt, &autoScale);  
   disp_boat(lg, lt, &autoScale, N_boat);
   draw_mothership(lg,lt,&autoScale);
   draw_scale(&autoScale);
}