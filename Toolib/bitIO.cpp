module WoodTools:bitIO;
import std;

#define statu_err_num(x) (unsigned int)(x)

namespace wood {
	void inline bitarry::null_init()
	{
		this->size = 0;
		this->arryp = nullptr;
		this->statusnum = (statu_good << err_flag) | statu_memMod_zero;
	}

	bitarry::bitarry()
	{
		this->null_init();
	}

	bitarry::bitarry(const size_t bitsize)
	{
		this->null_init();
		this->setSize(bitsize);
	}

	bitarry::bitarry(const unsigned char* arry, const size_t len)
	{
		this->null_init();
		this->setSize(len * 8);
		for (int i = 0;i < len;i++)
			this->arryp[i] = arry[i];
	}

	bitarry::bitarry(const bitarry& obj)
	{
		this->size = obj.size;
		this->arryp = new unsigned char[this->size / 8];
		this->statusnum = obj.statusnum;
		for (int i = 0;i < this->size / 8;i++)
			this->arryp[i] = obj.arryp[i];
	}

	bitarry::bitarry(bitarry&& obj)
	{
		this->size = obj.size;
		this->arryp = obj.arryp;
		this->statusnum = obj.statusnum;
		obj.arryp = nullptr;//ת������Ȩ��ֻ��һ������
		obj.size = 0;
	}

