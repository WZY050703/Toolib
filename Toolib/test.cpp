import std;
import WoodTools;

int main()
{
	using namespace std;
	char si[4] = {'a'};
	wood::bitarry re= wood::ToCBase64(si, 1);
	re.Print(0);
	cout << endl;
	re.Print(1);
	cout << endl;
	re.Print(5);
	cout << re.good() << endl << re.err() << endl;
	cout << re.good() << endl;
	return 0;
}