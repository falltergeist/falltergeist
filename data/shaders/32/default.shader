#shader fragment
#version 150

uniform vec4 color;
out vec4 fragColor;

void main(void)
{
  fragColor = color;
}

#shader vertex
#version 150

uniform mat4 MVP;
in vec2 Position;

void main(void)
{
  gl_Position = MVP*vec4(Position, 0.0, 1.0);
}

