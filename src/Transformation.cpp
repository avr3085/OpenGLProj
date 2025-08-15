#include "Transformation.h"

#define PI 3.1415962

m4 TranslationMatrix(v3 pos){
    m4 matrix;
    
    matrix.indices[0] = 1.0f;
    matrix.indices[1] = 0.0f;
    matrix.indices[2] = 0.0f;
    matrix.indices[3] = 0.0f;

    matrix.indices[4] = 0.0f;
    matrix.indices[5] = 1.0f;
    matrix.indices[6] = 0.0f;
    matrix.indices[7] = 0.0f;

    matrix.indices[8] = 0.0f;
    matrix.indices[9] = 0.0f;
    matrix.indices[10] = 1.0f;
    matrix.indices[11] = 0.0f;

    matrix.indices[12] = pos.indices[0]; // move in x axis
    matrix.indices[13] = pos.indices[1]; // move in y axis
    matrix.indices[14] = pos.indices[2]; // move in z axis
    matrix.indices[15] = 1.0f;

    return matrix;
}

m4 RotationMatrix(float angle){
    angle = angle/PI * 180.0f;
    float s = sinf(angle);
    float c = cosf(angle);

    m4 matrix;
    matrix.indices[0] = c;
    matrix.indices[1] = s;
    matrix.indices[2] = 0.0f;
    matrix.indices[3] = 0.0f;

    matrix.indices[4] = -s;
    matrix.indices[5] = c;
    matrix.indices[6] = 0.0f;
    matrix.indices[7] = 0.0f;

    matrix.indices[8] = 0.0f;
    matrix.indices[9] = 0.0f;
    matrix.indices[10] = 1.0f;
    matrix.indices[11] = 0.0f;

    matrix.indices[12] = 0.0f;
    matrix.indices[13] = 0.0f;
    matrix.indices[14] = 0.0f; 
    matrix.indices[15] = 1.0f;

    return matrix;
}

m4 TransRotMatrix(float angle, v3 translation){
    angle = angle/PI * 180.0f;
    float s = sinf(angle);
    float c = cosf(angle);

    m4 matrix;
    matrix.indices[0] = c;
    matrix.indices[1] = s;
    matrix.indices[2] = 0.0f;
    matrix.indices[3] = 0.0f;

    matrix.indices[4] = -s;
    matrix.indices[5] = c;
    matrix.indices[6] = 0.0f;
    matrix.indices[7] = 0.0f;

    matrix.indices[8] = 0.0f;
    matrix.indices[9] = 0.0f;
    matrix.indices[10] = 1.0f;
    matrix.indices[11] = 0.0f;

    matrix.indices[12] = translation.indices[0];
    matrix.indices[13] = translation.indices[1];
    matrix.indices[14] = translation.indices[2]; 
    matrix.indices[15] = 1.0f;

    return matrix;
}
