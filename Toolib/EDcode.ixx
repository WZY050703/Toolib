export module WoodTools:EDcode;
import :bitIO;

namespace wood {
	export bool ToBase64(const char* str, unsigned char* buffer, int MaxLen);
	export wood::bitarry ToBase64(wood::bitarry str);
	export wood::bitarry ToBase64(const char* str, int len);
	export wood::bitarry ToBase64(const unsigned char* str, int len);
	export wood::bitarry FromBase64(wood::bitarry str);
	export wood::bitarry FromBase64(const char* str, int len);
	export wood::bitarry FromBase64(const unsigned char* str, int len);
}