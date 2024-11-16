#include <Windows.h>
#include <mmsystem.h>
#include <GL/freeglut.h>
#include <math.h>


static double time = 0;
static double time2 = 0;
static double time3 = 0;
static double time4 = 0;
static double time5 = 0;
static double time6 = 0;

GLfloat R_Arm_x = 0;
GLfloat R_Arm_y = 0;
GLfloat L_Arm_x = 0;
GLfloat L_Arm_y = 0;
GLfloat R_Leg_x = 0;
GLfloat R_Leg_y = 0;
GLfloat L_Leg_x = 0;
GLfloat L_Leg_y = 0;
GLfloat Body_x = 0;
GLfloat R = 0;
GLfloat R2 = 0;
GLfloat Ball_ro_x = 0;
GLfloat Ball_ro_y = 0;
GLfloat Ball_lo_x = 0;
GLfloat Ball_lo_y = 0;
GLfloat Goal_ro = 0;
GLfloat Goal_lo = 0;

GLUquadricObj* cyl;

int a = 0;
int b = 0;
int c = 0;
float action_time = 0.0;
float savetime = 0.0;
int first1 = 0;
int first2 = 0;
int first3 = 0;

static int flag = 0;
static int key = 0;

#define RUN 1
#define JAP 2
#define ROCKET 3
#define YUNA 4
#define EXIT 6
#define GROUND 10
#define SHOOT 11
#define WHITE 12

void glInit(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position[] = { 400.0, 300.0, -700.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 0.1, 1000.0);

}

void SetCameraPosition() {
	glLoadIdentity();
	// 카메라 설정: gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	gluLookAt(-14.0, 5.0, -3.0,   // eye: 카메라 위치 (X, Y, Z)
		0.0, 0.0, 0.0,   // center: 바라보는 위치 (X, Y, Z)
		0.0, 1.0, 0.0);  // up: 카메라의 위쪽 방향 벡터 (X, Y, Z)
}

void Draw_Color(int i)
{
	if (i == RUN) {
		glColor3f(0.0, 1.0, 0.0);
	}
	else if (i == JAP) {
		glColor3f(1.0, 1.0, 0.0);
	}
	else if (i == ROCKET) {
		glColor3f(0.0, 1.0, 1.0);
	}
	else if (i == YUNA) {
		glColor3f(1.0, 0.0, 1.0);
	}
	else if (i == EXIT) {
		glColor3f(0.2, 0.2, 0.2);
	}
	else if (i == SHOOT)
	{
		glColor3f(0.0, 1.0, 0.0);
	}
	else if (i == GROUND)
	{
		glColor3f(0.3, 0.8, 0.3);
	}
	else if (i == WHITE)
	{
		glColor3f(0.9, 0.9, 0.9);
	}
}

void Change_Wire_Or_Solid(int i) {
	if (flag == 1)
		gluQuadricDrawStyle(cyl, GLU_LINE);
}

void DrawL_Arm(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glRotatef(x, a, b, c);
	glRotatef(90.0, 1.0, 0.0, 0.0);

	glTranslatef(0.25, 0.0, 0.0);
	glRotatef(15.0, 0.0, 1.0, 0.0);
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
}

void DrawL_Hand(int y, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.22);
	glRotatef(y, a, b, c);
	Change_Wire_Or_Solid(flag);
	if (key == YUNA)
	{
		gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);
	}

	else
	{
		gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);

	}
	glPopMatrix();
}

void DrawL_HandRocket()
{
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, R);
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);

	glPopMatrix();
}

void DrawR_Arm(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glRotatef(x, a, b, c);
	glRotatef(90.0, 1.0, 0.0, 0.0);

	glTranslatef(-0.25, 0.0, 0.0);
	glRotatef(-15.0, 0.0, 1.0, 0.0);
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
}

void DrawR_Hand(int y, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.22);
	glRotatef(y, a, b, c);
	Change_Wire_Or_Solid(flag);
	if (key == YUNA)
	{
		gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
	}

	else
	{
		gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);

	}
	glPopMatrix();
}

void DrawR_HandRocket()
{
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, R2);
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);

	glPopMatrix();
}

void DrawBody(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(x, a, b, c);
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1);
	glPopMatrix();
}



void DrawL_Legs(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.1, 0.0, 0.42);
	glRotatef(x, a, b, c);

	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);
}

void DrawL_foot(int y, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.18);
	glRotatef(y, a, b, c);
	Change_Wire_Or_Solid(flag);
	if (key == YUNA)
	{
		gluCylinder(cyl, 0.05, 0.03, 0.2, 50, 1);
	}

	else
	{
		gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);

	}
	glPopMatrix();
}


