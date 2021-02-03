#pragma once

#include "openxr/openxr.h"
#include <vector>

namespace Geometry {

struct Iris {
    XrVector4f Data;
    XrVector3f Color;
};

constexpr XrVector3f setosa{1, 0, 0};
constexpr XrVector3f versicolor{0, 1, 0};
constexpr XrVector3f virginica{0, 0, 1};

constexpr XrVector3f grey{0.5f, 0.5f, 0.5f};



std::vector<Iris> data = {
    {{5.1f, 3.5f, 1.4f, 0.2f}, setosa},     {{4.9f, 3.0f, 1.4f, 0.2f}, setosa},     {{4.7f, 3.2f, 1.3f, 0.2f}, setosa},
    {{4.6f, 3.1f, 1.5f, 0.2f}, setosa},     {{5.0f, 3.6f, 1.4f, 0.2f}, setosa},     {{5.4f, 3.9f, 1.7f, 0.4f}, setosa},
    {{4.6f, 3.4f, 1.4f, 0.3f}, setosa},     {{5.0f, 3.4f, 1.5f, 0.2f}, setosa},     {{4.4f, 2.9f, 1.4f, 0.2f}, setosa},
    {{4.9f, 3.1f, 1.5f, 0.1f}, setosa},     {{5.4f, 3.7f, 1.5f, 0.2f}, setosa},     {{4.8f, 3.4f, 1.6f, 0.2f}, setosa},
    {{4.8f, 3.0f, 1.4f, 0.1f}, setosa},     {{4.3f, 3.0f, 1.1f, 0.1f}, setosa},     {{5.8f, 4.0f, 1.2f, 0.2f}, setosa},
    {{5.7f, 4.4f, 1.5f, 0.4f}, setosa},     {{5.4f, 3.9f, 1.3f, 0.4f}, setosa},     {{5.1f, 3.5f, 1.4f, 0.3f}, setosa},
    {{5.7f, 3.8f, 1.7f, 0.3f}, setosa},     {{5.1f, 3.8f, 1.5f, 0.3f}, setosa},     {{5.4f, 3.4f, 1.7f, 0.2f}, setosa},
    {{5.1f, 3.7f, 1.5f, 0.4f}, setosa},     {{4.6f, 3.6f, 1.0f, 0.2f}, setosa},     {{5.1f, 3.3f, 1.7f, 0.5f}, setosa},
    {{4.8f, 3.4f, 1.9f, 0.2f}, setosa},     {{5.0f, 3.0f, 1.6f, 0.2f}, setosa},     {{5.0f, 3.4f, 1.6f, 0.4f}, setosa},
    {{5.2f, 3.5f, 1.5f, 0.2f}, setosa},     {{5.2f, 3.4f, 1.4f, 0.2f}, setosa},     {{4.7f, 3.2f, 1.6f, 0.2f}, setosa},
    {{4.8f, 3.1f, 1.6f, 0.2f}, setosa},     {{5.4f, 3.4f, 1.5f, 0.4f}, setosa},     {{5.2f, 4.1f, 1.5f, 0.1f}, setosa},
    {{5.5f, 4.2f, 1.4f, 0.2f}, setosa},     {{4.9f, 3.1f, 1.5f, 0.1f}, setosa},     {{5.0f, 3.2f, 1.2f, 0.2f}, setosa},
    {{5.5f, 3.5f, 1.3f, 0.2f}, setosa},     {{4.9f, 3.1f, 1.5f, 0.1f}, setosa},     {{4.4f, 3.0f, 1.3f, 0.2f}, setosa},
    {{5.1f, 3.4f, 1.5f, 0.2f}, setosa},     {{5.0f, 3.5f, 1.3f, 0.3f}, setosa},     {{4.5f, 2.3f, 1.3f, 0.3f}, setosa},
    {{4.4f, 3.2f, 1.3f, 0.2f}, setosa},     {{5.0f, 3.5f, 1.6f, 0.6f}, setosa},     {{5.1f, 3.8f, 1.9f, 0.4f}, setosa},
    {{4.8f, 3.0f, 1.4f, 0.3f}, setosa},     {{5.1f, 3.8f, 1.6f, 0.2f}, setosa},     {{4.6f, 3.2f, 1.4f, 0.2f}, setosa},
    {{5.3f, 3.7f, 1.5f, 0.2f}, setosa},     {{5.0f, 3.3f, 1.4f, 0.2f}, setosa},     {{7.0f, 3.2f, 4.7f, 1.4f}, versicolor},
    {{6.4f, 3.2f, 4.5f, 1.5f}, versicolor}, {{6.9f, 3.1f, 4.9f, 1.5f}, versicolor}, {{5.5f, 2.3f, 4.0f, 1.3f}, versicolor},
    {{6.5f, 2.8f, 4.6f, 1.5f}, versicolor}, {{5.7f, 2.8f, 4.5f, 1.3f}, versicolor}, {{6.3f, 3.3f, 4.7f, 1.6f}, versicolor},
    {{4.9f, 2.4f, 3.3f, 1.0f}, versicolor}, {{6.6f, 2.9f, 4.6f, 1.3f}, versicolor}, {{5.2f, 2.7f, 3.9f, 1.4f}, versicolor},
    {{5.0f, 2.0f, 3.5f, 1.0f}, versicolor}, {{5.9f, 3.0f, 4.2f, 1.5f}, versicolor}, {{6.0f, 2.2f, 4.0f, 1.0f}, versicolor},
    {{6.1f, 2.9f, 4.7f, 1.4f}, versicolor}, {{5.6f, 2.9f, 3.6f, 1.3f}, versicolor}, {{6.7f, 3.1f, 4.4f, 1.4f}, versicolor},
    {{5.6f, 3.0f, 4.5f, 1.5f}, versicolor}, {{5.8f, 2.7f, 4.1f, 1.0f}, versicolor}, {{6.2f, 2.2f, 4.5f, 1.5f}, versicolor},
    {{5.6f, 2.5f, 3.9f, 1.1f}, versicolor}, {{5.9f, 3.2f, 4.8f, 1.8f}, versicolor}, {{6.1f, 2.8f, 4.0f, 1.3f}, versicolor},
    {{6.3f, 2.5f, 4.9f, 1.5f}, versicolor}, {{6.1f, 2.8f, 4.7f, 1.2f}, versicolor}, {{6.4f, 2.9f, 4.3f, 1.3f}, versicolor},
    {{6.6f, 3.0f, 4.4f, 1.4f}, versicolor}, {{6.8f, 2.8f, 4.8f, 1.4f}, versicolor}, {{6.7f, 3.0f, 5.0f, 1.7f}, versicolor},
    {{6.0f, 2.9f, 4.5f, 1.5f}, versicolor}, {{5.7f, 2.6f, 3.5f, 1.0f}, versicolor}, {{5.5f, 2.4f, 3.8f, 1.1f}, versicolor},
    {{5.5f, 2.4f, 3.7f, 1.0f}, versicolor}, {{5.8f, 2.7f, 3.9f, 1.2f}, versicolor}, {{6.0f, 2.7f, 5.1f, 1.6f}, versicolor},
    {{5.4f, 3.0f, 4.5f, 1.5f}, versicolor}, {{6.0f, 3.4f, 4.5f, 1.6f}, versicolor}, {{6.7f, 3.1f, 4.7f, 1.5f}, versicolor},
    {{6.3f, 2.3f, 4.4f, 1.3f}, versicolor}, {{5.6f, 3.0f, 4.1f, 1.3f}, versicolor}, {{5.5f, 2.5f, 4.0f, 1.3f}, versicolor},
    {{5.5f, 2.6f, 4.4f, 1.2f}, versicolor}, {{6.1f, 3.0f, 4.6f, 1.4f}, versicolor}, {{5.8f, 2.6f, 4.0f, 1.2f}, versicolor},
    {{5.0f, 2.3f, 3.3f, 1.0f}, versicolor}, {{5.6f, 2.7f, 4.2f, 1.3f}, versicolor}, {{5.7f, 3.0f, 4.2f, 1.2f}, versicolor},
    {{5.7f, 2.9f, 4.2f, 1.3f}, versicolor}, {{6.2f, 2.9f, 4.3f, 1.3f}, versicolor}, {{5.1f, 2.5f, 3.0f, 1.1f}, versicolor},
    {{5.7f, 2.8f, 4.1f, 1.3f}, versicolor}, {{6.3f, 3.3f, 6.0f, 2.5f}, virginica},  {{5.8f, 2.7f, 5.1f, 1.9f}, virginica},
    {{7.1f, 3.0f, 5.9f, 2.1f}, virginica},  {{6.3f, 2.9f, 5.6f, 1.8f}, virginica},  {{6.5f, 3.0f, 5.8f, 2.2f}, virginica},
    {{7.6f, 3.0f, 6.6f, 2.1f}, virginica},  {{4.9f, 2.5f, 4.5f, 1.7f}, virginica},  {{7.3f, 2.9f, 6.3f, 1.8f}, virginica},
    {{6.7f, 2.5f, 5.8f, 1.8f}, virginica},  {{7.2f, 3.6f, 6.1f, 2.5f}, virginica},  {{6.5f, 3.2f, 5.1f, 2.0f}, virginica},
    {{6.4f, 2.7f, 5.3f, 1.9f}, virginica},  {{6.8f, 3.0f, 5.5f, 2.1f}, virginica},  {{5.7f, 2.5f, 5.0f, 2.0f}, virginica},
    {{5.8f, 2.8f, 5.1f, 2.4f}, virginica},  {{6.4f, 3.2f, 5.3f, 2.3f}, virginica},  {{6.5f, 3.0f, 5.5f, 1.8f}, virginica},
    {{7.7f, 3.8f, 6.7f, 2.2f}, virginica},  {{7.7f, 2.6f, 6.9f, 2.3f}, virginica},  {{6.0f, 2.2f, 5.0f, 1.5f}, virginica},
    {{6.9f, 3.2f, 5.7f, 2.3f}, virginica},  {{5.6f, 2.8f, 4.9f, 2.0f}, virginica},  {{7.7f, 2.8f, 6.7f, 2.0f}, virginica},
    {{6.3f, 2.7f, 4.9f, 1.8f}, virginica},  {{6.7f, 3.3f, 5.7f, 2.1f}, virginica},  {{7.2f, 3.2f, 6.0f, 1.8f}, virginica},
    {{6.2f, 2.8f, 4.8f, 1.8f}, virginica},  {{6.1f, 3.0f, 4.9f, 1.8f}, virginica},  {{6.4f, 2.8f, 5.6f, 2.1f}, virginica},
    {{7.2f, 3.0f, 5.8f, 1.6f}, virginica},  {{7.4f, 2.8f, 6.1f, 1.9f}, virginica},  {{7.9f, 3.8f, 6.4f, 2.0f}, virginica},
    {{6.4f, 2.8f, 5.6f, 2.2f}, virginica},  {{6.3f, 2.8f, 5.1f, 1.5f}, virginica},  {{6.1f, 2.6f, 5.6f, 1.4f}, virginica},
    {{7.7f, 3.0f, 6.1f, 2.3f}, virginica},  {{6.3f, 3.4f, 5.6f, 2.4f}, virginica},  {{6.4f, 3.1f, 5.5f, 1.8f}, virginica},
    {{6.0f, 3.0f, 4.8f, 1.8f}, virginica},  {{6.9f, 3.1f, 5.4f, 2.1f}, virginica},  {{6.7f, 3.1f, 5.6f, 2.4f}, virginica},
    {{6.9f, 3.1f, 5.1f, 2.3f}, virginica},  {{5.8f, 2.7f, 5.1f, 1.9f}, virginica},  {{6.8f, 3.2f, 5.9f, 2.3f}, virginica},
    {{6.7f, 3.3f, 5.7f, 2.5f}, virginica},  {{6.7f, 3.0f, 5.2f, 2.3f}, virginica},  {{6.3f, 2.5f, 5.0f, 1.9f}, virginica},
    {{6.5f, 3.0f, 5.2f, 2.0f}, virginica},  {{6.2f, 3.4f, 5.4f, 2.3f}, virginica},  {{5.9f, 3.0f, 5.1f, 1.8f}, virginica}
};



float a[] = {4.3f, 2.0f, 1.0f, 0.1f};
float b[] = {7.9f, 4.4f, 6.9f, 2.5f};

#define PNT(p1,p2,p3,p4) {{p1[0], p2[1], p3[2], p4[3]}, grey}

std::vector<Iris> tess = {
    PNT(a,a,a,b),	PNT(a,a,a,a),
    PNT(a,a,b,a),	PNT(a,a,a,a),
    PNT(a,b,a,a),	PNT(a,a,a,a),
    PNT(b,a,a,a),	PNT(a,a,a,a),
    PNT(a,a,b,b),	PNT(a,a,a,b),
    PNT(a,b,a,b),	PNT(a,a,a,b),
    PNT(b,a,a,b),	PNT(a,a,a,b),
    PNT(a,a,b,b),	PNT(a,a,b,a),
    PNT(a,b,b,a),	PNT(a,a,b,a),
    PNT(b,a,b,a),	PNT(a,a,b,a),
    PNT(a,b,b,b),	PNT(a,a,b,b),
    PNT(b,a,b,b),	PNT(a,a,b,b),
    PNT(a,b,a,b),	PNT(a,b,a,a),
    PNT(a,b,b,a),	PNT(a,b,a,a),
    PNT(b,b,a,a),	PNT(a,b,a,a),
    PNT(a,b,b,b),	PNT(a,b,a,b),
    PNT(b,b,a,b),	PNT(a,b,a,b),
    PNT(a,b,b,b),	PNT(a,b,b,a),
    PNT(b,b,b,a),	PNT(a,b,b,a),
    PNT(b,b,b,b),	PNT(a,b,b,b),
    PNT(b,a,a,b),	PNT(b,a,a,a),
    PNT(b,a,b,a),	PNT(b,a,a,a),
    PNT(b,b,a,a),	PNT(b,a,a,a),
    PNT(b,a,b,b),	PNT(b,a,a,b),
    PNT(b,b,a,b),	PNT(b,a,a,b),
    PNT(b,a,b,b),	PNT(b,a,b,a),
    PNT(b,b,b,a),	PNT(b,a,b,a),
    PNT(b,b,b,b),	PNT(b,a,b,b),
    PNT(b,b,a,b),	PNT(b,b,a,a),
    PNT(b,b,b,a),	PNT(b,b,a,a),
    PNT(b,b,b,b),	PNT(b,b,a,b),
    PNT(b,b,b,b),	PNT(b,b,b,a),
};


}  // namespace Geometry
