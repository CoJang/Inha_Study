========================================================================
    WIN32 APPLICATION : GalsPanic Project Overview
========================================================================

string str = "�ܼ�â�� ���� ���� ���ڿ�";
DWORD dwWrite;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
WriteFile(hOut, str.c_str(), str.size(), &dwWrite, NULL);

������
[0]. ���� ���ο� �ִ��� �Ǵ�
		-> �Ϸ��� �ٰ����� �� �Ǵ� ���� ������ �ʿ�

[1]. Flood Fill ��� ��ĥ �� 
	 �̹� ĥ���� ���� ���� �ʰ� ĥ�ϴ� �˰��� �ʿ�
	 -> ���� �˰������δ� ���� ���� ������ �����ʿ