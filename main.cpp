#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <fstream>
#include <string>
#include <cstdio>
#include "console.h"
using namespace std;
#define WO 15
#define HO 10
#define VMP 2//Value Min Pie
#define	MVP	2//Multiple Value Pie
#define MSG 4// MAX SizE GAME
const int  midW =WO/2;
const int  midH=HO/2;

const int endH = HO - 1, endW = WO - 1;
#ifndef _PIE_
#define _PIE_
struct pizz{
	int pie[MSG][MSG];
	int old[MSG][MSG];
	int islive;
	// xem các pie còn tồn tại không
	int empty;
	// Số ô còn trống (0)
	int score;
};
#endif
void intro(pizz f);
void show(string a, int x, int y);
void draw(int	value, int fy, int fx);
void grow(pizz &f);
void init(pizz &f);
void disp(pizz f);
void ctrl(pizz&f);
void checklive(pizz &f);
void turn(pizz &f, char key);
pizz irht(pizz f);
void destroy(pizz &f);
void main(){
	/*for (int i = 1; i < 256; i++)
	{
		cout << i << "\t";
		putchar(i);
		cout << "\t";
		if (i % 5 == 0){ cout << endl; }
	}
	_getch();*/
	ancontro();
	system("color B7 ");
	srand((unsigned int)time(NULL));
	pizz f;
	int a = 0;
	init(f);
	intro(f);
	while (1){

		if (f.empty == 0){
			checklive(f);
			if (f.islive == 0){
				drawkeyspecial("2GO~ ~ \n0AV~ ~ \n4ME~ ~ \n8ER~ ~ \n  ~o", WO*MSG  +1, 0,8+16*10,32+16*10,'*');//Số 4 là  một nữa độ dài chuỗi GAME OVER! -1
				while (1){
					char key = _getch();
					if (key == 'x' || key == 'X'){return; }
					if (key == 'z' || key == 'Z'){ clrscr(); init(f); intro(f); break; }
				}
			}
			else{
				ctrl(f);
			}
		}
		else if (f.empty == -1){
			return;
		}
		else{
			ctrl(f);
		}
	}
}
pizz irht(pizz f){
	pizz g;
	g.empty = f.empty;
	g.islive = f.islive;
	g.score = f.score;
	for (int i = 0; i < MSG; i++)
	{
		for (int j = 0; j < MSG; j++)
		{
			g.pie[i][j] = f.pie[i][j];
			g.old[i][j] = f.old[i][j];
		}
	}
	return g;
}
void intro(pizz f){

	for (int fx = 0; fx < MSG; fx++)
	{

		for (int fy = 0; fy < MSG; fy++)
		{
			int yH = HO*fy, xW = WO*fx;
			for (int i = 0; i < HO; i++){
				for (int j = 0; j < WO; j++)
				{
					gotoXY(j + xW, i +yH);
					if ((i == 0 || (i == endH) || j == 1 || j == WO - 2 || j == endW || j == 0)){
						TextColor(199);
						putchar(' ');
					}
				}
			}
		}
	}
	int sz = MSG;
	for (int j = 0; j < sz*HO; j++)
	{
		TextColor(8 + 16 * 3);
		show(" ", sz*WO, j);
	}
	TextColor(9 + 16 * 11);
	int x = sz*WO+1,  i = 0;
	drawkeyspecial("2G|W~W\n0A|S~S\n4M|A~A\n8E|D~D\nX~x|Z~Z", x, i++);
	TextColor(9 + 16 * 11);
}
void show(string a, int x, int y){
	gotoXY(x, y);
	cout << a;
}
void draw(int	value, int fy, int fx){
	int yH = HO*fy, xW = WO*fx;
	string str;
	int textco=0;
	switch (value){
	case 2:
		textco=15+16*2;
		str="2";
		break;
	case 4:
		textco=15+16*3;
		str="4";
		break;
	case 8:
		textco=15+16*4;
		str="8";
		break;
	case 16:
		textco=15+16*5;
		str="16";
		break;
	case 32:
		textco=15+16*6;
		str="32";
		break;
	case 64:
		textco=15+16*7;
		str="64";
		break;
	case 128:
		textco=15+16*8;
		str="128";
		break;
	case 256:
		textco=15+16*9;
		str="256";
		break;
	case 512:
		textco=15+16*10;
		str="512";
		break;
	case 1024:
		textco=15+16*11;
		str="512";
		break;
	case 2048:
		textco=15+16*12;
		str="2048";
		break;
	default:
		int number[10] = { 0 }, n = 0;
		int m = value;
		while (value > 0){
			number[n++] = value % 10;
			value /= 10;
		}
		value = m;
		m = 0;
		for (int i = 0; i < n / 2; i++)
		{
			swap(number[i], number[n - i - 1]);
		}
		for (int i = n; i < 10; i++){
			number[i] = -16;
		}
		for (int i = 1; i < endH; i++){
			for (int j = 2; j < endW-1; j++)
			{
				gotoXY(j + xW, i +yH);

				TextColor(15 + 16 * (int)(log(value) / log(VMP)) + 1);
				if (i == midH && j >=midW - n / 2 && j <=midW + n / 2 && n>0){ putchar(number[m++] + 48); }
				else
					putchar(' ');
			}
		}
	}
	if(textco!=0){
		TextColor(textco);
		for (int i = 1; i < endH; i++){
			for (int j = 2; j < endW-1; j++)
			{
				show(" ", j + xW, i +yH);
			}
		}
		show(str,midW - 1 + xW, midH +yH);
		return;
	}

}
void grow(pizz &f){
	int x, y;
	do{
		x = rand() % MSG;
		y = rand() % MSG;
		if (f.pie[x][y] == 0){
			f.pie[x][y] = ((rand() % 4 == 0) ? MVP : 1)*VMP;
			f.empty--;
			disp(f);
			return;
		}
		if (f.empty == 0){ f.islive = 0; return; }
	} while (1);

}


