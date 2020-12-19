#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Map.h" //подключили код с картой
#include "Player.h" //подключили код с player
#include "Objects.h" //подключили код с объектами
#include "view.h" //Подключение камеры
#include "mission.h" //Подключение миссий
#include "NPC.h" //Подключение НПС
#include <sstream>

using namespace sf;
using namespace std;

IntRect DrawMap(int X, int Y)
{
	X--, Y--;
	return IntRect(X*64, Y*64, 64, 64);
}


int main()
{
	int SetMission = 0;
	bool HaveMission = false;
#pragma region Рандомизация объектов на карте
	srand((time(0)));
	ReplaysRnd('f', 'F');
	ReplaysRnd('l', 'L');
	ReplaysRnd4('o', '9', '8', '7');
	ReplaysRnd4('k', '6', '5', '4');
#pragma endregion

	Music music;//создаем объект музыки
	music.openFromFile("Sounds/music.ogg");//загружаем файл
	music.setVolume(3);
	music.play();//воспроизводим музыку

	SoundBuffer soundBuffer;//создаём буфер для звука
	Sound sound;


	#pragma region Создание объектов

	#pragma region Карта
	Image map_image;//объект изображения для карты
	map_image.loadFromFile("Images/map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
#pragma endregion

	#pragma region Текст
	Font font;//шрифт 
	font.loadFromFile("Font/CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 18);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	//text.setColor(sf::Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold);//жирный текст. по умолчанию он "худой":)) и не подчеркнутый
	Text textmission = text;
#pragma endregion

	#pragma region Домa
	Object house_92_2("Objects.png", 92, 2, 1, 1, 4, 5);
	house_92_2.SymbolOnMap('Б');
	Object house_81_1("Objects.png", 81, 1, 6, 5, 4, 5);
	house_81_1.SymbolOnMap('Б');
	Object house_79_15("Objects.png", 79, 15, 5, 1, 5, 3);
	house_79_15.SymbolOnMap('Б');
	Object house_94_14("Objects.png", 94, 14, 1, 6, 5, 4);
	house_94_14.SymbolOnMap('Б');
	Object house_89_18("Objects.png", 89, 18, 1, 1, 4, 5);
	house_89_18.SymbolOnMap('Б');
	Object house_86_2("Objects.png", 86, 2, 5, 1, 5, 3);
	house_86_2.SymbolOnMap('Б');
#pragma endregion

	#pragma region Разные объекты
	Object Gate_74_11("Objects.png", 74, 11, 10, 1, 3, 2);
	Object throne_43_11("Objects.png", 43, 11, 10, 3, 2, 2);
	Object pool_87_14("Objects.png", 87, 14, 10, 7, 3, 3);
	Object tower_124_20("Objects.png", 124, 20, 13, 3, 4, 4);

#pragma endregion

	#pragma region Колонны
	Object column_58_8("Objects.png", 58, 8, 12, 3, 1, 2);
	column_58_8.SymbolOnMap('c');
	Object column_61_8("Objects.png", 61, 8, 12, 3, 1, 2);
	column_61_8.SymbolOnMap('c');
	Object column_64_8("Objects.png", 64, 8, 12, 3, 1, 2);
	column_64_8.SymbolOnMap('c');
	Object column_67_8("Objects.png", 67, 8, 12, 3, 1, 2);
	column_67_8.SymbolOnMap('c');
	Object column_70_8("Objects.png", 70, 8, 12, 3, 1, 2);
	column_67_8.SymbolOnMap('c');

	Object column_58_14("Objects.png", 58, 14, 12, 5, 1, 2);
	column_58_14.SymbolOnMap('c');
	Object column_61_14("Objects.png", 61, 14, 12, 5, 1, 2);
	column_61_14.SymbolOnMap('c');
	Object column_64_14("Objects.png", 64, 14, 12, 5, 1, 2);
	column_64_14.SymbolOnMap('c');
	Object column_67_14("Objects.png", 67, 14, 12, 5, 1, 2);
	column_67_14.SymbolOnMap('c');
	Object column_70_14("Objects.png", 70, 14, 12, 5, 1, 2);
	column_70_14.SymbolOnMap('c');
#pragma endregion



#pragma endregion

	bool showMissionText = true;//логическая переменная, отвечающая за появление текста миссии на экране
	Image quest_image;
	quest_image.loadFromFile("Images/missionbg.jpg");
	quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
	s_quest.setScale(1.0f, 1.0f);//чуть уменьшили картинку, => размер стал меньше

	float CurrentFrame = 0;
	float SizeFrame = 64;

	float CurrentCooficientSizeCam = 1;

	RenderWindow window(VideoMode(1200, 1040), "Lab3 CG", Style::Fullscreen);
	view.reset(FloatRect(0, 0, 1280, 720));
	Player player("MainHero.png", 64, 64, 64, 64);

	//Создание НПС игры
	NPC npc1("NPC.png", 90, 6, 1, 2, 0, 0, 1);
	NPC npc2("NPC.png", 48, 11, 1, 2, 2, 0, 3);
	NPC npc3("NPC.png", 34, 6, 1, 2, 4, 0, 3);

	Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.

	while (window.isOpen())
	{
		if (player.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();//игровое время в секундах идёт вперед, пока жив игрок, перезагружать как time его не надо. оно не обновляет логику игры

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)//событие нажатия клавиши
				if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ
					soundBuffer.loadFromFile("Sounds/OpenScroll.ogg");//загружаем в него звук
					sound.setBuffer(soundBuffer);//создаем звук и загружаем в него звук из буфера
					sound.setVolume(10);
					sound.play();
					textmission.setFillColor(Color::Black);
					text.setFillColor(Color::Black);
					switch (showMissionText) {//переключатель, реагирующий на логическую переменную showMissionText

					case true: {
						std::ostringstream playerHealthString;//строка здоровья игрока
						playerHealthString << (int)player.health; //заносим в строку здоровье 
						std::ostringstream TowerHealthString;//строка здоровья игрока
						TowerHealthString << (int)player.healthTower; //заносим в строку здоровье 
						std::ostringstream playerMisString;//строка здоровья игрока
						playerMisString << player.mis; //заносим в строку здоровье 
						std::ostringstream task;//строка текста миссии
						task << getTextMission(SetMission);//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии)
						textmission.setString("\nЗдоровье: " +playerHealthString.str() + "\nЗавершено заданий :" +playerMisString.str() +"/3\n" + task.str() + "\n\n\n\n\n\n\n\n\n\nЗдоровье темной башни:"+ TowerHealthString.str());
						showMissionText = false;//эта строка позволяет убрать все что мы вывели на экране

						std::ostringstream playerScoreString;    // объявили переменную
						std::ostringstream playerDiskString;    // объявили переменную
						playerScoreString << player.PlayerScore;		//занесли в нее число очков, то есть формируем строку
						playerDiskString << player.PlayerDisk;		//занесли в нее число очков, то есть формируем строку
						if (SetMission == 0) text.setString("");
						if (SetMission == 1) text.setString("Криссталлы: " + playerScoreString.str());
						if (SetMission == 3) text.setString("Диски: " + playerDiskString.str());
						break;//выходим , чтобы не выполнить условие "false" (которое ниже)
					}
					case false: {
						textmission.setString("");//если не нажата клавиша таб, то весь этот текст пустой
						text.setString("");
						showMissionText = true;// а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
						break;
					}
					}
				}
				if (!showMissionText) { window.draw(s_quest); window.draw(textmission); }
		}

			window.setView(view);

			textmission.setPosition(view.getCenter().x + 125, view.getCenter().y - 200);//позиция всего этого текстового блока
			text.setPosition(view.getCenter().x + 125, view.getCenter().y - 30);//позиция всего этого текстового блока
			s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 200);//позиция фона для блока

			if (player.PlayerScore >= 20 && !CompleteMission1)
			{
				if (SetMission != 2)
				{
					soundBuffer.loadFromFile("Sounds/qestadd.ogg");//загружаем в него звук
					sound.setBuffer(soundBuffer);//создаем звук и загружаем в него звук из буфера
					sound.setVolume(30);
					sound.play();
				}
				SetMission = 2;
			}
			if (player.PlayerDisk >= 15 && !CompleteMission2)
			{
				if (SetMission != 4)
				{
					soundBuffer.loadFromFile("Sounds/qestadd.ogg");//загружаем в него звук
					sound.setBuffer(soundBuffer);//создаем звук и загружаем в него звук из буфера
					sound.setVolume(30);
					sound.play();
				}
				SetMission = 4;
			}
#pragma region Управление камерой

			if (Keyboard::isKeyPressed(Keyboard::U))
			{
				view.zoom(1.01f);
				CurrentCooficientSizeCam *= 1.01f;
			}
			if (Keyboard::isKeyPressed(Keyboard::J))
			{
				CurrentCooficientSizeCam /= 1.01f;
				view.zoom(0.99f);
			}
#pragma endregion
#pragma region Миссии
			if (Keyboard::isKeyPressed(Keyboard::E))
			{
				if (SetMission == 0 && !CompleteMission1 && !HaveMission)
				{
				SetMission = getCurrentMission(88, 6, player.GetCoord_X(), player.GetCoord_Y(), 1);
				if (SetMission != 0)
				{
					player.ActiveMission1 = true;
					soundBuffer.loadFromFile("Sounds/qestadd.ogg");//загружаем в него звук
					sound.setBuffer(soundBuffer);//создаем звук и загружаем в него звук из буфера
					sound.setVolume(30);
					sound.play();
				}
				}
				if (SetMission == 0 && !CompleteMission2 && !HaveMission)
				{
					SetMission = getCurrentMission(33, 5, player.GetCoord_X(), player.GetCoord_Y(), 3);
					if (SetMission != 0)
					{
						player.ActiveMission2 = true;
						soundBuffer.loadFromFile("Sounds/qestadd.ogg");//загружаем в него звук
						sound.setBuffer(soundBuffer);//создаем звук и загружаем в него звук из буфера
						sound.setVolume(30);
						sound.play();
					}
				}
				if (SetMission == 0 && !CompleteMission3 && !HaveMission)
				{
					SetMission = getCurrentMission(47, 10, player.GetCoord_X(), player.GetCoord_Y(), 5);
					if (SetMission != 0)
					{
						player.ActiveMission3 = true;
						soundBuffer.loadFromFile("Sounds/qestadd.ogg");//загружаем в него звук
						sound.setBuffer(soundBuffer);//создаем звук и загружаем в него звук из буфера
						sound.setVolume(30);
						sound.play();
					}
				}
				if (SetMission == 2)
				{
					SetMission = getCurrentMission(88, 6, player.GetCoord_X(), player.GetCoord_Y(), 0);
					CompleteMission1 = true;
					player.completeMission1 = true;
					player.mis++;
					HaveMission = false;
					player.ActiveMission1 = false;
					soundBuffer.loadFromFile("Sounds/qestfinish.ogg");//загружаем в него звук
					sound.setBuffer(soundBuffer);//создаем звук и загружаем в него звук из буфера
					sound.setVolume(30);
					sound.play();
				}
				if (SetMission == 4)
				{
					SetMission = getCurrentMission(33, 5, player.GetCoord_X(), player.GetCoord_Y(), 0);
					CompleteMission2 = true;
					player.completeMission2 = true;
					player.mis++;
					HaveMission = false;
					player.ActiveMission2 = false;
					soundBuffer.loadFromFile("Sounds/qestfinish.ogg");//загружаем в него звук
					sound.setBuffer(soundBuffer);//создаем звук и загружаем в него звук из буфера
					sound.setVolume(30);
					sound.play();
				}
				if (SetMission == 6)
				{
					SetMission = getCurrentMission(47, 10, player.GetCoord_X(), player.GetCoord_Y(), 7);
					CompleteMission3 = true;
					player.mis++;
					HaveMission = false;
					player.ActiveMission3 = false;
				}
				if (SetMission!=0)
				HaveMission = true;
			}
			if (CompleteMission1 && CompleteMission2)
			{
				TileMap[11][75] = 'C';
				TileMap[12][75] = 'C';
			}
			if (player.healthTower<=0)
			{
				if (SetMission != 7)
				{
					soundBuffer.loadFromFile("Sounds/win.ogg");//загружаем в него звук
					sound.setBuffer(soundBuffer);//создаем звук и загружаем в него звук из буфера
					sound.setVolume(30);
					sound.play();
				}
				SetMission = 7;
				if (player.mis<=3)player.mis++;
				ReplaysAll('l', 'f');
				ReplaysAll('L', 'F');
				ReplaysAll('$', '@');
				ReplaysAll('d', ' ');
				ReplaysAll('D', ' ');
			}
#pragma endregion
#pragma region Общее управление в игре

			//Установка в свиток того, что герой умер
			if (player.health == 0)
			{
				SetMission = 8;
			}
			//Показать в консоле ткущую позицию
			if (Keyboard::isKeyPressed(Keyboard::I))
			{
				std::cout << player.GetCoord_X() << ";" << player.GetCoord_Y() << "\n" << "(" << player.GetCoord_X() / 64 << ";" << player.GetCoord_Y() / 64 << ")" << "\n";
			}
			//Закритие приложения
			if (Keyboard::isKeyPressed(Keyboard::Q))
			{
				window.close();
			}
			//Установка "Чит режима" для проверки работоспособности игры
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				player.health += 1000;
				CompleteMission1 = true;
				player.completeMission1 = true;
				CompleteMission2 = true;
				player.completeMission2 = true;
			}
