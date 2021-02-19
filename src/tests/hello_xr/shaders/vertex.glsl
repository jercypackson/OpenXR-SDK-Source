#version 410

in vec4 VertexPos;
in vec3 VertexColor;


out VertexData {
    vec3 PSVertexColor;
    flat int vertID;
} vert;

uniform mat4 ModelViewProjection;
uniform float proj5d[25];

// rotation
uniform float XWRot[25];
uniform float YWRot[25];
uniform float ZWRot[25];

uniform float gms_base[25];


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

    float view4d[25] = float[25](
        1, 0, 0, 0, 0,
        0, 1, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, -1, 0,
        0, 0, 0, 3, 1);


    float[] v5 = float[5](VertexPos.x, VertexPos.y, VertexPos.z, VertexPos.w, 1.0);


    v5 = mult(ZWRot, v5);
    v5 = mult(XWRot, v5);
    v5 = mult(YWRot, v5);

    //float[] r = mult(gms_base, v5);

    float[] view = mult(view4d, v5);
    float[] projected = mult(proj5d, view);


    vec3 pos = vec3(projected[0], projected[1], projected[2]) / projected[4];

    pos += vec3(0, 0.5, 0); //move off the floor
    //vec3 pos = VertexPos.xyz;
    gl_Position = ModelViewProjection * vec4(pos, 1.0);
    vert.PSVertexColor = VertexColor;
    vert.vertID = gl_VertexID;
}
