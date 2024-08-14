#include "game.h"

Game::Game(std::size_t grid_width, std::size_t grid_height): 
        snake(grid_width, grid_height),
        engine(dev()),
        random_w(0, static_cast<int>(grid_width) - 1), 
        random_h(0, static_cast<int>(grid_height) - 1){}

void Game::PlaceFood(){
    int x = random_w(engine);
    int y = random_h(engine);
    
    while(snake.SnakeCell(x,y)){
        x = random_w(engine);
        y = random_h(engine); 
    }

    food.x = x;
    food.y = y;
}

void Game::Update(){

    if(!snake.alive){
        return;
    }
    snake.Update();
    if(static_cast<int>(snake.head_x) == food.x && static_cast<int>(snake.head_y) == food.y){
        PlaceFood();
        score += 1;
        snake.GrowBody();
        snake.speed += .05;
    }

}

void Game::Run(Controller const &controller, Renderer &renderer,
				std::size_t target_frame_duration){

    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    while (1)
    {
        frame_start = SDL_GetTicks();
        controller.HandleInput(running, snake);
        Update();
        renderer.Render(snake, food);

        frame_end = SDL_GetTicks();

        frame_count++;
        frame_duration = frame_end - frame_start;

        if (frame_end - title_timestamp >= 1000) {
        renderer.UpdateWindowTitle(score, frame_count);
        frame_count = 0;
        title_timestamp = frame_end;
        }

        if (frame_duration < target_frame_duration) {
        SDL_Delay(target_frame_duration - frame_duration);
        }
    }    
}

int Game::GetScore() const{
    return score;
}
int Game::GetSize() const{
    return snake.size;
}