void init(pizz &f){
	f.empty = MSG*MSG;
	f.islive = 1;
	f.score = 0;
	for (int i = 0; i < MSG; i++)
	{
		for (int j = 0; j < MSG; j++)
		{
			f.pie[i][j] = 0;
		}
	}
	grow(f);
	grow(f);
}
void disp(pizz f){
	for (int i = 0; i < MSG; i++)
	{
		for (int j = 0; j < MSG; j++)
		{
			if (f.pie[i][j] != f.old[i][j])draw(f.pie[i][j], i, j);
		}
	}
	gotoXY((WO*MSG-7)/2, HO*MSG+1);
	TextColor(9 + 11 * 16);
	cout << "SCORE: " << f.score << "        ";
}
void ctrl(pizz&f){
	while (1){
		pizz g;
		g = irht(f);
		g.islive = 0;
		char key;
		while (_kbhit()){

			key = _getch();
			switch (key){
			case 'z':case 'Z':
				show("Are you play new game?", WO*MSG / 2 - 4, HO*MSG / 2);
				show("     Z:YES or C:NO", WO*MSG / 2 - 4, 1 + HO*MSG / 2);
				while (1){
					while (_kbhit()){
						char key = _getch();
						if (key == 'z' || key == 'Z'){ clrscr(); init(f); intro(f); disp(f);  return; }
						if (key == 'c' || key == 'C'){ clrscr(); intro(f); disp(f); return; }
					}
				}
			case 'x':case'X':
				show("Are you exit?", WO*MSG / 2 - 4, HO*MSG / 2);
				show("X:YES or C:NO", WO*MSG / 2 - 4,1+ HO*MSG / 2);
				while (1){
				while (_kbhit()){
					char key = _getch();
					if (key == 'x' || key == 'X'){ f.empty = -1; return; }
					if (key == 'c' || key == 'C'){ clrscr(); intro(f); disp(f); return; }
				}}
			case 'w':case'W':
				//Up
				for (int j = 0; j < MSG; j++){
					for (int i = 0; i < MSG - 1; i++){
						for (int k = i + 1; k < MSG; k++){
							if (g.pie[k][j]>0){
								if (g.pie[i][j] == 0){
									g.pie[i][j] = g.pie[k][j];
									g.pie[k][j] = 0;
									g.islive = 1;


								}
								else{
									if (g.pie[i][j] == g.pie[k][j]){
										g.pie[i][j] *= MVP;
										g.score += g.pie[i][j];
										g.pie[k][j] = 0;
										g.islive = 1;
										g.empty++;


									}
									break;
								}

							}
						}
					}

				}
				break;
			case 'a':case 'A'://Left
				for (int i = 0; i < MSG; i++){
					for (int j = 0; j < MSG - 1; j++){
						for (int k = j + 1; k < MSG; k++){
							if (g.pie[i][k]>0){
								if (g.pie[i][j] == 0){
									g.pie[i][j] = g.pie[i][k];
									g.pie[i][k] = 0;
									g.islive = 1;


								}
								else{
									if (g.pie[i][j] == g.pie[i][k]){
										g.pie[i][j] *= MVP;
										g.score += g.pie[i][j];
										g.pie[i][k] = 0;
										g.islive = 1;
										g.empty++;

									}
									break;
								}

							}
						}
					}

				}
				break;
			case 's':case 'S':
				//Down
				for (int j = 0; j < MSG; j++){
					for (int i = MSG - 1; i >0; i--){
						for (int k = i - 1; k >= 0; k--){
							if (g.pie[k][j] > 0){
								if (g.pie[i][j] == 0){
									g.pie[i][j] = g.pie[k][j];
									g.pie[k][j] = 0;
									g.islive = 1;

								}
								else{
									if (g.pie[i][j] == g.pie[k][j]){
										g.pie[i][j] *= MVP;
										g.score += g.pie[i][j];
										g.pie[k][j] = 0;
										g.islive = 1;
										g.empty++;

									}
									break;
								}

							}
						}
					}

				}
				break;
			case 'd':case 'D': //Right
				for (int i = 0; i < MSG; i++){
					for (int j = MSG - 1; j >0; j--){
						for (int k = j - 1; k >= 0; k--){
							if (g.pie[i][k] > 0){
								if (g.pie[i][j] == 0){
									g.pie[i][j] = g.pie[i][k];
									g.pie[i][k] = 0;
									g.islive = 1;

								}
								else{
									if (g.pie[i][j] == g.pie[i][k]){
										g.pie[i][j] *= MVP;
										g.score += g.pie[i][j];
										g.pie[i][k] = 0;
										g.islive = 1;
										g.empty++;

									}
									break;
								}
							}
						}
					}
				}
				break;
			}
		}
		if (g.islive == 1){
			for (int i = 0; i < MSG; i++)
			{
				for (int j = 0; j < MSG; j++)
				{
					f.old[i][j] = f.pie[i][j];
				}
			}
			f= irht(g);
			disp(f);
			grow(f);
			return;
		}

	}
}
void checklive(pizz &f){
	if (f.islive == 0){ return; }
	for (int i = 0; i < MSG; i++)
	{
		for (int j = 0; j < MSG; j++)
		{
			if (i>0){
				if (f.pie[i - 1][j] == f.pie[i][j]){
					f.islive = 1; return;
				}
			}
			if (i < MSG - 1){
				if (f.pie[i + 1][j] == f.pie[i][j]){
					f.islive = 1; return;
				}
			}
			if (j>0){
				if (f.pie[i][j - 1] == f.pie[i][j]){
					f.islive = 1; return;
				}
			}
			if (j < MSG - 1){
				if (f.pie[i][j + 1] == f.pie[i][j]){
					f.islive = 1; return;
				}
			}
		}
	}
	f.islive = 0;
}