void DrawR_Legs(int x, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(-0.1, 0.0, 0.42);
	glRotatef(x, a, b, c);

	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);
}

void DrawR_foot(int y, int a, int b, int c)
{
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.18);
	glRotatef(y, a, b, c);
	Change_Wire_Or_Solid(flag);
	if (key == YUNA)
	{
		gluCylinder(cyl, 0.05, 0.03, 0.2, 15, 1);
	}

	else
	{
		gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);

	}
	glPopMatrix();
}

void DrawNeck()
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	cyl = gluNewQuadric();

	glRotatef(90.0, 1.0, 0.0, 0.0);

	glTranslatef(0.0, 0.0, -0.045);
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.025, 100, 1);
	glPopMatrix();
}

void DrawGoal()
{
	Draw_Color(WHITE);
	Change_Wire_Or_Solid(flag);
	glPushMatrix();
	glTranslatef(0, 1.3, 0); // 박스 중심을 기준으로 이동
	glScalef(3.8,0.1, 0.1); // 크기 조정
	glutSolidCube(1.0f); // 정육면체를 사용하여 박스 그리기
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.9, 0, 0); // 박스 중심을 기준으로 이동
	glScalef(0.1, 2.7, 0.1); // 크기 조정
	glutSolidCube(1.0f); // 정육면체를 사용하여 박스 그리기
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.9, 0, 0); // 박스 중심을 기준으로 이동
	glScalef(0.1, 2.7, 0.1); // 크기 조정
	glutSolidCube(1.0f); // 정육면체를 사용하여 박스 그리기
	glPopMatrix();
	
}

void DrawFootball()
{
	Draw_Color(YUNA);
	
	Change_Wire_Or_Solid(flag);
	gluSphere(cyl, 0.1, 100, 120);
}
void DrawGround()
{
	Draw_Color(GROUND);
	glTranslatef(0.0, -10.23, 0.0);
	glRotatef(45.0, 0, 1, 0);
	glRotatef(0.0 + time4 - 30, 0.0, 0.0, 1);




	Change_Wire_Or_Solid(flag);
	gluSphere(cyl, 10.0, 100, 120);
}

void DrawHead()
{
	glTranslatef(0.0, 0.02, 0.0);
	glPushMatrix();
	cyl = gluNewQuadric();
	Change_Wire_Or_Solid(flag);
	Draw_Color(key);
	gluSphere(cyl, 0.20, 30, 10);


	///왼쪽 뿔
	glRotatef(90.0, 1.0, 0.0, 0.0);

	glTranslatef(-0.16, 0.0, -0.22);
	glRotatef(35.0, 0.0, 1.0, 0.0);
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);
	glPopMatrix();


	glPushMatrix();


	///오른쪽 뿔
	glRotatef(90.0, 1.0, 0.0, 0.0);

	glTranslatef(0.16, 0.0, -0.22);
	glRotatef(-35.0, 0.0, 1.0, 0.0);
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);
	glPopMatrix();



	glPushMatrix();


	//왼쪽 눈
	glTranslatef(-0.1, 0.1, 0.13);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();



	glPushMatrix();

	//오른쪽 눈
	glTranslatef(0.1, 0.1, 0.13);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();
	glPushMatrix();

}


void DrawAndroid()
{
	DrawBody(0, 0, 0, 0);
	DrawNeck();
	DrawHead();
	DrawR_Arm(R_Arm_x, 1, 0, 0);
	if (key == ROCKET)
	{
		DrawR_HandRocket();
	}
	else
	{
		DrawR_Hand(R_Arm_y, 1, 0, 0);

	}
	DrawL_Arm(L_Arm_x, 1, 0, 0);
	if (key == ROCKET)
	{
		DrawL_HandRocket();
	}
	else
	{
		DrawL_Hand(L_Arm_y, 1, 0, 0);
	}
	DrawL_Legs(L_Leg_x, 1, 0, 0);
	DrawL_foot(L_Leg_y, 1, 0, 0);
	DrawR_Legs(R_Leg_x, 1, 0, 0);
	DrawR_foot(R_Leg_y, 1, 0, 0);
}

