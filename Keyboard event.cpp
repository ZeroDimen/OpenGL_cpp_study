#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI		3.1415926
#define		Move_Speed	5		//화면이 상하좌우로 이동하는 속도
#define		Color_Speed 0.2		//색상이 변하는 속도 (0~1)
#define		Radius_Speed 10		//그려지는 원형의 반지름의 커지는 증가량

float		Move_x = 0;
float		Move_y = 0;

float		Window_Width = 500;
float		Window_Height = 500;

int			num = 10;
float		Radius = 30;
int			Draw = 3;

float		Color_Red = 0;
float		Color_Green = 0;
float		Color_Blue = 0;



void Modeling_Circle_POLYGON(void) {
	float	delta, theta;
	float	x, y;

	glColor3f(Color_Red, Color_Green, Color_Blue);
	glPointSize(3.0);
	delta = 2 * PI / num;

	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++) {
		theta = delta * i;
		x = Radius * cos(theta);
		y = Radius * sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
}

void Modeling_Circle_POINTS(void) {
	float	delta, theta;
	float	x, y;

	glColor3f(Color_Red, Color_Green, Color_Blue);
	glPointSize(3.0);
	delta = 2 * PI / num;

	glBegin(GL_POINTS);
	for (int i = 0; i < num; i++) {
		theta = delta * i;
		x = Radius * cos(theta);
		y = Radius * sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
}

void Modeling_Circle_LINE_LOOP(void) {
	float	delta, theta;
	float	x, y;

	glColor3f(Color_Red, Color_Green, Color_Blue);
	glPointSize(3.0);
	delta = 2 * PI / num;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num; i++) {
		theta = delta * i;
		x = Radius * cos(theta);
		y = Radius * sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
}


void Modeling_Axis(void) {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-250.0, 0.0);
	glVertex2f(250.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0, -250.0);
	glVertex2f(0, 250.0);
	glEnd();
}

void Modeling_Rectangle(void) {
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(100, 100);
	glVertex2i(150, 100);
	glVertex2i(150, 150);
	glVertex2i(100, 150);
	glEnd();
}

void Modeling_Ground(void) {
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2i(250, 250);
	glVertex2i(-250, 250);
	glVertex2i(-250, -250);
	glVertex2i(250, -250);
	glEnd();
}


void RenderScene(void) {
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	Modeling_Ground();
	Modeling_Rectangle();	// 1사분면에 있는 정사각형 
	Modeling_Axis();		// x축과 y축 
	if (Draw == 1)
	{
		Modeling_Circle_POINTS();
	}
	else if (Draw == 2)
	{

		Modeling_Circle_LINE_LOOP();
	}
	else if (Draw == 3)
	{
		Modeling_Circle_POLYGON();
	}
	glFlush();
}

void MyReshape(int w, int h) {
	Window_Width = w;
	Window_Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0 / 2.0 * w, 1.0 / 2.0 * w, -1.0 / 2.0 * h, 1.0 / 2.0 * h);
}

void MyKey(unsigned char key, int x, int y) {
	switch (key)
	{
	case '0':	//glViewport가 시작하는 좌표를 (0, 0)으로 만들어 다시 처음 중앙 위치로 이동
	{
		Move_x = 0;
		Move_y = 0;
		glViewport(Move_x, Move_y, Window_Width, Window_Height);
		break;
	}
	case 'q':		//q , w ++  원크기는 Radius_Speed 만큼 증가, 감소 하며 점의 수는 1 만큼 증가, 감소
	{				//a , s --
		Radius += Radius_Speed;
		break;
	}
	case 'a':
	{
		Radius -= Radius_Speed;
		break;
	}

	case 'w':
	{
		num += 1;
		break;
	}
	case 's':
	{
		num -= 1;
		break;
	}

	case '1':	// 1, 2, 3 을 사용하여 ,POLYGON ,POINTS, LINE_LOOP로 출력
	{
		Draw = 1;
		break;
	}
	case '2':
	{
		Draw = 2;
		break;
	}
	case '3':
	{
		Draw = 3;
		break;
	}
	// 7 8 9 ++  R.G.B 순으로 Color_Speed 씩 중심에 그리는 도형 색상 변경
	// 4 5 6 --
	case '7':
	{
		Color_Red += Color_Speed;
		break;
	}
	case '4':
	{
		Color_Red -= Color_Speed;
		break;
	}
	case '8':
	{
		Color_Green += Color_Speed;
		break;
	}
	case '5':
	{
		Color_Green -= Color_Speed;
		break;
	}
	case '9':
	{
		Color_Blue += Color_Speed;
		break;
	}
	case '6':
	{
		Color_Blue -= Color_Speed;
		break;
	}
	case 'e':	//e ++ glViewport를 사용해 현제 출력중인 화면을 3/4로 축소 하거나 4/3으로 확대 
	{			//d --
		Window_Width = Window_Width * 4 / 3;
		Window_Height = Window_Height * 4 / 3;
		Move_x = Move_x - Window_Width / 8;
		Move_y = Move_y - Window_Height / 8;
		glViewport(Move_x, Move_y, Window_Width, Window_Height);
		break;
	}
	case 'd':
	{
		Move_x = Move_x + Window_Width / 8;
		Move_y = Move_y + Window_Height / 8;
		Window_Width = Window_Width * 3 / 4;
		Window_Height = Window_Height * 3 / 4;
		glViewport(Move_x, Move_y, Window_Width, Window_Height);
		break;
	}

	default:
	{
		break;
	}

	}
	glutPostRedisplay();

}

void MySpecial(int key, int x, int y) //glViewport를 키보드 화살표를 이용하여 상하좌우로  Move_Speed 만큼 이동하는 함수
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
	{
		Move_x -= Move_Speed;

		glViewport(Move_x, Move_y, Window_Width, Window_Height);
		break;
	}
	case GLUT_KEY_RIGHT:
	{
		Move_x += Move_Speed;
		glViewport(Move_x, Move_y, Window_Width, Window_Height);
		break;
	}
	case GLUT_KEY_UP:
	{
		Move_y += Move_Speed;
		glViewport(Move_x, Move_y, Window_Width, Window_Height);
		break;
	}
	case GLUT_KEY_DOWN:
	{
		Move_y -= Move_Speed;
		glViewport(Move_x, Move_y, Window_Width, Window_Height);
		break;
	}
	default:
	{
		break;
	}
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("20193151 김동건");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKey);
	glutSpecialFunc(MySpecial);
	glutMainLoop();
	return 0;
}