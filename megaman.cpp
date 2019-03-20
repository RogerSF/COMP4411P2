// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <math.h>
#include "modelerglobals.h"
#include "modelerui.h"

// Colors
#define MEGAMAN_LIGHT_BLUE 0.455f, 0.7255f, 0.855f
#define MEGAMAN_DARK_BLUE 0.3098f, 0.4902f, 0.8275f
#define MEGAMAN_RED 1.0f, 0.0f, 0.0f
#define MEGAMAN_SKIN 1.0f, 0.8667f, 0.7647f

// To make a MegamanModel, we inherit off of ModelerView
class MegamanModel : public ModelerView 
{
public:
	MegamanModel(int x, int y, int w, int h, char *label)
        : ModelerView(x,y,w,h,label) { }

    virtual void draw();

	void addCustomLighting();
	void animateStep();

private:
	const int animationTotalFrame = 120;
	int animationFrame = 0;
	float rightArmFlex = 0;
	float rightArmSideFlex = 0;
	float rightForearmFlex = 0;
	float leftArmFlex = 0;
	float leftArmSideFlex = 0;
	float leftForearmFlex = 0;
	float energyPathTransformFactor = 0;
	float laserTransformFactor = 0;
	bool showChargingEnergy = false;
	bool showLaser = false;

