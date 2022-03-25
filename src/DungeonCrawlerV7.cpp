#include <iostream>
#include <limits>
#include <cmath>
#include <ctime>
#include <windows.h>

int pythag(int x1, int x2, int y1, int y2)
{
    return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

double pythag_dbl(int x1, int x2, int y1, int y2)
{
    return sqrt(pow(double(x2)-double(x1),2) + pow(double(y2)-double(y1),2));
}

int open_chest()
{
    char chest_response;
    int open = 0;
    std::cout << std::endl << std::endl;
    std::cout << "You have found a chest, would you like to open it?" << std::endl << "Y/N: ";
    std::cin >> chest_response;
    std::cout << std::endl;
    switch(chest_response){
        case 'Y':
        case 'y':
            std::cout << "You open the chest." << std::endl;
            open = 1;
            break;
        case 'N':
        case 'n':
            std::cout << "You don't open the chest." << std::endl;
            break;
        /*case 'E':
            std::cout << "Standard entry found, error in entry" << std::endl;
            break;*/
        default:
            std::cout << "That wasn't an option. You've wasted your turn." << std::endl;
            Sleep(1500);
            break;
    }
    return open;
}

int inventory(int flash_num, int rock_num)
{
    char inv_response;
    int in_inv = 1;
    int return_val = 0;
    while(in_inv == 1){
        int pick_flash = 0, pick_rock = 0;
        system("cls");
        std::cout << "     Player Inventory     " << std::endl << std::endl;
        int item_number = 0;
        if(flash_num > 0){
            item_number++;
            std::cout << item_number << ". Flash Bang";
            if(flash_num > 1){
                std::cout << " x" << flash_num;
            }
            std::cout << std::endl;
            pick_flash = item_number;
        }
        if(rock_num > 0){
            item_number++;
            std::cout << item_number << ". Rock";
            if(rock_num > 1){
                std::cout << " x" << rock_num;
            }
            std::cout << std::endl;
            pick_rock = item_number;
        }
        if(item_number == 0){
            std::cout << "There's nothing here." << std::endl;
        }
        std::cout << std::endl << "Pick a number to choose an item, or press 'e' to leave." << std::endl;
        std::cin.clear();
        std::cin >> inv_response;
        std::cout << std::endl;
        switch(inv_response){
            case '1':{
                if(pick_flash == 1){
                    std::cout << "You use a flash bang!" << std::endl;
                    flash_num = flash_num - 1;
                    Sleep(1000);
                    in_inv = 0;
                    return_val = 1;
                }
                else if(pick_rock == 1){
                    std::cout << "You look at a rock." << std::endl;
                    Sleep(1000);
                    std::cout << "It is very rocky." << std::endl;
                    Sleep(2000);
                    in_inv = 0;
                }
                if(pick_flash == 0 && pick_rock == 0){
                    std::cout << "Not a valid entry." << std::endl;
                    Sleep(1000);
                }
                break;
            }
            case '2':{
                if(pick_rock == 2){
                    std::cout << "You look at a rock." << std::endl;
                    Sleep(1000);
                    std::cout << "It is very rocky." << std::endl;
                    Sleep(2000);
                    in_inv = 0;
                }
                else{
                    std::cout << "Not a valid entry." << std::endl;
                    Sleep(1000);
                }
                break;
            }
            case 'e':{
                in_inv = 0;
                std::cout << "You exit your inventory." << std::endl;
                Sleep(500);
                break;
            }
            default:{
                std::cout << "Not a valid entry." << std::endl;
                Sleep(1000);
                break;
            }
        }
    }
    return return_val;
}

int main()
{
    system("cls");
    srand((unsigned) time(0));
    int game = 1, game_start = 1;
    int grid_size = 5;
    const int map_height = 17, map_width = 17; //Changing these would be a bad idea
    int player_in_grid_y = 0, player_in_grid_x = 0;
    int middle_square = grid_size/2;

    while(game==1){
        system("cls");
        int gridmap[grid_size][grid_size];
        int gamemap[grid_size*map_height][grid_size*map_width];
        int gamemap_seen[grid_size*map_height][grid_size*map_width];
        for(int i = 0; i < grid_size; i++){
            for(int k = 0; k < grid_size; k++){
                gridmap[i][k] = rand()%10 + 1;
            }
        }
        gridmap[middle_square][middle_square] = 0;
        for(int i = 0; i < grid_size*map_height; i++){
            for(int k = 0; k < grid_size*map_width; k++){
                gamemap_seen[i][k] = -1;
            }
        }
        /*for(int i = 0; i < grid_size; i++){
            for(int k = 0; k < grid_size; k++){
                std::cout << " " << gridmap[i][k] << " ";
            }
            std::cout << std::endl;
        }*/
        while(game_start==1){
            for(int a = 0; a < grid_size; a++){
                for(int b = 0; b < grid_size; b++){
                    for(int i = 0; i < map_height; i++){
                        for(int k = 0; k < map_width; k++){
                            if(i == 0 || k ==0 || i == (map_height - 1) || k == (map_width - 1)){
                                gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                            }
                            else{
                                gamemap[(a*map_height)+i][(b*map_width)+k] = 0;
                            }
                            if(i == 8 && k == 0){
                                gamemap[(a*map_height)+i][(b*map_width)+k] = 0;
                            }
                            if(i == 8 && k == (map_width-1)){
                                gamemap[(a*map_height)+i][(b*map_width)+k] = 0;
                            }
                            if(i == 0 && k == 8){
                                gamemap[(a*map_height)+i][(b*map_width)+k] = 0;
                            }
                            if(i == (map_height-1) && k == 8){
                                gamemap[(a*map_height)+i][(b*map_width)+k] = 0;
                            }
                        }
                    }
                    if(gridmap[a][b] == 0){ //Default square
                        for(int i = 0; i < map_height; i++){
                            for(int k = 0; k < map_width; k++){
                                if((i == 1 || i == 15) && ((k > 2 && k < 8) || (k > 8 && k < 14))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 1 || k == 15) && ((i > 2 && i < 8) || (i > 8 && i < 14))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 4 || i == 12) && (k > 3 && k < 13)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i > 5 && i < 11) && (k == 4 || k == 5 || k == 11 || k == 12)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                            }
                        }
                    }
                    if(gridmap[a][b] == 1){ //Transit square
                        for(int i = 0; i < map_height; i++){
                            for(int k = 0; k < map_width; k++){
                                if((i == 3 || i == 4) && k > 2 && k < 14){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 3 || k == 4) && i > 4 && i < 14){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 12 || k == 13) && i > 4 && i < 14){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 12 || i == 13) && k > 5 && k < 12){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 6 || i == 7) && k > 8 && k < 12){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 9 || i == 10) && k > 4 && k < 11){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 6 || k == 7) && i > 5 && i < 9){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                            }
                        }
                    }
                    if(gridmap[a][b] == 2){ //Maze square 1
                        for(int i = 0; i < map_height; i++){
                            for(int k = 0; k < map_width; k++){
                                if(i == 1 && (k == 5 || k == 12)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 2 && (k == 2 || k == 3 || k == 4 || k == 5 || k == 7 || k == 8 || k == 9 || k == 10 || k == 12 || k == 13 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 3 && (k == 2 || k == 5 || k == 10)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 4 && (k == 2 || k == 4 || k == 5 || k == 6 || k == 7 || k == 8 || k == 10 || k == 11 || k == 12 || k == 13 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 5 && (k == 5 || k == 12)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 6 && (k == 2 || k == 3 || k == 5 || k == 7 || k == 8 || k == 10 || k == 12 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 7 && (k == 2 || k == 5 || k == 7 || k == 10 || k == 12 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 8 && (k == 2 || k == 3 || k == 7 || k == 9 || k == 10 || k == 12 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 9 && (k == 5 || k == 7 || k == 12 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 10 && (k == 2 || k == 4 || k == 5 || k == 7 || k == 8 || k == 10 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 11 && (k == 2 || k == 10 || k == 12 || k == 13 || k == 14 || k == 15)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 12 && (k == 1 || k == 2 || k == 3 || k == 5 || k == 7 || k == 8 || k == 9 || k == 10)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 13 && (k == 5 || k == 12 || k == 13 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 14 && (k == 1 || k == 2 || k == 3 || k == 5 || k == 6 || k == 7 || k == 9 || k == 10 || k == 12 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 15 && (k == 9 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                            }
                        } 
                    }
                    if(gridmap[a][b] == 3){ //Four rooms 1
                        for(int i = 0; i < map_height; i++){
                            for(int k = 0; k < map_width; k++){
                                if((i == 6 || i == 7) && ((k > 0 && k < 5) || (k > 10 && k < 15))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 9 || i == 10) && ((k > 0 && k < 8) || (k > 11 && k < 16))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 6 || k == 7) && ((i > 0 && i < 8) || (i > 8 && i < 13) || (i > 13 && i < 16))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 9 || k == 10) && ((i > 0 && i < 8) || (i > 8 && i < 16))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                            }
                        }
                    }
                    if(gridmap[a][b] == 4){ //Temple 1
                        for(int i = 0; i < map_height; i++){
                            for(int k = 0; k < map_width; k++){
                                if((k == 7 || k == 9) && ((i > 1 && i < 6) || (i > 10 && i < 15))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 6 || k == 10) && (i == 5 || i == 11)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 5 || i == 6 || i == 7 || i == 9 || i == 10 || i == 11) && ((k > 1 && k < 6)|| (k > 10 && k < 15))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                            }
                        }
                    }
                    if(gridmap[a][b] == 5){ //Double dead end 1
                        for(int i = 0; i < map_height; i++){
                            for(int k = 0; k < map_width; k++){
                                if((i == 6 || i == 7 || i == 9 || i == 10) && (k > 0 && k < 5)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 6 || k == 7 || k == 9 || k == 10) && (i > 11 && i < 16)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 8 && (k == 3 || k == 4 || k == 6 || k == 11 || k == 13)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(k == 8 && (i == 12 || i == 13)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 10 && (k == 5 || k == 6)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 9 || i == 10) && (k > 7 && k < 16)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 6 || k == 7) && (i > 0 && i < 8)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 2 && (k == 8 || k == 9 || (k > 10 && k < 15))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 3 && (k == 9 || k == 11)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 4 && (k == 13 || k == 15)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 5 && (k == 9 || k == 10 || k == 11 || k == 13 || k == 15)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 6 && (k == 9 || k == 13)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 7 && (k == 8 || k == 9 || k == 11 || k == 13 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                            }
                        }
                    }
                    if(gridmap[a][b] == 6){ //Split room, top left to bottom right
                        for(int i = 0; i < map_height; i++){
                            for(int k = 0; k < map_width; k++){
                                if((i == 13 || i == 14) && (k == 1 || k == 15 || (k > 2 && k < 8) || (k > 8 && k < 14))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 11 || i == 12) && ((k > 0 && k < 5) || (k > 11 && k < 16) || k == 6 || k == 7 || k == 9 || k == 10)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 9 && k != 8){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 8 && k == 11){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 1 && (k == 2 || k == 3 || k == 4 || k == 5 || k == 11)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 2 && (k == 4 || k == 5 || (k > 6 && k < 10) || (k > 10 && k < 15))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 3 && (k == 1 || k == 2 || k == 4 || k == 5 || k == 7 || k == 9 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 4 && (k == 4 || k == 5 || k == 11 || k == 12 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 5 && (k > 1 && k < 12)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 6 && (k == 4 || k == 5 || k == 11 || k == 13 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 7 && (k == 1 || k == 2 || k == 4 || k == 5 || k == 11 || k == 13 || k == 14)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                            }
                        }
                    }
                    if(gridmap[a][b] == 7){ //Empty Room, four slots in middle
                        for(int i = 0; i < map_height; i++){
                            for(int k = 0; k < map_width; k++){
                                if((i == 4 || i == 5 || i == 6 || i == 10 || i == 11 || i == 12) && ((k > 3 && k < 8) || (k > 8 && k < 13))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 7 || i == 9) && (k > 3 && k < 13)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 8 && k > 7 && k < 9){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                            }
                        }
                    }
                    if(gridmap[a][b] == 8){ //Split room, bottom left to top right
                        for(int i = 0; i < map_height; i++){
                            for(int k = 0; k < map_width; k++){
                                if((i == 1 && k > 0 && k < 8) || (k == 1 && i > 0 && i < 8)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 9 || i == 10) && (k > 0 && k < 5)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 9 || k == 10) && (i > 0 && i < 4)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 6 || i == 7 || i == 8) && (k == 4 || k == 5)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 4 || i == 5) && (k > 3 && k < 16 && k != 13)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 13 || k == 14) && (i > 6 && i < 15 && i != 10)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 13 || i == 14) && (k == 9 || k == 10 || k == 11)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 6 || k == 7) && (i > 10 && i < 16)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 7 && (k > 5 && k < 12 && k != 8)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 9 && (k > 4 && k < 12 && k != 8)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(i == 11 && k > 8 && k < 12){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if(k == 11 && (i == 6 || i == 10)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                            }
                        }
                    }
                    if(gridmap[a][b] == 9){ //Four rooms 2
                        for(int i = 0; i < map_height; i++){
                            for(int k = 0; k < map_width; k++){
                                if((i == 6 || i == 7) && k != 8){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 9 || i == 10) && k != 1 && k != 8 && k != 11){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 6 || k == 7 || k == 9 || k == 10) && i != 1 && i != 8){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                            }
                        }
                    }
                    if(gridmap[a][b] == 10){ //Temple 2
                        for(int i = 0; i < map_height; i++){
                            for(int k = 0; k < map_width; k++){
                                if((i == 1 || i == 15) && k > 2 && k < 14 && k != 8){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 2 || i == 14) && k > 5 && k < 11 && k != 8){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 3 || i == 4 || i == 13 || i == 12) && (k == 7 || k == 9)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 1 || k == 15) && i > 2 && i < 14 && i != 8){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 2 || k == 14) && i > 5 && i < 11 && i != 8){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((k == 3 || k == 4 || k == 13 || k == 12) && (i == 7 || i == 9)){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                                if((i == 4 && (k == 4 || k == 12)) || (i == 5 && (k == 5 || k == 11)) || (i == 7 && (k == 7 || k == 9)) || (i == 12 && (k == 4 || k == 12)) || (i == 11 && (k == 5 || k == 11)) || (i == 9 && (k == 7 || k == 9))){
                                    gamemap[(a*map_height)+i][(b*map_width)+k] = 1;
                                }
                            }
                        }
                    }
                }
            }
            game_start = 0;
        }
        int gameloop = 1, game_over = 0;
        char entry, response;
        int player_x = 8 + (map_width*middle_square), player_y = 8 + (map_height*middle_square);
        for(int i = 0; i < grid_size; i++){
            if((player_x - ((i+1)*map_width)) < 0){
                player_in_grid_x = i;
                break;
            }
        }
        for(int i = 0; i < grid_size; i++){
            if((player_y - ((i+1)*map_height)) < 0){
                player_in_grid_y = i;
                break;
            }
        }
        int player_x_new = player_x, player_y_new = player_y;
        int goldencompass = 0;
        int treasure_grid_x, treasure_grid_y, treasure_x, treasure_y;
        int chest_1_grid_x, chest_1_grid_y, chest_1_x, chest_1_y;
        int chest_2_grid_x, chest_2_grid_y, chest_2_x, chest_2_y;
        int chest_3_grid_x, chest_3_grid_y, chest_3_x, chest_3_y;
        int chest_1_found = 0, chest_2_found = 0, chest_3_found = 0;
        double vision = 2.7;
        if(rand()%10+1>5){
            if(rand()%10+1>5){
                treasure_grid_x = 0;
            }
            else{
                treasure_grid_x = grid_size - 1;
            }
            treasure_grid_y = rand()%grid_size;
        }
        else{
            treasure_grid_x = rand()%grid_size;
            if(rand()%10+1>5){
                treasure_grid_y = 0;
            }
            else{
                treasure_grid_y = grid_size - 1;
            }
        }
        if(rand()%10+1>5){
            switch(rand()%4+1){
                case 1:{
                    chest_1_grid_x = middle_square - 1, chest_1_grid_y = middle_square - 1;
                    break;
                }
                case 2:{
                    chest_1_grid_x = middle_square, chest_1_grid_y = middle_square - 1;
                    break;
                }
                case 3:{
                    chest_1_grid_x = middle_square + 1, chest_1_grid_y = middle_square - 1;
                    break;
                }
                case 4:{
                    chest_1_grid_x = middle_square - 1, chest_1_grid_y = middle_square;
                    break;
                }
            }
            switch(rand()%4+1){
                case 1:{
                    chest_2_grid_x = middle_square + 1, chest_2_grid_y = middle_square;
                    break;
                }
                case 2:{
                    chest_2_grid_x = middle_square - 1, chest_2_grid_y = middle_square + 1;
                    break;
                }
                case 3:{
                    chest_2_grid_x = middle_square, chest_2_grid_y = middle_square + 1;
                    break;
                }
                case 4:{
                    chest_2_grid_x = middle_square + 1, chest_2_grid_y = middle_square + 1;
                    break;
                }
            }
        }
        else{
            switch(rand()%4+1){
                case 1:{
                    chest_2_grid_x = middle_square - 1, chest_2_grid_y = middle_square - 1;
                    break;
                }
                case 2:{
                    chest_2_grid_x = middle_square, chest_2_grid_y = middle_square - 1;
                    break;
                }
                case 3:{
                    chest_2_grid_x = middle_square + 1, chest_2_grid_y = middle_square - 1;
                    break;
                }
                case 4:{
                    chest_2_grid_x = middle_square - 1, chest_2_grid_y = middle_square;
                    break;
                }
            }
            switch(rand()%4+1){
                case 1:{
                    chest_1_grid_x = middle_square + 1, chest_1_grid_y = middle_square;
                    break;
                }
                case 2:{
                    chest_1_grid_x = middle_square - 1, chest_1_grid_y = middle_square + 1;
                    break;
                }
                case 3:{
                    chest_1_grid_x = middle_square, chest_1_grid_y = middle_square + 1;
                    break;
                }
                case 4:{
                    chest_1_grid_x = middle_square + 1, chest_1_grid_y = middle_square + 1;
                    break;
                }
            }
        }
        //std::cout << "Chest 1: " << chest_1_grid_x << "  " << chest_1_grid_y << std::endl;
        //std::cout << "Chest 2: " << chest_2_grid_x << "  " << chest_2_grid_y << std::endl;
        //std::cout << "Treasure chest: " << treasure_grid_x << "  " << treasure_grid_y << std::endl << std::endl;
        treasure_y = (treasure_grid_y*map_height) + 8;
        treasure_x = (treasure_grid_x*map_width) + 8;
        chest_1_y = (chest_1_grid_y*map_height) + 8, chest_1_x = (chest_1_grid_x*map_width) + 8;
        chest_2_y = (chest_2_grid_y*map_height) + 8, chest_2_x = (chest_2_grid_x*map_width) + 8;
        int chest_opened_yn = 0, open_chest_x = 0, open_chest_y = 0;
        int player_health = 100;
        //int enemy_1_x = 2, enemy_1_y = 11, enemy_1_moving = 0, enemy_1_alive = 1, enemy_1_x_new = enemy_1_x, enemy_1_y_new = enemy_1_y;
        gamemap[player_y][player_x] = 2;
        gamemap[treasure_y][treasure_x] = 3;
        gamemap[chest_1_y][chest_1_x] = 3;
        gamemap[chest_2_y][chest_2_x] = 3;
        int num_of_flash = 2, num_of_rocks = 1;
        //gamemap[enemy_1_y][enemy_1_x] = 10;
        while(gameloop==1){ //Gameplay starts here
            response = 'E';
            std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
            for(int i = 0; i < grid_size*map_height; i++){ //Code that copies the visible parts of the map to the seen map
                for(int k = 0; k < grid_size*map_width; k++){
                    if(pythag_dbl(player_x, k, player_y, i) < vision){
                        gamemap_seen[i][k] = gamemap[i][k];
                    }
                }
            }
            for(int i = 0; i < map_height; i++){ //Code that displays the map
                for(int k = 0; k < map_width; k++){
                    switch(gamemap_seen[(player_in_grid_y*map_height) + i][(player_in_grid_x*map_width) + k]){
                        case -1:{
                            std::cout << " ~ ";
                            break;
                        }
                        case 0:{
                            std::cout << "   ";
                            break;
                        }
                        case 1:{
                            if(gamemap_seen[(player_in_grid_y*map_height) + i][(player_in_grid_x*map_width) + k - 1] == 1){
                                std::cout << "#";
                            }
                            else{
                                std::cout << " ";
                            }
                            std::cout << "#";
                            if(gamemap_seen[(player_in_grid_y*map_height) + i][(player_in_grid_x*map_width) + k + 1] == 1){
                                std::cout << "#";
                            }
                            else{
                                std::cout << " ";
                            }
                            break;
                        }
                        case 2:{
                            std::cout << " P ";
                            break;
                        }
                        case 3:{
                            std::cout << " C ";
                            break;
                        }
                        case 10:{
                            std::cout << " ^ ";
                            break;
                        }
                        default:{
                            std::cout << " ` ";
                        }
                    }
                }
                std::cout << std::endl;
            }
            int treasure_distance = 0, chest_1_distance = 0, chest_2_distance = 0;
            if(goldencompass==1){
                std::cout << std::endl << "The treasure chest is " << pythag(player_x, treasure_x, player_y, treasure_y) << " tiles away" << std::endl << std::endl;
            }
            else{
                treasure_distance = pythag(player_x, treasure_x, player_y, treasure_y);
                chest_1_distance = pythag(player_x, chest_1_x, player_y, chest_1_y);
                chest_2_distance = pythag(player_x, chest_2_x, player_y, chest_2_y);
                if((treasure_distance < chest_1_distance) && (treasure_distance < chest_2_distance)){
                    std::cout << std::endl << "The nearest chest is " << treasure_distance << " tiles away" << std::endl << std::endl;
                }
                else if(chest_1_found == 0 && (chest_1_distance < treasure_distance) && (chest_1_distance < chest_2_distance)){
                    std::cout << std::endl << "The nearest chest is " << chest_1_distance << " tiles away" << std::endl << std::endl;
                }
                else if(chest_2_found == 0 && (chest_2_distance <= treasure_distance) && (chest_2_distance <= chest_1_distance)){
                    std::cout << std::endl << "The nearest chest is " << chest_2_distance << " tiles away" << std::endl << std::endl;
                }
                else if(chest_1_found == 0 && (chest_1_distance < treasure_distance)){
                    std::cout << std::endl << "The nearest chest is " << chest_1_distance << " tiles away" << std::endl << std::endl;
                }
                else{
                    std::cout << std::endl << "The nearest chest is " << treasure_distance << " tiles away" << std::endl << std::endl;
                }
            }
            //std::cout << "Player health: " << player_health << "HP" << std::endl;
            std::cout << std::endl << "You are in the grid space: " << player_in_grid_x + 1  << " " << player_in_grid_y + 1 << std::endl; 
            int entry_state = 1;
            while(entry_state==1){
            //std::cin.ignore(); //First entry doesn't respond if this is enabled
            std::cin.clear(); //Use this instead
            std::cout << std::endl;
            std::cin >> entry;
            std::cout << std::endl;
                switch(entry){
                    case 'w':{
                        if(player_y - 1 == -1){
                            player_y_new = player_y - 1;
                        }
                        else{
                            switch(gamemap[player_y-1][player_x]){
                                case 0:{
                                    player_y_new = player_y - 1;
                                    break;
                                }
                                case 1:{
                                    break;
                                }
                                case 3:
                                    chest_opened_yn = open_chest();
                                    if(chest_opened_yn == 1){
                                        open_chest_x = player_x, open_chest_y = player_y - 1;
                                    }
                                    break;
                                case 10:{
                                    std::cout << "You take 100 damage.";
                                    player_health =- 100;
                                    break;
                                }
                            }
                        }
                        entry_state = 0;
                        break;
                    }
                    case 's':{
                        if((player_y + 1) == (grid_size*map_height)){
                            player_y_new = player_y + 1;                      
                        }
                        else{
                            switch(gamemap[player_y+1][player_x]){
                                case 0:{
                                    player_y_new = player_y + 1;
                                    break;
                                }
                                case 1:{
                                    break;
                                }
                                case 3:
                                    chest_opened_yn = open_chest();
                                    if(chest_opened_yn == 1){
                                        open_chest_x = player_x, open_chest_y = player_y + 1;
                                    }
                                    break;
                                case 10:{
                                    std::cout << "You take 100 damage.";
                                    player_health =- 100;
                                    break;
                                }
                            }
                        }
                        entry_state = 0;
                        break;
                    }
                    case 'a':{
                        if(player_x - 1 == -1){
                            player_x_new = player_x - 1;
                        }
                        else{
                            switch(gamemap[player_y][player_x-1]){
                                case 0:{
                                    player_x_new = player_x - 1;
                                    break;
                                }
                                case 1:{
                                    break;
                                }
                                case 3:
                                    chest_opened_yn = open_chest();
                                    if(chest_opened_yn == 1){
                                        open_chest_x = player_x - 1, open_chest_y = player_y;
                                    }
                                    break;
                                case 10:{
                                    std::cout << "You take 100 damage.";
                                    player_health =- 100;
                                    break;
                                }
                            }
                        }
                        entry_state = 0;
                        break;
                    }
                    case 'd':{
                        if((player_x + 1) == (grid_size*map_width)){
                            player_x_new = player_x + 1;
                        }
                        else{
                            switch(gamemap[player_y][player_x+1]){
                                case 0:{
                                    player_x_new = player_x + 1;
                                    break;
                                }
                                case 1:{
                                    break;
                                }
                                case 3:
                                    chest_opened_yn = open_chest();
                                    if(chest_opened_yn == 1){
                                        open_chest_x = player_x + 1, open_chest_y = player_y;
                                    }
                                    break;
                                case 10:{
                                    std::cout << "You take 100 damage." << std::endl;
                                    player_health =- 100;
                                    break;
                                }
                            }
                        }
                        entry_state = 0;
                        break;
                    }
                    case 'p':{
                        std::cout << "You take a break." << std::endl;
                        entry_state = 0;
                        break;
                    }
                    case 'i':{
                        int temp1 = inventory(num_of_flash, num_of_rocks);
                        if(temp1 == 1){
                            num_of_flash = num_of_flash - 1;
                            for(int i = 0; i < map_height; i++){
                                for(int k = 0; k < map_width; k++){
                                    gamemap_seen[(player_in_grid_y*map_height) + i][(player_in_grid_x*map_width) + k] = gamemap[(player_in_grid_y*map_height) + i][(player_in_grid_x*map_width) + k];
                                }
                            }
                        }
                        entry_state = 0;
                        break;
                    }
                    default:{
                        std::cout << "Not a valid entry, please try again." << std::endl;
                        break;
                    }
                }
            }
            if(chest_opened_yn == 1){
                chest_opened_yn = 0;
                if(open_chest_x == treasure_x && open_chest_y == treasure_y){
                    std::cout << std::endl << std::endl << "You've found the treasure, congratulations!" << std::endl << "Game Over" << std::endl << std::endl;
                    Sleep(4000);
                    game_over = 1, gameloop = 0;
                }
                if(open_chest_x == chest_1_x && open_chest_y == chest_1_y){
                    std::cout << std::endl << "You found the golden compass!" << std::endl << "Compass system updated." << std::endl;
                    goldencompass = 1;
                    chest_1_found = 1;
                    gamemap[chest_1_y][chest_1_x] = 0, gamemap_seen[chest_1_y][chest_1_x] = 0;
                    Sleep(4000);
                }
                if(open_chest_x == chest_2_x && open_chest_y == chest_2_y){
                    std::cout << std::endl << "You found a brighter torch!" << std::endl << "Vision radius improved." << std::endl;
                    vision = 4.5;
                    chest_2_found = 1;
                    gamemap[chest_2_y][chest_2_x] = 0, gamemap_seen[chest_2_y][chest_2_x] = 0;
                    Sleep(4000);
                }
            }
            if(player_health <= 0){
                    std::cout << std::endl << std::endl << "You have died!" << std::endl << "Game Over" << std::endl << std::endl;
                    Sleep(4000);
                    game_over = 1, gameloop = 0;
            }
            if(player_y_new == (grid_size*map_height)){
                player_y_new = 0;
            }
            if(player_y_new == -1){
                player_y_new = ((grid_size*map_height) - 1);
            }
            if(player_x_new == (grid_size*map_width)){
                player_x_new = 0;
            }
            if(player_x_new == -1){
                player_x_new = ((grid_size*map_width) - 1);
            }
            gamemap[player_y][player_x] = 0;
            gamemap[player_y_new][player_x_new] = 2;
            player_y = player_y_new;
            player_x = player_x_new;
            for(int i = 0; i < grid_size; i++){
                if((player_x - ((i+1)*map_width)) < 0){
                    player_in_grid_x = i;
                    break;
                }
            }
            for(int i = 0; i < grid_size; i++){
                if((player_y - ((i+1)*map_height)) < 0){
                    player_in_grid_y = i;
                    break;
                }
            }
            /*if(enemy_1_alive == 1){
                switch(enemy_1_moving){
                    case 0:
                        enemy_1_y_new = enemy_1_y - 1;
                        break;
                    case 1:
                        enemy_1_y_new = enemy_1_y + 1;
                        break;
                    case 2:
                        enemy_1_x_new = enemy_1_x - 1;
                        break;
                    case 3:
                        enemy_1_x_new = enemy_1_x + 1;
                        break;
                }
                gamemap[enemy_1_y][enemy_1_x] = 0;
                gamemap[enemy_1_y_new][enemy_1_x_new] = 10;
                enemy_1_y = enemy_1_y_new, enemy_1_x = enemy_1_x_new;
                if(enemy_1_y < 5){
                    enemy_1_moving = 1;
                }
                if(enemy_1_y > 12){
                    enemy_1_moving = 0;
                }
            }*/
        system("cls");
        }
    while(game_over == 1){
        system("cls");
        std::cout << std::endl << std::endl << "Would you like to play again?" << std::endl << "Y/N: ";
        std::cin.clear();
        std::cin >> entry;
        std::cout << std::endl;
        switch(entry){
            case 'y':
            case 'Y':
                std::cout << "Starting new game." << std::endl;
                Sleep(2000);
                game_over = 0;
                break;
            case 'n':
            case 'N':
                std::cout << "Shutting down the game." << std::endl << "Thank you for playing." << std::endl;
                Sleep(2000);
                game_over = 0, game = 0;
                break;
            default:
                std::cout << "That's not a valid entry." << std::endl << "Please try again." << std::endl;
                Sleep(500);
            }
        }
    }
    return 0;
}