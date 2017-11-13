#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <classifier.c>

extern int* initialize_cluster_labels(double** , int,  int );
extern int* initialize_centroids(double**, int, int );
extern void assign_clusters(int, double**, int*, int*, int, int);
extern bool fix_centroids(int, double**, int*, int*, int, int);
extern void print_clusters(int*, int);
extern double get_cosine_distance(int, double*, double*);

int main()
{
double** vectors = (double**) malloc(2* sizeof(double*));
vectors[0] = (double*) malloc(2 * sizeof(double));
vectors[1] = (double*) malloc(2 * sizeof(double));
vectors[0][0] = 1;
vectors[0][1] = 2;
vectors[1][0] = 3;
vectors[1][1] = 4;

int dimension = 2;
int size = 2;
int k = 2;

double distance = get_cosine_distance(dimension, vectors[0], vectors[1]);
if (fabs(distance-0.983870) > 0.1) printf("failed\n");
else printf("succeeded\n");
printf("%f\n", distance);

int* cluster_labels = initialize_cluster_labels(vectors, size, k);
printf("labels=%d,%d\n",cluster_labels[0], cluster_labels[1]);

int* centroids = initialize_centroids(vectors, size, k);
printf("centroids=%d,%d\n", centroids[0], centroids[1]);

bool fixed = fix_centroids(dimension, vectors, centroids, cluster_labels, size, k);
if (fixed) {
printf("fix_centroids=true\n");
} else {
printf("fix_centroids=false\n");
}

assign_clusters(dimension, vectors, centroids, cluster_labels, size, k);
print_clusters(cluster_labels, size);

free(centroids);
free(cluster_labels);
printf("\ndone\n");
}
/*
succeeded
0.983870
labels=1,0
centroids=0,1
fix_centroids=true
0, 1,
done
*/
