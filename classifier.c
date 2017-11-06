#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>


/*
* dimension: number of features of the vector
* vectors: with a double value for each feature
* size: number of vectors
* k: number of clusters as denoted by k-means
*/
extern int* initialize_cluster_labels(double** , int,  int );
extern int* initialize_centroids(double**, int, int );
extern void assign_clusters(int, double**, int*, int*, int, int);
extern bool fix_centroids(int, double**, int*, int*, int, int);
extern void print_clusters(int*, int);
extern double get_cosine_distance(int, double*, double*);

void kmeans(int dimension, double **vectors, int size, int k, int max_iterations)
{
     if (vectors == NULL || size == 0 || k == 0 || dimension  == 0) return;

     int* cluster_labels = initialize_cluster_labels(vectors, size, k);
     int* centroids = initialize_centroids(vectors, size, k);
     bool centroids_updated = true;
     int count = 0;
     while(centroids_updated)
     {
         count++;
         if (count > max_iterations) break;
         assign_clusters(dimension, vectors, centroids, cluster_labels, size, k);
         centroids_updated = fix_centroids(dimension, vectors, centroids, cluster_labels, size, k);
     }

     print_clusters(cluster_labels, size);
     free(centroids);
     free(cluster_labels);
     return;
}

int* initialize_cluster_labels(double** vectors, int size, int k)
{
    int* cluster_labels = NULL;
    if (size == 0 || k == 0) return cluster_labels;
    cluster_labels = (int*) malloc(size * sizeof(int));
    if (cluster_labels == NULL){printf("Require more memory"); exit(1);}
    for (int i = 0; i < size; i++) cluster_labels[i] = rand() % k;
    return cluster_labels;
}

int* initialize_centroids(double** vectors, int size, int k)
{
    if (vectors == NULL || *vectors == NULL || k == 0) return NULL;
    srand(time(NULL));
    int* centroids = (int*) malloc(k * sizeof(int));
    if (centroids  == NULL) { printf("Require more memory"); exit(1);}
    for (int i = 0; i <k; i++)
    {
        centroids[i] = rand() % size;
    }
    return centroids;
}

void assign_clusters(int dimension, double** vectors, int* centroids, int* cluster_labels, int size, int k)
{
    for (int m = 0; m < size; m++)
    {
        double minimum = get_cosine_distance(dimension, vectors[centroids[cluster_labels[m]]], vectors[m]);
        for (int i = 0; i < k; i++)
        {
             double* centroid = vectors[centroids[i]];
             double distance = get_cosine_distance(dimension, centroid, vectors[m]);
             if (distance < minimum)
             {
                 cluster_labels[m] = i;
             }
        }
    }
}

bool fix_centroids(int dimension, double** vectors, int* centroids, int* cluster_labels, int size, int k)
{
    bool centroids_updated = false;
    int* new_centroids = (int*) malloc(k * sizeof(int));
    if (new_centroids == NULL) { printf("Require more memory"); exit(1);}
    for (int i = 0; i < k; i++)
    {
        int label = i;
        double minimum = 0;
        double* centroid = vectors[centroids[label]];
        for (int j = 0; j < size; j++)
        {
             if (j != centroids[label] && cluster_labels[j] == label)
             {
                double cosd = get_cosine_distance(dimension, centroid, vectors[j]);
                minimum += cosd * cosd;
             }
        }
        for (int j = 0; j < size; j++)
        {
             if (cluster_labels[j] != label) continue;
             double distance = 0;
             for (int m = 0; m < size; m++)
             {
                if (cluster_labels[m] != label) continue;
                if (m == j) continue;
                double cosd = get_cosine_distance(dimension, vectors[m], vectors[j]);
                distance += cosd * cosd;
             }
             if (distance < minimum)
             {
                 minimum = distance;
                 new_centroids[label] = j;
                 centroids_updated = true;
             }
        }
    }
    if (centroids_updated)
    {
        for (int j = 0; j < k; j++)
        {
            centroids[j] = new_centroids[j];
        }
    }
    free(new_centroids);
    return centroids_updated;
}

void print_clusters(int* cluster_labels, int size)
{
    if (cluster_labels == NULL || size == 0) return;
    for (int i = 0; i < size; i++)
    {
         printf("%d", cluster_labels[i]);
    }
}

double get_cosine_distance(int dimension, double* vec1, double* vec2)
{
    double distance = 0;
    double magnitude = 0;
    int i, j;
    for (i = 0; i < dimension; i++) distance += vec1[i] * vec2[i];
    for (i = 0; i < dimension; i++) magnitude += vec1[i] * vec1[i];
    magnitude = sqrt(magnitude);
    distance /= magnitude;
    magnitude = 0;
    for (i = 0; i < dimension; i++) magnitude += vec2[i] * vec2[i];
    magnitude = sqrt(magnitude);
    distance /= magnitude;
    return distance;
}

