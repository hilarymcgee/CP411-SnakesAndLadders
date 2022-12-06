//
// Created by mcgeeh on 12/2/2022.
//

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <math.h>

#define maxx 10
#define maxy 10
#define squareWidth 70
#define squareHeight 70
#define boardLeftPos 350
#define boardBottomPos 30
#define speed 2
GLfloat squareRightMax[maxx + 1] = {0}, squareBottomMax[maxy + 1] = {0};
#define DEG2RAD 3.14159 / 180.0

struct ladder
{
	int xp, xq, yp, yq;
};
struct snake
{
	int xp, xq, yp, yq;
};


extern void rect();
extern void Cylinder_draw();
extern void cyl();

using namespace std;


struct snake snake_arr[4];
struct ladder ladder_arr[4];

char mess[4];
int cnt;
int alt = 1;
int flg = 1;
int mt = 1;
int r, s;
int width, height;
int selec;

static GLfloat theta[] = {0.0, 0.0, 0.0};

GLfloat vertices[][3] = {
    {1150.0, 550.0, -50.0}, 
    {1250.0, 550.0, -50.0}, 
    {1250.0, 650.0, -50.0}, 
    {1150.0, 650.0, -50.0}, 
    {1150.0, 550.0,  50.0}, 
    {1250.0, 550.0,  50.0}, 
    {1250.0, 650.0,  50.0}, 
    {1150.0, 650.0,  50.0}
};

GLfloat colors[][3] = {
    {0.0,  0.0,  0.0}, 
    {1.0, -1.0, -1.0}, 
    {1.0,  1.0,  0.0}, 
    {0.0,  1.0,  0.0}, 
    {0.0,  0.0,  1.0}, 
    {1.0,  0.0,  1.0}, 
    {1.0,  1.0,  1.0}, 
    {0.0,  1.0,  1.0}
};

