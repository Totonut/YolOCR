#include"neuralNetwork.h"


const double THRESHOLD = 0.05;  // Average permissible output error
const long MAX_ITER = 10000;  // Max iter while learning


struct neuron **new_network(int *layers_Size, int layers)
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
            n[i][j].w = malloc(layers_Size[i+1] * sizeof(double));
        }
    }
    return n;
}

// Activation function


double logistic(double x)
{
    if (fabs(x)<1e-10)
        return 0.5;
    else
        return ( 1.0 / ( 1.0 + exp(-x)));
}

// Derivative

double derivative(double x)
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
                {
                  double sign = 1.0;
                  if((1.0 * rand() / RAND_MAX * 1.0) > 0.5)
                    sign = -1.0;
                  n[i][j].w[k] = sign * 0.5 *((1.0 * rand()) / (RAND_MAX * 1.0));
                }
}

// Learning functions

void init_inputs(struct neuron **n, int *example, int inputs)
{
    for(int i=0; i<inputs; i++)
        n[0][i].output = 1.0 * example[i];
}

void feedforward(struct neuron **n, int *layers_Size, int layers)
{
    double val;

    for(int l=1; l<layers; l++)
    {
        for(int j=0; j<layers_Size[l]; j++)
        {
            val = 0.0;
          
            for(int k=0; k<layers_Size[l-1]; k++)
                val+=n[l-1][k].w[j] * n[l-1][k].output;
            
            n[l][j].output = logistic(val);
        }
    }
}


double final_error(struct neuron **n, int **example, int *layers_Size,int layers)
{
    double output_error = 0.0;
    double Error;

    for(int i=0;i<layers_Size[layers-1];i++)
    {
        Error = n[layers-1][i].output - (1.0 * example[1][i]);
        n[layers-1][i].error = Error * derivative(n[layers-1][i].output);
        output_error += Error * Error;
    }
    return output_error;
}


void back_prop(struct neuron **n, int *layers_Size, int layers)
{
    double Error;

    for(int i=layers-2;i>0;i--)
    {
        for(int j=0;j<layers_Size[i];j++)
        {
            Error = 0;
           
            for(int k=0;k<layers_Size[i+1];k++)
                Error+= n[i+1][k].error * n[i][j].w[k];
            n[i][j].error = Error * derivative(n[i][j].output);
        }
    }
}



void weight_adjust(struct neuron **n, int *layers_Size, int layers)
{
    double A = 0.5;

    for(int i=layers-2;i>=0;i--)
        for(int j=0;j<layers_Size[i];j++)
            for(int k=0;k<layers_Size[i+1];k++)
                n[i][j].w[k]-= A * n[i+1][k].error * n[i][j].output;

}
 

