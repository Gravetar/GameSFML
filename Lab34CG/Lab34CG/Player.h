#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "view.h" //Подключение камеры

using namespace sf;
/// <summary>
/// Класс игрока
/// </summary>
class Player
{

#pragma region Основа
private:
	float x, y;
	float CurrentFrame = 0;
public:
	bool ActiveMission1 = false;
	bool ActiveMission2 = false;
	bool ActiveMission3 = false;
	bool completeMission1 = false;
	bool completeMission2 = false;
	bool defeat = false;

	SoundBuffer stepBuffer;//создаём буфер для звука
	Sound step;
	SoundBuffer soundBufferP;//создаём буфер для звука
	Sound soundP;

	bool DestroyTower = false;
	int PlayerScore, PlayerDisk, mis=0;
	float health;
	float healthTower = 5000;
	bool life;
	float w, h, dx, dy, speed;
	int direction;
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	float Time;
	/// <summary>
	/// Конструктор для Player
	/// </summary>
	/// <param name="F">Имя файла</param>
	/// <param name="X">Координата X</param>
	/// <param name="Y">Координата Y</param>
	/// <param name="W">Ширина</param>
	/// <param name="H">Высота</param>
	Player(String F, float X, float Y, float W, float H)
	{
		dx = 0; dy = 0; speed = 0; direction = 0; PlayerScore = 0; PlayerDisk = 0; life = true; health = 100;
		w = W; h = H;
		file = F;
		image.loadFromFile("Images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
		stepBuffer.loadFromFile("Sounds/step.ogg");//загружаем в него звук
		step.setBuffer(stepBuffer);//создаем звук и загружаем в него звук из буфера
		step.setVolume(10);
	}
#pragma endregion

	void Update(float time)
	{
		switch (direction)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
			break;
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		sprite.setPosition(x, y);


		interactionWithMap(time);

		control(time);
		if (health <= 0) { life = false; speed = 0; }
	}

	void control(float time)
	{
		Time = time;
		if (life)
		{
			#pragma region Управление Персонажем
			if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
			{
				if (step.getStatus()!=SoundSource::Status::Playing)
				{
					step.play();
				}
				speed = 0.3;
				direction = 1;
				CurrentFrame += 0.01 * time;
				if (CurrentFrame > 6) CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(w * int(CurrentFrame), h, w, h));
				PlayerGoordForView(GetCoord_X(), GetCoord_Y());
			}
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
			{
				if (step.getStatus() != SoundSource::Status::Playing)
				{
					step.play();
				}
				speed = 0.3;
				direction = 0;
				CurrentFrame += 0.01 * time;
				if (CurrentFrame > 6) CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(w * int(CurrentFrame), h * 2, w, h));
				PlayerGoordForView(GetCoord_X(), GetCoord_Y());

			}
			if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
			{
				if (step.getStatus() != SoundSource::Status::Playing)
				{
					step.play();
				}
				speed = 0.3;
				direction = 3;
				CurrentFrame += 0.01 * time;
				if (CurrentFrame > 6) CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(w * int(CurrentFrame), h * 3, w, h));
				PlayerGoordForView(GetCoord_X(), GetCoord_Y());
			}
			if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
			{
				if (step.getStatus() != SoundSource::Status::Playing)
				{
					step.play();
				}
				speed = 0.3;
				direction = 2;
				CurrentFrame += 0.01 * time;
				if (CurrentFrame > 6) CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(w * int(CurrentFrame), h * 4, w, h));
				PlayerGoordForView(GetCoord_X(), GetCoord_Y());
			}
			if (Keyboard::isKeyPressed(Keyboard::LShift) && speed != 0)
			{
				speed += 0.5;
				CurrentFrame += 0.01 * time;
			}
			if (Keyboard::isKeyPressed(Keyboard::LControl) && speed != 0)
			{
				speed -= 0.15;
			}
			if (Keyboard::isKeyPressed(Keyboard::Z))
			{
				speed = 0;
				CurrentFrame += 0.01 * time;
				if (CurrentFrame > 5) CurrentFrame -= 5;
				sprite.setTextureRect(IntRect(w * int(CurrentFrame), h * 6, w, h));
				for (int i = y / 64; i < (y + h) / 64; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 64*64, которые мы окрашивали в 9 уроке. про условия читайте ниже.
					for (int j = x / 64; j < (x + w) / 64; j++)//икс делим на 64, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 64*64, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 64 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
					{
						if (TileMap[i][j] == 'D')
						{
							if (healthTower >= 0)
							{
								if (!completeMission1) health -= 0.03 * time;
								if (completeMission2) healthTower -= 0.3 * time;
								else healthTower -= 0.03 * time;
								if (soundP.getStatus() != SoundSource::Status::Playing)
								{
									soundBufferP.loadFromFile("Sounds/attack.ogg");//загружаем в него звук
									soundP.setBuffer(soundBufferP);//создаем звук и загружаем в него звук из буфера
									soundP.setVolume(10);
									soundP.play();
								}
							}
							else
							{
								DestroyTower = true;
							}
						}
					}
			}
#pragma endregion
		}
		else
		{
			if (!defeat)
			{
				soundBufferP.loadFromFile("Sounds/defeat.ogg");//загружаем в него звук
				soundP.setBuffer(soundBufferP);//создаем звук и загружаем в него звук из буфера
				soundP.setVolume(30);
				soundP.play();
				defeat = true;
			}
			health = 0;
			CurrentFrame += 0.001 * time;
			if (CurrentFrame >= 3) CurrentFrame = 3;
			sprite.setTextureRect(IntRect(w * int(CurrentFrame), h*5, w, h));
		}
	}

	void interactionWithMap(float time)//ф-ция взаимодействия с картой
	{
		for (int i = y / 64; i < (y + h) / 64; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 64*64, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 64; j < (x + w) / 64; j++)//икс делим на 64, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 64*64, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 64 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (ActiveMission2)
				{
					if (TileMap[i][j] == 'q' || TileMap[i][j] == 'e' || TileMap[i][j] == 'y')
					{
						PlayerDisk += 1;
						if (TileMap[i][j] == 'q') TileMap[i][j] = '*';
						if (TileMap[i][j] == 'e' || TileMap[i][j] == 'y') TileMap[i][j] = ' ';
						soundBufferP.loadFromFile("Sounds/diskadd.ogg");//загружаем в него звук
						soundP.setBuffer(soundBufferP);//создаем звук и загружаем в него звук из буфера
						soundP.setVolume(30);
						soundP.play();
					}
				}
				if (TileMap[i][j] == 's')
				{
					if (health<100) health += 0.03*time;
				}
				if (TileMap[i][j] == '$')
				{
					health -= 10;
					TileMap[i][j] = '@';
					soundBufferP.loadFromFile("Sounds/dmg.ogg");//загружаем в него звук
					soundP.setBuffer(soundBufferP);//создаем звук и загружаем в него звук из буфера
					soundP.setVolume(30);
					soundP.play();
				}
				if (TileMap[i][j] == '0' || TileMap[i][j] == 'Б' || TileMap[i][j] == '_' || TileMap[i][j] == 'f' || TileMap[i][j] == 'F' || TileMap[i][j] == 'W' || TileMap[i][j] == 'T' || TileMap[i][j] == 'c'
					|| TileMap[i][j] == 'o' || TileMap[i][j] == '9' || TileMap[i][j] == '8' || TileMap[i][j] == '7' || TileMap[i][j] == 's' || TileMap[i][j] == 'l' || TileMap[i][j] == 'L' || TileMap[i][j] == 'd')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy > 0)//если мы шли вниз,
					{
						y = i * 64 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					}
					if (dy < 0)
					{
						y = i * 64 + 64;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
					}
					if (dx > 0)
					{
						x = j * 64 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
					}
					if (dx < 0)
					{
						x = j * 64 + 64;//аналогично идем влево
					}
				}
				if (ActiveMission1)
				{
					if (TileMap[i][j] == 'k' || TileMap[i][j] == '6' || TileMap[i][j] == '5' || TileMap[i][j] == '4') { //если символ равен 's' (камень)
						PlayerScore++;
						TileMap[i][j] = '*';
						soundBufferP.loadFromFile("Sounds/crystaladd.ogg");//загружаем в него звук
						soundP.setBuffer(soundBufferP);//создаем звук и загружаем в него звук из буфера
						soundP.setVolume(30);
						soundP.play();
					}
				}
				if (TileMap[i][j] == 't')
				{
					Teleport(95, 10);
					soundBufferP.loadFromFile("Sounds/diskadd.ogg");//загружаем в него звук
					soundP.setBuffer(soundBufferP);//создаем звук и загружаем в него звук из буфера
					soundP.setVolume(30);
					soundP.play();
				}
			}
	}
	int interactionWithNPC(int X, int Y, int W, int H, int Mission)
	{
		X *= 64; Y *= 64; W *= 64; H *= 64;
		if (GetCoord_X() >= X && GetCoord_X() <= X + W && GetCoord_Y() >= Y && GetCoord_X() <= Y + H)
			return Mission;
	}

	float GetCoord_X()
	{
		return x;
	}
	float GetCoord_Y()
	{
		return y;
	}

	void Teleport(int X, int Y)
	{
		x = X*64; y = Y*64;
		sprite.setPosition(x, y);
		PlayerGoordForView(GetCoord_X(), GetCoord_Y());
	}

};