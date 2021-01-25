#version 410

in vec4 VertexPos;
in vec3 VertexColor;

out vec3 PSVertexColor;

uniform mat4 ModelViewProjection;

struct vec5 {
    float a;
    float b;
    float c;
    float d;
    float e;
};

float multiply(vec5 r, vec5 c) {
    float result = 0;
    result += r.a * c.a;
    result += r.b * c.b;
    result += r.c * c.c;
    result += r.d * c.d;
    result += r.e * c.e;
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

    gl_Position = ModelViewProjection * vec4(VertexPos.xyz, 1.0);
    PSVertexColor = VertexColor;
}
