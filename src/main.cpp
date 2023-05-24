

/*
* file transfer program made by Ametsa#7777
* project using cURL library for webhook connection
* do not forget to set filePath and webhookUrl
*/


#include <iostream>
#include <string>
#define CURL_STATICLIB
#include "curl/curl.h"
#include <Windows.h>
#include <fstream>
#pragma comment (lib, "curl/libcurl_a.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Normaliz.lib")

const char* webhookUrl = "your webhook url";
const char* filePath = "file.exe"; // write file name with any extension
bool isElevated = false;

int main()
{

    HANDLE hToken;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION elevation;
        DWORD dwSize;
        if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &dwSize)) {
            isElevated = (elevation.TokenIsElevated != 0);
        }
        CloseHandle(hToken);
    }

    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {

        struct curl_httppost* formpost = nullptr;
        struct curl_httppost* lastptr = nullptr;
        curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "file", CURLFORM_FILE, filePath, CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_URL, webhookUrl);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        }
        curl_easy_cleanup(curl);


        curl_formfree(formpost);
    }

    curl_global_cleanup();
    system("PAUSE");

}
