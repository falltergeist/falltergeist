#version 150

uniform sampler2D tex;
uniform vec4 outlineColor;
uniform vec4 color;
uniform vec4 fade;
in vec2 UV;
out vec4 fragColor;

void main(void)
{
    ivec2 texSize = textureSize(tex,0);

    vec2 off = 1.0 / texSize;
    vec2 tc = UV.st;

    vec4 c = texture(tex, tc);
    vec4 n = texture(tex, vec2(tc.x, tc.y - off.y));
    vec4 e = texture(tex, vec2(tc.x + off.x, tc.y));
    vec4 s = texture(tex, vec2(tc.x, tc.y + off.y));
    vec4 w = texture(tex, vec2(tc.x - off.x, tc.y));

    vec4 origColor = vec4(color.rgb, c.a);

    float ua = 0.0;
    if (c.a == 0.0 && ( n.a > 0.0 || e.a>0.0 || s.a>0.0 || w.a>0.0))
    {
        origColor = outlineColor;
    }

    //vec4 underColor = outlineColor * vec4(ua);

    //origColor = mix(underColor, origColor, origColor.a);

    fragColor = mix(origColor, fade, fade.a);
    fragColor.a = origColor.a;

    //if (fragColor.a > 0.0)
    //    fragColor.a = 1.0;
}
