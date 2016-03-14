#version 150

uniform sampler2D tex;
uniform vec4 fade;
uniform int cnt[6];
uniform int global_light;
in vec2 UV;
out vec4 fragColor;

void main(void)
{

    const vec3 monitorsPalette[5] = vec3[](
        vec3(0.42, 0.42, 0.43),
        vec3(0.38, 0.40, 0.49),
        vec3(0.34, 0.42, 0.56),
        vec3(0.00, 0.57, 0.63),
        vec3(0.42, 0.73, 1.00)
    );


    const vec3 slimePalette[4] = vec3[] (
        vec3(0.00, 0.42, 0.00),
        vec3(0.04, 0.45, 0.02),
        vec3(0.10, 0.48, 0.05),
        vec3(0.16, 0.51, 0.10)
    );


    const vec3 shorePalette[6] = vec3[] (
        vec3(0.32, 0.24, 0.16),
        vec3(0.29, 0.23, 0.16),
        vec3(0.26, 0.21, 0.15),
        vec3(0.24, 0.20, 0.15),
        vec3(0.21, 0.18, 0.14),
        vec3(0.20, 0.16, 0.14)
    );


    const vec3 fireSlowPalette[5] = vec3[] (
        vec3(1.00, 0.00, 0.00),
        vec3(0.84, 0.00, 0.00),
        vec3(0.57, 0.16, 0.04),
        vec3(1.00, 0.46, 0.00),
        vec3(1.00, 0.23, 0.00)
    );


    const vec3 fireFastPalette[5] = vec3[] (
        vec3(0.27, 0.0, 0.0),
        vec3(0.48, 0.0, 0.0),
        vec3(0.70, 0.0, 0.0),
        vec3(0.48, 0.0, 0.0),
        vec3(0.27, 0.0, 0.0)
    );

    vec4 origColor = texture(tex, UV);

    if (origColor.a == 0.2 && origColor.r == 0.6)
    {
        int index = int((origColor.b * 255.0) / 51.0);
        int newIndex;

        if (index<0) index = 0;

        if (origColor.g == 0.0)
        {
            if (index>3) index = 3;
             newIndex = ((index) + cnt[0]) % 4;
            origColor.rgb = slimePalette[(newIndex)];
        }
        else if (origColor.g == 0.2)
        {
            if (index>4) index = 4;
             newIndex = ((index) + cnt[1]) % 5;
            origColor.rgb = monitorsPalette[(newIndex)];
        }
        else if (origColor.g == 0.4)
        {
            if (index>4) index = 4;
             newIndex = ((index) + cnt[2]) % 5;
            origColor.rgb = fireSlowPalette[(newIndex)];
        }
        else if (origColor.g == 0.6)
        {
            if (index>4) index = 4;
             newIndex = ((index) + cnt[3]) % 5;
            origColor.rgb = fireFastPalette[(newIndex)];
        }
        else if (origColor.g == 0.8)
        {
            if (index>5) index = 5;
             newIndex = ((index) + cnt[4]) % 6;
            origColor.rgb = shorePalette[(newIndex)];
        }
        else if (origColor.g == 1.0)
        {
            origColor.rgb = vec3((cnt[5]*4)/255.0,0,0);
        }

        origColor.a = 1.0;
   }
   else
   {
     // add light
     origColor.rgb = origColor.rgb/100*global_light;
   }

   fragColor = mix(origColor, fade, fade.a);
   fragColor.a = origColor.a;
}
