#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class NPC
{
private:
	float x, y;
	float CurrentFrame = 0;
	int mission;
	int rectx; int recty;
	int ZoneMissionX, ZoneMissionY, ZoneMissionWX, ZoneMissionHX;
public:
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	float w, h;

	/// <summary>
	/// Конструктор для NPC
	/// </summary>
	/// <param name="F">Имя файла</param>
	/// <param name="X">Координата X</param>
	/// <param name="Y">Координата Y</param>
	/// <param name="W">Ширина</param>
	/// <param name="H">Высота</param>
	NPC(String F, float X, float Y, float W, float H, int Rectx, int Recty, int Mission)
	{
		mission = Mission;
		w = W*64; h = H*64;
		rectx = Rectx*64; recty = Recty*64;
		file = F;
		image.loadFromFile("Images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X*64; y = Y*64;
		sprite.setTextureRect(IntRect(Rectx*64, Recty*64, w, h));
		sprite.setPosition(x, y);
	}
#pragma endregion

	void Update(float time)
	{
		CurrentFrame += 0.001 * time;
		if (CurrentFrame >= 2) CurrentFrame -= 2;
		sprite.setTextureRect(IntRect(rectx + int(CurrentFrame) * 64 , recty, w, h));
	}
};
