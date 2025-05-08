module WoodTools:bitIO;
import std;

namespace wood {
	bitarry::bitarry()
	{
		this->size = 0;
		this->arryp = nullptr;
	}

	bitarry::bitarry(const size_t bitsize)
	{
		this->size = (bitsize % 8 == 0) ? bitsize : bitsize + 8 - (bitsize % 8);
		this->arryp = new unsigned char[this->size / 8];
	}

	bitarry::bitarry(const unsigned char* arry, const size_t len)
	{
		this->size = 0;
		this->arryp = nullptr;
		this->setSize(len * 8);
		for (int i = 0;i < len;i++)
		{
			this->arryp[i] = arry[i];
		}
	}

	bitarry::bitarry(const bitarry& obj)
	{
		this->size = obj.size;
		this->arryp = new unsigned char[this->size / 8];
		for (int i = 0;i < this->size / 8;i++)
			this->arryp[i] = obj.arryp[i];
	}

	bitarry::bitarry(bitarry&& obj)
	{
		this->size = obj.size;
		this->arryp = obj.arryp;
		obj.arryp = nullptr;//转移所有权，只能一人所有
		obj.size = 0;
	}

	bitarry::~bitarry()
	{
		//std::cout << std::hex << "[DE]:0x" << this << ", arryp=" << (unsigned long long)this->arryp << std::endl; //debug
		delete[] this->arryp;
	}

	bool bitarry::setSize(const size_t bitsize)
	{
		if (this->arryp == nullptr)
		{
			this->size = (bitsize % 8 == 0) ? bitsize : bitsize + 8 - (bitsize % 8);
			this->arryp = new unsigned char[this->size / 8];
			return true;
		}
		else
			return false;
	}

	bitarry bitarry::read(const int v, const int len) const
	{
		if (v >= this->size || v < 0)//标位超出数据块
		{
			//std::cerr << "ERR[bitarry.read()]:Position out of data block.\n";
			return bitarry();//异常返回
		}
		int pi = v % 8, rei = 0;//bit位指针
		unsigned char* buffer = new unsigned char[len / 8 + 1];//读取的buffer
		buffer[len / 8] = 0;//初始化
		int ci, rci;//下标索引标识
		unsigned char bc1 = 0, bc2 = 0;//分两段的字读取buffer
		for (rei;rei < len;rei+=8)
		{
			ci = (v + rei) / 8;
			rci = rei / 8;
			if (v + rei + 8 > this->size)//读取到数据末端
			{
				int tmplen = len;
				if (len + v > this->size)//读取的超出数据块(不然就是没超出，正常尾处理)
					tmplen = this->size - v;//设置只读取完数据
				buffer[rci] = wood::bitRead(this->arryp[ci], pi, tmplen-rei);
				break;
			}
			if (rei + 8 > len)//要读的不满8bit,但没到数据末端
			{
				if (len - rei <= 8 - pi)//不跨位
				{
					bc1 = wood::bitRead(this->arryp[ci], pi, len - rei);
					bc2 = 0;
				}
				else//跨位
				{
					bc1 = wood::bitRead(this->arryp[ci], pi, 8 - pi);
					bc2 = wood::bitRead(this->arryp[ci + 1], 0, (len - rei) - (8 - pi));//读取剩下要读的
				}
				
				buffer[rci] = bc1 | (bc2 << (8 - pi));
				break;
			}
			bc1 = wood::bitRead(this->arryp[ci], pi, 8 - pi);
			bc2 = wood::bitRead(this->arryp[ci + 1], 0, pi);
			buffer[rci] = bc1 | (bc2 << (8 - pi));
		}
		wood::bitarry re(buffer, len / 8 + 1);
		//std::cout << buffer << std::endl;//DeBug
		delete[] buffer;
		return re;
	}

	bool bitarry::write(const int v, const int len, const unsigned char* data)
	{
		if (v >= this->size || v < 0)
			return false;//越界返回
		int pi = v % 8, rei = 0;//相对比特位，data数据位
		int ci;//下标索引标识
		wood::bitarry bdata(data, len);
		for (rei;rei < len;rei += 8)
		{
			ci = (v + rei) / 8;
			if (v + rei + 8 > this->size)//写到数据末端
			{
				int tmplen = len;
				if (len + v > this->size)//写的超出数据块(不然就是没超出，正常尾处理)
					tmplen = this->size - v;//设置只写完剩下能写的数据
				this->arryp[ci] = wood::bitWrite(this->arryp[ci], pi, tmplen - rei, bdata.read(rei, tmplen - rei).c_str()[0]);
				break;
			}
			if (rei + 8 > len)//要写的不满8bit,但没到数据末端
			{
				if (len - rei <= 8 - pi)//不跨位
				{
					this->arryp[ci] = wood::bitWrite(this->arryp[ci], pi, len - rei, bdata.read(rei, len - rei).c_str()[0]);
				}
				else//跨位
				{
					this->arryp[ci] = wood::bitWrite(this->arryp[ci], pi, 8 - pi, bdata.read(rei, 8 - pi).c_str()[0]);
					this->arryp[ci + 1] = wood::bitWrite(this->arryp[ci + 1], 0, (len - rei) - (8 - pi), bdata.read(rei + 8 - pi, (len - rei) - (8 - pi)).c_str()[0]);
				}
				break;
			}
			this->arryp[ci] = wood::bitWrite(this->arryp[ci], pi, 8 - pi, bdata.read(rei, 8 - pi).c_str()[0]);
			this->arryp[ci + 1] = wood::bitWrite(this->arryp[ci + 1], 0, pi, bdata.read(rei + 8 - pi, pi).c_str()[0]);
		}
		return true;
	}

	void bitarry::Print(unsigned short CHD)const
	{
		if (CHD >= 3)
		{
			std::cerr << "ERR[bitarry.Print()]:Wrong print moduel.\n";
			return;
		}
		for (int i = 0;i < (this->size / 8);i++)
		{
			if (CHD == 0)
				std::cout << this->arryp[i];
			else if (CHD == 1)
				std::cout << "0x" << std::hex << (unsigned int)this->arryp[i] << " ";
			else if (CHD == 2)
				std::cout << (unsigned int)this->arryp[i] << " ";
		}
		return;
	}

	const unsigned char* bitarry::c_str()const 
	{
		return this->arryp;
	}

	const size_t bitarry::resize()const
	{
		return this->size;
	}

	void bitarry::setMermey(const unsigned char data)
	{
		for (int i = 0;i < this->size / 8;i++)
			this->arryp[i] = data;
		return;
	}
}