double calculate(struct neuron **n, int **example, int *layers_Size, int layers)
 {
    double Error;

    init_inputs(n, example[0], layers_Size[0]);
    feedforward(n, layers_Size, layers);
    Error = final_error(n, example, layers_Size, layers);
    back_prop(n, layers_Size, layers);
    weight_adjust(n, layers_Size, layers);
    
    return Error;
 }


 void learn(struct neuron **n, int ***examples, int *layers_Size, int layers,
            int nb_ex)
{
    double Error;
    long iter = 0;

    do
    {
     iter++;
     Error = 0.0;

     for(int i=0;i<nb_ex;i++)
        Error += calculate(n, examples[i], layers_Size, layers);
    }while( (0.5*Error>THRESHOLD * nb_ex) && (iter<(long)MAX_ITER) );
    printf("N°iter : %ld / %ld\n", iter, MAX_ITER);
}


 // Display functions

 void display_weights(struct neuron **n, int *layers_Size, int layers)
 {
   for(int i=0;i<layers-1;i++)
   {
     printf("Layer # %d \n", i);
     for(int j=0;j<layers_Size[i];j++)
     {
       printf("  Neuron # %d \n    ", j+1);
       for(int k=0;k<layers_Size[i+1];k++)
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

// Other functions

 

  void save(struct neuron **n, int *layers_Size, int layers)
  {
    char *fname = "file_net";
    FILE *file;
    if ((file = fopen(fname, "w")) == NULL) 
    {
      err(3, "Error while creating %s", fname);
    }

    for(int i=0;i<layers-1;i++)
      for(int j=0;j<layers_Size[i];j++)
        for(int k=0;k<layers_Size[i+1];k++)
          fprintf(file, "%f\n",n[i][j].w[k]);
          
    fclose(file);
  }

  void load(struct neuron **n, int *layers_Size, int layers)
  {
    char *fname = "file_net";
    FILE *file;
    
    if ((file = fopen(fname, "r")) == NULL) 
    {
      err(3, "Error while opening  %s", fname);
    }

    for(int i=0;i<layers-1;i++)
      for(int j=0;j<layers_Size[i];j++)
        for(int k=0;k<layers_Size[i+1];k++)
          if(fscanf(file, "%lf", &(n[i][j].w[k])) != EOF);
     
     fclose(file);
  }

  void get_inputs(SDL_Surface *img, int *inputs)
  {
    perfectImage(img);
    for (int i=0; i<img->h; ++i)
    {
      for (int j=0; j<img->w; ++j)
      {
        inputs[j + i*img->w] = getPix(img,j,i) == 0x00000000;
      }
    }
  }

  void writeEx()
  { 
    char *fname = "file_ex";
    FILE *file;
  
    if ((file = fopen(fname, "w")) == NULL)
    {
      err(3, "Error while creating %s", fname);
    }
  } 

  void writeNewEx(int *e, int ans, int *layers_Size, int layers)
  {
    char *fname = "file_ex";
    FILE *file;
    if ((file = fopen(fname, "a")) == NULL)
    {
      err(3, "Error while creating %s", fname);
    }
  
    for(int i = 0; i<layers_Size[0]; i++)
      fprintf(file, "%d\n",e[i]);
    

    int j;
    for(j = 0; j<ans; j++)
      fprintf(file, "%d\n",0);
    fprintf(file, "%d\n",1);
    

    for(int k = j+1; k<layers_Size[layers-1]; k++)
      fprintf(file, "%d\n",0);
    
  
  fclose(file);
  }

  int*** readEx(int nb_ex, int *layers_Size, int layers)
  {
    char *fname = "file_ex";
    FILE *file;
    if ((file = fopen(fname, "r")) == NULL)
    {
      err(3, "Error while creating %s", fname);
    }

    int ***e = calloc(nb_ex,sizeof(int**));

    for(int i = 0; i<nb_ex; i++)
    {
      e[i] = calloc(2,sizeof(int*));
      e[i][0] = calloc(layers_Size[0],sizeof(int));
      e[i][1] = calloc(layers_Size[0],sizeof(int));
      for(int j = 0; j<layers_Size[0]; j++)
        if(fscanf(file, "%d", &(e[i][0][j])) != EOF); 
      
      for(int k = 0; k<layers_Size[layers-1]; k++)
        if(fscanf(file, "%d", &(e[i][1][k])) != EOF);
    }
    
    fclose(file);
    return e; 
  }


  struct neuron **load_network(int *layers_Size, int layers)
  {
    struct neuron **net = new_network(layers_Size, layers);
    load(net, layers_Size, layers);

    return net;
  }


  char comput(struct neuron **net, int *inputs, int *layers_Size, int layers, char *chars)
  {    
    init_inputs(net, inputs, layers_Size[0]);
    feedforward(net, layers_Size, layers);
           
    float max = 0;
    int id = 0;
    for(int i = 0; i<layers_Size[layers-1]; i++)
    {
      if(net[layers-1][i].output > max)
      {
        max = net[layers-1][i].output;
        id = i;
      }
    }
    return chars[id];
  }

  // Main
/*
 int main()
 {
  int in_size = 256;
  int ou_size = 88;

  SDL_Surface *img_ex = IMG_Load("ex/Exemples2.jpg");
  SDL_Surface *img_test = IMG_Load("test/Test3.jpg");
  perfectImage(img_ex);
  perfectImage(img_test);

  int nb_ex = 0;
  int **inputs = find_char(img_ex, &nb_ex);
 
 printf("Nb_ex = %d\n",nb_ex);

  char *chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-=/%()[]éèàùëêç.,;:?!&@$€";
    // 88
  //char *chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    //62

 //char *chars = "0123456789";

  int layers = 4;// Layers in the network (including input and output layers)
  int layers_Size[] = {in_size, 2*in_size, in_size, ou_size};   // Size of each layer
   
  struct neuron **net;
   
  net = new_network(layers_Size, layers);
  init_weights(net, layers_Size, layers);

// Learn and save
  writeEx();
  for(int i = 0; i<nb_ex; i++)
    writeNewEx(inputs[i], i%ou_size, layers_Size, layers);
  int ***examples = readEx(nb_ex, layers_Size, layers);
  printf("Début learn\n");
  learn(net, examples, layers_Size, layers, nb_ex);
  save(net,layers_Size, layers);
printf("Fin learn\n");

// Load
  //load(net, layers_Size, layers);

  int correct = 0;
  //printf("Examples :\n");
  for(int e = 0; e<nb_ex; e++)
  {    
    char ans = comput(net, inputs[e], layers_Size, layers, chars);
    //printf("\nOutputs %d :\n",e);
    correct += chars[e%ou_size] == ans;
    //printf("Expected %c / Ans : %c / %d\n",chars[e%ou_size],ans,chars[e%ou_size] == ans);
    
    
    for(int i = 0; i<layers_Size[layers-1]; i++)
    {
      if(net[layers-1][i].output > 0.5)
        printf("Ans : %c\n", chars[i]);
     // printf("Out[%d] = %f : %d\n", i, net[layers-1][i].output, net[layers-1][i].output > 0.5);
    }
    
  }

   
  // TESTS

  int correct2 = 0;
  int nb_test = 0;
  inputs = find_char(img_test, &nb_test);
  
  //printf("\nTests :\n");
  for(int t = 0; t<nb_test; t++)
  {
    char ans = comput(net, inputs[t], layers_Size, layers, chars);
    //printf("\nOutputs %d :\n",t);
    //printf("Ans : %c\n",ans);
    correct2 += chars[t%ou_size] == ans;
    //printf("Expected %c / Ans : %c / %d\n",chars[t%ou_size],ans,chars[t%ou_size] == ans);
  }
  
  printf("\n");
  printf("Ex : %d / %d = %f\n",correct,nb_ex, ((double)correct/(double)nb_ex)*100);
  printf("Test : %d / %d = %f\n",correct2,nb_test, ((double)correct2/(double)nb_test)*100);
  return 0;
 }
 */
