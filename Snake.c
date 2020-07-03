#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "Snake.h"

static int panelHandle;
int tabhandle0, tabhandle1, clk = 0,H,W,apple;
int snake_x,snake_y,dx=10,dy=10; // size of movment for the snake: snake_x is for X, and snake_y is for the Y, dx for movment step
double selection;

void DrawApple(Rect rect);
void DrawSnake(int x, int y); //makeing squre in the middle
void clearcanvas();
static void move_snake();
CmtThreadLockHandle lockhandle; // locking movement i think


int CVICALLBACK snakethread (void *callbackData);


/////////// Main Function
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Snake.uir", PANEL)) < 0)
		return -1;
	// TODO: Get the panel handle associated with a tab page with GetPanelHandleFromTabPage
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB, 0, &tabhandle0);
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB, 1, &tabhandle1);
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);

			break;
	}
	return 0;
}

int CVICALLBACK OkCallback (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK StartCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	
	
	double selection;
	switch (event)
	{
		case EVENT_COMMIT:
			//CanvasDrawRect (tabhandle0, GAMEPANEL_CANVAS, MakeRect(187,187,25,25), VAL_DRAW_FRAME);
			//Delay (0.5);
			if (!clk){
			GetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_HEIGHT, &H);
			GetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_WIDTH, &W);
			}
			clk=!clk;
			if (clk);{
				GetCtrlVal (tabhandle0, GAMEPANEL_BINARYSWITCH, &selection);
				SetCtrlAttribute (tabhandle0, GAMEPANEL_TIMER, ATTR_INTERVAL, selection);
				SetCtrlAttribute (tabhandle0, GAMEPANEL_TIMER, ATTR_ENABLED, clk);
				clearcanvas();
				snake_x = W/2;
				snake_y = H/2;
				DrawSnake(snake_x,snake_y);
				CmtNewLock(NULL,OPT_TL_SUPPORT_TIMEOUT, &lockhandle);
			}
				
			//CanvasClear (tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
			break;
	}
	return 0;
}


//next function must be uncomment to make it work
///////////// controlling the snake with arrows
int CVICALLBACK Snakefunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_KEYPRESS:
		{
			switch(eventData1)
			{
				case VAL_UP_ARROW_VKEY:
				{
					//CmtScheduleThreadPoolFunction (threadhandle, threadfunction3, NULL, &val1); // coppied from RAN
				}
				
				case VAL_DOWN_ARROW_VKEY:
				{
				//	CmtScheduleThreadPoolFunction (threadhandle, threadfunction4, NULL, &val1);// coppied from RAN
				}
					
			}
			
		}
		
		
	}
	
	
	
	return 0;
}


/*
VAL_UP_ARROW_VKEY = 0x0600
VAL_DOWN_ARROW_VKEY = 0x0700
VAL_LEFT_ARROW_VKEY = 0x0800
VAL_RIGHT_ARROW_VKEY = 0x0900
*/

int CVICALLBACK timer (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	//static int x = 187;
	//static int y = 187;
	//int character;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			//CanvasDrawRect (tabhandle0, GAMEPANEL_CANVAS, MakeRect(y,x,25,25), VAL_DRAW_FRAME);
		//	x = x + 25;
		//	CanvasClear (tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
		//	CanvasDrawRect (tabhandle0, GAMEPANEL_CANVAS, MakeRect(y,x,25,25), VAL_DRAW_FRAME);
			break;			

	}

	return 0;	
}

//// no need to write anything to that function now:
int CVICALLBACK difficulty (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}
int CVICALLBACK score (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void clearcanvas() {
	
	/// Draw canvas:
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, 0x00B0FFF);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, 0x00B0FFF);
	CanvasClear (tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
	
	/// Draw black line in left side:
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);
	CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(0,0, H,2), VAL_DRAW_INTERIOR);
	
	/// Draw black line in top side:
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);
	CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(0,0, 2,W), VAL_DRAW_INTERIOR);
	
	/// Draw black line in right side:
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);
	CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(0,W-2, H,2), VAL_DRAW_INTERIOR);
	
	/// Draw black line in bottom side:
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);
	CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(H-2,0, 2,W), VAL_DRAW_INTERIOR);
	
	CanvasUpdate (tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
}

/*
static void random_apple(){
	int eat;
	
	apple ;
}
*/

// func to make apple: equivalent to Ran's DrawWhiteRect:
/*
void DrawApple(Rect rect){
	
SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);	
SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);
CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, rect, VAL_DRAW_FRAME_AND_INTERIOR);
}
*/

// func to make a squre represent the snake: equivalent to Ran's DrawRightUser:
void DrawSnake (int X, int Y) {
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);	
	CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(Y/2-10 ,X/2-10 ,25 ,25 ), VAL_DRAW_FRAME_AND_INTERIOR);
	CanvasUpdate(tabhandle0,GAMEPANEL_CANVAS,VAL_ENTIRE_OBJECT);
}

// func to make the snake move to direction controlled by arrows, starting moving right: equivalent to Ran's move_ball:

static void move_snake(){
	
	  snake_x += dx;
	  snake_y += dy;
	  if (snake_x <= 0)
	  {
		 // score[1]+=1; //right
		//  sprintf(str2, "%d", score[1]);   
		  snake_x = W/2;
		  snake_y = H/2;
		  dy = 10*selection;
		  clearcanvas(); 
		  DrawSnake(snake_x, snake_y);
	  }
	  if (snake_x >= W)
	  {
		  //score[0]+=1; //left
		//  sprintf(str1, "%d", score[0]);
		  snake_x = W/2;
		  snake_y = H/2;
		  clearcanvas();
		  dy = 10*selection;
		  DrawSnake(snake_x, snake_y);
	  }
	   if (snake_y <=5 || snake_y >= H-5)
	   {
		  dy=-dy;
	   }
	
}


int CVICALLBACK snakethread (void *callbackData) {
	
	CmtGetLock(lockhandle);
	move_snake();
	CmtReleaseLock(lockhandle);
	return 0;
}
