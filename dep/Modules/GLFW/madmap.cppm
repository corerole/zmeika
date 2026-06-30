module;

export module madmap;
import std;

export namespace madmap {
	template<typename T> concept is_enum = std::is_enum_v<T>;
	template<is_enum T> constexpr std::size_t get_size() noexcept {
			return std::numeric_limits<std::underlying_type_t<T>>::max();
	};

	template<is_enum key_type,	typename value_type, std::size_t nKeys> struct madmap {
		static_assert(nKeys > 0);

		private:
			using holder_type = std::array<value_type, nKeys>;
			using size_type = std::size_t;

		private:
			constexpr size_type to_index(key_type x) const noexcept {
				return static_cast<std::size_t>(std::to_underlying(x));
			}

		public:
			constexpr value_type& operator[](key_type x) noexcept {
				return buckets[to_index(x)];
			}

			constexpr const value_type& operator[](key_type x) const noexcept {
				return buckets[to_index(x)];
			}

		public:
			constexpr madmap(std::initializer_list<std::pair<key_type, value_type>> init) {
				for (auto&& [k, v] : init) {
					buckets[to_index(k)] = v;
				}
			}

		private:
			holder_type buckets{};

		public:
			using iterator = holder_type::iterator;
			using const_iterator = holder_type::const_iterator;


		public:
			constexpr iterator find(key_type x) noexcept {
				auto&& it = *this;
				return iterator(&(it[x]));
			}

			constexpr const_iterator find(key_type x) const noexcept {
				auto&& it = *this;
				return const_iterator(&(it[x]));
			}

		public:	
			constexpr iterator begin() noexcept {
				return buckets.begin();
			}

			constexpr const_iterator begin() const noexcept {
				return buckets.cbegin();
			}

			constexpr iterator end() noexcept {
				return buckets.cend();
			}

			constexpr const_iterator end() const noexcept {
				return buckets.cend();
			}

			constexpr size_type size() const noexcept { return nKeys; }
	};
}