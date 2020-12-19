#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

using namespace sf;

/// <summary>
/// Объект
/// </summary>
class Object
{
private:
	String file;
	Image image;
	Texture texture;

	float position_x, position_y;
	float texturerectx, texturerecty;
	float colision_x=0, colision_y=0;
	bool colision = false;
	float width, height;

	bool symbol_on_map=false;
	bool Animation = false;
	float CurrentFrame = 0;
public:
	Sprite sprite;

	/// <summary>
	/// Инициализация
	/// </summary>
	/// <param name="File">Имя исходного файла с объектами</param>
	/// <param name="PositionX">Позиция на карте по X <b>(В БЛОКАХ)</b></param>
	/// <param name="PositionY">Позиция на карте по Y <b>(В БЛОКАХ)</b></param>
	/// <param name="Texture_RectX">Позиция объекта в файле по X<b>(В БЛОКАХ)</b></param>
	/// <param name="Texture_RectY">Позиция объекта в файле по Y<b>(В БЛОКАХ)</b></param>
	/// <param name="Width">Ширина объекта<b>(В БЛОКАХ)</b></param>
	/// <param name="Height">Высота объекта<b>(В БЛОКАХ)</b></param>
	Object(String File, float PositionX, float PositionY, float Texture_RectX, float Texture_RectY, float Width, float Height)
	{
		file = File;
		Texture_RectX--;
		Texture_RectY--;
		texturerectx = Texture_RectX;
		texturerecty = Texture_RectY;
		position_x = (PositionX)*64;
		position_y = (PositionY)*64;
		image.loadFromFile("Images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		width = Width*64;
		height = Height*64;

		sprite.setTextureRect(IntRect(Texture_RectX*64, Texture_RectY*64, width, height));
		sprite.setPosition(position_x, position_y);
	}

	void SymbolOnMap(char Symbol_On_map)
	{
		symbol_on_map = true;
		if (colision_x == 0) colision_x = width;
		if (colision_y == 0) colision_y = height;
		float h = height/ 64;
		float w = width / 64;
		int start_pos[] = { position_y /64,position_x/64 };
		int finish_pos[] = { start_pos[0] + colision_y /64,start_pos[1] + colision_x / 64 };
		int current_pos[] = { 0,0 };
				current_pos[0] = start_pos[0];
				current_pos[1] = start_pos[1];
				while (current_pos[0] != finish_pos[0])
				{
					while (current_pos[1] != finish_pos[1])
					{
						TileMap[current_pos[0]][current_pos[1]] = Symbol_On_map;
						current_pos[1]++;
					}
					if ((int)width % 64 > 0 && !colision) TileMap[current_pos[0]][current_pos[1]] = Symbol_On_map;
					current_pos[1]= start_pos[1];
					current_pos[0]++;
				}
	}

	/// <summary>
	/// Нельзя использовать после SymbolOnMap
	/// </summary>
	/// <param name="PositionX"></param>
	/// <param name="PositionY"></param>
	void SetPosition(int PositionX, int PositionY)
	{
		if (!symbol_on_map)
		{
			PositionX+=1;
			PositionY+=1;
			position_x = PositionX*64;
			position_y = PositionY*64;
			sprite.setPosition(PositionX * 64, PositionY * 64);
		}
	}

#pragma region SetColision

	void SetColision(int X, int Y)
	{
		if (!colision)
		{
			colision = true;
			colision_x = X * 64;
			colision_y = Y * 64;
		}
	}
	void SetColision(float X, float Y)
	{
		if (!colision)
		{
			colision = true;
			colision_x = X;
			colision_y = Y;
		}
	}
#pragma endregion
#pragma region GetPosition
	float GetPosition(char Type)
	{
		switch (Type)
		{
		case 'X':
			return position_x;
		case 'Y':
			return position_y;
		default:
			break;
		}
	}
	int GetPositionInBlocks(char Type)
	{
		switch (Type)
		{
		case 'X':
			return position_x / 64+1;
		case 'Y':
			return position_y / 64+1;
		default:
			break;
		}
	}
#pragma endregion

	void ReverseRotate(char Direction)
	{
		switch (Direction)
		{
		case 'X': 
			sprite.setScale(-1, 1);
		case 'Y':
			sprite.setScale(1, -1);
		default:
			break;
		}
	}

	void Update(float time, int countofframe)
	{
		if (Animation)
		{
			if (countofframe == 3)
			{
				CurrentFrame += 0.01 * time;
				if (CurrentFrame >= 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect((texturerectx) * 64 + int(CurrentFrame) * 192, texturerecty * 64, width, height));
			}
		}
	}

	void SetAnimation(bool value)
	{
		Animation = value;
	}

};