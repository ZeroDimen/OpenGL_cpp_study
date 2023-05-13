#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#define	PI	3.1415926

//3차원에서 구, 원의 이동을 하기위한 변수
float phi, theta;
float delta_phi, delta_theta;

//평면에 영향을 주는 변수
float shape_height, shape_angle;
bool moving_shape, stop_shape;

//gluLookAt에 영향을 주는 변수
float eye_x, eye_y, eye_z;
float eye_axis_distance;
float cam_turn;


// 3차원 좌표의 점을 조절하는 구조체
GLfloat		vertices[][3] =
{
		{ -1.0, -1.0,  1.0 },		// 0 
		{ -1.0,  1.0,  1.0 },		// 1
		{ 1.0,  1.0,  1.0 },		// 2
		{ 1.0, -1.0,  1.0 },		// 3
		{ -1.0, -1.0, -1.0 },		// 4
		{ -1.0,  1.0, -1.0 },		// 5
		{ 1.0,  1.0, -1.0 },		// 6
		{ 1.0, -1.0, -1.0 },		// 7


};
// 색상을 조절하는 구조체
GLfloat		colors[][3] =
{
		{ 1.0, 0.0, 0.0 },			// red
		{ 0.0, 1.0, 0.0 },			// green 
		{ 1.0, 1.0, 0.0 },			// yellow
		{ 1.0, 1.0, 1.0 },			// white
		{ 0.0, 0.0, 1.0 },			// blue
		{ 1.0, 0.0, 1.0 },			// magenta
};
void polygon(int a, int b, int c, int d) // 폴리곤 형태의 선을 그어 면을 만드는 함수
{
	glColor3fv(colors[a]);
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}
void shape_side_1() //왼쪽 앞 평면
{
	glPushMatrix();
	glTranslatef(1.0, 0.0, -1.0);
	glRotatef(shape_angle, 0.0, 1.0, 0.0);
	glTranslatef(-1.0, 0.0, 1.0);
	polygon(2, 3, 7, 6);
	glPopMatrix();
}
void shape_side_2() //오른쪽 앞 평면
{
	glPushMatrix();
	glTranslatef(0.0, 1.0, -1.0);
	glRotatef(shape_angle, -1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 1.0);
	polygon(1, 2, 6, 5);
	glPopMatrix();
}
void shape_side_3() //오른쪽 뒤 평면
{
	glPushMatrix();
	glTranslatef(-1.0, 0.0, -1.0);
	glRotatef(shape_angle, 0.0, -1.0, 0.0);
	glTranslatef(1.0, 0.0, 1.0);
	polygon(5, 4, 0, 1);
	glPopMatrix();
}
void shape_side_4() //왼쪽 뒤 평면
{
	glPushMatrix();
	glTranslatef(0.0, -1.0, -1.0);
	glRotatef(shape_angle, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 1.0, 1.0);
	polygon(3, 0, 4, 7);
	glPopMatrix();
}
void shape_side_5() //위 평면
{
	glPushMatrix();
	glTranslatef(0.0, 0.0, shape_height);
	polygon(0, 3, 2, 1);
	glPopMatrix();
}
void shape_side_6()	//아래 평면
{
	polygon(4, 5, 6, 7);
}
void cube(void) // 선을 그어 면을 만드는 함수를 어러게 호출
{
	shape_side_1();
	shape_side_2();
	shape_side_3();
	shape_side_4();
	shape_side_5();
	shape_side_6();
}
void reshape(int w, int h) // 화면의 크기를 변동 시키면 호출 되는 함수
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 20.0);
}
void axis(void) // 3차원 공간의 0.0 이 원점인 축을 그리는 함수
{

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x축 (빨강)
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y축 (초록)
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z축 (파랑)
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}
void frame_reset(void) {
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void camera(void) // 3차원 공간을 평면으로 보여주기위한 카메라
{
	cam_turn = 1.0; // 카메라의 z축 벡터 선언을 여기서 하는 것으로 음수로 바뀐 카메라의 벡터를 다시 양수로 바꾸지않음

	eye_x = eye_axis_distance * cos(phi) * cos(theta);
	eye_y = eye_axis_distance * cos(phi) * sin(theta);
	eye_z = eye_axis_distance * sin(phi);

	if (cos(phi) < 0) // cos(phi)를 계산하여 0보다 작으면 Lookat 함수의 시점이 바뀌는 것을 조절함
	{
		cam_turn = cam_turn * -1.0;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye_x, eye_y, eye_z, 0.0, 0.0, 0.0, 0.0, 0.0, cam_turn);
}
void display(void) // 기본으로 호출되는 함수
{
	glEnable(GL_DEPTH_TEST);
	frame_reset();

	camera();
	axis();
	cube();

	if (stop_shape == FALSE) // 도형이 펼쳐지는 중 스페이스바 입력시 멈추거나 다시 진행
	{
		if (moving_shape == TRUE && shape_angle < 90) //(Act == TRUE)'t'키 입력시 육면체 옆면을 펼치고 윗면을 하늘로 보냄
		{
			shape_angle = shape_angle + 0.7;
			shape_height = shape_height + 0.02;
		}
		if (moving_shape == FALSE && shape_angle > 0) //(Act == FALSE)'t'키 입력시 펼쳐진 육면체와 하늘로 보낸 윗면을 다시 되돌림
		{
			shape_angle = shape_angle - 0.7;
			shape_height = shape_height - 0.02;
		}
	}

	glFlush();
	glutSwapBuffers();
}
void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		phi = phi - delta_phi;
		break;
	case GLUT_KEY_DOWN:
		phi = phi + delta_phi;
		break;
	case GLUT_KEY_LEFT:
		theta = theta - delta_theta;
		break;
	case GLUT_KEY_RIGHT:
		theta = theta + delta_theta;
		break;
	case GLUT_KEY_F1:
		eye_axis_distance = eye_axis_distance + 1; //F1키 입력시 정육면체와의 거리가 증가
		break;
	case GLUT_KEY_F2:
		eye_axis_distance = eye_axis_distance - 1; //F1키 입력시 정육면체와의 거리가 감소
		break;

	}
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 't': //t 입력시 펼쳐지거나 다시 접히는 기능
		moving_shape = moving_shape ? FALSE : TRUE;
		stop_shape = FALSE;
		break;
	case 32: //스페이스바 입력시 멈춤
	{
		stop_shape = stop_shape ? FALSE : TRUE;
	}

	}
	glutPostRedisplay();
}
void init()
{
	glEnable(GL_DEPTH_TEST);

	phi = 0.5;
	theta = 1.0;
	delta_phi = 0.1;
	delta_theta = 0.1;

	eye_axis_distance = 6.0;


	shape_angle = 0.0;
	moving_shape = FALSE;
	stop_shape = FALSE;
}
void main(int argc, char** argv) // 메인 함수
{
	glutInit(&argc, argv);
	init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutIdleFunc(display);
	glutMainLoop();
}