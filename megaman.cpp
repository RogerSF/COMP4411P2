// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <math.h>
#include "modelerglobals.h"

// Colors
#define MEGAMAN_LIGHT_BLUE 0.455f, 0.7255f, 0.855f
#define MEGAMAN_DARK_BLUE 0.3098f, 0.4902f, 0.8275f

// To make a MegamanModel, we inherit off of ModelerView
class MegamanModel : public ModelerView 
{
public:
	MegamanModel(int x, int y, int w, int h, char *label)
        : ModelerView(x,y,w,h,label) { }

    virtual void draw();

	void addCustomLighting();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createMegamanModel(int x, int y, int w, int h, char *label)
{
    return new MegamanModel(x,y,w,h,label); 
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out MegamanModel
void MegamanModel::draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set the background to white

    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
    ModelerView::draw();

	addCustomLighting(); //Whistle No.1

	// draw the sample model
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		// MEGAMAN: BODY
		setDiffuseColor(MEGAMAN_LIGHT_BLUE);
		glPushMatrix();
		glTranslated(-2, -2.5, -1.25);
		drawBox(4, 5, 2.5);
		glPopMatrix();
		
			// MEGAMAN: RIGHT UPPER ARM
			setDiffuseColor(MEGAMAN_LIGHT_BLUE);
			glPushMatrix();
			glTranslated(-2, 1.5, 0);
			glRotated(VAL(RIGHT_ARM_UP), 0, 0, 1);
			glRotated(-90, 0, 1, 0);
			glRotated(VAL(RIGHT_ARM_FLEX), 0, 1, 0);
			drawCylinder(3, 1, 1);

				setDiffuseColor(MEGAMAN_DARK_BLUE);
				glPushMatrix();
				glTranslated(0, 0, 3);
				glRotated(VAL(RIGHT_FOREARM_FLEX), 0, 1, 0);
				drawCylinder(3, 1.2, 1.2);

					glPushMatrix();
					glTranslated(0, 0, 3);
					drawSphere(1);
					
				glPopMatrix();
				
			glPopMatrix();


		// draw central column
		glPushMatrix();
		glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
		glRotated(-90, 1.0, 0.0, 0.0);
		drawCylinder(5+VAL(HEIGHT), 0.1, 0.1);

		glTranslated(0.0, 0.0, 5+VAL(HEIGHT));
		// draw hat
		drawCylinder(1, 5, 0.1);
		glTranslated(0,0,2);
		drawSphere(1);
		//draw 8 arms
		glTranslated(0.0, 3.5, -5-sin(VAL(ROTATE)*M_PI/180));
		drawCylinder(3+sin(VAL(ROTATE)*M_PI/180), 0.1, 0.2); //sin(VAL(ROTATE)*M_PI/180);
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
		drawCylinder(3+sin((VAL(ROTATE)+90)*M_PI/180), 0.1, 0.2);
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
		drawCylinder(3+sin((VAL(ROTATE)-90)*M_PI/180), 0.1, 0.2);
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
		drawCylinder(3+sin((VAL(ROTATE)+180)*M_PI/180), 0.1, 0.2);
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
		drawCylinder(3+sin((VAL(ROTATE)+135)*M_PI/180), 0.1, 0.2);
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
		drawCylinder(3+sin((VAL(ROTATE)-135)*M_PI/180), 0.1, 0.2);
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
		drawCylinder(3+sin((VAL(ROTATE)-45)*M_PI/180), 0.1, 0.2);
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
		drawCylinder(3+sin((VAL(ROTATE)+45)*M_PI/180), 0.1, 0.2);
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

void MegamanModel::addCustomLighting()
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

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
    controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -180, 180, 1, 0);
	controls[SEAT_ROTATE] = ModelerControl("Seat Rotate", -180, 180, 1, 0);
	controls[LIGHT_X] = ModelerControl("Light PosX", 0, 10, 0.1f, 5);
	controls[LIGHT_Y] = ModelerControl("Light PosY", 0, 10, 0.1f, 5);
	controls[LIGHT_Z] = ModelerControl("Light PosZ", 0, 10, 0.1f, 0);
	controls[RIGHT_ARM_FLEX] = ModelerControl("Right Arm Flex", 0, 90, 1, 0);
	controls[RIGHT_ARM_UP] = ModelerControl("Right Arm Up", 0, 90, 1, 0);
	controls[RIGHT_FOREARM_FLEX] = ModelerControl("Right Form Arm Flex", 0, 90, 1, 0);

    ModelerApplication::Instance()->Init(&createMegamanModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
