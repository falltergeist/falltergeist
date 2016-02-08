#version 330

uniform sampler2D tex;
uniform vec4 fade;
in vec2 UV;
out vec4 fragColor;

void main(void)
{
  fragColor = mix(texture(tex, UV), fade, fade.a);
//  fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
