module;

export module CameraUBO;
import std;
import glm;
import vulkan;
import vulkan_helpers;

namespace {
	struct CameraUBO_s {
		public:
			glm::mat4 view;
			glm::mat4 perspective;
			glm::vec3 position;
	};

	vk::raii::Buffer get_CameraUBO_Buffer(const vk::raii::Device& device) {
		vk::BufferCreateInfo CameraBufferInfo{};
		constexpr std::uint64_t camera_matrices_size = sizeof(CameraUBO_s);
		CameraBufferInfo.size = camera_matrices_size;
		CameraBufferInfo.usage = vk::BufferUsageFlagBits::eUniformBuffer;
		CameraBufferInfo.sharingMode = vk::SharingMode::eExclusive;
		return vk::raii::Buffer(device, CameraBufferInfo);
	}

	vk::raii::DescriptorPool get_CameraUBO_DescriptorPool(const vk::raii::Device& logical_device) {
		vk::DescriptorType dcst = vk::DescriptorType::eUniformBuffer;
		unsigned descriptors_count = 1;
		vk::DescriptorPoolSize dps(dcst, descriptors_count);
		vk::DescriptorPoolCreateFlags flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet; // { FREE_DESCRIPTOR_SET_BIT };
		unsigned MaxSets = 1;
		std::array<vk::DescriptorPoolSize, 1> poolSizes_ = { dps };
		vk::DescriptorPoolCreateInfo dci(flags, MaxSets, poolSizes_);
		return vk::raii::DescriptorPool(logical_device, dci);
	}

	vk::raii::DescriptorSetLayout get_CameraUBO_DescriptorSetLayout(const vk::raii::Device& Device) {
		std::array<vk::DescriptorSetLayoutBinding, 1> layouts;
		layouts[0].binding = 0;
		layouts[0].descriptorCount = 1;
		layouts[0].descriptorType = vk::DescriptorType::eUniformBuffer;
		layouts[0].pImmutableSamplers = nullptr;
		layouts[0].stageFlags = vk::ShaderStageFlagBits::eVertex;

		vk::DescriptorSetLayoutCreateInfo descSetLayoutCreateInfo({}, layouts);

		return vk::raii::DescriptorSetLayout(Device, descSetLayoutCreateInfo);
	}

	vk::raii::DescriptorSet get_CameraUBO_DescriptorSet(
		const vk::raii::Device& logical_device,
		const vk::raii::DescriptorPool& descPool,
		const vk::raii::DescriptorSetLayout& descSetLayout
	) {
		std::array<vk::DescriptorSetLayout, 1> ls = { *descSetLayout };
		vk::DescriptorSetAllocateInfo dsai(descPool, ls);
		auto desc_sets = logical_device.allocateDescriptorSets(dsai);
		return vk::raii::DescriptorSet(std::move(desc_sets[0]));
	}

	std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> get_CameraUBO_BufferAndDeviceMemory(
		const vk::raii::Device& device,
		const vk::raii::PhysicalDevice& physicalDevice,
		vk::raii::Buffer&& buffer
	) {
		auto uboMemReqs = buffer.getMemoryRequirements();
		vk::MemoryAllocateInfo uboAlloc{};
		uboAlloc.allocationSize = uboMemReqs.size;
		uboAlloc.memoryTypeIndex = vk::supp::findMemoryType(
			uboMemReqs.memoryTypeBits,
			vk::MemoryPropertyFlagBits::eHostVisible |
			vk::MemoryPropertyFlagBits::eHostCoherent,
			physicalDevice
		);

		vk::raii::DeviceMemory uboBufferMemory(device, uboAlloc);
		buffer.bindMemory(uboBufferMemory, 0);
		return std::pair(std::forward<decltype(buffer)>(buffer), std::forward<decltype(uboBufferMemory)>(std::move(uboBufferMemory)));
	}

} // anon ns

export namespace CameraUBO {
	struct GazeDirection final {
		static constexpr const float PITCH_LIMIT = glm::radians(89.9f);
		private:
			float m_yaw;
			float m_pitch;

		public:
			constexpr glm::vec3 GetForwardVec3() const noexcept {
				glm::vec3 forward;
				forward.x = std::cos(m_yaw) * std::cos(m_pitch);
				forward.y = std::sin(m_pitch);
				forward.z = std::sin(m_yaw) * std::cos(m_pitch);
				forward = glm::normalize(forward);
				return forward;
			}

