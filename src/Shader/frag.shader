#version 330 core
out vec4 FragColor;

in vec3 outCol;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    // FragColor = outCol;
    // FragColor = vec4(outCol, 1.0f);
    // FragColor = texture(ourTexture, TexCoord);
    FragColor = texture(ourTexture, TexCoord) * vec4(outCol, 1.0f);
};