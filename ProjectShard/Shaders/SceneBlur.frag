#version 330 core
in vec2 TexCoords;
out vec4 color;

#define distortion 0.2

uniform sampler2D screenTexture;
uniform bool blurScreen;
uniform float screenWidth;
uniform float screenHeight;
uniform float iGlobalTime;

const float offset = 1.0 / 300; 

vec2 curve(vec2 uv)
{
	uv = (uv - 0.5) * 2.0;
	uv *= 1.1;	
	uv.x *= 1.0 + pow((abs(uv.y) / 5.0), 2.0);
	uv.y *= 1.0 + pow((abs(uv.x) / 4.0), 2.0);
	uv  = (uv / 2.0) + 0.5;
	uv =  uv *0.92 + 0.04;
	return uv;
}

vec2 radialDistortion(vec2 coord) 
{
	vec2 cc = coord - vec2(0.5);
	float dist = dot(cc, cc) * distortion;
	return coord + cc * (1.0 - dist) * dist;
}

void main()
{
	//vec2 iResolution = vec2(screenWidth, screenHeight);
	//vec2 q = TexCoords.xy / iResolution.xy;
 //   vec2 uv = q;
 //   uv = curve( uv );
 //   vec3 oricol = texture(screenTexture, vec2(q.x,q.y) ).xyz;
 //   vec3 col;
	//float x =  sin(0.3 * iGlobalTime + uv.y * 21.0) * sin(0.7 * iGlobalTime + uv.y * 29.0) *sin(0.3 + 0.33 * iGlobalTime + uv.y * 31.0) * 0.0017;

	//col.r = texture(screenTexture, vec2(x+uv.x+0.001,uv.y+0.001)).x+0.05;
 //   col.g = texture(screenTexture,vec2(x+uv.x+0.000,uv.y-0.002)).y+0.05;
 //   col.b = texture(screenTexture,vec2(x+uv.x-0.002,uv.y+0.000)).z+0.05;
 //   col.r += 0.08*texture(screenTexture,0.75*vec2(x+0.025, -0.027)+vec2(uv.x+0.001,uv.y+0.001)).x;
 //   col.g += 0.05*texture(screenTexture,0.75*vec2(x+-0.022, -0.02)+vec2(uv.x+0.000,uv.y-0.002)).y;
 //   col.b += 0.08*texture(screenTexture,0.75*vec2(x+-0.02, -0.018)+vec2(uv.x-0.002,uv.y+0.000)).z;

	//col = clamp(col*0.6+0.4*col*col*1.0,0.0,1.0);

 //   float vig = (0.0 + 1.0*16.0*uv.x*uv.y*(1.0-uv.x)*(1.0-uv.y));
	//col *= vec3(pow(vig,0.3));

 //   col *= vec3(0.95,1.05,0.95);
	//col *= 2.8;

	//float scans = clamp( 0.35+0.35*sin(3.5*iGlobalTime+uv.y*iResolution.y*1.5), 0.0, 1.0);
	
	//float s = pow(scans,1.7);
	//col = col*vec3( 0.4+0.7*s) ;

	//col *= 1.0+0.01*sin(110.0*iGlobalTime);
	//if (uv.x < 0.0 || uv.x > 1.0)
	//	col *= 0.0;
	//if (uv.y < 0.0 || uv.y > 1.0)
	//	col *= 0.0;
	
	//col *= 1.0 - 0.65 * vec3(clamp((mod(TexCoords.x, 2.0) - 1.0) * 2.0, 0.0, 1.0));
	////color = vec4(col, 1.0);
	//color = texture(screenTexture, TexCoords);

	//if (mod(floor(TexCoords.y * screenHeight / 1.0), 2.0) == 0.0)
 //       color= vec4(0.0, 0.0, 0.0, 1.0);
 //   else
        color = texture(screenTexture, TexCoords);

	//if(blurScreen)
	//{
	//	vec2 offsets[9] = vec2[](
	//		vec2(-offset, offset),  // top-left
	//		vec2(0.0f,    offset),  // top-center
	//		vec2(offset,  offset),  // top-right
	//		vec2(-offset, 0.0f),    // center-left
	//		vec2(0.0f,    0.0f),    // center-center
	//		vec2(offset,  0.0f),    // center-right
	//		vec2(-offset, -offset), // bottom-left
	//		vec2(0.0f,    -offset), // bottom-center
	//		vec2(offset,  -offset)  // bottom-right    
	//	);

	//	float kernel[9] = float[](
	//	1.0 / 16, 2.0 / 16, 1.0 / 16,
	//	2.0 / 16, 4.0 / 16, 2.0 / 16,
	//	1.0 / 16, 2.0 / 16, 1.0 / 16);
    
	//	vec3 sampleTex[9];
	//	for(int i = 0; i < 9; i++)
	//	{
	//		sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
	//	}
	//	vec3 col = vec3(0.0);
	//	for(int i = 0; i < 9; i++)
	//		col += sampleTex[i] * kernel[i];
    
	//	color = vec4(col, 1.0);
	//}
	//else
	//{
	//	//color = texture(screenTexture, TexCoords);
	//}
}