

#version 330 core
in vec4 f_worldPos;
in vec3 f_normal;
in vec4 f_light_view;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform int shader_num;
out vec4 FragColor;


void main(){
    vec3 light_color = mix(objectColor, lightColor, 0.15);
    // Ambient
    float ambient_p = 0.1f;
    vec3 ambient = ambient_p * light_color;

    // Diffuse
    //Calculate the amount of light hitting each surface

    vec3 f_norm = normalize(f_normal);
    vec3 lightFaceDir = normalize(lightPos - vec3(f_worldPos));

    //Calculate the degree of coincidence between surfaces and lights
    // dot Matching of surface and light
    // max When facing backwards, set the light to 0
    float diffPer = max(dot(f_norm, lightFaceDir), 0.0);
    vec3 diffuse = diffPer * light_color;

    // Specular
    float specularStrength = 0.5;
    vec3 viewFaceDir = normalize(0.0 - vec3(f_worldPos));
    vec3 incidentLDir = -lightFaceDir; 
    //Calculate the reflection direction
    vec3 reflectDir = reflect(incidentLDir, f_norm);
    int materialShiness = 32;
    //Reflection values are expressed as coefficients
    float specPer = pow(max(dot(viewFaceDir, reflectDir), 0.0), materialShiness);
    vec3 specular = specularStrength * specPer * light_color;
    vec3 lighting = (ambient + diffuse + specular);
    FragColor = vec4(lighting * objectColor, 1.0);
    
}
