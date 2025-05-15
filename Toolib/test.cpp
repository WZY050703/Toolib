import std;
import WoodTools;

int main()
{
	using namespace std;
	wood::bitarry anull;
	cout << anull.c_str() << endl;
	char si[] = "qweas";
	wood::bitarry bs64 = wood::ToBase64(si, 5);
	cout << "base64: ";
	bs64.Print(0);
	cout << endl;
	wood::bitarry res = wood::FromBase64("cXdlYXM=", 8);
	cout << "str: ";
	res.Print(0);
	cout << endl;
	return 0;
}