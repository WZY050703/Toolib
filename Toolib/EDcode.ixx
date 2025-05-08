export module WoodTools:EDcode;
import :bitIO;

namespace wood {
	export bool ToBase64(const char* str, unsigned char* buffer, int MaxLen);
	export wood::bitarry ToCBase64(wood::bitarry str);
	export wood::bitarry ToCBase64(const char* str, int len);
}