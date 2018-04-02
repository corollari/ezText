#include "InputBox.h"
#include"lib\keyboard.h"

InputBox::InputBox(int nChars) { //El int que se la pasa es el máximo numero de carácteres que puede contener la caja
	maxCharCount = nChars;
	input = "";
	sprite.Create(input.c_str());
}

std::string InputBox::getInput() {
	return input;
}

void InputBox::setInput(std::string inputString) {
	input = inputString;
	sprite.Update(input.c_str());
}

TextSprite* InputBox::getSprite() {
	return &sprite;
}

void InputBox::update() {
	bool render = false;
	if (Keyboard_GetKeyTrg(KEYBOARD_BACKSPACE)) {
		if (input.size() > 0) {
			input.pop_back();
			render = true;
		}
	}
	else if (Keyboard_GetKeyTrg(KEYBOARD_C) && SDL_GetModState() & KMOD_CTRL) {
		SDL_SetClipboardText(input.c_str());
	}
	else if (Keyboard_GetKeyTrg(KEYBOARD_V) && SDL_GetModState() & KMOD_CTRL) {
		if (input.size() < maxCharCount) {
			input += SDL_GetClipboardText();
			render = true;
		}
	}
	else {
		for (char i = 32; i < 127; i++) {
			if (Keyboard_GetKeyTrg(i)) {
				if (input.size() < maxCharCount) {
					input += i;
					render = true;
				}
				break;
			}
		}
	}
	if(render)
		sprite.Update(input.c_str());
}

void InputBox::draw(int x, int y) {
	sprite.Draw(x, y);
}