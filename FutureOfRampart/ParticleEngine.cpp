#include "ParticleEngine.h"
#include <algorithm>

using namespace std;

// Returns a random float from 0 to < 1
float randomFloat() {
	return (float)rand() / ((float)RAND_MAX + 1);
}

ParticleEngine::ParticleEngine(Vector3 origin, int quantity, GLuint textureId, float dT, float rad) :
                basePosition(origin), 
                amount(quantity), 
                texture(textureId), 
                duration(dT),
                radius(rad)
{}

void ParticleEngine::initialize()
{
  // create all of the particles and start them at the origin
  // with no motion
  for(int i = 0; i < amount; ++i)
  {
    Particle* p = new Particle();
    p->pos = basePosition;
    p->timeAlive = 0;
    p->timespan = duration;
    // assign a random velocity
    // update will scale this to the bounds of our explosion
    p->velocity = Vector3(randomFloat()*amount, randomFloat()*amount, randomFloat()*amount);
    p->color = Vector3(1.0f, 1.0f, 1.0f);
    particles.push_back(p);
  }
}

bool compareParticles(Particle* particle1, Particle* particle2)
{
  return (particle1->pos).z <
		(particle2->pos).z;
}

void ParticleEngine::step()
{
  bool areParticles = false;
  for(int i = 0; i < particles.size(); ++i)
  {
    areParticles = true;
    Particle* p = particles.at(i);
    
    // advance by velocity
    p->pos.x += (p->velocity.x * STEP_TIME);
    p->pos.y += (p->velocity.y * STEP_TIME);
    p->pos.z += (p->velocity.z * STEP_TIME);

    // add effect of gravity to velocity
    p->velocity.y -= GRAVITY * STEP_TIME;

    p->timeAlive += STEP_TIME;
    
    if(p->timeAlive > p->timespan)
      particles.pop_back();

   // delete p;
  }

  if(!areParticles)
    done = true;
}

void ParticleEngine::advance(float dt)
{
  while (dt > 0) {
		if (timeUntilNextStep < dt) {
			dt -= timeUntilNextStep;
			step();
			timeUntilNextStep = STEP_TIME;
		}
		else {
			timeUntilNextStep -= dt;
			dt = 0;
		}
	}
}

void ParticleEngine::draw()
{
			sort(particles.begin(), particles.end(), compareParticles);
			
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			glBegin(GL_QUADS);
			for(unsigned int i = 0; i < particles.size(); i++) 
      {
				Particle* p = particles[i];
				glColor4f(p->color[0], p->color[1], p->color[2],
						  (1 - p->timeAlive / p->timespan));

				float size = PARTICLE_SIZE / 2;
				
				Vector3 pos = p->pos;
				
				glTexCoord2f(0, 0);
				glVertex3f(pos[0] - size, pos[1] - size, pos[2]);
				glTexCoord2f(0, 1);
				glVertex3f(pos[0] - size, pos[1] + size, pos[2]);
				glTexCoord2f(1, 1);
				glVertex3f(pos[0] + size, pos[1] + size, pos[2]);
				glTexCoord2f(1, 0);
				glVertex3f(pos[0] + size, pos[1] - size, pos[2]);
			}
			glEnd();
}






