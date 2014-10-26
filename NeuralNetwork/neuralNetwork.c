#include"neuralNetwork.h"   


const float THRESHOLD = 0.001;  // Average prmissible output error
const long MAX_ITER = 100000;  // Max iter while learning


struct neuron **new_network(int layers, int *layers_Size)
{
    struct neuron **n;
    n = malloc(layers *sizeof(struct neuron *));
    
    for(int i = 0; i<layers;i++)
    {
        n[i]= malloc(layers_Size[i] *sizeof(struct neuron));
    }

    for(int i = 0; i<layers-1;i++)
    {
        for(int j = 0; j<layers_Size[i]; j++)
        {
            n[i][j].w = malloc(layers_Size[i+1] * sizeof(float));
        }
    }
    return n;
}

// Activation function


float logistic(float x)
{
    if (fabs(x)<1e-10)
        return 0.5;
    else
        return ( 1.0 / ( 1.0 + exp(-x)));
}

// Derivative

float derivative(float x)
{
    return ( x * (1 - x) );
}

// Weights initialization

void init_weights(struct neuron **n, int *layers_Size, int layers)
{
    int i, j, k;
    int t;

    time((time_t *)&t);
    srand(t);

    for(i=0;i<layers-1;i++)
        for(j=0;j<layers_Size[i];j++)
            for(k=0;k<layers_Size[i+1];k++)
                n[i][j].w[k] = 1.0 * rand() / RAND_MAX * 1.0;
}

// Learning functions

void init_inputs(struct neuron **n, int *example, int inputs)
{
    int i;

    for(i=0;i<inputs;i++)
        n[0][i].output = 1.0 * example[i];
}

void feedforward(struct neuron **n, int *layers_Size, int layers)
{
    int i, j, k;
    float val;

    for(i=1;i<layers;i++)
    {
        for(j=0;j<layers_Size[i];j++)
        {
            val = 0.0;
          
            for(k=0;k<layers_Size[i-1];k++)
                val+=n[i-1][k].w[j] * n[i-1][k].output;
            
            n[i][j].output = logistic(val);
        }
    }
}


float final_error(struct neuron **n, int *example, int *layers_Size,int layers)
{
    int i;
    float output_error = 0.0;
    float Error;

    for(i=0;i<layers_Size[layers-1];i++)
    {
        Error = (1.0 * example[layers_Size[0]+i]) - n[layers-1][i].output;
        n[layers-1][i].error = Error * derivative(n[layers-1][i].output);
        output_error += 0.5 * Error * Error;
    }
    return output_error;
}


void back_prop(struct neuron **n, int *layers_Size, int layers)
{
    int i, j, k;
    float Error;

    for(i=layers-2;i>0;i--)
    {
        for(j=0;j<layers_Size[i];j++)
        {
            Error = 0;
           
            for(k=0;k<layers_Size[i+1];k++)
                Error+= n[i+1][k].error * n[i][j].w[k];
            n[i][j].error = Error * derivative(n[i][j].output);
        }
    }
}



void weight_adjust(struct neuron **n, int *layers_Size, int layers)
{
    int i, j, k;


    for(i=layers-2;i>=0;i--)
        for(j=0;j<layers_Size[i];j++)
            for(k=0;k<layers_Size[i+1];k++)
                n[i][j].w[k]+= n[i+1][k].error * n[i][j].output;

}
 

 float calculate(struct neuron **n, int *example, int *layers_Size, int layers)
 {
    float Error;

    init_inputs(n, example, layers_Size[0]);
    feedforward(n, layers_Size, layers);
    Error = final_error(n, example, layers_Size, layers);
    back_prop(n, layers_Size, layers);
    weight_adjust(n, layers_Size, layers);
    
    return Error;
 }


 void learn(struct neuron **n, int **examples, int *layers_Size, int layers,
            int nb_ex)
{
    int i;
    float Error;
    long iter = 0;

    do
    {
     iter++;
     Error = 0.0;

     for(i=0;i<nb_ex;i++)
        Error += calculate(n, examples[i], layers_Size, layers);
    }while( (Error>THRESHOLD * nb_ex) && (iter<(long)MAX_ITER) );
}


 // Display functions

 void display_weights(struct neuron **n, int *layers_Size, int layers)
 {
   int i, j, k;

   for(i=0;i<layers-1;i++)
   {
     printf("Layer # %d \n", i);
     for(j=0;j<layers_Size[i];j++)
     {
       printf("  Neuron # %d \n    ", j+1);
       for(k=0;k<layers_Size[i+1];k++)
	 printf(" %2.4f ",n[i][j].w[k]);
       printf("\n");
     }
   }
 }


 void display_outputs(struct neuron **n, int *layers_Size, int layers)
 {
   int i, j;
   for(i=0;i<layers;i++)
   {
     printf("Layer # %d \n", i);
     for(j=0;j<layers_Size[i];j++)
     {
       printf("     Neuron # %d   %f\n", j+1, n[i][j].output);
     }
   }
 }


 // Main function

 int main()
 {

    int layers = 3;// Layers in the network (including input and output layers)
    int layers_Size[] = {2,4,1} ;   // Size of each layer
    
    struct neuron **net;
    int nb_ex = 4;  // Number of examples;

    int e1[] = {0,0,0};
    int e2[] = {0,1,1};
    int e3[] = {1,0,1};
    int e4[] = {1,1,0};

    int *examples[] = {e1,e2,e3,e4};

    net = new_network(layers, layers_Size);

    init_weights(net, layers_Size, layers);
    learn(net, examples, layers_Size, layers, nb_ex);
  

    for(int i = 0; i<nb_ex; i++)
    {
        init_inputs(net, examples[i], layers_Size[0]);
        feedforward(net, layers_Size, layers);
        printf("\n%d XOR %d = %f\n",examples[i][0], examples[i][1],
            net[layers-1][layers_Size[layers-1]-1].output);
    }
    printf("\n");

    return 0;
 }
