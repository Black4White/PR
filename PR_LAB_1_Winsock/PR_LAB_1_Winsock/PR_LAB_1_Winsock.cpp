#include <iostream>
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>
#include <fstream>
#include <regex>
#include <iterator>
#include <cstring>;

#pragma warning (disable:4996) 

#define BUFFERSIZE 4096
using namespace std;



string ResolveIP(string& hostname)
{
	WSADATA ws;
	int res;
	// Initializing winsock
	// Before using any of the winsock constructs, the library must be initialized by calling the WSAStartup function. 
	res = WSAStartup(MAKEWORD(2, 2), &ws);
	if (res != 0)
	{
		cout << "Ошибка инициализации: " << res;
		exit(1);
	}

	hostent* record = gethostbyname(hostname.c_str());
	DWORD dw;
	if (record == NULL)
	{
		dw = WSAGetLastError();
		if (dw != 0)
		{
			cout << "Function failed with an error: " << dw << endl;
		}

		cout << hostname << " is unavailable" << endl;
		exit(1);
	}
	in_addr* address = (in_addr*)record->h_addr;
	string ip_address = inet_ntoa(*address);
	return ip_address;
}


string  get_resource(string& host, string& host_ip, string& resource)
{
	WSAData ws;
	WORD DLLVersion = MAKEWORD(2, 1);
	int res;
	string response = "";
	// Initializing winsock
	// Before using any of the winsock constructs, the library must be initialized by calling the WSAStartup function. 
	res = WSAStartup(MAKEWORD(2, 2), &ws);
	if (res != 0)
	{
		cout << "Failed to initialize winsock: " << res;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr(host_ip.c_str());
	addr.sin_port = htons(80);
	addr.sin_family = AF_INET;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(sock, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		cout << "Ошибка поключения!" << endl;
		return "";
	}
	cout << "Подключение к хосту: " << host << endl;
	cout << "IP-адрес: " << host_ip << endl << endl;

	string  get_http = "GET " + resource + " HTTP/1.1\r\n";
	get_http += "Host: " + host + "\r\n";
	//get_http += "Connection: close\r\n";
	get_http += "\r\n";

	send(sock, get_http.c_str(), strlen(get_http.c_str()), 0);

	int resp_leng;

	char buffer[BUFFERSIZE];
	int conc = 0, bin_size = 0;
	while (true)
	{
		resp_leng = recv(sock, (char*)&buffer, BUFFERSIZE, 0);
		if (resp_leng <= 0) {
			break;
		}
		response += string(buffer, resp_leng);
	}

	// Подстчет количества символов в заголовке.
	int pos = response.find("\r\n\r\n");
	cout << "Header lenght: " << pos << endl;
	string header = response;
	header = header.substr(0, pos);
	cout << "Header: " << endl << header << endl << endl;

	response = response.substr(pos + 4);
	cout << "Content lenght: " << response.length() << " bytes" << endl << endl;

	closesocket(sock);
	WSACleanup();

	return response;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	FILE* fp;
	string host = "unite.md";
	string host_ip = "";
	string resource = "/";

	host_ip = ResolveIP(host);
	string html_code = get_resource(host, host_ip, resource);
	//cout << html_code;

	if ((fp = fopen("images\\index.html", "wb")) == NULL)
	{
		printf("Cannot open file.\n");
		exit(1);
	}
	fwrite(html_code.data(), 1, html_code.size(), fp);
	fclose(fp);

	regex regular("([\/\\w-% ]+[\\.]+jpg)|([\/\\w-% ]+[\\.]+png)|([\/\\w-% ]+[\\.]+gif)|([\/\\w-% ]+[\\.]+bmp)|([\/\\w-% ]+[\\.]+ico)");
	sregex_iterator rit(html_code.begin(), html_code.end(), regular);
	sregex_iterator rend;

	while (rit != rend)
	{
		string expectsString{ rit->str() };
		expectsString = "/" + expectsString;

		//заменяем // на /
		size_t pos = 0;
		while ((pos = expectsString.find("//", pos)) != string::npos) {
			expectsString.replace(pos, 2, "/");
			pos += 1;
		}
		//заменяем пробелы в имени ресурса на %20
		pos = 0;
		while ((pos = expectsString.find(" ", pos)) != string::npos) {
			expectsString.replace(pos, 1, "%20");
			pos += 3;
		}

		cout << "Найденный элемент: " << expectsString << endl;

		//вырезаем из пути имя файла
		const size_t lastSlashIndex = expectsString.find_last_of("/\\");
		string filename = expectsString.substr(lastSlashIndex + 1);
		//cout << filename << endl;
		filename = "images\\" + filename;

		//проверка на существования файла в папке
		if (FILE* file = fopen(filename.c_str(), "r")) {
			fclose(file);
			cout << "уже существует. " << endl << endl;
			++rit;
			continue;
		}


		string response = get_resource(host, host_ip, expectsString);
		//cout << response;

		if ((fp = fopen(filename.c_str(), "wb")) == NULL) {
			printf("Не может открыть файл.\n");
			exit(1);
		}
		fwrite(response.data(), 1, response.size(), fp);
		fclose(fp);

		cout << "файл записан. " << endl << endl;
		++rit;
	}

	return 0;
}

