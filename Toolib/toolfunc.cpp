module WoodTools:toolfunc;

namespace wood {
	int HowLongUtf8(const unsigned char* str)
	{
		int len = 0;
		for (int i = 7; i >= 0; i--)
		{
			if (wood::bitRead(str[0], i, 1) == 0)
			{
				if (i == 7)
					len = 1;
				else
					len = 7 - i;
				break;
			}
		}
		return len;
	}
}