GLfloat mxB(GLfloat x, GLfloat m, GLfloat k) { // returns y value of a line
	return (m * x + k);
}
float snlf(float y, float m, float c) { // (y-c)/m
	return (y - c) / m;
}
void glutBitmapString(const char *str) {
	int i = 0;
	while (str[i] != '\0')
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i++]); //GLUT_BITMAP_TIMES_ROMAN_24
}
void polygon(int a, int b, int c, int d, int e) { // dice drawer
	// dice color filler
	glBegin(GL_POLYGON);
	glColor3f(1.000, 0.753, 0.796);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();

	// dice ouline
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.000, 0.412, 0.706);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();

	// dice numbers as dots
	glLineWidth(2.0);
	glColor3f(1, 1, 1); // dice dot colors
	glPointSize(6.0);
	glBegin(GL_POINTS);
	switch (e)
	{
	case 1:
		glVertex3f(1200.0,600.0,-50.0);
		break;
	case 2:
		glVertex3f(1175.0, 651.0, 25.0);
		glVertex3f(1225.0, 651.0, -25.0);
		break;
	case 3:
		glVertex3f(1149.0, 575.0, 25.0);
		glVertex3f(1149.0, 600.0, 0.0);
		glVertex3f(1149.0, 625.0, -25.0);
		break;
	case 4:
		glVertex3f(1251.0, 575.0, 25.0);
		glVertex3f(1251.0, 575.0, -25.0);
		glVertex3f(1251.0, 625.0, 25.0);
		glVertex3f(1251.0, 625.0, -25.0);
		break;
	case 5:
		glVertex3f(1175.0, 549.0, 25.0);
		glVertex3f(1175.0, 549.0, -25.0);
		glVertex3f(1200.0, 549.0, 0.0);
		glVertex3f(1225.0, 549.0, 25.0);
		glVertex3f(1225.0, 549.0, -25.0);
		break;
	case 6:
		glVertex3f(1175.0, 575.0, 51.0);
		glVertex3f(1175.0, 600.0, 51.0);
		glVertex3f(1175.0, 625.0, 51.0);
		glVertex3f(1225.0, 575.0, 51.0);
		glVertex3f(1225.0, 600.0, 51.0);
		glVertex3f(1225.0, 625.0, 51.0);
		break;
	}
	glEnd();
}
void colorcube(void) { // draw dice sides
	polygon(0, 3, 2, 1, 1); // front
	polygon(2, 3, 7, 6, 2); // right
	polygon(0, 4, 7, 3, 3); // top
	polygon(1, 2, 6, 5, 4); // bottom
	polygon(4, 5, 6, 7, 5); // back
	polygon(0, 1, 5, 4, 6); // left
}
void ltorladder(GLint a, GLint b, GLint c, GLint d) { // left to right ladder
	glBegin(GL_QUADS);

	// Ladder Side Beams
	glVertex3f(squareRightMax[a] + 27, squareBottomMax[b] + 23, 15);
	glVertex3f(squareRightMax[a] + 30, squareBottomMax[b] + 18, 15);
	glVertex3f(squareRightMax[c] + 50, squareBottomMax[d] + 10, 15);
	glVertex3f(squareRightMax[c] + 47, squareBottomMax[d] + 15, 15);
	glVertex3f(squareRightMax[a] + 3, squareBottomMax[b] + 47, 15);
	glVertex3f(squareRightMax[a] + 6, squareBottomMax[b] + 42, 15);
	glVertex3f(squareRightMax[c] + 26, squareBottomMax[d] + 34, 15);
	glVertex3f(squareRightMax[c] + 23, squareBottomMax[d] + 39, 15);

	// draw ladder rungs
	GLfloat xi = squareRightMax[a] + 27;
	int d1 = 8, d2 = 13;
	GLfloat m = (squareBottomMax[b] + 23.0 - (squareBottomMax[d] + 15.0)) / (squareRightMax[a] + 27.0 - (squareRightMax[c] + 47.0));
	GLfloat k = squareBottomMax[b] + 23.0 - (m * (squareRightMax[a] + 27.0));

	while (((squareRightMax[c] + 47) - (xi + d1)) > 8)
	{
		glVertex3f(xi + d1, mxB(xi + d1, m, k), 16);
		glVertex3f(xi + d2, mxB(xi + d2, m, k), 16);
		glVertex3f(xi - 24 + d2, mxB(xi + d2, m, k) + 24, 16);
		glVertex3f(xi - 24 + d1, mxB(xi + d1, m, k) + 24, 16);
		d1 += 15;
		d2 += 15;
	}

	glEnd();
}
void rtolladder(GLint a, GLint b, GLint c, GLint d) { // right to left ladder
	glBegin(GL_QUADS);

	// Ladder Side Beams
	glVertex3f(squareRightMax[a] + 6, squareBottomMax[b] + 32, 15);
	glVertex3f(squareRightMax[a] + 9, squareBottomMax[b] + 37, 15);
	glVertex3f(squareRightMax[c] + 29, squareBottomMax[d] + 29, 15);
	glVertex3f(squareRightMax[c] + 26, squareBottomMax[d] + 24, 15);
	glVertex3f(squareRightMax[a] + 6 + 24, squareBottomMax[b] + 32 + 24, 15);
	glVertex3f(squareRightMax[a] + 9 + 24, squareBottomMax[b] + 37 + 24, 15);
	glVertex3f(squareRightMax[c] + 29 + 24, squareBottomMax[d] + 29 + 24, 15);
	glVertex3f(squareRightMax[c] + 26 + 24, squareBottomMax[d] + 24 + 24, 15);

	// draw ladder rungs
	GLfloat xi = squareRightMax[c] + 26;
	int d1 = 8, d2 = 13;
	GLfloat m = (squareBottomMax[b] + 32.0 - (squareBottomMax[d] + 24.0)) / (squareRightMax[a] + 6.0 - (squareRightMax[c] + 26.0));
	GLfloat k = squareBottomMax[b] + 32.0 - (m * (squareRightMax[a] + 6.0));
	while (((squareRightMax[a] + 6) - (xi + d1)) > 8)
	{
		glVertex3f(xi + d1, mxB(xi + d1, m, k), 16);
		glVertex3f(xi + d2, mxB(xi + d2, m, k), 16);
		glVertex3f(xi + d2 + 24, mxB(xi + d2, m, k) + 24, 16);
		glVertex3f(xi + d1 + 24, mxB(xi + d1, m, k) + 24, 16);
		d1 += 15;
		d2 += 15;
	}

	glEnd();
}
void ladders() // draws ladders
{
	GLfloat m;
	glPointSize(20.0);
	glColor3f(0.647, 0.165, 0.165);

	switch (selec)
	{
	case 0:
		ltorladder(1, 0, 4, 2);
		ladder_arr[0].xp = 1, ladder_arr[0].xq = 4, ladder_arr[0].yp = 0, ladder_arr[0].yq = 2;
		ltorladder(2, 6, 3, 8);
		ladder_arr[1].xp = 2, ladder_arr[1].xq = 3, ladder_arr[1].yp = 6, ladder_arr[1].yq = 8;
		rtolladder(8, 4, 6, 6);
		ladder_arr[2].xp = 8, ladder_arr[2].xq = 6, ladder_arr[2].yp = 4, ladder_arr[2].yq = 6;
		rtolladder(5, 4, 3, 5);
		ladder_arr[3].xp = 5, ladder_arr[3].xq = 3, ladder_arr[3].yp = 4, ladder_arr[3].yq = 5;
		break;
	case 1:
		ltorladder(1, 1, 4, 4);
		ladder_arr[0].xp = 1, ladder_arr[0].xq = 4, ladder_arr[0].yp = 1, ladder_arr[0].yq = 4;
		ltorladder(7, 7, 9, 8);
		ladder_arr[1].xp = 7, ladder_arr[1].xq = 9, ladder_arr[1].yp = 7, ladder_arr[1].yq = 8;
		rtolladder(8, 0, 7, 2);
		ladder_arr[2].xp = 8, ladder_arr[2].xq = 7, ladder_arr[2].yp = 0, ladder_arr[2].yq = 2;
		rtolladder(3, 6, 2, 8);
		ladder_arr[3].xp = 3, ladder_arr[3].xq = 2, ladder_arr[3].yp = 6, ladder_arr[3].yq = 8;
		break;
	case 2:
		ltorladder(1, 1, 4, 4);
		ladder_arr[0].xp = 1, ladder_arr[0].xq = 4, ladder_arr[0].yp = 1, ladder_arr[0].yq = 4;
		ltorladder(2, 6, 3, 8);
		ladder_arr[1].xp = 2, ladder_arr[1].xq = 3, ladder_arr[1].yp = 6, ladder_arr[1].yq = 8;
		rtolladder(8, 4, 6, 6);
		ladder_arr[2].xp = 8, ladder_arr[2].xq = 6, ladder_arr[2].yp = 4, ladder_arr[2].yq = 6;
		rtolladder(8, 0, 7, 2);
		ladder_arr[3].xp = 8, ladder_arr[3].xq = 7, ladder_arr[3].yp = 0, ladder_arr[3].yq = 2;
		break;
	}
	snake_arr[0].xp = 2, snake_arr[0].yp = 9, snake_arr[0].xq = 0, snake_arr[0].yq = 1;
	snake_arr[1].xp = 5, snake_arr[1].yp = 3, snake_arr[1].xq = 6, snake_arr[1].yq = 0;
	snake_arr[2].xp = 6, snake_arr[2].yp = 8, snake_arr[2].xq = 6, snake_arr[2].yq = 4;
	snake_arr[3].xp = 8, snake_arr[3].yp = 6, snake_arr[3].xq = 9, snake_arr[3].yq = 2;
}

