﻿#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)
#include <iostream>

#define		Window_Width	800
#define		Window_Height	800

int			point[100][2];
int			num = 0;

double factorial(int n)
{
	if (n <= 1) return 1;
	else return n * factorial(n - 1);
}

double binomial(int n, int i) // 조합
{
	float value = factorial(n) / (factorial(n - i) * factorial(i));
	return value;
}

float bernstein(int degree, int index, float time)
{
	float value;
	value = binomial(degree, index) * pow((1 - time), degree - index) * pow(time, index);
	return value;
}

void Draw_Bezier_Curve(void)
{
	int curve_degree;
	int curvepoint_num = 25; // 한 점과 한 점 사이에 몇등분 할것인지
	float patial_time;
	float sumx;
	float sumy;
	float time = 0;
	glColor3f(1.0, 1.0, 0.0);

	curve_degree = num - 1; // 점의 개수 - 1 차식
	patial_time = 1.0 / curvepoint_num;

	glBegin(GL_LINE_STRIP);
	for (curvepoint_num; curvepoint_num >= 0; curvepoint_num--) // curvepoint_num 등분한 만큼 반복
	{
		sumx = sumy = 0.0;

		for (int i = 0; i <= curve_degree; i++)
		{
			sumx += bernstein(curve_degree, i, time) * point[i][0];
			sumy += bernstein(curve_degree, i, time) * point[i][1];
		}

		time += patial_time; // curvepoint_num 한부분인 patial_time만큼 0부터 1까지 반복해서 더함

		glVertex2f(sumx, sumy);
	}
	glEnd();
}
void Draw_Control_Points(void) {

	glPointSize(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (int k = 0; k < num; k++) {
		glVertex2f(point[k][0], point[k][1]);
	}
	glEnd();

}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glColor3f(1.0, 0.0, 0.0);

	if (num >= 1)
		Draw_Control_Points();
	if (num >= 2)
		Draw_Bezier_Curve();

	glFlush();
	glutSwapBuffers();
}
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	glLoadIdentity();
	gluOrtho2D(0, Window_Width, 0, Window_Height);
}
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		point[num][0] = x;
		point[num][1] = Window_Height - y;
		num++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		num = 0;
	}
	glutPostRedisplay();
	RenderScene();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("Bezier Curve");
	init();
	glutDisplayFunc(RenderScene);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}