struct model
{
    sampler2D diffuseMap;
    sampler2D normalMap;
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 ambienceColor;
    float shinnes;
    bool isDiffuseMapUsing;
    bool isNormalMapUsing;
};

uniform model u_model;

uniform sampler2D u_shadowMap;

uniform highp mat4 u_projectionLightMatrix;
uniform highp mat4 u_shadowLightMatrix;
uniform highp mat4 u_lightMatrix;
uniform highp float u_lightPower;

uniform highp vec4 u_eyePosition;
uniform highp bool u_isDrawDynamic;

varying highp vec4 v_positionLightMatrix;
varying highp vec4 v_position;
varying highp vec3 v_normal;
varying highp vec2 v_texcoord;
varying highp mat3 v_tbnMatrix;
varying highp vec4 v_lightDirection;

void main(void)
{

    vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 diffMatColor = texture2D(u_model.diffuseMap, v_texcoord);
    float ambienceFactor = 0.1;
    float len = 1.0;

    if(u_isDrawDynamic){
        len = 1.0 + 0.25 * pow(length(v_position - u_eyePosition),2.0);
    }

    if(!u_model.isDiffuseMapUsing){
        diffMatColor = vec4(u_model.diffuseColor, 1.0);
    }

    vec3 usingNormal = v_normal;
    vec3 eyeVector = normalize(vec3(v_position - u_eyePosition));
    vec3 lightVector = normalize(v_lightDirection.xyz);

    if(u_model.isNormalMapUsing){
        usingNormal = normalize(texture2D(u_model.normalMap, v_texcoord).rgb * 2.0 - 1.0);
        eyeVector = normalize(v_tbnMatrix * eyeVector);
        lightVector = normalize(v_tbnMatrix * lightVector);
    }

    vec3 reflectLight = normalize(reflect(lightVector, usingNormal));

    vec4 diffColor = diffMatColor * u_lightPower * max(0.0, dot(usingNormal, -lightVector)) / len;
    resultColor += diffColor;

    vec4 ambientColor = ambienceFactor * diffMatColor;
    resultColor += ambientColor * vec4(u_model.ambienceColor, 1.0);

    vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0) * u_lightPower *
            pow(max(0.0, dot(reflectLight, -eyeVector)), u_model.shinnes) / len;
    resultColor += specularColor * vec4(u_model.specularColor, 1.0) ;

    gl_FragColor = resultColor;
}
