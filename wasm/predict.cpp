#include <iostream>
#include <cmath>
#include <fstream>
#include "model_weights.h"

inline float leaky_relu(float x, float negative_slope = LEAKY_RELU_NEGATIVE_SLOPE) {
    return x > 0.0f ? x : x * negative_slope;
}

void forward(const float* input, float* output) {
    // Layer 1 - compiler can auto-vectorize with proper alignment
    alignas(64) float hidden1[HIDDEN1_DIM];
    for (int i = 0; i < HIDDEN1_DIM; ++i) {
        float sum = LAYER1_BIAS[i];
        for (int j = 0; j < INPUT_DIM; ++j) {
            sum += LAYER1_WEIGHT[i][j] * input[j];
        }
        hidden1[i] = leaky_relu(sum);
    }

    // Layer 2
    alignas(64) float hidden2[HIDDEN2_DIM];
    for (int i = 0; i < HIDDEN2_DIM; ++i) {
        float sum = LAYER2_BIAS[i];
        for (int j = 0; j < HIDDEN1_DIM; ++j) {
            sum += LAYER2_WEIGHT[i][j] * hidden1[j];
        }
        hidden2[i] = leaky_relu(sum);
    }

    // Layer 3 (output)
    for (int i = 0; i < OUTPUT_DIM; ++i) {
        float sum = LAYER3_BIAS[i];
        for (int j = 0; j < HIDDEN2_DIM; ++j) {
            sum += LAYER3_WEIGHT[i][j] * hidden2[j];
        }
        output[i] = sum;
    }
}

int main() {
    alignas(64) float input[INPUT_DIM];

    std::ifstream input_file("example_data.txt");

    for (int i = 0; i < INPUT_DIM; ++i) {
        input_file >> input[i];
    }

    alignas(64) float output[OUTPUT_DIM];

    forward(input, output);

    std::size_t max_index = 0;
    for (std::size_t i = 1; i < OUTPUT_DIM; ++i) {
        if (output[i] > output[max_index]) {
            max_index = i;
        }
    }

    std::cout << "Predicted class: " << CLASS_NAMES[max_index] << std::endl;

    return 0;
}