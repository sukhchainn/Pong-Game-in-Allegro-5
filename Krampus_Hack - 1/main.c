#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>
#include "buttons.c"

#define MAXWIDTH 800
#define MAXHEIGHT 600
#define REC1Y 50
#define REC2Y 550

struct Paddle{
    int x1;
    int y1;
    int x2;
    int y2;
} pad1, pad2;

enum Direction{
    UP_RIGHT,
    DOWN_RIGHT,
    DOWN_LEFT,
    UP_LEFT
}Dir = UP_RIGHT;

typedef struct Paddle Paddle;

void MovePaddleUp(Paddle *ship);
void MovePaddleDown(Paddle *ship);

int x = 50, y = (MAXHEIGHT/2);

enum KEYS{UP, DOWN, W, S, SPACE};
bool keys[5] = {false, false, false, false, false};


int main()
{
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();

    int font_size = 30, player1 = 0, player2 = 0;
    bool done=false, d_text=false, menu=true;
    pad1.x1 = 45;   pad2.x1 = 745;
    pad1.y1 = 200;  pad2.y1 = 200;
    pad1.x2 = 50;   pad2.x2 = 750;
    pad1.y2 = 400;  pad2.y2 = 400;


    ALLEGRO_DISPLAY *display = al_create_display(MAXWIDTH, MAXHEIGHT);
    ALLEGRO_EVENT_QUEUE *ev_queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0/60.0);
    ALLEGRO_COLOR acolor = al_map_rgb(204, 102, 153);
    ALLEGRO_COLOR bcolor = al_map_rgb(0, 255, 0);
    ALLEGRO_COLOR ccolor = al_map_rgb(191, 255, 0);
    //ALLEGRO_COLOR player = al_map_rgb(0, 0, 0);
    ALLEGRO_FONT *font1 = al_load_font("Code.ttf", 30, 1);
    ALLEGRO_FONT *font2 = al_load_font("GoodDog.otf", font_size, 1);

    al_register_event_source(ev_queue, al_get_display_event_source(display));
    al_register_event_source(ev_queue, al_get_timer_event_source(timer));
    al_register_event_source(ev_queue, al_get_mouse_event_source());
    al_register_event_source(ev_queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();
    al_start_timer(timer);

    while(!done)
    {
        ALLEGRO_EVENT event;
        al_draw_filled_rectangle(0, 0, 800, 50, bcolor);
        al_draw_filled_rectangle(0, 550, 800, 600, bcolor);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;

        al_draw_filled_rounded_rectangle(pad1.x1, pad1.y1, pad1.x2, pad1.y2, 3, 3, acolor);
        al_draw_filled_rounded_rectangle(pad2.x1, pad2.y1, pad2.x2, pad2.y2, 3, 3, acolor);

        if(menu == true)
        {
        button(100, 50, 400, 300, ccolor, 2, bcolor, font_size, "START", font1, al_map_rgb(0, 153, 0), event, &menu, 0);
        }
        else
        {
            if(player1 == 10)
            {
                al_draw_textf(font1, al_map_rgb(13, 40, 100),400, MAXHEIGHT/2, 1, "\n Player 1 has Won with %d points \n", player1);
            }
            else if(player2 == 10)
            {
                al_draw_textf(font1, al_map_rgb(13, 40, 100),400, MAXHEIGHT/2, 1, "\n Player 2 has Won with %d points \n", player1);
            }

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
         //REC1
            if(y <= REC1Y && Dir == UP_RIGHT)
            {
                Dir = DOWN_RIGHT;
            }
            else if(y <= REC1Y && Dir == UP_LEFT)
            {
                Dir = DOWN_LEFT;
            }
        //RIGHT WALL
            else if(x >= MAXWIDTH && Dir == DOWN_RIGHT)
            {
                Dir = DOWN_LEFT;
                player1 += 1;
            }
            else if(x >= MAXWIDTH && Dir == UP_RIGHT)
            {
                Dir = UP_LEFT;
                player1 += 1;
            }
        //REC2
            else if(y >= REC2Y && Dir == DOWN_LEFT)
            {
                Dir = UP_LEFT;
            }
            else if(y >= REC2Y && Dir == DOWN_RIGHT)
            {
                Dir = UP_RIGHT;
            }

        //LEFT WALL
            else if(x <= 0 && Dir == UP_LEFT)
            {
                Dir = UP_RIGHT;
                player2 += 1;
            }
            else if(x <= 0 && Dir == DOWN_LEFT)
            {
                Dir = DOWN_RIGHT;
                player2 += 1;
            }

        //Pad1
            if(x >= pad1.x1 && x <= pad1.x2 &&
               y >= pad1.y1 && y <= pad1.y2 && Dir == UP_LEFT)
            {
                Dir = UP_RIGHT;
            }
            if(x >= pad1.x1 && x <= pad1.x2 &&
               y >= pad1.y1 && y <= pad1.y2 && Dir == DOWN_LEFT)
            {
                Dir = DOWN_RIGHT;
            }

        //Pad2
            if(x >= pad2.x1 && x <= pad2.x2 &&
               y >= pad2.y1 && y <= pad2.y2 && Dir == UP_RIGHT)
            {
                Dir = UP_LEFT;
            }
            if(x >= pad2.x1 && x <= pad2.x2 &&
               y >= pad2.y1 && y <= pad2.y2 && Dir == DOWN_RIGHT)
            {
                Dir = DOWN_LEFT;
            }

        //if(event.type == ALLEGRO_EVENT_TIMER)


        //Ball
            if(Dir == UP_RIGHT){
                x += 8;
                y -= 3;
            }
            else if(Dir == DOWN_RIGHT){
                x += 8;
                y += 3;
            }
            else if(Dir == DOWN_LEFT){
                x -= 8;
                y += 3;
            }
            else if(Dir == UP_LEFT){
                x -= 8;
                y -= 3;
            }
        }

        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(event.keyboard.keycode)
			{
			    case ALLEGRO_KEY_R
                    :main();
                    break;
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_W:
					MovePaddleUp(&pad1);
					keys[W] = true;
					break;
				case ALLEGRO_KEY_S:
					MovePaddleDown(&pad1);
					keys[S] = true;
					break;
                case ALLEGRO_KEY_UP:
                    MovePaddleUp(&pad2);
					keys[UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
                    MovePaddleDown(&pad2);
					keys[DOWN] = true;
					break;
			}
        }

        if(event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(event.keyboard.keycode)
			{
			    case ALLEGRO_KEY_W:
					keys[W] = false;
					break;
				case ALLEGRO_KEY_S:
					keys[S] = false;
					break;
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
			}
		}
            if(keys[UP])
            {
                MovePaddleUp(&pad2);
            }
            else if(keys[DOWN])
            {
                MovePaddleDown(&pad2);
            }
            if(keys[W])
            {
                MovePaddleUp(&pad1);
            }
            else if(keys[S])
            {
                MovePaddleDown(&pad1);
            }

        al_draw_filled_circle(x, y, 8, al_map_rgb(0, 0, 0));
        al_draw_textf(font1, al_map_rgb(13, 40, 100),400, 15, 1, "%d : %d", player1, player2);
        }
        al_flip_display();
        if(al_is_event_queue_empty(ev_queue));
        al_wait_for_event(ev_queue, &event);
        al_rest(0.005);
        al_clear_to_color(al_map_rgb(255, 255, 255));

   }

    al_destroy_display(display);
    al_uninstall_keyboard();
    al_uninstall_mouse();
    return 0;
}

void MovePaddleUp(Paddle *ship)
{
	if(!(ship->y1 < REC1Y)){
	ship->y1 -= 5;
	ship->y2 -= 5;
	}
}
void MovePaddleDown(Paddle *ship)
{
	if(!(ship->y2 > REC2Y)){
	ship->y1 += 5;
	ship->y2 += 5;
	}
}
