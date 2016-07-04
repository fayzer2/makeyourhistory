// Make Your History V 0.0.1
// By Rennan M
// 06/16
// C / ALlegro



#include <allegro.h>
#include "jogador.hpp"
#include "meujogo.hpp"

void inicia_allegro(){
	allegro_init(); //INICIAR BIBLIOTECA
	install_keyboard(); //INSTALAR TECLADO

	set_window_title("Rennan - APS C | Versao Alpha 0.0.2");

	set_color_depth(32); //DEFINIR PIXELS
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0); //DEFINIR PLACA DE VIDEO E TAMANHO DA TELA
	buffer = create_bitmap(800, 600); //CRIA UM BUFFER DE IMAGEM USANDO COMO REFERENCIA O PONTEIRO COM ALTURA E LARGURA
	
	LOCK_VARIABLE(tj); //TRAVAR VARIAVEL
	LOCK_FUNCTION(itj); //TRAVAR FUNÇ~AO
	
	//CONTADOR FPS
	install_int_ex(itj, BPS_TO_TIMER(FRAME_RATE));
}

int main(){
	inicia_allegro();
	load_jogo();

	bool  sair;
	sair = false;

	//LOOP PRINCIPAL DO JOGO
	while(!sair){
		if(tj){
			while(tj){
				atualiza_jogo();
				tj--;
			}
			
			clear_to_color(buffer, 0x00000); //SEMPRE RESETA-SE O BUFFER PARA APLICAR DOUBLE BUFFERING E EVITAR EFEITO FREEZING
			
			desenhar_jogo();
			desenhar_tela();
		}
		else{
			rest(1);
		}
		if(key[KEY_ESC]){ //BOTAO PARA SAIR DO PROGRAMA
			sair = true;
		}
	
	}
	
	destroy_bitmap(buffer);
	return 0;
}
