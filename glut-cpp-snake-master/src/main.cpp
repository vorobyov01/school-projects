#include <GL/glut.h>
#include <vector>
#include <stdint.h>
//#include <iostream>

using namespace std;
const int8_t M = 20;
const int8_t N = 30;
const int8_t DPI = 20;

int num = 4;
int dir = 1;

class Apple{
	public:
		int x, y;
		void New() {
			x = rand() % N;
			y = rand() % M;
		}
		void DrawApple() {
			glColor3f(1.0, 0.0, 0.0);
			glRectf(x*DPI, y*DPI, (x+1)*DPI, (y+1)*DPI);
		}
} m[10];

struct {
	int x;
	int y;
} snake[100];


const int w = N*DPI;
const int h = M*DPI;
void KeyboardEvent(int key, int a, int b);
void Tick();
void drawSnake();
void timer(int = 0);
void drawField();
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawField();
	drawSnake();
	for (int i = 0; i < 10; i++) {
		m[i].DrawApple();
	}
	glEnd();
	glFlush();
}

int main(int argc, char **argv) {
	/*snake[0].y = snake[1].y = snake[2].y = snake[3].y = 15;
	snake[0].x = 5; snake[1].x = 4; snake[2].x = 3; snake[3].x = 2;*/
	snake[0].x = snake[0].y = 10;
	for (int i  = 0; i < 10; i++)
		m[i].New();
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize (w, h);
	glutCreateWindow ("Snake"); 
	glClearColor(1.0,1.0,0.6,1.0);  //цвет фона
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w,0,h);
	glutDisplayFunc (display);
	glutSpecialFunc(KeyboardEvent);
	glutTimerFunc(50, timer, 0);
	glutMainLoop();
}


void drawField() {
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);

	for (int i = 0; i < w; i+=DPI) {
		glVertex2f(i, 0); glVertex2f(i, h);
	}
	for (int i = 0; i < h; i+=DPI) {
		glVertex2f(0, i); glVertex2f(w, i);
	}
	glEnd();
}
void timer(int) {
	display();
	Tick();
	glutTimerFunc(50, timer, 0);
}

void Tick() {
	for (int i = num-1; i >= 1; i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}
	for (int i = 0; i < 10; i++) {
		if (snake[0].x == m[i].x && snake[0].y == m[i].y) {
			m[i].New();
			num++;
			snake[num-1].x = snake[num-2].x; snake[num-1].y = snake[num-2].y;	
		}
	}
	if(dir == 0) snake[0].x--;
	if(dir == 1) snake[0].y++;
	if(dir == 2) snake[0].x++;
	if(dir == 3) snake[0].y--;
	if (snake[0].x >= N) snake[0].x = 0;
	if (snake[0].x < 0)	snake[0].x = N;
	if (snake[0].y >= M) snake[0].y = 0;
	if (snake[0].y < 0) snake[0].y = M;
	//cout << snake[0].x << " " << snake[0].y << endl;
}

void KeyboardEvent(int key, int a, int b) {
	if (key == 100 && dir != 2) dir = 0;
	if (key == 101 && dir != 3) dir = 1;
	if (key == 102 && dir != 0) dir = 2;
	if (key == 103 && dir != 1) dir = 3;
}

void drawSnake() {
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < num; i++) {
		glRectf(snake[i].x*DPI, snake[i].y*DPI, (snake[i].x+1)*DPI, (snake[i].y+1)*DPI);
	}
}
