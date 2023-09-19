#pragma once
#include <iostream>
#include <string>

//Window config
#define GAME_NAME "Space Invaders"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 920
#define HALF_SCREEN_WIDTH SCREEN_WIDTH / 2
#define HALF_SCREEN_HEIGHT SCREEN_HEIGHT / 2

//Game config
#define SHIP_WIDTH 40
#define SHIP_HEIGHT 40
#define BULLET_WIDTH 6
#define BULLET_HEIGHT 20
#define ENEMY_RED_WIDTH 40
#define ENEMY_RED_HEIGHT 40
#define ENEMY_BLUE_WIDTH 35
#define ENEMY_BLUE_HEIGHT 35
#define ENEMY_GREEN_WIDTH 30
#define ENEMY_GREEN_HEIGHT 30
#define ENEMY_UFO_WIDTH 50
#define ENEMY_UFO_HEIGHT 50
#define MOVE_DOWN_DISTANCE 50
#define ENEMY_GAP_WIDTH 60
#define ENEMY_GAP_HEIGHT 50

//UI config
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 40
#define TEXT_SIZE 24
#define SCREEN_OFFSET 100

//File path
//UI texture
#define DEFAULT_FONT "font/OpenSans-Bold.ttf"
#define GAME_FONT "font/gomarice_game_continue_02.ttf"
#define VOLUMN_BAR "texture/volumn_color.png"
#define VOLUMN_BAR_EMPTY "texture/volumn_empty.png"
#define VOLUMN_SLIDER "texture/volumn_slider.png"
#define BUTTON_EMPTY "texture/button_empty.png"
#define LOGO_TEXTURE "texture/logo_splash_screen.png"
//game texture
#define SHIP_TEXTURE "texture/ship.png"
#define BULLET_TEXTURE "texture/bullet_sprite.png"
#define RED_ENEMY_TEXTURE "texture/red_enemy_sprite.png"
#define BLUE_ENEMY_TEXTURE "texture/blue_enemy_sprite.png"
#define GREEN_ENEMY_TEXTURE "texture/green_enemy_sprite.png"
#define BACKGROUND "texture/background.jpg"
#define EXPLOSION_TEXTURE "texture/explosion.png"

//sound
#define UI_CLICK "sound/UI_click.wav"
#define PLAYER_DIE "sound/explosion.wav"
#define ENEMY_DIE "sound/invaderkilled.wav"
#define SHOOT_SOUND "sound/shoot.wav"