	float lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}
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

	this->addCustomLighting(); //Whistle No.1
	this->animateStep();

	// draw the sample model
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		// MEGAMAN: BODY
		setDiffuseColor(MEGAMAN_LIGHT_BLUE);
		glPushMatrix();
		glTranslated(-2, -2.5, -1.25);
		drawBox(4, 5, 2.5);

			// MEGAMAN: HEAD
			setDiffuseColor(MEGAMAN_SKIN);
			glPushMatrix();
			glTranslated(2, 5.8, 1.25);
			glRotated(VAL(HEAD_NOD), 1, 0, 0);
			glRotated(VAL(HEAD_SHAKE), 0, 1, 0);
			glRotated(VAL(HEAD_TILT), 0, 0, 1);
			glTranslated(0, 1.5, 0.2);
			drawSphere(2.4);

				// MEGAMAN: HELMET TOP
				setDiffuseColor(MEGAMAN_DARK_BLUE);
				glPushMatrix();
				glTranslated(0, 0.5, -0.2);
				drawSphere(2.5);
				glPopMatrix();

				// MEGAMAN: HELMET LEFT
				glPushMatrix();
				glTranslated(-0.2, 0, -0.28);
				drawSphere(2.5);
				glPopMatrix();

				// MEGAMAN: HELMET LEFT
				glPushMatrix();
				glTranslated(0.2, 0, -0.28);
				drawSphere(2.5);
				glPopMatrix();

				// MEGAMAN: HELMET LEFT EAR
				setDiffuseColor(MEGAMAN_LIGHT_BLUE);
				glPushMatrix();
				glTranslated(2.45, 0, -0.2);
				glRotated(90, 0, 1, 0);
				drawCylinder(0.5, 1, 0.8);
				glPopMatrix();

				// MEGAMAN: HELMET RIGHT EAR
				glPushMatrix();
				glTranslated(-2.45, 0, -0.2);
				glRotated(90, 0, -1, 0);
				drawCylinder(0.5, 1, 0.8);
				glPopMatrix();

				// MEGAMAN: HELMET TOP
				setDiffuseColor(MEGAMAN_LIGHT_BLUE);
				glPushMatrix();
				glTranslated(0, 1.4, -0.2);
				glScaled(0.7, 1.8, 2.15);
				drawSphere(1);
				glPopMatrix();

				// MEGAMAN: HELMET TOP
				glPushMatrix();
				glTranslated(-0.35, 1, 2.15);
				glRotated(21, -1, 0, 0);
				drawBox(0.7, 0.7, 0.2);
				glPopMatrix();

			glPopMatrix();
		
			// MEGAMAN: RIGHT UPPER ARM
			setDiffuseColor(MEGAMAN_LIGHT_BLUE);
			glPushMatrix();
			glTranslated(0, 4, 1.25);
			glRotated(-90, 0, 1, 0);
			glRotated(rightArmFlex, 0, 1, 0);
			glRotated(rightArmSideFlex, 1, 0, 0);
			drawCylinder(3, 1, 1);

				// MEGAMAN: RIGHT FORE ARM
				setDiffuseColor(MEGAMAN_DARK_BLUE);
				glPushMatrix();
				glTranslated(0, 0, 3);
				glRotated(rightForearmFlex, 0, 1, 0);
				drawCylinder(3, 1.2, 1.2);

					// MEGAMAN: RIGHT HAND
					glPushMatrix();
					glTranslated(0, 0, 3);
					drawSphere(1);
					glPopMatrix();

				glPopMatrix();
				
			glPopMatrix();

			// MEGAMAN: LEFT UPPER ARM
			setDiffuseColor(MEGAMAN_LIGHT_BLUE);
			glPushMatrix();
			glTranslated(4, 4, 1.25);
			glRotated(90, 0, 1, 0);
			glRotated(leftArmFlex, 0, -1, 0);
			glRotated(leftArmSideFlex, 1, 0, 0);
			drawCylinder(3, 1, 1);

				// MEGAMAN: LEFT FORE ARM
				setDiffuseColor(MEGAMAN_DARK_BLUE);
				glPushMatrix();
				glTranslated(0, 0, 3);
				glRotated(leftForearmFlex, 0, -1, 0);
				drawCylinder(2.5, 1.2, 1.5);

					// MEGAMAN: LEFT HAND CANNON
					glPushMatrix();
					glTranslated(0, 0, 2.4);
					drawCylinder(1, 1.4, 0.9);
				
						glPushMatrix();
						glTranslated(0, 0, 0.5);
						drawCylinder(1, 0.9, 0.5);

							setDiffuseColor(MEGAMAN_RED);
							glPushMatrix();
							glTranslated(0, 0, 0.5);
							drawCylinder(0.55, 0.4, 0.4);

							// Charging energy
							if (ModelerUserInterface::m_controlsAnimOnMenu->value() && this->showChargingEnergy) {
								
								for (int i = 0; i < 30; i++)
								{
									float r = float(rand() % 20) / float(100);
									float dx = float((rand() % 80) - 40) / float(20);
									float dy = float((rand() % 80) - 40) / float(20);
									float dz = float(rand() % 80) / float(20);
									glPushMatrix();
									glTranslated(dx*energyPathTransformFactor, dy*energyPathTransformFactor, dz*energyPathTransformFactor + 0.5);
									drawSphere(r);
									glPopMatrix();
								}
							} else if (ModelerUserInterface::m_controlsAnimOnMenu->value() && this->showLaser)
							{
								glPushMatrix();
								glTranslated(0, 0, laserTransformFactor*3);
								drawCylinder(2, 0.2 ,0.2);
								glPopMatrix();
							}

							glPopMatrix();

						glPopMatrix();

					glPopMatrix();

				glPopMatrix();

			glPopMatrix();

			// MEGAMAN: PANTS
			setDiffuseColor(MEGAMAN_DARK_BLUE);
			glPushMatrix();
			glTranslated(-0.25, -1, -0.25);
			drawBox(4.5, 2, 3);
			glPopMatrix();

			// MEGAMAN: RIGHT LEG
			setDiffuseColor(MEGAMAN_LIGHT_BLUE);
			glPushMatrix();
			glTranslated(0.8, -0.5, 1.25);
			glRotated(90, 1, 0, 0);
			glRotated(VAL(RIGHT_LEG_FLEX), -1, 0, 0);
			glRotated(VAL(RIGHT_LEG_SIDE_FLEX), 0, -1, 0);
			drawCylinder(2.5, 1, 1);

				// MEGAMAN: RIGHT LOWER LEG
				setDiffuseColor(MEGAMAN_DARK_BLUE);
				glPushMatrix();
				glTranslated(0, 0, 2.5);
				glRotated(VAL(RIGHT_LOWER_LEG_FLEX), 1, 0, 0);
				drawCylinder(3, 1.2, 1.5);

					// MEGAMAN: RIGHT FOOT
					glPushMatrix();
					glTranslated(0, 0.2, 3);
					glScaled(1, 1.2, 1);
					glRotated(VAL(RIGHT_FOOT_FLEX), 1, 0, 0);
					drawCylinder(1.5, 1.2, 1.8);
					glPopMatrix();

				glPopMatrix();

			glPopMatrix();

			// MEGAMAN: LEFT LEG
			setDiffuseColor(MEGAMAN_LIGHT_BLUE);
			glPushMatrix();
			glTranslated(3.2, -0.5, 1.25);
			glRotated(90, 1, 0, 0);
			glRotated(VAL(LEFT_LEG_FLEX), 1, 0, 0);
			glRotated(VAL(LEFT_LEG_SIDE_FLEX), 0, 1, 0);
			drawCylinder(2.5, 1, 1);

				// MEGAMAN: LEFT LOWER LEG
				setDiffuseColor(MEGAMAN_DARK_BLUE);
				glPushMatrix();
				glTranslated(0, 0, 2.5);
				glRotated(VAL(LEFT_LOWER_LEG_FLEX), 1, 0, 0);
				drawCylinder(3, 1.2, 1.5);

					// MEGAMAN: RIGHT FOOT
					glPushMatrix();
					glTranslated(0, 0.2, 3);
					glScaled(1, 1.2, 1);
					glRotated(VAL(LEFT_FOOT_FLEX), 1, 0, 0);
					drawCylinder(1.5, 1.2, 1.8);
					glPopMatrix();

				glPopMatrix();

			glPopMatrix();

		glPopMatrix();

	glPopMatrix();
}

