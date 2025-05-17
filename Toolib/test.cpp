import std;
import WoodTools;
const char BASE32[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
int main()
{
	using namespace std;

	char si[] = "qweas";
	wood::bitarry bsX = wood::ToBase2X(5, si, 5, BASE32);
	cout << "baseX=32: ";
	bsX.Print(0);
	cout << endl;

	wood::bitarry res = wood::FromBase2X(5, bsX, BASE32);
	cout << "str: ";
	res.Print(0);
	cout << endl;
	return 0;
}