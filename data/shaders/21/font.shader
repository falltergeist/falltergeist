#shader fragment
#version 120

uniform sampler2D tex;
uniform vec4 outlineColor;
uniform vec4 color;
uniform vec4 fade;
uniform vec2 texSize;
varying vec2 UV;

void main(void)
{

    vec2 off = 1.0 / texSize;
    vec2 tc = UV.st;

    vec4 c = texture2D(tex, tc);
    vec4 n = texture2D(tex, vec2(tc.x, tc.y - off.y));
    vec4 e = texture2D(tex, vec2(tc.x + off.x, tc.y));
    vec4 s = texture2D(tex, vec2(tc.x, tc.y + off.y));
    vec4 w = texture2D(tex, vec2(tc.x - off.x, tc.y));

    vec4 origColor = vec4(color.rgb, c.a);

    float ua = 0.0;
    if (c.a == 0.0 && ( n.a > 0.0 || e.a>0.0 || s.a>0.0 || w.a>0.0))
    {
        origColor = outlineColor;
    }


    gl_FragColor = mix(origColor, fade, fade.a);
    gl_FragColor.a = origColor.a;
}

#shader vertex
#version 120

uniform mat4 MVP;
attribute vec2 Position;
attribute vec2 TexCoord;
uniform vec2 offset;
varying vec2 UV;

void main(void)
{
  UV = TexCoord;
  gl_Position = MVP*vec4(Position+offset, 0.0, 1.0);
}
