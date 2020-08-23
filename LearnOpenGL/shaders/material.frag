#version 330 core

out vec4 color;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;

//材质
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

    sampler2D diffusetexure;
    sampler2D speculartexure;
};
uniform Material material;
//光照
struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform vec3 objectColor;
uniform vec3 viewPos;

void main()
{
    // 环境光(最暗处的颜色)
    //float ambientStrength = 0.1f;
    //vec3 ambient = light.ambient * material.ambient;
    //增加贴图

    vec3 ambient  = light.ambient  * vec3(texture(material.diffusetexure, TexCoord));

    // 漫反射（光照和法线计算漫反射）
    vec3 norm = normalize(Normal);
    //入射光线
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = (diff * material.diffuse) * light.diffuse;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffusetexure, TexCoord));

    // 镜面反射
    //float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specular = (spec * material.specular) * light.specular; 
    vec3 specular = light.specular * spec * vec3(texture(material.speculartexure, TexCoord));

    //vec3 result = (ambient + diffuse + specular) * objectColor;
    //vec3 result = (ambient + diffuse) * objectColor;

    color = vec4(ambient + diffuse + specular, 1.0f); 
}