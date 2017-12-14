#include <stdio.h>
#include <conio.h>
#include "console.h"
#include <iostream>
#include <string>
using namespace std;


void hiencontro()
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = TRUE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}
void ancontro()
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}

//-------------------------Screen-------------------------
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0, 0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}


//screen: goto [x,y]
void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
#define i0 i==0
#define i1 i==1
#define i2 i==2 
#define i3 i==3 
#define i4 i==4 
#define i5 i==5
#define i6 i==6 
#define i7 i==7 
#define iH i==HiK-1
#define i31 i%3==1
#define i61 i%6==1
#define j0 j==0
#define j1 j==1 
#define j2 j==2 
#define j3 j==3 
#define j4 j==4 
#define j5 j==5 
#define j6 j==6 
#define j7 j==7 
#define jW j==WiK-1
#define j61 j%6==1
#define j31 j%3==1
#define usqua !(j61&&i61)
#define notdraw !(i0 || iH || j0 || jW)
void drawkeyspecial(string str, int x, int y){
	return drawkeyspecial(str, x, y, 9 + 16 * 14, 4 + 16 * 11, '*');
}
void drawkeyspecial(string str, int x, int y, int coText, int coBG, int mode){
	str += " ";
	int n = str.length();
	x -= 9;
	int x0 = x;
	bool isSpe = false;
	for (int i = 0; i < n; i++)
	{
		if (str[i] == '~'){
			x += 9;
			switch (str[i + 1]){
			case 'W':case 'w':
				isSpe = true;
				for (int i = 0; i < HiK; i++)
				{
					for (int j = 0; j < WiK; j++)
					{
						gotoXY(x + j, y + i);
						if (notdraw && (j4||(i2&&(j3||j5))||(i3&&(j6||j2)))
							){
							TextColor(coText);
							putchar(mode);
						}
						else { TextColor(coBG); putchar(' '); }


					}
				}

				break;
			case 'S':case's':
				isSpe = true;
					for (int i = 0; i < HiK; i++)
					{
						for (int j = 0; j < WiK; j++)
						{
							gotoXY(x + j, y + i);
							if (notdraw && (j4 || (i6 && (j3 || j5)) || (i5 && (j6 || j2)))
								){
								TextColor(coText);
								putchar(mode);
							}
							else { TextColor(coBG); putchar(' '); }


						}
					}
					
					break;
			case 'D':case'd':
				isSpe = true;
				for (int i = 0; i < HiK; i++)
				{
					for (int j = 0; j < WiK; j++)
					{
						gotoXY(x + j, y + i);
						if (notdraw && (i4 || (j6 && (i3 || i5)) || (j5 && (i6 || i2)))
							){
							TextColor(coText);
							putchar(mode);
						}
						else { TextColor(coBG); putchar(' '); }


					}
				}
			
				break;
			case 'a':case'A':
				isSpe = true;
				for (int i = 0; i < HiK; i++)
				{
					for (int j = 0; j < WiK; j++)
					{
						gotoXY(x + j, y + i);
						if (notdraw && (i4  || (j2 && (i3 || i5)) || (j3 && (i6 || i2)))
							){
							TextColor(coText);
							putchar(mode);
						}
						else { TextColor(coBG); putchar(' '); }


					}
				}

				break;
			case 'x':case'X':
				isSpe = true;
				for (int i = 0; i < HiK; i++)
				{
					for (int j = 0; j < WiK; j++)
					{
						gotoXY(x + j, y + i);
						if (notdraw && (i61||j61||i==j||i+j==8)
							){
							TextColor(coText);
							putchar(mode);
						}
						else { TextColor(coBG); putchar(' '); }


					}
				}

				break;
			case 'z':case'Z':
				isSpe = true;
				for (int i = 0; i < HiK; i++)
				{
					for (int j = 0; j < WiK; j++)
					{
						gotoXY(x + j, y + i);
						if (notdraw && (i31||j31)
							){
							TextColor(coText);
							putchar(mode);
						}
						else { TextColor(coBG); putchar(' '); }


					}
				}

				break;
			case '~':
				isSpe = true;
				drawkey('~', x , y, coText, coBG, mode);
				break;
			case ' ':
				isSpe = true;
				for (int i = 0; i < HiK; i++)
				{
					for (int j = 0; j < WiK; j++)
					{
						gotoXY(x + j, y + i);
						if (notdraw && ((i+j)%2==0)&&i!=j
							){
							TextColor(coText);
							putchar(mode);
						}
						else { TextColor(coBG); putchar(' '); }


					}
				}

				break;
			case 'o':
				isSpe = true;
				for (int i = 0; i < HiK; i++)
				{
					for (int j = 0; j < WiK; j++)
					{
						gotoXY(x + j, y + i);
						if (notdraw && (i4||((i3||i5)&&(j2||j6))||((i2||i6)&&(j5||j3)))
							){
							TextColor(coText);
							putchar(mode);
						}
						else { TextColor(coBG); putchar(' '); }


					}
				}

				break;
			}
		}
		else if (isSpe == true){  isSpe = false; }
		else
		if (str[i] == '\n'){ x = x0;  y = 9 + y; continue; }
		else drawkey(str[i], x += 9, y, coText, coBG, mode);
	}
}
void drawkey(char key, int x, int y, int coText, int coBG, int mode){
	switch (key){ 
	case '~':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && ((i4 && (j61 || j4)) || (i3 && (j2 || j3)) || (i5 && (j5 || j6)))
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }


			}
		}
		return;
	case '*': for (int i = 0; i < HiK; i++)
	{
				  for (int j = 0; j < WiK; j++)
				  {
					  gotoXY(x + j, y + i);
					  if (notdraw && (j4 || i4 || i == j || i + j == 8) && !(i4&&j4)
						  ){
						  TextColor(coText);
						  putchar(mode);
					  }
					  else { TextColor(coBG); putchar(' '); }


				  }
	}
			  return;
	case ' ':
		return;
	case 'A':case'a':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i5 || (j4&&i1) || ((i6 || i7) && j61) || (i4 && (j2 || j6)) || ((j3 || j5) && (i2 || i3))) && !(i5&&j61)
					/*(j1 || j7 || i1 || i4) && !(i1 && (j1||j7))*/
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }


			}
		}
		return;
	case 'B':case 'b':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i31 || j61) && !(j7 && i31)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'C':case'c':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (j1 || i61 || (j7 && (i2 || i6))) && usqua
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;

	case 'D':case'd':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (j61 || i61) && !(j7 && i61)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'E':case'e':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (j1 || i31 || (j7 && (i2 || i6))) && usqua&&!(i4&&j7)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'F':case'f':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (j1 || i1 || i4) && !(i1&&j1) && !(j7&&i4)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'G':case 'g':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i31 || j61) && usqua && !(i4 && (j2 || j3 || j7)) && !(j7&&i3)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'H':case 'h':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (j61 || i4)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;

	case 'I':case 'i':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i61 || j4)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'J':case 'j':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i1 || j4 || (i7 && (j2 || j3)) || (j1&&i6)) && !(j4&&i7)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'K':case 'k':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (j1 || (i4 && (j2 || j3 || j4)) || (j5 && (i3 || i5)) || (j6 && (i2 || i6)) || (j7 && (i1 || i7)))
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'L':case 'l':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i7 || j1)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'M':case 'm':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (j61 || ((i + j == 8) || (i == j)) && (i<5))
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'N':case 'n':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (j61 || i == j)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'O':case 'o':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i61 || j61 || i + j == 8) && usqua
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'P':case 'p':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (j1 || i1 || i4 || (j7 && (i2 || i3))) && !(j7 && (i1 || i4))
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'Q':case 'q':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i61 || j61 || (i == j&&i>3)) && !(i7&&j6) && !(i6&&j7) && !(i1 && j61) && !(i7&&j1)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'R':case 'r':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i1 || i4 || j1 || (i == j&&i>3) || (j7&&i<4)) && !(j7 && (i1 || i4))
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'S':case 's':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i31 || j61) && usqua&&!(j1 && (i4 || i5)) && !(j7 && (i3 || i4))
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'T':case 't':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i1 || j4)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'U':case 'u':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (j61 || i7) && !(i7 && j61)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'V':case 'v':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && ((j61 && (i<5)) || (i6 && (j3 || j5)) || (j4&&i7) || (i5 && (j2 || j6)))
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'W':case 'w':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (j61 || (i7 && (j2 || j6)) || (j4 && (i4 || i5)) || (i6 && (j3 || j5))) && !(i7 && j61)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'X':case 'x':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i + j == 8 || i == j)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'Y':case 'y':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (((i == j || i + j == 8) && i<4) || (j4&&i>3))
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case 'Z':case 'z':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i61 || i + j == 8)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '0':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i61 || j61) && usqua
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '1':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i7 || j4 || i + j == 5)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '2':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i31 || j61) && !((i1 || i4) && j61) && !(j7&&i5) && !(j1&&i3)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '3':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i31 || j61) && !(j61&&i31)&!(j1 && (i3 || i5))
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '4':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i + j == 5 || i5 || j5)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '5':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i31 || j1 || (j7 && (i5 || i6))) && !(j1 && (i4 || i5 || i7)) && !(j7 && i7)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '6':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i31 || j61) && usqua&&!(j7 && (i3 || i4))
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '7':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i1 || i + j == 8)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '8':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i31 || j61) && usqua&&!(i4&&j61)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '9':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i31 || j61) && usqua&&!(j1 && (i4 || i5))
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '?':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && ((j1 && (i2 || i3)) || i1 || (i + j == 9 && i<6) || (j4&&i7)) && !(i1&&j61)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '!':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && j4&&!(j4&&i6)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '+':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i4 || j4) && !(i + j == 5 || i + j == 11)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '-':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && i4&&!(j61)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '=':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && (i3 || i5) && !(j61)
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	case '_':
		for (int i = 0; i < HiK; i++)
		{
			for (int j = 0; j < WiK; j++)
			{
				gotoXY(x + j, y + i);
				if (notdraw && i7
					){
					TextColor(coText);
					putchar(mode);
				}
				else { TextColor(coBG); putchar(' '); }
			}
		}
		return;
	}
}
void drawkey(char key, int x, int y){
	return drawkey(key, x, y, 5 + 10 * 16, 5 + 9 * 16, key);
}
void drawkey(char key, int x, int y, int mode){
	return drawkey(key, x, y, 5 + 10 * 16, 5 + 9 * 16, mode);
}
void drawstr(string str, int x, int y){
	int n = str.length();
	x -= 9;
	int x0 = x ;
	for (int i = 0; i < n; i++)
	{
		if (str[i] == '\n'){ x = x0;  y = 9 + y; continue; }
		else drawkey(str[i], x+=9 , y, 9 + 16 * 14, 4 + 16 * 11,'*');
	}
}
void drawstr(string str, int x, int y, char lang){
	switch (lang){
	case 'e':case'E': return drawstr(str, x, y);
	}
}