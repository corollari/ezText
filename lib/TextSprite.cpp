#include "TextSprite.h"
#include "video.h"
#include <vector>

TextSprite::TextSprite() {
	//Weas
}

TextSprite::TextSprite(const char* text, int size) {
	Create(text, size);
}

void TextSprite::Create(const char* text, int size) {
	m_color = { 0,0,0,0xFF };
	m_size = size;
	m_textoRenderizado = NULL;
	Update(text);
}

TextSprite::~TextSprite() {
	SDL_DestroyTexture(m_textoRenderizado);
}

struct fontAllocHolder {
	TTF_Font* pFont;
	int size;
};

std::vector<fontAllocHolder> fontAllocList;


TTF_Font* fontAlloc(int size) {
	int i = 0;
	TTF_Font* font;
	while (i < fontAllocList.size() && fontAllocList[i].size != size) {
		i++;
	}
	if (i < fontAllocList.size()) {
		return fontAllocList[i].pFont;
	}
	else {
		fontAllocList.push_back({ TTF_OpenFont("Program/data/fonts/arial.ttf", size), size });
		return fontAllocList.back().pFont;
	}
}

void TextSprite::Update(const char* text) {
	if(m_textoRenderizado)
		SDL_DestroyTexture(m_textoRenderizado);

	if (!*text) //SDL no creará una textura si se le pasa una string vacía así que le meto un espacio en blanco para simular el mismo efecto
		text = " ";

	SDL_Surface* textSurface = TTF_RenderText_Blended(fontAlloc(m_size), text, m_color);
	if (textSurface != NULL) {
		m_textoRenderizado = SDL_CreateTextureFromSurface(g_Video.renderer, textSurface);

		//Copiado de la libreria que nos dieron (no sé que hace pero lo añado para manterner compatibilidad con el tipo Sprite)
		SDL_SetTextureBlendMode(m_textoRenderizado, SDL_BLENDMODE_BLEND); // Indicamos al hardware de que este sprite va a necesitar c?culos de alpha blending (para que no se vea el rect?gulo donde no hay dibujo)

		scalex = textSurface->w;
		scaley = textSurface->h;
	}
	SDL_FreeSurface(textSurface);
}

void TextSprite::SetScale(int size) {
	m_size = size;
}

void TextSprite::Draw(int x, int y) {
	//Copy paste del metodo Draw de la clase Sprite

	// La SDL necesita que le especifiquemos un par de rectángulos en su formato para poder dibujar
	SDL_Rect srcrect;
	SDL_Rect dstrect;

	// Posición de la esquina superior izquierda
	srcrect.x = 0;
	srcrect.y = 0;

	// Número de píxels a leer
	srcrect.w = scalex;
	srcrect.h = scaley;

	// Posición de la esquina superior izquierda al dibujar
	dstrect.x = x;
	dstrect.y = y;

	/* Original
	dstrect.x = x - static_cast<int>(frame->hx * scalex);
	dstrect.y = y - static_cast<int>(frame->hy * scaley);
	*/

	// Tamaño visible al dibujar
	dstrect.w = static_cast<int>(scalex);
	dstrect.h = static_cast<int>(scaley);

	SDL_RenderCopy(g_Video.renderer, m_textoRenderizado, &srcrect, &dstrect);

}

int TextSprite::getScaleY() const {
	return scaley;
}

int TextSprite::getScaleX() const {
	return scalex;
}

void TextSprite::SetColor(char r, char g, char b, char alpha) {
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = alpha;
}