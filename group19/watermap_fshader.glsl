#version 330 core

// Light properties.
uniform vec3 Ia, Id, Is;

// Time for water animation.
uniform float time;

// Textures.
uniform sampler2D reflectionTex;
uniform sampler2D waterNormalMap;
uniform sampler2D riverSurfaceMap;

// Vertices 3D position (after heightmap displacement) in model space.
in vec3 vertexPosition3DModel;

in vec3 reflectionCoord;

// Light and view directions.
in vec3 lightDir, viewDir;

// First output buffer is pixel color (mandatory output, gl_FragColor).
layout(location = 0) out vec4 color;


void main()
{
	  // Normalize the vectors.
    vec3 L = normalize(lightDir);
    vec3 V = normalize(viewDir);

	//current UV coordinate
    vec2 UV = vec2((vertexPosition3DModel.xy +1.0)/2.0);
	
	//reflection UV
	vec2 ref_UV = reflectionCoord.xy; //gl_FragCoord.xy * 0.5 + 0.5;	

    //Get the normal vector from normal map
	vec3 normal = normalize(texture(waterNormalMap,ref_UV).rgb);

	//Define other properties of light for water surface
	float power = 60.0f;
	float ka, kd, ks;
	ka = 0.6f;
    kd = 0.4f;
    ks = 0.6f;

	//Get the texture value from texture map
	float time_tmp = time * 0.0002;
	//vec3 material = vec3(0.0,0.0,1.0);//texture2D(riverSurfaceMap, vec2(cos(UV.x + time_tmp), sin(UV.y-time_tmp))).rgb;
	vec3 material = texture2D(reflectionTex, ref_UV).rgb;
	 // Compute the ambient color component based on texture mapping.
    vec3 ambient = Ia * ka * material;

    // Compute the diffuse color component.
    vec3 diffuse = Id * kd * material * max(dot(normal,L),0.0);

	// Hack : water is normal mapped for diffuse lightning and flat for specular.
	normal = vec3(0.0, 0.0, 1.0);

    // Compute the specular color component.
    vec3 specular = Is * ks * material * pow(max(dot(V,reflect(L,normal)),0.0),power);

	color = vec4(material,1.0);; //vec4(ambient + diffuse + specular, 1.0);
}