void MegamanModel::animateStep()
{
	if(ModelerUserInterface::m_controlsAnimOnMenu->value())
	{
		if(this->animationFrame >= this->animationTotalFrame)
		{
			this->animationFrame = 0;
		} else
		{
			this->animationFrame += 1;
		}


		if (animationFrame < 30)
		{
			float percentage = float(this->animationFrame) / float(30);
			rightArmFlex = lerp(0, 90, percentage);
			rightArmSideFlex = lerp(80, -10, percentage);
			rightForearmFlex = lerp(0, 80, percentage);
			leftArmFlex = lerp(0, 90, percentage);
			leftArmSideFlex = lerp(80, 0, percentage);
			leftForearmFlex = 0;
		} else if (animationFrame < 55)
		{
			// Laser charge up
			this->showChargingEnergy = true;
			float percentage = float(this->animationFrame - 30) / float(25);
			energyPathTransformFactor = lerp(1, 0, percentage);
		} else if (animationFrame < 60)
		{
			this->showChargingEnergy = false;
			this->showLaser = true;
			float percentage = float(this->animationFrame - 55) / float(5);
			rightArmFlex = lerp(90, 50, percentage);
			rightArmSideFlex = lerp(-10, -30, percentage);
			leftArmSideFlex = lerp(0, -30, percentage);
			laserTransformFactor = lerp(0, 1, percentage);
		} else if (animationFrame < 65)
		{
			this->showLaser = false;
			float percentage = float(this->animationFrame - 60) / float(5);
			rightArmFlex = lerp(50, 20, percentage);
			rightArmSideFlex = lerp(-30, 0, percentage);
			leftArmSideFlex = lerp(-30, -10, percentage);
		} else if (animationFrame < 75)
		{
			// Pause
		} else if (animationFrame < 105)
		{
			float percentage = float(this->animationFrame - 75) / float(30);
			rightArmFlex = lerp(20, 0, percentage);
			rightArmSideFlex = lerp(0, 80, percentage);
			rightForearmFlex = lerp(80, 0, percentage);
			leftArmSideFlex = lerp(-10, 80, percentage);
			leftArmFlex = lerp(90, 0, percentage);
		} else
		{
			// Pause
		}
		
	} else
	{
		rightArmFlex = VAL(RIGHT_ARM_FLEX);
		rightArmSideFlex = VAL(RIGHT_ARM_SIDE_FLEX);
		rightForearmFlex = VAL(RIGHT_FOREARM_FLEX);
		leftArmFlex = VAL(LEFT_ARM_FLEX);
		leftArmSideFlex = VAL(LEFT_ARM_SIDE_FLEX);
		leftForearmFlex = VAL(LEFT_FOREARM_FLEX);
	}
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
	controls[HEAD_NOD] = ModelerControl("Head Nod", -45, 45, 1, 0);
	controls[HEAD_SHAKE] = ModelerControl("Head Shake", -90, 90, 1, 0);
	controls[HEAD_TILT] = ModelerControl("Head Tilt", -45, 45, 1, 0);
	controls[RIGHT_ARM_FLEX] = ModelerControl("Right Arm Flex", -30, 90, 1, 0);
	controls[RIGHT_ARM_SIDE_FLEX] = ModelerControl("Right Arm Side Flex", -30, 90, 1, 80);
	controls[RIGHT_FOREARM_FLEX] = ModelerControl("Right Forearm Flex", 0, 90, 1, 0);
	controls[LEFT_ARM_FLEX] = ModelerControl("Left Arm Flex", -30, 90, 1, 0);
	controls[LEFT_ARM_SIDE_FLEX] = ModelerControl("Left Arm Side Flex", -30, 90, 1, 80);
	controls[LEFT_FOREARM_FLEX] = ModelerControl("Left Fore Arm Flex", 0, 90, 1, 0);
	controls[RIGHT_LEG_FLEX] = ModelerControl("Right Leg Flex", -45, 45, 1, 0);
	controls[RIGHT_LEG_SIDE_FLEX] = ModelerControl("Right Leg Side Flex", -20, 80, 1, 0);
	controls[RIGHT_LOWER_LEG_FLEX] = ModelerControl("Right Lower Leg Flex", 0, 90, 1, 0);
	controls[RIGHT_FOOT_FLEX] = ModelerControl("Right Foot Flex", 0, 90, 1, 0);
	controls[LEFT_LEG_FLEX] = ModelerControl("Left Leg Flex", -45, 45, 1, 0);
	controls[LEFT_LEG_SIDE_FLEX] = ModelerControl("Left Leg Side Flex", -20, 80, 1, 0);
	controls[LEFT_LOWER_LEG_FLEX] = ModelerControl("Left Lower Leg Flex", 0, 90, 1, 0);
	controls[LEFT_FOOT_FLEX] = ModelerControl("Left Foot Flex", 0, 90, 1, 0);

    ModelerApplication::Instance()->Init(&createMegamanModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
