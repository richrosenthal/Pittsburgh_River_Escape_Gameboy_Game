/*Author Richard Rosenthal Jr. This is for GBJAM7! Date: 8-22-2019. This is my first attempt at creating a gameboy game.
The object of the game is to avoid colliding with a boat that is chasing you. Everytime the boat goes off screen the speed of the game will get faster
Most of this is learn from tutorials, so I apologize for sloppy code. I'm still learning C and GBDK */



#include <gb/gb.h>
#include <stdio.h>
#include "pittsburghtiles.c"
#include "pittsburghwaterfront.c"
#include <gb/font.h>
#include "windowmap.c"
#include "GameCharacter.c"
#include "GameSprites.c"



struct GameCharacter ship;
struct GameCharacter badShip;
UBYTE spritesize = 8;



void movegamecharacter(struct GameCharacter* character, UINT8 x, UINT8 y){
        move_sprite(character->spriteids[0], x, y);
        move_sprite(character->spriteids[1], x + spritesize, y);
        move_sprite(character->spriteids[2], x, y + spritesize);
        move_sprite(character->spriteids[3], x + spritesize, y + spritesize);

}

UBYTE checkcollisions(struct GameCharacter* one, struct GameCharacter* two){
  return  (one->x >= two->x && one->x <= two->x + two->width) && (one->y >= two->y && one->y <= two->y + two->height) || (two->x >= one->x && two->x <= one->x + one->width) && (two->y >= one->y && two->y <= one->y + one->height);

}

void setupship(){
    ship.x = 80;
    ship.y = 130;
    ship.width = 16;
    ship.height = 16;

    // load sprites for ship
    set_sprite_tile(0, 0);
    ship.spriteids[0] = 0;
    set_sprite_tile(1, 1);
    ship.spriteids[1] = 2;
    set_sprite_tile(2, 2);
    ship.spriteids[2] = 1;
    set_sprite_tile(3, 3);
    ship.spriteids[3] = 3;
 
     movegamecharacter(&ship, ship.x, ship.y);

}

void setupbadShip(){
    badShip.x = 10;
    badShip.y = 130;
    badShip.width = 16;
    badShip.height = 16;

    // load sprites for badShip
    set_sprite_tile(4,4);
    badShip.spriteids[0] = 4;
    set_sprite_tile(5,5);
    badShip.spriteids[1] = 6;
    set_sprite_tile(6,6);
    badShip.spriteids[2] = 5;
    set_sprite_tile(7,7);
    badShip.spriteids[3] = 7;

    movegamecharacter(&badShip, badShip.x, badShip.y);

    
}




void main(){

    

    UINT8 speed = 125;
    UINT8 score = 1;
    set_bkg_data(0,28,pittsburghtiles); //(27,22, pittsburgh)
    set_bkg_tiles(0,0,40,18, pittsburghwaterfront);
    set_sprite_data(0, 8, GameSprites);
    setupship();
    setupbadShip();
    
     NR52_REG = 0x80; 
     NR50_REG = 0x77; 
     NR51_REG = 0xFF; 

    

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
   

  
     while(!checkcollisions(&ship, &badShip)){
        scroll_bkg(1,0);
        if(joypad() & J_DOWN){
             ship.y += 1;
             movegamecharacter(&ship, ship.x, ship.y);
        }
        if(joypad() & J_UP){
             ship.y -= 1;
             movegamecharacter(&ship, ship.x, ship.y);
        }   


        if(joypad() & J_LEFT){
            ship.x -= 2;
            movegamecharacter(&ship, ship.x, ship.y);
        }
        if(joypad() & J_RIGHT){
            ship.x += 2;
            movegamecharacter(&ship, ship.x, ship.y);
        }

        badShip.x += 3;
         if(badShip.x >= 144){
             badShip.x = 0;
             ship.y = 139;
             badShip.y = ship.y;
             speed -=2;
         }
         
        
        movegamecharacter(&badShip, badShip.x, badShip.y);
        movegamecharacter(&ship, ship.x, ship.y);
       
        delay(speed);
        score += 1;
        if(speed <= 6){
             speed = 10;
        }
    }
            NR10_REG = 0x16;
            NR11_REG = 0x40;
            NR12_REG = 0x73;
            NR13_REG = 0x00;
            NR14_REG = 0xC3;
    
    
    printf("\n \n \n === You Sunk ===\n");
    
    delay(100);
    printf("The End!");
}



 
   

