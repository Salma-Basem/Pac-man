#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <string.h>
#include <iostream>
#include"RGBpixmap.h"
//#include "stdafx.h"
#include <string>
#include <GL/glut.h>
RGBpixmap pix[4];
RGBpixmap ghosts[4];
RGBpixmap PacmanRight;
RGBpixmap PacmanLeft;
RGBpixmap PacmanUp;
RGBpixmap PacmanDown;




bool purpleD = true;
bool orangeD = true;
bool blueD = true;
bool redD = true;
bool pacD = true;
bool pacDY = true;

float xfood = 10, yfood = 10;
int points = 0;
bool flag1 = false;
const int REFRESH_MS = 5;
bool wrapAround = false;
GLsizei winWidth = 60, winHeight = 60;
GLfloat xwcMin = 0.0, xwcMax = 60.0;
GLfloat ywcMin = 0.0, ywcMax = 60.0;


float fXPos = 20, fYPos = 280;
float gx1 = 30, gy1 = 25;
float gx2 = 200, gy2 = 30;
float gx3 = 220, gy3 = 160;
float gx4 = 280, gy4 = 260;

int random;
//int prev = random;

//min+ rand()%(max-min+1) 
//min 10    max 275
// 22W 25H
void drawmap();
void eatfood();
void timer(int value);
void InitGraphics(int argc, char* argv[]);
void OnDisplay();
//void O();
void moveghost();
void comp(int w, int z, int p1x, int p1y);
void resultsDisplay();
void OnSpecialKeyPress(int key, int x, int y);
void SetTransformations();


int main(int argc, char* argv[]) {
	InitGraphics(argc, argv);
	return 0;

	
	
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(REFRESH_MS, timer, 0);
}

void InitGraphics(int argc, char* argv[]) {
	glutInit(&argc, argv);// intil gpu
	glutInitDisplayMode(GLUT_RGB);
	//Create an 800x600 window with its top-left corner at pixel (100, 100)
	glutInitWindowPosition(100, 100); //pass (-1, -1) for Window-Manager defaults
	glutInitWindowSize(800, 600);
	glutCreateWindow("pacman game");

	PacmanRight.readBMPFile("right.bmp");
	PacmanDown.readBMPFile("down.bmp");
	PacmanLeft.readBMPFile("left.bmp");
	PacmanUp.readBMPFile("up.bmp");

	pix[0] = PacmanRight;
	pix[1].readBMPFile("fo.bmp");

	ghosts[0].readBMPFile("orange.bmp");
	ghosts[1].readBMPFile("blue.bmp");
	ghosts[2].readBMPFile("red.bmp");
	ghosts[3].readBMPFile("pink.bmp");

	glutDisplayFunc(OnDisplay);

	glutSpecialFunc(OnSpecialKeyPress);



	glutIdleFunc(OnDisplay);//idle callback is continuously called when events are not being received
	glutMainLoop();
}

void SetTransformations() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 310, 0, 310);

}


void drawmap() {


	glColor3f(0, 0, 0);

	glLineWidth(3);

	//frame
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2d(10, 300);
	glVertex2d(300, 300);
	glVertex2d(300, 10);
	glVertex2d(10, 10);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(43, 270);
	glVertex2f(55, 270);
	glVertex2f(55, 70);
	glVertex2f(93, 70);
	glVertex2f(93, 110);
	glVertex2f(105, 110);
	glVertex2f(105, 64);
	glVertex2f(43, 64);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(93, 220);
	glVertex2f(105, 220);
	glVertex2f(105, 156);
	glVertex2f(93, 156);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(93, 270);
	glVertex2f(165, 270);
	glVertex2f(165, 245);
	glVertex2f(140, 245);
	glVertex2f(140, 264);
	glVertex2f(93, 264);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(143, 200);
	glVertex2f(175, 200);
	glVertex2f(175, 140);
	glVertex2f(215, 140);
	glVertex2f(215, 132);
	glVertex2f(143, 132);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(163, 90);
	glVertex2f(215, 90);
	glVertex2f(215, 85);
	glVertex2f(180, 85);
	glVertex2f(180, 55);
	glVertex2f(163, 55);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(203, 270);
	glVertex2f(245, 270);
	glVertex2f(245, 256);
	glVertex2f(203, 256);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(253, 210);
	glVertex2f(265, 210);
	glVertex2f(265, 125);
	glVertex2f(253, 125);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(253, 70);
	glVertex2f(265, 70);
	glVertex2f(265, 54);
	glVertex2f(253, 54);
	glEnd();
}




