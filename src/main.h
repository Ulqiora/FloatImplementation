#ifndef _SRC_MAIN_H_
#define _SRC_MAIN_H_
#include "Float/Float.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <iostream>
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))
#define NUMBER_NEURON_L1 5
#define NUMBER_NEURON_L2 1
#define NUMBER_NEURON_L3 1
using namespace std;
float** InitWeightsL12Standart();
Float** CopyWeightsToMyFloat(float** weights,int rows, int cols);
Float*  CopyNeuronsToMyFloat(float* neurons,int size);
void CalcNextLayerStand(float** weights,int rows,int cols,float* leftLayer,float* rightLayer);
void CalcNextLayer(Float** weights,int rows,int cols,Float* leftLayer,Float* rightLayer);
void PrintResult(Float* output,int size);
void PrintResultS(float* output,int size);
#endif //_SRC_MAIN_H_