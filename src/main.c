#include "Float/Float.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <iostream>
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
int main() {
    float inputS[NUMBER_NEURON_L1] = {150.35629,236.5986,5998.236,0.12698,2.123658};
    Float* input = CopyNeuronsToMyFloat(inputS,NUMBER_NEURON_L1);
    printf("%f\n",*(float*)(input+4));



    float** weights_L12_Stand = InitWeightsL12Standart();
    Float** weights_L12 = CopyWeightsToMyFloat(weights_L12_Stand,NUMBER_NEURON_L1,NUMBER_NEURON_L2);
    printf("%g\n",*(float*)(weights_L12[4]+0));
    
    Float output[NUMBER_NEURON_L2];
    float outputS[NUMBER_NEURON_L2];

    auto start = chrono::steady_clock::now();
    CalcNextLayer(weights_L12,NUMBER_NEURON_L1,NUMBER_NEURON_L2,input,output);
    auto end = chrono::steady_clock::now();
    CalcNextLayerStand(weights_L12_Stand,NUMBER_NEURON_L1,NUMBER_NEURON_L2,inputS,outputS);
    PrintResult((Float*)outputS,NUMBER_NEURON_L2);
    PrintResult(output,NUMBER_NEURON_L2);
        std::cout << "Elapsed time in nanoseconds: "
        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
        << " ns" << endl;
}

float** InitWeightsL12Standart(){
    float** weights_L12_Stand = (float**)calloc(NUMBER_NEURON_L1,sizeof(float*));
    for(int i=0;i<NUMBER_NEURON_L1;i++)
        weights_L12_Stand[i] = (float*)calloc(NUMBER_NEURON_L2,sizeof(float));
    weights_L12_Stand[0][0] = 0.03569;
    weights_L12_Stand[1][0] = -2.4569;
    weights_L12_Stand[2][0] = 0.03569;
    weights_L12_Stand[3][0] = -2.4569;
    weights_L12_Stand[4][0] = 0.03569;
    return weights_L12_Stand;
}

Float** CopyWeightsToMyFloat(float** weights,int rows, int cols){
    Float** weights_L = (Float**)calloc(NUMBER_NEURON_L1,sizeof(Float*));
    for(int i=0;i<NUMBER_NEURON_L1;i++){
        weights_L[i] = (Float*)calloc(NUMBER_NEURON_L2,sizeof(Float));
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            weights_L[i][j] = *(Float*)(weights[i]+j);
        }
    }
    return weights_L;
}

Float*  CopyNeuronsToMyFloat(float* neurons,int size){
    Float* neuronsMy = (Float*)calloc(size,sizeof(Float));
    for(int i=0;i<size;i++){
        neuronsMy[i] = *(Float*)(neurons+i);
    }
    return neuronsMy;
}

void PrintResult(Float* output,int size){
    for(int i=0;i<size;i++){
        printf("%g\n",*(float*)(output+i));
    }
}
void PrintResultS(float* output,int size){
    for(int i=0;i<size;i++){
        printf("%g\n",output[i]);
    }
}

void CalcNextLayer(Float** weights,int rows,int cols,Float* leftLayer,Float* rightLayer){
    // printf("number neurons in leftlayer = %d\n",cols);
    for(int i=0;i<cols;i++){
        // printf("number neuron in rightlayer = %d\n",i);
        rightLayer[i].value_ = 0;
        for(int j=0;j<rows;j++){
            // printf("number neuron in leftlayer = %d\n",i);
            rightLayer[i] = Addiction(rightLayer[i],Multiplication(leftLayer[j],weights[j][i]));
            printf("%g\\\\%g\t",*(float*)(rightLayer+i),Multiplication(leftLayer[j],weights[j][i]));
        }
        printf("\n");
        // rightLayer[i] = FunctionActivation(rightLayer[i]);
    }
}
void CalcNextLayerStand(float** weights,int rows,int cols,float* leftLayer,float* rightLayer){
    // printf("number neurons in leftlayer = %d\n",cols);
    for(int i=0;i<cols;i++){
        // printf("number neuron in rightlayer = %d\n",i);
        rightLayer[i] = 0;
        for(int j=0;j<rows;j++){
            // printf("number neuron in leftlayer = %d\n",i);
            rightLayer[i] = rightLayer[i] + leftLayer[j]*weights[j][i];
            printf("%g\t",rightLayer[i]);
        }
        printf("\n");
        // rightLayer[i] = 1/(1+fabs(rightLayer[i]));
    }
}





//     float val=236.5986;
//     float val2=0.03569;
//     Float temp = StandartFloatToCustomFloat(val);
//     Float temp2 = StandartFloatToCustomFloat(val2);
//     Float res = Multiplication(temp,temp2);
//     PrintBits(temp);
//     PrintBits(temp2);
//     PrintBits(res);
//     Float res2=StandartFloatToCustomFloat(val*val2);
//     printf("%g\n",*((float*)&res2));
//     printf("%g\n",*((float*)&res));