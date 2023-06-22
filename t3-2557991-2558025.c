#include "trabalho3.h"
#include "imagem.h"
#include <stdio.h>


void zeraBackGround(Imagem3C *img, Imagem3C *bg);

int contaVeiculos (Imagem3C* img, Imagem3C* bg,
                   int contagem [N_TIPOS_DE_VEICULOS]);

void suavizaImagemX (Imagem3C* img);

Imagem3C* copiaImagemX (Imagem3C* img);

Imagem3C* criaImagem3CX (int largura, int altura);

int contaVeiculos (Imagem3C* img, Imagem3C* bg, int contagem [N_TIPOS_DE_VEICULOS])
{
    zeraBackGround(img, bg);


    int i,j,tamanho, total;
    tamanho = 0;
    total = 0;

    for(i = 0; i < 4; i++)
    {
        contagem[i] = 0;
    }

    for(i = img->altura/8 - 10 + 50; i < 7 * img->altura/8; i+= 100)
    {
        for(j = 0; j < 11 * img->largura/13; j++)
        {
           if(img->dados[0][i][j] == 0 && img->dados[1][i][j] == 0 && img->dados[2][i][j] == 0)
           {
                if(img->dados[0][i][j + 1] == 0 && img->dados[1][i][j + 1] == 0 && img->dados[2][i][j + 1] == 0)
                {
                    if(img->dados[0][i][j + 2] == 0 && img->dados[1][i][j + 2] == 0 && img->dados[2][i][j + 2] == 0)
                    {
                        if(tamanho > 60)
                        {
                            if(tamanho > 150)
                            {
                                if(tamanho > 330)
                                {
                                    contagem[3]++;
                                    tamanho = 0;
                                }
                                else
                                {
                                    contagem[2]++;
                                    tamanho = 0;
                                }
                            }
                            else
                            {
                                contagem[1]++;
                                tamanho = 0;
                            }
                        }
                        else
                            tamanho = 0;
                    }
                    else
                    {
                        tamanho++;
                    }
                }
                else
                {
                    tamanho++;
                }
           }
           else
           {
                tamanho++;
           }
        }
    }

    for(i = img->altura/8 - 10 + 80; i < 7 * img->altura/8; i+= 100)
    {
        for(j = 0; j < 11 * img->largura/13; j++)
        {
           if(img->dados[0][i][j] == 0 && img->dados[1][i][j] == 0 && img->dados[2][i][j] == 0)
           {
                if(img->dados[0][i][j + 1] == 0 && img->dados[1][i][j + 1] == 0 && img->dados[2][i][j + 1] == 0)
                {
                    if(img->dados[0][i][j + 2] == 0 && img->dados[1][i][j + 2] == 0 && img->dados[2][i][j + 2] == 0)
                    {
                        if(tamanho > 35 && tamanho < 74)
                        {
                            contagem[0]++;
                            tamanho = 0;
                        }
                        else
                            tamanho = 0;
                    }
                    else
                    {
                        tamanho++;
                    }
                }
                else
                {
                    tamanho++;
                }
           }
           else
           {
                tamanho++;
           }
        }
    }

    for(i = 0; i < 4; i++)
        total += contagem[i];

    return (total);
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

    for(i = 0; i < img->altura/8 - 10; i++)
    {
        for(j = 0; j < largura; j++)
        {
            img->dados[0][i][j] =  0;
            img->dados[1][i][j] =  0;
            img->dados[2][i][j] =  0;
        }
    }

    for(i = 7 * img->altura/8 + 10; i < img->altura; i++)
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
	copia = copiaImagemX (img);

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

Imagem3C* criaImagem3CX (int largura, int altura)
{
	int i, j;
	Imagem3C* img;

	img = (Imagem3C*) malloc (sizeof (Imagem3C));

	img->largura = largura;
	img->altura = altura;

	img->dados = (unsigned char***) malloc (sizeof (unsigned char**) * 3); /* Uma matriz por canal. */
	for (i = 0; i < 3; i++)
	{
		img->dados [i] = (unsigned char**) malloc (sizeof (unsigned char*) * altura);
		for (j = 0; j < altura; j++)
			img->dados [i][j] = (unsigned char*) malloc (sizeof (unsigned char) * largura);
	}

	return (img);
}

Imagem3C* copiaImagemX (Imagem3C* img)
{
	unsigned long i, j, k;
	Imagem3C* copia;

	copia = criaImagem3CX (img->largura, img->altura);

	if (!copia)
		return (NULL);

	for (i = 0; i < 3; i++)
		for (j = 0; j < copia->altura; j++)
			for (k = 0; k < copia->largura; k++)
				copia->dados [i][j][k] = img->dados [i][j][k];

	return (copia);
}
