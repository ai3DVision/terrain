#include "../common/common.h"

static const unsigned int nCubeVertices = 36;
static const vec3 cubeVertices[] =
{
    vec3(0.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(1.0, 0.0, 0.0),
    vec3(1.0, 1.0, 0.0),
    vec3(1.0, 1.0, 1.0),
    vec3(1.0, 0.0, 1.0),
    vec3(1.0, 1.0, 0.0),
    vec3(1.0, 0.0, 1.0),
    vec3(1.0, 1.0, 0.0),
    vec3(1.0, 0.0, 0.0),
    vec3(1.0, 1.0, 1.0),
    vec3(0.0, 1.0, 1.0),
    vec3(1.0, 0.0, 1.0),
    vec3(0.0, 1.0, 1.0),
    vec3(1.0, 0.0, 1.0),
    vec3(0.0, 0.0, 1.0),
    vec3(0.0, 0.0, 1.0),
    vec3(0.0, 0.0, 0.0),
    vec3(1.0, 0.0, 1.0),
    vec3(0.0, 0.0, 0.0),
    vec3(1.0, 0.0, 1.0),
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 0.0),
    vec3(0.0, 1.0, 1.0),
    vec3(0.0, 0.0, 0.0),
    vec3(0.0, 1.0, 1.0),
    vec3(0.0, 0.0, 1.0),
    vec3(1.0, 1.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(1.0, 1.0, 1.0),
    vec3(0.0, 1.0, 0.0),
    vec3(1.0, 1.0, 1.0),
    vec3(0.0, 1.0, 1.0)
};

static const unsigned int nCubeColors = 36;
static const vec3 cubeColors[] =
{
    vec3(0.583f,  0.771f,  0.014f),
    vec3(0.609f,  0.115f,  0.436f),
    vec3(0.327f,  0.483f,  0.844f),
    vec3(0.822f,  0.569f,  0.201f),
    vec3(0.435f,  0.602f,  0.223f),
    vec3(0.310f,  0.747f,  0.185f),
    vec3(0.597f,  0.770f,  0.761f),
    vec3(0.559f,  0.436f,  0.730f),
    vec3(0.359f,  0.583f,  0.152f),
    vec3(0.483f,  0.596f,  0.789f),
    vec3(0.559f,  0.861f,  0.639f),
    vec3(0.195f,  0.548f,  0.859f),
    vec3(0.014f,  0.184f,  0.576f),
    vec3(0.771f,  0.328f,  0.970f),
    vec3(0.406f,  0.615f,  0.116f),
    vec3(0.676f,  0.977f,  0.133f),
    vec3(0.971f,  0.572f,  0.833f),
    vec3(0.140f,  0.616f,  0.489f),
    vec3(0.997f,  0.513f,  0.064f),
    vec3(0.945f,  0.719f,  0.592f),
    vec3(0.543f,  0.021f,  0.978f),
    vec3(0.279f,  0.317f,  0.505f),
    vec3(0.167f,  0.620f,  0.077f),
    vec3(0.347f,  0.857f,  0.137f),
    vec3(0.055f,  0.953f,  0.042f),
    vec3(0.714f,  0.505f,  0.345f),
    vec3(0.783f,  0.290f,  0.734f),
    vec3(0.722f,  0.645f,  0.174f),
    vec3(0.302f,  0.455f,  0.848f),
    vec3(0.225f,  0.587f,  0.040f),
    vec3(0.517f,  0.713f,  0.338f),
    vec3(0.053f,  0.959f,  0.120f),
    vec3(0.393f,  0.621f,  0.362f),
    vec3(0.673f,  0.211f,  0.457f),
    vec3(0.820f,  0.883f,  0.371f),
    vec3(0.982f,  0.099f,  0.879f)
};

static const unsigned int nCubeUVs = 36;
static const vec2 cubeUVs[] =
{
    vec2(0.333, 0.75),
    vec2(0.666, 0.75),
    vec2(0.333, 0.5),
    vec2(0.666, 0.75),
    vec2(0.333, 0.5),
    vec2(0.666, 0.5),

    vec2(0.666, 0.25),
    vec2(0.333, 0.25),
    vec2(0.666, 0.5),
    vec2(0.333, 0.25),
    vec2(0.666, 0.5),
    vec2(0.333, 0.5),

    vec2(0.666, 0.25),
    vec2(0.666, 0.0),
    vec2(0.333, 0.25),
    vec2(0.666, 0.0),
    vec2(0.333, 0.25),
    vec2(0.333, 0.0),

    vec2(0.0, 0.75),
    vec2(0.333, 0.75),
    vec2(0.0, 0.5),
    vec2(0.333, 0.75),
    vec2(0.0, 0.5),
    vec2(0.333, 0.5),

    vec2(0.666, 0.75),
    vec2(0.333, 0.75),
    vec2(0.666, 1.0),
    vec2(0.333, 0.75),
    vec2(0.666, 1.0),
    vec2(0.333, 1.0),

    vec2(0.666, 0.5),
    vec2(0.666, 0.75),
    vec2(1.0, 0.5),
    vec2(0.666, 0.75),
    vec2(1.0, 0.5),
    vec2(1.0, 0.75)
};

static const unsigned int nCubeIndices = 36;
static const unsigned int cubeIndices[]=
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 36
};
