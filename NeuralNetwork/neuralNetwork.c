#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

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
        sum += weights[i * size + j] * errors_Vect[j];
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
double A = 0.1; // taux d'apprentissage
double in = 0;
double *errors = malloc(network->n_Size * sizeof(double));
//double errors[network.n_Size] = {0};
for (size_t i = 0; i<network->n_Size; i++)
{
    errors[i] = 0;
}

//do
//{
    for(int e = 0; e < sets_of_examples; ++e)
    {
        //for(int i = 0; i < network.Layers[0].n_Size; ++i)
        //{
            
        //}

        network->values_Vect[0] = examples[e * sets_of_examples + 0];
        network->values_Vect[1] = examples[e * sets_of_examples + 1];

        for(size_t l = 1; l < network->l_Size; ++l)
        {
            for(size_t j = 0; j < network->Layers[l].n_Size; ++j)
            {
                index = network->Layers[l].n_Index[j];

                in = sum_i (network->weights, index, network->values_Vect, network->n_Size);
                network->values_Vect[index] = logistic(in); 
            }
        }
        
        errors[network->n_Size-1] = examples[e * sets_of_examples + 3] - network->values_Vect[network->n_Size-1];
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
                network->weights[i * network->n_Size + j] = network->weights[i * network->n_Size + j] * A * network->values_Vect[i] * errors[j];
            }

        }
    }
//}
//while(true);
//return network;
}
/*
double my_rand()
{
    double x = 0;
    printf("x avant %lf \n",x);
    do
    {
        x = drand48();
        printf("x pendant %lf \n",x);
    }while(!x);
    printf("X apres %lf \n",x);
    return x;
}
*/

int main()
{
    srand48(time(NULL));
    printf("SALUT \n");

    int tab_L1[2] = {1,2};
    int tab_L2[2] = {3,4};
    int tab_L3[2] = {5,6};
    int tab_L4[2] = {7,8};
    int tab_L5[1] = {9};
    
    struct neuralLayer L1;
    L1.n_Size = 2;    
    L1.n_Index = tab_L1;
    struct neuralLayer L2;
    L2.n_Size = 2;
    L2.n_Index = tab_L2;
    struct neuralLayer L3;
    L3.n_Size = 2;
    L3.n_Index = tab_L3;
    struct neuralLayer L4;
    L4.n_Size = 2;
    L4.n_Index = tab_L4;
    struct neuralLayer L5;
    L5.n_Size = 1;
    L5.n_Index = tab_L5;

    struct neuralLayer *Layers = malloc(5 * sizeof(struct neuralLayer));
    Layers[0] = L1;
    Layers[1] = L2;
    Layers[2] = L3;
    Layers[3] = L4;
    Layers[4] = L5;

    double vals[9] = {0};
    double weights[9*9] = {0};
    weights[2*9+0] = drand48();
    weights[2*9+1] = drand48();
    weights[3*9+0] = drand48();
    weights[3*9+1] = drand48();
    weights[4*9+2] = drand48();
    weights[4*9+3] = drand48();
    weights[5*9+2] = drand48();
    weights[5*9+3] = drand48();
    weights[6*9+4] = drand48();
    weights[6*9+5] = drand48();
    weights[7*9+4] = drand48();
    weights[7*9+5] = drand48();
    weights[8*9+6] = drand48();
    weights[8*9+7] = drand48();

    struct neuralNetwork my_net;
    my_net.l_Size = 5;
    my_net.Layers = Layers;
    my_net.n_Size = 9;
    my_net.values_Vect = vals;
    my_net.weights = weights;



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


    


    return 0;
}
