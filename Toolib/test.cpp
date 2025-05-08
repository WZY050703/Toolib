import std;
import WoodTools;

int main()
{
	/*wood::bitarry str((unsigned char*)"Man", 4);
	//std::cout << "&str:0x" << std::hex << &str << ", arryp=" << (unsigned long long)str.c_str() << std::endl;
	wood::bitarry res = wood::ToCBase64(str);
	res.Print(0);*/
	char si[4] = { 'a'};
	int ai = *((int*)si);
	std::cout << std::hex << ai << std::endl;
	wood::bitarry re = wood::ToCBase64(si, 1);
	re.Print(0);
	std::cout << "\n";
	re.Print(1);
	return 0;
}