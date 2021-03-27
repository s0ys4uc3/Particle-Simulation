#pragma once
#include <tuple>
#include <GL/glut.h>
#include <time.h>
using namespace std;
class Particle
{
private:
	tuple <float, float, float> position; //x, y, z position
	tuple <float, float, float> velocity; //x, y, z velocity
	tuple <GLubyte, GLubyte, GLubyte> color; // rgb color code
	float radius;
	int id;
public:
	Particle(tuple <float, float, float> position, 
			tuple <unsigned short, unsigned short, unsigned short> color, 
			float radius, int id) {
		this->position = position;
		this->color = color;
		this->radius = radius;
		this->id = id;

		srand(static_cast <unsigned> (time(0)));
		float LO = 0.000f;
		float HI = 0.010f;
		float x_vec = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		float y_vec = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		float z_vec = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		velocity = make_tuple(x_vec, y_vec, z_vec);
	}


	tuple <float, float, float> getPosition() { return position; }
	tuple <unsigned short, unsigned short, unsigned short> getColor() { return color; }
	float getRadius() { return radius; }
	int getId() { return id; }

	void draw()
	{
		glTranslatef(0.0f, 0.0f, 0.0f);
		glPushMatrix();

		glColor3ub(get<0>(color),
			get<1>(color),
			get<2>(color));

		glTranslatef(get<0>(position),
			get<1>(position),
			get<2>(position));

		glutSolidSphere(radius, 16, 32);
		glPopMatrix();
	}

	void move(GLfloat lowerBoundary, GLfloat upperBoundary) {
		// bouncing x
		if (get<0>(position) > upperBoundary || get<0>(position) < lowerBoundary) get<0>(velocity) = -1.0f * get<0>(velocity);
		// bouncing y
		if (get<1>(position) > upperBoundary || get<1>(position) < lowerBoundary) get<1>(velocity) = -1.0f * get<1>(velocity);
		// bouncing z
		if (get<2>(position) > upperBoundary || get<2>(position) < lowerBoundary) get<2>(velocity) = -1.0f * get<2>(velocity);

		// move x
		get<0>(position) = get<0>(position) + get<0>(velocity);

		// move y
		get<1>(position) = get<1>(position) + get<1>(velocity);

		// move z
		get<2>(position) = get<2>(position) + get<2>(velocity);
	}
};

