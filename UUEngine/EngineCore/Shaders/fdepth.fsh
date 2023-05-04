varying highp vec4 v_position;

void main(void)
{
    float depth = v_position.z / v_position.w;
    depth = depth * 0.5 + 0.5;

    float v1 = depth * 255.0;
    float f1 = fract(v1);
    float vn1 = floor(v1) / 255.0;

    float v2 = f1 * 255.0;
    float f2 = fract(v2);
    float vn2 = floor(v2) / 255.0;

    float v3 = f1 * 255.0;
    float f3 = fract(v2);
    float vn3 = floor(v3) / 255.0;

    gl_FragColor = vec4(v1,v2,v3,f3);
}
