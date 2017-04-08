#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Lista_Paginada.h"
#include "Jugador.h"
#include "EnemyFactory.h"
#include "Cola_Paginada.h"
#include "Servidor.h"
#include "Jefe.h"

#define PANT_X 1300
#define PANT_Y 690.0
const float FPS=60;


enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
using namespace std;

int AirWarNivel(int nivel,const char* Nombre_Jug, bool control) {

    ALLEGRO_DISPLAY *ventana = NULL;
    ALLEGRO_EVENT_QUEUE *eventos = NULL;

    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER* timer_torres=NULL;
    ALLEGRO_TIMER* timer_naves=NULL;

    ALLEGRO_BITMAP* img_torre=NULL;
    ALLEGRO_BITMAP* img_jet=NULL;
    ALLEGRO_BITMAP* img_bomber=NULL;
    ALLEGRO_BITMAP* img_kamikaze=NULL;
    ALLEGRO_BITMAP* img_bala=NULL;
    ALLEGRO_BITMAP* img_balamisil=NULL;
    ALLEGRO_BITMAP* img_jugador=NULL;
    ALLEGRO_BITMAP* img_torremisil=NULL;
    ALLEGRO_BITMAP* img_misil=NULL;
    ALLEGRO_BITMAP* img_laser=NULL;
    ALLEGRO_BITMAP* img_aumentadisparos=NULL;
    ALLEGRO_BITMAP* img_escudo=NULL;
    ALLEGRO_BITMAP* img_campo=NULL;
    ALLEGRO_BITMAP* img_jefe=NULL;
    ALLEGRO_BITMAP* img_mina=NULL;
    ALLEGRO_BITMAP* img_escolta=NULL;
    ALLEGRO_BITMAP* fondo=NULL;

    ALLEGRO_FONT* font=NULL;
    ALLEGRO_FONT* font_clear=NULL;

    bool key[4] = {false, false, false, false};
    bool redraw = true;

    al_init();
    al_init_image_addon();
    if(control){
        al_install_keyboard();
    }
    al_init_font_addon();
    al_init_ttf_addon();

    timer = al_create_timer(1.0/FPS);
    timer_torres=al_create_timer(3);
    timer_naves=al_create_timer(1);
    ventana = al_create_display(PANT_X, PANT_Y);
    eventos = al_create_event_queue();

    al_set_window_title(ventana,Nombre_Jug);

    img_torre=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/Torre.png");
    img_torremisil=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/TorreMisil.png");
    img_bala=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/bullet1.png");
    img_balamisil=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/misil2.png");
    img_jet=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/jet.png");
    img_bomber=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/bomber.png");
    img_kamikaze=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/kami.png");
    img_jugador=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/jugador1.png");
    img_laser=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/laser1.png");
    img_misil=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/misil1.png");
    img_mina=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/mina.png");
    img_escolta=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/escolta.png");

    if(nivel%3==1){
        fondo=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/Nivel1.png");
        img_jefe=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/boss1.png");
    }else if(nivel%3==2){
        fondo=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/Nivel2.png");
        img_jefe=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/boss2.png");
    }else{
        fondo=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/Nivel3.png");
        img_jefe=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/boss3.png");
    }
    img_escudo=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/escudo.png");
    img_campo=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/shield3.png");
    img_aumentadisparos=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/aumento.png");

    font=al_load_ttf_font("/home/alfredo/Inicio/Documentos/28 Days Later.ttf",18,0);
    font_clear=al_load_ttf_font("/home/alfredo/Inicio/Documentos/28 Days Later.ttf",42,0);

    al_register_event_source(eventos, al_get_display_event_source(ventana));
    al_register_event_source(eventos, al_get_timer_event_source(timer));
    al_register_event_source(eventos,al_get_timer_event_source(timer_torres));
    al_register_event_source(eventos,al_get_timer_event_source(timer_naves));
    al_register_event_source(eventos, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);
    al_start_timer(timer_torres);
    al_start_timer(timer_naves);

    Jugador jugador;
    Jefe boss(nivel);
    Servidor servidor;
    if(!control){
        servidor.inicializar();
    }
    EnemyFactory fabrica;
    Lista_Paginada torres("/home/alfredo/Inicio/Documentos/torres.txt",5);
    Lista_Paginada balas_enemigas("/home/alfredo/Inicio/Documentos/balasTorre.txt",5);
    Lista_Paginada naves("/home/alfredo/Inicio/Documentos/Naves.txt",5);

    int pasosTorre=0;
    int pasosNaves=0;

    float tiempo_final=0;
    float posYFondo=-1900;

    bool presentacion=true;

    while (control || servidor.server>0) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (ev.timer.source == timer) {
                if(control){
                    if (key[KEY_UP]) {
                        jugador.desplazar(1);
                    }
                    if (key[KEY_DOWN]) {
                        jugador.desplazar(2);
                    }
                    if (key[KEY_LEFT]) {
                        jugador.desplazar(4);
                    }
                    if (key[KEY_RIGHT]) {
                        jugador.desplazar(3);
                    }
                }else{
                    recv(servidor.server, servidor.buffer, servidor.bufsize, 0);
                    string dir=reinterpret_cast<const char*>(servidor.buffer);
                    cout<<"Mensaje original: "<<dir<<endl;
                    while(dir.find('+')==1){
                        string msj_b=dir.substr(0,dir.find('+'));
                        if(msj_b=="U"){
                            jugador.desplazar(1);
                        }else if(msj_b=="D"){
                            jugador.desplazar(2);
                        }else if(msj_b=="L"){
                            jugador.desplazar(4);
                        }else if(msj_b=="R"){
                            jugador.desplazar(3);
                        }else if(msj_b=="S"){
                            jugador.agregarBala();
                        }
                        dir=dir.substr(dir.find('+')+1);
                    }
                    std::fill_n(servidor.buffer, servidor.bufsize, 0);
                }
                redraw = true;
                tiempo_final+=(1.0/FPS);
                if(posYFondo<0){
                    posYFondo+=10*(1.0/FPS);
                }else{
                    al_stop_timer(timer_torres);
                    al_stop_timer(timer_naves);
                    if(torres.tam>0 || naves.tam>0){
                        while(torres.tam>0){
                            torres.remover(torres.tam-1);
                        }
                        while(naves.tam>0){
                            naves.remover(naves.tam-1);
                        }
                    }
                }
            }
            else if(ev.timer.source==timer_torres){
                torres.insertar(torres.tam-1,fabrica.getTorreEnemiga());
            }else if(ev.timer.source==timer_naves){
                naves.insertar(naves.tam-1,fabrica.getNaveEnemiga());
            }
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if (control && ev.type == ALLEGRO_EVENT_KEY_DOWN ) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;

                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;
            }
        }
        else if (control && ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode) {
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
                case ALLEGRO_KEY_W:
                    jugador.agregarBala();
                    break;
                case ALLEGRO_KEY_Q:
                    if(jugador.modo=="BA"){
                        jugador.modo="MS";
                    }else if(jugador.modo=="MS"){
                        jugador.modo="LS";
                    }else if(jugador.modo=="LS"){
                        jugador.modo="BA";
                    }
                    break;
                case ALLEGRO_KEY_D:
                    jugador.ammo_laser+=50;
                    break;
                case ALLEGRO_KEY_E:
                    jugador.usarPowerUp();
                    break;
                case ALLEGRO_KEY_T:
                    jugador.invulnerable+=120;
                    break;
            }
        }
        if (redraw && al_is_event_queue_empty(eventos)) {
            if(jugador.vidas<=0){
                al_draw_textf(font_clear , al_map_rgb(200 , 10 , 100) , 550 , 350 , ALLEGRO_ALIGN_CENTRE , "FIN DEL JUEGO");
                al_flip_display();
                al_rest(2);
                break;
            }
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(fondo,0,posYFondo,0);
            if(jugador.modo=="BA"){
                al_draw_textf(font , al_map_rgb(200 , 10 , 100) , 1250 , 340 , ALLEGRO_ALIGN_CENTRE , "AMMO\nINF");
                al_draw_bitmap(img_bala,1240,310,0);
            }else if(jugador.modo=="MS"){
                al_draw_textf(font , al_map_rgb(200 , 10 , 100) , 1250 , 340 , ALLEGRO_ALIGN_CENTRE , "AMMO %d",jugador.ammo_misil);
                al_draw_bitmap(img_misil,1240,310,0);
            }else if(jugador.modo=="LS"){
                al_draw_textf(font , al_map_rgb(200 , 10 , 100) , 1250 , 340 , ALLEGRO_ALIGN_CENTRE , "AMMO %d",jugador.ammo_laser);
                al_draw_bitmap(img_laser,1240,310,0);
            }
            al_draw_textf(font , al_map_rgb(200 , 10 , 100) , 1250 , 30 , ALLEGRO_ALIGN_CENTRE , "TIME %.2f" ,tiempo_final);
            al_draw_textf(font , al_map_rgb(200 , 10 , 100) , 1250 , 100 , ALLEGRO_ALIGN_CENTRE , "VIDAS %d" , jugador.vidas);
            al_draw_textf(font , al_map_rgb(200 , 10 , 100) , 1250 , 170 , ALLEGRO_ALIGN_CENTRE , "SCORE %d" , jugador.puntaje);
            al_draw_textf(font , al_map_rgb(200 , 10 , 100) , 1250 , 440 , ALLEGRO_ALIGN_CENTRE , "POWER-UPS");
            al_draw_textf(font , al_map_rgb(200 , 10 , 100) , 1250 , 240 , ALLEGRO_ALIGN_CENTRE , "Nivel %d",nivel);
            al_draw_bitmap(img_jugador, jugador.posX, jugador.posY, 0);



            if(posYFondo>=0){
                al_draw_bitmap(img_jefe,boss.posX,boss.posY,0);
                boss.moverse(0,0);
                if(pasosTorre==50){
                    balas_enemigas.insertar(balas_enemigas.tam-1,BalaMisil(0,boss.posX-100,boss.posY+100));
                    balas_enemigas.insertar(balas_enemigas.tam-1,BalaMisil(0,boss.posX+100,boss.posY+100));
                }else if(pasosTorre>=100){
                    pasosTorre=0;
                    balas_enemigas.insertar(balas_enemigas.tam-1,BalaTorre(0,boss.posX-100,boss.posY+100));
                    balas_enemigas.insertar(balas_enemigas.tam-1,BalaTorre(0,boss.posX+100,boss.posY+100));
                }
                jugador.detectarColisionJefe(boss);
                boss=jugador.detectarColisionBalasJefe(boss);
                pasosTorre++;
                if(boss.resistencia<0){
                    al_draw_textf(font_clear , al_map_rgb(200 , 10 , 100) , 550 , 350 , ALLEGRO_ALIGN_CENTRE , "NIVEL COMPLETADO");
                    al_flip_display();
                    al_rest(2);
                    break;
                }
            }else if(posYFondo<0 && posYFondo>=-100){
                al_draw_textf(font_clear , al_map_rgb(200 , 10 , 100) , 550 , 350 , ALLEGRO_ALIGN_CENTRE , "JEFE EN CAMINO");
            }

            if(jugador.invulnerable>0){
                jugador.invulnerable-=(1.0/FPS);
                al_draw_bitmap(img_campo,jugador.posX,jugador.posY,0);
            }else{
                jugador.invulnerable=0;
            }
            if(jugador.powerUps.tam>0){
                if(jugador.powerUps.head->element.getID()=="AD"){
                    al_draw_bitmap(img_aumentadisparos,1240,410,0);
                }else if(jugador.powerUps.head->element.getID()=="AL"){
                    al_draw_bitmap(img_laser,1240,410,0);
                }else if(jugador.powerUps.head->element.getID()=="AM"){
                    al_draw_bitmap(img_misil,1240,410,0);
                }else{
                    al_draw_bitmap(img_escudo,1240,410,0);
                }
            }
            if(jugador.balas.tam>0){
                for(int p=0;p<jugador.balas.tam;p++){
                    Elemento bTemp=jugador.balas.recorrer(p);
                    if(bTemp.getID()=="BA"){
                        al_draw_bitmap(img_bala,bTemp.posX,bTemp.posY,0);
                    }else if(bTemp.getID()=="MS"){
                        al_draw_bitmap(img_misil,bTemp.posX,bTemp.posY,0);
                    }else{
                        al_draw_bitmap(img_laser,bTemp.posX,bTemp.posY,0);
                    }
                }
                jugador.mover_Balas();
                jugador.eliminar_Balas();
            }
            if(torres.tam>0){
                for(int u=0;u<torres.tam;u++){
                    Elemento tTemp=torres.recorrer(u);
                    if(tTemp.getID()=="TR"){
                        al_draw_bitmap(img_torre,tTemp.posX,tTemp.posY,0);
                    }else if(tTemp.getID()=="TM"){
                        al_draw_bitmap(img_torremisil,tTemp.posX,tTemp.posY,0);
                    }else if(tTemp.getID()=="MN"){
                        al_draw_bitmap(img_mina,tTemp.posX,tTemp.posY,0);
                    }else if(tTemp.getID()=="AD"){
                        al_draw_bitmap(img_aumentadisparos,tTemp.posX,tTemp.posY,0);
                    }else if(tTemp.getID()=="AM"){
                        al_draw_bitmap(img_misil,tTemp.posX,tTemp.posY,0);
                    }else if(tTemp.getID()=="AL"){
                        al_draw_bitmap(img_laser,tTemp.posX,tTemp.posY,0);
                    }else{
                        al_draw_bitmap(img_escudo,tTemp.posX,tTemp.posY,0);
                    }
                    if(pasosTorre>=150){
                        if(tTemp.getID()=="TR"){
                            balas_enemigas.insertar(0,BalaTorre(tTemp.posX,tTemp.posX,tTemp.posY));
                        }else if(tTemp.getID()=="TM"){
                            balas_enemigas.insertar(0,BalaMisil(tTemp.posX,tTemp.posX,tTemp.posY));
                        }
                    }
                }
                torres.moverse(jugador.posX,jugador.posY);
                jugador.detectarColisionBalas(torres);
                jugador.detectarColisionJugador(torres,50);
                for(int i=0;i<torres.tam;i++){
                    if(torres.recorrer(i).posY<0 || torres.recorrer(i).posY>=PANT_Y){
                        if(torres.recorrer(i).getID()=="MN"){
                            balas_enemigas.insertar(balas_enemigas.tam-1,BalaMisil(0,550,0));
                            balas_enemigas.insertar(balas_enemigas.tam-1,BalaMisil(0,600,0));
                            balas_enemigas.insertar(balas_enemigas.tam-1,BalaMisil(0,650,0));
                        }
                        torres.remover(i);
                    }
                }
                if(pasosTorre>=150){
                    pasosTorre=0;
                }
                pasosTorre++;
            }

            if(naves.tam>0){
                for(int i=0;i<naves.tam;i++){
                    Elemento nav=naves.recorrer(i);
                    if(nav.getID()=="JT"){
                        al_draw_bitmap(img_jet,nav.posX,nav.posY,0);
                        if(pasosNaves>=50){
                            balas_enemigas.insertar(0,BalaMisil(nav.posX,nav.posX,nav.posY));
                        }
                    }else if(nav.getID()=="JK"){
                        al_draw_bitmap(img_kamikaze,nav.posX,nav.posY,0);
                    }else if(nav.getID()=="BD"){
                        al_draw_bitmap(img_bomber,nav.posX,nav.posY,0);
                        if(pasosNaves>=50){
                            balas_enemigas.insertar(0,BalaMisil(nav.posX,nav.posX,nav.posY));
                        }
                    }else if(nav.getID()=="SC"){
                        al_draw_bitmap(img_escolta,nav.posX,nav.posY,0);
                        if(pasosNaves>=50){
                            balas_enemigas.insertar(0,BalaMisil(nav.posX,nav.posX,nav.posY));
                        }
                    }else if(nav.getID()=="AD"){
                        al_draw_bitmap(img_aumentadisparos,nav.posX,nav.posY,0);
                    }else if(nav.getID()=="AM"){
                        al_draw_bitmap(img_misil,nav.posX,nav.posY,0);
                    }else if(nav.getID()=="AL"){
                        al_draw_bitmap(img_laser,nav.posX,nav.posY,0);
                    }else{
                        al_draw_bitmap(img_escudo,nav.posX,nav.posY,0);
                    }
                }
                naves.moverse(jugador.posX,jugador.posY);
                jugador.detectarColisionJugador(naves,50);
                jugador.detectarColisionBalas(naves);
                for(int c=0;c<naves.tam;c++){
                    if(naves.recorrer(c).posY>=PANT_Y || naves.recorrer(c).posY<0){
                        naves.remover(c);
                    }
                }
                if(pasosNaves>=50){
                    pasosNaves=0;
                }
                pasosNaves++;
            }

            if(balas_enemigas.tam>0){
                for(int s=0;s<balas_enemigas.tam;s++){
                    Elemento bEn=balas_enemigas.recorrer(s);
                    if(bEn.getID()=="BT"){
                        al_draw_bitmap(img_bala,bEn.posX,bEn.posY,0);
                    }else{
                        al_draw_bitmap(img_balamisil,bEn.posX,bEn.posY,0);
                    }

                }
                balas_enemigas.moverse(jugador.posX,jugador.posY);
                jugador.detectarColisionBalasEnemigas(balas_enemigas,20);
                for(int i=0;i<balas_enemigas.tam;i++){
                    if(balas_enemigas.recorrer(i).posY>=PANT_Y){
                        balas_enemigas.remover(i);
                    }
                }
            }

            al_flip_display();
        }
    }
    if(!control){

        while (!servidor.isExit){
            cout << "\nServer: ";
            do {
                //cin >> buffer;
                //send(server, buffer, bufsize, 0);
                if (*servidor.buffer == '#') {
                    //send(server, buffer, bufsize, 0);
                    *servidor.buffer = '*';
                    servidor.isExit = true;
                }
            } while (*servidor.buffer != '*');
        }
        cout<< "\n\n=> Connection terminated with IP "<< inet_ntoa(servidor.server_addr.sin_addr);
        close(servidor.server);
        close(servidor.client);
        cout<< "\nGoodbye..."<< endl;
        servidor.isExit = false;
        exit(1);
        cout<< "adios"<<endl;
        close(servidor.client);

    }

    al_destroy_timer(timer);
    al_destroy_timer(timer_naves);
    al_destroy_timer(timer_torres);
    al_destroy_bitmap(img_jugador);
    al_destroy_bitmap(img_torre);
    al_destroy_bitmap(img_torremisil);
    al_destroy_bitmap(img_bala);
    al_destroy_bitmap(img_balamisil);
    al_destroy_bitmap(img_jet);
    al_destroy_bitmap(img_kamikaze);
    al_destroy_bitmap(img_bomber);
    al_destroy_bitmap(img_laser);
    al_destroy_bitmap(img_misil);
    al_destroy_bitmap(img_escudo);
    al_destroy_bitmap(img_campo);
    al_destroy_bitmap(img_mina);
    al_destroy_bitmap(img_escolta);
    al_destroy_bitmap(img_aumentadisparos);
    al_destroy_bitmap(fondo);
    al_destroy_bitmap(img_jefe);
    al_destroy_font(font);
    al_destroy_font(font_clear);
    al_destroy_event_queue(eventos);
    al_destroy_display(ventana);

    return 0;
}

