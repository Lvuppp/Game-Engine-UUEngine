uniform sampler2D u_texture;
uniform highp vec4 u_lightPosition;
uniform highp vec4 u_eyePosition;
uniform highp float u_lightPower;
uniform highp float u_specularFactor;
uniform highp float u_ambientFactor;
varying highp vec4 v_position;
varying highp vec3 v_normal;
varying highp vec2 v_texcoord;

void main(void)
{
    vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 diffMatColor = texture2D(u_texture, v_texcoord);

    vec3 eyeVector = normalize(vec3(v_position - u_eyePosition));
    vec3 lightVector = normalize(vec3(v_position - u_lightPosition));
    vec3 reflectLight = normalize(reflect(lightVector, v_normal));

    float len = length(v_position - u_eyePosition);

    vec4 diffColor = diffMatColor * u_lightPower * max(0.0, dot(v_normal, -lightVector))
            / (1.0 + 0.25 * pow(len,2.0));
    resultColor += diffColor;

    vec4 ambientColor = u_ambientFactor * diffMatColor;
    resultColor += ambientColor;

    vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0) * u_lightPower *
            pow(max(0.0, dot(reflectLight, -eyeVector)), u_specularFactor) / (1.0 + 0.25 * pow(len, 2.0));
    resultColor += specularColor;

    gl_FragColor = resultColor;
}
