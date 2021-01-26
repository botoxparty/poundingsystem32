#include "soundgenerator.h"

SoundGenerator::SoundGenerator()
{
}

char *SoundGenerator::soundNames[8] = {"Sine", "Sine2", "Sawtooth",
											 "Square", "Saxxx", "Jappy", "Star", "Microwave"};

float SoundGenerator::Sine(Oscillator *osc)
{
	float_t z;

	while (osc->phase < 0) // keep phase in [0, 2pi]
		osc->phase += _2PI;
	while (osc->phase >= _2PI)
		osc->phase -= _2PI;

	z = sinf(osc->phase);
	osc->out = osc->amp * z * z * z * z * z;

	osc->phase += _2PI * Ts * osc->freq; // increment phase
	return osc->out;
}

float_t SoundGenerator::SineTable(Oscillator *op) // Complex waveform : +/- |sin(phi)|^alpha(freq), tends to a sine at high freqs
{
	float_t z, x, alpha;

	while (op->phase < 0) // keep phase in [0, 2pi]
		op->phase += _2PI;
	while (op->phase >= _2PI)
		op->phase -= _2PI;

	x = op->freq;
	//alpha = 3.f;
	//http://www.math.ucla.edu/~ronmiech/Interpolation/HTMDOCS/Introduction/Interpolation_Applet.htm  :
	alpha = 81.096f + x * (-.037f + .582E-5f * x - .311E-9f * x * x); //alpha varies from 80 to 1 with freq from 30Hz to 8000Hz
	//alpha = 60.695f -.023f * x + .31E-5f * x*x -.141E-9f * x*x*x ;
	//alpha = (50.f-1)/(30.f-8000)*(x - 8000) + 1 ;
	//z = powf(fabsf(sinf(op->phase )), alpha) ;

	z = powf(fabsf(sinetable[lrintf(ALPHA * (op->phase))]), alpha);

	if (op->phase < _PI)
		op->out = op->amp * z;
	else
		op->out = -op->amp * z;

	op->phase += _2PI * Ts * op->freq; // increment phase

	return op->out;
}