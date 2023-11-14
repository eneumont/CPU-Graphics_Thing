#version 430

#define INVERT_MASK (1 << 0)
#define GRAYSCALE_MASK (1 << 1)
#define COLORTINT_MASK (1 << 2)
#define GRAIN_MASK (1 << 3)
#define SCANLINE_MASK (1 << 4)
#define CUSTOM_MASK (1 << 5)

in layout(location = 0) vec2 ftexcoord;
out layout(location = 0) vec4 ocolor;

uniform float blend = 1;
uniform uint params = 0;

layout(binding = 0) uniform sampler2D screenTexture;

float random(vec2 st) {
	return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec4 invert(in vec4 color) {
	return vec4(vec3(1) - color.rgb, color.a);
}

vec4 grayscale(in vec4 color) {
	return vec4(vec3((0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b) / 3), color.a);
}

vec4 colorTint(in vec4 color) {
	return color;
}

vec4 grain(in vec4 color) {
	return color;
}

vec4 scanline(in vec4 color) {
	return color;
}

vec4 custom(in vec4 color) {
	return color;
}

void main() {
	vec4 basecolor = texture(screenTexture, ftexcoord);
	vec4 postprocess = basecolor;
	
	// 0001 <-mask
	// 0001 <-params
	if(bool(params & INVERT_MASK)) postprocess = invert(postprocess);
	if(bool(params & GRAYSCALE_MASK)) postprocess = grayscale(postprocess);
	if(bool(params & COLORTINT_MASK)) postprocess = colorTint(postprocess);
	if(bool(params & GRAIN_MASK)) postprocess = grain(postprocess);
	if(bool(params & SCANLINE_MASK)) postprocess = scanline(postprocess);
	if(bool(params & CUSTOM_MASK)) postprocess = custom(postprocess);

	ocolor = mix(basecolor, postprocess, blend);
}