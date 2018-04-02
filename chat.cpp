#include "chat.h"

const int pixelsBetweenLines = 2;
const int pixelsBetweenMessages = 5;
const int messageSenderFontSize = 25;
const int messageFontSize = 20;
const int numCharToBreakLine = 10;

Chat::Chat() {
	m_maxPixelLength = Position(SCREEN_WIDTH / 3, SCREEN_HEIGHT); //Default chat window size
}

void Chat::draw(Position printPosition) {
	for (int i = (m_history.size() - 1); i >= 0; i--) {
		if (printPosition.getY() > SCREEN_HEIGHT) {
			m_removeMessage(i);
			continue;
		}
		m_history[i].sender->Draw(printPosition.getX(), printPosition.getY());
		int addOffsetBeginning = m_history[i].sender->getScaleX();
		for (int j = 0; j < m_history[i].msg.size(); j++) {
			m_history[i].msg[j]->Draw(printPosition.getX() + addOffsetBeginning, printPosition.getY());
			printPosition.setY(printPosition.getY() + m_history[i].msg[j]->getScaleY() + pixelsBetweenLines);
			addOffsetBeginning = 0;
		}
		printPosition = printPosition + Position(0, pixelsBetweenMessages);
	}
}

void Chat::setSize(Position newSize) {
	m_maxPixelLength = newSize;
}

void Chat::addMessage(string sender, string messageToAdd){
	m_history.push_back(struct message());
	m_history.back().sender =new TextSprite(sender.c_str(), messageSenderFontSize);
	messageToAdd = ": " + messageToAdd; //Añadir formato al texto aquí
	int addOffsetBeginning = m_history.back().sender->getScaleX(); //Para manejar la primera linea, en la que hay que tener en cuenta el offset causado por el texto de sender
	TextSprite testLength; //Holds the sprite being tested, used for efficiency purposes
	string tempString;
	while (messageToAdd.size()) {
		int lengthLine = ((m_maxPixelLength.getX() < messageToAdd.size()) ? m_maxPixelLength.getX() : messageToAdd.size()); //Assumes the absolute minimum number of pixels a character could span is 1
		
		do {
			tempString = messageToAdd.substr(0, lengthLine);
			testLength.Create(tempString.c_str(), messageFontSize);
			for (int startingValue = --lengthLine; (startingValue - lengthLine) < numCharToBreakLine && messageToAdd[lengthLine] != ' '; lengthLine--) {}
		} while ((addOffsetBeginning + testLength.getScaleX()) >= m_maxPixelLength.getX());

		m_history.back().msg.push_back(new TextSprite(tempString.c_str(), messageFontSize)); //Arreglar esta basura
		//m_history.back().msg.back().Create(tempString.c_str(), messageFontSize);
		messageToAdd.erase(0, tempString.size());
		addOffsetBeginning = 0;
	}

}

void Chat::m_removeMessage(int index) {
	delete m_history[index].sender;
	for (int i = 0; i < m_history[index].msg.size(); i++) {
		delete m_history[index].msg[i];
	}
	m_history.erase(m_history.begin() + index);
}