module;

export module OSD;

import std;
import glm;

export namespace OSD {

#if 0
	enum class VirtualSpaceMode {
		OneFrame = 0,
		InfiniteSpace = 1,
		InfiniteVerticalTape = 2,
		InfiniteHoryzontalTape = 3,
		ScreenMatrix = 4,
		ScreenArray = 5
	};

	template<typename T> using Matrix = std::vector<std::vector<T>>;

	struct PositionedObject {
		private:
			Object object;

		public:

	};

	struct VirtualScreen {
		private:
			std::vector<PositionedObject> objects;
		public:

	};

	template<VirtualSpaceMode Mode> struct VirtualSpace {};

	template<> struct VirtualSpace<VirtualSpaceMode::ScreenMatrix> { 
		private:
			Matrix<VirtualScreen> vs;

		public:
			void draw_screen(unsigned n) {

			}
	};

	template<VirtualSpaceMode Mode> struct OSD {
		private:
			VirtualSpace<Mode> vs;

		public:
			void add_object(Object&& obj) {};
			void draw() {

			}; 
	};
#endif
} // OSD ns