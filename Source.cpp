#include<stdlib.h>
#include<GL/glew.h>
#include<map>
#include<string>
#include<tuple>
#include"Particle.h"
using namespace std;

map<string, GLfloat> Eye = {
	{"posX", 5.0f}, {"posY", 5.0f}, {"posZ", 5.0f},
	{"lookAtX", 0.0f}, {"lookAtY", 0.0f}, {"lookAtZ", 0.0f},
	{"upX", 0.0f}, {"upY", 1.0f}, {"upZ", 0.0f}
};

// Cube's edge length also boundaries of Eye's positions
GLfloat edgeLength = 10.0f;

// Create prototypic sphere
// Its id is always -1
Particle ps = Particle(make_tuple(5.0f, 5.0f, 5.0f),
	make_tuple(224, 17, 95), 0.1f, -1);

GLfloat lowerBoundary = 0.1f;
GLfloat upperBoundary = edgeLength - lowerBoundary;

void limitEyePosition() {
	// Set lower boundary for x, y, z
	if (Eye["posX"] < lowerBoundary) Eye["posX"] = lowerBoundary;
	if (Eye["posY"] < lowerBoundary) Eye["posY"] = lowerBoundary;
	if (Eye["posZ"] < lowerBoundary) Eye["posZ"] = lowerBoundary;

	// Set upper boundary for x, y, z
	if (Eye["posX"] > upperBoundary) Eye["posX"] = upperBoundary;
	if (Eye["posY"] > upperBoundary) Eye["posY"] = upperBoundary;
	if (Eye["posZ"] > upperBoundary) Eye["posZ"] = upperBoundary;
}

GLuint loadBMP_custom(const char* imagepath) {

	printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// Actual RGB data
	unsigned char* data;

	// Open the file
	FILE* file = fopen(imagepath, "rb");
	if (!file) {
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath);
		getchar();
		return 0;
	}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	// Make sure this is a 24bpp file
	if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n");    fclose(file); return 0; }
	if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n");    fclose(file); return 0; }

	// Read the information about the image
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

										 // Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	// Everything is in memory now, the file can be closed.
	fclose(file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// OpenGL has now copied the data. Free our own version
	delete[] data;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Return the ID of the texture we just created
	return textureID;
}

GLuint balltex = loadBMP_custom("imgimg.bmp");

void drawWalls() {
	// Color source https://colorswall.com/palette/24609/

	glBegin(GL_QUADS);

	// Top face -y
	glColor3ub(119, 136, 153);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(edgeLength, 0.0f, 0.0f);
	glVertex3f(edgeLength, 0.0f, edgeLength);
	glVertex3f(0.0f, 0.0f, edgeLength);

	// South face z
	glColor3ub(133, 148, 163);
	glVertex3f(0.0f, 0.0f, edgeLength);
	glVertex3f(0.0f, edgeLength, edgeLength);
	glVertex3f(edgeLength, edgeLength, edgeLength);
	glVertex3f(edgeLength, 0.0f, edgeLength);

	// East face x
	glColor3ub(146, 160, 173);
	glVertex3f(edgeLength, 0.0f, edgeLength);
	glVertex3f(edgeLength, edgeLength, edgeLength);
	glVertex3f(edgeLength, edgeLength, 0.0f);
	glVertex3f(edgeLength, 0.0f, 0.0f);

	// North face -z
	glColor3ub(160, 172, 184);
	glVertex3f(edgeLength, 0.0f, 0.0f);
	glVertex3f(edgeLength, edgeLength, 0.0f);
	glVertex3f(0.0f, edgeLength, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// West face -x
	glColor3ub(173, 184, 194);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, edgeLength);
	glVertex3f(0.0f, edgeLength, edgeLength);
	glVertex3f(0.0f, edgeLength, 0.0f);

	// Top face y
	glColor3ub(187, 196, 204);
	glVertex3f(0.0f, edgeLength, 0.0f);
	glVertex3f(edgeLength, edgeLength, 0.0f);
	glVertex3f(edgeLength, edgeLength, edgeLength);
	glVertex3f(0.0f, edgeLength, edgeLength);

	glEnd();
}


void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Put functions to draw here
	//drawAxes();
	drawWalls();
	ps.draw(balltex);
	ps.move(lowerBoundary, upperBoundary);

	glutSwapBuffers();
	glLoadIdentity();

	limitEyePosition();

	Eye["lookAtX"] = get<0>(ps.getPosition());
	Eye["lookAtY"] = get<1>(ps.getPosition());
	Eye["lookAtZ"] = get<2>(ps.getPosition());

	gluLookAt(Eye["posX"], Eye["posY"], Eye["posZ"],
		Eye["lookAtX"], Eye["lookAtY"], Eye["lookAtZ"],
		Eye["upX"], Eye["upY"], Eye["upZ"]);

}

void reshapeScene(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, width, height);
	gluPerspective(60, 1.0f, 1.0, 100);
	glMatrixMode(GL_MODELVIEW);
}

// This func is a para of glutKeyBoardFunc()
void keyboard(unsigned char key, int x_mouse_pos, int y_mouse_pos) {
	switch (key)
	{
	case 27: // ESC key
		exit(0);
		break;
	default:
		break;
	}
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);

	// Set color mode
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	// Set window width, height
	glutInitWindowSize(640, 640);

	// Set window position
	glutInitWindowPosition(0, 0);

	// Set Set window name
	glutCreateWindow("Particle Simulation");

	// Pass a function to draw
	glutDisplayFunc(renderScene);

	// Keep that function alive
	glutIdleFunc(renderScene);

	// Pass a function to handle the change of window
	glutReshapeFunc(reshapeScene);

	// Pass functions to handle keyboard events
	glutKeyboardFunc(keyboard);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glutMainLoop();
	return 0;
}