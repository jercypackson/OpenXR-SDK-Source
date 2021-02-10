#pragma once

#include <array>
#include <cmath>

// taken from https://github.com/aleksandr-amirkhanov/ManyLands/blob/5565d9013b54a501544c79fb260ccbe0a1cfb31c/src/Matrix_lib.h#L189

class Matrix_lib {
   public:
    static std::array<float, 25> getXWRotationMatrix(float angle) {

        std::array<float, 25> rotation{};

        rotation[0] = std::cos(angle);
        rotation[1] = 0;
        rotation[2] = 0;
        rotation[3] = std::sin(angle);
        rotation[4] = 0;

        rotation[5] = 0;
        rotation[6] = 1;
        rotation[7] = 0;
        rotation[8] = 0;
        rotation[9] = 0;

        rotation[10] = 0;
        rotation[11] = 0;
        rotation[12] = 1;
        rotation[13] = 0;
        rotation[14] = 0;

        rotation[15] = -std::sin(angle);
        rotation[16] = 0;
        rotation[17] = 0;
        rotation[18] = std::cos(angle);
        rotation[19] = 0;

        rotation[20] = 0;
        rotation[21] = 0;
        rotation[22] = 0;
        rotation[23] = 0;
        rotation[24] = 1;

        return rotation;
    }

    static std::array<float, 25> getYWRotationMatrix(float angle) {
        std::array<float, 25> rotation{};

        rotation[0] = 1;
        rotation[1] = 0;
        rotation[2] = 0;
        rotation[3] = 0;
        rotation[4] = 0;

        rotation[5] = 0;
        rotation[6] = std::cos(angle);
        rotation[7] = 0;
        rotation[8] = -std::sin(angle);
        rotation[9] = 0;

        rotation[10] = 0;
        rotation[11] = 0;
        rotation[12] = 1;
        rotation[13] = 0;
        rotation[14] = 0;

        rotation[15] = 0;
        rotation[16] = std::sin(angle);
        rotation[17] = 0;
        rotation[18] = std::cos(angle);
        rotation[19] = 0;

        rotation[20] = 0;
        rotation[21] = 0;
        rotation[22] = 0;
        rotation[23] = 0;
        rotation[24] = 1;

        return rotation;
    }

    static std::array<float, 25> getZWRotationMatrix(float angle) {
        std::array<float, 25> rotation{};

        rotation[0] = 1;
        rotation[1] = 0;
        rotation[2] = 0;
        rotation[3] = 0;
        rotation[4] = 0;

        rotation[5] = 0;
        rotation[6] = 1;
        rotation[7] = 0;
        rotation[8] = 0;
        rotation[9] = 0;

        rotation[10] = 0;
        rotation[11] = 0;
        rotation[12] = std::cos(angle);
        rotation[13] = -std::sin(angle);
        rotation[14] = 0;

        rotation[15] = 0;
        rotation[16] = 0;
        rotation[17] = std::sin(angle);
        rotation[18] = std::cos(angle);
        rotation[19] = 0;

        rotation[20] = 0;
        rotation[21] = 0;
        rotation[22] = 0;
        rotation[23] = 0;
        rotation[24] = 1;

        return rotation;
    }
};
