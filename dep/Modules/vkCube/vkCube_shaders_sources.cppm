module;

export module vkCube_shaders_sources;
import std;

constexpr std::string_view vert(
R"(
#version 450

layout(binding = 0, std140) uniform Matrices {
    mat4 modelviewMatrix;
    mat4 modelviewprojectionMatrix;
    mat3 normalMatrix;
} ubo;

layout(location = 0) in vec4 in_position;
layout(location = 2) in vec3 in_normal;
layout(location = 1) in vec4 in_color;

layout(location = 0) out vec4 vVaryingColor;

const vec4 lightPos = vec4(2.0, 2.0, 20.0, 0.0);

void main() {
    gl_Position = ubo.modelviewprojectionMatrix * in_position;
    vec3 eyeNormal = normalize(ubo.normalMatrix * in_normal);
    vec4 worldPos4 = ubo.modelviewMatrix * in_position;
    vec3 worldPos = worldPos4.xyz / worldPos4.w;
    vec3 lightDir = normalize(lightPos.xyz - worldPos);
    float diff = max(0.0, dot(eyeNormal, lightDir));
    vVaryingColor = vec4(in_color.rgb * diff, 1.0);
}
)");

constexpr std::string_view frag(
R"(
#version 420

layout(location = 0) out vec4 f_color;
layout(location = 0) in vec4 vVaryingColor;

void main()
{
    f_color = vVaryingColor;
}
)");

namespace vkCube {
  export namespace shaders_sources {
    using ::frag;
    using ::vert;
  }
}