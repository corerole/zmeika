module;

export module glfw_enums;
import std;
import flags;

enum class AspectRatioFormats {
	Square,
	PAL,
	SXGA,
	Classic35mm,
	Widescreen,
	Widescreen16_10,
	Cinemascope,
	AmericanWide,
	EuropeanWide,
	MobilePortrait,
	IMAX
};

enum class Orientation : bool {
	Portait = false,
	Landscape = true,
};
					 
enum class FrameActionState : bool {
	disabled = false,
	enabled = true
};

enum class CursorState : unsigned {
	normal		= 0x00034001,
	hidden		= 0x00034002,
	disabled	= 0x00034003,
	captured	= 0x00034004
};

enum class CursorRawInputState : bool {
	disabled = false,
	enabled = true
};

enum class CharMods : unsigned {
	shift = 0x0001,
	control = 0x0002,
	alt = 0x0004,
	super = 0x0008,
	caps_lock = 0x0010,
	num_lock = 0x0020 // = 0x0012
};

template<> struct flags::FlagTraits<CharMods> {
	static constexpr bool isBitmask = true;
	static constexpr AllFlags<CharMods> allFlags{ .m_mask = 0x3F }; // 0x1F
};

enum class KeyState {
	release = 0,
	press = 1,
	repeat = 2,
	stick = 3
};

export namespace glfw_enums {
		enum class Key : int {
			NULL,	/* or Unknown */ // my
			vA,
			vB,
			vC,
			vD,
			vE,
			vF,
			vG,
			vH,
			vI,
			vJ,
			vK,
			vL,
			vM,
			vN,
			vO,
			vP,
			vQ,
			vR,
			vS,
			vT,
			vU,
			vV,
			vW,
			vX,
			vY,
			vZ,
			v1_and_Bang,
			v2_and_At,
			v3_and_Hash,
			v4_and_Dollar,
			v5_and_Percent,
			v6_and_Caret,
			v7_and_Ampersand,
			v8_and_Star,
			v9_and_Left_Bracket,
			v0_and_Right_Brackert,
			vReturnEnter,
			vEscape,
			vDelete,
			vTab,
			vSpaceBar,
			vDash_and_underscore,
			vEquals_and_Plus,
			vLeft_Brace,
			vRight_Brace,
			vBackslash_and_Pipe,
			vNonUS_Slash_and_Tilde, // orig   
			vSemiColon_and_Colon,
			vApostrophe_and_Double_Quotation_Mark,
			vGrave_Accent_and_Tilde,
			vComma_and_LessThen,
			vPeriod_and_GreaterThen,
			vForwardSlash_and_QuestionMark,
			vCapsLock,
			vF1,
			vF2,
			vF3,
			vF4,
			vF5,
			vF6,
			vF7,
			vF8,
			vF9,
			vF10,
			vF11,
			vF12,
			vPrintScreen, //  
			vScrollLock,
			vPause, //  
			vInsert,
			vHome,
			vPageUp,
			vDeleteForward,
			vEnd,
			vPageDown,
			vRightArrow,
			vLeftArrow,
			vDownArrow,
			vUpArrow,
			vNumLock_and_Clear, // 
			vForwardSlash,
			vStar,
			vDash,
			vPlus,
			vEnter,
			v1_and_End,
			v2_and_Down_Arrow,
			v3_and_PageDn,
			v4_and_Left_Arrow,
			v5_,
			v6_and_Right_Arrow,
			v7_and_Home,
			v8_and_Up_Arrow,
			v9_and_PageUp,
			v0_and_Insert,
			vPeriod_and_Delete,
			vNonUS_Backslash_and_Pipe,
			vApplication,
			vPower,
			vEquals,
			vF13,
			vF14,
			vF15,
			vF16,
			vF17,
			vF18,
			vF19,
			vF20,
			vF21,
			vF22,
			vF23,
			vF24,
			vComma,
			vInternational1,
			vInternational2,
			vInternational3,
			vInternational4,
			vInternational5,
			vInternational6,
			vLANG1,
			vLANG2,
			vLANG3,
			vLANG4,
			vLANG5,
			vLeftControl,
			vLeftShift,
			vLeftAlt,
			vLeftGUI,
			vRightControl,
			vRightShift,
			vRightAlt,
			vRightGUI,
			vScanNextTrack,
			vScanPreviosTrack,
			vStop,
			vPlay_Pause,
			vMute,
			vVolumeIncrement,
			vVolumeDecrement,
			vAL_Consumer_Control_Configuration,
			vAL_EmailReader,
			vAL_Calculator,
			vAL_LocalMachineBrowser,
			vAC_Search,
			vAC_Home,
			vAC_Back,
			vAC_Forward,
			vAC_Stop,
			vAC_Refresh,
			vAC_Bookmarks,

