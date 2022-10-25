#include "getFeatureCode.h"

std::string& getFeatureCode::trim(std::string& str, const std::string& chars) {
	TRIM(str, chars);
	return str;
}

std::string& getFeatureCode::trim(char* str) {
	std::string ret = str;
	return getFeatureCode::trim(ret);
}

std::string& getFeatureCode::�����ı�(std::string &str,bool ȥ����һ��, bool ȥ��ͷβ�հ׷�) {
	if (ȥ����һ��) str = str.substr(str.find_first_of('\n') + 1);
	if (ȥ��ͷβ�հ׷�) str = getFeatureCode::trim(str);
	return str;
}

//���кڴ��ڳ���
std::string getFeatureCode::execmd(const char* ����, int ��������С, bool ȥ����һ��, bool ȥ��ͷβ�հ׷�) {
	if (��������С == 0) ��������С = 1024;
	std::string ���� = "";

	char* ������ = new char[��������С];
	FILE* pipe = _popen(����, "r");
	if (!pipe) return ����;
	while (!feof(pipe)) {
		if (fgets(������, ��������С, pipe)) {
			���� += ������;
		}
	}
	_pclose(pipe);
	return getFeatureCode::�����ı�(����, ȥ����һ��, ȥ��ͷβ�հ׷�);
}

LPWSTR getFeatureCode::ConvertCharToLPWSTR(const char* szString) {
	int dwLen = (int)strlen(szString) + 1;
	int nwLen = MultiByteToWideChar(CP_ACP, 0, szString, dwLen, NULL, 0);//������ʵĳ���
	LPWSTR lpszPath = new WCHAR[dwLen];
	MultiByteToWideChar(CP_ACP, 0, szString, dwLen, lpszPath, nwLen);
	return lpszPath;
}

std::string getFeatureCode::runCmd(std::string& strCmd, bool ȥ����һ��, bool ȥ��ͷβ�հ׷�) {
	SECURITY_ATTRIBUTES sa{};
	HANDLE hRead = nullptr, hWrite = nullptr;
	std::string strResult;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	strCmd = "cmd /c " + strCmd;//����"cmd /c"��Ϊ����ִ������dir������,ִ���ַ���ָ��������Ȼ���ն�

	//���������ܵ�������DOS�������ͨ��
	if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
		return NULL;
	}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;//��������õ��ļ����
	si.hStdOutput = hWrite;//�´������̵ı�׼�������д�ܵ�һ��
	si.wShowWindow = SW_HIDE;//���ش���
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	LPWSTR cmd = getFeatureCode::ConvertCharToLPWSTR(strCmd.c_str());
	//ִ��cmd����,���������йܵ���д��cmd����صĴ�
	if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi)) {
		CloseHandle(pi.hThread);
		return NULL;
	}
	
	//��������Ƿ�Ҫ����������ִ����,��ping�Ⱥ�ʱ�϶������.
	if (pi.hProcess != NULL) {
		if (WaitForSingleObject(pi.hProcess, INFINITE) == WAIT_FAILED) {
			return FALSE;
		}
	}

	CloseHandle(hWrite);//�رչܵ����

	char buffer[4096] = { 0 };
	DWORD bytesRead;

	while (ReadFile(hRead, buffer, 4096, &bytesRead, NULL))//�������ܵ��ж�ȡ����
	{
		strResult += buffer;
		memset(&buffer, 0, 4096);
		Sleep(200);//��ֹ����
	}
	CloseHandle(hRead);
	return getFeatureCode::�����ı�(strResult, ȥ����һ��, ȥ��ͷβ�հ׷�);
}

std::string getFeatureCode::runCmd(const char* strCmd, bool ȥ����һ��, bool ȥ��ͷβ�հ׷�) {
	std::string str = strCmd;
	return getFeatureCode::runCmd(str, ȥ����һ��, ȥ��ͷβ�հ׷�);
}

std::string getFeatureCode::get_CPU_Name() {
	return getFeatureCode::runCmd("wmic cpu get Name");
}

std::string getFeatureCode::get_CPU_id() {
	return getFeatureCode::runCmd("wmic cpu get processorid");
}

std::string getFeatureCode::get_DiskDrive_id() {
	return getFeatureCode::runCmd("wmic diskdrive where index=0 get serialnumber");
}

std::string getFeatureCode::get_BaseBoard_id() {
	return getFeatureCode::runCmd("wmic baseboard get serialnumber");
}

std::string getFeatureCode::get_BIOS_id() {
	return getFeatureCode::runCmd("wmic bios get serialnumber");
}

std::string getFeatureCode::get_CPU_SystemName() {
	return getFeatureCode::runCmd("wmic cpu get SystemName");
}

std::string getFeatureCode::get_NIC_WIFI_MACAddress() {
	return getFeatureCode::runCmd("wmic nic where \"Name like 'Microsoft Wi-Fi Direct Virtual Adapter'\" get MACAddress");
}