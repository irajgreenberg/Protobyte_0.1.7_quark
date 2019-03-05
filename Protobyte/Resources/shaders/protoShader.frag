#version 430

in vec3 position;
//in vec3 normal;
in vec4 color;
in vec2 textureCoords;

in vec3 viewVec;
in vec3 lightVec;

// default active texture slot 0
// glsl >= 4.2 can avoid setting uniform sampler location in GL
// using binding approach below
layout (binding = 0) uniform sampler2D diffuseMap; // 0
layout (binding = 1) uniform sampler2D bumpMap; // 1


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

// materials
uniform vec4 diffuseMaterial;
uniform vec4 ambientMaterial;
uniform vec4 specularMaterial;
uniform vec4 emissiveMaterial;
uniform float shininess;


layout (location = 0) out vec4 fragColor;



vec3 calcPhongBump(vec3 norm, vec3 diffR){
	vec3 r = reflect(-lightVec, norm);
	vec3 ambient = lights[0].intensity * vec3(ambientMaterial);
	float sDotN = max( dot(lightVec, norm), 0.0 );
	vec3 diffuse = lights[0].intensity * diffR * sDotN;
	vec3 spec = vec3(0.0);
	if(sDotN > 0.0){
		spec = lights[0].intensity * vec3(specularMaterial) *
		pow( max( dot(r, viewVec), 0.0 ),
		shininess );
	}
	
	return ambient + diffuse + spec;
}


/*vec3 calcPhong(){
	vec3 n = normalize(normal);
	vec3 s = normalize( lights[0].position - position );
	vec3 v = normalize( vec3(-position) );
	vec3 r = reflect(-s, n);
	
	vec4 tex = texture(diffuseMap, textureCoords.st)*color;

	vec3 phong = lights[0].intensity * (vec3(ambientMaterial) + vec3(diffuseMaterial) * max(dot(s, n), 0.0)*vec3(tex) + vec3(specularMaterial) * pow( max( dot(r, v), 0.0), shininess ) );

	return phong;
}*/



void main() {
	vec4 normal = texture(bumpMap, textureCoords);
	vec4 texColor = texture(diffuseMap, textureCoords);//*color;
	fragColor = vec4( calcPhongBump(normal.xyz, texColor.rgb), 1.0);
	//fragColor = vec4( calcPhong(), 1.0 );
}