#version 330
uniform sampler2D tex;
uniform vec4 fade;
uniform int cnt[6];
uniform int global_light;
in vec2 UV;
out vec4 fragColor;

void main(void)
{
    vec4 origColor = texture(tex, UV);
    origColor.r=0.0;
    origColor.g=0.0;
    origColor.b=1.0;
    if (origColor.a>0)
    {
        origColor.a=0.5;
    }
    origColor.rgb = origColor.rgb/100*global_light;
    fragColor = mix(origColor, fade, fade.a);
    fragColor.a = origColor.a;
}
