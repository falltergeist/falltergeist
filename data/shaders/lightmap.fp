#version 330

uniform vec4 fade;
in float fLight;
out vec4 fragColor;

void main(void)
{
   vec4 origColor = vec4(fLight/2.+0.5,fLight/2.+0.5,fLight/2.2+0.5, 1.0);

   fragColor = mix(origColor, fade, fade.a);
   fragColor.a = origColor.a;
}
