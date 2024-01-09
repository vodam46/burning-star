#ifndef NOISE_H
#define NOISE_H

extern int SEED;
extern int hash[256];

float noise2d(float x, float y, float freq, int depth);

void noise_init();

#endif
