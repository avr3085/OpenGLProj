#include <cmath>

struct m4{
    float indices[16];
};

struct v3{
    float indices[3];
};

m4 TranslationMatrix(v3 pos);
m4 RotationMatrix(float angle);
