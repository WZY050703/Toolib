module WoodTools:EDcode;
import std.compat;
import :bitIO;

namespace wood {
	const char __BASE64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	const char __BASE32[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

	bool ToBase64(const char* str, unsigned char* buffer, int MaxLen)
	{
		int len = strlen(str);
		uint32_t stmp = 0;
		int k = 0;
		bool isfinish = true;
		for (int i = 0; i < len; i += 3)
		{
			stmp = ((uint8_t)str[i]) << 8 * 2;
			if (i + 1 < len)
				stmp += ((uint8_t)str[i + 1]) << 8;
			if (i + 2 < len)
				stmp += ((uint8_t)str[i + 2]);
			for (int j = 0; j < 4; j++)
			{
				if (k + j >= MaxLen)
					break;
				if (j * 6 <= 8 * (len - i)) // 非无数据段
				{
					buffer[k + j] = wood::__BASE64[wood::bitRead(stmp, 24 - (j + 1) * 6, 6)];
				}
				else                     // 无数据填充
					buffer[k + j] = '='; // 也可以填完后把末尾A替换为=
			}
			if (k + 4 >= MaxLen)
			{
				isfinish = false;
				break;
			}
			k += 4;
		}
		return isfinish;
	}

	wood::bitarry ToBase2X(const int x, wood::bitarry str, const char* BASEX_List)
	{
		if (x >= 8)//基值异常返回
		{
			return wood::bitarry();
		}
		str.setMemModel(statu_memMod_one);//设置模式
		size_t ssize = str.resize();
		size_t len = ssize / x + 1 + 1;
		unsigned char* recBuffer = new unsigned char[len];
		recBuffer[len - 1] = 0;//封闭位，形成字符串
		recBuffer[len - 2] = 0;//次封闭位，若用不到则置0
		for (size_t i = 0; i < len - 1; i++)
		{
			if ((i + 1) * x <= ssize)
				recBuffer[i] = BASEX_List[str.read(i * x, x).c_str()[0]];
			else
			{
				if (i * x < ssize)//读取剩下的
					recBuffer[i] = BASEX_List[str.read(i * x, ssize - i * x).c_str()[0] << (x - (ssize - i * x))];//位移相当于补0
				break;
			}
		}
		wood::bitarry reba(recBuffer, len);
		delete[] recBuffer;
		return reba;
	}

	wood::bitarry ToBase2X(const int x, const char* str, const int len, const char* BASEX_List)
	{
		return wood::ToBase2X(x, wood::bitarry((const unsigned char*)str, len), BASEX_List);
	}

	wood::bitarry ToBase2X(const int x, const unsigned char* str, const int len, const char* BASEX_List)
	{
		return wood::ToBase2X(x, wood::bitarry(str, len), BASEX_List);
	}

	unsigned char get_base2X_num(const int x, const char cc, const char* BASEX_List)
	{
		unsigned char renum = 0;
		for (int i = 0; i < pow(2, x); i++)
		{
			if (BASEX_List[i] == cc)
			{
				renum = i;
				break;
			}
		}
		return renum;
	}

	wood::bitarry FromBase2X(const int x, wood::bitarry str, const char* BASEX_List)
	{
		if (x >= 8)//基值异常返回
		{
			return wood::bitarry();
		}
		size_t slen = str.resize() / 8;
		const unsigned char* sstr = str.c_str();
		size_t len = slen * x + 8;
		wood::bitarry recBuffer(len);
		recBuffer.setMermey(0u);
		recBuffer.setMemModel(statu_memMod_one);//设置模式
		for (size_t i = 0; i < slen; i++)
		{
			unsigned char tmpc = get_base2X_num(x, sstr[i], BASEX_List) << (8 - x);
			recBuffer.write(i * x, x, wood::bitarry(&tmpc, 1).setMemModel(statu_memMod_one));
		}
		return recBuffer;
	}

	wood::bitarry FromBase2X(const int x, const char* str, const int len, const char* BASEX_List)
	{
		return wood::FromBase2X(x, wood::bitarry((const unsigned char*)str, len), BASEX_List);
	}

	wood::bitarry FromBase2X(const int x, const unsigned char* str, const int len, const char* BASEX_List)
	{
		return wood::FromBase2X(x, wood::bitarry(str, len), BASEX_List);
	}

	wood::bitarry ToBase64(wood::bitarry str)
	{
		return ToBase2X(6, str, __BASE64);
	}

	wood::bitarry ToBase64(const char* str, int len)
	{
		return wood::ToBase64(wood::bitarry((const unsigned char*)str, len));
	}

	wood::bitarry ToBase64(const unsigned char* str, int len)
	{
		return wood::ToBase64(wood::bitarry(str, len));
	}

	unsigned char get_base64_num(const char cc)
	{
		unsigned char renum = 0;
		if ('A' <= cc && cc <= 'Z')
			renum = cc - 'A';
		else if ('a' <= cc && cc <= 'z')
			renum = cc - 'a' + 26;
		else if ('0' <= cc && cc <= '9')
			renum = cc - '0' + 26 * 2;
		else if ('+' == cc)
			renum = 26 * 2 + 10;
		else if ('/' == cc)
			renum = 26 * 2 + 10 + 1;
		else
			renum = 0;
		return renum;
	}

	wood::bitarry FromBase64(wood::bitarry str)
	{
		size_t slen = str.resize() / 8;
		const unsigned char* sstr = str.c_str();
		size_t len = slen * 6 + 8;
		wood::bitarry recBuffer(len);
		recBuffer.setMermey(0u);
		recBuffer.setMemModel(statu_memMod_one);//设置模式
		for (size_t i = 0; i < slen; i++)
		{
			unsigned char tmpc = get_base64_num(sstr[i]) << (8 - 6);
			recBuffer.write(i * 6, 6, wood::bitarry(&tmpc, 1).setMemModel(statu_memMod_one));
		}
		return recBuffer;
	}

	wood::bitarry FromBase64(const char* str, int len)
	{
		return wood::FromBase64(wood::bitarry((const unsigned char*)str, len));
	}

	wood::bitarry FromBase64(const unsigned char* str, int len)
	{
		return wood::FromBase64(wood::bitarry(str, len));
	}

	wood::bitarry ToBase32(wood::bitarry str)
	{
		return ToBase2X(5, str, __BASE32);
	}

	wood::bitarry ToBase32(const char* str, int len)
	{
		return wood::ToBase32(wood::bitarry((const unsigned char*)str, len));
	}

	wood::bitarry ToBase32(const unsigned char* str, int len)
	{
		return wood::ToBase32(wood::bitarry(str, len));
	}

	unsigned char get_base32_num(const char cc)
	{
		unsigned char renum = 0;
		if ('A' <= cc && cc <= 'Z')
			renum = cc - 'A';
		else if ('2' <= cc && cc <= '7')
			renum = cc - '2' + 26;
		else
			renum = 0;
		return renum;
	}

	wood::bitarry FromBase32(wood::bitarry str)
	{
		size_t slen = str.resize() / 8;
		const unsigned char* sstr = str.c_str();
		size_t len = slen * 5 + 8;
		wood::bitarry recBuffer(len);
		recBuffer.setMermey(0u);
		recBuffer.setMemModel(statu_memMod_one);//设置模式
		for (size_t i = 0; i < slen; i++)
		{
			unsigned char tmpc = get_base32_num(sstr[i]) << (8 - 5);
			recBuffer.write(i * 5, 5, wood::bitarry(&tmpc, 1).setMemModel(statu_memMod_one));
		}
		return recBuffer;
	}

	wood::bitarry FromBase32(const char* str, int len)
	{
		return wood::FromBase32(wood::bitarry((const unsigned char*)str, len));
	}

	wood::bitarry FromBase32(const unsigned char* str, int len)
	{
		return wood::FromBase32(wood::bitarry(str, len));
	}
}