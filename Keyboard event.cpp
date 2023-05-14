#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI		3.1415926
#define		Move_Speed	5		//ȭ���� �����¿�� �̵��ϴ� �ӵ�
#define		Color_Speed 0.2		//������ ���ϴ� �ӵ� (0~1)
#define		Radius_Speed 10		//�׷����� ������ �������� Ŀ���� ������

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
	Modeling_Rectangle();	// 1��и鿡 �ִ� ���簢�� 
	Modeling_Axis();		// x��� y�� 
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
	case '0':	//glViewport�� �����ϴ� ��ǥ�� (0, 0)���� ����� �ٽ� ó�� �߾� ��ġ�� �̵�
	{
		Move_x = 0;
		Move_y = 0;
		glViewport(Move_x, Move_y, Window_Width, Window_Height);
		break;
	}
	case 'q':		//q , w ++  ��ũ��� Radius_Speed ��ŭ ����, ���� �ϸ� ���� ���� 1 ��ŭ ����, ����
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

	case '1':	// 1, 2, 3 �� ����Ͽ� ,POLYGON ,POINTS, LINE_LOOP�� ���
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
	// 7 8 9 ++  R.G.B ������ Color_Speed �� �߽ɿ� �׸��� ���� ���� ����
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
	case 'e':	//e ++ glViewport�� ����� ���� ������� ȭ���� 3/4�� ��� �ϰų� 4/3���� Ȯ�� 
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

void MySpecial(int key, int x, int y) //glViewport�� Ű���� ȭ��ǥ�� �̿��Ͽ� �����¿��  Move_Speed ��ŭ �̵��ϴ� �Լ�
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
	glutCreateWindow("20193151 �赿��");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKey);
	glutSpecialFunc(MySpecial);
	glutMainLoop();
	return 0;
}