///////////////////////////////////НОМЕР МИССИИ//////////////////////////////////
#include <string>

bool CompleteMission1 = false;
bool CompleteMission2 = false;
bool CompleteMission3 = false;

int getCurrentMission(int startx, int starty, int x, int y, int mission_)//ф-ция номера миссия, которая меняет номер миссии, в зависимости от координаты игрока Х (сюда будем передавать эту координату)
{
	startx *= 64; starty *= 64;
	int mission = 0;
	if ((x > startx) && (x < startx + 64*3) && (y > starty) && (y < starty + 64 * 3)) { mission = mission_; } //знакомим игрока с игрой
	return mission;//ф-ция возвращает номер миссии
}
/////////////////////////////////////ТЕКСТ МИССИИ/////////////////////////////////
std::string getTextMission(int currentMission) {
	std::string missionText = "";//текст миссии и его инициализация
	switch (currentMission)//принимается номер миссии и в зависимости от него переменной missionText присваивается различный текст
	{
	case 0: missionText = "\nДобро пожаловать в игру!\nНет активных заданий\n\nУправление:\nW,A,S,D-Движение\nTAB-открыть основной свиток\nQ-Выход из игры\nE-взять/сдать квест\nU/J-Отдалить/приблизить камеру\nZ-атака\nLeftShift-ускорение бега\nLeftCtrl-замедление бега"; break;
	case 1: missionText = "\nАктивное задание:\nСобрать 20 криссталлов из пещеры\n   на юге\n\nНаграда: Защита от обратной \n  атаки башни"; break;
	case 2: missionText = "\nАктивное задание:\nВернуться к жителю деревни"; break;
	case 3: missionText = "\nАктивное задание:\nСобрать 15 дисков(5 на каждой\n   из трех локаций\n\nУвеличенный урон по \n  башне"; break;
	case 4: missionText = "\nАктивное задание:\nВернуться к человеку в пещере"; break;
	case 5: missionText = "\nАктивное задание:\nУничтожить башню тьмы\n   в конце леса"; break;
	case 6: missionText = "\nАктивное задание:\nВернуться к человеку в тронном зале"; break;
	case 7: missionText = "\nПОЗДРАВЛЕНИЯ!\nПоздравляем, игра завершина!"; break;
	case 8: missionText = "\nПоражение:(\nК сожалению ваше здоровье\n  достигло нуля,\nвы проиграли, вы можете\n   выйти из игры нажав Q"; break;
	}
	return missionText;//ф-ция возвращает текст
};

void SetFinishMission(int Mission)
{
	if (Mission == 2) CompleteMission1 = true;
}
bool GetFinishMission(int Mission)
{
	if (Mission == 2) return CompleteMission1;
}