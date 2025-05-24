#pragma once

#include <iostream>
#include <string>
#include <math.h>
#include <numbers>

namespace Utils::Arrays {

template <typename T, std::size_t N>
std::size_t getArrLengthStatic(T (&array)[N]) {
  return N;
}

// // Array allocation and delocation; but only work for primitive types

template <typename T>
void allocate3DArray(T ****arr, int xCount, int yCount, int zCount) {
  *arr = (T***) malloc(xCount * sizeof(T**));
  if (*arr == NULL) {
    perror("Failed to allocate memory for arr");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < xCount; i++) {
    (*arr)[i] = (T**) malloc(yCount * sizeof(T*));
    if ((*arr)[i] == NULL) {
      perror("Failed to allocate memory for arr[i]");
      exit(EXIT_FAILURE);
    }

    for (int j = 0; j < yCount; j++) {
      (*arr)[i][j] = (T*) malloc(zCount * sizeof(T));
      if ((*arr)[i][j] == NULL) {
        perror("Failed to allocate memory for arr[i][j]");
        exit(EXIT_FAILURE);
      }
    }
  }
}

template <typename T>
void free3DArray(T ***arr, int xCount, int yCount) {
  for (int i = 0; i < xCount; i++) {
    for (int j = 0; j < yCount; j++) {
      free(arr[i][j]); // Free each array of elements
    }
    free(arr[i]); // Free each array of pointers
  }
  free(arr); // Free the array of pointers to pointers
}

template <typename T>
void allocate2DArray(T ***arr, int xCount, int yCount) {
  *arr = (T**) malloc(xCount * sizeof(T*));
  if (*arr == NULL) {
    perror("Failed to allocate memory for arr");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < xCount; i++) {
    (*arr)[i] = (T*) malloc(yCount * sizeof(T));
    if ((*arr)[i] == NULL) {
      perror("Failed to allocate memory for arr[i]");
      exit(EXIT_FAILURE);
    }
  }
}

template <typename T>
void free2DArray(T **arr, int xCount) {
  for (int i = 0; i < xCount; i++) {
    free(arr[i]); // Free each array of pointers
  }
  free(arr); // Free the array of pointers to pointers
}

template <typename T>
void allocate1DArray(T **arr, int count) {
  *arr = (T*) malloc(count * sizeof(T));
  if (*arr == NULL) {
    perror("Failed to allocate memory for arr");
    exit(EXIT_FAILURE);
  }
}

template <typename T>
void free1DArray(T *arr) {
  free(arr); // Free the array of pointers to pointers
}

}
