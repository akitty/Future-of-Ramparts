#pragma once

#define PI 3.14
#include "Matrix4.h"
class IsoCamera
{
	public:
		Matrix4 & cam;
		Matrix4 rotatePosY;
		Matrix4 rotateNegY;
		Matrix4 xPosTran;
		Matrix4 xNegTran;
		Matrix4 zPosTran;
		Matrix4 zNegTran;

		IsoCamera(void);
		IsoCamera(Matrix4 & c) : cam(c)
		{
			rotatePosY.rotatey(90.0f);		// rotates along y axis 90 degrees
			rotateNegY.rotatey(-90.0f);		// rotates along y axis -90 degrees
			xPosTran.translate(1.0,0.0,0.0);	// an x translation of 1
			xNegTran.translate(-1.0,0.0,0.0); // an x translation of -1
			zPosTran.translate(0.0,0.0,1.0);	// a z translation of 1
			zNegTran.translate(0.0,0.0,-1.0);	// a z translation of -1
		}

		/**
		 * rotateView rotates the y position of the camera by 90 degrees.
		 * entered when the 'd' character is pressed.
		 */
		inline void rotateView() 
		{
			cam.multiply(rotatePosY);
		}

		/**
		 * rotateViewCounter rotates the y position of the camera by -90 degrees.
		 * entered when the 'a' character is pressed.
		 */
		inline void rotateViewCounter()
		{
			cam.multiply(rotateNegY);
		}

		/**
		 * translatePosX translates the x position of the camera by 1 unit.
		 * entered when the right arrow character is pressed.
		 */
		inline void translatePosX()
		{
			cam.multiply(xPosTran);
		}

		/**
		 * translateNegX translates the x position of the camera by -1 unit.
		 * entered when the left arrow character is pressed.
		 */
		inline void translateNegX()
		{
			cam.multiply(xNegTran);
		}

		/**
		 * translatePosZ translates the z position of the camera by 1 unit.
		 * entered when the down arrow character is pressed.
		 */
		inline void translatePosZ()
		{
			cam.multiply(zPosTran);
		}

		/**
		 * translateNegZ translates the z position of the camera by -1 unit.
		 * entered when the up arrow character is pressed.
		 */
		inline void translateNegZ()
		{
			cam.multiply(zNegTran);
		}

		inline void handleInput(unsigned char key, int, int) 
		{
      cout << key << endl;
			// x pos
			if(key == 'd') translatePosX();
			// x neg
			else if(key == 'a') translateNegX();
			// z pos
			else if(key == 'w') translatePosZ();
			// z neg
			else if(key == 's') translateNegZ();
			// rotate pos y
			else if(key == 'q') rotateView();
			// rotate neg y
			else if(key == 'e') rotateViewCounter();
			else { cout << "invalid key is pressed\n"; }
		}
};

