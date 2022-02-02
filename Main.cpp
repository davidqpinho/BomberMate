#include "Main.h"
#include "Engine/ScenesRouter.h"
#include "Scenes/Menu.h"

//find . -name '*.h' | xargs wc -l | sort -nr
//g++ Main.cpp -o BomberMate $(pkg-config allegro-5 allegro_image-5 --libs --cflags)
//g++ Main.cpp Engine/*.cpp Scenes/*.cpp Components/*.cpp Stages/*.cpp Utils/*.cpp -o BomberMate $(pkg-config allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 --libs --cflags)
//g++ Main.cpp Engine/*.cpp Scenes/*.cpp -o BomberMate $(pkg-config allegro-5 allegro_image-5 --libs --cflags)
//g++ Main.cpp TestClass/*.cpp -o BomberMate $(pkg-config allegro-5 allegro_image-5 --libs --cflags)
//g++ Main.cpp Engine/*.cpp TestClass/*.cpp -o BomberMate $(pkg-config allegro-5 allegro_image-5 --libs --cflags)
//g++ Main.cpp Engine/*.cpp Scenes/*.cpp -o hello -lallegro -lallegro_font -lallegro_ttf -lallegro_image

int init( ALLEGRO_DISPLAY ** display, ALLEGRO_EVENT * event, ALLEGRO_EVENT_QUEUE ** queue, SceneRouter ** router, ALLEGRO_TIMER ** timer);
void destroy(ALLEGRO_DISPLAY ** display, SceneRouter ** router, ALLEGRO_TIMER ** timer);

int main()
{   
    
    ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE keyState;
    ALLEGRO_TIMER * timer;
    SceneRouter * router;
    
    
    bool running = true;
    
    if(!init( &display, &event, &queue, &router, &timer)) 
    {
        fprintf(stderr, "Fail to initialize Game\n");
        return -1;
    }  
    
    while(running){

        if (!al_is_event_queue_empty(queue)) {
    	
            al_wait_for_event(queue, &(event));        
            
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            return false;
            
            if(event.type == ALLEGRO_EVENT_TIMER){
                router->ProcessScene();             
                running = router->ProcessEvent(&event, &queue);
            }
        }        
    }  
    
    destroy(&display, &router, &timer);  
    return 0;    
}

int init( 
    ALLEGRO_DISPLAY ** display, 
    ALLEGRO_EVENT * event, 
    ALLEGRO_EVENT_QUEUE ** queue, 
    SceneRouter ** router, 
    ALLEGRO_TIMER ** timer
){
    
    if (!al_init())
    {
        fprintf(stderr, "Fail to initialize allegro 5\n");
        return -1;
    }
 
    *display = al_create_display(ScreenWidth, ScreenHeigth);
    if (!*display)
    {
        fprintf(stderr, "Fail to initialize display\n");
        return -1;
    }

    *queue = al_create_event_queue();
    if (!*queue)
    {
        fprintf(stderr, "Fail to initialize event queue\n");
        return -1;
    }

    *timer = al_create_timer(1.0/FPS);
    if (!*timer)
    {
        fprintf(stderr, "Fail to initialize timer\n");
        return -1;
    }

	al_install_keyboard();
	al_install_mouse();

	al_register_event_source(*queue, al_get_keyboard_event_source());
	al_register_event_source(*queue, al_get_display_event_source(*display));
	al_register_event_source(*queue, al_get_mouse_event_source());
    al_register_event_source(*queue, al_get_timer_event_source(*timer));

	al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    
    * router =  new SceneRouter(new Menu());

    al_start_timer(*timer);

    return 1;
}

void destroy(ALLEGRO_DISPLAY ** display, SceneRouter ** router, ALLEGRO_TIMER ** timer){
    
    delete * router;
    al_destroy_display(*display);
    al_destroy_timer(* timer);
	al_uninstall_keyboard();
	al_uninstall_mouse();
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
}

