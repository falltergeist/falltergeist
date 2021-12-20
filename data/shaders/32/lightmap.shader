#shader fragment
#version 150

uniform vec4 fade;
in float fLight;
out vec4 fragColor;

void main(void)
{
   vec4 origColor = vec4(fLight/2.+0.5,fLight/2.+0.5,fLight/2.2+0.5, 1.0);

   fragColor = mix(origColor, fade, fade.a);
   fragColor.a = origColor.a;
}

#shader vertex
#version 150

uniform mat4 MVP;
in vec2 Position;
in float lights;
uniform vec2 offset;
out float fLight;

void main(void)
{
  fLight = lights;
  gl_Position = MVP*vec4(Position-offset, 0.0, 1.0);
}
