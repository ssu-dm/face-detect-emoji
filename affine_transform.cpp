#include <limits>
#include <numeric>

#include "image_types.h"
#include "affine_transform.h"

double meanX(const std::vector<Point>& pts) {
    if (pts.empty()) return 0.0;
    double sum = std::accumulate(
        pts.begin(), pts.end(), 0.0,
        [](double acc, const Point& p) {
            return acc + p.x;
        }
    );
    return sum / static_cast<double>(pts.size());
}

double meanY(const std::vector<Point>& pts) {
    if (pts.empty()) return 0.0;
    double sum = std::accumulate(
        pts.begin(), pts.end(), 0.0,
        [](double acc, const Point& p) {
            return acc + p.y;
        }
    );
    return sum / static_cast<double>(pts.size());
}

bool estimateAffinePartial2D(
    const std::vector<Point>& src_points,
    const std::vector<Point>& dst_points,
    AffineTransform& outM
) {
    int n = src_points.size();

    double src_cx = meanX(src_points);
    double src_cy = meanY(src_points);
    double dst_cx = meanX(dst_points);
    double dst_cy = meanY(dst_points);

    double num_a = 0.0;
    double num_b = 0.0;
    double den = 0.0;

    for (int i = 0; i < n; i++) {
        double sx = src_points[i].x - src_cx;
        double sy = src_points[i].y - src_cy;
        double dx = dst_points[i].x - dst_cx;
        double dy = dst_points[i].y - dst_cy;

        num_a += sx * dx + sy * dy; // cos 선분 (vector 내적)
        num_b += sx * dy - sy * dx; // sin 선분 (vector 외적)
        den += sx * sx + sy * sy;
    }

    if (den == 0.0) {
        return false;
    }

    double a = num_a / den;
    double b = num_b / den;

    double tx = dst_cx - (a * src_cx - b * src_cy);
    double ty = dst_cy - (b * src_cx + a * src_cy);

    outM.m00 = a;  
    outM.m01 = -b; 
    outM.m02 = tx;
    outM.m10 = b;
    outM.m11 = a;
    outM.m12 = ty;

    return true;
}