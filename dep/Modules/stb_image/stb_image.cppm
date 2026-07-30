module;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

export module stb_image;
import std;

namespace stb_image_c_api {
	using ::stbi__context;

	using ::stbi_load;
	using ::stbi_load_from_memory;
	using ::stbi_image_free;
	using ::stbi_write_png;
} // ns stb_image_c_api 

export namespace stb_image {
	struct RawPic {
		public:
			unsigned height;
			unsigned width;
			unsigned channels;
			std::vector<unsigned char> data;
	};

	template<typename T> concept ArrayLike = std::true_type::value;

	void write_png(const std::string& filename, const RawPic& pic) {
		int res = stb_image_c_api::stbi_write_png(
			filename.c_str(), pic.width, pic.height, pic.channels,
			reinterpret_cast<const void *>(pic.data.data()), pic.width * pic.channels
		);
		if (!res) { throw; }
	};

	RawPic load_image(const std::string& filepath) {
		RawPic res;
		int h = 0; int w = 0; int c = 0;
		unsigned char* ptr = stb_image_c_api::stbi_load(filepath.c_str(), &w, &h, &c, 4);
		// stb_image_c_api::stbi_write_png("test.png", w, h, c, ptr, w*c);
		res.height = h;
		res.width = w;
		res.channels = c;
		auto len = res.height * res.width * res.channels;
		std::span<const unsigned char> data(ptr, len);
		res.data.append_range(data);
		stb_image_c_api::stbi_image_free(ptr);
		return res;
	}

	RawPic load_image_from_memory(const ArrayLike auto& image) {
		using value_type = std::remove_cvref_t<decltype(image)>::value_type;
		constexpr std::size_t sz = sizeof(value_type);
		RawPic res;
		auto pd = reinterpret_cast<const unsigned char *>(image.data());
		int ps = image.size() * sz;
		int h = 0; int w = 0; int c = 0;
		unsigned char* ptr = stb_image_c_api::stbi_load_from_memory(pd, ps, &h, &w, &c, 0);
		res.height = h;
		res.width = w;
		res.channels = c;
		auto len = res.height * res.width * res.channels;
		std::span<const unsigned char> data(ptr, len);
		res.data.append_range(data);
		stb_image_c_api::stbi_image_free(ptr);
		return res;
	}
} // stb_image