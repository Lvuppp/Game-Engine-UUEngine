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
uniform highp float u_ShadowPointCloudFilteringQuality;

uniform highp vec4 u_eyePosition;
uniform highp bool u_isDrawDynamic;

varying highp vec4 v_positionLightMatrix;
varying highp vec4 v_position;
varying highp vec3 v_normal;
varying highp vec2 v_texcoord;
varying highp mat3 v_tbnMatrix;
varying highp vec4 v_lightDirection;



highp float SamplerShadowMap(sampler2D map, vec2 coords, float compare)
{
    vec4 v = texture2D(map, coords);
    float value = v.x * 255.0 + (v.y * 255.0 + (v.z * 255.0 + v.w)/ 255.0) / 255.0;
    return step(compare, value);
}

highp float SampleShadowMapLinear(sampler2D map, vec2 coords, float compare, vec2 texelsize)
{
    vec2 pixsize = coords / texelsize + 0.5;
    vec2 pixfractpart = fract(pixsize);
    vec2 starttexel = (pixsize - pixfractpart) * texelsize;
    float bltexel = SamplerShadowMap(map, starttexel, compare);
    float brtexel = SamplerShadowMap(map, starttexel + vec2(texelsize.x, 0.0), compare);
    float tltexel = SamplerShadowMap(map, starttexel + vec2(0.0, texelsize.y), compare);
    float trtexel = SamplerShadowMap(map, starttexel + texelsize, compare);

    float mixL = mix(bltexel, tltexel, pixfractpart.y);
    float mixR = mix(brtexel, trtexel, pixfractpart.y);

    return mix(mixL, mixR, pixfractpart.x);
}

// point cloud filtering
highp float SampleShadowMapPCF(sampler2D map, vec2 coords, float compare, vec2 texelsize)
{
    float result = 0.0;
    float spcfq = u_ShadowPointCloudFilteringQuality;
    for(float y = -spcfq; y < spcfq; y += 1.0)
        for(float x = -spcfq; x < spcfq; x += 1.0)
        {
            vec2 offset = vec2(x, y) * texelsize;
            result += SampleShadowMapLinear(map, coords + offset, compare, texelsize);
        }
    return result / 9.0;
}

highp float CalcShadowAmount(sampler2D map, vec4 plm)
{
    vec3 value = (plm.xyz / plm.w) * vec3(0.5) + vec3(0.5);
    float offset = 3.8 * dot(v_normal, v_lightDirection.xyz); // первый коэффициент должен влиять на качество тени
    return SampleShadowMapPCF(map, value.xy, value.z * 255.0 + offset, vec2(1.0 / 1024.0, 1.0 / 1024.0));
}


void main(void)
{
    highp float shadowCoef = CalcShadowAmount(u_shadowMap, v_positionLightMatrix);
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

    shadowCoef += 0.5;
    if(shadowCoef > 1.0)
        shadowCoef = 1.0;

    gl_FragColor = resultColor * shadowCoef ;
}
