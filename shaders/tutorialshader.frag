#version 460 core

out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //mix uses the final argument as a blend factor, in this case it'll use 0.2 of texture2 and 0.8 of texture1
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}
