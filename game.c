#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

// Structs

typedef struct _Bubble
{
	bool isStatic;
	SDL_Rect rect;
	SDL_Surface* image;
	
}bubble;

// Valores Globais

const int TELA_LARGURA = 1080;
const int TELA_ALTURA = 720;

// Declarações de Funções

bool inicio();
bool carregarMidia();
SDL_Surface* imageLoader(char nome[]);
bubble criadorDeBubbles(bool isStatic, SDL_Rect rect, SDL_Surface* image);
void fps();
void encerramento();

// Variáveis Globais

SDL_Window* janelaPrincipal = NULL;
SDL_Surface* surfacePrincipal = NULL;
SDL_Surface* bolas = NULL;
SDL_Surface* background = NULL;
int i, j;

SDL_Rect rBola = {428,576,100,100};
bubble level[5][10];
bubble mainBall;

int main(int argc, char **argv)
{
//	Criando variáveis do jogo
	
	bool stop = false;
	SDL_Event event;
	mainBall = criadorDeBubbles(false,rBola,bolas);
	for(i = 0; i < 5; i++)
	{
		for (j = 0; j < 10; j++)
		{
			SDL_Rect boi = {100*j + 5,100*i + 5,100,100};
			level[i][j] = criadorDeBubbles(true,boi,bolas);
		} /**/
	}
// Startup sequence

	if (!inicio())
	{
		puts("Erro de inicio");
	}
	else
	{
		if (!carregarMidia())
		{
			puts("Midia error!");
		}
		else 
		{
// Out-of-loop commands (strt)
			SDL_SetColorKey(bolas, true , SDL_MapRGB(bolas->format, 0xFF, 0xFF, 0xFF));
/**/		
// Out-of-loop commands (end)
			while (!stop)
			{
// Before-poll commands (strt)
				SDL_UpdateWindowSurface(janelaPrincipal);
				fps();
// Before-poll commands (end)
				while (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
						case SDL_QUIT:
							stop = true;
							break;
						case SDL_KEYDOWN:
							switch (event.key.keysym.sym)
							{
								case SDLK_a:
									rBola.x-=2;
									printf("x: %i// y: %i\n",rBola.x,rBola.y);
									break;
								case SDLK_d:
									rBola.x+=2;
									printf("x: %i// y: %i\n",rBola.x,rBola.y);
									break;
								case SDLK_s:
									rBola.y+=2;
									printf("x: %i// y: %i\n",rBola.x,rBola.y);
									break;
								case SDLK_w:
									rBola.y-=2;
									printf("x: %i// y: %i\n",rBola.x,rBola.y);
									break;
							}
					}
// After-poll commands (strt)					
// After-poll commands (end)
				}
			}
		}
	}
	
	encerramento();
	
	return 0;
}

bool inicio()
{
	bool sucesso = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		printf("SDL could not initialize! Error: %s\n", SDL_GetError());
		sucesso = false;
	}
	else
	{
		janelaPrincipal = SDL_CreateWindow("Boboshooter 2K17", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TELA_LARGURA, TELA_ALTURA, SDL_WINDOW_SHOWN);
		if (janelaPrincipal == NULL)
		{
			printf("The window could not be initialized! Error: %s\n", SDL_GetError());
			sucesso = false;
		}
		else
		{
/*			int imgFlags = IMG_INIT_JPG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("Failed to initialize IMG functions! Error: %s\n", IMG_GetError());
				sucesso = false;
			}
			else */
//			{
				surfacePrincipal = SDL_GetWindowSurface(janelaPrincipal);
		}
	}
	
	return sucesso;
}

bool carregarMidia()
{
	bool sucesso = true;
	bolas = imageLoader("bola.bmp");
	if (bolas == NULL) sucesso = false;
	background = imageLoader("TEMPbackground.bmp");
	if (background == NULL) sucesso = false;

	return sucesso;
}

SDL_Surface* imageLoader(char nome[])
{
	SDL_Surface* surface = NULL;
	surface = SDL_LoadBMP(nome);
	if (surface == NULL)
	{
		printf("Error at printing image %s! Error: %s\n", nome, SDL_GetError());
	}
	
	return surface;
}

bubble criadorDeBubbles(bool isStatic, SDL_Rect rect, SDL_Surface* image)
{
	bubble butt;
	butt.isStatic = isStatic;
	butt.rect = rect;
	butt.image = image;
	
	return butt;
}

void fps()
{
	SDL_BlitSurface(background, NULL ,surfacePrincipal, NULL);
	SDL_BlitSurface(bolas, NULL ,surfacePrincipal, &rBola);
	for(i = 0; i < 5; i++)
	{
		for (j = 0; j < 10; j++)
		{
			SDL_BlitSurface(level[i][j].image,NULL,surfacePrincipal,&level[i][j].rect);
		}
	}
}

void encerramento()
{
	SDL_DestroyWindow(janelaPrincipal);
	janelaPrincipal = NULL;
	SDL_Quit();
}
