#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "Snake.h"

static int panelHandle;
int tabhandle0, tabhandle1, clk = 0,H,W,apple;
int movex=25,movey=25; // size of movment for the snake: movex is for X, and movey is for the Y
//void DrawApple(Rect rect);
void DrawSnake(); //makeing squre in the middle
void clearcnvas();
static void move_snake();




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
				clearcnvas();
				DrawSnake(W,H);
			}
				
		
			//CanvasClear (tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
			
			break;
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

void clearcnvas() {
	
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
/*
static void move_ball(){
	
	
}

*/



// controlling the snake with arrows:
/*
int CVICALLBACK Snakefunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	return 0;
}
*/