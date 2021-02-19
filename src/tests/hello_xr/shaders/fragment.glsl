#version 410

in VertexData {
    vec3 PSVertexColor;
    flat int vertID;
} vert;

out vec4 FragColor;

uniform sampler2D atlas;
uniform int length = 265;

uniform bool dodiscard = false;

void main() {

    if (dodiscard && distance(gl_PointCoord, vec2(0.5)) > 0.5) discard;

    vec3 d = min(vert.PSVertexColor, vec3(0));

	int x = vert.vertID % length;
    int y = vert.vertID / length;

    vec2 uv = vec2(x,y) / length;

    float nr = texture(atlas, uv + gl_PointCoord / length).r;
	FragColor = vec4(vert.PSVertexColor * (1-nr), 1);
}