#pragma endregion
#pragma region Updates
			player.Update(time);		
			npc1.Update(time);
			npc2.Update(time);
			npc3.Update(time);
#pragma endregion

window.clear();

#pragma region Отрисовка карты
			for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if (TileMap[i][j] == '0')  s_map.setTextureRect(DrawMap(2, 2));//если встретили символ , то рисуем  квадратик

					if (TileMap[i][j] == 'f')  s_map.setTextureRect(DrawMap(2, 3));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'F')  s_map.setTextureRect(DrawMap(3, 2));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'C' || TileMap[i][j] == 'c')  s_map.setTextureRect(DrawMap(3, 1));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'W')  s_map.setTextureRect(DrawMap(1, 4));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'w')  s_map.setTextureRect(DrawMap(2, 4));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'p')  s_map.setTextureRect(DrawMap(4, 1));//если встретили символ , то рисуем  квадратик

					if (TileMap[i][j] == 'q')  s_map.setTextureRect(DrawMap(5, 4));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'e')  s_map.setTextureRect(DrawMap(5, 5));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'y')  s_map.setTextureRect(DrawMap(5, 6));//если встретили символ , то рисуем  квадратик

					if (TileMap[i][j] == 't')  s_map.setTextureRect(DrawMap(4, 2));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'd' || TileMap[i][j] == 'D')  s_map.setTextureRect(DrawMap(5, 1));//если встретили символ , то рисуем  квадратик

					if (TileMap[i][j] == 'o')  s_map.setTextureRect(DrawMap(1, 5));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == '9')  s_map.setTextureRect(DrawMap(2, 5));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == '8')  s_map.setTextureRect(DrawMap(3, 5));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == '7')  s_map.setTextureRect(DrawMap(4, 5));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'k')  s_map.setTextureRect(DrawMap(1, 6));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == '6')  s_map.setTextureRect(DrawMap(2, 6));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == '5')  s_map.setTextureRect(DrawMap(3, 6));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == '4')  s_map.setTextureRect(DrawMap(4, 6));//если встретили символ , то рисуем  квадратик

					if (TileMap[i][j] == 'R')  s_map.setTextureRect(DrawMap(3, 4));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'r' || TileMap[i][j] == 'T')  s_map.setTextureRect(DrawMap(4, 4));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 's')  s_map.setTextureRect(DrawMap(1, 1));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == '$')  s_map.setTextureRect(DrawMap(4, 3));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'l')  s_map.setTextureRect(DrawMap(5, 2));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'L')  s_map.setTextureRect(DrawMap(5, 3));//если встретили символ , то рисуем  квадратик

					if (TileMap[i][j] == 'Б')  s_map.setTextureRect(DrawMap(1, 1)); //если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == '_' || TileMap[i][j] == '^')  s_map.setTextureRect(DrawMap(1, 2));//если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == '*')  s_map.setTextureRect(DrawMap(2, 1)); //если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == 'B')  s_map.setTextureRect(DrawMap(3, 3)); //если встретили символ , то рисуем  квадратик
					if (TileMap[i][j] == ' ')  s_map.setTextureRect(DrawMap(1, 1));//если встретили символ s, то рисуем 2й квадратик
					if (TileMap[i][j] == '1' || TileMap[i][j] == '@')  s_map.setTextureRect(DrawMap(1, 3));//если встретили символ s, то рисуем 2й квадратик
					s_map.setPosition(j * 64, i * 64);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 64*64 и мы увидим один квадрат
					window.draw(s_map);//рисуем квадратики на экран
				}
