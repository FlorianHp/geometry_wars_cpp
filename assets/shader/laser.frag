#version 120

uniform float time;

float hash(vec2 p)
{
    p = fract(p * 233.33);
    p += dot(p, p + 34.123);
    return fract(p.x * p.y);
}

void main()
{
    vec2 uv = gl_TexCoord[0].xy;

    vec2 centered = uv - 0.5;
    float dist = length(centered);

    float pulse = 0.5 + 0.5 * sin(time * 4.0);

    float spark = hash(uv * (time * 2.0));
    float flicker = sin(time * 8.0 + spark * 6.28);

    float chaotic = abs(sin((uv.x + uv.y) * 10.0 + time * 6.0));

    float core = smoothstep(0.18 + pulse * 0.08, 0.0, dist);

    float glow = smoothstep(0.45, 0.0, dist) * (0.8 + 0.2 * chaotic);

    float rays = abs(sin(atan(centered.y, centered.x) * 12.0 + time * 4.0));
    float rayGlow = smoothstep(0.3, 0.0, dist) * rays * 0.4;

    vec3 col = vec3(0.0);
    col += vec3(1.0, 0.9, 0.4) * core;
    col += vec3(0.3, 0.5, 1.0) * glow;
    col += vec3(1.0, 1.0, 0.7) * rayGlow;

    col *= (0.9 + 0.1 * flicker);

    float alpha = max(core, max(glow, rayGlow));

    gl_FragColor = vec4(col, alpha);
}