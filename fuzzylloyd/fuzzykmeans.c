#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fuzzykmeans.h"

double dist2(double* v0, double* v1) {
  return sqrt(pow(v0[0] - v1[0], 2) + pow(v0[1] - v1[1],2));
}

double weight(double* vi, double* centers,int j,int k){
  double w = 0.0;
  double *pcenter = &centers[j];
  for (int l = 0; l <2* k; l+=2){
    double *pcenterl = &centers[l];
    w += pow(dist2(vi, pcenter),2)/pow(dist2(vi, pcenterl),2);
  }
  return pow(w, -1);
}

void fuzzykmeans(double* data, int n, double* centers, int k){
  double *centv = (double*) malloc(2*sizeof(double));
  double wsum = 0.0;
  double w = 0.0;
  centv[0] = 0.0;
  centv[1] = 0.0;
  for (int c = 0; c < 2*k; c +=2){
    for(int v = 0; v < 2*n; v +=2){
      double *pvec = &data[v];
      w = weight(pvec, centers, c, k);
      centv[0] += pow(w, 2) * pvec[0];
      centv[1] += pow(w, 2) * pvec[1];
      wsum += pow(w, 2);                                                                                
    }
    centv[0] /= wsum;
    centv[1] /= wsum;
    centers[c] = centv[0];
    centers[c+1] = centv[1];                                                                           
    centv[0] = 0.0;
    centv[1] = 0.0;
    wsum = 0.0;
  }
  free(centv);
}
