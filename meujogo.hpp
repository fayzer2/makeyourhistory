	
//CRIANDO PONTEIROS PARA AS SPRITES DO GAME
BITMAP *casa_a;
BITMAP *casa_b;
BITMAP *casa_c;
BITMAP *bosque_a;
BITMAP *bosque_b;
BITMAP *bosque_c;
BITMAP *bosque2_a;
BITMAP *bosque2_b;
BITMAP *bosque2_c;
BITMAP *fundo;
BITMAP *colisao;
BITMAP *alto;

player jogadorr;

//VARIAVEIS DE DESLOCAMENTO
bool desloca; //TRUE: MAPA ANDA CONFORME O PLAYER SE MOVIMENTA
int desloca_mapa_x; //DEFINE O TANTO QUE O MAPA DESLOCA NO EIXO X
int desloca_mapa_y; //DEFINE O TANTO QUE O MAPA DESLOCA NO EIXO Y

//INDICARA ONDE O JOGADOR ESTA
int lugar; //1 CASA, 2 BOSQUE

//CARREGAR ARQUIVOS DO JOGO
void load_jogo(){
	jogadorr.inicia();
	//BMPS
	casa_a = load_bmp("imagens/casa_final.bmp", NULL);
	casa_c = load_bmp("imagens/casa_final_colisao.bmp", NULL);
	casa_b = load_bmp("imagens/casa_final_alto.bmp",NULL);
	bosque_a = load_bmp("imagens/bosque1.bmp", NULL);
	bosque_b = load_bmp("imagens/bosque1_ceu.bmp", NULL);
	bosque_c = load_bmp("imagens/bosque1_colisao.bmp", NULL);
	bosque2_a =	load_bmp("imagens/bosque2.bmp", NULL);
	bosque2_b = load_bmp("imagens/bosque2_alto.bmp", NULL);
	bosque2_c = load_bmp("imagens/bosque2_colisao.bmp", NULL);
	
	
	//IMAGENS DO PRIMEIRO CENARIO
	fundo = casa_a;
	colisao = casa_c;
	alto = casa_b;
	lugar = 1;
	
	desloca_mapa_x = 0; //CONTEM O VALOR DO DESLOCAMENTO DO SCROOL X
	desloca_mapa_y = 0; //CONTEM O VALOR DO DESLOCAMENTO DO SCROLL Y
	desloca = false; //ENQUANTO FOR FALSE O MAP NAO TERA O SCROLL
}

