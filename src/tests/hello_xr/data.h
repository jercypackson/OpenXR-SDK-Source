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

std::vector<Iris> data = {
    {{-1.00f, 1.60f, -2.55f, -1.10f}, setosa},     {{-1.20f, 1.10f, -2.55f, -1.10f}, setosa},
    {{-1.40f, 1.30f, -2.65f, -1.10f}, setosa},     {{-1.50f, 1.20f, -2.45f, -1.10f}, setosa},
    {{-1.10f, 1.70f, -2.55f, -1.10f}, setosa},     {{-0.70f, 2.00f, -2.25f, -0.90f}, setosa},
    {{-1.50f, 1.50f, -2.55f, -1.00f}, setosa},     {{-1.10f, 1.50f, -2.45f, -1.10f}, setosa},
    {{-1.70f, 1.00f, -2.55f, -1.10f}, setosa},     {{-1.20f, 1.20f, -2.45f, -1.20f}, setosa},
    {{-0.70f, 1.80f, -2.45f, -1.10f}, setosa},     {{-1.30f, 1.50f, -2.35f, -1.10f}, setosa},
    {{-1.30f, 1.10f, -2.55f, -1.20f}, setosa},     {{-1.80f, 1.10f, -2.85f, -1.20f}, setosa},
    {{-0.30f, 2.10f, -2.75f, -1.10f}, setosa},     {{-0.40f, 2.50f, -2.45f, -0.90f}, setosa},
    {{-0.70f, 2.00f, -2.65f, -0.90f}, setosa},     {{-1.00f, 1.60f, -2.55f, -1.00f}, setosa},
    {{-0.40f, 1.90f, -2.25f, -1.00f}, setosa},     {{-1.00f, 1.90f, -2.45f, -1.00f}, setosa},
    {{-0.70f, 1.50f, -2.25f, -1.10f}, setosa},     {{-1.00f, 1.80f, -2.45f, -0.90f}, setosa},
    {{-1.50f, 1.70f, -2.95f, -1.10f}, setosa},     {{-1.00f, 1.40f, -2.25f, -0.80f}, setosa},
    {{-1.30f, 1.50f, -2.05f, -1.10f}, setosa},     {{-1.10f, 1.10f, -2.35f, -1.10f}, setosa},
    {{-1.10f, 1.50f, -2.35f, -0.90f}, setosa},     {{-0.90f, 1.60f, -2.45f, -1.10f}, setosa},
    {{-0.90f, 1.50f, -2.55f, -1.10f}, setosa},     {{-1.40f, 1.30f, -2.35f, -1.10f}, setosa},
    {{-1.30f, 1.20f, -2.35f, -1.10f}, setosa},     {{-0.70f, 1.50f, -2.45f, -0.90f}, setosa},
    {{-0.90f, 2.20f, -2.45f, -1.20f}, setosa},     {{-0.60f, 2.30f, -2.55f, -1.10f}, setosa},
    {{-1.20f, 1.20f, -2.45f, -1.20f}, setosa},     {{-1.10f, 1.30f, -2.75f, -1.10f}, setosa},
    {{-0.60f, 1.60f, -2.65f, -1.10f}, setosa},     {{-1.20f, 1.20f, -2.45f, -1.20f}, setosa},
    {{-1.70f, 1.10f, -2.65f, -1.10f}, setosa},     {{-1.00f, 1.50f, -2.45f, -1.10f}, setosa},
    {{-1.10f, 1.60f, -2.65f, -1.00f}, setosa},     {{-1.60f, 0.40f, -2.65f, -1.00f}, setosa},
    {{-1.70f, 1.30f, -2.65f, -1.10f}, setosa},     {{-1.10f, 1.60f, -2.35f, -0.70f}, setosa},
    {{-1.00f, 1.90f, -2.05f, -0.90f}, setosa},     {{-1.30f, 1.10f, -2.55f, -1.00f}, setosa},
    {{-1.00f, 1.90f, -2.35f, -1.10f}, setosa},     {{-1.50f, 1.30f, -2.55f, -1.10f}, setosa},
    {{-0.80f, 1.80f, -2.45f, -1.10f}, setosa},     {{-1.10f, 1.40f, -2.55f, -1.10f}, setosa},
    {{0.90f, 1.30f, 0.75f, 0.10f}, versicolor},    {{0.30f, 1.30f, 0.55f, 0.20f}, versicolor},
    {{0.80f, 1.20f, 0.95f, 0.20f}, versicolor},    {{-0.60f, 0.40f, 0.05f, 0.00f}, versicolor},
    {{0.40f, 0.90f, 0.65f, 0.20f}, versicolor},    {{-0.40f, 0.90f, 0.55f, 0.00f}, versicolor},
    {{0.20f, 1.40f, 0.75f, 0.30f}, versicolor},    {{-1.20f, 0.50f, -0.65f, -0.30f}, versicolor},
    {{0.50f, 1.00f, 0.65f, 0.00f}, versicolor},    {{-0.90f, 0.80f, -0.05f, 0.10f}, versicolor},
    {{-1.10f, 0.10f, -0.45f, -0.30f}, versicolor}, {{-0.20f, 1.10f, 0.25f, 0.20f}, versicolor},
    {{-0.10f, 0.30f, 0.05f, -0.30f}, versicolor},  {{0.00f, 1.00f, 0.75f, 0.10f}, versicolor},
    {{-0.50f, 1.00f, -0.35f, 0.00f}, versicolor},  {{0.60f, 1.20f, 0.45f, 0.10f}, versicolor},
    {{-0.50f, 1.10f, 0.55f, 0.20f}, versicolor},   {{-0.30f, 0.80f, 0.15f, -0.30f}, versicolor},
    {{0.10f, 0.30f, 0.55f, 0.20f}, versicolor},    {{-0.50f, 0.60f, -0.05f, -0.20f}, versicolor},
    {{-0.20f, 1.30f, 0.85f, 0.50f}, versicolor},   {{0.00f, 0.90f, 0.05f, 0.00f}, versicolor},
    {{0.20f, 0.60f, 0.95f, 0.20f}, versicolor},    {{0.00f, 0.90f, 0.75f, -0.10f}, versicolor},
    {{0.30f, 1.00f, 0.35f, 0.00f}, versicolor},    {{0.50f, 1.10f, 0.45f, 0.10f}, versicolor},
    {{0.70f, 0.90f, 0.85f, 0.10f}, versicolor},    {{0.60f, 1.10f, 1.05f, 0.40f}, versicolor},
    {{-0.10f, 1.00f, 0.55f, 0.20f}, versicolor},   {{-0.40f, 0.70f, -0.45f, -0.30f}, versicolor},
    {{-0.60f, 0.50f, -0.15f, -0.20f}, versicolor}, {{-0.60f, 0.50f, -0.25f, -0.30f}, versicolor},
    {{-0.30f, 0.80f, -0.05f, -0.10f}, versicolor}, {{-0.10f, 0.80f, 1.15f, 0.30f}, versicolor},
    {{-0.70f, 1.10f, 0.55f, 0.20f}, versicolor},   {{-0.10f, 1.50f, 0.55f, 0.30f}, versicolor},
    {{0.60f, 1.20f, 0.75f, 0.20f}, versicolor},    {{0.20f, 0.40f, 0.45f, 0.00f}, versicolor},
    {{-0.50f, 1.10f, 0.15f, 0.00f}, versicolor},   {{-0.60f, 0.60f, 0.05f, 0.00f}, versicolor},
    {{-0.60f, 0.70f, 0.45f, -0.10f}, versicolor},  {{0.00f, 1.10f, 0.65f, 0.10f}, versicolor},
    {{-0.30f, 0.70f, 0.05f, -0.10f}, versicolor},  {{-1.10f, 0.40f, -0.65f, -0.30f}, versicolor},
    {{-0.50f, 0.80f, 0.25f, 0.00f}, versicolor},   {{-0.40f, 1.10f, 0.25f, -0.10f}, versicolor},
    {{-0.40f, 1.00f, 0.25f, 0.00f}, versicolor},   {{0.10f, 1.00f, 0.35f, 0.00f}, versicolor},
    {{-1.00f, 0.60f, -0.95f, -0.20f}, versicolor}, {{-0.40f, 0.90f, 0.15f, 0.00f}, versicolor},
    {{0.20f, 1.40f, 2.05f, 1.20f}, virginica},     {{-0.30f, 0.80f, 1.15f, 0.60f}, virginica},
    {{1.00f, 1.10f, 1.95f, 0.80f}, virginica},     {{0.20f, 1.00f, 1.65f, 0.50f}, virginica},
    {{0.40f, 1.10f, 1.85f, 0.90f}, virginica},     {{1.50f, 1.10f, 2.65f, 0.80f}, virginica},
    {{-1.20f, 0.60f, 0.55f, 0.40f}, virginica},    {{1.20f, 1.00f, 2.35f, 0.50f}, virginica},
    {{0.60f, 0.60f, 1.85f, 0.50f}, virginica},     {{1.10f, 1.70f, 2.15f, 1.20f}, virginica},
    {{0.40f, 1.30f, 1.15f, 0.70f}, virginica},     {{0.30f, 0.80f, 1.35f, 0.60f}, virginica},
    {{0.70f, 1.10f, 1.55f, 0.80f}, virginica},     {{-0.40f, 0.60f, 1.05f, 0.70f}, virginica},
    {{-0.30f, 0.90f, 1.15f, 1.10f}, virginica},    {{0.30f, 1.30f, 1.35f, 1.00f}, virginica},
    {{0.40f, 1.10f, 1.55f, 0.50f}, virginica},     {{1.60f, 1.90f, 2.75f, 0.90f}, virginica},
    {{1.60f, 0.70f, 2.95f, 1.00f}, virginica},     {{-0.10f, 0.30f, 1.05f, 0.20f}, virginica},
    {{0.80f, 1.30f, 1.75f, 1.00f}, virginica},     {{-0.50f, 0.90f, 0.95f, 0.70f}, virginica},
    {{1.60f, 0.90f, 2.75f, 0.70f}, virginica},     {{0.20f, 0.80f, 0.95f, 0.50f}, virginica},
    {{0.60f, 1.40f, 1.75f, 0.80f}, virginica},     {{1.10f, 1.30f, 2.05f, 0.50f}, virginica},
    {{0.10f, 0.90f, 0.85f, 0.50f}, virginica},     {{0.00f, 1.10f, 0.95f, 0.50f}, virginica},
    {{0.30f, 0.90f, 1.65f, 0.80f}, virginica},     {{1.10f, 1.10f, 1.85f, 0.30f}, virginica},
    {{1.30f, 0.90f, 2.15f, 0.60f}, virginica},     {{1.80f, 1.90f, 2.45f, 0.70f}, virginica},
    {{0.30f, 0.90f, 1.65f, 0.90f}, virginica},     {{0.20f, 0.90f, 1.15f, 0.20f}, virginica},
    {{0.00f, 0.70f, 1.65f, 0.10f}, virginica},     {{1.60f, 1.10f, 2.15f, 1.00f}, virginica},
    {{0.20f, 1.50f, 1.65f, 1.10f}, virginica},     {{0.30f, 1.20f, 1.55f, 0.50f}, virginica},
    {{-0.10f, 1.10f, 0.85f, 0.50f}, virginica},    {{0.80f, 1.20f, 1.45f, 0.80f}, virginica},
    {{0.60f, 1.20f, 1.65f, 1.10f}, virginica},     {{0.80f, 1.20f, 1.15f, 1.00f}, virginica},
    {{-0.30f, 0.80f, 1.15f, 0.60f}, virginica},    {{0.70f, 1.30f, 1.95f, 1.00f}, virginica},
    {{0.60f, 1.40f, 1.75f, 1.20f}, virginica},     {{0.60f, 1.10f, 1.25f, 1.00f}, virginica},
    {{0.20f, 0.60f, 1.05f, 0.60f}, virginica},     {{0.40f, 1.10f, 1.25f, 0.70f}, virginica},
    {{0.10f, 1.50f, 1.45f, 1.00f}, virginica},     {{-0.20f, 1.10f, 1.15f, 0.50f}, virginica},

};

}  // namespace Geometry
