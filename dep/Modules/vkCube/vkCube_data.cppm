module;

export module vkCube_data;
import std;
import vulkan;
import glm;

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
				 std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
				UBO ubo;

				glm::vec3 m_position = glm::vec3(0.0f, 2.0f, 8.0f);
				float m_yaw = 0.0f;
				float m_pitch = 0.0f;

			public:
				vkCube::data::UBO update(const vk::Extent2D& extent) {
#if 1
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
#else
					// Вычисляем направление взгляда из углов
					glm::vec3 forward;
					forward.x = cos(m_yaw) * cos(m_pitch);
					forward.y = sin(m_pitch);
					forward.z = sin(m_yaw) * cos(m_pitch);
					forward = glm::normalize(forward);

					glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
					glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
					glm::vec3 up = glm::cross(right, forward);

					glm::mat4 view = glm::gtc::lookAt(m_position, m_position + forward, up);

					// Модельная матрица – объект находится в центре (можно изменить)
					glm::mat4 model = glm::mat4(1.0f);
					ubo.modelview = view * model;

					// Проекция – без изменений
					float aspect = static_cast<float>(extent.width) / static_cast<float>(extent.height);
					glm::mat4 projection = glm::gtc::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
					ubo.modelviewprojection = projection * ubo.modelview;

					// Матрица нормалей
					glm::mat3 normalMatrix = glm::gtc::transpose(glm::inverse(glm::mat3(ubo.modelview)));
					for (int i = 0; i < 3; ++i) {
						ubo.normal[i] = glm::vec4(normalMatrix[i], 0.0f);
					}

					return ubo;
#endif
				}
		};
	}
}