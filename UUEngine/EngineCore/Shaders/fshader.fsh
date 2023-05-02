struct model
{
    sampler2D diffuseMap;
    sampler2D normalMap;
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 ambienceColor;
    float shinnes;
};

uniform model u_model;
uniform highp vec4 u_lightPosition;
uniform highp bool u_isDiffuseMapUsing;
uniform highp vec4 u_eyePosition;
uniform highp float u_lightPower;
uniform highp bool u_isDrawDynamic;

varying highp vec4 v_position;
varying highp vec3 v_normal;
varying highp vec2 v_texcoord;

void main(void)
{

    vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 diffMatColor = texture2D(u_model.diffuseMap, v_texcoord);
    float ambienceFactor = 0.1;
    float specularFactor = 60.0;
    float len = 1.0;

    if(u_isDrawDynamic){
        len = 1.0 + 0.25 * pow(length(v_position - u_eyePosition),2.0);
    }

    if(!u_isDiffuseMapUsing){
        diffMatColor = vec4(u_model.diffuseColor, 1.0);
    }

    vec3 eyeVector = normalize(vec3(v_position - u_eyePosition));
    vec3 lightVector = normalize(vec3(v_position - u_lightPosition));
    vec3 reflectLight = normalize(reflect(lightVector, v_normal));

    vec4 diffColor = diffMatColor * u_lightPower * max(0.0, dot(v_normal, -lightVector)) / len;
    resultColor += diffColor;

    vec4 ambientColor = ambienceFactor * diffMatColor;
    resultColor += ambientColor * vec4(u_model.ambienceColor, 1.0);

    vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0) * u_lightPower *
            pow(max(0.0, dot(reflectLight, -eyeVector)), u_model.shinnes) / len;
    resultColor += specularColor * vec4(u_model.specularColor, 1.0) ;

    gl_FragColor = resultColor;
}
