#pragma once
#include <string>
#include <vector>
#include "position.h"
#include "lib\TextSprite.h"

using namespace std;

struct message {
	TextSprite* sender;
	vector<TextSprite*> msg;
};


class Chat { //implementado como objeto porque en un futuro puede haber varios chats en paralelo
public:
	Chat();
	void addMessage(string sender, string message);
	void draw(Position);
	void setSize(Position);
private:
	void m_removeMessage(int index);
	vector<message> m_history;
	Position m_maxPixelLength;
};