	bitarry::~bitarry()
	{
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

	bitarry bitarry::setMemModel(const unsigned int model)
	{
		this->statusnum = wood::bitWrite(this->statusnum, memMod_flag, 2, model);
		return *this;
	}

	bitarry bitarry::read(const size_t v, const int len)
	{
		if (v >= this->size || v < 0)//��λ�������ݿ�
		{
			this->statusnum = wood::bitWrite(this->statusnum, err_flag, 1, statu_err);
			this->statusnum = wood::bitWrite(this->statusnum, err_num_flag, (int)(sizeof(unsigned int) * 8 - err_num_flag), statu_err_num(1));
			return bitarry();//�쳣����
		}
		int pi = v % 8, rei = 0;//bitλָ��
		unsigned char* buffer = new unsigned char[len / 8 + 1];//��ȡ��buffer
		buffer[len / 8] = 0;//��ʼ��
		int ci, rci;//�±�������ʶ
		unsigned char bc1 = 0, bc2 = 0;//�����ε��ֶ�ȡbuffer
		bool bit_turn_flag = (bool)wood::bitRead(this->statusnum, memMod_flag, 1);
		for (rei;rei < len;rei += 8)
		{
			ci = (v + rei) / 8;
			rci = rei / 8;
			if (v + rei + 8 > this->size)//��ȡ������ĩ��
			{
				int tmplen = len;
				if (len + v > this->size)//��ȡ�ĳ������ݿ�(��Ȼ����û����������β����)
					tmplen = this->size - v;//����ֻ��ȡ������
				bc1 = wood::bitRead(this->arryp[ci], (bit_turn_flag) ? (8 - pi - (tmplen - rei)) : pi, tmplen - rei);//��ȡ�ĳ���һ�£�λ���෴
				buffer[rci] = bc1;
				break;
			}
			if (rei + 8 > len)//Ҫ���Ĳ���8bit,��û������ĩ��
			{
				if (len - rei <= 8 - pi)//����λ
				{
					bc1 = wood::bitRead(this->arryp[ci], (bit_turn_flag) ? (8 - pi - (len - rei)) : pi, len - rei);
					bc2 = 0;
					buffer[rci] = bc1;
				}
				else//��λ
				{
					bc1 = wood::bitRead(this->arryp[ci], (bit_turn_flag) ? (8 - pi - (8 - pi)) : pi, 8 - pi);
					bc2 = wood::bitRead(this->arryp[ci + 1], (bit_turn_flag) ? (8 - 0 - ((len - rei) - (8 - pi))) : 0, (len - rei) - (8 - pi));//��ȡʣ��Ҫ����
					buffer[rci] = (bit_turn_flag) ? (bc2 | (bc1 << ((len - rei) - (8 - pi)))) : (bc1 | (bc2 << (8 - pi)));
				}
				break;
			}
			bc1 = wood::bitRead(this->arryp[ci], (bit_turn_flag) ? (8 - pi - (8 - pi)) : pi, 8 - pi);
			bc2 = wood::bitRead(this->arryp[ci + 1], (bit_turn_flag) ? (8 - 0 - pi) : 0, pi);
			buffer[rci] = (bit_turn_flag) ? (bc2 | (bc1 << pi)) : (bc1 | (bc2 << (8 - pi)));//��ŵ�˳��Ҳ��ͬ
		}
		wood::bitarry re(buffer, len / 8 + 1);
		delete[] buffer;
		return re;
	}

	bool bitarry::write(const size_t v, const int len, wood::bitarry bdata)
	{
		if (v >= this->size || v < 0)
		{
			this->statusnum = wood::bitWrite(this->statusnum, err_flag, 1, statu_err);
			this->statusnum = wood::bitWrite(this->statusnum, err_num_flag, (int)(sizeof(unsigned int) * 8 - err_num_flag), statu_err_num(2));
			return false;//Խ�緵��
		}
		int pi = v % 8, rei = 0;//��Ա���λ��data����λ
		int ci;//�±�������ʶ
		bool bit_turn_flag = (bool)wood::bitRead(this->statusnum, memMod_flag, 1);
		for (rei;rei < len;rei += 8)
		{
			ci = (v + rei) / 8;
			if (v + rei + 8 > this->size)//д������ĩ��
			{
				int tmplen = len;
				if (len + v > this->size)//д�ĳ������ݿ�(��Ȼ����û����������β����)
					tmplen = this->size - v;//����ֻд��ʣ����д������
				this->arryp[ci] = wood::bitWrite(this->arryp[ci], (bit_turn_flag) ? (8 - pi - (tmplen - rei)) : pi, tmplen - rei, bdata.read(rei, tmplen - rei).c_str()[0]);
				break;
			}
			if (rei + 8 > len)//Ҫд�Ĳ���8bit,��û������ĩ��
			{
				if (len - rei <= 8 - pi)//����λ
				{
					this->arryp[ci] = wood::bitWrite(this->arryp[ci], (bit_turn_flag) ? (8 - pi - (len - rei)) : pi, len - rei, bdata.read(rei, len - rei).c_str()[0]);
				}
				else//��λ
				{
					this->arryp[ci] = wood::bitWrite(this->arryp[ci], (bit_turn_flag) ? (8 - pi - (8 - pi)) : pi, 8 - pi, bdata.read(rei, 8 - pi).c_str()[0]);
					this->arryp[ci + 1] = wood::bitWrite(this->arryp[ci + 1], (bit_turn_flag) ? (8 - 0 - ((len - rei) - (8 - pi))) : 0, (len - rei) - (8 - pi), bdata.read(rei + 8 - pi, (len - rei) - (8 - pi)).c_str()[0]);
				}
				break;
			}
			this->arryp[ci] = wood::bitWrite(this->arryp[ci], (bit_turn_flag) ? (8 - pi - (8 - pi)) : pi, 8 - pi, bdata.read(rei, 8 - pi).c_str()[0]);
			this->arryp[ci + 1] = wood::bitWrite(this->arryp[ci + 1], (bit_turn_flag) ? (8 - 0 - pi) : 0, pi, bdata.read(rei + 8 - pi, pi).c_str()[0]);
		}
		return true;
	}

	bool bitarry::write(const size_t v, const int len, const char* data)
	{
		return this->write(v, len, bitarry((unsigned char*)data, len));
	}

	bool bitarry::write(const size_t v, const int len, const unsigned char* data)
	{
		return this->write(v, len, bitarry(data, len));
	}

	void bitarry::Print(unsigned short CHD)
	{
		if (CHD >= 3)
		{
			this->statusnum = wood::bitWrite(this->statusnum, err_flag, 1, statu_err);
			this->statusnum = wood::bitWrite(this->statusnum, err_num_flag, (int)(sizeof(unsigned int) * 8 - err_num_flag), statu_err_num(0));
			std::cerr << bitarry_Errs[0] << std::endl;
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
		return (this->arryp == nullptr) ? __null_str : this->arryp;
	}

	const size_t bitarry::resize()const
	{
		return this->size;
	}

	bitarry bitarry::setMermey(const unsigned char data)
	{
		for (int i = 0;i < this->size / 8;i++)
			this->arryp[i] = data;
		return *this;
	}

	bitarry bitarry::setMermey(const unsigned char* data, int v, int len)
	{
		for (int i = 0;(v + i < this->size / 8) && (i < len);i++)
			this->arryp[v + i] = data[i];
		return *this;
	}

	bool bitarry::good()const
	{
		return (bool)wood::bitRead(this->statusnum, err_flag, 1);
	}

	const char* bitarry::err()
	{
		if (this->good() == false)
		{
			this->statusnum = wood::bitWrite(this->statusnum, err_flag, 1, statu_good);//�ָ���־
			return bitarry_Errs[wood::bitRead(this->statusnum, err_num_flag, (int)(sizeof(unsigned int) * 8 - err_num_flag))];
		}
		return nullptr;
	}
}