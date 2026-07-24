module;

export module vkCube_shaders_sources;
import std;

namespace vkCube {
	export namespace shaders_sources {

		constexpr std::string_view vert(
			R"(
				#version 450

				layout(set = 0, binding = 0) uniform Matrices {
						mat4 ViewMatrix;
						mat4 ProjectionMatrix;
						vec3 position;
				} CameraUBO;

				layout(location = 0) in vec4 in_position;
				layout(location = 1) in vec4 in_color;
				layout(location = 2) in vec3 in_normal;

				layout(location = 0) out vec4 vVaryingColor;

				const vec3 pos_offset = vec3(0.0, 4.0, 0.0);
				const vec4 lightPos = vec4(2.0, 2.0, 20.0, 0.0);

				void main() {
						mat4 modelMatrix = mat4(1.0);
						modelMatrix[3].xyz = CameraUBO.position - pos_offset;
						mat4 modelviewMatrix = CameraUBO.ViewMatrix * modelMatrix;
						mat4 modelviewprojectionMatrix = CameraUBO.ProjectionMatrix * modelviewMatrix;
						mat3 normalMatrix = transpose(inverse(mat3(modelviewMatrix)));
						gl_Position = modelviewprojectionMatrix * in_position;
						vec3 eyeNormal = normalize(normalMatrix * in_normal);
						vec4 worldPos4 = modelviewMatrix * in_position;
						vec3 worldPos = worldPos4.xyz / worldPos4.w;
						vec3 lightDir = normalize(lightPos.xyz - worldPos);
						float diff = max(0.0, dot(eyeNormal, lightDir));
						vVaryingColor = vec4(in_color.rgb * diff, 1.0);
				}
			)"
		);

		constexpr std::string_view frag(
			R"(
				#version 450

				layout(location = 0) out vec4 f_color;
				layout(location = 0) in vec4 vVaryingColor;

				void main()	{	f_color = vVaryingColor; }
			)"
		);



	}
}