#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


 
const int LARGURA_TELA = 580;
const int ALTURA_TELA = 480;
char *nome;
int c1=255,c2=0,c3=0;
ALLEGRO_BITMAP *fundo = NULL;
ALLEGRO_BITMAP *imagem = NULL;
ALLEGRO_BITMAP *inicio = NULL;
ALLEGRO_BITMAP *botaoC = NULL;
ALLEGRO_BITMAP *botaoCor = NULL;
ALLEGRO_BITMAP *botaoR = NULL;
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_FONT *fonte = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
char str[17];
bool sair = false;
bool concluido = false;
int x,y,pos_x,pos_y;
int bmp [480] [1440],curs [480] [1440],cursor=12;

bool inicializar();
void manipular_entrada(ALLEGRO_EVENT evento);
void exibir_texto_centralizado();
bool carregar_arquivos();
void finalizar();
void geraBit();
int testaArquivo();
bool validaNome();
void copiaBitmap();
void telaInicial();
bool carregaTela();
bool carregaCursor();
bool carregaBota();
bool carregaCor();
bool carregaBotaR();
int geraBitMuda();
void Circ();
void retaVerDown ();
void retaVerUp ();
void retaInclRigUp();
void retaInclRigDown();
void retaHorDown();
void retaHorUp();
void retaInclLefDown();
void retaInclLefUp();
int  tioPita();
void Circ();
void botaoRGB();
void botaoCir();
void botaoRet();
void ponto();



 
int main(void){
    bool draw = true;
    int c1=255,c2=0,c3=0;
    nome=(char*) malloc(30*sizeof(char));
    int i,j,k,w,l,r=0,g=0,b=0,ps_1_x,ps_1_y,ps_2_x,ps_2_y,tamanho,okX = 0,okY = 0;
    bool retaOk_1 = false,retaOk_2 = false,bm=false,circuloOk_2=false,circuloOk_1=false;
    if (!inicializar())
    {
        return -1;
    }
 
    strcpy(str, "");
 
    if (!carregar_arquivos())
    {
        return -1;
    }

    telaInicial();
    copiaBitmap(nome,bmp);
    geraBit("tela.bmp",bmp);
    carregaTela();
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    while (!sair){

        while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
 
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(evento.keyboard.keycode==23){
                    cursor++;
                }
                else if(evento.keyboard.keycode==19){
                    cursor--;
                }
                else if(evento.keyboard.keycode==7){
                    
                   
                        if (geraBitMuda("tela.bmp",bmp, 255,0,0,c3,c2,c1) != 1){
                            c1=0;
                            c2=255;
                            
                            if (geraBitMuda("tela.bmp",bmp, 0,0,255,c3,c2,c1) != 1){
                                c1=0;
                                c2=0;
                                c3=255;
                                
                                if (geraBitMuda("tela.bmp",bmp, 0,255,0,c3,c2,c1) != 1){
                                    c1=255;
                                    c2=0;
                                    c3=0;   
                                }
                            }
                        }
                    
                    c1=255;
                    c2=0;
                    c3=0; 
                    carregaTela();
                }
                if(cursor<=0){
                    cursor=0;
                }
                else if(cursor>=30){
                    cursor=30;
                }

            }
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                // Verificamos se ele está sobre a região do retângulo central
                if (evento.mouse.x >= 511 &&
                    evento.mouse.x <= 562 &&
                    evento.mouse.y >= 130 &&
                    evento.mouse.y <= 207 ){
                    botaoCir(r,g,b);
                    while(!circuloOk_1){
                        
                        //pega primeiro click do centro do circulo.
                        while (!al_is_event_queue_empty(fila_eventos)){
                        ALLEGRO_EVENT evento;
                        al_wait_for_event(fila_eventos, &evento);
                            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                                ps_1_x =evento.mouse.x ;
                                ps_1_y =evento.mouse.y ;
                                while(!circuloOk_2){
                                   
                                    while (!al_is_event_queue_empty(fila_eventos)){
                                        ALLEGRO_EVENT evento;
                                        al_wait_for_event(fila_eventos, &evento);
                                       
                                        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                                            ps_2_x =evento.mouse.x ;
                                            ps_2_y =evento.mouse.y ;
                                            
                                            if(ps_1_y > ps_2_y){
                                                ps_2_y = ps_1_y - ps_2_y;
                                            }
                                            else{
                                                ps_2_y -= ps_1_y;
                                            }
                                            if(ps_1_x>ps_2_x){
                                                ps_2_x=ps_1_x-ps_2_x;
                                            }
                                            else{
                                                ps_2_x-=ps_1_x;
                                            }

                                            ps_2_y = sqrt(pow(ps_2_y,2)+pow(ps_2_x,2));
                                            Circ(bmp, ps_1_y, ps_1_x ,ps_2_y ,r,g, b);
                                            
                                            circuloOk_2=true;
                                            circuloOk_1=true;   
                                        }
                                        else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                                            pos_x = evento.mouse.x;
                                            pos_y = evento.mouse.y;

                                            if(pos_x>480)
                                                pos_x=480;
                                        }
                                        al_draw_bitmap(fundo, 0, 0, 0);
                                        al_draw_bitmap(botaoC, 0, 0, 0);
                                        al_draw_bitmap(botaoR, 0, 0, 0);
                                        al_draw_bitmap(botaoCor, 0, 0, 0);
                                        al_draw_bitmap(imagem, 0, 0, 0);
                                        al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
                                        al_draw_filled_rectangle(pos_x, pos_y, pos_x + cursor, pos_y-cursor, al_map_rgb(r,g,b));
                                        al_flip_display();
                                    }
                                }
                            }
                            else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                                pos_x = evento.mouse.x;
                                pos_y = evento.mouse.y;

                                if(pos_x>480)
                                    pos_x=480;
                            }
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(botaoC, 0, 0, 0);
                            al_draw_bitmap(botaoR, 0, 0, 0);
                            al_draw_bitmap(botaoCor, 0, 0, 0);
                            al_draw_bitmap(imagem, 0, 0, 0);
                            al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
                            al_draw_filled_rectangle(pos_x, pos_y, pos_x + cursor, pos_y - cursor, al_map_rgb(r,g,b));
                            al_flip_display();
                        }
                    }
                    circuloOk_2=false;
                    circuloOk_1=false;

                }
                else if (evento.mouse.x >= 511 && 
                    evento.mouse.x <= 562 && 
                    evento.mouse.y >= 218 && 
                    evento.mouse.y <= 302 ){
                    
                    botaoRet(r,g,b);
                    while(!retaOk_1){
                        //pega primeiro click do centro do circulo.
                        while (!al_is_event_queue_empty(fila_eventos)){
                        ALLEGRO_EVENT evento;
                        al_wait_for_event(fila_eventos, &evento);
                            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                                ps_1_x =evento.mouse.x ;
                                ps_1_y =evento.mouse.y ;
                                ponto(ps_1_x,ps_1_y,r,g,b);

                                while(!retaOk_2){
                                    while (!al_is_event_queue_empty(fila_eventos)){
                                        ALLEGRO_EVENT evento;
                                        al_wait_for_event(fila_eventos, &evento);
                                        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                                            ps_2_x =evento.mouse.x ;
                                            ps_2_y =evento.mouse.y ;
                                            for (i=0;i<3;i++){

                                                if(ps_2_x+i == ps_1_x || ps_2_x-i == ps_1_x){
                                                    okX=1;
                                                    ponto(ps_1_x,ps_2_y,r,g,b); 
                                                }
                                                if(ps_2_y+i == ps_1_y || ps_2_y-i == ps_1_y){
                                                    okY=1;
                                                     ponto(ps_2_x,ps_1_y,r,g,b); 
                                                }
                                            }                                        
                                            if(ps_2_y > ps_1_y && okX == 1 ){ 
                                                tamanho = ps_2_y - ps_1_y;
                                                retaVerDown(bmp,ps_1_y,ps_1_x,tamanho,r,g,b);
                                                retaOk_1=true;
                                                retaOk_2=true;
                                                okX = 0;
                                            }
                                            else if(okY==1 && ps_2_x > ps_1_x){ 
                                                tamanho = ps_2_x - ps_1_x;
                                                retaHorUp(bmp,ps_1_y,ps_1_x,tamanho,r,g,b);
                                                retaOk_1=true;
                                                retaOk_2=true;
                                                okY = 0;
                                            }
                                            else if(okY==1 && ps_2_x < ps_1_x){ 
                                                tamanho = ps_1_x - ps_2_x;
                                                retaHorDown(bmp,ps_1_y,ps_1_x,tamanho,r,g,b);
                                                retaOk_1=true;
                                                retaOk_2=true;
                                                okY = 0;
                                            }
                                            else if(ps_2_y < ps_1_y && okX ==1){ 
                                                tamanho = ps_1_y - ps_2_y;
                                                retaVerUp(bmp,ps_1_y,ps_1_x,tamanho,r,g,b);
                                                retaOk_1=true;
                                                retaOk_2=true;
                                                okX = 0;
                                            }
                                            else if(ps_2_y > ps_1_y && ps_2_x > ps_1_x){ 
                                                tamanho = ps_2_x - ps_1_x;
                                                retaInclRigDown(bmp,ps_1_y,ps_1_x,tamanho,r,g,b);
                                                retaOk_1=true;
                                                retaOk_2=true;
                                            } 
                                            else if(ps_2_y < ps_1_y && ps_2_x < ps_1_x){ 
                                                tamanho = ps_1_x - ps_2_x;
                                                retaInclLefUp(bmp,ps_1_y,ps_1_x,tamanho,r,g,b);
                                                retaOk_1=true;
                                                retaOk_2=true;
                                            }     
                                            else if(ps_2_y < ps_1_y && ps_2_x > ps_1_x){ 
                                                tamanho = ps_2_x - ps_1_x;
                                                retaInclRigUp(bmp,ps_1_y,ps_1_x,tamanho,r,g,b);
                                                retaOk_1=true;
                                                retaOk_2=true;
                                            }
                                            else if(ps_2_y > ps_1_y && ps_2_x < ps_1_x){
                                                tamanho = ps_1_x - ps_2_x;
                                                retaInclLefDown(bmp,ps_1_y,ps_1_x,tamanho,r,g,b);
                                                retaOk_1=true;
                                                retaOk_2=true;
                                            }
                                            
                                        }
                                        else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                                            pos_x = evento.mouse.x;
                                            pos_y = evento.mouse.y;

                                            if(pos_x>480)
                                                pos_x=480;
                                        }
                                        al_draw_bitmap(fundo, 0, 0, 0);
                                        al_draw_bitmap(botaoC, 0, 0, 0);
                                        al_draw_bitmap(botaoR, 0, 0, 0);
                                        al_draw_bitmap(botaoCor, 0, 0, 0);
                                        al_draw_bitmap(imagem, 0, 0, 0);
                                        al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
                                        al_draw_filled_rectangle(pos_x, pos_y, pos_x + cursor, pos_y -cursor, al_map_rgb(r,g,b));
                                        al_flip_display();
                                    }
                                }
                            }
                            else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                                pos_x = evento.mouse.x;
                                pos_y = evento.mouse.y;

                                if(pos_x>480)
                                    pos_x=480;
                            }
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(botaoC, 0, 0, 0);
                            al_draw_bitmap(botaoR, 0, 0, 0);
                            al_draw_bitmap(botaoCor, 0, 0, 0);
                            al_draw_bitmap(imagem, 0, 0, 0);
                            al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
                            al_draw_filled_rectangle(pos_x, pos_y, pos_x + cursor, pos_y - cursor, al_map_rgb(r,g,b));
                            al_flip_display();
                        }
                    }
                retaOk_1=false;
                retaOk_2=false;
                }
                else if (evento.mouse.x >= 506 &&
                    evento.mouse.x <= 515 &&
                    evento.mouse.y >= 342 &&
                    evento.mouse.y <= 355 ){
                    botaoRGB("r+gb.png",r,g,b);
                r+=10;
                r=maximo(r);
                    
                }
                else if (evento.mouse.x >= 526 &&
                    evento.mouse.x <= 537 &&
                    evento.mouse.y >= 342 &&
                    evento.mouse.y <= 355 ){
                    botaoRGB("rg+b.png",r,g,b);
                g+=10;
                g=maximo(g);
                }
                else if (evento.mouse.x >= 546 &&
                    evento.mouse.x <= 556 &&
                    evento.mouse.y >= 342 &&
                    evento.mouse.y <= 355 ){
                    botaoRGB("rgb+.png",r,g,b);
                b+=10;
                b=maximo(b);
                }
                else if (evento.mouse.x >= 546 &&
                    evento.mouse.x <= 556 &&
                    evento.mouse.y >= 382 &&
                    evento.mouse.y <= 396 ){
                    botaoRGB("rgb-.png",r,g,b);
                    b-=10;
                    b=maximo(b);
                }
                else if (evento.mouse.x >= 527 &&
                    evento.mouse.x <= 536 &&
                    evento.mouse.y >= 382 &&
                    evento.mouse.y <= 396 ){
                    botaoRGB("rg-b.png",r,g,b);
                    g-=10;
                    g=maximo(g);
                }
                else if (evento.mouse.x >= 507 &&
                    evento.mouse.x <= 516 &&
                    evento.mouse.y >= 382 &&
                    evento.mouse.y <= 396 ){
                    botaoRGB("r-gb.png",r,g,b);
                    r-=10;
                    r=maximo(r);
                }
                else{
                    
                    x=evento.mouse.x ;
                    y=evento.mouse.y ;
                    ponto(x,y,r,g,b);
                    al_draw_bitmap(imagem, 0, 0, 0);
                    al_draw_filled_rectangle(pos_x, pos_y, pos_x + cursor, pos_y - cursor, al_map_rgb(r,g,b));
                    al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
                    al_flip_display();     
                }       
            }
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                sair = true; 
            }
            else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                pos_x = evento.mouse.x;
                pos_y = evento.mouse.y;

                if(pos_x>480)
                    pos_x=480;
            }
            al_draw_bitmap(fundo, 0, 0, 0);
            al_draw_bitmap(botaoC, 0, 0, 0);
            al_draw_bitmap(botaoR, 0, 0, 0);
            al_draw_bitmap(botaoCor, 0, 0, 0);
            al_draw_bitmap(imagem, 0, 0, 0);
            al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
            al_draw_filled_rectangle(pos_x, pos_y, pos_x + cursor, pos_y - cursor, al_map_rgb(r,g,b));
            al_flip_display();
        }
 
        al_draw_bitmap(fundo, 0, 0, 0);
        al_draw_bitmap(botaoC, 0, 0, 0);
        al_draw_bitmap(botaoR, 0, 0, 0);
        al_draw_bitmap(botaoCor, 0, 0, 0);
        al_draw_bitmap(imagem, 0, 0, 0);
        al_draw_filled_rectangle(pos_x, pos_y, pos_x + cursor, pos_y - cursor, al_map_rgb(r,g,b));
        al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
        al_flip_display();
    }
 
    finalizar();
    free(nome);
    return 0;
}
int maximo(int h){
    if(h<=0){
        return 0;
    }
    else if(h>=255){
        return 255;
    }
    return h;

}
void ponto(int x, int y,int r,int g, int b){
    int i,k,j,l;

    for(i=0;i<x*3;i+=10);
        i-=10;
        if(x<480 && y < 480){
            for(j=0;j<cursor;j++){
                for(l=0;l<cursor*3;l+=3){
                    bmp[(480-y)+j][l+(x*3)+2]=r;
                    bmp[(480-y)+j][l+(x*3)+1]=g;
                    bmp[(480-y)+j][l+(x*3)]=b;
                }
            }
            geraBit("tela.bmp",bmp);
            carregaTela();
        }
}
void botaoRGB(char arqPNG[30],int r, int g, int b){
    int w,i,j,k,l;
    carregaCor(arqPNG);
    al_draw_bitmap(fundo, 0, 0, 0);
    al_draw_bitmap(botaoC, 0, 0, 0);
    al_draw_bitmap(botaoR, 0, 0, 0);
    al_draw_bitmap(botaoCor, 0, 0, 0);
    al_draw_bitmap(imagem, 0, 0, 0);
     al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
    al_flip_display();
    
    for(w=0;w<10000;w++);
    carregaCor("rgb.png");
    al_draw_bitmap(fundo, 0, 0, 0);
    al_draw_bitmap(botaoC, 0, 0, 0);
    al_draw_bitmap(botaoR, 0, 0, 0);
    al_draw_bitmap(botaoCor, 0, 0, 0);
    al_draw_bitmap(imagem, 0, 0, 0);
    al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
    al_flip_display();
}
void botaoRet(int r, int g, int b){
    int w,i,j,k,l;
    carregaBotaR("BotR2.png");
    al_draw_bitmap(fundo, 0, 0, 0);
    al_draw_bitmap(botaoC, 0, 0, 0);
    al_draw_bitmap(botaoR, 0, 0, 0);
    al_draw_bitmap(botaoCor, 0, 0, 0);
    al_draw_bitmap(imagem, 0, 0, 0);
    al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
    al_flip_display();
    
    for(w=0;w<10000;w++);
    carregaBotaR("BotR1.png");
    al_draw_bitmap(fundo, 0, 0, 0);
    al_draw_bitmap(botaoC, 0, 0, 0);
    al_draw_bitmap(botaoR, 0, 0, 0);
    al_draw_bitmap(botaoCor, 0, 0, 0);
    al_draw_bitmap(imagem, 0, 0, 0);
    al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
    al_flip_display();
}
void botaoCir(int r, int g, int b){
    int w,i,j,k,l;
    carregaBota("BotCir2.png");
    al_draw_bitmap(fundo, 0, 0, 0);
    al_draw_bitmap(botaoC, 0, 0, 0);
    al_draw_bitmap(botaoR, 0, 0, 0);
    al_draw_bitmap(botaoCor, 0, 0, 0);
    al_draw_bitmap(imagem, 0, 0, 0);
    al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
    al_flip_display();
    
    for(w=0;w<10000;w++);
    carregaBota("BotCir1.png");
    al_draw_bitmap(fundo, 0, 0, 0);
    al_draw_bitmap(botaoC, 0, 0, 0);
    al_draw_bitmap(botaoR, 0, 0, 0);
    al_draw_bitmap(botaoCor, 0, 0, 0);
    al_draw_bitmap(imagem, 0, 0, 0);
    al_draw_filled_rectangle(520,420, 550, 450, al_map_rgb(r,g,b));
    al_flip_display();
}
void telaInicial(){

    while (!concluido){

        while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
 
            if (!concluido){
                manipular_entrada(evento);
 
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
                    concluido = validaNome();
                }
            }
 
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                concluido = true;
                sair = true; 
            }
        }
 
        al_draw_bitmap(inicio, 0, 0, 0);
 
        if (!concluido){
            al_draw_text(fonte, al_map_rgb(0, 0, 0), 290,
                        (450 - al_get_font_ascent(fonte)) / 2,
                        ALLEGRO_ALIGN_CENTRE, "Nome do arquivo:");
        }
        
    
        exibir_texto_centralizado();

        al_flip_display();
    }
}
 