class player {
private:
	float p1, p2, p3, p4, q1, q2, q3, q4, oy, m, c, col1;
	int add, up, tmp, t, flag;
    float color_red, color_green, color_blue;

public:
	player(GLfloat, GLfloat, GLfloat, GLint tmp, float color_red, float color_green, float color_blue);
	void distance(int);
	void updatey();
	void disp();
	void init(int r);
	void check();
	int check100();
	void tryy(int i);
	void try2(int i);
    float get_color_red();
    float get_color_green();
    float get_color_blue();
};
float player::get_color_red() {
    return color_red;
}
float player::get_color_green() {
    return color_green;
}
float player::get_color_blue() {
    return color_blue;
}
player::player(GLfloat p1, GLfloat q1, GLfloat col, GLint tmp, float color_red, float color_green, float color_blue) {
	add = speed, up = 0, flag = 1;
	this->p1 = p1;
	this->p2 = p1 - 10;
	this->p3 = p1;
	this->p4 = p1 + 10;
	this->q1 = q1;
	this->q2 = q1 + 10;
	this->q3 = q1 + 20;
	this->q4 = q1 + 10;
	this->col1 = col;
	oy = q1 - boardBottomPos;
	this->tmp = tmp;
    
    this->color_red = color_red;
    this->color_green = color_green;
    this->color_blue = color_blue;
}

player player_one(boardLeftPos - 40, boardBottomPos + 40, 1, 70, 1.000, 0.412, 0.706);
player player_two(boardLeftPos - 40, boardBottomPos + 10, 0.5, 70, 0.000, 0.753, 0.796);

