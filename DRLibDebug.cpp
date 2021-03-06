// DRLibDebug.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>
#include <iostream>

#define SQR(x) ((x) * (x))
#define PITAGORAS(x,y) (sqrt(SQR(x) + SQR(y)))
#define SIGN(x) ((x) < 0 ? -1 : 1)

typedef struct 
{
	double position[3];
	double rotation[3];
	double velocity[3];
	double acceleration[3];
	bool hasVelocityDest[2];
	double velocityDest[2];
} SEntityParams;


void simulate(SEntityParams* p, double timePassed)
{
	double velocity2d[] = {
		PITAGORAS(p->velocity[0], p->velocity[1]),
		p->velocity[2]
	}, deltaSpeed[3] = { 0, 0, 0 };
	double currentCourse = p->rotation[0], nextCourse = p->rotation[0];
	if (p->hasVelocityDest[0])
	{
		double axy = PITAGORAS(p->acceleration[0], p->acceleration[1]);
		if (abs(p->velocityDest[0] - velocity2d[0]) < axy)
		{
			std::cout << "WTF" << std::endl;
		}
		else
		{
			deltaSpeed[0] = p->acceleration[0] * timePassed;
			deltaSpeed[1] = p->acceleration[1] * timePassed;
		}
	}
	double interimCourse = 0.5 * (currentCourse + nextCourse);
	double velocityXY = PITAGORAS(p->velocity[0], p->velocity[1]) + deltaSpeed[0];
	SEntityParams result;
	memcpy(&result, p, sizeof(SEntityParams));
	result.velocity[0] = (p->velocity[0] + deltaSpeed[0]);
	result.velocity[1] = (p->velocity[1] + deltaSpeed[1]);
	result.velocity[2] = 0;
	result.position[0] = p->position[0] + velocity2d[0] * timePassed + deltaSpeed[0] * 0.5 * SQR(timePassed) * sin(interimCourse);
	result.position[1] = p->position[1] + velocity2d[1] * timePassed + deltaSpeed[0] * 0.5 * SQR(timePassed) * cos(interimCourse);
	memcpy(p, &result, sizeof(SEntityParams));
}

int main()
{
	SEntityParams p;
	memset(&p, 0, sizeof(SEntityParams));
	p.position[0] = 624091;
	p.position[1] = 3556990;
	p.position[2] = 100;
	p.rotation[0] = -0.332295;
	p.velocity[0] = -213.718;
	p.velocity[1] = 619.309;
	p.acceleration[0] = 60.4849;
	p.acceleration[1] = 20.6441;
	p.hasVelocityDest[0] = true;
	p.velocityDest[0] = -10000000;
	simulate(&p, 0.1);
	simulate(&p, 0.1);
	simulate(&p, 0.1);
	simulate(&p, 0.1);
	simulate(&p, 0.1);
	if (p.velocity[0] > -213.718 && p.velocity[1] > 619.309)
	{
		std::cout << "AT LAST" << std::endl;
	}
    return 0;
}

