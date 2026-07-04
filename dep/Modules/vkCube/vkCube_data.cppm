module;

export module vkCube_data;
import std;
import vulkan;
import glfw;
import glm;

#if 0
template<std::floating_point value_type, value_type SENSITIVITY, int INITAL_X, int INITAL_Y>
std::pair<value_type, value_type> get_relevant_angles(int cx, int cy) {
	thread_local static int px = INITAL_X;
	thread_local static int py = INITAL_X;

	auto dx = cx - px;
	auto dy = cy - py;

	value_type deltaYaw = dx * SENSITIVITY;
	value_type deltaPitch = dy * SENSITIVITY;

	return { deltaYaw, deltaPitch };
}
#endif 

namespace vkCube {
	export namespace data {
		struct UBO {
			public:
				glm::mat4 modelview;
				glm::mat4 modelviewprojection;
				glm::vec4 normal[3];
		};

		struct UBO_obj {
			private:
				static constexpr const float PITCH_LIMIT = glm::radians(89.9f);

			private:
				// std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
				UBO ubo;

				glm::vec3 m_position = glm::vec3(0.0f, 2.0f, 8.0f);
				float m_yaw = 1.0f;
				float m_pitch = 1.0f;
				float height = 1.0f;
				float width = 1.0f;

			public:
				void update_hw(unsigned new_height, unsigned new_width) {
					height = new_height;
					width = new_width;
				}

				void update_mouse_pos(const std::pair<float, float>& dxy) {
					auto&& [dx, dy] = dxy;
					m_yaw += glm::radians(dx);
					m_pitch += glm::radians(dy);
					
					m_pitch = glm::clamp(m_pitch, -PITCH_LIMIT, PITCH_LIMIT);

					glm::vec3 forward;
					forward.x = cos(m_yaw) * cos(m_pitch);
					forward.y = sin(m_pitch);
					forward.z = sin(m_yaw) * cos(m_pitch);
					forward = glm::normalize(forward);

					glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
					glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
					glm::vec3 up = glm::cross(right, forward);

					glm::mat4 view = glm::gtc::lookAt(m_position, m_position + forward, up);

					glm::mat4 model = glm::mat4(1.0f);
					ubo.modelview = view * model;

					auto aspect = width / height;
					glm::mat4 projection = glm::gtc::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
					ubo.modelviewprojection = projection * ubo.modelview;

					glm::mat3 normalMatrix = glm::gtc::transpose(glm::inverse(glm::mat3(ubo.modelview)));
					for (int i = 0; i < 3; ++i) {
						ubo.normal[i] = glm::vec4(normalMatrix[i], 0.0f);
					}
				}

				vkCube::data::UBO get_ubo() {
					return ubo;
				}
		};
	}
}

#if 0
void foo() {
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
	float t = elapsed / 10.0f;

	ubo.modelview = glm::mat4(1.0f);
	ubo.modelview = glm::gtc::translate(ubo.modelview, glm::vec3(0.0f, 0.0f, -8.0f));
	ubo.modelview = glm::gtc::rotate(ubo.modelview, glm::radians(45.0f + (0.25f * t)), glm::vec3(1.0f, 0.0f, 0.0f));
	ubo.modelview = glm::gtc::rotate(ubo.modelview, glm::radians(45.0f - (0.5f * t)), glm::vec3(0.0f, 1.0f, 0.0f));
	ubo.modelview = glm::gtc::rotate(ubo.modelview, glm::radians(10.0f + (0.15f * t)), glm::vec3(0.0f, 0.0f, 1.0f));

	float aspect = static_cast<float>(extent.width) / static_cast<float>(extent.height);
	glm::mat4 projection = glm::gtc::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

	ubo.modelviewprojection = projection * ubo.modelview;

	glm::mat3 normalMatrix = glm::gtc::transpose(glm::inverse(glm::mat3(ubo.modelview)));
	for (int i = 0; i < 3; ++i) {
		ubo.normal[i] = glm::vec4(normalMatrix[i], 0.0f);
	}
	return ubo;
}
#endif
