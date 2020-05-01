// IFT3100H20 ~ image_filter_330_fs.glsl

#version 330

// attribut en sortie
out vec4 fragment_color;

uniform vec3 tint;
uniform float factor;

uniform float width;
uniform float height;


void main()
{
  float r=gl_FragCoord.x/width;
  float g=gl_FragCoord.y/height;
  float b=1.;

  // échantillonner la texture
  vec3 texture_sample = vec3(r,g,b);

  // mixage avec la teinte de couleur
  vec3 filtered_color = mix(texture_sample, tint, factor);
  

  // couleur finale du fragment
  fragment_color = vec4(filtered_color, 1.0);

}
