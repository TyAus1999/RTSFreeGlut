#pragma once
#include <iostream>
#include <GL/glut.h>
typedef unsigned long long u64;

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
	}
	unit(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
		initFaces();
		initColours();
		initRotation();
	}
	~unit() {

	}
	void draw() {
		glRotated(rotation[0], 1.0, 0.0, 0.0);
		glRotated(rotation[1], 0.0, 1.0, 0.0);
		glRotated(rotation[2], 0.0, 0.0, 1.0);
		for (int i = 0; i < 6; i++)
			this->drawFace(i);
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
			double* r = &rotation[xyz];
			*r += angle;
			double div = *r / 360.0;
			div = floor(div);
			if (div > 0)
				*r -= 360.0 * div;
			else if (div < 0)
				*r += 360 * div;
		}
		else
			return;
	}

private:
	double x, y, z;//this is the top left
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