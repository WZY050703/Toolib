import std;
export module WoodTools:bitIO;

namespace wood
{
	export template <typename T> T inline bitRead(const T data, const int v, const int len)
	{
		return (((T)(data << (sizeof(T) * 8 - v - len))) >> (sizeof(T) * 8 - v - len)) >> v;
	}

	export template <typename T> T inline bitWrite(const T buffer, const int st, const int len, const T data)
	{
		return ((((buffer >> (st + len)) << len) | ((T)(data << (sizeof(T) * 8 - len)) >> (sizeof(T) * 8 - len))) << st) | (((T)(buffer << (sizeof(T) * 8 - st))) >> (sizeof(T) * 8 - st));
	}

	const char bitarry_Errs[][80] = {
		"ERR[bitarry.Print()]:Wrong print moduel.\n",
		"ERR[bitarry.read()]:Position out of data block.\n",
		"ERR[bitarry.write()]:Position out of data block.\n",
		"ERR[bitarry[]]:Position out of data block.\n"
	};

	const unsigned char __null_str[1] = { '\0' };

	const unsigned int statu_good = 0x1u;
	const unsigned int statu_err = 0x0u;

	const int memMod_flag = 0;
	const int err_flag = 2;
	const int err_num_flag = 3;

	export const unsigned int statu_memMod_zero = 0x0u;
	export const unsigned int statu_memMod_one = 0x1u;

	export class bitarry {
	public:
		bitarry();
		explicit bitarry(const size_t size);//禁止隐式转换调用构造函数
		bitarry(const unsigned char* arry, const size_t len);//从数组快速构建
		bitarry(const bitarry& obj);//拷贝构造函数
		bitarry(bitarry&& obj);//移动构造函数
		~bitarry();
		bool setSize(const size_t bitsize);//仅仅用于定义声明时没申请内存的状况
		bitarry setMemModel(const unsigned int model);//0:normal, 1:turned bit
		bitarry read(const size_t v, const int len);
		bool write(const size_t v, const int len, wood::bitarry bdata);
		bool write(const size_t v, const int len, const char* data);
		bool write(const size_t v, const int len, const unsigned char* data);
		void Print(unsigned short CHD);
		const unsigned char* c_str()const;
		const size_t resize()const;
		bitarry setMermey(const unsigned char data);
		bitarry setMermey(const unsigned char* data, int v, int len);
		bool good()const;
		const char* err();
		bool operator[](const int v);

	private:
		size_t size;
		unsigned char* arryp;
		unsigned int statusnum; //now: 0-1: memrey mod, 2:err flag, 3-32: err num
		void inline null_init();
	};
} // namespace wood