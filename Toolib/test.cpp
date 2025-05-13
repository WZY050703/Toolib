import std;
import WoodTools;

int main()
{
	using namespace std;
	char si[] = "qweas";
	//wood::bitarry re= wood::ToBase64(wood::bitarry((const unsigned char*)si, 5));
	wood::bitarry re = wood::ToBase64(si, 5);
	re.Print(0);
	cout << endl;
	re.Print(1);
	cout << endl;
	re.Print(5);
	cout << re.good() << endl << re.err() << endl;
	cout << re.good() << endl;
	return 0;
}