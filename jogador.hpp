//JOGADOR


int tj = 0; //VARIAVEL DE VELOCIDADE DE JOGO

const int FRAME_RATE = 60; //DEFINIR FPS

void itj(){
		tj++;
}
END_OF_FUNCTION(tj)

//FUNCAO PARA TODOS BITMAPS
BITMAP *buffer;

//ESPACO DE PIXEL AO PLAYER ANDAR
const int deslocamento = 4;

//DOUBLE BUFFER
void desenhar_tela(){
		blit(buffer, screen, 0, 0, 0, 0, 800, 600);
}



class player{  //CLASSE PLAYER DECLARADA PARA AJUDAR NA ORGANIZAÇ~AO DO PROJETO E PROPORCIONA ALGUMAS POSSIBILIDADES A MAIS, COMO PEGAR_
 BITMAP *jogador;  // _ A LOCALIZAÇAO X, Y, DO JOGADOR NO MAPA.
 int x,y; //POSICAO NO MAPA
 int direcao;
 int animacao; 
 int atacar;
           
    public:     
       void inicia();
       void desenha(); 
       void teclado();
       int posicao_jogadorx(){
		   return x;
		};
       int posicao_jogadory(){
			return y;
		};
       void posicao(int _x, int _y);
   
};
 
void player::inicia(){ //FUNCAO RESPONSAVEL PARA DAR LOAD NO PERSONAGEM
    jogador = load_bmp("imagens/personagem.bmp",NULL); // *LOAD_BMP* CARREGAR ARQUIVOS BITMAPS DO SEU PC, PRIMEIRO PARAMETRO LOCAL, SEGUNDO PALHETA DE COR.        
 //INICIA VARIAVEIS
 
 direcao = 0;
 animacao = 0;
 
 x = 540;
 y = 280;                
}
 
void player::desenha(){
    masked_blit(jogador, buffer, animacao*32, direcao*32, x, y, 32,32); //PREFERI USAR *MASKED_BLIT* POIS ELE JA RECONHECE A COR RGB(255,0,255) COMO TRANSPARENTE_
} 			//PARAMETROS: PONTEIRO DA IMAGEM, PONTEIRO DO(DISPLAY), VARIAVEL INT DE ANIMACAO, INT ANIMACAO DA DIRECAO, INT DESTX, INT DESTY, INT LARGURA, INT ALTURA
 
void player::teclado()
{
      int ax = x;
      int ay = y;
      //TECLAS DE CONTROLE
      if (key[KEY_UP]){
           y-=deslocamento; 
           direcao = 3;              
      }
      if(key[KEY_DOWN]){
           y+=deslocamento;
           direcao = 0;
      }
      if(key[KEY_LEFT]){
           x-=deslocamento;
           direcao = 1;
      }
      if(key[KEY_RIGHT]){
           x+=deslocamento;
           direcao = 2;
      }  
      if(ax != x || ay != y){
           //
           animacao++;
           if(animacao > 2){
				animacao = 0;
			}
      }                            
       
      // limites
      if(x < 0){
			 x = 0;
		}
      if(x > 800){ //PARA O PLAYER NUNCA PASSAR DO LIMITE DA TELA
			 x = 800;
		}
      if (y < 0){
			 y = 0;
		}
      if(y > 600){
			  y = 600;
		}
}

void player::posicao(int _x, int _y){  //FUNCAO PARA PEGAR LOCALIZAÇ~AO DO PLAYER
		x = _x;
		y = _y;
}
