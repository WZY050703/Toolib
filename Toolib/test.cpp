import std;
import WoodTools;
const char BASE32[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
int main()
{
	using namespace std;

	unsigned char si[80] = {};
	cout << "Input:";
	cin >> si;
	cout << "len: " << wood::HowLongUtf8(si) << endl;
	wood::bitarry bi(si, 10);
	bi.Print(1);
	return 0;
}