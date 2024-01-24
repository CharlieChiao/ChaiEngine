#version 430 core

in vec3 color;
in vec3 lightPosition;
in vec3 thePosition;
in vec3 normal;
in vec2 texCoord;
in mat3 TBN;
in vec4 fragPosLight;

uniform int toggleColor;
uniform vec4 lightColor;
uniform vec3 camPos;
uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D brush0;
uniform sampler2D normal0;
uniform samplerCube shadowCubeMap;
uniform float farPlane;

out vec4 theColor;

vec4 pointLight()
{	
	// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = lightPosition - thePosition;

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = (1.0f / (a * dist * dist + b * dist + 1.0f)) * 5.0f;

	// ambient lighting
	float ambient = 0.40f;

	// diffuse lighting
	//vec3 normal = normalize(normal);
	vec3 normal = texture(normal0, texCoord * 2).xyz;
	normal = normal * 2.0 - 1.0;
	normal = normalize(TBN * normal);

	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	//diffuse = mix(0.0f, diffuse, texture(brush0, texCoord).r);

	// specular lighting
	float specularlight = 0.50f;
	vec3 viewdirection = normalize(camPos - thePosition);
	vec3 reflectiondirection = reflect(-lightDirection, normal);
	float specamount = pow(max(dot(viewdirection, reflectiondirection), 0.0f), 16);
	float specular = specamount * specularlight;
	//specular = mix(0.0f, specular, texture(brush0, texCoord).r);

	// Shadow value
	float shadow = 0.0f;
	vec3 fragToLight = thePosition - lightPosition;
	float currentDepth = length(fragToLight);
	float bias = max(0.5f * (1.0f - dot(normal, lightDirection)), 0.0005f); 

	// Not really a radius, more like half the width of a square
	int sampleRadius = 2;
	float offset = 0.02f;
	for(int z = -sampleRadius; z <= sampleRadius; z++)
	{
		for(int y = -sampleRadius; y <= sampleRadius; y++)
		{
		    for(int x = -sampleRadius; x <= sampleRadius; x++)
		    {
		        float closestDepth = texture(shadowCubeMap, fragToLight + vec3(x, y, z) * offset).r;
				// Remember that we divided by the farPlane?
				// Also notice how the currentDepth is not in the range [0, 1]
				closestDepth *= farPlane;
				if (currentDepth > closestDepth + bias)
					shadow += 1.0f;     
		    }    
		}
	}
	// Average shadow
	shadow /= pow((sampleRadius * 2 + 1), 3);

	//shadow = 0.0f;
	//inten = 1.0;

	if(toggleColor == 0)
	{
		return (texture(diffuse0, texCoord) * (diffuse * (1.0f - shadow) * inten + ambient) + texture(specular0, texCoord).r * specular * (1.0f - shadow) * inten) * lightColor;
	}else
	{
		return ((diffuse * (1.0f - shadow) * inten + ambient) + specular * (1.0f - shadow) * inten) * lightColor;
	}
}

void main()
{	
	theColor = pointLight();
}