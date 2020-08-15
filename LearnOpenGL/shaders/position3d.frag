#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    //显示图片
    //color = texture(ourTexture1, TexCoord);
    //图片和颜色混合
    //color = texture(ourTexture1, TexCoord) * vec4(ourColor, 1.0f);
    //混合两张图片
     color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}