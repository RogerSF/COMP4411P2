// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "modelerglobals.h"
#include "mat.h"
#include "vec.h"

#include <FL/gl.h>
#include <math.h>
#include <GL/glu.h>
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
public:
    SampleModel(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label) { }

    virtual void draw();

    void addCustomLighting();
    // void drawTextureBox(double x, double y, double z);
    // void drawTextureCylinder(double h, double r1, double r2);
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{ 
    return new SampleModel(x,y,w,h,label); 
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
    ModelerView::draw();

    addCustomLighting(); //Whistle No.1

	// draw the floor
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5,0,-5);
	drawBox(10,0.01f,10);
	glPopMatrix();

	// draw the sample model
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));
		// draw base
		glPushMatrix();
		glTranslated(-1.5, 0, -1.5);
		glScaled(3, 0.3, 3);
		drawTextureBox(1, 1, 1);
		// drawBox(1, 1, 1);
		glPopMatrix();

		// draw central column
		glPushMatrix();
		glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
		glRotated(-90, 1.0, 0.0, 0.0);
		drawTextureCylinder(5+VAL(HEIGHT), 0.1, 0.1);

		glTranslated(0.0, 0.0, 5+VAL(HEIGHT));
		// draw hat
		drawCylinder(1, 5, 0.1);
		glTranslated(0,0,2);
		drawSphere(1);
		//draw 8 arms
		glTranslated(0.0, 3.5, -5-sin(VAL(ROTATE)*M_PI/180));
		drawTextureCylinder(3+sin(VAL(ROTATE)*M_PI/180), 0.1, 0.2); //sin(VAL(ROTATE)*M_PI/180);
		// drawSphere(0.5);
			glPushMatrix();
			glRotated(VAL(SEAT_ROTATE), 0, 0, 1);
			glTranslated(-0.5, -0.5, -0.2);
			drawBox(1, 1, 0.2);
			drawBox(0.2, 1, 1);
			drawBox(1, 0.1, 0.4);
			glTranslated(0, 1, 0);
			drawBox(1, 0.1, 0.4);
			glPopMatrix();


		glTranslated(3.5, -3.5, sin(VAL(ROTATE)*M_PI/180) - sin((VAL(ROTATE)+90)*M_PI/180));
		drawTextureCylinder(3+sin((VAL(ROTATE)+90)*M_PI/180), 0.1, 0.2);
		// drawSphere(0.5);
			glPushMatrix();
			glRotated(VAL(SEAT_ROTATE), 0, 0, 1);
			glTranslated(-0.5, -0.5, -0.2);
			drawBox(1, 1, 0.2);
			drawBox(0.1, 1, 0.4);
			glTranslated(0, 1, 0);
			drawBox(0.9, 0.1, 1);
			glTranslated(1, 0, 0);
			drawBox(0.1, -1, 0.4);
			glPopMatrix();

		glTranslated(-7, 0, sin((VAL(ROTATE)+90)*M_PI/180) - sin((VAL(ROTATE)-90)*M_PI/180));
		drawTextureCylinder(3+sin((VAL(ROTATE)-90)*M_PI/180), 0.1, 0.2);
		// drawSphere(0.5);
			glPushMatrix();
			glRotated(VAL(SEAT_ROTATE), 0, 0, 1);
			glTranslated(-0.5, -0.5, -0.2);
			drawBox(1, 1, 0.2);
			drawBox(1, 0.2, 1);
			drawBox(0.1, 1, 0.4);
			glTranslated(1, 0, 0);
			drawBox(0.1, 1, 0.4);
			glPopMatrix();

		glTranslated(3.5, -3.5, sin((VAL(ROTATE)-90)*M_PI/180) - sin((VAL(ROTATE)+180)*M_PI/180));
		drawTextureCylinder(3+sin((VAL(ROTATE)+180)*M_PI/180), 0.1, 0.2);
		// drawSphere(0.5);
			glPushMatrix();
			glRotated(VAL(SEAT_ROTATE), 0, 0, 1);
			glTranslated(-0.5, -0.5, -0.2);
			drawBox(1, 1, 0.2);
			drawBox(1, 0.1, 0.4);
			glTranslated(1, 1, 0);
			drawBox(-1, -0.1, 0.4);
			drawBox(-0.2, -1, 1);
			glPopMatrix();

		glTranslated(2.47487, 1.02513, sin((VAL(ROTATE)+180)*M_PI/180) - sin((VAL(ROTATE)+135)*M_PI/180));
		drawTextureCylinder(3+sin((VAL(ROTATE)+135)*M_PI/180), 0.1, 0.2);
		// drawSphere(0.5);
			glPushMatrix();
			glRotated(VAL(SEAT_ROTATE), 0, 0, 1);
			glRotated(135, 0, 0, 1);
			glTranslated(-0.5, -0.5, -0.2);
			drawBox(1, 1, 0.2);
			drawBox(1, 0.2, 1);
			drawBox(0.1, 1, 0.4);
			glTranslated(1, 0, 0);
			drawBox(0.1, 1, 0.4);
			glPopMatrix();

		glTranslated(-4.94974, 0, sin((VAL(ROTATE)+135)*M_PI/180) - sin((VAL(ROTATE)-135)*M_PI/180));
		drawTextureCylinder(3+sin((VAL(ROTATE)-135)*M_PI/180), 0.1, 0.2);
		// drawSphere(0.5);
			glPushMatrix();
			glRotated(VAL(SEAT_ROTATE), 0, 0, 1);
			glRotated(45, 0, 0, 1);
			glTranslated(-0.5, -0.5, -0.2);
			drawBox(1, 1, 0.2);
			drawBox(1, 0.2, 1);
			drawBox(0.1, 1, 0.4);
			glTranslated(1, 0, 0);
			drawBox(0.1, 1, 0.4);
			glPopMatrix();

		glTranslated(0, 4.94974, sin((VAL(ROTATE)-135)*M_PI/180) - sin((VAL(ROTATE)-45)*M_PI/180));
		drawTextureCylinder(3+sin((VAL(ROTATE)-45)*M_PI/180), 0.1, 0.2);
		// drawSphere(0.5);
			glPushMatrix();
			glRotated(VAL(SEAT_ROTATE), 0, 0, 1);
			glRotated(-45, 0, 0, 1);
			glTranslated(-0.5, -0.5, -0.2);
			drawBox(1, 1, 0.2);
			drawBox(1, 0.2, 1);
			drawBox(0.1, 1, 0.4);
			glTranslated(1, 0, 0);
			drawBox(0.1, 1, 0.4);
			glPopMatrix();

		glTranslated(4.94974, 0, sin((VAL(ROTATE)-45)*M_PI/180) - sin((VAL(ROTATE)+45)*M_PI/180));
		drawTextureCylinder(3+sin((VAL(ROTATE)+45)*M_PI/180), 0.1, 0.2);
		// drawSphere(0.5);
			glPushMatrix();
			glRotated(VAL(SEAT_ROTATE), 0, 0, 1);
			glRotated(-135, 0, 0, 1);
			glTranslated(-0.5, -0.5, -0.2);
			drawBox(1, 1, 0.2);
			drawBox(1, 0.2, 1);
			drawBox(0.1, 1, 0.4);
			glTranslated(1, 0, 0);
			drawBox(0.1, 1, 0.4);
			glPopMatrix();

		glPopMatrix();

	glPopMatrix();
}