#pragma endregion

#pragma region Отрисовка объектов
			window.draw(player.sprite);
			window.draw(npc1.sprite);
			window.draw(npc2.sprite);
			window.draw(npc3.sprite);

			window.draw(Gate_74_11.sprite);
			window.draw(throne_43_11.sprite);

			if (player.healthTower>0)
			{
				window.draw(tower_124_20.sprite);
			}

			pool_87_14.SetAnimation(true);
			pool_87_14.Update(time, 3);
			window.draw(pool_87_14.sprite);

			window.draw(column_58_8.sprite);
			window.draw(column_61_8.sprite);
			window.draw(column_64_8.sprite);
			window.draw(column_67_8.sprite);
			window.draw(column_70_8.sprite);
			window.draw(column_58_14.sprite);
			window.draw(column_61_14.sprite);
			window.draw(column_64_14.sprite);
			window.draw(column_67_14.sprite);
			window.draw(column_70_14.sprite);

			window.draw(house_92_2.sprite);
			window.draw(house_81_1.sprite);
			window.draw(house_79_15.sprite);
			window.draw(house_94_14.sprite);
			window.draw(house_89_18.sprite);
			window.draw(house_86_2.sprite);

#pragma region Текст(Очки)

#pragma endregion
			if (!showMissionText) window.draw(s_quest);
			window.draw(textmission);//рисую этот текст
			window.draw(text);//рисую этот текст
			window.display();
#pragma endregion

		}
	return 0;
}