bool inicializar(){



    if (!al_init()){
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return false;
    }
 
    al_init_font_addon();
 
    if (!al_init_ttf_addon()){
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return false;
    }
    al_init_primitives_addon();
    
    if (!al_init_primitives_addon()){
        fprintf(stderr, "Falha ao inicializar primitives\n");
        return false;
    }
 
    if (!al_init_image_addon()){
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return false;
    }

    if (!al_install_keyboard()){
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    
    if (!janela){
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }
    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }
 
    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    al_set_window_title(janela, "CART");
 
    fila_eventos = al_create_event_queue();
    if (!fila_eventos){ 
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return false;
    }
 
    // Dizemos que vamos tratar os eventos vindos do mouse
    al_register_event_source(fila_eventos, al_get_mouse_event_source());  
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
 
    return true;
}
bool carregaTela(){
    imagem = al_load_bitmap("tela.bmp");
    
    if (!imagem){
        fprintf(stderr, "Falha ao carregar \"tela.bmp\".\n");
        return false;
    }
}
bool carregaBota(char arqui [30]){
    botaoC = al_load_bitmap(arqui);
    
    if (!botaoC){
        fprintf(stderr, "Falha ao carregar \"BotC\".\n");
        return false;
    }
}
bool carregaCor(char arqui [30]){
    botaoCor = al_load_bitmap(arqui);
    
    if (!botaoCor){
        fprintf(stderr, "Falha ao carregar \"BotC\".\n");
        return false;
    }
}
bool carregaBotaR(char arqui [30]){
    botaoR = al_load_bitmap(arqui);
    
    if (!botaoR){
        fprintf(stderr, "Falha ao carregar \"BotC\".\n");
        return false;
    }
}

