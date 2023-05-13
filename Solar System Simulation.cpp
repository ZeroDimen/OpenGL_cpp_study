#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI	3.1415926

int			Width = 800;
int			Height = 800;

float		sun_radius = 70.0;

float		MercuryRotation = 0.0, earthRotation = 0.0, moonRotation = 0.0;

float		Mercury_rotation_speed = 0.0414;	//������ ���� �ӵ��� 4.14��
float		earth_rotation_speed = 0.01;		//���Ƿ� ���� ������ ���� �ӵ�
float		moon_rotation_speed = 0.1351;		//������ ���� �ӵ��� 13.51��


void init(void) {
	glMatrixMode(GL_PROJECTION); //�����  ���ؼ� ���������� ��� ȭ�鿡 �Ѹ� ��
	glLoadIdentity();
	gluOrtho2D(-1.0 * Width / 2.0, Width / 2.0, -1.0 * Height / 2.0, Height / 2.0);
}


void Draw_Circle(float c_radius) {
	float	delta;
	int		num = 36;

	delta = 2 * PI / num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++)
		glVertex2f(c_radius * cos(delta * i), c_radius * sin(delta * i));
	glEnd();
}



void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); // Set display-window color to black.

	MercuryRotation += Mercury_rotation_speed;
	earthRotation += earth_rotation_speed;
	moonRotation += moon_rotation_speed;

	/***********�ڵ� �ۼ��ϱ� ***************/
	// �¾� : �������� �� 
	glColor3f(1.0, 0.0, 0.0);
	Draw_Circle(sun_radius);

	// ���� : ȸ���� �� 
	glPushMatrix(); // �� �Լ��� �Ҹ��� ���� ��ȯ ��ǥ�� ����
	glRotatef(MercuryRotation, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 150, 0.0);	//���� ���� y������ 150��ŭ �̵�
	glScalef(0.17, 0.17, 0.0); // ���� ũ���� 1/3 
	glColor3f(0.7, 0.7, 0.7);
	Draw_Circle(sun_radius); 

	glPopMatrix(); // ������ glPushMatrix()  ������ ��ǥ ���¸� �ٽ� ȣ��

	// ���� : �ʷϻ��� �� 
	glPushMatrix();	// �� �Լ��� �Ҹ��� ���� ��ȯ ��ǥ�� ����
	glRotatef(earthRotation, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 300, 0.0);	//���� ���� y������ 300��ŭ �̵�
	glScalef(0.5, 0.5, 0.0); // ���Ƿ� ���� �¾� ũ���� 1/2
	glColor3f(0.0, 1.0, 0.0);
	Draw_Circle(sun_radius);



	// ��   : ������� �� 
	glPushMatrix();	// �� �Լ��� �Ҹ��� ���� ��ȯ ��ǥ�� ����
	glRotatef(moonRotation, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 150.0, 0.0);	//���� ��ġ ���� y������ 150��ŭ �̵�
	glScalef(0.25, 0.25, 0.0); // ���� ũ���� 1/4
	glColor3f(1.0, 1.0, 0.0);
	Draw_Circle(sun_radius);


	
	glPopMatrix(); //������ glPushMatrix()  ������ ��ǥ ���¸� �ٽ� ȣ��
	glPopMatrix(); //���� glPushMatrix()  ������ ��ǥ ���¸� �ٽ� ȣ��


	glFlush();
	glutSwapBuffers();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Solar System");
	init();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}

