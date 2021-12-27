#version 450


in vec3 rotatedNormal;
in vec4 fragPos;
in vec3 glColor;
in vec3 s;

const float ambientStrength = 0.2;
const float infiniteStrength = 0.2;
const float pointLightStrength = 0.3;
const float spotLightStrength = 2.0;
const vec3 viewPos = vec3(0.0, 0.0, -1.0);
const float specularStrength = 0.6;

out vec3 outColor;


vec3 ambientLight() {
 vec3 lightColor = vec3(1,1,1); //White Light
 vec3 Ambient = (lightColor * ambientStrength);
 return Ambient;
}

vec3 pointLight() {
 vec3 lightPos = vec3(0,4,0);
 vec3 color = vec3(1,1,1); //Green Light

 vec3 lightVector = normalize(lightPos-vec3(fragPos));
 float diff = max(0, dot(vec3(rotatedNormal), vec3(lightVector)));
 
 vec3 reflectVector = reflect(-lightVector, rotatedNormal);
 float spec = pow(max(dot(viewPos,reflectVector),0),32);

 vec3 ambient = ambientLight();
 vec3 diffuse = diff * color;
 vec3 specular = specularStrength * spec * color;

 return (ambient + diffuse + specular);
}


//done
vec3 spotLight()
{
 vec3 lightPos = s;
 vec3 direction = vec3(-1,-1,0);
 vec3 lightColor = vec3(0,0,1); //Blue Light
 float cutoff = cos(radians(20));
 
 vec3 lightDir = normalize(lightPos - vec3(fragPos));
 vec3 ambient = ambientLight();
 
 float theta = dot(lightDir, normalize(-direction));
  if(theta > cutoff) 
  {
   vec3 normal = rotatedNormal;
   float diff = max(dot(normal, lightDir), 0.0);
   vec3 diffuse = (diff * lightColor);
   
   vec3 viewDir = normalize(viewPos - vec3(fragPos));
   vec3 reflectDir = -reflect(-lightDir,normal);
   float spec = pow(max(dot(viewDir,reflectDir), 0),32);
   vec3 specular = (specularStrength * spec * lightColor);
   
   return (diffuse + specular) * spotLightStrength;
  } 
  else 
  {
      return vec3(0,0,0);//ambient * spotLightStrength;
  }
}

vec3 infiniteLight() {
 vec3 lightColor = vec3(1,1,1); //red light
 vec3 lightPos = vec3(0,10,4);
 vec3 dis = vec3(lightPos - vec3(fragPos));
 
 vec3 normal = rotatedNormal;
 vec3 lightDir = normalize(dis);
 float diff = max(dot(normal, lightDir),0);
 vec3 diffuse = (diff*lightColor );
 
 vec3 viewDir = normalize(viewPos - vec3(fragPos));
 vec3 reflectDir = reflect(-lightDir, normal);

 float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
 vec3 specular = (specularStrength * spec * lightColor);

 vec3 ambient = ambientLight();
 
 vec3 infiniteLight = (diffuse + specular) * infiniteStrength;
 return infiniteLight;
}

void main() {
 vec3 point = pointLight();
 vec3 infinite = infiniteLight();
 vec3 spot = spotLight();
 vec3 ambient = ambientLight();
 outColor = glColor * (spot+point);

}