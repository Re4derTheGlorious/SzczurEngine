#version 330 core

// Input from vertex shader
in vec3 position;
in vec4 color;
in vec2 texCoord;

// Output for OpenGL
out vec4 FragColor;

// Bound texture
uniform sampler2D boundTexture;
uniform bool isTextured;

void main()
{
    if (isTextured)
    {
        vec4 pixel = texture(boundTexture, texCoord);

        if (pixel.a == 0.0)
            discard;

        FragColor = pixel * color;
    }
    else
    {
        FragColor = color;
    }
}
