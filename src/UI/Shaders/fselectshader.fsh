precision highp float;
uniform float u_code;

void main(void)
{
    gl_FragColor = vec4(u_code / 255.0, 0.0, 0.0, 0.5);
}
