import std;
import WoodTools;

int main()
{
	char si[4] = { 'a'};
	int ai = *((int*)si);
	std::cout << std::hex << ai << std::endl;
	wood::bitarry re = wood::ToCBase64(si, 1);
	re.Print(0);//不是正常的Base64!
	std::cout << "\n";
	re.Print(1);
	return 0;
}