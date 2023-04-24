uniform sampler2D u_texture;
uniform highp vec4 u_lightPosition;
uniform highp float u_lightPower;
varying highp vec4 v_position;
varying highp vec3 v_normal;
varying highp vec2 v_texcoord;

void main(void)
{
    vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 diffMatColor = vec4(0.5, 0.25, 0.1, 0.0);

    vec3 eyeVector = normalize(v_position.xyz - eyePosition.xyz);
    vec3 lightVector = normalize(v_position.xyz - u_lightPosition.xyz);
    vec3 reflectLight = normalize(reflect(lightVector, v_normal));

    float len = length(v_position.xyz - eyePosition.xyz);
    float specularFactor = 10.0;
    float ambiendFactor = 0.1;

    vec4 diffColor = diffMatColor * u_lightPower /**dot(v_normal, -lightVector)*/
            / (1.0 + 0.25 * pow(len, 2.0));

    resultColor += diffColor;

    gl_FragColor = resultColor;
}