void OnDisplay() {


	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	SetTransformations();
	drawmap();
	moveghost();
	//O();
	glEnable(GL_TEXTURE_2D);
	glPixelZoom(1, 1);
	glRasterPos2i(fXPos, fYPos);
	pix[0].draw();
	glPixelZoom(1, 1);
	glRasterPos2i(xfood, yfood);
	pix[1].draw();
	
	/*glPixelZoom(0.10, 0.10);
	glRasterPos2i(gx1, gy1);
	ghosts[0].draw();
	gx1 += 0.1;

	glPixelZoom(0.10, 0.10);
	glRasterPos2i(gx2, gy2);
	ghosts[1].draw();
	gx2 -= 0.1;

	glPixelZoom(0.10, 0.10);
	glRasterPos2i(gx3, gy3);
	ghosts[2].draw();
	gy3 += 0.01;
	gx3 -= 0.2;

	glPixelZoom(0.10, 0.10);
	glRasterPos2i(gx4, gy4);
	ghosts[3].draw();
	gy4 -= 0.1;*/

	
	{//if ((fXPos  < gx1 || fXPos == gx2 || fXPos == gx3 || fXPos == gx4) || (fYPos == gy1 || fYPos == gy2 || fYPos == gy3 || fYPos == gy4) || (fXPos + 40 == gx1 || fXPos + 40 == gx2 || fXPos + 40 == gx3 || fXPos + 40 == gx4) || (fYPos + 40 == gy1 || fYPos + 40 == gy2 || fYPos + 40 == gy3 || fYPos + 40 == gy4))
		if (points > 5)
		{
			resultsDisplay();

		}
	}
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
	//sndPlaySound(TEXT("pacman_beginning.wav"), SND_ASYNC);

}
void moveghost() {

	glPixelZoom(0.10, 0.10);
	glRasterPos2i(gx1, gy1);
	ghosts[0].draw();

	if (gy1 >= 280 || gy1 <= 10)
	{
		orangeD = !orangeD;
	}

	if (orangeD == false)
	{
		gy1 += 0.2;
	}
	else
	{
		gy1 -= 0.2;
	}
	glPixelZoom(0.10, 0.10);
	glRasterPos2i(gx2, gy2);
	ghosts[1].draw();


	if (gx2 >= 270 || gx2 <= 20)
	{
		blueD = !blueD;

	}

	if (blueD == false)
	{
		gx2 += 0.2;

	}

	else
	{
		gx2 -= 0.2;
	}

	glPixelZoom(0.10, 0.10);
	glRasterPos2i(gx3, gy3);
	ghosts[2].draw();



	if (gx3 >= 240 || gx3 <= 180)
	{
		redD = !redD;

	}

	if (redD == false)
	{
		gx3 += 0.2;

	}

	else
	{
		gx3 -= 0.2;
	}
	glPixelZoom(0.10, 0.10);
	glRasterPos2i(gx4, gy4);
	ghosts[3].draw();


	if (gy4 >= 280 || gy4 <= 10)
	{
		purpleD = !purpleD;

	}

	if (purpleD == false)
	{
		gy4 += 0.2;

	}

	else
	{
		gy4 -= 0.2;

	}
}