void Shoot()
{
	
	
	if (first1 == 0)        /////초기화
	{
		time = 0;
		first1 = 1;
		Ball_ro_x = 0;
		Ball_lo_y = 0;
		savetime = time;
	}
	

	sndPlaySound(TEXT("./runsample.wav"), SND_ASYNC | SND_NOSTOP);

	if (time < savetime + 5.98)
	{
		if (Ball_ro_x <= 90)
		{
			Ball_ro_x += 1.5;
		}
	}
	if (time >= savetime + 5.98 && Ball_ro_x >= 0)
	{
		if (Ball_ro_x <= 90 && Ball_ro_x >= 0)
		{
			Ball_ro_x -= 2.0;
			Ball_lo_y -= cos(Ball_ro_x *2 / 180 * 3.141592)/10;
		}
		if (Ball_ro_x < 0)
		{
	
			Ball_lo_y = 0;
		}
		
	}
	if (time <= 14)
	{
		if (Goal_ro <= 180)
		{
			Goal_ro += 1.2;
		}
	}


	if (time < savetime + 5)
	{

		if ( L_Arm_x > -39.0) {                   ////처음 손동작
		
			L_Arm_x -= 2.0;
		
		}
		else if (L_Arm_x < -41.0)
		{
			L_Arm_x += 2.0;
			
		}

		if (R_Arm_x > 39.0) {                   ////처음 손동작

			R_Arm_x -= 2.0;
		}
		else if (R_Arm_x < 37.0)
		{
			R_Arm_x += 2.0;
		}

		if (R_Arm_y > 3.0) {                   ////처음 손동작

			R_Arm_y -= 2.0;
		}
		else if (R_Arm_y < 1.0)
		{
			R_Arm_y += 2.0;
		}
		if (L_Arm_y > -43.0) {                   ////처음 손동작

			L_Arm_y -= 2.0;
		}
		else if (L_Arm_y < -46.0)
		{
			L_Arm_y += 2.0;
		}


		if (Body_x > -10.0) {                   ////처음 손동작

			Body_x -= 1.0;

		}

		if (L_Leg_x > -30.0) 
		{                   ////처음 발동작
			L_Leg_x -= 3.0;
		}
		else if(L_Leg_x < -35.0)
		{
			L_Leg_x += 3.0;
		}


		if (L_Leg_y > 54.5)
		{                   ////처음 발동작
			L_Leg_y -= 3.0;
		}
		else if (L_Leg_y < 50.5)
		{                   ////처음 발동작
			L_Leg_y += 3.0;
		}

		if (R_Leg_y > -1.5)
		{                   ////처음 발동작
			R_Leg_y -= 2.0;
		}
		else if (R_Leg_y < -3.5)
		{                   ////처음 발동작
			R_Leg_y += 2.0;
		}

		if (R_Leg_x > 87.0)
		{                   ////처음 발동작
			R_Leg_x -= 6.0;
		}
		else if (R_Leg_x < 80.0)
		{                   ////처음 발동작
			R_Leg_x += 6.0;
		}
	}

	else if (time > savetime + 5 && time < savetime + 10)
	{
		

		if (L_Arm_x > 40.0) {                   ////2 손동작

			L_Arm_x -= 10.0;

		}
		else if (L_Arm_x < 30.0)
		{
			L_Arm_x += 10.0;

		}

		if (R_Arm_x > -30.0) {                   ////2 손동작

			R_Arm_x -= 10.0;
		}
		else if (R_Arm_x < -45.0)
		{
			//R_Arm_x += 10.0;
		}

		if (R_Arm_y > 3.0) {                   ////2 손동작

			R_Arm_y -= 2.0;
		}
		else if (R_Arm_y < 1.0)
		{
			R_Arm_y += 2.0;
		}
		if (L_Arm_y > -43.0) {                   ////2 손동작

			L_Arm_y -= 2.0;
		}
		else if (L_Arm_y < -46.0)
		{
			L_Arm_y += 2.0;
		}


		if (Body_x > -10.0) {                   ////

			Body_x -= 1.0;

		}

		if (L_Leg_x > 3.0)
		{                   ////2 발동작
			L_Leg_x -= 3.0;
		}
		else if (L_Leg_x < 0.0)
		{
			L_Leg_x += 3.0;
		}


		if (L_Leg_y > 54.5)
		{                   ////2 발동작
			L_Leg_y -= 3.0;
		}
		else if (L_Leg_y < 50.5)
		{                   ////2 발동작
			L_Leg_y += 3.0;
		}

		if (R_Leg_y > -1.5)
		{                   ////2 발동작
			R_Leg_y -= 2.0;
		}
		else if (R_Leg_y < -3.5)
		{                   ////2 발동작
			R_Leg_y += 2.0;
		}

		if (R_Leg_x > -60.0)
		{                   ////2 발동작
			R_Leg_x -= 20.0;
		}
		else if (R_Leg_x < -80.0)
		{                   ////2 발동작
			R_Leg_x += 20.0;
		}
	}
	else if (time > savetime + 10 && time < savetime + 12)
	{
		if (Body_x < 0.0) {                   ////처음 손동작

			Body_x += 1.0;

		}
		if (L_Arm_x > -37.0) {                   ////처음 손동작

			L_Arm_x -= 4.0;

		}
		else if (L_Arm_x < -41.0)
		{
			L_Arm_x += 4.0;

		}

		if (R_Arm_x > 39.0) {                   ////처음 손동작

			R_Arm_x -= 4.0;
		}
		else if (R_Arm_x < 35.0)
		{
			R_Arm_x += 4.0;
		}

		if (R_Arm_y > 5.0) {                   ////처음 손동작

			R_Arm_y -= 4.0;
		}
		else if (R_Arm_y < 1.0)
		{
			R_Arm_y += 4.0;
		}
		if (L_Arm_y > -43.0) {                   ////처음 손동작

			L_Arm_y -= 4.0;
		}
		else if (L_Arm_y < -48.0)
		{
			L_Arm_y += 4.0;
		}
	}
	else if (time >= savetime + 12 && time < savetime + 14)
	{
		if (L_Arm_x > 40.0) {                   ////2 손동작

			L_Arm_x -= 10.0;

		}
		else if (L_Arm_x < 30.0)
		{
			L_Arm_x += 10.0;

		}

		if (R_Arm_x > -30.0) {                   ////2 손동작

			R_Arm_x -= 10.0;
		}
		else if (R_Arm_x < -45.0)
		{
			//R_Arm_x += 10.0;
		}

		if (R_Arm_y > 3.0) {                   ////2 손동작

			R_Arm_y -= 2.0;
		}
		else if (R_Arm_y < 1.0)
		{
			R_Arm_y += 2.0;
		}
		if (L_Arm_y > -43.0) {                   ////2 손동작

			L_Arm_y -= 2.0;
		}
		else if (L_Arm_y < -46.0)
		{
			L_Arm_y += 2.0;
		}


		if (L_Leg_x > -30.0)
		{                   ////처음 발동작
			L_Leg_x -= 3.0;
		}
		else if (L_Leg_x < -35.0)
		{
			L_Leg_x += 3.0;
		}


		if (L_Leg_y > 54.5)
		{                   ////처음 발동작
			L_Leg_y -= 3.0;
		}
		else if (L_Leg_y < 50.5)
		{                   ////처음 발동작
			L_Leg_y += 3.0;
		}

		if (R_Leg_y > -1.5)
		{                   ////처음 발동작
			R_Leg_y -= 2.0;
		}
		else if (R_Leg_y < -3.5)
		{                   ////처음 발동작
			R_Leg_y += 2.0;
		}

		if (R_Leg_x > 87.0)
		{                   ////처음 발동작
			R_Leg_x -= 6.0;
		}
		else if (R_Leg_x < 80.0)
		{                   ////처음 발동작
			R_Leg_x += 6.0;
		}

	}
	else if (time >14)
	{
		time = 0;
		Goal_ro = 0;
	}
	
	

	cyl = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();             // 현재 모델뷰 행렬 저장
	DrawGround();
	glPopMatrix();              // 저장된 모델뷰 행렬 복원

	// Football 그리기
	

	glPushMatrix();             // 새로운 모델뷰 행렬을 시작
	
	glRotatef(45.0, 0, 1, 0);
	glTranslatef(0.0, -10.23, 0.0);
	glRotatef(Ball_ro_x, 0.0, 0.0, 1);
	glTranslatef(10.08 + Ball_lo_y, -0.1, 0.0);
	
	DrawFootball();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45.0, 0, 1, 0);
	glTranslatef(0.0, -10.23, 0.0);
	glRotatef(Goal_ro, 0.0, 0.0, 1);
	glTranslatef(10.08 , 0.0, 0.0);
	glRotatef(90.0, 0, 1, 0);
	glRotatef(90.0, 1, 0, 0);
	DrawGoal();
	glPopMatrix();

	SetCameraPosition();
	
	// 축구공을 차는 동작
	
	
	glRotatef(-230.0, 0, 1, 0);
	//glRotatef(fabs(sin(time) * 16), 1, 0, 0);
	

	//float i = 0;
	//i = fabs(sin(time) * 0.08);
	glPushMatrix();
	glRotatef(Body_x, 0, 0, 1);    ////////몸 전체 틀기
	//glTranslatef(0.0, i, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawAndroid();
	glutSwapBuffers();
}


