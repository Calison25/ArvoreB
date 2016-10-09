#include "main.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


int main (){
	ALLEGRO_DISPLAY *window = NULL;

    ALLEGRO_BITMAP *background,*arvore, *positivo, *negativo, *voltarImg = NULL;

    ALLEGRO_EVENT_QUEUE *queue_events = NULL;

    ALLEGRO_FONT * font = NULL;

    int choice,result,listChoice,voltar,sair;

    choice = 0;
    listChoice = 0;
    sair = 0;

     // Inicializamos a biblioteca
    al_init();

    //bibliotecas para fontes ttf
    al_init_font_addon();
    al_init_ttf_addon();

    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();

    // Criamos a nossa janela - dimensões de 640x480 px
    window = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    al_set_window_position(window, 180, 50);


    //cor de fundo da minha tela
    al_clear_to_color(al_map_rgb(255, 255, 255));

    //Configura o título da janela
    al_set_window_title(window, "Arvore B");

    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(window);
        return -1;
    }

    if (!al_set_system_mouse_cursor(window, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(window);
        return -1;
    }

    //FIM DO CARREGAMENTO DAS BIBLIOTECAS NECESSARIAS DO ALLEGRO

    //Carrega as imagens dos botões
    background = al_load_bitmap("d://Calison//UNEB//Semestres//Nono//ED2//ArvoreB//Images//background.jpg");
    arvore = al_load_bitmap("d://Calison//UNEB//Semestres//Nono//ED2//ArvoreB//Images//arvore-grande.png");
    positivo = al_load_bitmap("d://Calison//UNEB//Semestres//Nono//ED2//ArvoreB//Images//positivo.png");
    negativo = al_load_bitmap("d://Calison//UNEB//Semestres//Nono//ED2//ArvoreB//Images//negativo.png");
    voltarImg = al_load_bitmap("d://Calison//UNEB//Semestres//Nono//ED2//ArvoreB//Images//voltar.png");
    font = al_load_font("d://Calison//UNEB//Semestres//Nono//ED2//ArvoreB//Fonts//Arial.ttf",25,0);

    queue_events = al_create_event_queue();
    if (!queue_events)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(window);
        return -1;

    }

    al_register_event_source(queue_events, al_get_mouse_event_source());

    al_register_event_source(queue_events, al_get_display_event_source(window));

    // Desenha os botões na tela
    al_draw_bitmap(background, 0, 0, 0);

    while(!sair){
        ALLEGRO_EVENT event;
        voltar = 0;

        al_draw_bitmap(background, 0, 0, 0);
        al_draw_bitmap(arvore, 150, 30, 0);
        al_draw_text(font, al_map_rgb(255,255,255), 385, 50, 0, "Criar");
        al_draw_text(font, al_map_rgb(255,255,255), 280, 110, 0, "Buscar");
        al_draw_text(font, al_map_rgb(255,255,255), 450, 110, 0, "Listagem");
        al_draw_text(font, al_map_rgb(255,255,255), 475, 200, 0, "Diferencial");
        al_draw_text(font, al_map_rgb(255,255,255), 210, 200, 0, "Remover");
        al_flip_display();

        al_wait_for_event(queue_events, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            //Escolhe qual algoritmo usar
            if(event.mouse.x >= 385 && event.mouse.x <= 440 && event.mouse.y >= 50 && event.mouse.y <= 80 ){
                choice = CRIAR;
            }else if(event.mouse.x >= 280 && event.mouse.x <= 360 && event.mouse.y >= 110 && event.mouse.y <= 140){
                 choice = BUSCAR;
            }else if(event.mouse.x >= 450 && event.mouse.x <= 550 && event.mouse.y >= 110 && event.mouse.y <= 140){
                 choice = LISTAGEM;
            }else if(event.mouse.x >= 475 && event.mouse.x <= 585 && event.mouse.y >= 200 && event.mouse.y <= 220){
                 choice = DIFERENCIAL;
            }else if(event.mouse.x >= 210 && event.mouse.x <= 310 && event.mouse.y >= 200 && event.mouse.y <= 220){
                 choice = REMOVER;
            }

        }

        if(choice > 0){
            switch(choice){
                case CRIAR:{
                    result = criarArvore();
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    al_draw_bitmap(background, 0, 0, 0);
                    al_draw_bitmap(voltarImg, 20, 10, 0);
                    while(!sair || !voltar){
                        al_wait_for_event(queue_events, &event);

                        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                            sair = 1;
                            break;
                        }

                        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                            if((event.mouse.x >= 20 && event.mouse.x <= 40) && (event.mouse.y >= 15 && event.mouse.y <= 30)){
                                // Caso clique em voltar, retorna para tela anterior
                                voltar = 1;
                                break;
                            }

                        }

                        if(result){
                           al_draw_bitmap(positivo, 150, 30, 0);
                        }else{
                           al_draw_bitmap(negativo, 150, 30, 0);
                        }
                        al_flip_display();
                    }
                    break;
                }
                case REMOVER:{
                    printf("REMOVENDO");
                    break;
                }
                case BUSCAR:{
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    al_draw_bitmap(background, 0, 0, 0);
                    al_draw_bitmap(arvore, 150, 30, 0);
                    al_draw_text(font, al_map_rgb(255,255,255), 270, 120, 0, "ID");
                    al_draw_text(font, al_map_rgb(255,255,255), 490, 120, 0, "Nome");
                    al_draw_bitmap(voltarImg, 20, 10, 0);
                    al_flip_display();

                    while(!sair || !voltar){
                        al_wait_for_event(queue_events, &event);

                        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                            sair = 1;
                            break;
                        }

                        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                            if(event.mouse.x >= 270 && event.mouse.x <= 290 && event.mouse.y >= 110 && event.mouse.y <= 140){
                                listChoice = BUSCARID;
                            }else if(event.mouse.x >= 490 && event.mouse.x <= 570 && event.mouse.y >= 110 && event.mouse.y <= 140){
                                listChoice = BUSCARNOME;
                            }else if((event.mouse.x >= 20 && event.mouse.x <= 40) && (event.mouse.y >= 15 && event.mouse.y <= 30)){
                                // Caso clique em voltar, retorna para tela anterior
                                voltar = 1;
                                break;
                            }
                        }

                        if(listChoice > 0){
                           start(listChoice);
                           listChoice = 0;
                        }
                    }

                    break;
                }
                case LISTAGEM:{
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    al_draw_bitmap(background, 0, 0, 0);
                    al_draw_bitmap(arvore, 150, 30, 0);
                    al_draw_text(font, al_map_rgb(255,255,255), 360, 50, 0, "Alfabetica");
                    al_draw_text(font, al_map_rgb(255,255,255), 260, 120, 0, "Letra/String");
                    al_draw_text(font, al_map_rgb(255,255,255), 470, 120, 0, "Telefone");
                    al_draw_bitmap(voltarImg, 20, 10, 0);
                    al_flip_display();
                    while(!sair || !voltar){
                        al_wait_for_event(queue_events, &event);

                        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                            sair = 1;
                            break;
                        }

                        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                            if(event.mouse.x >= 360 && event.mouse.x <= 470 && event.mouse.y >= 50 && event.mouse.y <= 80 ){
                                listChoice = ALFABETICA;
                            }else if(event.mouse.x >= 260 && event.mouse.x <= 390 && event.mouse.y >= 110 && event.mouse.y <= 140){
                                listChoice = LETRA;
                            }else if(event.mouse.x >= 470 && event.mouse.x <= 570 && event.mouse.y >= 110 && event.mouse.y <= 140){
                                listChoice = TELEFONE;
                            }else if((event.mouse.x >= 20 && event.mouse.x <= 40) && (event.mouse.y >= 15 && event.mouse.y <= 30)){
                                // Caso clique em voltar, retorna para tela anterior
                                voltar = 1;
                                break;
                            }
                        }

                        if(listChoice > 0){
                           start(listChoice);
                           listChoice = 0;
                        }
                    }

                    break;
                }
                case DIFERENCIAL:{
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    al_draw_bitmap(background, 0, 0, 0);
                    al_draw_bitmap(arvore, 150, 30, 0);
                    al_draw_text(font, al_map_rgb(255,255,255), 380, 50, 0, "Idade");
                    al_draw_text(font, al_map_rgb(255,255,255), 350, 130, 0, "Qualquer Data");
                    al_draw_text(font, al_map_rgb(255,255,255), 350, 200, 0, "Data Especifica");
                    al_draw_bitmap(voltarImg, 20, 10, 0);
                    al_flip_display();
                    while(!sair || !voltar ){
                        al_wait_for_event(queue_events, &event);


                        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                            sair = 1;
                            break;
                        }

                        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                            if(event.mouse.x >= 380 && event.mouse.x <= 440 && event.mouse.y >= 50 && event.mouse.y <= 80 ){
                                listChoice = IDADE;
                            }else if(event.mouse.x >= 350 && event.mouse.x <= 510 && event.mouse.y >= 130 && event.mouse.y <= 160){
                                listChoice = QUALQUER;
                            }else if(event.mouse.x >= 350 && event.mouse.x <= 510 && event.mouse.y >= 200 && event.mouse.y <= 230){
                                listChoice = ESPECIFICA;
                            }else if((event.mouse.x >= 20 && event.mouse.x <= 40) && (event.mouse.y >= 15 && event.mouse.y <= 30)){
                                // Caso clique em voltar, retorna para tela anterior
                                voltar = 1;
                                break;
                            }
                        }

                        if(listChoice > 0){
                           start(listChoice);
                           listChoice = 0;
                        }
                    }

                    break;
                }
            }
            choice = 0;
        }
    }
    return 1;
}

