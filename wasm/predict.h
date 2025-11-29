#ifndef WASM_PREDICT_H
#define WASM_PREDICT_H

inline float leaky_relu(float x, float negative_slope = 0.01f) {
    return x > 0.0f ? x : x * negative_slope;
}

void forward(const float* input, float* output);

#endif  // WASM_PREDICT_H