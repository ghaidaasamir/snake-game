#include "snake.h"

void Snake::Update(){
    SDL_Point prev_cell;
    prev_cell.x = head_x;
    prev_cell.y = head_y;
    UpdateHead();
    SDL_Point current_cell;
    current_cell.x = head_x;
    current_cell.y = head_y;
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
        UpdateBody(current_cell, prev_cell);
    }
}

void Snake::UpdateHead(){
    if(direction == Direction::kUp){
        head_y -= speed;
    }
    else if (direction == Direction::kDown)
    {
        head_y += speed;
    }
    else if (direction == Direction::kLeft)
    {
        head_x -= speed;
    }
    else if (direction == Direction::kRight)
    {
        head_x += speed;
    }

    if (head_x < 0) {
        head_x = grid_width - 1; 
    } else if (head_x >= grid_width) {
        head_x = 0;
    }

    if (head_y < 0) {
        head_y = grid_height - 1; 
    } else if (head_y >= grid_height) {
        head_y = 0;
    }

    // self-collision
    for (auto& item : body) {
        if (head_x == item.x && head_y == item.y) {
            alive = false;
        }
    }
}

void Snake::UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell){

    if (body.size() > 0) {
        for (size_t i = body.size() - 1; i > 0; --i) {
            body[i].x = body[i - 1].x;
            body[i].y = body[i - 1].y;
        }
    }
        
    if (body.size() > 0) {
        body[0].x = prev_cell.x;
        body[0].y = prev_cell.y;
    }

    if (growing) {
        body.push_back({prev_cell.x, prev_cell.y});
        growing = false;
    }

    for (auto& item : body) {
        if (current_cell.x == item.x && current_cell.y == item.y) {
            alive = false;
        }
    }
}

void Snake::GrowBody(){

    growing = true;

}

bool Snake::SnakeCell(int x, int y){
    for (auto& item : body) {
        if (x == item.x && y == item.y) {
            return true;
        }
    }
    return false;
}