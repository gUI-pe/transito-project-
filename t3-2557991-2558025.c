#include "trabalho3.h"
#include <stdio.h>
#include "gerador_de_testes.h"

void zeraBackGround(Imagem3C *img, Imagem3C *bg);

int contaVeiculos (Imagem3C* img, Imagem3C* bg,
                   int contagem [N_TIPOS_DE_VEICULOS]);

void suavizaImagemX (Imagem3C* img);

int contaVeiculos (Imagem3C* img, Imagem3C* bg, int contagem [N_TIPOS_DE_VEICULOS])
{
    zeraBackGround(img, bg);

    return 1;
}
//void suavizaImagemX (Imagem3C* img)
void zeraBackGround(Imagem3C *img, Imagem3C *bg)
{
    int i, j;

    int altura = img->altura;
    int largura = img->largura;

    suavizaImagemX(img);
    suavizaImagemX(bg);

    for(i = 0; i < altura; i++)
    {
        for(j = 0; j < largura; j++)
        {
            if(img->dados[0][i][j] < bg->dados[0][i][j] *1.25 && img->dados[0][i][j] > bg->dados[0][i][j] * 0.75 && img->dados[1][i][j] < bg->dados[1][i][j] *1.25 && img->dados[1][i][j] > bg->dados[1][i][j] * 0.75 && img->dados[2][i][j] < bg->dados[2][i][j] *1.25 && img->dados[2][i][j] > bg->dados[2][i][j] *0.75)
            {
                img->dados[0][i][j] = (unsigned char) 0;
                img->dados[1][i][j] = (unsigned char) 0;
                img->dados[2][i][j] = (unsigned char) 0;
            }
        }
    }

    for(i = 0; i < img->altura/8; i++)
    {
        for(j = 0; j < largura; j++)
        {
            img->dados[0][i][j] =  0;
            img->dados[1][i][j] =  0;
            img->dados[2][i][j] =  0;
        }
    }

    for(i = 7 * img->altura/8; i < img->altura; i++)
    {
        for(j = 0; j < largura; j++)
        {
            img->dados[0][i][j] =  0;
            img->dados[1][i][j] =  0;
            img->dados[2][i][j] =  0;
        }
    }

    for(i = 0; i < altura; i++)
    {
        for(j = 11 * img->largura/13; j < img->largura; j++)
        {
            img->dados[0][i][j] =  0;
            img->dados[1][i][j] =  0;
            img->dados[2][i][j] =  0;
        }
    }

    char foostring [64];
    sprintf (foostring, "t%d.bmp", i);
    salvaImagem3C (img, foostring);
}

void suavizaImagemX (Imagem3C* img)
{
	unsigned long row, col;
	int canal, peso_centro;
	Imagem3C* copia; /* Precisamos guardar os dados originais. Seria bem mais eficiente guardar apenas uma janela, mas copiar tudo é bem mais simples... */
	copia = copiaImagem (img);

	peso_centro = 20 ;
	for (canal = 0; canal < 3; canal++)
		for (row = 1; row < img->altura-1; row++)
			for (col = 1; col < img->largura-1; col++)
				img->dados [canal][row][col] = (copia->dados [canal][row-1][col-1] +
				                                copia->dados [canal][row-1][col]*2 +
												copia->dados [canal][row-1][col+1] +
			                                    copia->dados [canal][row][col-1]*2 +
												copia->dados [canal][row][col]*peso_centro +
												copia->dados [canal][row][col+1]*2 +
												copia->dados [canal][row+1][col-1] +
												copia->dados [canal][row+1][col]*2 +
												copia->dados [canal][row+1][col+1])/(peso_centro + 12);
	destroiImagem3C (copia);
}

