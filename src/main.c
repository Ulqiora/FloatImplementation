#include "main.h"
int main() {
    float inputS[NUMBER_NEURON_L1] = {150.35629f,236.5986f,5998.236f,0.12698f,2.123658f,23.658f,-435.436f,91.547f,846.0012f,104.000};
    Float* input = CopyNeuronsToMyFloat(inputS,NUMBER_NEURON_L1);
    check
    for(int i=0;i<NUMBER_NEURON_L1;i++){
        assert(inputS[i] == *(float*)(input+i));
    }
    float** weights_L12_Stand = InitWeightsL12Standart();
    Float** weights_L12 = CopyWeightsToMyFloat(weights_L12_Stand,NUMBER_NEURON_L1,NUMBER_NEURON_L2);
    for(int i=0;i<NUMBER_NEURON_L1;i++){
        for (int j = 0; j < NUMBER_NEURON_L2; j++) {
            assert(weights_L12_Stand[i][j] == *(float*)(weights_L12[i] + j));
        }
    }
    Float output[NUMBER_NEURON_L2];
    float outputS[NUMBER_NEURON_L2];
    CalcNextLayer(weights_L12,NUMBER_NEURON_L1,NUMBER_NEURON_L2,input,output);
    CalcNextLayerStand(weights_L12_Stand,NUMBER_NEURON_L1,NUMBER_NEURON_L2,inputS,outputS);
}

float** InitWeightsL12Standart(){
    float** weights_L12_Stand = (float**)calloc(NUMBER_NEURON_L1,sizeof(float*));
    for(int i=0;i<NUMBER_NEURON_L1;i++)
        weights_L12_Stand[i] = (float*)calloc(NUMBER_NEURON_L2,sizeof(float));
    weights_L12_Stand[0][0] = 0.03569f;
    weights_L12_Stand[1][0] = -2.4569f;
    weights_L12_Stand[2][0] = 0.03569f;
    weights_L12_Stand[3][0] = -2.4569f;
    weights_L12_Stand[4][0] = 0.03569f;
    weights_L12_Stand[5][0] = 0.03569f;
    weights_L12_Stand[6][0] = -2.4569f;
    weights_L12_Stand[7][0] = 0.03569f;
    weights_L12_Stand[8][0] = -2.4569f;
    weights_L12_Stand[9][0] = 0.03569f;
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
            Float res = Multiplication(leftLayer[j],weights[j][i]);
            printf("%g\\\\%g\t",*(float*)(rightLayer+i),*(float*)(&res));
        }
        printf("\n");
        rightLayer[i] = FunctionActivation(rightLayer[i]);
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
            printf("%g\\\\%g\t",rightLayer[i],leftLayer[j]*weights[j][i]);
        }
        printf("\n");
        rightLayer[i] = 1/(1+fabs(rightLayer[i]));
    }
}
