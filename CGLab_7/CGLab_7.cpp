#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <gl\glut.h>
// по сетке растра меняется шаг
	// по dx/dy шаг уменьшается

void init();
void draw();


void main(int argc, char** argv)
{
	glutInit(&argc, argv); // инициализируем GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // устанавливаем для окна режим отображения
	glutInitWindowSize(600, 600); // устанавливаем размеры окна
	glutInitWindowPosition(50, 50); // устанавливаем положение окна
	glutCreateWindow("LabWork7"); // создаём окно
	init(); // запускаем функцию инициализации
	glutDisplayFunc(draw); // устанавливаем функцию рисования
	glutMainLoop(); // запускаем главный цикл GLUT

}

void init()
{
	glClearColor(0.07, 0.2, 0.34, 1.0); // задаём значение очистки цветом буфера цвета(цвет фона)
	glMatrixMode(GL_PROJECTION); // задаём текущей матрицу проекции
	glLoadIdentity(); // устанавливаем единичную матрицу
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0); // ортогональная проекция - плоскость Oxy
}

void draw()
{
	GLfloat A = 100, B = 50, X1 = 0, Y1 = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 600, 600);
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINES); //рисуем оси
	glVertex2f(-100.0, 0.0); glVertex2f(100.0, 0.0);
	glVertex2f(0.0, 100.0); glVertex2f(0.0, -100.0);
	glEnd();

	////Отрезок прямой в заданной четверти в указанном направлении методом оценочной функции.Фукция Ay – Bx=0 преобразуется в соответствии с условиями.
	////если F(x, y) < 0, то y : = y + 1, делается шаг + 1 по y;
	////если F(x, y) > 0, то x : = x + 1, делается шаг + 1 по x;
	////если F(x, y) = 0, то x : = x + 1 при A>B;
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	while (X1 < A) {
		glVertex2f(X1, Y1);
		if ((A * Y1 - B * X1) < 0) {
			Y1 = Y1 + 0.01;
			glVertex2f(X1, Y1);
		}
		else if ((A * Y1 - B * X1) > 0) {
			X1 = X1 + 0.01;
			glVertex2f(X1, Y1);
		}
		else {
			X1 = X1 + 0.01;
			glVertex2f(X1, Y1);
		}
	}
	glEnd();

	//методом цифровых дифференциальных анализаторов .	
	GLfloat dX, dY, X2, Y2, C = -100, D = 100;
	X2 = 0, Y2 = 0,
		glColor3f(0.5, 0.0, 0.5);
	glBegin(GL_LINE_STRIP);
	dX = C - X2;
	dY = D - Y2;
	glVertex2f(X2, Y2);
	while (Y2 < D) {
		Y2 = Y2 + 1;
		X2 = X2 + dY / dX;
		glVertex2f(X2, Y2);
	}
	glEnd();
	glFlush();

}
