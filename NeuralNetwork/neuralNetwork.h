#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"SDL/SDL_image.h"
#include"perfectImage.h"
#include<err.h>

struct neuron
{
    float *w;
    float output;
    float error;
};

struct neuron **new_network(int layers, int *layers_Size);
float logistic(float x);
float derivative(float x);
void init_weights(struct neuron **n, int *layers_Size, int layers);
void init_inputs(struct neuron **n, int *example, int inputs);
void feedforward(struct neuron **n, int *layers_Size, int layers);
float final_error(struct neuron **n, int **example,int *layers_Size,int layers);
void back_prop(struct neuron **n, int *layers_Size, int layers);
void weight_adjust(struct neuron **n, int *layers_Size, int layers);
float calculate(struct neuron **n, int **example, int *layers_Size, int layers);
void learn(struct neuron **n, int ***example, int *layers_Size, int layers, 
           int nb_ex);
void display_weights(struct neuron **n, int *layers_Size, int layers);
void display_outputs(struct neuron **n, int *layers_Size, int layers);

void get_inputs(SDL_Surface *img, int *inputs);
void save(struct neuron **n, int *layers_Size, int layers);
void load(struct neuron **n, int *layers_Size, int layers);
void writeEx();
void writeNewEx(int *e, int ans, int *layers_Size, int layers);
int*** readEx(int nb_ex, int *layers_Size, int layers);

#endif
