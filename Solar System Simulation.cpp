#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI	3.1415926

int			Width = 800;
int			Height = 800;

float		sun_radius = 70.0;

float		MercuryRotation = 0.0, earthRotation = 0.0, moonRotation = 0.0;

float		Mercury_rotation_speed = 0.0414;	//지구의 공전 속도의 4.14배
float		earth_rotation_speed = 0.01;		//임의로 만든 지구의 공전 속도
float		moon_rotation_speed = 0.1351;		//지구의 공전 속도의 13.51배


void init(void) {
	glMatrixMode(GL_PROJECTION); //행렬을  곱해서 최종적으로 어떻게 화면에 뿌릴 것
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

	/***********코드 작성하기 ***************/
	// 태양 : 빨간색의 구 
	glColor3f(1.0, 0.0, 0.0);
	Draw_Circle(sun_radius);

	// 수성 : 회색의 구 
	glPushMatrix(); // 이 함수가 불리기 전의 변환 좌표를 저장
	glRotatef(MercuryRotation, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 150, 0.0);	//원점 기준 y축으로 150만큼 이동
	glScalef(0.17, 0.17, 0.0); // 지구 크기의 1/3 
	glColor3f(0.7, 0.7, 0.7);
	Draw_Circle(sun_radius); 

	glPopMatrix(); // 수성의 glPushMatrix()  이전의 좌표 상태를 다시 호출

	// 지구 : 초록색의 구 
	glPushMatrix();	// 이 함수가 불리기 전의 변환 좌표를 저장
	glRotatef(earthRotation, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 300, 0.0);	//원점 기준 y축으로 300만큼 이동
	glScalef(0.5, 0.5, 0.0); // 임의로 만든 태양 크기의 1/2
	glColor3f(0.0, 1.0, 0.0);
	Draw_Circle(sun_radius);



	// 달   : 노랑색의 구 
	glPushMatrix();	// 이 함수가 불리기 전의 변환 좌표를 저장
	glRotatef(moonRotation, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 150.0, 0.0);	//지구 위치 기준 y축으로 150만큼 이동
	glScalef(0.25, 0.25, 0.0); // 지구 크기의 1/4
	glColor3f(1.0, 1.0, 0.0);
	Draw_Circle(sun_radius);


	
	glPopMatrix(); //지구의 glPushMatrix()  이전의 좌표 상태를 다시 호출
	glPopMatrix(); //달의 glPushMatrix()  이전의 좌표 상태를 다시 호출


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

