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

    export class bitarry {
	public:
		bitarry();
		bitarry(const size_t size);
		bitarry(const unsigned char* arry, const size_t len);//��������ٹ���
		bitarry(const bitarry& obj);//�������캯��
		bitarry(bitarry&& obj);//�ƶ����캯��
		~bitarry();
		bool setSize(const size_t bitsize);//�������ڶ�������ʱû�����ڴ��״��
		bitarry read(const size_t v, const int len)const;
		bool write(const size_t v, const int len, const unsigned char* data);
		void Print(unsigned short CHD)const;
		const unsigned char* c_str()const;
		const size_t resize()const;
		void setMermey(const unsigned char data);

	private:
		size_t size;
		unsigned char* arryp;
	};
} // namespace wood