bool carregar_arquivos(){
    fundo = al_load_bitmap("modeloTela.png");
    
    if (!fundo){
        fprintf(stderr, "Falha ao carregar \"bg.jpg\".\n");
        return false;
    }
    carregaCor("rgb.png");
    carregaBota("BotCir1.png");
    carregaBotaR("BotR1.png");
    carregaTela();
    inicio = al_load_bitmap("inicio.png");
    
    if (!inicio){
        fprintf(stderr, "Falha ao carregar \"tela.bmp\".\n");
        return false;
    }

    fonte = al_load_font("SIXTY.TTF", 42, 0);
    
    if (!fonte){
        fprintf(stderr, "Falha ao carregar \"comic.ttf\".\n");
        return false;
    }
 
    return true;
}
 
void finalizar()
{
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(imagem);
    al_destroy_bitmap(inicio);
    al_destroy_bitmap(botaoC);
    al_destroy_bitmap(botaoR);
    al_destroy_bitmap(botaoCor);
    
    al_destroy_font(fonte);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
}
 
void manipular_entrada(ALLEGRO_EVENT evento){

    if (evento.type == ALLEGRO_EVENT_KEY_CHAR){
        
        if (strlen(str) <= 16){
            char temp[] = {evento.keyboard.unichar, '\0'};
            if (evento.keyboard.unichar == ' '){
                strcat(str, temp);
            }
            else if (evento.keyboard.unichar >= '0' &&
                     evento.keyboard.unichar <= '9'){
                strcat(str, temp);
            }
            else if (evento.keyboard.unichar >= 'A' &&
                     evento.keyboard.unichar <= 'Z'){
                strcat(str, temp);
            }
            else if (evento.keyboard.unichar >= 'a' &&
                     evento.keyboard.unichar <= 'z'){
                strcat(str, temp);
            }
        }
        if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0){
            str[strlen(str) - 1] = '\0';
        }
    }
}
 
