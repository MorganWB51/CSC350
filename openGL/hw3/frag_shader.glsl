#version 450


in vec3 rotatedNormal;
in vec4 fragPos;
in vec3 glColor;

out vec4 outColor;

void main()
{
 vec3 ambientLight = vec3(0.1, 0.1, 0.1);
 vec3 disfuseLight = vec3(0.0, -0.5, 5.0);
 vec3 eye = vec3(0.0, 0.0, -1.0);

 vec3 Normal = normalize(rotatedNormal);
 vec3 lightDirection = normalize(disfuseLight - vec3(fragPos));
 float diffuse = max(0.0, dot(Normal, lightDirection));
 vec3 diff = diffuse * vec3(1,1,1);
 //vec3 result = (ambientLight + diff) * glColor;

 vec3 viewDir = normalize(eye - vec3(fragPos));
 vec3 reflectDir = reflect(-lightDirection , rotatedNormal);  
 float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
 vec3 specular = 1.5 * spec * vec3(1,1,1);  
 vec3 result = (ambientLight + diff + specular) * glColor;

 outColor = vec4(result, 1.0);

 
 /*
 vec3 halfVector = normalize(eye + disfuseLight );

 float specular = min(1.0, dot(Normal,halfVector));
 specular = max(0.0, specular);

 //Diffuse
 
 vec3 lightedColor = min(specular*vec3(1.0)+glColor*(ambientLight+diffuse), vec3(1.0));
 outColor = vec4(lightedColor, 1.0);

 //outColor = vec4(glColor, 1.0);
*/
};