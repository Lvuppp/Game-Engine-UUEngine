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

varying highp vec2 v_texcoord;

void main(void)
{
    gl_FragColor =  texture2D(u_model.diffuseMap, v_texcoord);
}