void victory_screen() // Winner Screen
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 1.0, 1.0, 1.0);
	int i;
	glColor3f(0.333, 0.420, 0.184);
	glRasterPos3f(600, 380, 10);
	if (alt == 0)
		glutBitmapString("PLAYER 1 WINS");
	else
		glutBitmapString("PLAYER 2 WINS");
	glutSwapBuffers();
}


void IR(int)
{
	if (alt == 0)
		player_one.distance(r);
	else
		player_two.distance(r);
}
void IR2(int a) // Update y of current pawn
{
	if (alt == 0)
		player_one.updatey();
	else
		player_two.updatey();
}
void IR3(int i)
{
	if (alt == 0)
		player_one.tryy(i);
	else
		player_two.tryy(i);
}
void IR4(int i)
{
	if (alt == 0)
		player_one.try2(i);
	else
		player_two.try2(i);
}
void game_screen() // Gameply Screen
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 0.8, 1.0); // Background Color "Yellow"

	// Display Dice
	glPushMatrix();
	glTranslatef(1200.0, 600.0, 0.0);
	glRotatef(theta[0], 1.0, 1.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glTranslatef(-1200.0, -600.0, 0.0);
	colorcube();
	glPopMatrix();

	// Does nothing?
	glColor3f(0.25, 0.50, 0.75);
	glFlush();

    // Display start position
    glColor3f(0.000, 0.000, 0.545);
    glRasterPos3f(boardLeftPos - 120, boardBottomPos + 30, 20.0);
    glutBitmapString("START");

	// Display Player 1 and Player 2
	player_one.disp();
	player_two.disp();

	// Display Board
	rect();

	// Text Color for Player 1 and Player 2
	glColor3f(0.000, 0.000, 0.545);

    // Display Title of Game
    glRasterPos3f(50.0, 700.0, 20.0);
    glutBitmapString("SNAKES & LADDERS");


    // Display Creator
    glRasterPos3f(50.0, 50.0, 20.0);
    glutBitmapString("Created by: ");
    glRasterPos3f(50.0, 30.0, 20.0);
    glutBitmapString("Hilary McGee");

	// Display Player 1 and Player 2
	glRasterPos3f(50.0, 600.0, 20.0);
	glutBitmapString("PLAYER 1 : ");
	glRasterPos3f(50.0, 550.0, 20.0);
	glutBitmapString("PLAYER 2 : ");

	// Player 1 Icon Display
	glColor3f(player_one.get_color_red(), player_one.get_color_green(), player_one.get_color_blue());
	glBegin(GL_QUADS);
	glVertex3f(165.0, 595.0, 20.0);
	glVertex3f(175.0, 605.0, 20.0);
	glVertex3f(165.0, 615.0, 20.0);
	glVertex3f(155.0, 605.0, 20.0);
	glEnd();

	// Player 2 Icon Display
	glColor3f(player_two.get_color_red(), player_two.get_color_green(), player_two.get_color_blue());
	glBegin(GL_QUADS);
	glVertex3f(165.0, 545.0, 20.0);
	glVertex3f(175.0, 555.0, 20.0);
	glVertex3f(165.0, 565.0, 20.0);
	glVertex3f(155.0, 555.0, 20.0);
	glEnd();

	// Static Image Display Push
	glPushMatrix();

	// Roll Dice Button Ellipse
	glTranslatef(1200.0, 300.0, 0.0);
	glColor3f(0.000, 0.000, 0.545);
	glBegin(GL_POLYGON);
	for (i = 0; i < 360; i++)
	{
		float rad = i * DEG2RAD;
		glVertex3f(cos(rad) * 50, sin(rad) * 30, 18.0);
	}
	glEnd();
	glPopMatrix();

	// Roll Dice Button Text
	glColor3f(1.0, 1.0, (201.0 / 255.0));
	glRasterPos3f(1177, 294, 20); //1163, 306, 20
	glutBitmapString("ROLL");

	// Ladders
	ladders();

    // tOP 3d Board Side
	glColor3f(0.333, 0.420, 0.184);
	glBegin(GL_QUADS);
	glVertex3f(boardLeftPos + 20, squareBottomMax[maxy] + 20, 0);
	glVertex3f(boardLeftPos, squareBottomMax[maxy], 10);
	glVertex3f(squareRightMax[maxx], squareBottomMax[maxy], 10);
	glVertex3f(squareRightMax[maxx] + 20, squareBottomMax[maxy] + 20, 0);
	glEnd();

	// Right 3d Board Side
    glColor3f(0.333, 0.420, 0.184);
	glBegin(GL_QUADS);
	glVertex3f(squareRightMax[maxx], squareBottomMax[maxy], 10);
	glVertex3f(squareRightMax[maxx] + 20, squareBottomMax[maxy] + 20, 0);
	glVertex3f(squareRightMax[maxx] + 20, boardBottomPos + 20, 0);
	glVertex3f(squareRightMax[maxx], boardBottomPos, 10);
	glEnd();

	Cylinder_draw();
	glutSwapBuffers();
}
int spincube() // Spin the cube
{
	theta[0] += 12;
	if (theta[0] > 360.0)
	{
		cnt++;
		theta[0] -= 360;
	}
	game_screen();
	if (cnt < 2)
		spincube();
	else
	{
		if (flg)
		{
			srand(time(NULL));
			s = r = (rand() % 6) + 1;
			switch (s)
			{
			case 1:
				theta[1] += 90;
				theta[2] -= 45;
				break;
			case 2:
				theta[2] += 45;
				break;
			case 3:
				theta[2] -= 45;
				break;
			case 4:
				theta[2] += 135;
				break;
			case 5:
				theta[2] += 225;
				break;
			case 6:
				theta[1] -= 90;
				theta[2] -= 45;
				break;
			}
			flg = 0;
			spincube();
		}
	}
	return 0;
}
void change_to_victory_screen(int a)
{
	glutDisplayFunc(victory_screen);
	glClearColor(0.0, 1.0, 1.0, 1.0);
	glutPostRedisplay();
}

