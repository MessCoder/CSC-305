R"(
#version 330 core
uniform int selection;
uniform vec3 defaultColor;
uniform vec3 selectionColor;

out vec4 color;

void main() {
    if ( selection == gl_PrimitiveID ) {
        color = vec4(selectionColor, 1);
    } else {
        color = vec4(defaultColor, 1);
    }
}
)"
