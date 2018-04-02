#pragma once
#include <SDL_ttf.h>

class TextSprite{
public:
	TextSprite(const char*, int size = 20);
	TextSprite();
	//TextSprite(TextSprite&);
	~TextSprite();
	void Create(const char*, int size = 20);
	void Update(const char*);
	void SetScale(int);
	void Draw(int x, int y);
	void SetColor(char r, char g, char b, char alpha = 0xFF);

	int getScaleY() const;
	int getScaleX() const;
private:
	SDL_Texture* m_textoRenderizado;
	SDL_Color m_color;

	int m_size;
	float scaley;
	float scalex;
};