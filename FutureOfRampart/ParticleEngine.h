#pragma once
#include "Vector3.h"
#include "TextureManager.h"
#include <gl\glut.h>
#include <vector>

using namespace std;

// PARTICLE RELATED PHYSICAL CONSTANTS
const float GRAVITY = 3.0f;
// The number of particles to emit
const int   NUM_PARTICLES = 100;
// The interval of time, in seconds, by which the particle engine periodically
// steps.
const float STEP_TIME = 0.01f;
// The length of the sides of the quadrilateral drawn for each particle.
const float PARTICLE_SIZE = 0.05f;
// The number of milliseconds to which the timer is set
const int   TIMER_MS = 25; 

/*
 * Container struct for particles themselves
 */
 struct Particle
 {
   Vector3    pos, 
              velocity, 
              color;
   float      timeAlive, 
              timespan;
 };

/*
 * A general class to handle particle generation.
 */
class ParticleEngine
{
  public:
    // texture to use with the particles
    GLuint texture;
    // the starting position of the particles
    Vector3 basePosition;
    // the amount of time to display the particle animation
    float duration;
    // the amount of time before calling step() again
    float timeUntilNextStep;
    // the velocity of this particle
    float velocity;
    // the number of particles to emit
    int amount;
    // the maximum distance to travel for any particle
    float radius;
    // the particles this engine is using
    vector<Particle*> particles;
    // whether or not this particle animation has finished
    bool done;

    /*
     * This ParticleEngine (emitter) takes in its position within the world, 
     * the number of particles to emit, the texture to use, and the duration 
     * for how long we release particles.
     */
    ParticleEngine(Vector3 origin, int quantity, GLuint textureId, float duration, float radius);

   /* 
    *  Creates the timer function for calling the update method for each of 
    *  the particles in addition to any other initializations.
    */
    void initialize();

    /* advances emission state by the step time */
    void step();

    /* advances emission state by the number of steps equivalent to this
     * amount of passing time */
    void advance(float dt);

    /* draw all of the particles in their current state */
    void draw();

   /***************************************************************
    Desired Usage Procedure:
    1.) Instantiate a particle engine at the given position. Particle engine
    processes parameters and prepares for execution. 
    
    2.) Call initialize to start the timer to call update and enable draw to start occuring. 
    
    3.) The timer continues until all of the particles have ran through 
    the duration time. 
    
    4.) Everything is cleaned up at the end of this execution.
    ***************************************************************/
};
