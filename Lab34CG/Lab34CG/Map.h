#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()
#include <random>
const int HEIGHT_MAP = 25;//размер карты высота
const int WIDTH_MAP = 130;//размер карты ширина 
int getRandomNumber(int min, int max);
void ReplaysRnd(char value1, char value2);

//Основная карта
sf::String TileMap[HEIGHT_MAP] = {
	"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
	"0@f@@@ff@@@@@@fff@@@@@@fff@@@@@f@@@@ff@@@ff@@@f@@@@@f@@@@@@@@ff@@@fff@@@@@@fff o ====   o     e   0ffffffllllfflllllfffflllfffff0",
	"0@@@f@@@@@@@f@@@@@f@ff@@@@@@f@@@@f@@@@@@@@@@f@@@f@@@@@@f@@@@@@@@f@@@@@ff@@@@@@   ==== ===== ====  0ffffffff@@@$@@@@@@$@@@@fff ff0",
	"0000000000000000000000000000000000000000WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW @  ==== ===== ====  0f fff@@@@ffffy  ffff@@fffffff0",
	"0________________________________****kk*WwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwW  @ ==== ===== ====  0ffff  @$$$fffffffff@@ffff fff0",
	"0_****kk**********______________*****kk*WwWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWwW  @ ====   @   ====  0fllf f$$$$fff$ff$$f@@fff f$ff0",
	"0_************kk****_____******kk***k***WwWCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCWwW  @   @    @   ====  0flll f$$$$fffff$fff$@ffllllff0",
	"0*****____________**__********___*******WwWCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCWwW  @@  @   @ @    @   0fll  f$$$$ff  fffff@@fffll$$f0",
	"0***_______*****__*q****q**_____________WwWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCWwW   @@@@@@@@@@@@@@    0fff@@$@@fffffff$fff@$ff  ffff0",
	"0______******_____***___**_________**___WwWRRRRRRRRrrRWCCCCCCCCCCCCCCCCCCCWwW  o   e  @ffff@   o  @@@$@@@ffffllllfffff@@fffllfff0",
	"0___****kk***__*****__***************___WwWRRRRrrRRRRRWWWCCCCCCCCCCCCCCCCCWWW     o   @@ff@@      @@@@@$@fffff flllfff$@fff$ffff0",
	"0___**___****__*****__******k********___WwWTTRrrrrrrrrRRRpppppppppppppppppw0w@@@@@@@@@@@ff@@ o e  0fffffffff   o  yfff@@@@@@$@ff0",
	"0___**____***__***____**___________**___WwWTTRrrrrrrrrRRRpppppppppppppppppw0w@@@@@@@@@@ffff@      0fff  ffff o  o  fff@$$@@@@@ff0",
	"0___*************___****________________WwWRRRRrrRRRRRWWWCCCCCCCCCCCCCCCCCWWW      o  @@@@@@      0ffffff$ff  $y $ ffffffff@@@ff0",
	"0___******k***q**___**__________**kk**__WwWRRRRRRRRrrRWCCCCCCCCCCCCCCCCCCCWwW  o      @sss@   =====ff fffff  $  $  $ ffffff$@@ff0",
	"0___**______________**_______**_**______WwWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCWwW  =====  @sss@   =====ff$ff fff   $ y fffff$ff@$@ff0",
	"0___**_______*****k*****q*********______WwWCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCWwW  =====  @sss @@@=====fffffffffff $fffffffffff@@$ff0",
	"0___*k**_____***kk*******k******________WwWCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCWwW  =====  @  e    =====ff ff@@@@@@@@@@@@@@@@$@$@$@ff0",
	"0_____**______****___________**_________WwWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWwW    @    @  ====     0fllff@@@@$$$$$@@@@@@@@$@$@@ff0",
	"0_^^^^**________***__________**_________WwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwW    @ o  @  ====     0flff$$$@fffflllllffffffllffff0",
	"0_^_^^*******_____****_______***k*______WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW    @    @  ====     0fff@@@fffllllffffy fffflDdddd0",
	"0_^_____**k**_______*****______**********      @ oo  @          o   @ @   @  @   @    @  ====  o  0fff@@@@@@@$$@@@@@@@@@@@@Ddddd0",
	"0_^^___t__**********************_********   @     @@    @@  @@@  @ @@ @@ @@@@@@@@@@@@@@@ ====  e  0fff@@@@@@@@@@@@@@@@@@@@@Ddddd0",
	"0__^^^^^_____****k****q****_____________0  o    @    @ @  o       @    @   @    o      @@@@@      0 ffffffff ffflllfffllllfDdddd0",
	"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
};

//Функция генерации случайного числа
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);


};

//Функция расстановки случайных изображений объектов(2 отображения)
void ReplaysRnd(char value1, char value2)
{
	int Rnd;
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			Rnd = getRandomNumber(1, 2);
			if (TileMap[i][j] == value1)
			{
				if (Rnd == 2) TileMap[i][j] = value2;
			}
		}
};
//Функция расстановки случайных изображений объектов(4 отображения)
void ReplaysRnd4(char value1, char value2, char value3, char value4)
{
	int Rnd;
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			Rnd = getRandomNumber(1, 4);
			if (TileMap[i][j] == value1)
			{
				if (Rnd == 2) TileMap[i][j] = value2;
				if (Rnd == 3) TileMap[i][j] = value3;
				if (Rnd == 4) TileMap[i][j] = value4;
			}
		}
};
//Функция замены всех объектов одного типа на объекты другого типа
void ReplaysAll(char value1, char value2)
{
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == value1)
			{
				TileMap[i][j] = value2;
			}
		}
};

/*
' '		-Трава
'0'		-Стена
'f'+'F'	-Дерево
'_'		-Стена пещеры
'*'		-Дорога пещеры
*/