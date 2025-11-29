#include "predict.h"
#include "model_weights.h"

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
