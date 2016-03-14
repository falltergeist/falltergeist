#version 120

uniform vec4 fade;
varying float fLight;

void main(void)
{
   vec4 origColor = vec4(fLight/2.+0.5,fLight/2.+0.5,fLight/2.2+0.5, 1.0);

   gl_FragColor = mix(origColor, fade, fade.a);
   gl_FragColor.a = origColor.a;
}