			vLMB,
			vMMB,
			vRMB,
			v1MB,
			v2MB
		};

#if 1
		using KeyStateMap = std::unordered_map<Key, KeyState>;
		KeyStateMap inital_key_state = {
			{ Key::NULL, KeyState::release },
			{ Key::vA, KeyState::release },
			{ Key::vB, KeyState::release },
			{ Key::vC, KeyState::release },
			{ Key::vD, KeyState::release },
			{ Key::vE, KeyState::release },
			{ Key::vF, KeyState::release },
			{ Key::vG, KeyState::release },
			{ Key::vH, KeyState::release },
			{ Key::vI, KeyState::release },
			{ Key::vJ, KeyState::release },
			{ Key::vK, KeyState::release },
			{ Key::vL, KeyState::release },
			{ Key::vM, KeyState::release },
			{ Key::vN, KeyState::release },
			{ Key::vO, KeyState::release },
			{ Key::vP, KeyState::release },
			{ Key::vQ, KeyState::release },
			{ Key::vR, KeyState::release },
			{ Key::vS, KeyState::release },
			{ Key::vT, KeyState::release },
			{ Key::vU, KeyState::release },
			{ Key::vV, KeyState::release },
			{ Key::vW, KeyState::release },
			{ Key::vX, KeyState::release },
			{ Key::vY, KeyState::release },
			{ Key::vZ, KeyState::release },
			{ Key::v1_and_Bang, KeyState::release },
			{ Key::v2_and_At, KeyState::release },
			{ Key::v3_and_Hash, KeyState::release },
			{ Key::v4_and_Dollar, KeyState::release },
			{ Key::v5_and_Percent, KeyState::release },
			{ Key::v6_and_Caret, KeyState::release },
			{ Key::v7_and_Ampersand, KeyState::release },
			{ Key::v8_and_Star, KeyState::release },
			{ Key::v9_and_Left_Bracket, KeyState::release },
			{ Key::v0_and_Right_Brackert, KeyState::release },
			{ Key::vReturnEnter, KeyState::release },
			{ Key::vEscape, KeyState::release },
			{ Key::vDelete, KeyState::release },
			{ Key::vTab, KeyState::release },
			{ Key::vSpaceBar, KeyState::release },
			{ Key::vDash_and_underscore, KeyState::release },
			{ Key::vEquals_and_Plus, KeyState::release },
			{ Key::vLeft_Brace, KeyState::release },
			{ Key::vRight_Brace, KeyState::release },
			{ Key::vBackslash_and_Pipe, KeyState::release },
			{ Key::vNonUS_Slash_and_Tilde, KeyState::release }, // orig, KeyState::release 
			{ Key::vSemiColon_and_Colon, KeyState::release },
			{ Key::vApostrophe_and_Double_Quotation_Mark, KeyState::release },
			{ Key::vGrave_Accent_and_Tilde, KeyState::release },
			{ Key::vComma_and_LessThen, KeyState::release },
			{ Key::vPeriod_and_GreaterThen, KeyState::release },
			{ Key::vForwardSlash_and_QuestionMark, KeyState::release },
			{ Key::vCapsLock, KeyState::release },
			{ Key::vF1, KeyState::release },
			{ Key::vF2, KeyState::release },
			{ Key::vF3, KeyState::release },
			{ Key::vF4, KeyState::release },
			{ Key::vF5, KeyState::release },
			{ Key::vF6, KeyState::release },
			{ Key::vF7, KeyState::release },
			{ Key::vF8, KeyState::release },
			{ Key::vF9, KeyState::release },
			{ Key::vF10, KeyState::release },
			{ Key::vF11, KeyState::release },
			{ Key::vF12, KeyState::release },
			{ Key::vPrintScreen,  KeyState::release },
			{ Key::vScrollLock, KeyState::release },
			{ Key::vPause, KeyState::release },
			{ Key::vInsert, KeyState::release },
			{ Key::vHome, KeyState::release },
			{ Key::vPageUp, KeyState::release },
			{ Key::vDeleteForward, KeyState::release },
			{ Key::vEnd, KeyState::release },
			{ Key::vPageDown, KeyState::release },
			{ Key::vRightArrow, KeyState::release },
			{ Key::vLeftArrow, KeyState::release },
			{ Key::vDownArrow, KeyState::release },
			{ Key::vUpArrow, KeyState::release },
			{ Key::vNumLock_and_Clear, KeyState::release },
			{ Key::vForwardSlash, KeyState::release },
			{ Key::vStar, KeyState::release },
			{ Key::vDash, KeyState::release },
			{ Key::vPlus, KeyState::release },
			{ Key::vEnter, KeyState::release },
			{ Key::v1_and_End, KeyState::release },
			{ Key::v2_and_Down_Arrow, KeyState::release },
			{ Key::v3_and_PageDn, KeyState::release },
			{ Key::v4_and_Left_Arrow, KeyState::release },
			{ Key::v5_, KeyState::release },
			{ Key::v6_and_Right_Arrow, KeyState::release },
			{ Key::v7_and_Home, KeyState::release },
			{ Key::v8_and_Up_Arrow, KeyState::release },
			{ Key::v9_and_PageUp, KeyState::release },
			{ Key::v0_and_Insert, KeyState::release },
			{ Key::vPeriod_and_Delete, KeyState::release },
			{ Key::vNonUS_Backslash_and_Pipe, KeyState::release },
			{ Key::vApplication, KeyState::release },
			{ Key::vPower, KeyState::release },
			{ Key::vEquals, KeyState::release },
			{ Key::vF13, KeyState::release },
			{ Key::vF14, KeyState::release },
			{ Key::vF15, KeyState::release },
			{ Key::vF16, KeyState::release },
			{ Key::vF17, KeyState::release },
			{ Key::vF18, KeyState::release },
			{ Key::vF19, KeyState::release },
			{ Key::vF20, KeyState::release },
			{ Key::vF21, KeyState::release },
			{ Key::vF22, KeyState::release },
			{ Key::vF23, KeyState::release },
			{ Key::vF24, KeyState::release },
			{ Key::vComma, KeyState::release },
			{ Key::vInternational1, KeyState::release },
			{ Key::vInternational2, KeyState::release },
			{ Key::vInternational3, KeyState::release },
			{ Key::vInternational4, KeyState::release },
			{ Key::vInternational5, KeyState::release },
			{ Key::vInternational6, KeyState::release },
			{ Key::vLANG1, KeyState::release },
			{ Key::vLANG2, KeyState::release }, 
			{ Key::vLANG3, KeyState::release },
			{ Key::vLANG4, KeyState::release },
			{ Key::vLANG5, KeyState::release },
			{ Key::vLeftControl, KeyState::release },
			{ Key::vLeftShift, KeyState::release },
			{ Key::vLeftAlt, KeyState::release },
			{ Key::vLeftGUI, KeyState::release },
			{ Key::vRightControl, KeyState::release },
			{ Key::vRightShift, KeyState::release },
			{ Key::vRightAlt, KeyState::release },
			{ Key::vRightGUI, KeyState::release },
			{ Key::vScanNextTrack, KeyState::release },
			{ Key::vScanPreviosTrack, KeyState::release },
			{ Key::vStop, KeyState::release },
			{ Key::vPlay_Pause, KeyState::release },
			{ Key::vMute, KeyState::release },
			{ Key::vVolumeIncrement, KeyState::release },
			{ Key::vVolumeDecrement, KeyState::release },
			{ Key::vAL_Consumer_Control_Configuration, KeyState::release },
			{ Key::vAL_EmailReader, KeyState::release },
			{ Key::vAL_Calculator, KeyState::release },
			{ Key::vAL_LocalMachineBrowser, KeyState::release },
			{ Key::vAC_Search, KeyState::release },
			{ Key::vAC_Home, KeyState::release },
			{ Key::vAC_Back, KeyState::release },
			{ Key::vAC_Forward, KeyState::release },
			{ Key::vAC_Stop, KeyState::release },
			{ Key::vAC_Refresh, KeyState::release },
			{ Key::vAC_Bookmarks, KeyState::release },
			{ Key::vLMB, KeyState::release },
			{ Key::vMMB, KeyState::release },
			{ Key::vRMB, KeyState::release },
			{ Key::v1MB, KeyState::release },
			{ Key::v2MB, KeyState::release }
		};
#endif

#if 1
		using AspectRatioValueType = float;
		using AspectRaitoFormatsMapType = std::unordered_map<AspectRatioFormats, std::pair<AspectRatioValueType, AspectRatioValueType>>;

