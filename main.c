#include "Float/Float.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUMBER_NEURON_L1 5
#define NUMBER_NEURON_L2 1
#define NUMBER_NEURON_L3 1
void CalcNextLayerStand(float** weights,int rows,int cols,float* leftLayer,float* rightLayer);
void CalcNextLayer(Float** weights,int rows,int cols,Float* leftLayer,Float* rightLayer);
void PrintResult(Float* output,int size);
void PrintResultS(float* output,int size);
int main() {
    float inputS[NUMBER_NEURON_L1] = {150.35629,236.5986,5998.236,0.12698,2.123658};
    float** weights_L12_Stand = (float**)calloc(NUMBER_NEURON_L1,sizeof(float*));
    for(int i=0;i<NUMBER_NEURON_L1;i++){
        weights_L12_Stand[i] = (float*)calloc(NUMBER_NEURON_L2,sizeof(float));
    }
    weights_L12_Stand[0][0] = 0.03569;
    weights_L12_Stand[1][0] = -2.4569;
    weights_L12_Stand[2][0] = 0.03569;
    weights_L12_Stand[3][0] = -2.4569;
    weights_L12_Stand[4][0] = 0.03569;
    Float** weights_L12 = (Float**)calloc(NUMBER_NEURON_L1,sizeof(Float*));
    for(int i=0;i<NUMBER_NEURON_L1;i++){
        weights_L12[i] = (Float*)calloc(NUMBER_NEURON_L2,sizeof(Float));
    }
    weights_L12[0][0] = *(Float*)(weights_L12_Stand[0]+0);
    weights_L12[1][0] = *(Float*)(weights_L12_Stand[1]+0);
    weights_L12[2][0] = *(Float*)(weights_L12_Stand[2]+0);
    weights_L12[3][0] = *(Float*)(weights_L12_Stand[3]+0);
    weights_L12[4][0] = *(Float*)(weights_L12_Stand[4]+0);
    
    Float input[NUMBER_NEURON_L1] = {*(Float*)(&inputS)};
    Float output[NUMBER_NEURON_L2];
    float outputS[NUMBER_NEURON_L2];
    CalcNextLayer(weights_L12,NUMBER_NEURON_L1,NUMBER_NEURON_L2,input,output);
    CalcNextLayerStand(weights_L12_Stand,NUMBER_NEURON_L1,NUMBER_NEURON_L2,inputS,outputS);
    PrintResultS(outputS,NUMBER_NEURON_L2);
    PrintResult(output,NUMBER_NEURON_L2);
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

