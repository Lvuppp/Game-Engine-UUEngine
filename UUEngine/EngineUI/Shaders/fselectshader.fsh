uniform float u_code;

void main(void)
{
    gl_FragColor = vec4(u_code / 255.0f, 0.0, 0.0, 0.5);
}