void Run()
{
	sndPlaySound(TEXT("./runsample.wav"), SND_ASYNC | SND_NOSTOP);
	
	L_Arm_x = sin(time) * 80;
	R_Arm_x = -L_Arm_x;
	R_Arm_y = -fabs(sin(time) * 60 + 50);
	L_Arm_y = -fabs(-sin(time) * 60 + 50);

	R_Leg_y = fabs(-sin(time) * 30 - 30);
	L_Leg_y = fabs(sin(time) * 30 - 30);
	R_Leg_x = sin(time) * 60;
	L_Leg_x = -R_Leg_x;
	
	cyl = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DrawGround();
	glLoadIdentity();
	SetCameraPosition();

	glRotatef(-230.0, 0, 1, 0);
	glRotatef(fabs(sin(time) * 16), 1, 0, 0);
	glRotatef(sin(time) * 16, 0, 1, 0);

	float i = 0;
	i = fabs(sin(time) * 0.08);
	glPushMatrix();
	glTranslatef(0.0, i, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawAndroid();
	glutSwapBuffers();

}

void Jap()
{
	sndPlaySound(TEXT("./japsample.wav"), SND_ASYNC | SND_NOSTOP);
	
	L_Arm_x = (-40) + sin(time2) * 60;
	R_Arm_x = (-80) - L_Arm_x;
	R_Arm_y = -fabs(cos(time2) * 80);

	L_Arm_y = -fabs(-cos(time2) * 80);
	R_Leg_y = fabs(-sin(time) * 30 - 20);
	L_Leg_y = fabs(sin(time) * 30 - 20);
	R_Leg_x = sin(time) * 30;
	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DrawGround();
	glLoadIdentity();
	SetCameraPosition();

	glRotatef(-230.0, 0, 1, 0);
	glRotatef(sin(time) * 10, 0, 0, 1);

	float j = 0;
	j = fabs(sin(time2) * 0.085);
	glPushMatrix();
	glTranslatef(0.0, j, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawAndroid();
	glutSwapBuffers();

}

void ex()
{
	sndPlaySound(TEXT("./exsample.wav"), SND_ASYNC | SND_NOSTOP);
	
	L_Arm_x = (-40) + sin(time) * 60;
	R_Arm_x = (-80) - L_Arm_x;
	R_Arm_y = -fabs(cos(time2) * 10);

	L_Arm_y = -fabs(-cos(time2) * 10);
	R_Leg_y = fabs(-sin(time) * 30 - 30);
	L_Leg_y = fabs(sin(time) * 30 - 30);
	R_Leg_x = sin(time) * 60;
	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();
	SetCameraPosition();
	glRotatef(-180, 0, 1, 0);
	glRotatef(time6, 0, 0, 1);
	glScalef(0.4 / (sin(time3)), 0.4 / (sin(time3)), 0.4 / (sin(time3)));


	glPushMatrix();
	glTranslatef(0.0, 0.5, 0.0);
	DrawAndroid();
	glutSwapBuffers();

}



void MyKeyboard(unsigned char KeyPressed, int x, int y) {
	switch (KeyPressed) {
	case 'w':
		flag = 1;
		break;
	case 's':
		flag = 0;
		break;
	case 'q':
		key = 6;
		break;
	}
}

void InitializeCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 0.1, 1000.0);  // 원근 투영 설정 (시야각, 화면 비율, near plane, far plane)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void MyDisplay()
{
	
	SetCameraPosition();

	if (key == RUN) {
		Run();
		glPopMatrix();
	}
	else if (key == JAP) {
		Jap();
		glPopMatrix();
	}
	else if (key == 5) {
		sndPlaySound(NULL, SND_ASYNC);
	}
	else if (key == SHOOT) {
		Shoot();
		glPopMatrix();
	}
	else if (key == EXIT) {
		ex();
		glPopMatrix();
	}



}

void MyTimer(int Value)
{
	time = time + 0.1;
	time2 = time2 + 0.5;
	time3 = time3 + 0.01;
	time5 = time5 + 0.01;
	time4 = time4 + 1.0;
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}


void MyMainMenu(int entryID)
{
	key = entryID;
}




int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Dance Dance");
	glInit();

	

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Run", 1);
	glutAddMenuEntry("Jap", 2);
	glutAddMenuEntry("Shoot", 11);
	glutAddMenuEntry("중지", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutKeyboardFunc(MyKeyboard);
	glutTimerFunc(40, MyTimer, 1);
	
	
	glutDisplayFunc(MyDisplay);
	InitializeCamera();

	glutMainLoop();
	return 0;
}