void player::tryy(int i) // ?
{
	mt = 0;
	if ((ladder_arr[i].yq * 70.0 + 30 + oy) > q1)
	{
		q1 += speed;
		q2 += speed;
		q3 += speed;
		q4 += speed;
		p1 = snlf(q1, m, c);
		p2 = p1 - 10;
		p3 = p1;
		p4 = p1 + 10;
		glutPostRedisplay();
		glutTimerFunc(1, IR3, i);
	}
	else
		mt = 1;
}
void player::try2(int i) // ?
{
	mt = 0;
	if ((snake_arr[i].yq * 70 + 30 + oy) < q1)
	{
		q1 -= speed;
		q2 -= speed;
		q3 -= speed;
		q4 -= speed;
		if (m != 0)
		{
			p1 = snlf(q1, m, c);
			p2 = p1 - 10;
			p3 = p1;
			p4 = p1 + 10;
		}
		glutPostRedisplay();
		glutTimerFunc(1, IR4, i);
	}
	else
		mt = 1;
}
void player::check() // Check for special movement
{
	int a = (p1 - 350) / 70;
	int b = (q1 - 30) / 70, i;
	for (i = 0; i < 4; i++)
	{
		if (a == ladder_arr[i].xp && b == ladder_arr[i].yp)
		{

			m = (ladder_arr[i].yp * 70.0 + boardBottomPos + oy - (ladder_arr[i].yq * 70.0 + boardBottomPos + oy)) / (ladder_arr[i].xp * 70.0 + boardLeftPos + 30 - (ladder_arr[i].xq * 70.0 + boardLeftPos + 30));
			c = (ladder_arr[i].yp * 70.0 + boardBottomPos + oy - (m * (ladder_arr[i].xp * 70.0 + boardLeftPos + 30)));
			this->tryy(i);
			if (((ladder_arr[i].yq - ladder_arr[i].yp) % 2))
			{
				flag = !flag;
				add *= (-1);
			}
		}
	}
	for (i = 0; i < 4; i++)
	{
		if (a == snake_arr[i].xp && b == snake_arr[i].yp)
		{
			if (snake_arr[i].xp == snake_arr[i].xq)
				m = 0;
			else
				m = (snake_arr[i].yp * 70.0 + boardBottomPos + oy - (snake_arr[i].yq * 70.0 + boardBottomPos + oy)) / (snake_arr[i].xp * 70.0 + boardLeftPos + 30 - (snake_arr[i].xq * 70.0 + boardLeftPos + 30));
			c = (snake_arr[i].yp * 70.0 + boardBottomPos + oy - (m * (snake_arr[i].xp * 70.0 + boardLeftPos + 30)));
			this->try2(i);
			if ((snake_arr[i].yq - snake_arr[i].yp) % 2)
			{
				flag = !flag;
				add *= (-1);
			}
		}
	}
	mt = 1;
}
void player::disp() // Pawn Display
{
	//glColor3f(col1, 1.0, 0.0);
    glColor3f(this->color_red, this->color_green, this->color_blue);
	glBegin(GL_POLYGON);
	glVertex3f(p1, q1, 28);
	glVertex3f(p2, q2, 28);
	glVertex3f(p3, q3, 28);
	glVertex3f(p4, q4, 28);
	glEnd();
	glFlush();
	glutPostRedisplay();
}
void player::updatey() // Update y of current pawn
{
	if (tmp && t)
	{
		tmp -= speed;
		q1 += speed;
		q2 += speed;
		q3 += speed;
		q4 += speed;
		glutPostRedisplay();
		glutTimerFunc(1, IR2, 0);
	}
	else if (this->t && tmp <= 0)
	{
		t--;
		add = add * (-1);
		tmp = 70;
		this->init(t);
		this->distance(t);
	}
	up = 0;
}
void player::init(int r) // Initialize the pawn
{
	this->t = r;
}
void player::distance(int r)
{
	if (flag)
	{
		if ((p1 - 1) < 380 && up)
			this->updatey();
		else if ((p1 + 1) <= (1010) && (this->t) && tmp)
		{
			tmp -= speed;
			p1 += add, p2 += add, p3 += add, p4 += add;
			glutPostRedisplay();
			glutTimerFunc(1, IR, 0);
		}
		else if (this->t && tmp <= 0)
		{
			t -= 1;
			tmp = 70;
			glutPostRedisplay();
			glutTimerFunc(1, IR, 0);
		}
		else if ((p1 + 1) > (1010))
		{
			up = 1;
			flag = 0;
			if (this->t)
			{
				tmp = 70;
				this->updatey();
			}
			if (this->t == 0)
				this->check();
		}
		else if (this->t == 0)
			this->check();
	}
	else
	{
		if (p1 + 1 > 1010 && this->t && up)
		{
			this->updatey();
		}
		else if ((p1 - 1) >= (380) && this->t && tmp)
		{
			tmp -= speed;
			p1 += add, p2 += add, p3 += add, p4 += add;
			glutPostRedisplay();
			glutTimerFunc(1, IR, 1);
		}
		else if (this->t && tmp <= 0)
		{
			t--;
			tmp = 70;
			glutPostRedisplay();
			glutTimerFunc(1, IR, 1);
		}
		else if ((p1 - 1) < (380))
		{
			up = 1;
			flag = 1;
			if (this->t)
			{
				tmp = 70;
				this->updatey();
			}
			if (this->t == 0)
				this->check();
		}
		else if (this->t == 0)
			this->check();
	}
}
int player::check100() // check if pawn is in the last position
{
	int a = (p1 - 350) / 70;
	int b = (q1 - 30) / 70;
	if (b == 9 && (a - r) <= 0)
	{
		if (a - r < 0)
		{
			mt = 1;
			return -1;
		}
		else if ((a - r) == 0)
		{
			this->init(r);
			this->distance(r);
			glutTimerFunc((r + 2) * 1000, change_to_victory_screen, 0);
		}
		return 1;
	}
	return 0;
}