void atualiza_jogo(){
	int troca = 0;
	int ax, ay;
	ax = jogadorr.posicao_jogadorx(); //ALOCA EM AX A ULTIMA POSICAO DO PLAYER NO EIXO X
	ay = jogadorr.posicao_jogadory(); //ALOCA EM AY A ULTIMA POSICAO DO PLAYER NO EIXO Y
	jogadorr.teclado(); //CHAMA FUNÇAO TECLADO QUE POSSIBILITA O PLAYER SE MOVIMENTAR PELAS SETAS
	
	//VERIFICACAO DE COLISAO
	bool colide = false; //ENQUANTO FOR FALSE O JOGADOR PODE SE LOCOMOVER EM DETERMIDADA DIREÇAO
	int px = jogadorr.posicao_jogadorx(); 
	int py = jogadorr.posicao_jogadory()+16; //ALOCA EM AY A ULTIMA POSICAO DO PLAYER NO EIXO Y +16 (COLOQUEI +16 POIS MEU PLAYER ESTAVA BUGANDO NA PAREDE)
	
	//DEPENDENDO DO TAMANHO DO MAPA E PRECISO QUE ELE SE MOVA
	if(lugar == 1){ //ESSE MAPA E O INTERIOR DE UMA CASA, ENTAO E SO SETAR UM TAMANHO FIXO
		px = jogadorr.posicao_jogadorx()-160; 
		py = jogadorr.posicao_jogadory()-160+16;
	}
	if(lugar == 2){ //JA ESSE 'E PRECISO CHAMAR UMA FUNÇAO PARA IR COMPARANDO A POSIÇAO ATUAL DO PLAYER ATE AS BORDAS DO MAPA_
		px = px + desloca_mapa_x;    //_ SEGUINDO A DIREÇAO ESCOLHIDA.
		py = py + desloca_mapa_y;
	}
	if(lugar == 3){
		px = px + desloca_mapa_x;
		py = py + desloca_mapa_y;
	}
	
	for(int i=0; i<30; i++){		//MATRIZ PARA VERIFIÇAO DE CORES NO MAPA, CASO O PROGRAMA IDENTIFIQUE ALGUMA DESSAS CORES LISTADAS_
		for(int j=0; j<16; j++){	//_TROCA O MAPA E SEUS ARQUIVOS.
			//COR ROSA				// SIM O MAPA E UMA MATRIZ !!
			if(getpixel(colisao, px+i, py+j) == 0xff0000){  //ESSE GETPIXEL E PARA COLISOES
				colide = true; //TRUE COLIDE, A COR USADA RGB(255,0,0)
			}
			//COR VERDE
			if(getpixel(colisao, px+i, py+j) == 0x00ff00){  //*GETPIXEL* PRIMEIRO PARAMETRO CAMADA QUE DESEJA FAZER A COMPARACAO, POSICAO X, POSICAO Y, == COR RGB QUE DESEJA COMPARAR.
				troca = 1;
			}
			//COR AZUL
			if(getpixel(colisao, px+i, py+j) == 0x0000ff){
				troca = 2;
			}
			//COR Azul claro
			if(getpixel(colisao, px+i, py+j) == 0x00ffff){
				troca = 3;
			}
			//COR AMARELO
			if(getpixel(colisao, px+i, py+j) == 0x672a4b){
				troca = 4;
			}
		}
	}
	if(colide){
		//VOLTAR AO ESTADO ANTERIOR
		jogadorr.posicao(ax, ay);
	}
	
	switch(lugar){
		case 1: //CASA
			if(troca == 1){
				//TROCA DE LUGARES
				lugar = 2; //DEFINE O LUGAR
				fundo = bosque_a; //USE O PONTEIRO DE CADA MAPA
				colisao = bosque_c;
				alto = bosque_b;
				jogadorr.posicao(410, 370); //POSICAO ONDE O PLAYER VAI COMECAR NESSE MAPA (X, Y)
				desloca_mapa_x = 10; //DESLOCAMENTO DO MAPA NO EIXO X AO MUDAR PARA ESSE MAPA
				desloca_mapa_y = 160; //DESLOCAMENTO DO MAPA NO EIXO Y AO MUDAR PARA ESSE MAPA
				desloca = true;
			}
			break;
		case 2: //BOSQUE
			if(troca == 2){
				//TROCA DE LUGARES
				lugar = 1;
				fundo = casa_a;
				colisao = casa_c;
				alto = casa_b;
				jogadorr.posicao(290, 440);
				desloca_mapa_x = 0; 
				desloca_mapa_y = 0;
				desloca = false; //COMO ESTA FALSE O MAPA NA SE MOVIMENTA LOGO AS VARIAVEIS X E Y ESTAO COMO 0
			}
			if(troca == 3){ //BOSQUE 2
				lugar = 3;
				fundo = bosque2_a;
				colisao = bosque2_c;
				alto = bosque2_b;
				jogadorr.posicao(500, 900);
				desloca_mapa_x = 0;
				desloca_mapa_y = 0;
				desloca = true;
				
			}
			if(troca == 4){ //VOLTA BOSQUE 1
				lugar = 2;
				fundo = bosque_a;
				colisao = bosque_c;
				alto = bosque_b;
				jogadorr.posicao(860, 60);
				desloca_mapa_x = 0;
				desloca_mapa_y = 0;
			}
			break;
		default:
			break;
	}
	if(desloca){
		int aux = deslocamento; //VARIAVEL PARA INFORMAR SE O PLAYER ESTA EM MOVIMENTO E A DIRECAO
		if(ax < 160 && desloca_mapa_x > 0){ //CONTROLA DESLOCAMENTO DO MAPA SE ESTA NAS BORDAS
			desloca_mapa_x -=aux;     			//MAPA DESLOCA PARA ESQUERDA
			jogadorr.posicao(ax+aux, ay); 	//ENQUANTO O JOGADOR SE MOVE PARA DIREITA
			ax = jogadorr.posicao_jogadorx(); 
			ay = jogadorr.posicao_jogadory();
			
			if(ax < 160 && desloca_mapa_x > 0){ //VERIFICA OS LIMITES
				desloca_mapa_x -=aux;			
				jogadorr.posicao(ax+aux, ay); 
			}
		}
		if(ay < 160 && desloca_mapa_y > 0){ //VERIFICA OS LIMITES
			desloca_mapa_y -=aux;			//MAPA DESLOCA PARA CIMA
			jogadorr.posicao(ax, ay+aux); // ENQUANTO JOGADOR SE MOVE PARA BAIXO
			ax = jogadorr.posicao_jogadorx();
			ay = jogadorr.posicao_jogadory();
			
			if(ay < 60 && desloca_mapa_y > 0){ //VERIFICA OS LIMITES
				desloca_mapa_y -=aux;
				jogadorr.posicao(ax, ay+aux); 
			}
		}
		if(ax > 800-160 && desloca_mapa_x < fundo->w-800){ //VERIFICA ARQUIVO DE BMP FAZENDO COMPARACAO COM A LARGURA DA TELA 
			desloca_mapa_x +=aux;
			jogadorr.posicao(ax-aux, ay); 
			ax = jogadorr.posicao_jogadorx();
			ay = jogadorr.posicao_jogadory();
			if(ax > 800-60 && desloca_mapa_x < fundo->w-600){ //  -> 
				desloca_mapa_x +=aux; // DESLOCA O MAPA PARA DIREITA 
				jogadorr.posicao(ax-aux, ay); //ENQUANTO O PLAYER DESLOCA PARA ESQUERDA
			}
		}
		if(ay > 600-160 && desloca_mapa_y < fundo->h-600){
			desloca_mapa_y +=aux;
			jogadorr.posicao(ax, ay-aux);
			ax = jogadorr.posicao_jogadorx();
			ay = jogadorr.posicao_jogadory();
			if(ay > 600-60 && desloca_mapa_y < fundo->h-600){
				desloca_mapa_y +=aux; //DESLOCA O MAPA PARA BAIXO
				jogadorr.posicao(ax, ay-aux); //ENQUANTO O PLAYER DESLOCA PARA CIMA
			}
		}
	}
	ax = jogadorr.posicao_jogadorx();
	ay = jogadorr.posicao_jogadory();
}

//DESENHA TUDO NO BUFFER
void desenhar_jogo(){
	int largura, altura, ax = 0, ay = 0;
	int bx = 0;
	int by = 0;
	
	switch(lugar){
		case 1:
			bx = 160;
			by = 160;
			largura = 480;
			altura = 325;
			break;
		case 2: //BOSQUE
			ax = desloca_mapa_x;
			ay = desloca_mapa_y;
			largura = 800;
			altura = 600;
			break;
		case 3: //BOSQUE2
			ax = desloca_mapa_x;
			ay = desloca_mapa_y;
			largura = 800;
			altura = 600;
			break;
		default:
			break;
	}
	
	blit(fundo, buffer, ax, ay, bx, by, 800, 600);
	jogadorr.desenha();
	masked_blit(alto, buffer, ax, ay, bx, by, 800, 600);
}
