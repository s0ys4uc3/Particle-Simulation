#pragma once
#include <tuple>
#include <GL/glut.h>
using namespace std;
class Particle
{
private:
	tuple <float, float, float> position; //x, y, z position
	tuple <GLubyte, GLubyte, GLubyte> color; // rgb color code
	float radius;
	int life; // 1 means alive else dead
	int id;
public:
	Particle(tuple <float, float, float> position, 
			tuple <unsigned short, unsigned short, unsigned short> color, 
			float radius, int id) {
		this->position = position;
		this->color = color;
		this->radius = radius;
		this->id = id;

		life = 1;
	}


	tuple <float, float, float> getPosition() { return position; }
	tuple <unsigned short, unsigned short, unsigned short> getColor() { return color; }
	float getRadius() { return radius; }
	int getLife() { return life; }
	int getId() { return id; }
};

