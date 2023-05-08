attribute highp vec4 a_position;

uniform highp mat4 u_projectionLightMatrix;
uniform highp mat4 u_shadowLightMatrix;
uniform highp mat4 u_modelMatrix;

varying highp vec4 v_position;

void main(void)
{
    v_position = u_projectionLightMatrix * u_shadowLightMatrix * u_modelMatrix * a_position;
    gl_Position = v_position;
}
