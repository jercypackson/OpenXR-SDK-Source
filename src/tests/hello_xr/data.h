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

constexpr XrVector3f color{0, 0.5, 1};


constexpr XrVector3f c0{0, 0, 0}    ;
constexpr XrVector3f c1{0.5,0,0}    ;
constexpr XrVector3f c2{1,0,0}      ;
constexpr XrVector3f c3{1,1,0}      ;
constexpr XrVector3f c4{0,1,0}      ;
constexpr XrVector3f c5{0,0.5,0}    ;
constexpr XrVector3f c6{0,1,1}      ;
constexpr XrVector3f c7{0,0,1}      ;
constexpr XrVector3f c8{1,0,1}      ;
constexpr XrVector3f c9{1, 1, 1}    ;

std::map<int, XrVector3f> colors {
    {0, XrVector3f{0.2670, 0.0049, 0.3294}},
    {1, XrVector3f{0.2812, 0.1575, 0.4704}},
    {2, XrVector3f{0.2437, 0.2906, 0.5381}},
    {3, XrVector3f{0.1906, 0.4071, 0.5561}},
    {4, XrVector3f{0.1471, 0.5130, 0.5570}},
    {5, XrVector3f{0.1196, 0.6173, 0.5368}},
    {6, XrVector3f{0.2080, 0.7187, 0.4729}},
    {7, XrVector3f{0.4249, 0.8067, 0.3501}},
    {8, XrVector3f{0.7064, 0.8682, 0.1715}},
    {9, XrVector3f{0.9932, 0.9062, 0.1439}},
};

constexpr XrVector3f grey{0.5f, 0.5f, 0.5f};

std::vector<Iris> data = {};

float a[] = {-1,-1,-1,-1};
float b[] = {1, 1, 1, 1};
float c[] = {0, 0, 0, 0};

#define PNT(p1,p2,p3,p4) {{p1[0], p2[1], p3[2], p4[3]}, grey}
#define PNTW(p1,p2,p3,p4) {{p1[0], p2[1], p3[2], p4[3]}, {1,1,1}}

#define PNTC(p1,p2,p3,p4, c) {{p1[0], p2[1], p3[2], p4[3]}, XrVector3f{p1[0], p2[1], p3[2]}}


std::vector<Iris> tess = {
    PNTW(c,c,c,b),	PNTC(c,c,c,c),
    PNTC(c,c,b,c),	PNTC(c,c,c,c),
    PNTC(c,b,c,c),	PNTC(c,c,c,c),
    PNTC(b,c,c,c),	PNTC(c,c,c,c),

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