void DrawEllipse(float radiusX, float radiusY) // draw snake head
{
	
	int i;

	// draw snake head ouline
	glColor3f(0.196, 0.804, 0.196);
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < 360; i++)
	{
		float rad = i * DEG2RAD;
		glVertex2f(cos(rad) * radiusX, sin(rad) * radiusY);
	}
	glEnd();

	// snake head filler
	glColor3f(0.196, 0.804, 0.196);
	glBegin(GL_POLYGON);
	for (i = 0; i < 360; i++)
	{
		float rad = i * DEG2RAD;
		glVertex2f(cos(rad) * radiusX, sin(rad) * radiusY);
	}
	glEnd();
}
void Cylinder_draw() // draw snakes
{
	// define snake bodies
	GLfloat xsnake[] = {380, 995, 782, 784}, zsnake[] = {175, 210, 370, 70}, lcarr[] = {0.3, -0.15, 0.30, -0.20, 0.45, -0.15, 0.55, -0.2, 0.70, -0.25, 0.80, -0.35, 0.9};
	GLfloat i;
	GLint j, lc = 0, reploop[] = {70, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 25, 70}, snakeLc[] = {13, 7, 6, 5};
	
	for (j = 0; j < 4; j++) // draw the four snakes
	{
		glColor3f(0.196, 0.804, 0.196);
		glPointSize(20.0);
		lc = 0;
		glBegin(GL_TRIANGLES);
		glVertex3f(xsnake[j] - 10, zsnake[j] - 10, 12);
		glVertex3f(xsnake[j], zsnake[j] - 36, 12);
		glVertex3f(xsnake[j] + 10, zsnake[j] - 10, 12);
		glEnd();

		// snake body
		while (lc < snakeLc[j])
		{

			for (i = 0; i < reploop[lc]; i++)
			{
				glBegin(GL_POINTS);
				glVertex3i(xsnake[j]-5, zsnake[j]-5, 12);
				glEnd();
				zsnake[j]++;
				if (j % 2 == 0)
					xsnake[j] += lcarr[lc];
				else
					xsnake[j] -= lcarr[lc];
			}
			lc++;
		}

		// Full snake head with face

		// glPushMatrix();
		// glTranslatef(xsnake[j], zsnake[j], 18);
		// glColor3f( 	0.000, 0.000, 0.000);
		// glPointSize(3.0);

		// glBegin(GL_POINTS);
		// glVertex3f(-12.5, 7.5, 20);
		// glVertex3f(12.5, 7.5, 20);
		// glEnd();

		// glBegin(GL_POLYGON);
		// glVertex3f(0, -1, 20);
		// glVertex3f(-4, -13, 20);
		// glVertex3f(-4, -1, 20);
		// glVertex3f(4, -1, 20);
		// glVertex3f(4, -13, 20);
		// glEnd();

		// DrawEllipse(25, 15);
		// glPopMatrix();

        glPushMatrix();
		glTranslatef(xsnake[j], zsnake[j], 18);
		glColor3f( 	0.000, 0.000, 0.000);
		glPointSize(3.0);

        // snake eyes
		glBegin(GL_POINTS);
		glVertex3f(-10, 6, 20);
		glVertex3f(10, 6, 20);
		glEnd();

        // snake mouth
		glBegin(GL_POLYGON);
		glVertex3f(0, -1, 20);
		glVertex3f(-4, -13, 20);
		glVertex3f(-4, -1, 20);
		glVertex3f(4, -1, 20);
		glVertex3f(4, -13, 20);
		glEnd();

		DrawEllipse(20, 11);
		glPopMatrix();
	}
}
void rect() // Board Draw Function
{
	// Creates Bounding Array for Tiles
	int i, j, k;
	squareRightMax[-1] = boardLeftPos;
	squareBottomMax[-1] = boardBottomPos;
	for (i = 0; i <= maxx; i++) {
        squareRightMax[i] = boardLeftPos + i * squareWidth;
        squareBottomMax[i] = boardBottomPos + i * squareHeight;
    }

	// Board Background Draw
	glColor3f(1.000, 0.894, 0.710); // Grey
	glBegin(GL_QUADS);
	glVertex3f(boardLeftPos, 		boardBottomPos, 	 10);
	glVertex3f(squareRightMax[maxx], boardBottomPos, 	 10);
	glVertex3f(squareRightMax[maxx], squareBottomMax[maxy], 10);
	glVertex3f(boardLeftPos, 		squareBottomMax[maxy], 10);
	glEnd();

	// Draw Tile Numbers and Borders
	int tileNum = 1;
	int direction = 1;
	i = 0;

    // Draw Board Border to fix bug with GL_LINE_LOOP around each square
    glColor3f(0.333, 0.420, 0.184);
    glBegin(GL_LINES);
    glVertex3f(squareRightMax[maxx], squareBottomMax[0], 11);
    glVertex3f(squareRightMax[maxx], squareBottomMax[maxy], 11);
    glVertex3f(squareRightMax[0], squareBottomMax[maxy], 11);
    glVertex3f(squareRightMax[maxx], squareBottomMax[maxy], 11);
    glEnd();

	for (j = 0; j < maxy; j++) { // for each row bottom to top
		while (1) { // for each column left to right

			if (direction < 0) 		// if going left
			{
				if (i < 0) 			// if left end
					break;          // go next row
			}
			else 					// if going right
			{
				if (i > maxx - 1) 	// if right end
					break;          // go next row
			}

			// Square Border Draw
			glColor3f(0.333, 0.420, 0.184);
			glBegin(GL_LINE_LOOP);
			glVertex3f(squareRightMax[i				], squareBottomMax[j		], 11);
			glVertex3f(squareRightMax[i				], squareBottomMax[j + 1	], 11);
			glVertex3f(squareRightMax[i + direction	], squareBottomMax[j + 1	], 11);
			glVertex3f(squareRightMax[i + direction	], squareBottomMax[j		], 11);
			glEnd();

			// Tile Number Draw
			glColor3f(0, 0, 0);
			glRasterPos3f(squareRightMax[i] + 10, squareBottomMax[j] + 10, 20);
			k = 0;
			sprintf(mess, "%d", tileNum);
			if (tileNum == 100)
				strcpy(mess, "END");
			glutBitmapString(mess);
			tileNum++;
			i += direction;
		}

		if (direction > 0) 	// If going right, go left
		{
			direction = -1;
		}
		else 				// If going left, go right
		{
			direction = 1;
		}

		i += direction; 	// go next tile
	}
}



