import std.compat;
module WoodTools:EDcode;
import :bitIO;

namespace wood {
    const char __BASE64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    bool ToBase64(const char* str,unsigned char* buffer, int MaxLen)
    {
        int len = strlen(str);
        uint32_t stmp = 0;
        unsigned int k = 0;
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
                    /*
                    //debug
                    unsigned int pk = wood::bitRead(stmp, 24 - (j + 1) * 6, 6);
                    std::cout << pk << "\t" << wood::__BASE64[pk] << std::endl;
                    */
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

    wood::bitarry ToCBase64(wood::bitarry str)
    {
        size_t ssize = str.resize();
        size_t len = ssize / 6 + 1 + 1;
        unsigned char* recBuffer = new unsigned char[len];
        recBuffer[len - 1] = 0;//封闭位，形成字符串
        recBuffer[len - 2] = 0;//次封闭位，若用不到则置0
        for (int i = 0;i < len - 1;i++)
        {
            //str.read(ssize - i * 6, 6);//debug
            //std::cout << i << "," << (int)str.read(i * 6, 6).c_str()[0] << "," << __BASE64[str.read(i * 6, 6).c_str()[0]] << std::endl;
            recBuffer[i] = __BASE64[str.read(i * 6, 6).c_str()[0]];
        }
        return wood::bitarry(recBuffer, len);
    }

    wood::bitarry ToCBase64(const char* str, int len)
    {
        wood::bitarry bstr((const unsigned char*)str, len);
        return wood::ToCBase64(bstr);
    }
}