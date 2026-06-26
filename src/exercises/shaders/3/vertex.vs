/*
Output the vertex position to the fragment shader using the out keyword and set the fragment's color
equal to this vertex position (see how even the vertex position values are interpolated across the triangle).
Once you managed to do this; try to answer the following question: why is the bottom-left side of our triangle black?:
*/
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
out vec3 position;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    position = vec3(aPos);
}

/*
Answer: the left-bottom side is black because it's coordinates are (-0.5, -0.5, 0.0), which gets fixed to (0.0, 0.0, 0.0),
        that's the color black.
*/