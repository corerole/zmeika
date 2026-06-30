module;

#define HAS_SPACESHIP_OPERATOR		1

export module flags;
import std;

export namespace flags {
	template<typename T> concept is_enum = std::is_enum_v<T>;

	template<typename T> struct AllFlags {
		using type = std::underlying_type_t<T>;
		type m_mask;
	};
	
	template <typename FlagBitsType> struct FlagTraits {
		static constexpr bool isBitmask = false;
		static constexpr AllFlags<FlagBitsType> allFlags;
	};

	template <is_enum BitType> struct Flags {
		public:
			using BitsType = BitType;
			using values = BitType;
			using MaskType = typename std::underlying_type_t<BitType>;

			// constructors
			constexpr Flags() noexcept : m_mask(0) {}

			constexpr Flags(BitType bit) noexcept : m_mask(static_cast<MaskType>(bit)) {}

			constexpr Flags(Flags<BitType> const& rhs) noexcept = default;

			constexpr explicit Flags(MaskType flags) noexcept : m_mask(flags) {}

			// relational operators
	#if defined( HAS_SPACESHIP_OPERATOR )
			auto operator<=>(Flags<BitType> const&) const = default;
	#else
			constexpr bool operator<(Flags<BitType> const& rhs) const noexcept {
				return m_mask < rhs.m_mask;
			}

			constexpr bool operator<=(Flags<BitType> const& rhs) const noexcept {
				return m_mask <= rhs.m_mask;
			}

			constexpr bool operator>(Flags<BitType> const& rhs) const noexcept {
				return m_mask > rhs.m_mask;
			}

			constexpr bool operator>=(Flags<BitType> const& rhs) const noexcept {
				return m_mask >= rhs.m_mask;
			}

			constexpr bool operator==(Flags<BitType> const& rhs) const noexcept {
				return m_mask == rhs.m_mask;
			}

			constexpr bool operator!=(Flags<BitType> const& rhs) const noexcept {
				return m_mask != rhs.m_mask;
			}
	#endif

			// logical operator
			constexpr bool operator!() const noexcept {
				return !m_mask;
			}

			// bitwise operators
			constexpr Flags<BitType> operator&(Flags<BitType> const& rhs) const noexcept {
				return Flags<BitType>(m_mask & rhs.m_mask);
			}

			constexpr Flags<BitType> operator|(Flags<BitType> const& rhs) const noexcept {
				return Flags<BitType>(m_mask | rhs.m_mask);
			}

			constexpr Flags<BitType> operator^(Flags<BitType> const& rhs) const noexcept {
				return Flags<BitType>(m_mask ^ rhs.m_mask);
			}

			constexpr Flags<BitType> operator~() const noexcept {
				return Flags<BitType>(m_mask ^ FlagTraits<BitType>::allFlags.m_mask);
			}

			// assignment operators
			constexpr Flags<BitType>& operator=(Flags<BitType> const& rhs) noexcept = default;

			constexpr Flags<BitType>& operator|=(Flags<BitType> const& rhs) noexcept {
				m_mask |= rhs.m_mask;
				return *this;
			}

			constexpr Flags<BitType>& operator&=(Flags<BitType> const& rhs) noexcept {
				m_mask &= rhs.m_mask;
				return *this;
			}

			constexpr Flags<BitType>& operator^=(Flags<BitType> const& rhs) noexcept {
				m_mask ^= rhs.m_mask;
				return *this;
			}

			// cast operators
			explicit constexpr operator bool() const noexcept {
				return !!m_mask;
			}

			explicit constexpr operator MaskType() const noexcept {
				return m_mask;
			}

		private:
			MaskType m_mask;
	};
}
#if !defined( HAS_SPACESHIP_OPERATOR )
	// relational operators only needed for pre C++20
	export template <typename BitType>
	constexpr bool operator<(BitType bit, Flags<BitType> const& flags) noexcept {
		return flags.operator>(bit);
	}

	export template <typename BitType>
	constexpr bool operator<=(BitType bit, Flags<BitType> const& flags) noexcept {
		return flags.operator>=(bit);
	}

	export template <typename BitType>
	constexpr bool operator>(BitType bit, Flags<BitType> const& flags) noexcept {
		return flags.operator<(bit);
	}

	export template <typename BitType>
	constexpr bool operator>=(BitType bit, Flags<BitType> const& flags) noexcept {
		return flags.operator<=(bit);
	}

	export template <typename BitType>
	constexpr bool operator==(BitType bit, Flags<BitType> const& flags) noexcept {
		return flags.operator==(bit);
	}

	export template <typename BitType>
	constexpr bool operator!=(BitType bit, Flags<BitType> const& flags) noexcept {
		return flags.operator!=(bit);
	}
#endif

	// bitwise operators
	export template <typename BitType>
	constexpr flags::Flags<BitType> operator&(BitType bit, flags::Flags<BitType> const& flags) noexcept {
		return flags.operator&(bit);
	}

	export template <typename BitType>
	constexpr flags::Flags<BitType> operator|(BitType bit, flags::Flags<BitType> const& flags) noexcept {
		return flags.operator|(bit);
	}

	export template <typename BitType>
	constexpr flags::Flags<BitType> operator^(BitType bit, flags::Flags<BitType> const& flags) noexcept {
		return flags.operator^(bit);
	}

	// bitwise operators on BitType

	// template<typename BitType> concept isSameEnum = ;
	// template <typename BitType, typename std::enable_if<FlagTraits<BitType>::isBitmask, bool>::type = true>
	export template<typename BitType>
	inline constexpr flags::Flags<BitType> operator&(BitType lhs, BitType rhs) noexcept {
		return flags::Flags<BitType>(lhs) & rhs;
	}

	// template <typename BitType, typename std::enable_if<FlagTraits<BitType>::isBitmask, bool>::type = true>
	export template<typename BitType>
	inline constexpr flags::Flags<BitType> operator|(BitType lhs, BitType rhs) noexcept {
		return flags::Flags<BitType>(lhs) | rhs;
	}

	// template <typename BitType, typename std::enable_if<FlagTraits<BitType>::isBitmask, bool>::type = true>
	export template<typename BitType>
	inline constexpr flags::Flags<BitType> operator^(BitType lhs, BitType rhs) noexcept {
		return flags::Flags<BitType>(lhs) ^ rhs;
	}

	// template <typename BitType, typename std::enable_if<FlagTraits<BitType>::isBitmask, bool>::type = true>
	export template<typename BitType>
	inline constexpr flags::Flags<BitType> operator~(BitType bit) noexcept {
		return ~(flags::Flags<BitType>(bit));
	}