void SampleModel::addCustomLighting()
{
	//Configuring the customized light
	glEnable(GL_LIGHTING);
	GLfloat* lightPos = new GLfloat[4];
	lightPos[0] = VAL(LIGHT_X);
	lightPos[1] = VAL(LIGHT_Y);
	lightPos[2] = VAL(LIGHT_Z);
	lightPos[3] = 1; //w value of light - not alpha! let lightsource be a point in space
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	//reference cube to show the position of light
	glPushMatrix();
	glTranslated(lightPos[0], lightPos[1], lightPos[2]);
	setDiffuseColor(1.0, 1.0, 0.0);
	drawBox(0.5, 0.5, 0.5);
	glPopMatrix();
}
//int main()
//{
//	// Initialize the controls
//	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
//	// stepsize, defaultvalue)
//    ModelerControl controls[NUMCONTROLS];
//    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
//    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
//    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
//    controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
//	controls[ROTATE] = ModelerControl("Rotate", -180, 180, 1, 0);
//	controls[SEAT_ROTATE] = ModelerControl("Seat Rotate", -180, 180, 1, 0);
//	controls[LIGHT_X] = ModelerControl("Light PosX", 0, 10, 0.1f, 5);
//	controls[LIGHT_Y] = ModelerControl("Light PosY", 0, 10, 0.1f, 5);
//	controls[LIGHT_Z] = ModelerControl("Light PosZ", 0, 10, 0.1f, 5);
//
//    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
//    return ModelerApplication::Instance()->Run();
//}
