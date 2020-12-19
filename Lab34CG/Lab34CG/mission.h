///////////////////////////////////����� ������//////////////////////////////////
#include <string>

bool CompleteMission1 = false;
bool CompleteMission2 = false;
bool CompleteMission3 = false;

int getCurrentMission(int startx, int starty, int x, int y, int mission_)//�-��� ������ ������, ������� ������ ����� ������, � ����������� �� ���������� ������ � (���� ����� ���������� ��� ����������)
{
	startx *= 64; starty *= 64;
	int mission = 0;
	if ((x > startx) && (x < startx + 64*3) && (y > starty) && (y < starty + 64 * 3)) { mission = mission_; } //�������� ������ � �����
	return mission;//�-��� ���������� ����� ������
}
/////////////////////////////////////����� ������/////////////////////////////////
std::string getTextMission(int currentMission) {
	std::string missionText = "";//����� ������ � ��� �������������
	switch (currentMission)//����������� ����� ������ � � ����������� �� ���� ���������� missionText ������������� ��������� �����
	{
	case 0: missionText = "\n����� ���������� � ����!\n��� �������� �������\n\n����������:\nW,A,S,D-��������\nTAB-������� �������� ������\nQ-����� �� ����\nE-�����/����� �����\nU/J-��������/���������� ������\nZ-�����\nLeftShift-��������� ����\nLeftCtrl-���������� ����"; break;
	case 1: missionText = "\n�������� �������:\n������� 20 ����������� �� ������\n   �� ���\n\n�������: ������ �� �������� \n  ����� �����"; break;
	case 2: missionText = "\n�������� �������:\n��������� � ������ �������"; break;
	case 3: missionText = "\n�������� �������:\n������� 15 ������(5 �� ������\n   �� ���� �������\n\n����������� ���� �� \n  �����"; break;
	case 4: missionText = "\n�������� �������:\n��������� � �������� � ������"; break;
	case 5: missionText = "\n�������� �������:\n���������� ����� ����\n   � ����� ����"; break;
	case 6: missionText = "\n�������� �������:\n��������� � �������� � ������� ����"; break;
	case 7: missionText = "\n������������!\n�����������, ���� ���������!"; break;
	case 8: missionText = "\n���������:(\n� ��������� ���� ��������\n  �������� ����,\n�� ���������, �� ������\n   ����� �� ���� ����� Q"; break;
	}
	return missionText;//�-��� ���������� �����
};

void SetFinishMission(int Mission)
{
	if (Mission == 2) CompleteMission1 = true;
}
bool GetFinishMission(int Mission)
{
	if (Mission == 2) return CompleteMission1;
}