#version 410

in vec4 VertexPos;
in vec3 VertexColor;

out vec3 PSVertexColor;

uniform mat4 ModelViewProjection;
uniform float proj5d[25];
uniform int projIdx = 3; //which coordinate to project on [0;3]

struct vec5 {
    float a;
    float b;
    float c;
    float d;
    float e;
};

//float dot(float a0, float a1, float a2, float a3, float a4, float b[5]) {
//    return dot(a0, a1, a2, a3, a4, b[0], b[1], b[2], b[3], b[4]);
//}

float dot(float a0, float a1, float a2, float a3, float a4, float b0, float b1, float b2, float b3, float b4) {
    float result = 0;
    result += a0 * b0;
    result += a1 * b1;
    result += a2 * b2;
    result += a3 * b3;
    result += a4 * b4;
    return result;
}

float[5] mult(float mat55[25], float vec5[5]) {

    float ret[5];

    for (int i = 0; i < 5; i++) {
        ret[i] = dot(
            mat55[0 + i], mat55[5 + i], mat55[10 + i], mat55[15 + i], mat55[20 + i], 
            vec5[0],      vec5[1],      vec5[2],       vec5[3],       vec5[4]
        );
    }

    return ret;
}

void main() {

    /*
    0 5 10 15 20
    1 6 11 16 21
    2 7 12 17 22
    3 8 13 18 23
    4 9 14 19 24
    */

    float view4d[25];

    view4d[0] = 1;
    view4d[1] = 0;
    view4d[2] = 0;
    view4d[3] = 0;
    view4d[4] = 0;

    view4d[5] = 0;
    view4d[6] = 1;
    view4d[7] = 0;
    view4d[8] = 0;
    view4d[9] = 0;

    view4d[10] = 0;
    view4d[11] = 0;
    view4d[12] = 1;
    view4d[13] = 0;
    view4d[14] = 0;

    view4d[15] = 0;
    view4d[16] = 0;
    view4d[17] = 0;
    view4d[18] = -1;
    view4d[19] = 0;

    view4d[20] = 0;
    view4d[21] = 0;
    view4d[22] = 0;
    view4d[23] = 3;
    view4d[24] = 1;




    float[] view = mult(view4d, float[5](VertexPos.x, VertexPos.y, VertexPos.z, VertexPos.w, 1.0));
    float[] projected = mult(proj5d, view);


    vec3 pos = vec3(projected[0], projected[1], projected[2]) / projected[4];
    //vec3 pos = VertexPos.xyz;
    gl_Position = ModelViewProjection * vec4(pos, 1.0);
    PSVertexColor = VertexColor;
}
