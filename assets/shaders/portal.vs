#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
    vec2 FragUV;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 MODEL;
uniform mat4 lightSpaceMatrix;

uniform sampler2D NOISE;
uniform sampler2D SCREENTEXTURE;
uniform float TIME;

void main()
{
    // could be better
    vec4 clipPosition = projection * view * MODEL * vec4(aPos, 1.0);
    clipPosition /= clipPosition.w;

    vec2 fraguv = (clipPosition.xy + vec2(1.0)) * 0.5;

    vec2 time = vec2(TIME, TIME);

    vec2 noiseOffset = (
        texture(NOISE, fraguv + (time * vec2(0.34,0.12))).xy +
        texture(NOISE, fraguv + (time * vec2(0.13,0.26))).xz)
         * vec2(0.03, 0.03);
    
    vec3 position = aPos + (aNormal * vec3(noiseOffset.x, 0.0,noiseOffset.y));

    vs_out.FragPos = vec3(MODEL * vec4(position, 1.0));
    vs_out.Normal = transpose(inverse(mat3(MODEL))) * aNormal;
    vs_out.TexCoords = aTexCoords;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position = projection * view * MODEL * vec4(position, 1.0);

    clipPosition = projection * view * MODEL * vec4(position, 1.0);
    clipPosition /= clipPosition.w;

    vs_out.FragUV = (clipPosition.xy + vec2(1.0)) * 0.5;
}