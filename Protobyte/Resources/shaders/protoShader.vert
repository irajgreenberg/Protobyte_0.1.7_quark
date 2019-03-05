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
	vec3 intensity;
	//vec4 diffuse;
	//vec4 ambient;
	//vec4 specular;
};

// currently max 8 lts
uniform Light lights[8];


// for frag shader
out vec3 position;
//out vec3 normal;
out vec4 color;
out vec2 textureCoords;

// for bump mapping
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

  vec3 norm = normalize(normalMatrix * vertexNormal);
  vec3 tang = normalize(normalMatrix * vertexTangent);
  vec3 binorm = normalize(cross(norm, tang)) * 1; // use -1 to reverse

  mat3 toTangentSpace = mat3 (
	tang.x, binorm.x, norm.x,
	tang.y, binorm.y, norm.y,
	tang.z, binorm.z, norm.z
  );

/*  mat3 toTangentSpace = mat3 (
	tang.x, tang.y, tang.z,
	binorm.x, binorm.y, binorm.z,
	norm.x, norm.y, norm.z
  );*/


  position = vec3( modelViewMatrix * vec4(vertexPosition, 1.0) );
  //normal = normalize(normalMatrix * vertexNormal); // don't relaly need anymore

  lightVec = normalize( toTangentSpace * (lights[0].position.xyz - position) );
  viewVec = toTangentSpace * normalize(-position);

  gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
  
}