#shader fragment
#version 120

uniform vec4 fade;
varying float fLight;

void main(void)
{
   vec4 origColor = vec4(fLight/2.+0.5,fLight/2.+0.5,fLight/2.2+0.5, 1.0);

   gl_FragColor = mix(origColor, fade, fade.a);
   gl_FragColor.a = origColor.a;
}

#shader vertex
#version 120

uniform mat4 MVP;
attribute vec2 Position;
attribute float lights;
uniform vec2 offset;
varying float fLight;

void main(void)
{
  fLight = lights;
  gl_Position = MVP*vec4(Position-offset, 0.0, 1.0);
}