int main(int argc, char* argv[]){

    AirWarNivel(1,"Partida de Alfredo",true);
    return 0;

}




/*int main(int argc, char* argv[]){

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *timer_torres=NULL;
    bool redraw=true;
    bool key[4] = { false, false, false, false };
    inicializarTorres();

    if(!al_init()) {
        al_show_native_message_box(display, "Error", "Error", "Failed the display!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    if(!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Fallar al crear al_init_image_addon!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    if(!al_install_keyboard()) {
        al_show_native_message_box(display, "Error", "Error", "Fallar al cargar keyboard!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        al_show_native_message_box(display, "Error", "Error", "Fallo al crear el timer!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    timer_torres=al_create_timer(4);

    display = al_create_display(PANT_X, PANT_Y);
    if(!display) {
        al_show_native_message_box(display, "Error", "Error", "Fallo al crear el display!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(timer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        al_show_native_message_box(display, "Error", "Error", "Problemas al crear el queue!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    ALLEGRO_BITMAP* imagen1=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/fondo1.png");
    if(!imagen1) {
        al_show_native_message_box(display, "Error", "Error", "Problema al cargar imagen 1!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return 0;
    }

    ALLEGRO_BITMAP* imagen2=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/fondo2.png");
    if(!imagen2) {
        al_show_native_message_box(display, "Error", "Error", "Problema al cargar imagen 2!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return 0;
    }

    ALLEGRO_BITMAP* imagen3=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/fondo3.png");
    if(!imagen3) {
        al_show_native_message_box(display, "Error", "Error", "Problema al cargar imagen 3!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return 0;
    }

    ALLEGRO_BITMAP* jug=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/nave3.png");
    if(!jug) {
        al_show_native_message_box(display, "Error", "Error", "Problema al cargar jug!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return 0;
    }

    ALLEGRO_BITMAP* bala=al_load_bitmap("/home/alfredo/Inicio/Documentos/Imágenes/bala2.png");
    if(!bala) {
        al_show_native_message_box(display, "Error", "Error", "Problema al cargar bala!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return 0;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_register_event_source(event_queue,al_get_timer_event_source(timer_torres));

    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();

    al_start_timer(timer);

    al_start_timer(timer_torres);

    int coord_x=50;
    int coord_y=50;
    int cont_torres=0;

    Cola_Paginada<ALLEGRO_BITMAP*> imagenes(imagen1);
    imagenes.insertar(imagen2);
    imagenes.insertar(imagen3);

    Cola_Paginada<ALLEGRO_BITMAP*> balas;

    Lista_Paginada torres;

    while(true)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {

            if(ev.timer.source==timer){
                if(key[KEY_UP] && coord_y >= 4.0) {
                    coord_y -= 4.0;
                }

                if(key[KEY_DOWN] && coord_y <= PANT_Y - 4.0) {
                    coord_y += 4.0;
                }

                if(key[KEY_LEFT] && coord_x >= 4.0) {
                    coord_x -= 4.0;
                }

                if(key[KEY_RIGHT] && coord_x <= PANT_X - 4.0) {
                    coord_x += 4.0;
                }
                redraw = true;
            }else if(ev.timer.source==timer_torres){
                torres.insertar(0,lecturaTorres(cont_torres));
                cont_torres++;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;

                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
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
                case ALLEGRO_KEY_W:
                    balas.insertar(bala,coord_x,coord_y);
                    break;
            }
        }
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0,0,0));
            Nodo<ALLEGRO_BITMAP*>* curr=imagenes.head;
            int alt=0;
            while(curr!=NULL){
                al_draw_bitmap(curr->element,0,alt,0);
                curr=curr->next;
                alt+=230;
            }
            al_draw_bitmap(jug,coord_x,coord_y,0);
            curr=balas.head;
            while(curr!=NULL){
                al_draw_bitmap(curr->element,curr->posX,curr->posY,0);
                al_draw_bitmap(curr->element,curr->posX+80,curr->posY,0);
                curr->posY-=20;
                curr=curr->next;
            }
            if(torres.tam>0) {
                for(int i=0;i<torres.tam;i++){
                    Elemento tempEn=torres.recorrer(i);
                    if (tempEn.posY > PANT_Y || tempEn.resistencia <= 0) {
                        torres.remover(i);
                    }else{
                        al_draw_bitmap(tempEn.imagen, tempEn.posX, tempEn.posY, 0);
                    }
                }
                torres.moverse();
            }
            curr=NULL;
            delete curr;
            al_flip_display();
            al_rest(0.15);
            imagenes.insertar(imagenes.remover());
        }
    }

    al_destroy_bitmap(imagen1);
    al_destroy_bitmap(imagen2);
    al_destroy_bitmap(imagen3);
    al_destroy_bitmap(jug);
    al_destroy_bitmap(bala);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}*/

/*void inicializarTorres(){
    ofstream arquive("/home/alfredo/Inicio/Documentos/totalTorres.txt");
    for(int v=0;v<50;v++){
        arquive<<Torre().info();
        arquive<<TorreMisil().info();
    }
    arquive.close();
}

Elemento lecturaTorres(int pPos){
    fstream arquive("/home/alfredo/Inicio/Documentos/totalTorres.txt");
    string texto="";
    while(pPos>=0){
        getline(arquive,texto);
        pPos--;
    }
    arquive.close();

    string id=texto.substr(0,texto.find(';'));
    texto=texto.substr(texto.find(';')+1);
    int resist=stoi(texto.substr(0,texto.find(';')));
    texto=texto.substr(texto.find(';')+1);
    int posicX=stoi(texto.substr(0,texto.find(';')));
    texto=texto.substr(texto.find(';')+1);
    int posicY=stoi(texto.substr(0,texto.find(';')));

    if(id=="TM"){
        return TorreMisil(resist,posicX,posicY);
    }else if(id=="TR"){
        return Torre(resist,posicX,posicY);
    }else{
        cout<<"Problemas con el ID"<<endl;
    }
}*/

