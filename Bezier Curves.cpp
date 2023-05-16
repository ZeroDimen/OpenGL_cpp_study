#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)
#include <iostream>
using namespace std;

#define		Window_Width	800
#define		Window_Height	800

int			point[100][2];
int			num = 0;

double factorial(int f_num)
{
	double sum = 1;

	for (int i = 1; i <= f_num; i++)
	{
		sum = sum * i;
	}
	return sum;
}

float binomial(int binomial_n, int binomial_i)
{
	float value = 0;

	value = factorial(binomial_n) / (factorial(binomial_n - binomial_i) * factorial(binomial_i));

	return value;
}

float bernstein(int bernstein_n, int bernstein_i, float bernstein_t)
{
	float b_value = 0;

	b_value = binomial(bernstein_n, bernstein_i)
		* pow(1.0 - bernstein_t, bernstein_n - bernstein_i)
		* pow(bernstein_t, bernstein_i);

	return b_value;
}

void Draw_Bezier_Curve(void) {

	int curve_degree;
	float curvepoint_num = 100; // 주어진 선분을 몇 등분 할건지
	float partial_time;			// n등분한 선분의 길이
	float time;
	float sum_x, sum_y;

	curve_degree = num - 1;
	partial_time = 1.0 / curvepoint_num; 

	glColor3f(1.0, 1.0, 0.0);

	glBegin(GL_LINE_STRIP);

	for (time = 0; time <= 1.0; time = time + partial_time) //n 등분한 선분의 길이 합이 1이 넘기전까지 반복
	{
		sum_x = 0;
		sum_y = 0;

		for (int i = 0; i <= curve_degree; i++) // 마우스 클릭시 입력된 점의 개수 - 1만큼 반복
		{
			sum_x = sum_x + bernstein(curve_degree, i, time) * point[i][0];
			sum_y = sum_y + bernstein(curve_degree, i, time) * point[i][1];
		}
		glVertex2f(sum_x, sum_y);
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