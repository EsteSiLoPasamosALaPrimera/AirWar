#include <iostream>
<<<<<<< HEAD
#include <typeinfo>
#include "fstream"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "Cola_Paginada.h"
#include "ListaPaginada.h"
#include "Torre.h"
#include "TorreMisil.h"
#include "Enemigo.h"


#define PANT_X 1300
#define PANT_Y 690
const float FPS=60;
enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
using namespace std;

int main(int argc, char* argv[]){

    /*ofstream arch("/home/alfredo/Inicio/Documentos/torres.txt");
    arch<<"Dequiem";
    arch.close();*/

    ListaPaginada<Torre> l;
    l.insercionPaginadaAlFinal(Torre(5000,50,50));
    l.insercionPaginadaAlFinal(Torre());
    l.insercionPaginadaAlFinal(TorreMisil());
    l.imprimir();
    /*ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *timer_torres=NULL;
    bool redraw=true;
    bool key[4] = { false, false, false, false };

    ListaPaginada<Torre> torres;

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

    timer_torres=al_create_timer(5);

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

    Cola_Paginada<ALLEGRO_BITMAP*> imagenes(imagen1);
    imagenes.insertar(imagen2);
    imagenes.insertar(imagen3);

    Cola_Paginada<ALLEGRO_BITMAP*> balas;

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
                torres.insertarAlFinal(Torre());
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
            if(torres.tam>0){
                Nodo<Torre>* torr=torres.head;
                while(torr!=NULL){
                    if(torr->element.posY>690 || torr->element.resistencia<=0){
                        Nodo<Torre>* Ttemp=torr->next;
                        torres.remover(torr);
                        torr=Ttemp;
                        Ttemp=NULL;
                        delete Ttemp;
                    }else{
                        al_draw_bitmap(torr->element.imagen,torr->element.posX,torr->element.posY,0);
                        torr->element.moverse();
                        torr=torr->next;
                    }
                }
                torr=NULL;
                delete torr;
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
    al_destroy_event_queue(event_queue);*/

=======

int main() {
    std::cout << "Hello, World!" << std::endl;
>>>>>>> 8c99ef948ed7c43be910cafcebfe29a7157d9ed9
    return 0;
}