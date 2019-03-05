#version 430
// best practices:
// include version # up top
// write your own uniforms
// put as amny shader computations in vert Shader vs. frag shader
// avoid logic in shaders as much as possible (do at init on CPU)

// attibutes in memory
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec4 vertexColor;
layout (location = 3) in vec2 vertexTextureCoords;
layout (location = 4) in vec3 vertexTangent;

// Lights
// max 8 lt srcs (fer now...)
struct Light {
	vec3 position;
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
};

// currently max 8 lts
uniform Light lights[8];

// for frag shader
out vec4 color;
out vec2 textureCoords;
out vec3 viewVec;
out vec3 lightVec;


// coord transforms
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 lightModelViewProjectionMatrix;


void main(){
  
  	color = vertexColor;
	textureCoords = vertexTextureCoords;
  

  // matrix from eye space to tangent space
  vec3 normal = normalize(normalMatrix * vertexNormal);
  vec3 tangent = normalize(normalMatrix * vertexTangent);
  vec3 biNormal = normalize(cross(normal, tangent));
	
// Create tangent space matrix
	mat3 tangentSpaceMat = mat3(tangent.x, biNormal.x, normal.x,
							tangent.y, biNormal.y, normal.y,
							tangent.z, biNormal.z, normal.z);

// position in eye space
 vec3 pos = vec3(modelViewMatrix * vec4(vertexPosition, 1.0));


 // transform lt and view vecs to tangent space
 lightVec = normalize(tangentSpaceMat * (lights[0].position.xyz - pos) );
 viewVec = tangentSpaceMat * normalize(-pos);


// Position in clip space
  gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
  
}