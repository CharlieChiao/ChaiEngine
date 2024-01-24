#version 430 core

layout(location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTex;
layout (location = 4) in vec3 tangent;
layout (location = 5) in vec3 bitangent;

uniform vec3 lightPos;
uniform mat4 model;
uniform mat4 cameraMatrix;
uniform mat4 lightProjection;

out vec3 color;
out vec3 lightPosition;
out vec3 thePosition;
out vec3 normal;
out vec2 texCoord;
out mat3 TBN;
out vec4 fragPosLight;

void main()
{
	thePosition = (model * vec4(aPos,1.0f)).xyz;
	gl_Position = cameraMatrix * vec4(thePosition,1.0f);
	lightPosition = lightPos;
	color = aColor;
	normal = (model * vec4(aNormal, 0.0f)).xyz;
	texCoord = aTex;
	vec3 T = normalize(vec3(model * vec4(tangent,   0.0)));
    vec3 B = normalize(vec3(model * vec4(bitangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal,   0.0)));
	TBN = mat3(T, B, N);
	fragPosLight = lightProjection * vec4(thePosition, 1.0f);
}
