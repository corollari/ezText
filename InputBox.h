#pragma once
#include "lib\TextSprite.h"
#include <string>

class InputBox {
public:
	InputBox(int);
	std::string getInput();
	void update();
	void draw(int, int);
	void setInput(std::string);
	TextSprite* getSprite();
private:
	std::string input;
	TextSprite sprite;
	int maxCharCount;
};