void exibir_texto_centralizado(){
    
    if (strlen(str) > 0){
        al_draw_text(fonte, al_map_rgb(0,0,0), 180- al_get_font_ascent(fonte),
        (565 - al_get_font_ascent(fonte)) / 2,
        ALLEGRO_ALIGN_CENTRE + al_get_font_ascent(fonte), str);
    }
}
void geraBit(char arquivoT [30], int matriz [480] [1440]){
    FILE *arq;
    int l,p,a=0xff,k,cont,i [12]={0x42,0x4d,0x36,0x8c,0x00,0x0a,0x28,0xe0,0x01,0x18,0x12,0x0b};
    int dire [] = {0,1,2,3,5,4,4,4,4,4,2,4,4,4,6,4,4,4,7,8,4,4,7,8,4,4,8,4,9,4,4,4,4,4,4,3,5,4,10,11,4,4,10,11,4,4,4,4,4,4,4,4,4,4};
    arq=fopen(arquivoT, "wb");
    if(arq!=NULL){
            
        for(k=0;k<54;k++){
            fputc(i[dire[k]],arq);
        }
        for(k=0;k<480;k++){
            for(cont =0;cont < 1440;cont ++){   
                fputc(matriz[k] [cont],arq);                   
            }
        }
    }
}
int geraBitMuda(char arquivoT [30], int matriz [480] [1440], int vermelho, int verde, int azul, int r,int g, int b){
    FILE *arq;
    int retor =0;
    int l,p,a=0xff,k,cont,i [12]={0x42,0x4d,0x36,0x8c,0x00,0x0a,0x28,0xe0,0x01,0x18,0x12,0x0b};
    int dire [] = {0,1,2,3,5,4,4,4,4,4,2,4,4,4,6,4,4,4,7,8,4,4,7,8,4,4,8,4,9,4,4,4,4,4,4,3,5,4,10,11,4,4,10,11,4,4,4,4,4,4,4,4,4,4};
    arq=fopen(arquivoT, "wb");
    if(arq!=NULL){
            
        for(k=0;k<54;k++){
            fputc(i[dire[k]],arq);
        }
        for(p=0;p<480;p++){
            for(l=0;l<1440;l+=3){
                if(l <1440 && matriz[p] [l] == r && matriz[p] [l+1] == g && matriz[p] [l+2] == b){
                    matriz[p] [l] = vermelho ;
                    matriz[p] [l+1] = verde ;
                    matriz[p] [l+2] = azul ;
                    retor=1;
                }
            }
        }
        for(k=0;k<480;k++){
            for(cont =0;cont < 1440;cont ++){   
                fputc(matriz[k] [cont],arq);                   
            }
        }
    }
    return retor;
}
int testaArquivo(char nome [30]){
    
    FILE *fp;
    fp=fopen(nome,"r");
    
    if(fp!=NULL){
        fclose(fp);
        return 1;
    }
    else{
        return 0;
    }
}
bool validaNome(){
    int i;
    strcpy(nome,str);
    strcat(nome,".bmp");
    if(testaArquivo(nome)==0){
        strcpy(str,"");
         al_draw_bitmap(inicio, 0, 0, 0);
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 290,
        (450 - al_get_font_ascent(fonte)) / 2,
        ALLEGRO_ALIGN_CENTRE, "Arquivo nao existe!");
        al_flip_display();
        for(i=0;i<100000000;i++);
        
        return false;
    }
    else {
        return true;
    }

}

