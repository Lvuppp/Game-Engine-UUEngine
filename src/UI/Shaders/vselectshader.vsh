precision highp float;
attribute highp vec4 a_position;

uniform highp mat4 u_projectionMatrix;
uniform highp mat4 u_modelMatrix;
uniform highp mat4 u_viewMatrix;

void main(void)
{
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}