// void display1() // Intro Screen
// {
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 	glClearColor(1.0, 1.0, 0.8, 1.0);
// 	int i;
// 	// Text Color
// 	glColor3f(0.333, 0.420, 0.184);
// 	// Text Position and Name
// 	glRasterPos3f(400, 700, 10);
// 	glutBitmapString("SIR M.VISVESVARAYA INSTITUTE OF TECHNOLOGY");
// 	glRasterPos3f(370, 650, 10);
// 	glutBitmapString("DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
// 	glRasterPos3f(600, 600, 10);
// 	glutBitmapString("SNAKE 'N' LADDER");
// 	glRasterPos3f(200, 400, 10);
// 	glutBitmapString("USN : 1MV12CS055");
// 	glRasterPos3f(200, 350, 10);
// 	glutBitmapString("USN : 1MV12CS052");
// 	glRasterPos3f(850, 400, 10);
// 	glutBitmapString("NAME : MOHAMMED IBRAHIM B");
// 	glRasterPos3f(850, 350, 10);
// 	glutBitmapString("NAME : MANJUNATH S HORAPETI");
// 	glRasterPos3f(200, 200, 10);
// 	glutBitmapString("UNDER THE GUIDANCE OF : Mr.SHANKAR R");
// 	// "NEXT" button Border
// 	glColor3f(1.000, 0.000, 0.000);
// 	glBegin(GL_LINE_LOOP);
// 	glVertex3f(615.0, 100.0, 10.0);
// 	glVertex3f(615.0, 140.0, 10.0);
// 	glVertex3f(710.0, 140.0, 10.0);
// 	glVertex3f(710.0, 100.0, 10.0);
// 	glEnd();
// 	// "NEXT" button Color "Light Grey" Background
// 	glColor3f(1.000, 0.000, 0.000);
// 	glBegin(GL_QUADS);
// 	glVertex3f(615.0, 100.0, 9.0);
// 	glVertex3f(615.0, 140.0, 9.0);
// 	glVertex3f(710.0, 140.0, 9.0);
// 	glVertex3f(710.0, 100.0, 9.0);
// 	glEnd();
// 	// "NEXT" button Text
// 	glColor3f(1.000, 1.000, 0.000);
// 	glRasterPos3f(630, 110, 10.0);
// 	glutBitmapString("NEXT");
// 	glFlush(); // Immediate Render
// 	glutSwapBuffers();
// }

