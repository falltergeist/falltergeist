#version 330

uniform sampler2D tex;
uniform vec4 outlineColor;
uniform vec4 color;
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
    ua = mix(ua, 1.0, c.a);
    ua = mix(ua, 1.0, n.a);
    ua = mix(ua, 1.0, e.a);
    ua = mix(ua, 1.0, s.a);
    ua = mix(ua, 1.0, w.a);

    vec4 underColor = outlineColor * vec4(ua);

    fragColor = underColor;
    fragColor = mix(fragColor, origColor, origColor.a);

//    if (fragColor.a > 0.0)
//        fragColor.a = 1.0;

//  fragColor = texture(tex, UV);
//  fragColor = vec4(1.0, 0.0, 0.0, 1.0);
//  fragColor.g = 0.0;
//  fragColor.b = 0.0;
}