		AspectRaitoFormatsMapType AspectRatioStandardFormats = {
				{ AspectRatioFormats::Square,							{ 1.0,	1.0 } },
				{ AspectRatioFormats::PAL,								{ 4.0,	3.0 } },
				{ AspectRatioFormats::SXGA,								{ 5.0,	4.0 } },
				{ AspectRatioFormats::Classic35mm,				{ 5.0,	4.0 } },
				{ AspectRatioFormats::Widescreen,					{ 16.0, 9.0 } },
				{ AspectRatioFormats::Widescreen16_10,		{ 16.0,	10.0} },
				{ AspectRatioFormats::Cinemascope,				{ 21.0, 9.0 } },
				{ AspectRatioFormats::AmericanWide,				{ 1.85, 1.0 } },
				{ AspectRatioFormats::EuropeanWide,				{ 1.66, 1.0 } },
				{ AspectRatioFormats::MobilePortrait,			{ 9.0,	16.0}	},
				{ AspectRatioFormats::IMAX,								{ 1.43, 1.0 } }
		};

		template<AspectRatioFormats F>
		constexpr std::pair<AspectRatioValueType, AspectRatioValueType> get_AspectRatioStandardFormats() {
			if constexpr (F == AspectRatioFormats::Square) { return 						{ 1.0,	1.0 }; }
			if constexpr (F == AspectRatioFormats::PAL) { return								{ 4.0,	3.0 }; }
			if constexpr (F == AspectRatioFormats::SXGA) { return								{ 5.0,	4.0 }; }
			if constexpr (F == AspectRatioFormats::Classic35mm) { return				{ 5.0,	4.0 }; }
			if constexpr (F == AspectRatioFormats::Widescreen) { return					{ 16.0, 9.0 }; }
			if constexpr (F == AspectRatioFormats::Widescreen16_10) { return		{ 16.0,	10.0}; }
			if constexpr (F == AspectRatioFormats::Cinemascope) { return				{ 21.0, 9.0 }; }
			if constexpr (F == AspectRatioFormats::AmericanWide) { return				{ 1.85, 1.0 }; }
			if constexpr (F == AspectRatioFormats::EuropeanWide) { return				{ 1.66, 1.0 }; }
			if constexpr (F == AspectRatioFormats::MobilePortrait) { return			{ 9.0,	16.0}; }
			if constexpr (F == AspectRatioFormats::IMAX) { return								{ 1.43, 1.0 }; }
		}

