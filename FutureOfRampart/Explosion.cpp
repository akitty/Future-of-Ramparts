#include "Explosion.h"
#include <algorithm>

const float PI = 3.1415926535f;
// The number of milliseconds to which the timer is set
const int   FPS = 2; 
const float GRAVITY = 0.0002;

float randomFloat() {
	return (float)rand() / ((float)RAND_MAX + 1);
}

Explosion::Explosion(Vector3 o) :
                origin(o)
{
  for(int i = 0; i < NUM_PARTICLES; ++i)
  {
    particles.push_back(new SmokeParticle());
  }

  for(int i = 0; i < NUM_PARTICLES; ++i)
  {
    float negX = 0;
    float negZ = 0;

    switch (i%4){
      case 0 : negX= 1; negZ= 1; break;
      case 1 : negX= 1; negZ=-1; break;
      case 2 : negX=-1; negZ= 1; break;
      case 3 : negX=-1; negZ=-1; break;
    }
    particles.at(i)->velocity.x = negX*randomFloat();
    particles.at(i)->velocity.y = randomFloat();
    particles.at(i)->velocity.z = negZ*randomFloat();
    particles.at(i)->timeAlive = 0;
    particles.at(i)->pos = origin;
  }

  frame = 0;

  frameTime = 0;

  timeAlive = 0;

  done = false;
}

void Explosion::drawShockwave( float Radius, int numPoints )
{
 glBegin( GL_LINE_STRIP );
   //glColor3f(1.0,0.3,0.3);
    for( int i=0; i<numPoints; i++ )
    {
      float Angle = i * ((2.0*PI)/numPoints); 
      float X = cos( Angle )*Radius; 
      float Y = sin( Angle )*Radius;
      glVertex3f( origin.x + X, origin.y, origin.z + Y );
    }
 glEnd();
}

bool compareParticles(SmokeParticle* particle1, SmokeParticle* particle2)
{
  return (particle1->pos).z <
		(particle2->pos).z;
}

void Explosion::step()
{
  for(int i = 0; i < NUM_PARTICLES; ++i)
  {
    particles[i]->timeAlive += STEP_TIME;

    if(particles[i]->timeAlive < DURATION)
    {
      particles[i]->pos.x += (particles[i]->velocity.x * STEP_TIME) / NUM_FRAMES;
      particles[i]->pos.y -= GRAVITY;
      particles[i]->pos.y += (particles[i]->velocity.y * STEP_TIME)*5 / NUM_FRAMES;
      particles[i]->pos.z += (particles[i]->velocity.z * STEP_TIME) / NUM_FRAMES;
    }
  }
}

void Explosion::advance(float dt)
{
  timeAlive += dt; 
  while (dt > 0) {
		if (frameTime < dt) {
			dt -= frameTime;
			step();
			frameTime = STEP_TIME;
		}
		else {
			frameTime -= dt;
			dt = 0;
		}
	}
}

void Explosion::render()
{
    frame++;
    advance(FPS);
    
    if(timeAlive < DURATION)
    {
		  sort(particles.begin(), particles.end(), compareParticles);

			glEnable(GL_BLEND);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		  glEnable(GL_TEXTURE_2D);
		  glBindTexture(GL_TEXTURE_2D, 14);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      
      drawShockwave(timeAlive / DURATION, 50);
      float cd = 1 - (timeAlive / DURATION);

		  glBegin(GL_QUADS);
		    for(int i = 0; i < particles.size(); i++) 
        {
			    SmokeParticle* p = particles[i];

          float blend = p->timeAlive / DURATION;
          if(blend > 1.0f) blend = 1.0f;
          
			    glColor4f(1.0, 1.0, 1.0, 1 - blend);

			    float size = PARTICLE_SIZE / 2;
          Vector3 pos = p->pos;

          Vector3 bl = Vector3(pos[0] - size*cd, pos[1] - size*cd, pos[2]);
          Vector3 br = Vector3(pos[0] - size*cd, pos[1] + size*cd, pos[2]);
          Vector3 tr = Vector3(pos[0] + size*cd, pos[1] + size*cd, pos[2]);
          Vector3 tl = Vector3(pos[0] + size*cd, pos[1] - size*cd, pos[2]);
				
			    glTexCoord2f(0, 0);
			    glVertex3f(bl.x, bl.y, bl.z);
			    glTexCoord2f(0, 1);
			    glVertex3f(br.x, br.y, br.z);
			    glTexCoord2f(1, 1);
			    glVertex3f(tr.x, tr.y, tr.z);
			    glTexCoord2f(1, 0);
			    glVertex3f(tl.x, tl.y, tl.z);
		    }
		  glEnd();
      glDisable(GL_TEXTURE_2D);
      glDisable(GL_BLEND);
    }
    else end();
}

void Explosion::end()
{
  particles.clear();
  done = true;
}





