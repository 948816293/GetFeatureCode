#include "getFeatureCode.h"

std::string& getFeatureCode::trim(std::string& str, const std::string& chars) {
	TRIM(str, chars);
	return str;
}

std::string& getFeatureCode::trim(char* str) {
	std::string ret = str;
	return getFeatureCode::trim(ret);
}

std::string getFeatureCode::execmd(const char* ����, int ��������С, bool ȥ����һ��, bool ȥ��ͷβ�հ׷�) {
	if (��������С == 0) ��������С = 1024;
	std::string ���� = "";

	char* ������ = new char[��������С];
	FILE* pipe = _popen(����, "r");
	if (!pipe) return ����;
	while (!feof(pipe)) {
		if (fgets(������, ��������С, pipe)) {
			if (ȥ����һ��) {
				ȥ����һ�� = false;
				continue;
			}
			���� += ������;
		}
	}
	_pclose(pipe);
	if (ȥ��ͷβ�հ׷�) ���� = getFeatureCode::trim(����);
	return ����;
}

std::string getFeatureCode::get_CPU_Name() {
	return execmd("wmic cpu get Name");
}

std::string getFeatureCode::get_CPU_id() {
	return execmd("wmic cpu get processorid");
}

std::string getFeatureCode::get_DiskDrive_id() {
	return execmd("wmic diskdrive where index=0 get serialnumber");
}

std::string getFeatureCode::get_BaseBoard_id() {
	return execmd("wmic baseboard get serialnumber");
}

std::string getFeatureCode::get_BIOS_id() {
	return execmd("wmic bios get serialnumber");
}

std::string getFeatureCode::get_CPU_SystemName() {
	return execmd("wmic cpu get SystemName");
}

std::string getFeatureCode::get_NIC_WIFI_MACAddress() {
	return execmd("wmic nic where \"Name like 'Microsoft Wi-Fi Direct Virtual Adapter'\" get MACAddress");
}