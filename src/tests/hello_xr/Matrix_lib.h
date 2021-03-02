#pragma once

#include <array>
#include <cmath>
#include <xr_linear.h>

// taken from https://github.com/aleksandr-amirkhanov/ManyLands/blob/5565d9013b54a501544c79fb260ccbe0a1cfb31c/src/Matrix_lib.h#L189

class Matrix_lib {
   public:
    static XrMatrix4x4f getXWRotationMatrix(float angle) {

        XrMatrix4x4f rotation{};

        rotation.m[0] = std::cos(angle);
        rotation.m[1] = 0;
        rotation.m[2] = 0;
        rotation.m[3] = std::sin(angle);
        
        rotation.m[4] = 0;
        rotation.m[5] = 1;
        rotation.m[6] = 0;
        rotation.m[7] = 0;
        
        rotation.m[8] = 0;
        rotation.m[9] = 0;
        rotation.m[10] = 1;
        rotation.m[11] = 0;
        
        rotation.m[12] = -std::sin(angle);
        rotation.m[13] = 0;
        rotation.m[14] = 0;
        rotation.m[15] = std::cos(angle);

        return rotation;
    }

    static XrMatrix4x4f getYWRotationMatrix(float angle) {
        XrMatrix4x4f rotation{};

        rotation.m[0] = 1;
        rotation.m[1] = 0;
        rotation.m[2] = 0;
        rotation.m[3] = 0;

        rotation.m[4] = 0;
        rotation.m[5] = std::cos(angle);
        rotation.m[6] = 0;
        rotation.m[7] = -std::sin(angle);

        rotation.m[8] = 0;
        rotation.m[9] = 0;
        rotation.m[10] = 1;
        rotation.m[11] = 0;

        rotation.m[12] = 0;
        rotation.m[13] = std::sin(angle);
        rotation.m[14] = 0;
        rotation.m[15] = std::cos(angle);

        return rotation;
    }

    static XrMatrix4x4f getZWRotationMatrix(float angle) {
        XrMatrix4x4f rotation{};

        rotation.m[0] = 1;
        rotation.m[1] = 0;
        rotation.m[2] = 0;
        rotation.m[3] = 0;

        rotation.m[4] = 0;
        rotation.m[5] = 1;
        rotation.m[6] = 0;
        rotation.m[7] = 0;

        rotation.m[8] = 0;
        rotation.m[9] = 0;
        rotation.m[10] = std::cos(angle);
        rotation.m[11] = -std::sin(angle);

        rotation.m[12] = 0;
        rotation.m[13] = 0;
        rotation.m[14] = std::sin(angle);
        rotation.m[15] = std::cos(angle);

        return rotation;
    }
};
