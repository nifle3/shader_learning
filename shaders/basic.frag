#version 330 core

in vec3 myColor;

out vec4 FragColor;

uniform float time;

void main() {
  vec3 updatedColor = vec3(cos(time+myColor.x)*0.5 + 0.5, sin(time+myColor.y)*0.5+0.5, cos(time+myColor.z)*0.5+0.5);

	FragColor = vec4(updatedColor, 1.0f);
}
