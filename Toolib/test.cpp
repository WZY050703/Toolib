import std;
import WoodTools;

int main()
{
	using namespace std;
	wood::bitarry anull;
	cout << anull.c_str() << endl;//现在null对象返回指针不会是nullptr了，而是一个指向“\0”的指针

	char si[] = "qweas";
	wood::bitarry bs64 = wood::ToBase64(si, 5);
	cout << "base64: ";
	bs64.Print(0);
	cout << endl;
	wood::bitarry res = wood::FromBase64("cXdlYXM=", 8);
	cout << "str: ";
	res.Print(0);
	cout << endl;

	res.read(100, 1);
	cout << res.good() << ":" << res.err() << endl;
	res.write(100, 1, "3");
	cout << res.good() << ":" << res.err() << endl;
	res.Print(5);
	cout << res.good() << ":" << res.err() << endl;
	cout << res.good();
	return 0;
}