			constexpr void update_angles_by_delta(const std::pair<float, float>& dxy) noexcept {
				auto&& [dx, dy] = dxy;
				m_yaw += glm::radians(dx);
				m_pitch += glm::radians(dy);
				m_pitch = glm::clamp(m_pitch, -PITCH_LIMIT, PITCH_LIMIT);
			}

			constexpr std::pair<float, float> get_YP() const noexcept { return {m_yaw, m_pitch}; }

		public:
			constexpr GazeDirection(float yaw = 1.0f, float pitch = 1.0f) : m_yaw(yaw), m_pitch(pitch) {}
	};

	using WorldUp = glm::vec3;
	using PositionCoords = glm::vec3;
	
	struct Position {
		private:
			PositionCoords m_position;

		public:
			constexpr void update_position_by_delta(const glm::vec3& pos_delta) noexcept { m_position += pos_delta;	}
			constexpr void update_position_with_gaze_direction_by_delta(const GazeDirection& gd, const PositionCoords& pc_delta, const WorldUp& wu) noexcept {
				auto&& forward = gd.GetForwardVec3();
				auto&& worldUp = wu;
				glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
				glm::vec3 delta = right * pc_delta.x + forward * pc_delta.z + worldUp * pc_delta.y;
				update_position_by_delta(delta);
			}
			constexpr const glm::vec3& get_position() const { return m_position; }

		public:
			constexpr Position() noexcept = default;
			constexpr Position(float x, float y, float z) noexcept : m_position(x, y, z) {}
			constexpr Position(PositionCoords pc) noexcept : m_position(pc) {}
	};

	struct CameraPosition final : Position {
		using Position::Position;
		constexpr CameraPosition() noexcept = default;
		constexpr CameraPosition(Position pos) : Position(pos) {}
	};

	using ViewMatrix = glm::mat4;
	constexpr ViewMatrix get_ViewMatrix(const GazeDirection& gd, const CameraPosition& pos, const WorldUp& wl) noexcept {
		auto&& forward = gd.GetForwardVec3();
		auto&& worldUp = wl;
		auto&& m_position = pos.get_position();
		glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
		glm::vec3 up = glm::cross(right, forward);
		auto view = glm::gtc::lookAt(m_position, m_position + forward, up);
		return view;
	}

	using ModelMatrix = glm::mat4;
	using ModelViewMatrix = glm::mat4;
	constexpr ModelViewMatrix get_ModelView(const ViewMatrix& vm, const ModelMatrix& mm) noexcept {
		return vm * mm;
	}

	using NormalMatrix = glm::mat3;
	constexpr NormalMatrix get_NormalMatrix(const ModelViewMatrix& mvm) noexcept {
		return glm::gtc::transpose(glm::inverse(glm::mat3(mvm)));
	}

	template<typename T> concept AspectRatioLike = requires(const T & ar) { { ar.get_Ratio() } -> std::convertible_to<float>; };

	using PerspectiveMatrix = glm::mat4;
	constexpr PerspectiveMatrix get_PerspectiveMatrix(std::convertible_to<float> auto fov, const AspectRatioLike auto& ar) {
#if 0
		float fov_ = 0;
		if constexpr (std::same_as<decltype(fov), float>) {
			fov_ = fov;
		}	else {
			fov_ = static_cast<float>(fov);
		}
#else
		float fov_ = fov;
#endif
		
		float aspect = ar.get_Ratio();
		constexpr float near = 0.1f;
		constexpr float far = 1000.0f;
		return glm::gtc::perspective(glm::radians(fov_), aspect, near, far);
	}

#if 0
	constexpr UBO make_UBO(const ViewMatrix& vm, const PerspectiveMatrix& pm) noexcept {
		constexpr ModelMatrix model(1.0f);
		auto mvm = get_ModelView(vm, model);
		auto mvp = mvm * pm;
		auto norms = get_NormalMatrix(mvm);
		return UBO {
			.modelview = mvm,
			.modelviewprojection = mvp,
			.normal = {
					glm::vec4(norms[0], 0.0f), glm::vec4(norms[1], 0.0f), glm::vec4(norms[2], 0.0f)
			},
		};
	}
#endif
	struct AR {
		private:
			float h;
			float w;

		public:
			constexpr void set_hw(int nh, int nw) noexcept { h = nh, w = nw; }
			constexpr float get_Ratio() const noexcept { return w / h; }

		public:
			constexpr AR(float h, float w) : h(h), w(w) {}
	};

	constexpr Position pos_(0.0f, 1.0f, 0.0f);

