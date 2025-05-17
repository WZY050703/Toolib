export module WoodTools:EDcode;
import :bitIO;

namespace wood {
	export bool ToBase64(const char* str, unsigned char* buffer, int MaxLen);

	export wood::bitarry ToBase2X(const int x, wood::bitarry str, const char* BASEX_List);
	export wood::bitarry ToBase2X(const int x, const char* str, const int len, const char* BASEX_List);
	export wood::bitarry ToBase2X(const int x, const unsigned char* str, const int len, const char* BASEX_List);
	export wood::bitarry FromBase2X(const int x, wood::bitarry str, const char* BASEX_List);
	export wood::bitarry FromBase2X(const int x, const char* str, const int len, const char* BASEX_List);
	export wood::bitarry FromBase2X(const int x, const unsigned char* str, const int len, const char* BASEX_List);

	export wood::bitarry ToBase64(wood::bitarry str);
	export wood::bitarry ToBase64(const char* str, int len);
	export wood::bitarry ToBase64(const unsigned char* str, int len);
	export wood::bitarry FromBase64(wood::bitarry str);
	export wood::bitarry FromBase64(const char* str, int len);
	export wood::bitarry FromBase64(const unsigned char* str, int len);
	export wood::bitarry ToBase32(wood::bitarry str);
	export wood::bitarry ToBase32(const char* str, int len);
	export wood::bitarry ToBase32(const unsigned char* str, int len);
	export wood::bitarry FromBase32(wood::bitarry str);
	export wood::bitarry FromBase32(const char* str, int len);
	export wood::bitarry FromBase32(const unsigned char* str, int len);
}