//void O() {
//	glColor3f(1, 0, 0);
//
//	glLineWidth(3);
//
//	//frame
//	glBegin(GL_LINES);
//	//!((40 <= random && random <= 60) && (50 <= randomy && randomy <= 270))
//		glVertex2d(40, 50);
//		glVertex2d(60, 270);
//		//&& !((40 <= random && random <= 110) && (50 <= randomy && randomy <= 70))
//		glVertex2d(40, 50);
//		glVertex2d(110, 70);
//		//&& !((80 <= random && random <= 110) && (50 <= randomy && randomy <= 110))
//		glVertex2d(90, 50);
//		glVertex2d(110, 110);
//
//		//&& !((90 <= random && random <= 110) && (140 <= randomy && randomy <= 220))
//		glVertex2d(90, 140);
//		glVertex2d(110, 220);
//		//&& !((90 <= random && random <= 170) && (250 <= randomy && randomy <= 270))
//		glVertex2d(90, 250);
//		glVertex2d(170, 270);
//		//&& !((140 <= random && random <= 170) && (230 <= randomy && randomy <= 270))
//		glVertex2d(140, 230);
//		glVertex2d(170, 270);
//		//&& !((140 <= random && random <= 220) && (120 <= randomy && randomy <= 140))
//		glVertex2d(140, 120);
//		glVertex2d(220, 140);
//		//&& !((140 <= random && random <= 180) && (120 <= randomy && randomy <= 200))
//		glVertex2d(140, 120);
//		glVertex2d(180, 200);
//		//&& !((200 <= random && random <= 250) && (240 <= randomy && randomy <= 270))
//		glVertex2d(200, 240);
//		glVertex2d(250, 270);
//		
//		//&& !((160 <= random && random <= 180) && (40 <= randomy && randomy <= 90))
//			glVertex2d(160, 40);
//			glVertex2d(180, 90);
//		//&& !((160 <= random && random <= 220) && (70 <= randomy && randomy <= 90))
//			glVertex2d(160, 70);
//			glVertex2d(220, 90);
//		//&& !((250 <= random && random <= 270) && (40 <= randomy && randomy <= 70))
//			glVertex2d(250, 40);
//			glVertex2d(270, 70);
//		//&& !((250 <= random && random <= 270) && (110 <= randomy && randomy <= 210))
//			glVertex2d(250, 110);
//			glVertex2d(270, 210);
//	glEnd();
//}
void eatfood() {
	//22,25
	//w 22 , h 25
	int prev;
	int randomy = 10 + (rand() % 266);
	prev = randomy;
	int x1 = fXPos - xfood;
	int y1 = fYPos - yfood;
	int x2 = fXPos + 100 - xfood + 63;
	int y2 = fYPos + 95 - yfood + 70;
	bool flag = false;

	while (flag == false) {
		randomy = 10 + (rand() % 266);
		random = 10 + (rand() % 266);
		if (!((225 <= random && random <= 295) && (15 <= randomy && randomy <= 95))
			&& !((135 <= random && random <= 205) && (15 <= randomy && randomy <= 115))
			&& !((225 <= random && random <= 295) && (85 <= randomy && randomy <= 235))
			&& !((175 <= random && random <= 275) && (215 <= randomy && randomy <= 295))
			&& !((115 <= random && random <= 195) && (205 <= randomy && randomy <= 275))
			&& !((55 <= random && random <= 195) && (225 <= randomy && randomy <= 295))
			&& !((55 <= random && random <= 135) && (115 <= randomy && randomy <= 245))
			&& !((55 <= random && random <= 135) && (45 <= randomy && randomy <= 135))
			&& !((15 <= random && random <= 135) && (25 <= randomy && randomy <= 95))
			&& !((15 <= random && random <= 135) && (25 <= randomy && randomy <= 295))
			&& !((115 <= random && random <= 205) && (95 <= randomy && randomy <= 225))
			&& !((115 <= random && random <= 245) && (95 <= randomy && randomy <= 165))
			&& !((115 <= random && random <= 245) && (45 <= randomy && randomy <= 115))
			) {
			/*if (!((40 <= random && random <= 60) && (50 <= randomy && randomy <= 270))
				&& !((40 <= random && random <= 110) && (50 <= randomy && randomy <= 70))
				&& !((90 <= random && random <= 110) && (50 <= randomy && randomy <= 110))

				&& !((90 <= random && random <= 110) && (140 <= randomy && randomy <= 220))

				&& !((90 <= random && random <= 170) && (250 <= randomy && randomy <= 270))
				&& !((140 <= random && random <= 170) && (230 <= randomy && randomy <= 270))


				&& !((140 <= random && random <= 220) && (120 <= randomy && randomy <= 140))
				&& !((140 <= random && random <= 180) && (120 <= randomy && randomy <= 200))

				&& !((200 <= random && random <= 250) && (240 <= randomy && randomy <= 270))

				&& !((160 <= random && random <= 180) && (40 <= randomy && randomy <= 90))
				&& !((160 <= random && random <= 220) && (70 <= randomy && randomy <= 90))

				&& !((250 <= random && random <= 270) && (40 <= randomy && randomy <= 70))
				&& !((250 <= random && random <= 270) && (110 <= randomy && randomy <= 210))
				) {*/
			flag = true;
			//sndPlaySound(TEXT("pacman_eatfruit.wav"), SND_ASYNC);
		}


	}
	if (abs(x1) <= 7 && abs(y1) <= 7) {
		points++;

		xfood = random;
		yfood = randomy;
		sndPlaySound(TEXT("pacman_eatfruit.wav"), SND_ASYNC);
	}
	random = 10 + (rand() % 266);

	while (prev == random) {
		random = 10 + (rand() % 266);
		//sndPlaySound(TEXT("pacman_eatfruit.wav"), SND_ASYNC);
	}

	/*sndPlaySound(TEXT("pacman_eatfruit.wav"), SND_ASYNC);*/
	//OnSpecialKeyPress;
}


void resultsDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (points == 5) {

		//Won
		const char* message = "CONGRATULATIONS, YOU WON!";
		glRasterPos2f(170, 250);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	}

	//if ((gx1 == fXPos || fXPos == gx2 || fXPos == gx3 || fXPos == gx4) || (fYPos == gy1 || fYPos == gy2 || fYPos == gy3 || fYPos == gy4) || (fXPos + 40 == gx1 || fXPos + 40 == gx2 || fXPos + 40 == gx3 || fXPos + 40 == gx4) || (fYPos + 40 == gy1 || fYPos + 40 == gy2 || fYPos + 40 == gy3 || fYPos + 40 == gy4))
	if (points > 5)
	{
			const char* message = "SORRY , YOU lost";
			glRasterPos2f(170, 250);
			while (*message)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		}

		//sndPlaySound(TEXT("pacman_death.wav"), SND_ASYNC);
		glutSwapBuffers();
		
	

}
char c;
void OnSpecialKeyPress(int key, int x, int y)
{

	/*HDC dng = GetDC(NULL);
	COLORREF c = GetPixel(dng, fXPos, fYPos);
	ReleaseDC(NULL, dng);
	if ((int)GetRValue(c) == 0 && (int)GetGValue(c) == 0 && (int)GetBValue(c) == 0) {
		cout << "rrrrrrrr      ";
	}*/
	int p1y = fYPos + 20;
	int p1x = fXPos + 20;
	switch (key)
	{
		int z;
		int w;
	case GLUT_KEY_LEFT://		Left function key
		c = 'l';
		z = fYPos + 2;
		w = fXPos - 2;
		//w = fXPos;
		flag1 = false;
		comp(w, z, p1x, p1y);
		if (fXPos < 11) {
			fXPos = fXPos;
		//sndPlaySound(TEXT("pacman_chomp.wav"), SND_ASYNC);
			break;
		}
		if (flag1 == true) {
			fXPos -= 2;
			pix[0] = PacmanLeft;
			eatfood();
		}
	//	sndPlaySound(TEXT("pacman_chomp.wav"), SND_ASYNC);
		break;
	case GLUT_KEY_RIGHT://		Right function key	
		//if fy > ybox keep fy as it is 
		c = 'r';
		z = fYPos + 2;
		//z = fYPos + 20;
		w = fXPos + 10;
		//w = fXPos;
		flag1 = false;
		comp(w, z, p1x, p1y);
		if (fXPos > 288) {
			fXPos = fXPos;
		//sndPlaySound(TEXT("pacman_chomp.wav"), SND_ASYNC);
			break;
		}
		if (flag1 == true) {
			fXPos += 2;
			pix[0] = PacmanRight;
			eatfood();
		}
	//	sndPlaySound(TEXT("pacman_chomp.wav"), SND_ASYNC);
		break;
	case GLUT_KEY_UP://		Up function key
		c = 'u';
		z = fYPos + 22;
		//z = fYPos ;
		w = fXPos + 5;
		flag1 = false;
		comp(w, z, p1x, p1y);
		if (fYPos > 278) {
			fYPos = fYPos;
		//	sndPlaySound(TEXT("pacman_chomp.wav"), SND_ASYNC);
			break;
		}
		if (flag1 == true) {
			fYPos += 2;
			pix[0] = PacmanUp;
			eatfood();
		}
	//	sndPlaySound(TEXT("pacman_chomp.wav"), SND_ASYNC);
		break;

	case GLUT_KEY_DOWN://		Down function key
		c = 'd';
		z = fYPos - 2;
		//z = fYPos;
		w = fXPos + 5;
		flag1 = false;
		comp(w, z, p1x, p1y);

		if (fYPos < 11) {
			fYPos = fYPos;
	//	sndPlaySound(TEXT("pacman_chomp.wav"), SND_ASYNC);
			break;
		}
		if (flag1 == true) {
			fYPos -= 2;
			pix[0] = PacmanDown;
			eatfood();
		}
		break;
		//sndPlaySound(TEXT("pacman_chomp.wav"), SND_ASYNC);
	};
}
void comp(int w, int z, int p1x, int p1y) {

	if (!(((40 <= w && w <= 60) && (50 <= z && z <= 270)))) {//&& (((40 <= p1x && p1x <= 60) && (50 <= p1y && p1y <= 270)))) {
		if (!(((40 <= w && w <= 110) && (50 <= z && z <= 70)))) {// && (((40 <= p1x && p1x <= 110) && (50 <= p1y && p1y <= 70)))) {
			if (!(((90 <= w && w <= 110) && (50 <= z && z <= 110)))) {// && (((90 <= p1x && p1x <= 110) && (50 <= p1y && p1y <= 110)))) {
				if (!(((90 <= w && w <= 110) && (140 <= z && z <= 220)))) {// && (((90 <= p1x && p1x <= 110) && (140 <= p1y && p1y <= 220)))) {
					if (!(((90 <= w && w <= 170) && (250 <= z && z <= 270)))) {//&& ( ((90 <= p1x && p1x <= 170) && (250 <= p1y && p1y <= 270)))) {
						if (!(((140 <= w && w <= 170) && (230 <= z && z <= 270)))) {// && ( ((140 <= p1x && p1x <= 170) && (230 <= p1y && p1y <= 270)))) {
							if (!(((140 <= w && w <= 220) && (120 <= z && z <= 140)))) {// && ( ((140 <= p1x && p1x <= 220) && (120 <= p1y && p1y <= 140))))  {
								if (!(((140 <= w && w <= 180) && (120 <= z && z <= 200)))) {// && ( ((140 <= p1x && p1x <= 180) && (120 <= p1y && p1y <= 200)))) {
									if (!(((200 <= w && w <= 250) && (240 <= z && z <= 270)))) {// && ( ((200 <= p1x && p1x <= 250) && (240 <= p1y && p1y <= 270)))) {
										if (!(((160 <= w && w <= 180) && (40 <= z && z <= 90)))) {// && ( ((160 <= p1x && p1x <= 180) && (40 <= p1y && p1y <= 90)))) {
											if (!(((160 <= w && w <= 220) && (70 <= z && z <= 90)))) {// && ( ((160 <= p1x && p1x <= 220) && (70 <= p1y && p1y <= 90)))) {
												if (!(((250 <= w && w <= 270) && (40 <= z && z <= 70)))) {// && ( ((250 <= p1x && p1x <= 270) && (40 <= p1y && p1y <= 70)))) {
													if (!(((250 <= w && w <= 270) && (110 <= z && z <= 210)))) {//&& (((250 <= p1x && p1x <= 270) && (110 <= p1y && p1y <= 210)))) {
														flag1 = true;
														//sndPlaySound(TEXT("pacman_chomp.wav"), SND_ASYNC);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
		//sndPlaySound(TEXT("pacman_chomp.wav"), SND_ASYNC);
}