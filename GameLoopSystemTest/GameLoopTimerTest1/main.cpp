#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes



 
int main(int argc, char **argv)
{
	const float FPS = 60;
	

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	bool redraw = true;
 
	al_init();
 
	timer = al_create_timer(1.0 / FPS);
   
 
	display = al_create_display(640, 480);
   
 
	al_install_keyboard();
	event_queue = al_create_event_queue();
   
	al_register_event_source(event_queue, al_get_keyboard_event_source()); 
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
 

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();


	int counter1 = 0;
	//int counter2 = 0;
	int framesps = 0;
	int framecounter = 0;
	//int framesconvertedtoseconds = 0;
	ALLEGRO_FONT * font30_;
	font30_ = al_load_font("arial.ttf", 30, 0);

	int totdrawings = 5000;
	bool up = false;
	bool down = false;

	al_start_timer(timer);

 
	while(1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
 
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{			
				case ALLEGRO_KEY_UP://choose later....
					 up = true;					
					break;
				case ALLEGRO_KEY_DOWN://choose later....
					down = true;					
					break;
			}
		}
		if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{			
				case ALLEGRO_KEY_UP://choose later....
					 up = false;					
					break;
				case ALLEGRO_KEY_DOWN://choose later....
					down = false;					
					break;
			}
		}



		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
 
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			if(down == true)
			{
				totdrawings = totdrawings - 10;	
			}
			if(up == true)
			{
				totdrawings = totdrawings + 10;	
			}
			
			//maybe the ev.timer.count is being converted to int and then being rounded up so sometimes this wont get entered so misdisplay fps//or maybe its just too fast ???
			
			if(ev.timer.count%60 == 0)//to show the framesdrawn based upon actual time
			{
				framesps = counter1;
				counter1 = 0;
			}



			for(int i = 0; i < totdrawings; i++)//my delay loop//change to a counter so i can test for different systems the number of draws..15000about 30fps
			{
				al_draw_filled_rectangle(i, i-10, i+10, i, al_map_rgb(i,i,i));
			}


			al_draw_textf(font30_, al_map_rgb(255,255,255), 100, 100, ALLEGRO_ALIGN_CENTRE, "%d" , framesps);//how many frames have been drawn
			al_draw_textf(font30_, al_map_rgb(255,255,255), 300, 100, ALLEGRO_ALIGN_CENTRE, "%d" , ev.timer.count/60);//this is the seconds pass in actual facts...
			al_draw_textf(font30_, al_map_rgb(255,255,255), 400, 100, ALLEGRO_ALIGN_CENTRE, "%d" , ev.timer.count%60);
			al_draw_textf(font30_, al_map_rgb(255,255,255), 500, 100, ALLEGRO_ALIGN_CENTRE, "%d" , totdrawings);


			redraw = false;
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
			
			counter1++;
		}
	}
 
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
 
	return 0;
}