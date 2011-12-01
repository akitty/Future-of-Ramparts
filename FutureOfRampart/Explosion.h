#pragma once
#include "Vector3.h"
#include "TextureManager.h"
#include "TextureNumbers.h"
#include "Geode.h"
#include <gl\glut.h>
#include <vector>

using namespace std;

// The number of particles to emit
const int   NUM_PARTICLES = 100;
// The length of the sides of the quadrilateral drawn for each particle.
const float PARTICLE_SIZE = 8.0f;
// texture id for the smoke we'll use in this explosion
const GLuint texture = MAP_TOP_P1;
// assuming a 1 second long animation
const int NUM_FRAMES = 40;
// lasting one second
const int DURATION = 150;
// how long each step is
const float STEP_TIME = 0.01f;

/*
 * Container struct for the explosion smoke particles.
 * They need to know their position, their velocity, and their
 * time that they have been alive. 
 */
 struct SmokeParticle
 {
   Vector3    pos, 
              velocity;
   float      timeAlive;
 };

/*
 * A general class to handle particle generation.
 */
class Explosion : public Geode
{
  public:
    // Particle texture
    GLuint texture;
    // Origin in space of the particles
    Vector3 origin;
    // Amount of time to display each particle
    float frameTime;
    // the number of smoke particles in this explosion
    vector<SmokeParticle*> particles;
    // overall time alive
    float timeAlive;
    // boolean indicating that the animation is done and it
    // can now be removed from the scene graph
    bool done;

    int frame;
    /*
     * This ParticleEngine (emitter) takes in its position in the world,
     * then initializes everything so it can start animating on the 
     * next frame until it is done. Uses glutTimerFunc
     */
    Explosion(Vector3 origin);

    /* for use of drawing our shockwave */
    void drawShockwave( float Radius, int numPoints );

    /* advances emission state by the step time */
    void step();

    /* advances emission state by the number of steps equivalent to this
     * amount of passing time */
    void advance(float dt);

    /* draw all of the particles in their current state */
    void render();

    /* ends the explosion animation */
    void end();
};