void copiaBitmap(char Narq[30],int matriz [480] [1440]){
    FILE *cop;
    int w,j,k,l,i,cont=0;
    int r,d;

    cop=fopen(Narq, "rb");

    if(cop!=NULL){
        
        for(k=0;k<54;k++){
            fgetc(cop);
        }

        for(k=0;k<480;k++){
            for(cont =0;cont < 1440;cont ++){   
                d=fgetc(cop);
                matriz[k] [cont] = d;
            }
        }
        

    }   
    
    fclose(cop);
    //rename("novo.bmp",nome);
}
void retaVerDown (int matriz [480] [1440], int y, int x ,int tama ,int r,int g, int b) {
    int i;
    //tama=tama*12;
    for (i=0;i<tama && y < 480 ;i+=12){
        ponto(x,y+i,r,g,b);
    }
    geraBit("tela.bmp",bmp);
    carregaTela();
}
void retaVerUp (int matriz [480] [1440], int y, int x ,int tama ,int r,int g, int b) {
    int i;
    //tama=tama*12;
    for (i=0;i<tama && y < 480 ;i+=12){
        ponto(x,y-i,r,g,b);
    }
    geraBit("tela.bmp",bmp);
    carregaTela();
}
void retaInclRigUp(int matriz [480] [1440], int y, int x ,int tama ,int r,int g, int b) {
    int i;
    //tama=tama*12;
    for (i=0;i<tama && y < 480 ;i+=12){
        ponto(x+i,y-i,r,g,b);
    }
    geraBit("tela.bmp",bmp);
    carregaTela();
}

