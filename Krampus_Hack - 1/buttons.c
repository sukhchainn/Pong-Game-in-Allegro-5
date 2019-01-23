/*
#include "buttons.h"
*/
int button(int width, int height, int place_x, int place_y, ALLEGRO_COLOR colorU, float boundry, ALLEGRO_COLOR boundry_color, int font_size, char* text, ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, ALLEGRO_EVENT event, bool *var, int value)
{
    al_draw_filled_rectangle(place_x-(width/2), place_y-(height/2), place_x+(width/2), place_y+(height/2), colorU);
    al_draw_rectangle(place_x-(width/2), place_y-(height/2), place_x+(width/2), place_y+(height/2), boundry_color, boundry);
    al_draw_text(font, font_color, place_x, place_y-(font_size/2), 1, text);

    if(event.mouse.x >= (place_x-(width/2)) && event.mouse.x <= (place_x+(width/2)) && event.mouse.y >= (place_y-(height/2)) && event.mouse.y <= (place_y+(height/2)) && event.mouse.button & 1)
        *var = value;

    return 0;
}

int bool_button(int width, int height, int place_x, int place_y, ALLEGRO_COLOR colorU, float boundry, ALLEGRO_COLOR boundry_color, int font_size, char* text, ALLEGRO_FONT *font, ALLEGRO_COLOR font_color, ALLEGRO_EVENT event, bool *var)
{
    al_draw_filled_rectangle(place_x-(width/2), place_y-(height/2), place_x+(width/2), place_y+(height/2), colorU);
    al_draw_rectangle(place_x-(width/2), place_y-(height/2), place_x+(width/2), place_y+(height/2), boundry_color, boundry);
    al_draw_text(font, font_color, place_x, place_y-(font_size/2), 1, text);

    if(event.mouse.x >= (place_x-(width/2)) && event.mouse.x <= (place_x+(width/2)) && event.mouse.y >= (place_y-(height/2)) && event.mouse.y <= (place_y+(height/2)) && event.mouse.button & 1 && event.type ==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        *var = !*var;

    return 0;
}
/*
int input_feild(int x1, int y1, int x2, int y2, ALLEGRO_COLOR colorU, float boundry, ALLEGRO_COLOR boundry_color, ALLEGRO_FONT *font, ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE *ev_queue)
{
    int x=0;
    al_draw_filled_rounded_rectangle(x1, y1, x2, y2, 10, 10, colorU);
    al_draw_rounded_rectangle(x1, y1, x2, y2, 10, 10, boundry_color, boundry);

    if(event.mouse.x >= x1 && event.mouse.x <= x2 && event.mouse.y >= y1 && event.mouse.y <= y2 && event.mouse.button & 1 && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        char* str1, str2;
        int p=0;
        while(1)
        {
            al_draw_text(font, al_map_rgb(0, 153, 0), x1+5+x, y1+5, 1, "|");
            al_wait_for_event(ev_queue, &event);
            str1[p] = 'a' + event.keyboard.keycode - 1;
            ++p;
            al_draw_text(font, al_map_rgb(0, 153, 0), x1+10+x, y1+5, 1, str1);
            x+5;
            //printf("%s", str1);
            if(event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                break;
            }
            al_flip_display();

        }
    }
    return 0;
}
*/
bool menu_icon(int width, int height, int place_x, int place_y, ALLEGRO_COLOR colorU, ALLEGRO_COLOR bg_color, ALLEGRO_EVENT event, bool *var)
{
    al_draw_line(place_x-(width/2)+width/4, place_y-(height/2)+height/3 , place_x-(width/2)+width-(width/4), place_y-(height/2)+height/3, colorU, 5);
    al_draw_line(place_x-(width/2)+width/4, place_y-(height/2)+(height/2) , place_x-(width/2)+width-(width/4), place_y-(height/2)+(height/2), colorU, 5);
    al_draw_line(place_x-(width/2)+width/4, place_y-(height/2)+height-(height/3), place_x-(width/2)+width-(width/4), place_y-(height/2)+height-(height/3), colorU, 5);
    if(event.mouse.x >= (place_x-(width/2)) && event.mouse.x <= (place_x+(width/2)) && event.mouse.y >= (place_y-(height/2)) && event.mouse.y <= (place_y+(height/2)) && event.mouse.button & 1 && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        *var = !*var;
        return 0;
}
