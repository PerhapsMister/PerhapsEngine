#version 430 core
out vec4 FragColor;  

float checker(vec2 uv, float repeats) 
{
  float cx = floor(repeats * uv.x);
  float cy = floor(repeats * uv.y); 
  float result = mod(cx + cy, 2.0);
  return sign(result);
}
 

const vec2 texSize = vec2(0.5,0.5);
void main()
{
    vec2 uv = gl_FragCoord.xy * 0.1;
  uv.x *= texSize.x / texSize.y;
  float c = mix(1.0, 0.0, checker(uv, 1f));
  FragColor = vec4(c, c, c, 1.0); 
    
}