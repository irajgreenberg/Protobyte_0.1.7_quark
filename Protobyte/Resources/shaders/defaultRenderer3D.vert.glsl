#version 430 core

layout (location = 4) in vec3 vertexTangent;
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec4 vertexColor;
layout (location = 3) in vec2 vertexTextureCoords;


out VS_OUT
{
    vec2 texcoord;
    vec3 eyeDir;
    vec3 lightDir[8];
    vec3 normal;
} vs_out;

// shadow coords
uniform mat4 shadowModelViewBiasProjectionMatrix;
out vec4 shadowMapCoords; //shadow coordinates;   

// coord transforms
uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 lightModelViewProjectionMatrix;

// switch with passed in lights
uniform vec3 light_pos = vec3(-10, -10, 10);

// Lights
// max 8 lt srcs (fer now...)
struct Light {
  vec3 position;
  vec3 intensity;
  //vec4 diffuse;
  //vec4 ambient;
  //vec4 specular;
};
uniform Light lights[8];

void main(void)
{
    // Calculate vertex position in view space.
    vec4 P = modelViewMatrix * vec4(vertexPosition, 1.0);

    // Calculate normal (N) and tangent (T) vectors in view space from
    // incoming object space vectors.
    vec3 V = P.xyz;
    vec3 N = normalize(mat3(modelViewMatrix) * vertexNormal);
    vec3 T = normalize(mat3(modelViewMatrix) * vertexTangent);
    // Calculate the bitangent vector (B) from the normal and tangent
    // vectors.
    vec3 B = cross(N, T);

    // shadowmap 
  //shadowMapCoords = shadowModelViewBiasProjectionMatrix*(modelMatrix*vec4(vertexPosition, 1.0));
  shadowMapCoords = shadowModelViewBiasProjectionMatrix*vec4(vertexPosition, 1.0);
   
    // The light vector (L) is the vector from the point of interest to
    // the light. Calculate that and multiply it by the TBN matrix.
    for(int i=0; i<8; ++i){
    vec3 L = lights[i].position - P.xyz;
    vs_out.lightDir[i] = normalize(vec3(dot(L, T), dot(L, B), dot(L, N)));
  }

    // The view vector is the vector from the point of interest to the
    // viewer, which in view space is simply the negative of the position.
    // Calculate that and multiply it by the TBN matrix.
    V = -P.xyz;
    vs_out.eyeDir = normalize(vec3(dot(V, T), dot(V, B), dot(V, N)));

    // Pass the texture coordinate through unmodified so that the fragment
    // shader can fetch from the normal and color maps.
    vs_out.texcoord = vertexTextureCoords;

    // Pass the per-vertex normal so that the fragment shader can
    // turn the normal map on and off.
    vs_out.normal = N;

    // Calculate clip coordinates by multiplying our view position by
    // the projection matrix.
    gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}