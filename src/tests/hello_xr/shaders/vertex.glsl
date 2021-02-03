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

void main() {

    /*
    0 5 10 15 20
    1 6 11 16 21
    2 7 12 17 22
    3 8 13 18 23
    4 9 14 19 24
    */

    float projected[5];
    
    for (int i = 0; i < 5; i++) {
        projected[i] = dot(
            proj5d[0 + i], proj5d[5 + i], proj5d[10 + i], proj5d[15 + i], proj5d[20 + i], 
            VertexPos.x, VertexPos.y, VertexPos.z, VertexPos.w, 1.0
        );
    }

    vec3 pos = vec3(projected[0], projected[2], projected[3]) / projected[4];
    gl_Position = ModelViewProjection * vec4(pos, 1.0);
    PSVertexColor = VertexColor;
}
