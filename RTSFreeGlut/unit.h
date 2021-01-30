#pragma once
#include <iostream>
#include <GL/glut.h>
typedef unsigned long long u64;
using namespace std;

struct face {
	double width;
	double height;
	int direction;
};

class unit {
public:
	unit() {
		x = 0;
		y = 0;
		z = 0;
		initFaces();
		initColours();
		initRotation();
		this->rotation[0] = 45;
	}
	unit(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
		initFaces();
		initColours();
		initRotation();
	}
	void draw() {
		glPushMatrix();
		glTranslated(x, y, z);
		glRotated(rotation[0], 1.0, 0.0, 0.0);
		glRotated(rotation[1], 0.0, 1.0, 0.0);
		glRotated(rotation[2], 0.0, 0.0, 1.0);
		glBegin(GL_QUADS);
		
		//Front face
		glColor3d(0.5, 0.5, 0.5);
		glVertex3d(-1, 1, -1);
		glVertex3d(-1, -1, -1);
		glVertex3d(1, -1, -1);
		glVertex3d(1, 1, -1);

		//Backface
		glColor3d(1, 0.5, 0.5);
		glVertex3d(-1, -1, 1);
		glVertex3d(-1, 1, 1);
		glVertex3d(1, 1, 1);
		glVertex3d(1, -1, 1);

		//Right face
		glColor3d(0.5, 1, 0.5);
		glVertex3d(1, 1, -1);
		glVertex3d(1, -1, -1);
		glVertex3d(1, -1, 1);
		glVertex3d(1, 1, 1);

		//Left Face
		glColor3d(0.5, 0.5, 1);
		glVertex3d(-1, 1, -1);
		glVertex3d(-1, 1, 1);
		glVertex3d(-1, -1, 1);
		glVertex3d(-1, -1, -1);

		//Top Face
		glColor3d(1, 1, 0.5);
		glVertex3d(-1, 1, -1);
		glVertex3d(1, 1, -1);
		glVertex3d(1, 1, 1);
		glVertex3d(-1, 1, 1);

		//Bottom Face
		glColor3d(1, 0.5, 1);
		glVertex3d(-1, -1, -1);
		glVertex3d(-1, -1, 1);
		glVertex3d(1, -1, 1);
		glVertex3d(1, -1, -1);

		glEnd();
		glPopMatrix();
	}
	void move(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	//xyz
	//0=x, 1=y, 2=z
	void rotateAdd(double angle, int xyz) {
		if (xyz >= 0 && xyz < 3) {
			rotation[xyz] += angle;
			if (rotation[xyz] > 360)
				rotation[xyz] -= 360;
			else if (rotation[xyz] < 0)
				rotation[xyz] += 360;
		}
		else
			return;
	}

private:
	double x, y, z;
	double rotation[3];
	double colours[3];
	face faces[6];
	void drawFace(int index) {
		face* f = &faces[index];
		double newX, newY, newZ, permX, permY, permZ;
		glColor3d(colours[0], colours[1], colours[2]);
		switch (f->direction) {
		case 0://
			newX = this->x + f->width;
			newY = this->y - f->height;
			glVertex3d(this->x, this->y, this->z);
			glVertex3d(newX, this->y, this->z);
			glVertex3d(newX, newY, this->z);
			glVertex3d(this->x, newY, this->z);
			break;
		case 1://+x+z
			newX = this->x + f->width;
			newZ = this->z - f->height;
			glVertex3d(this->x, this->y, this->z);
			glVertex3d(newX, this->y, this->z);
			glVertex3d(newX, this->y, newZ);
			glVertex3d(this->x, this->y, newZ);
			break;
		case 2://
			newY = this->y - f->height;
			newZ = this->z - f->width;
			glVertex3d(this->x, this->y, this->z);
			glVertex3d(this->x, this->y, newZ);
			glVertex3d(this->x, newY, newZ);
			glVertex3d(this->x, newY, this->z);
			break;
		case 3:
			permY = this->y - f->height;
			newX = this->x + f->width;
			newZ = this->z - f->height;
			glVertex3d(this->x, permY, this->z);
			glVertex3d(newX, permY, this->z);
			glVertex3d(newX, permY, newZ);
			glVertex3d(this->x, permY, newZ);
			break;
		case 4:
			permZ = this->z - f->height;
			newX = this->x + f->width;
			newY = this->y - f->height;
			glVertex3d(this->x, this->y, permZ);
			glVertex3d(newX, this->y, permZ);
			glVertex3d(newX, newY, permZ);
			glVertex3d(this->x, newY, permZ);
			break;
		case 5:
			permX = this->x + f->width;
			newY = this->y - f->height;
			newZ = this->z - f->width;
			glVertex3d(permX, this->y, this->z);
			glVertex3d(permX, newY, this->z);
			glVertex3d(permX, newY, newZ);
			glVertex3d(permX, this->y, newZ);
			break;
		}
	}

	void initRotation() {
		for (int i = 0; i < 3; i++) {
			rotation[i] = 0;
		}
	}
	void initColours() {
		for (int i = 0; i < 3; i++)
			colours[i] = 0.6;
	}
	void initFaces() {
		for (char i = 0; i < 6; i++) {
			faces[i].height = 1.0;
			faces[i].width = 1.0;
			faces[i].direction = i;
		}
	}
};