void mouse(int btn, int state, int x, int y)
{
    if (x >= ((1140 * width) / 1367) && x <= ((1260 * width) / 1367) && y <= (((767 - 260) * height) / 767) && y >= (((767 - 340) * height) / 767))
    {
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mt)
        {
            cnt = 0;
            flg = 1;
            theta[1] = 90;
            theta[2] = 45;
            mt = 0;
            int a = spincube();
            alt = !alt;
            if (a == 0 && alt == 0)
            {
                if (player_one.check100() == 0)
                {
                    player_one.init(r);
                    player_one.distance(r);
                }
            }
            else
            {
                if (player_two.check100() == 0)
                {
                    player_two.init(r);
                    player_two.distance(r);
                }
            }
        }
    }
	// }
}

void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
		exit(0);
		break;
	}

	glutPostRedisplay();
}
void myReshape(int w, int h) // glut resize window function
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1367.0, 0.0, 767.0, -180.0, 180.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 0.8, 1.0);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1366, 768);
	srand(time(NULL));
	selec = rand() % 3;
	glEnable(GL_POLYGON_SMOOTH);
	glutCreateWindow("Snakes and Ladders");
	// glutFullScreen();
	glLineWidth(2.0);

    // Init Cube Rotation
    theta[1] = 90;
    theta[2] = 45;
    spincube();

	glutDisplayFunc(game_screen);
	glEnable(GL_DEPTH_TEST);
	glutMouseFunc(mouse);
	glutKeyboardFunc(key);
	glutReshapeFunc(myReshape);
	glutMainLoop();
}