void retaInclRigDown(int matriz [480] [1440], int y, int x ,int tama ,int r,int g, int b) {
    int i;
    //tama=tama*12;
    for (i=0;i<tama && y < 480 ;i+=12){
        ponto(x+i,y+i,r,g,b);
    }
    geraBit("tela.bmp",bmp);
    carregaTela();
}
void retaHorDown(int matriz [480] [1440], int y, int x ,int tama ,int r,int g, int b) {
    int i;
    //tama=tama*12;
    for (i=0;i<tama && y < 480 ;i+=12){
        ponto(x-i,y,r,g,b);
    }
    geraBit("tela.bmp",bmp);
    carregaTela();
}
void retaHorUp(int matriz [480] [1440], int y, int x ,int tama ,int r,int g, int b) {
    int i;
    //tama=tama*12;
    for (i=0;i<tama && y < 480 ;i+=12){
        ponto(x+i,y,r,g,b);
    }
    geraBit("tela.bmp",bmp);
    carregaTela();
}
void retaInclLefDown(int matriz [480] [1440], int y, int x ,int tama ,int r,int g, int b) {
    int i;
    //tama=tama*12;
    for (i=0;i<tama && y < 480 ;i+=12){
        ponto(x-i,y+i,r,g,b);
    }
    geraBit("tela.bmp",bmp);
    carregaTela();
}
void retaInclLefUp(int matriz [480] [1440], int y, int x ,int tama ,int r,int g, int b) {
    int i;
    //tama=tama*12;
    for (i=0;i<tama && y < 480 ;i+=12){
        ponto(x-i,y-i,r,g,b);
    }
    geraBit("tela.bmp",bmp);
    carregaTela();
}
int tioPita(int x, int hipote){
    int y;
    y=pow(hipote,2)-pow(x,2);
    y=sqrt(y);  
    return y;
} 
void Circ(int matriz [480] [1440], int y, int x ,int raio ,int r,int g, int b){
    //printf("%d %d\n",y,x );
    int posi,tex,i,j,k,l=1,px1,px2,px3,px4,py1,py2,py3,py4,px11,px21,px31,px41,py11,py21,py31,py41;

    for(i=0;i<raio;i+=12){
        posi=tioPita(i,raio);   
        
        px1=x+i;
        py1=y+posi;
        px11=x+posi;
        py11=y+i;   
        if(px1>0 && px1 < 480 && py1>12 && py1 <480){
            ponto(px1,py1,r,g,b); 
        }
        if(px11>0 && px11 < 480 && py11>12 && py11 <480){ 
            ponto(px11,py11,r,g,b);
        }
        px2=x-i;
        py2=y+posi;
        px21=x-posi;
        py21=y+i;
        if(px2>0 && px2 <480 && py2>12 && py2 <480){
            ponto(px2,py2,r,g,b);
        }
        if(px21>0 && px21 <480 && py21>12 && py21 <480){
            ponto(px21,py21,r,g,b);
        }
        px3=x-i;
        py3=y-posi;
        px31=x-posi;
        py31=y-i;
        if(px3>0 && px3 <480 && py3>12 && py3 <480){
            ponto(px3,py3,r,g,b);
        }
        if(px31>0 && px31<1440 && py31>12 && py31 <480){
            ponto(px31,py31,r,g,b);
        }
        px4=x+i;
        py4=y-posi;
        px41=x+posi;
        py41=y-i;
        if(px4>0 && px4 < 480 && py4>12 && py4 <480){
            ponto(px4,py4,r,g,b);
        }
        if(px41>0 && px41 < 480 && py41>12 && py41 <480){
            ponto(px41,py41,r,g,b);
        }
        //printf("px1 %d, px2 %d, px3 %d, px4 %d, py1 %d, py2 %d, py3 %d, py4 %d,\n", px1,px2,px3,px4,py1,py2,py3,py4);
        //printf("px11 %d, px21 %d, px31 %d, px41 %d, py11 %d, py21 %d, py31 %d, py41 %d \n",px11,px21,px31,px41,py11,py21,py31,py41);

    }
    //system("pause");
}
