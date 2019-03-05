#version 430

// no more gl_FragColor, so we need to declare ourself
// great shader tutorials: http://antongerdelan.net/opengl/texturemaps.html

in vec4 color;
in vec2 textureCoords;
in vec3 viewVec;
// in vec3 normal;
in vec3 lightVec;

// default active texture slot 0
// glsl >= 4.2 can avoid setting uniform sampler location in GL
// using binding approach below
layout (binding = 0) uniform sampler2D diffuseMap; // 0
layout (binding = 1) uniform sampler2D bumpMap; // 1

//in vec4 shadowMapCoords;

// Lights
uniform vec3 globalAmbientLight;

// max 8 lt srcs (fer now...)
// not 100% sure i Need this declared in both shaders
struct Light {
	vec3 position;
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
};

// currently max 8 lts
uniform Light lights[8];



struct MaterialProps{
	vec3 ambientMaterial;
	vec3 specularMaterial;
	float shininess;
};



MaterialProps mats = MaterialProps(vec3(.2, .2, .2), vec3(.2, .2, .2), 128);
	


layout (location = 0) out vec4 fragColor;


vec3 phongModel(vec3 norm, vec3 diffR) {
	vec3 r = reflect(-lightVec, norm);
	vec3 ambient = lights[0].ambient.xyz * mats.ambientMaterial;
	float sDotN = max (dot(lightVec, norm), 0.0);
	vec3 diffuse = lights[0].diffuse.xyz * diffR * sDotN;
	vec3 spec = vec3(0.0);
	if(sDotN > 0.0){
	  spec = lights[0].specular.xyz * mats.specularMaterial * pow(max(dot(r, viewVec), 0.0 ), mats.shininess);
	}
	return ambient + diffuse + spec;
}



void main(){
	
	// look up normal from normal map
	vec4 normal = texture(bumpMap, textureCoords)*color;
	vec4 tex = texture(diffuseMap, textureCoords)*color;

	
	//fragColor = vec4(emissive + ambient + diffuse + specular, 1);
	//fragColor = vec4(emissive + ambient + diffuse + specular, 1);
	
	fragColor = vec4(phongModel(normal.xyz, tex.rgb), 1.0);
	//fragColor.a = color.a;
	


	//fragColor = color;
}