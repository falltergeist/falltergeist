#version 330

uniform vec4 fade;
in float fLight;
out vec4 fragColor;

void main(void)
{
   vec4 origColor = vec4(0.4,0.4,0.3,fLight*0.3);


   fragColor = mix(origColor, fade, fade.a);
   fragColor.a = origColor.a;
}
