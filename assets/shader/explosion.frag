#version 120

uniform float t;
uniform float power;

float hash(vec2 p)
{
    p = fract(p * 233.33);
    p += dot(p, p + 34.123);
    return fract(p.x * p.y);
}

void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    vec2 p = uv - 0.5;

    float r = length(p);
    float blast = smoothstep(0.0, 0.1 + t * power, r);

    float ring = abs(sin(r * (50.0 - t * 20.0) - t * 12.0));
    ring *= smoothstep(0.2 + t * 0.5, 0.0, r);

    float n = hash(uv * (40.0 + t * 5.0));
    float flicker = 0.5 + 0.5 * sin(t * 15.0 + n * 6.2831);

    vec3 col = vec3(0.0);
    col += vec3(1.0, 0.9, 0.7) * (1.0 - blast) * flicker;  // core
    col += vec3(1.0, 0.5, 0.1) * ring;                    // ring
    col *= smoothstep(1.0, 0.0, t);                      // fade out

    float alpha = max(max(blast, ring), 0.0) * smoothstep(1.0, 0.0, t);

    if (alpha < 0.1)
        discard;

    gl_FragColor = vec4(col, alpha);
}