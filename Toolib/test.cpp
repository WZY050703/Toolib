import std;
import WoodTools;

int main()
{
	using namespace std;

	char si[] = "qweas";
	wood::bitarry bs32 = wood::ToBase32(si, 5);
	cout << "base32: ";
	bs32.Print(0);
	cout << endl;

	wood::bitarry res = wood::FromBase32(bs32);
	cout << "str: ";
	res.Print(0);
	cout << endl;
	return 0;
}