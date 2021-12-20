#shader vertex
#version 330 core

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aTexturePosition;

uniform mat4 uProjectionMatrix;
out vec2 texturePosition;

void main(void)
{
    gl_Position = uProjectionMatrix * vec4(aPosition, 0.0, 1.0);
    texturePosition = aTexturePosition;
}

#shader fragment
#version 330 core

uniform sampler2D uTexture;
in vec2 texturePosition;
out vec4 FragColor;

void main(void)
{
    FragColor = texture(uTexture, texturePosition);
}
