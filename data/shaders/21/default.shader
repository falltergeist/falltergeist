#shader fragment
#version 120

uniform vec4 color;

void main(void)
{
  gl_FragColor = color;
}

#shader vertex
#version 120

uniform mat4 MVP;
attribute vec2 Position;

void main(void)
{
  gl_Position = MVP*vec4(Position, 0.0, 1.0);
}