	struct CameraUBO final {
		static constexpr const WorldUp worldUp{ 0.0f, 1.0f, 0.0f };
		static constexpr const float fov{ 75.0f };
		static constexpr CameraPosition pos = pos_;
		private:
			GazeDirection gd;
			AR ar;

		public:
			constexpr std::pair<ViewMatrix, PerspectiveMatrix> get_Matrices() const noexcept {
				ViewMatrix vm = get_ViewMatrix(gd, pos, worldUp);
				PerspectiveMatrix pm = get_PerspectiveMatrix(fov, ar);
				return std::pair(std::move(vm), std::move(pm));
			}

			constexpr auto get_Gaze_Direction() const noexcept { return gd; }

		public:
			constexpr void update_acpect_ratio(int h, int w) noexcept {
				ar.set_hw(h, w);
			}

			constexpr void update_angles_by_delta(const std::pair<float, float>& dxy) noexcept {
				gd.update_angles_by_delta(dxy);
			}

#if 0
			constexpr void update_position_by_delta(const PositionCoords& delta) noexcept {
				pos.update_position_with_gaze_direction_by_delta(gd, delta, worldUp);
			}
#endif

		public:
			CameraUBO(const AR& ar, const GazeDirection& gd = {}) : gd(gd), ar(ar) {}
	};

	struct vkUBO_T {
		private:
			CameraUBO camera;
			vk::raii::DescriptorPool desc_pool;
			vk::raii::DescriptorSetLayout desc_layout;
			vk::raii::DescriptorSet desc_set;
			std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> ubo_buffer_and_mem;

		public:
			vkUBO_T(
				const vk::Extent2D& extent,
				const vk::raii::Device& logical_device,
				const vk::raii::PhysicalDevice& physical_device
			)
				: camera({static_cast<float>(extent.height), static_cast<float>(extent.width)}, {})
				, desc_pool(get_CameraUBO_DescriptorPool(logical_device))
				, desc_layout(get_CameraUBO_DescriptorSetLayout(logical_device))
				, desc_set(get_CameraUBO_DescriptorSet(logical_device, desc_pool, desc_layout))
				, ubo_buffer_and_mem(get_CameraUBO_BufferAndDeviceMemory(logical_device, physical_device, get_CameraUBO_Buffer(logical_device)))
			{
				constexpr unsigned ubo_size = sizeof(CameraUBO_s);

				vk::DescriptorBufferInfo bufferInfo{};
				bufferInfo.buffer = *ubo_buffer_and_mem.first;
				bufferInfo.offset = 0;
				bufferInfo.range = ubo_size;

				vk::WriteDescriptorSet writeSet{};
				writeSet.dstSet = *desc_set;
				writeSet.dstBinding = 0;
				writeSet.dstArrayElement = 0;
				writeSet.descriptorCount = 1;
				writeSet.descriptorType = vk::DescriptorType::eUniformBuffer;
				writeSet.pBufferInfo = &bufferInfo;

				logical_device.updateDescriptorSets(writeSet, {});
			}

			const vk::raii::DescriptorSet& get_DescriptorSet() const {
				return desc_set;
			}

			const vk::raii::DescriptorSetLayout& get_DescriptorSetLayout() const {
				return desc_layout;
			}

		public:
			void update_extent(const vk::Extent2D& extent) {
				camera.update_acpect_ratio(extent.height, extent.width);
			}

			void update_angles_by_delta(const std::pair<float, float>& m_pos) {
				camera.update_angles_by_delta(m_pos);
			}

#if 0
			void update_position_by_delta(float dx, float dy, float dz) {
				camera.update_position_by_delta({ dx, dy, dz });
			}
#endif

			void update_device_buffer(float dx, float dy, float dz) {
				constexpr glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
				auto pos_delta = glm::vec3(dx, dy, dz);
				auto&& [view, persp] = camera.get_Matrices();
				auto forward = camera.get_Gaze_Direction().GetForwardVec3();
				static glm::vec3 current_pos(0, 0, 0);
				
				glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
				glm::vec3 delta = right * dx + forward * dz + worldUp * dy;
				current_pos -= delta;

				CameraUBO_s ubo(view, persp, current_pos);

				void* uboPtr = ubo_buffer_and_mem.second.mapMemory(0, sizeof(ubo));
				std::memcpy(uboPtr, &ubo, sizeof(ubo));
				ubo_buffer_and_mem.second.unmapMemory();
			}
	};
} // ns UBO