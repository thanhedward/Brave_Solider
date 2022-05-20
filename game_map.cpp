#include "game_map.h"
#include "commonFunction.h"
#include "baseObject.h"

void GameMap::LoadMap(char* name)
{
    ifstream filein;
    filein.open(name,ios_base::in);

    game_map_.max_x_ = 0;
    game_map_.max_y_ = 0;

    for (int i=0;i<MAX_MAP_Y; i++){
        for (int j=0; j<MAX_MAP_X; j++)
        {
            int temp;
            filein >> temp;
            game_map_.tile[i][j] = temp;
            int value = game_map_.tile[i][j];
            if (value > 0)
            {
                if (j > game_map_.max_x_){
                    game_map_.max_x_ = j;
                }

                if (i > game_map_.max_y_)
                {
                    game_map_.max_y_ = i;
                }
            }
        }
    }

    game_map_.max_x_ = (game_map_.max_x_ + 1)*TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_ + 1)*TILE_SIZE;

    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;

    game_map_.file_name_ = name;


}


void GameMap::LoadTiles(SDL_Renderer* screen)
{
    string file_img[10];
//    FILE* fp = NULL;
    for (int i=0; i< MAX_TILES; i++)
    {
        string path = "../map/" + to_string(i) + ".png";

        // check the path
        ifstream ifs(path.c_str());
        if (!ifs)
        {
            continue;
        }
        file_img[i] = path;
        tile_mat[i].LoadImg(file_img[i], screen);

    }
}



void GameMap::DrawMap(SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = game_map_.start_x_/TILE_SIZE;   
    x1 = (game_map_.start_x_%TILE_SIZE) * -1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = game_map_.start_y_/TILE_SIZE;
    y1 = (game_map_.start_y_%TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map_.start_x_/TILE_SIZE;
        for (int j = x1; j < x2; j+= TILE_SIZE)
        {
            int value = game_map_.tile[map_y][map_x];
            if (value > 0)
            {
                tile_mat[value].SetRect(j,i);
                tile_mat[value].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}


