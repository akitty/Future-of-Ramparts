#pragma once
#include "Geode.h"
#include "Vector3.h"
#include <gl\glut.h>

// constant for PI used to help with functions
const float PI = 3.1415926535f;

// PARTICLE RELATING PHYSICAL CONSTANTS
const float GRAVITY = 3.0f;
const int NUM_PARTICLES = 1000;
//The interval of time, in seconds, by which the particle engine periodically
//steps.
const float STEP_TIME = 0.01f;
//The length of the sides of the quadrilateral drawn for each particle.
const float PARTICLE_SIZE = 0.05f;

/*
 * Container struct for particles themselves
 */
 struct particle
 {
   Vector3 pos, 
           velocity, 
           color;
   float timeAlive, 
         timespan;
 };

// Returns a random float from 0 to < 1
float randomFloat() {
	return (float)rand() / ((float)RAND_MAX + 1);
}

/*
 * A general class to handle particle generation.
 */
class ParticleEngine
{
  public:
    // texture to use with the particles
    GLuint textureId;
    // the starting position of the particles
    Vector3 basePosition;
    // the amount of time to display the particle animation
    float duration;
    // the velocity of this particle
    float velocity;
    // the number of particles to emit
    int quantity;

    /*
     * This ParticleEngine (emitter) takes in its position within the world, 
     * the number of particles to emit, the texture to use, and the duration 
     * for how long we release particles.
     */
    ParticleEngine(Vector3 origin, int quantity, GLuint textureId, float duration);
    ~ParticleEngine();
};
