#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//double exp(double x);
double drand48(void);
void srand48(long int seed);
/*
struct neuron 
{
    double V; // Value
    int I; // Index (start at 0)
    int L; // Layer
    int Next_Number; // Number of nexts
    int Next[]; // Array of following/next neurons indexs
    double Weight[]; // Weight of the different transitions 
	        // (Weight[i] = weight of the transition with neuron Next[i])
};
*/

struct neuralLayer 
{
    //int I; // Index of the layer in the network
    size_t n_Size; // Number of neurons
    int *n_Index; // array of "n_Size" size containing index of each neuron of the layer 
    //struct neuron Neurons[]; // Neurons of the layer
};

struct neuralNetwork
{
    size_t l_Size; // Number of layers
    struct neuralLayer *Layers; // Layers in the network
    size_t n_Size; // Total number of neurons in the network
    // struct neuron Neurons_Arrays[]; // All the neurons of the network (sorted using index I)
    double *values_Vect; // Values of each neuron of the network (indexed using I)
    double *weights; // Matrix of "N_Size" size containing weight of each link
    // Activation function g (return "double")
};

double logistic (double x)
{  
    return 1/(1 + exp(-x)); 
}

/*** Functions ***/

double sum_i (double *weights, int j, double *values_Vect, size_t size)
{
    double sum = 0;
    for (size_t i = 0; i<size; i++)
    {
        sum += weights[j * size + i] * values_Vect[i];
    }
    return sum;

}

double sum_j (double *weights, int i, double errors_Vect[], size_t size)
{
    double sum = 0;
    for (size_t j = 0; j<size; j++)
    {
        sum += weights[j * size + i] * errors_Vect[j];
    }
    return sum;
}

// Algo for a XOR function
// examples[][] = array of arrays containing 3 double values.
//                1st and 2nd values are the inputs for XOR
//                3rd is the wanted output value
void Back_Prop_Learning(int sets_of_examples, double *examples, struct neuralNetwork *network)
{

int index = 0;
double A = 1; // taux d'apprentissage
double in = 0;
double *errors = malloc(network->n_Size * sizeof(double));
for (size_t i = 0; i<network->n_Size; i++)
{
    errors[i] = 0;
}

int test = 0;
do
{
    for(size_t err = 0; err<network->n_Size; err++)
    {
        errors[err] = 0;
    }
    for(int e = 0; e < sets_of_examples; ++e)
    {
        network->values_Vect[0] = examples[e * 3 + 0];
        network->values_Vect[1] = examples[e * 3 + 1];   
        
        for(size_t l = 1; l < network->l_Size; ++l)
        {
            for(size_t j = 0; j < network->Layers[l].n_Size; ++j)
            {
                index = network->Layers[l].n_Index[j];

                in = sum_i (network->weights, index, network->values_Vect, network->n_Size);
                network->values_Vect[index] = logistic(in);                
            }
        }        
        errors[network->n_Size-1] = examples[e * 3 +3] - network->values_Vect[network->n_Size-1];
        for(int l = network->l_Size-2; l>=0; --l)
        {
            for(size_t i = 0; i < network->Layers[l].n_Size; ++i)
            {
                index = network->Layers[l].n_Index[i];
                errors[index] = network->values_Vect[index] * (1- network->values_Vect[index]) * sum_j(network->weights, index, errors, network->n_Size);            
            }
        }
        for(size_t i = 0; i< network->n_Size; i++)
        {
            for(size_t j = 0; j< network->n_Size; j++)
            {
                if(network->weights[i * network->n_Size + j])
                {
                network->weights[i * network->n_Size + j] = network->weights[i * network->n_Size + j] + A * network->values_Vect[i] * errors[j];
                }
            }
        }        
        if(test%100 == 0)
        {   
            printf("\nTest %d \n \n",test);
            printf("    Example %d / %d \n",e+1,sets_of_examples);

            for(size_t t = 0; t<network->n_Size; t++)
            {            
                printf("Value[%d] = %lf \n",t,network->values_Vect[t]);            
            }
            
            for(size_t t = 0; t<network->n_Size; t++)
            {            
                printf("Error[%d] = %lf \n",t,errors[t]);
            }
            
            for(size_t i = 0; i<network->n_Size; i++)
            {            
                for(size_t j = 0; j<network->n_Size; j++)
                {
                if(network->weights[i * network->n_Size + j])
                {
                printf("weight [%d,%d] = %lf \n",j,i,network->weights[i*network->n_Size + j]);
                }
                }
            }     
        }        
    }
    test++;
}
while(test <= 100);
}


int main()
{
    srand48(time(NULL));
    printf("SALUT \n");

    int tab_L1[2] = {0,1};
    int tab_L2[2] = {2,3};
    int tab_L3[1] = {4};
    
    struct neuralLayer L1;
    L1.n_Size = 2;    
    L1.n_Index = tab_L1;
    struct neuralLayer L2;
    L2.n_Size = 2;
    L2.n_Index = tab_L2;
    struct neuralLayer L3;
    L3.n_Size = 1;
    L3.n_Index = tab_L3;

    struct neuralLayer *Layers = malloc(3 * sizeof(struct neuralLayer));
    Layers[0] = L1;
    Layers[1] = L2;
    Layers[2] = L3;

    double vals[5] = {0};
    double weights[5*5] = {0}; 
    weights[2*5+0] = -1;   //drand48();
    weights[2*5+1] =  1.5;   //drand48();
    weights[3*5+0] =  2;   //drand48();
    weights[3*5+1] = -2.5;  //drand48();
    weights[4*5+2] = -3;  //drand48();
    weights[4*5+3] =  3.5; //drand48();

    struct neuralNetwork my_net;
    my_net.l_Size = 3;
    my_net.Layers = Layers;
    my_net.n_Size = 5;
    my_net.values_Vect = vals;
    my_net.weights = weights;

    //double examples2[4][3] = {{0,0,0},{0,1,1},{1,0,1},{1,1,0}};
    double examples[4*3] ={0,0,0,0,1,1,1,0,1,1,1,0};

    for(size_t i = 0; i<my_net.n_Size;i++)
    {
        printf("Neuron %d value = %lf \n",i,my_net.values_Vect[i]); 
    }
    for(size_t i = 0; i<my_net.n_Size; i++)
    {
        for(size_t j = 0; j<my_net.n_Size; j++)
        {
            printf("weight [%d,%d] = %lf \n",(i * my_net.n_Size + j) % my_net.n_Size,i, my_net.weights[i * my_net.n_Size + j]);
        }
    }

    Back_Prop_Learning(4,examples,&my_net);

/*
    for(size_t i = 0; i<my_net.n_Size;i++)
    {
        printf("Neuron %d value = %lf \n",i+1,my_net.values_Vect[i]); 
    }
    for(size_t i = 0; i<my_net.n_Size; i++)
    {
        for(size_t j = 0; j<my_net.n_Size; j++)
        {
            printf("Weight n%d,n%d = %lf \n",i+1 , (i * my_net.n_Size + j) % my_net.n_Size+1, my_net.weights[i * my_net.n_Size + j]);
        }
    }
*/  
    return 0;
}