		constexpr std::pair<AspectRatioValueType, AspectRatioValueType> get_AspectRatioStandardFormats(AspectRatioFormats F) {
			if (F == AspectRatioFormats::Square) { return 						{ 1.0,	1.0 }; }
			if (F == AspectRatioFormats::PAL) { return								{ 4.0,	3.0 }; }
			if (F == AspectRatioFormats::SXGA) { return								{ 5.0,	4.0 }; }
			if (F == AspectRatioFormats::Classic35mm) { return				{ 5.0,	4.0 }; }
			if (F == AspectRatioFormats::Widescreen) { return					{ 16.0, 9.0 }; }
			if (F == AspectRatioFormats::Widescreen16_10) { return		{ 16.0,	10.0}; }
			if (F == AspectRatioFormats::Cinemascope) { return				{ 21.0, 9.0 }; }
			if (F == AspectRatioFormats::AmericanWide) { return				{ 1.85, 1.0 }; }
			if (F == AspectRatioFormats::EuropeanWide) { return				{ 1.66, 1.0 }; }
			if (F == AspectRatioFormats::MobilePortrait) { return			{ 9.0,	16.0}; }
			if (F == AspectRatioFormats::IMAX) { return								{ 1.43, 1.0 }; }
			return { 1.0, 1.0 };
		}
		
		using AspectRaitoFormatsMapType = AspectRaitoFormatsMapType;
#endif		
		using AspectRatioFormats = AspectRatioFormats;
		using CharModsFlags = flags::Flags<CharMods>;
		using Orientation = Orientation;
		using FrameActionState = FrameActionState;
		using CursorState = CursorState;
		using CursorRawInputState = CursorRawInputState;
		using KeyState = KeyState; 
		// using MouseKey = MouseKey;
		// using KeyStateMap = KeyStateMap;
} // ns glfw_enums
