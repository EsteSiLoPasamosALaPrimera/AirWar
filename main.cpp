#include <iostream>
#include "fstream"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "Cola_Paginada.h"
#include "Torre.h"
#include "TorreMisil.h"
#include "Elemento.h"
#include "Lista_Paginada.h"
#include "Jugador.h"
#include "BalaTorre.h"


#define PANT_X 1300
#define PANT_Y 690
const float FPS=60;
enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
using namespace std;

int main(int argc, char* argv[]) {

    /*Lista_Paginada bl;
    bl.nom_archivo="/home/alfredo/Inicio/Documentos/balas.txt";
    bl.insertar(0,Bala(50,50,50));
    bl.insertar(0,Bala(60,60,60));
    bl.insertar(0,Bala(70,70,70));
    bl.insertar(0,Bala(70,70,70));
    bl.insertar(0,Bala(70,70,70));
    bl.imprimir();*/


    /*ALLEGRO_DISPLAY *ventana = NULL;
    ALLEGRO_EVENT_QUEUE *eventos = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER* timer_torres=NULL;
    bool key[4] = {false, false, false, false};
    bool redraw = true;

    al_init();
    al_init_image_addon();
    al_install_keyboard();

    timer = al_create_timer(1.0/FPS);
    timer_torres=al_create_timer(2);
    ventana = al_create_display(PANT_X, PANT_Y);
    eventos = al_create_event_queue();

    al_register_event_source(eventos, al_get_display_event_source(ventana));
    al_register_event_source(eventos, al_get_timer_event_source(timer));
    al_register_event_source(eventos,al_get_timer_event_source(timer_torres));
    al_register_event_source(eventos, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);
    al_start_timer(timer_torres);

    Jugador jugador;
    Lista_Paginada torres;
    Lista_Paginada balas_enemigas("/home/alfredo/Inicio/Documentos/balasTorre.txt",5);
    Lista_Paginada balas_naves("/home/alfredo/Inicio/Documentos/balasNaves.txt",5);
    int pasosTorre=0;

    while (true) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (ev.timer.source == timer) {
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
                redraw = true;
            }else if(ev.timer.source==timer_torres){
                torres.insertar(0,Torre());
            }
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
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
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
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
            }
        }
        if (redraw && al_is_event_queue_empty(eventos)) {
            if(jugador.vidas<=0){
                break;
            }
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(jugador.imagen, jugador.posX, jugador.posY, 0);
            if(jugador.balas.tam>0){
                for(int p=0;p<jugador.balas.tam;p++){
                    Elemento bTemp=jugador.balas.recorrer(p);
                    al_draw_bitmap(bTemp.imagen,bTemp.posX,bTemp.posY,0);

                }
                jugador.mover_Balas();
                jugador.eliminar_Balas();

            }
            if(torres.tam>0){
                for(int u=0;u<torres.tam;u++){
                    Elemento tTemp=torres.recorrer(u);
                    al_draw_bitmap(tTemp.imagen,tTemp.posX,tTemp.posY,0);
                    if(pasosTorre>=50){
                        if(tTemp.getID()=="TR"){
                            balas_enemigas.insertar(0,BalaTorre(tTemp.posX,tTemp.posX,tTemp.posY));
                        }else{
                            balas_enemigas.insertar(0,BalaMisil(tTemp.posX,tTemp.posX,tTemp.posY));
                        }
                    }
                }
                torres.moverse();
                jugador.detectarColisionBalas(torres);
                jugador.detectarColisionJugador(torres,50);
                for(int i=0;i<torres.tam;i++){
                    if(torres.recorrer(i).posY>=PANT_Y || torres.recorrer(i).posY<0){
                        torres.remover(i);
                    }
                }
                if(pasosTorre>=50){
                    pasosTorre=0;
                }
                pasosTorre++;
            }

            if(balas_enemigas.tam>0){
                for(int s=0;s<balas_enemigas.tam;s++){
                    Elemento bEn=balas_enemigas.recorrer(s);
                    al_draw_bitmap(bEn.imagen,bEn.posX,bEn.posY,0);
                }
                balas_enemigas.diagonal();
                jugador.detectarColisionBalasEnemigas(balas_enemigas,10);
                for(int i=0;i<balas_enemigas.tam;i++){
                    if(balas_enemigas.recorrer(i).posY>=PANT_Y){
                        balas_enemigas.remover(i);
                    }
                }
            }
            al_flip_display();
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(eventos);
    al_destroy_display(ventana);*/

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

