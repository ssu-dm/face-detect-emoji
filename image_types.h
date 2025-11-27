#pragma once

#include <vector>
#include <cstdint>

struct Point {
    double x;
    double y;
};

struct AffineTransform {
    double m00, m01, m02;
    double m10, m11, m12;

    bool operator==(const AffineTransform& other) const {
        return m00 == other.m00 && m01 == other.m01 && m02 == other.m02 &&
               m10 == other.m10 && m11 == other.m11 && m12 == other.m12;
    }
};

struct Image {
    int width;
    int height;
    int channels;
    std::vector<uint8_t> data;

    Image() : width(0), height(0), channels(0) {}
    Image(int w, int h, int c)
        : width(w), height(h), channels(c), data(w * h * c, 0) {}

    inline uint8_t getPixelSafe(int x, int y, int c) const {
        if (x < 0 || x >= width || y < 0 || y >= height || c < 0 || c >= channels) {
            return 0;
        }
        return data[(y * width + x) * channels + c];
    }
};
