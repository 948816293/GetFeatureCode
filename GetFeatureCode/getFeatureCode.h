#ifndef GETFEATURECODE_H
#define GETFEATURECODE_H

#include <iostream>
#include <vector>
#include <Windows.h>
#include <tchar.h>

#define TRIM(s, chars) \
do{ \
    std::string map(0xFF, '\0'); \
    for (auto &ch : chars) { \
        map[(unsigned char &)ch] = '\1'; \
    } \
    while( s.size() && map.at((unsigned char &)s.back())) s.pop_back(); \
    while( s.size() && map.at((unsigned char &)s.front())) s.erase(0,1); \
}while(0);

class getFeatureCode {
private:
	static std::string& trim(std::string& str, const std::string& chars = " \r\n\t");
	static std::string& trim(char* str);
	static LPWSTR ConvertCharToLPWSTR(const char* szString);//const char* to LPWSTR
public:
	static std::string execmd(const char* ����, int ��������С = 1024, bool ȥ����һ�� = true, bool ȥ��ͷβ�հ׷� = true);
	static std::string runCmd(std::string& strCmd, bool ȥ����һ�� = true, bool ȥ��ͷβ�հ׷� = true);
	static std::string runCmd(const char* strCmd, bool ȥ����һ�� = true, bool ȥ��ͷβ�հ׷� = true);
	static std::string& �����ı�(std::string &str, bool ȥ����һ�� = true, bool ȥ��ͷβ�հ׷� = true);
	static std::string get_CPU_Name();
	static std::string get_CPU_id();
	static std::string get_DiskDrive_id();
	static std::string get_BaseBoard_id();
	static std::string get_BIOS_id();
	static std::string get_CPU_SystemName();
	static std::string get_NIC_WIFI_MACAddress();


};



#endif // !GETFEATURECODE_H





