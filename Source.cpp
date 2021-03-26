#include<GL/glut.h>
#include<map>
#include <string>
using namespace std;

void drawSth() {
	glColor3ub(255, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
}

void drawAxes() {
	GLfloat axisLength = 5.0f;

	glPushMatrix();

	// red X
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
		
		// x axis
		glVertex3f(-axisLength, 0.0f, 0.0f);
		glVertex3f(axisLength, 0.0f, 0.0f);

		// arrow x
		glVertex3f(axisLength, 0.0f, 0.0f);
		glVertex3f(axisLength - 1.0f, 1.0f, 0.0f);
		glVertex3f(axisLength, 0.0f, 0.0f);
		glVertex3f(axisLength - 1.0f, -1.0f, 0.0f);

	glEnd();
	glFlush();

	// green y
	glColor3ub(0, 255, 0);
	glBegin(GL_LINES);

		// y axis
		glVertex3f(0.0f, -axisLength, 0.0f);
		glVertex3f(0.0f, axisLength, 0.0f);
		
		// arrow y
		glVertex3f(0.0f, axisLength, 0.0f);
		glVertex3f(1.0f, axisLength - 1.0f, 0.0f);
		glVertex3f(0.0f, axisLength, 0.0f);
		glVertex3f(-1.0f, axisLength - 1.0f, 0.0f);

	glEnd();
	glFlush();

	// blue z
	glColor3ub(0, 0, 255);
	glBegin(GL_LINES);

		// z axis
		glVertex3f(0.0f, 0.0f, -axisLength);
		glVertex3f(0.0f, 0.0f, axisLength);

		// arrow z
		glVertex3f(0.0f, 0.0f, axisLength);
		glVertex3f(0.0f, 1.0f, axisLength - 1.0f);
		glVertex3f(0.0f, 0.0f, axisLength);
		glVertex3f(0.0f, -1.0f, axisLength - 1.0f);

	glEnd();
	glFlush();

	glPopMatrix();
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Put functions to draw here
	drawAxes();
	drawSth();

	glutSwapBuffers();
	glLoadIdentity();

	map<string, GLfloat> Eye = {
		{"eyeX", 10.0f}, {"eyeY", 10.0f}, {"eyeZ", 10.0f},
		{"lookAtX", 0.0f}, {"lookAtY", 0.0f}, {"lookAtZ", 0.0f},
		{"upX", 0.0f}, {"upY", 1.0f}, {"upZ", 0.0f}
	};

	gluLookAt(Eye["eyeX"], Eye["eyeY"], Eye["eyeZ"],
		Eye["lookAtX"], Eye["lookAtY"], Eye["lookAtZ"],
		Eye["upX"], Eye["upY"], Eye["upZ"]);

}

void reshapeScene(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, width, height);
	gluPerspective(60, 1.0f, 1.0, 100);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Particle Simulation");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutReshapeFunc(reshapeScene);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}