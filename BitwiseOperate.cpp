class BitwiseOperate
{
public:
	//判断偶数
	static bool IsEven(int num)
	{
		return !(num & 1);
	}
	//2的n次方
	static size_t PowerTwo(size_t n)
	{
		return size_t(1) << n;
	}
	//m的n次方
	static size_t Pow(size_t m, size_t n)
	{
		size_t re = 1;
		while (n != 0)
		{
			if (n & 1)
			{
				re *= m;
			}
			m *= m;
			n = n >> 1;
		}
		return re;
	}
	//判断num转成二进制后, 从右到左(从高位到低位)第pos(pos最小为1)位是否为1. 例如BinaryPos(5,2)为false.
	static bool BinaryPos(size_t num, size_t pos)
	{
		return num & (1 << (pos - 1));
	}
	//读取num的第index(index最小为1)个字节(从低位往高位读). 例如9876543210的从低到高个字节分别为: 234, 22, 176, 76, 2, 0...
	static size_t ReadByte(size_t num, size_t index)
	{   //第k个字节: (num >> (8k-8)) & 0xff
		return (num >> ((index << 3) - 8)) & 0xff;
	}
	//判断是否是2的指数
	static bool IsPowerOfTwo(int num)
	{
		if (num <= 0) return false;
		return !(num & (num - 1));
	}
	//计算: num % (2^n)
	static size_t GetRemainderOfPowerTwo(size_t num, size_t n)
	{
		return num & ((1 << n) - 1);
	}
	//计算num所需的二进制位数(最高位1所在的位置)
	static size_t BinaryLength(size_t num)
	{
		if (num == 0)return 0;
		size_t Length = 0;
		for (size_t Shift = sizeof(size_t) * CHAR_BIT - 1; Shift >= 0; Shift--)
		{
			if (num & (size_t(1) << Shift))
			{
				Length = Shift + 1;
				break;
			}
		}
		return Length;
	}
	//统计num对应的二进制数中1的个数. 例如9876543210返回15
	static size_t CountOne(size_t num)
	{
		size_t Count = 0;
		while (num)
		{
			num &= (num - 1);
			Count++;
		}
		return Count;
	}
	//统计num对应的二进制数中0的个数. 例如9876543210返回19
	static size_t CountZero(size_t num)
	{
		return BinaryLength(num) - CountOne(num);
	}
	//交换整数值
	static void Swap(size_t& num1, size_t& num2)
	{
		num1 ^= num2;
		num2 ^= num1;
		num1 ^= num2;
	}
	//判断num1和num2是否同号. 例如IsDiffSign(-1,2)返回false, IsDiffSign(1,2)返回true
	static bool IsSameSign(int num1, int num2)
	{
		return (num1 ^ num2) >= 0;
	}
};
