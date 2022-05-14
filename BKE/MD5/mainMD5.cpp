/* #include <iostream>
#include "md5.h"

using std::cout; using std::endl;

int main(int argc, char* argv[])
{
    cout << "md5 of 'grape': " << md5("grape") << endl;
    return 0;
}
*/
/* #define _CRT_SECURE_NO_WARNINGS  */
#include <iostream>
#include "md5.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	bool isRunning = true;
	do {

		cout << "1. Get MD5 fingerprint " << endl;
		cout << "2. Load from file " << endl;
		cout << "3. Exit " << endl;

		string choise;
		cin >> choise;
		switch (choise[0])
		{
		case '1':
		{
			cout << "Provide input value:" << endl;
			string value;
			cin >> value;
			cout << "input text: \n" + value + " \n MD5 fingerprint: " << md5 (value) << endl;
			break;
		}

		case '2':
		{
			cout << "Provide file name with extension:" << endl;
			string filename;
			cin >> filename;
			ifstream file(filename);
			if (file.is_open()) {
				string filetext;
				string line;
				while (getline(file, line)) {
					// using printf() in all tests for consistency
					//printf("%s", line.c_str());
					filetext += line + '\n';
				}
				file.close();
				cout << "input text: \n" + filetext + " \n SHA256 fingerprint: " << md5 (filetext) << endl;
				break;
			}
		}

		case '3':
			isRunning = false;
		default:
			/* isRunning = false; */
			break;
		}

	} while (isRunning);

	return 0;
}