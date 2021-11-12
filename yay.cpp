	#include <allegro5/allegro.h>
	#include <allegro5/allegro_image.h>
	#include <allegro5/allegro_font.h>
	#include <allegro5/allegro_ttf.h>
    #include <allegro5/allegro_audio.h>
    #include <allegro5/allegro_acodec.h>
	#include <iostream>

	using namespace std;

	const float FPS = 8;
	const int SCREEN_W = 500;
	const int SCREEN_H = 550;

	enum MYKEYS
	{
	    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
	};

	    //matriz definindo mapa do jogo: 1 representa paredes, 2 representa passagem com bolinhas, e 3 com frutas
	char MAPA[26][26] =
	{
	    "1111111111111111111111111",
	    "1222222221111111222232221",
	    "1221111121111111211111221",
	    "1221111122222223211111221",
	    "1222222221111111222222221",
	    "1112111121111111211112121",
	    "1222111122221222211112221",
	    "1212111111121211111112121",
	    "1212222111221221112222121",
	    "1211112111211121112111121",
	    "1211112122222222212111121",
	    "1222112221112111222112221",
	    "0222111121112111211112220",
	    "1222222221112111222222221",
	    "1211111121112111211111121",
	    "1211122222222222222211121",
	    "1222221112112112111222221",
	    "1211121112222222111211121",
	    "1211121112111112111211121",
	    "1222222222222222222222221",
	    "1211121111112111111211121",
	    "1222221111112111111322221",
	    "1211122222212122222211121",
	    "1222221111223221111222221",
	    "1111111111111111111111111",
	};

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *mapa   = NULL;
	ALLEGRO_BITMAP *ball   = NULL;
	ALLEGRO_BITMAP *frutas = NULL;
	ALLEGRO_BITMAP *pacman   = NULL;
	ALLEGRO_BITMAP *pac_up   = NULL;
	ALLEGRO_BITMAP *pac_left   = NULL;
	ALLEGRO_BITMAP *pac_down   = NULL;
	ALLEGRO_BITMAP *pac_right   = NULL;
	ALLEGRO_BITMAP *amarelo = NULL;
	ALLEGRO_BITMAP *verde = NULL;
	ALLEGRO_BITMAP *azul = NULL;
	ALLEGRO_BITMAP *vermelho = NULL;
	ALLEGRO_BITMAP *rosa = NULL;
	ALLEGRO_BITMAP *marrom = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_SAMPLE *death = al_load_sample("maguila.wav");
	ALLEGRO_SAMPLE *win = al_load_sample("win.wav");
	ALLEGRO_SAMPLE *tetris = al_load_sample("tetris.wav");







	    int i = 15, j = 12; //posição inicial do Pacman na matriz
	    int a = 22, b = 1; // posicao do fantasma azul
	    int c = 19, d = 8;// posicao do fantasma verde
	    int e = 5, f = 8;// posicao do fantasma amarelo
	    int g = 6, h = 11; // posicao do fantasma vermelho
	    int m = 1, n = 20;// poscao do fantasma marrom
	    int o = 22, p = 20;//posicao do fantasma rosa
	    bool morte = false; // booleano para a morte do pacman(utilizado no final)
	    bool acabar = false; // booleano para a vitória do pacman(utilizado no final)



	    int q = 20; //tamanho de cada célula no mapa
	    //POSICAO DO PACMAN
	    int posy = i*q;
	    int posx = j*q;
	    //POSICOES DOS FANTASMAS
	    int azulx = a*q;
	    int azuly = b*q;

	    int verdex = c*q;
	    int verdey = d*q;

	    int amarelox = e*q;
	    int amareloy = f*q;

	    int vermelhox = g*q;
	    int vermelhoy = h*q;

	    int marromx = m*q;
	    int marromy = n*q;

	    int rosax = o*q;
	    int rosay = p*q;


	///////////////////////////////////////////////////
	    //valor sorteado
	    int randomtime =  -1;

	    
	    // variaveis para contar o numero de bolas frutas e pontos feitos
	    int nbola = 226; 
	    int nfruta = 4;
	    int pontos = 0;
	    int k =0;
	    int l =0;

	    // declaracao das variaveis posteriormente utilizadas para o movimento do pacman
	    int intencao = 0;
	    int anterior = 0;

	    bool key[4] = { false, false, false, false };
	    bool redraw = true;
	    bool sair = false;
	    /*
// ultimas coordenadas do pacman
	    int lastx = i;
	    int lasty = j;
	    //coordenadas do f esperto
	    int ultvx = g;
	    int ultvy = h;


*/


	void mov(char MAP[][26],int &x, int &y, int &posicaofY, int &posicaofX, int fant){

	    srand(time(NULL));
	    randomtime = rand()%1;
	//  individualizacao dos movimentos realizados pelos fantasmas, sorteados aleatoriamente baseado no horario do sistema.
	    if(fant == 1)
	        srand(time(NULL));
	    randomtime = rand()%4;

	    if(fant == 2)
	        srand(time(NULL));
	    randomtime = rand()%4;

	    if(fant == 3)
	        srand(time(NULL));
	    randomtime = rand()%4;
	    if(fant == 4)
	        srand(time(NULL));
	    randomtime = rand()%4;

	    if(fant == 5)
	        srand(time(NULL));
	    randomtime = rand()%4;

	    // apos sorteado um valor, os ifs irao verificar se existe alguma parede e modificar a posicao do fantasma
	    if(randomtime == 0 and MAP[x-1][y] != '1'){
	        x--;
	        posicaofX = x*q;
	    }

	    else if(randomtime == 1 and MAP[x+1][y] != '1'){
	        x++;
	        posicaofX = x*q;
	    }

	    else if(randomtime == 2 and MAP[x][y+1] != '1'){
	        y++;
	        posicaofY = y*q;
	    }

	    else if(randomtime == 3 and MAP[x][y-1] != '1'){
	        y--;
	        posicaofY = y*q;
	    }
        cout << randomtime << endl;
	    }


	    int inicializa() {
	        if(!al_init())
	        {
	            cout << "Falha ao carregar Allegro" << endl;
	            return 0;
	        }
            if(!al_install_audio)
            {
            	cout << "Falha ao instalar o audio" << endl;
            	return 0;
            }
	        if(!al_install_keyboard())
	        {
	            cout << "Falha ao inicializar o teclado" << endl;
	            return 0;
	        }

	        timer = al_create_timer(1.0 / FPS);
	        if(!timer)
	        {
	            cout << "Falha ao inicializar o temporizador" << endl;
	            return 0;
	        }

	        if(!al_init_image_addon())
	        {
	            cout <<"Falha ao iniciar al_init_image_addon!" << endl;
	            return 0;
	        }

	        display = al_create_display(SCREEN_W, SCREEN_H);
	        if(!display)
	        {
	            cout << "Falha ao inicializar a tela" << endl;
	            al_destroy_timer(timer);
	            return 0;
	        }

	        mapa = al_load_bitmap("map.bmp");
	        if(!mapa)
	        {
	            cout << "Falha ao carregar o mapa!" << endl;
	            al_destroy_display(display);
	            return 0;
	        }
	        al_draw_bitmap(mapa,0,0,0);

	        pacman = al_load_bitmap("pacman.png");
	        if(!pacman)
	        {
	            cout << "Falha ao carregar o pacman!" << endl;
	            al_destroy_display(display);
	            return 0;
	        }
	        al_draw_bitmap(pacman,posx,posy,0);

	        azul = al_load_bitmap("azul.png");
	        amarelo = al_load_bitmap("amarelo.png");
	        verde = al_load_bitmap("verde.png");
	        vermelho = al_load_bitmap("vermelho.png");
	        marrom = al_load_bitmap("marrom.png");
	        rosa = al_load_bitmap("rosa.png");
            if(!al_install_audio()){
              fprintf(stderr, "failed to initialize audio!\n");
              return -1;
            }

            if(!al_init_acodec_addon()){
              fprintf(stderr, "failed to initialize audio codecs!\n");
              return -1;
            }

   if (!al_reserve_samples(3)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }
            win = al_load_sample("win.wav");
            tetris = al_load_sample("tetris.wav");
            death = al_load_sample("maguila.wav");


//DRAW BITMAP DOS FANTASMAS
	    if(!vermelho)
	    {
	        cout << "Falha ao carregar o fantasma Vermelho!" << endl;
	        al_destroy_display(display);

	        return 0;
	    }
	    al_draw_bitmap(vermelho,vermelhox,vermelhoy,0);
	    if(!rosa)
	    {
	        cout << "Falha ao carregar o fantasma Rosa!" << endl;
	        al_destroy_display(display);

	        return 0;
	    }
	    al_draw_bitmap(rosa,rosax,rosay,0);
	    if(!marrom)
	    {
	        cout << "Falha ao carregar o fantasma Marrom!" << endl;
	        al_destroy_display(display);

	        return 0;
	    }
	    al_draw_bitmap(marrom,marromx,marromy,0);


	    if(!azul)
	    {
	        cout << "Falha ao carregar o fantasma Azul!" << endl;
	        al_destroy_display(display);

	        return 0;
	    }
	    al_draw_bitmap(azul,azulx,azuly,0);

	    if(!amarelo)
	    {
	        cout << "Falha ao carregar o fantasma Amarelo!" << endl;
	        al_destroy_display(display);

	        return 0;
	    }
	    al_draw_bitmap(amarelo,amarelox,amareloy,0);

	    if(!verde)
	    {
	        cout << "Falha ao carregar o fantasma Verde!" << endl;
	        al_destroy_display(display);

	        return 0;
	    }
	    al_draw_bitmap(verde,verdex,verdey,0);
	    //FIM
	        ball = al_load_bitmap("bolas.png");
	        if(!ball)
	        {
	            cout << "Falha ao carregar as bolas!" << endl;
	            al_destroy_display(display);
	            return 0;
	        }
	        al_draw_bitmap(ball,k*20,l*20,0);
              // FONTES
	          al_init_font_addon();
	          al_init_ttf_addon();
	          font = al_load_font("/usr/share/fonts/truetype/liberation/LiberationMono-Bold.ttf", 28, 0);
	      if (!font)
	    {
	        font = al_load_font("C:/Windows/Fonts/OCRAEXT.ttf", 28, 0);
	    }
	      if (!font)
	    {
	        al_destroy_display(display);
	        cout<< "Falha ao carregar fonte."<<endl;
	        return -1;
	    }

	        frutas = al_load_bitmap("frutas.png");
	        if(!frutas)
	        {
	            cout << "Falha ao carregar as frutas!" << endl;
	            al_destroy_display(display);
	            return 0;
	        }
	        al_draw_bitmap(frutas,k*20,l*20,0);
	        event_queue = al_create_event_queue();
	        if(!event_queue)
	        {
	            cout << "Falha ao criar a fila de eventos" << endl;
	            al_destroy_display(display);
	            al_destroy_timer(timer);
	            return 0;
	        }
	        pacman = al_load_bitmap("pacman.png");
	        pac_up = al_load_bitmap("pac_up.png");
	        pac_down = al_load_bitmap("pac_down.png");
	        pac_left = al_load_bitmap("pac_left.png");
	        pac_right = al_load_bitmap("pac_right.png");
	        
	        al_register_event_source(event_queue, al_get_display_event_source(display));
	        al_register_event_source(event_queue, al_get_timer_event_source(timer));
	        al_register_event_source(event_queue, al_get_keyboard_event_source());

	        al_clear_to_color(al_map_rgb(0,0,0));
	        al_flip_display();
	        al_start_timer(timer);

	        return 1;
	    }

	    int main(int argc, char **argv)
	    {
	        int cont = 0;
	        if(!inicializa()) return -1;

	        while(!sair)
	        {
	            ALLEGRO_EVENT ev;
	            al_wait_for_event(event_queue, &ev);

	            if(ev.type == ALLEGRO_EVENT_TIMER)
	            {

               // FAZER O TÚNEL
			if(intencao!=1 && j == 24 && i ==12 ){ // caso alcance um ponto da matriz ele aparece em outro
                i = 12;
				j = 0;
                posx = j*q;
                posy = i*q;
				
            }

            else if(intencao!=3 && j <= -1){
                i = 12;
                j = 24;
                posx = j*q;
                posy = i*q;
				
            }
		//fim do tunel//


	        //movimentacao utilizando as intenções de movimento, ifs para 4 intenções mudando a colocação da matriz mapa e as posições
	        if(intencao==4){ // PARA BAIXO
	            if(MAPA[i-1][j] != '1'){ // CASO A POSIÇÃO DESIGNADA NA MATRIZ, ( PARA CIMA) SEJA DIFERENTE DE 1(PAREDE) ASSUME A POSIÇAÕ
	                pacman=pac_up;       // E TAMBEM JA DEFINE A ANTIGA POSICAO PARA A VARIAVEL ANTEIRIOR
	                i--;
	                posy = i*q;
	                anterior=4; 
	            }
	            else{
	                if(anterior==1 && MAPA[i][j-1] != '1'){
	                    pacman=pac_left;
	                    j--;
	                    posx = j*q;
	                }
	                if(anterior==3 && MAPA[i][j+1] != '1'){
	                    pacman=pac_right;
	                    j++;
	                    posx = j*q;
	                }
	            }
	            //os proximos 2 trechos sao para contabilizar os pontos e sumir com as bolas e frutas
	                if(MAPA[i][j] == '2'){
	                    MAPA[i][j] = '0';
	                    nbola--;
	                    pontos++;
	                }
	                 if(MAPA[i][j] == '3'){
	                    MAPA[i][j] = '0';
	                    nfruta--;
	                    pontos+=10;
	                }
	        }
	        
	        if(intencao==2){ //PARA CIMA
	            if(MAPA[i+1][j] != '1'){
	                pacman=pac_down;
	                i++;
	                posy = i*q;
	                anterior=2;
	            }
	            else{
	                if(anterior==1 && MAPA[i][j-1] != '1'){         
	                    pacman=pac_left;
	                    j--;
	                    posx = j*q;
	                }
	                if(anterior==3 && MAPA[i][j+1] != '1'){
	                    pacman=pac_right;
	                    j++;
	                    posx = j*q;
	                }   
	            }
	            if(MAPA[i][j] == '2'){
	                MAPA[i][j] = '0';
	                nbola--;
	                pontos++;
	            }
	                if(MAPA[i][j] == '3'){
	                    MAPA[i][j] = '0';
	                    nfruta--;
	                    pontos+=10;
	                }
	        }
	            
	        if(intencao==1){ // PARA DIREITA
	            if(MAPA[i][j-1] != '1'){
	                pacman=pac_left;
	                j--;
	                posx = j*q;
	                anterior=1;
	            }
	            else{
	                if(anterior==2 && MAPA[i+1][j] != '1'){
	                    pacman=pac_down;
	                    i++;
	                    posy = i*q;
	                }
	                if(anterior==4 && MAPA[i-1][j] != '1'){                 
	                    pacman=pac_up;
	                    i--;
	                    posy = i*q;
	                }
	            }
	            if(MAPA[i][j] == '2'){
	                MAPA[i][j] = '0';
	                nbola--;
	                pontos++;
	            }
	                if(MAPA[i][j] == '3'){
	                    MAPA[i][j] = '0';
	                    nfruta--;
	                    pontos += 10;
	                }
	        }
	            

	        if(intencao==3){  //PARA ESQUERDA
	            if(MAPA[i][j+1] != '1'){
	                pacman=pac_right;
	                j++;
	                posx = j*q;
	                anterior=3;
	            }
	            else{               
	                if(anterior==2 && MAPA[i+1][j] != '1'){
	                    pacman=pac_down;
	                    i++;
	                    posy = i*q;
	                }
	                if(anterior==4 && MAPA[i-1][j] != '1'){
	                    pacman=pac_up;
	                    i--;
	                    posy = i*q;
	                }
	            }
	            if(MAPA[i][j] == '2'){
	                MAPA[i][j] = '0';
	                nbola--;
	                pontos++;
	            }
	            if(MAPA[i][j] == '3'){
	                MAPA[i][j] = '0';
	                nfruta--;
	                pontos+=10;
	            }
	        }
	        //**********************************//

	                redraw = true;
	            }
	            else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	            {
	                break;
	            }
	            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
	            {
	                switch(ev.keyboard.keycode) // utilizar as teclas pressionadas para ja guardar o movimento anterior e atribuir um movimento novo. 
	                {
	                    case ALLEGRO_KEY_UP:
	                    anterior = intencao;
	                    intencao = 4;
	                    break;

	                    case ALLEGRO_KEY_DOWN:
	                    anterior = intencao;
	                    intencao = 2;
	                    break;

	                    case ALLEGRO_KEY_LEFT:
	                    anterior = intencao;
	                    intencao = 1;
	                    break;

	                    case ALLEGRO_KEY_RIGHT:
	                    anterior = intencao;
	                    intencao = 3;
	                    break;
	                }
	            }
	            else if(ev.type == ALLEGRO_EVENT_KEY_UP)
	            {
	                switch(ev.keyboard.keycode)
	                {
	                    case ALLEGRO_KEY_UP:
	                    key[KEY_UP] = false;
	                    break;

	                    case ALLEGRO_KEY_DOWN:
	                    key[KEY_DOWN] = false;
	                    break;

	                    case ALLEGRO_KEY_LEFT:
	                    key[KEY_LEFT] = false;
	                    break;

	                    case ALLEGRO_KEY_RIGHT:
	                    key[KEY_RIGHT] = false;
	                    break;

	                    case ALLEGRO_KEY_ESCAPE:
	                    sair = true;
	                    break;
	                }
	            }
	                    al_draw_textf(font, al_map_rgb(200, 200, 200), 0, 505, 0, "Score: %d", pontos);

	            if(redraw && al_is_event_queue_empty(event_queue))
	            {
	                redraw = false;

	                al_clear_to_color(al_map_rgb(0,0,0));
	                al_draw_bitmap(mapa,0,0,0);
	                al_draw_textf(font, al_map_rgb(200, 200, 200), 0, 505, 0, "Score: %d", pontos);
	                for(k=0; k <26; k++){
	                    for (l=0; l<26; l++){
	                        if(nbola == 0)                  //FOR utilizado para ler a matriz e desenhar as bolinhas
	                            continue;
	                        else if(MAPA[k][l] == '2')
	                            al_draw_bitmap(ball,l*20,k*20,0);
	                    }
	                }
	                for(k=0; k <26; k++){
	                    for (l=0; l<26; l++){              //FOR utilizado para ler a matriz e desenhar as frutas
	                        if(MAPA[k][l] == '3')
	                            al_draw_bitmap(frutas,l*20,k*20,0);
	                    }
	                }
	            al_draw_bitmap(pacman,posx,posy,0);
	            al_draw_bitmap(amarelo,amareloy,amarelox,0);
	            al_draw_bitmap(vermelho,vermelhoy,vermelhox,0);
	            al_draw_bitmap(verde,verdey,verdex,0);
	            al_draw_bitmap(azul, azuly,azulx,0);
	            al_draw_bitmap(marrom,marromy,marromx,0);
	            al_draw_bitmap(rosa,rosay,rosax,0);

	                        //fantasmas
	            mov(MAPA,a,b,azuly,azulx,0);
	            mov(MAPA,e,f,amareloy,amarelox,1);
	            mov(MAPA,c,d,verdey,verdex,2);
	            mov(MAPA,g,h,vermelhoy,vermelhox,3);
	            mov(MAPA,m,n,marromy,marromx,4);
	            mov(MAPA,o,p,rosay,rosax,5);
	            
	                al_flip_display();
	            }
	        //pacman morre ao entrar na mesma posicao da matriz que algum fantasma
	            if( (g==i && h==j) || (i==a && j==b) || (i==c && j==d) || (i==e && j==f) || (i == m && j == n) || (i == o && j == p) ){
	            	//tocar um som para caso isso aconteca
	            	al_play_sample(death, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	                morte = true;
	            }
	            // tocar uma musica de fundo
	            if(pontos==1)
	            	al_play_sample(tetris, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                // tocar um som para vitória
	            if(pontos ==300){
	            	al_play_sample(win, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	            	acabar = true;
	            }
	            if(pontos==300){
	            	//al_stop_sample(tetris);
	            }

	        if(morte){
	            al_destroy_bitmap(pacman);
	            al_destroy_bitmap(ball);
	            al_destroy_bitmap(azul);
	            al_destroy_bitmap(vermelho);
	            al_destroy_bitmap(amarelo);
	            al_destroy_bitmap(verde);
	            al_destroy_bitmap(rosa);
	            al_destroy_bitmap(marrom);
	            al_rest(2.0);
	            return 0;
	            }

	        if(acabar){
	            al_destroy_bitmap(pacman);
	            al_destroy_bitmap(ball);
	            al_destroy_bitmap(azul);
	            al_destroy_bitmap(vermelho);
	            al_destroy_bitmap(amarelo);
	            al_destroy_bitmap(verde);
	            al_destroy_bitmap(rosa);
	            al_destroy_bitmap(marrom);
	            al_rest(15.0);
	            return 0;
	            }


	        }

	        ////////////////////////////////////////////////////
	        al_destroy_bitmap(mapa);
	        al_destroy_bitmap(pacman);
	        al_destroy_bitmap(azul);
	        al_destroy_bitmap(vermelho);
	        al_destroy_bitmap(amarelo);
	        al_destroy_bitmap(verde);
	        al_destroy_bitmap(rosa);
	        al_destroy_bitmap(marrom);
	        al_destroy_bitmap(ball);
	        //al_destroy_sample(win);
	        al_destroy_timer(timer);
	        al_destroy_display(display);
	        al_destroy_event_queue(event_queue);
	        return 0;
	    }
