#include "commonFunction.h"
#include "baseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatObject.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "ExplosionObject.h"
#include "Geometric.h"

#include <iostream>

using namespace std;
BaseObject g_background;
TTF_Font* font_time;
TTF_Font* font_menu;
TTF_Font* font_menu_over;

int recordBestScore(int mark)
{
    ifstream filein;
    filein.open("./record.txt", ios_base::in);
    int previousPoint = 0;
    filein >> previousPoint;
    if (mark > previousPoint)
    {
        ofstream ofs ("./record.txt", std::ofstream::out);
        ofs << mark;
        ofs.close();
    }
    return previousPoint;
}

bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
	{
		return false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("Brave Solider", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
			success = false;
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR  , RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = false;
		}
	}

	if (TTF_Init() == -1)
    {
        success = false;
    }

    font_time = TTF_OpenFont("./game_resource/dlxfont_.ttf", 15);
    font_menu = TTF_OpenFont("./game_resource/000BattleDamaged-Regular.ttf", 42);
    font_menu_over = TTF_OpenFont("./game_resource/Rokkitt-VariableFont_wght.ttf", 35);
    if (font_time == NULL)
    {
        success = false;
    }

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return false;
    }

    // Read file wav audio
    g_sound_bullet[0] = Mix_LoadWAV("./game_resource/sphere_bullet.wav");
    g_sound_bullet[1] = Mix_LoadWAV("./game_resource/laser_bullet.wav");
    g_sound_exp[0] = Mix_LoadWAV("./game_resource/explosion1.wav");
    g_money_sound = Mix_LoadWAV("./game_resource/beep.wav");

    g_background_music = Mix_LoadMUS("./game_resource/background_music.wav");

    if (g_sound_exp[0] == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_money_sound == NULL)
    {
        success = false;
    }

    return success;
}

bool LoadBackGround()
{
	bool ret = g_background.LoadImg("./assets/image/background.png", g_screen);
	if (ret == false)
	{
		return false;
	}
	return true;
}

void close ()
{
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	Mix_FreeChunk(g_sound_bullet[0]);
    Mix_FreeChunk(g_sound_bullet[1]);
    Mix_FreeChunk(g_sound_exp[0]);
    Mix_FreeChunk(g_money_sound);

    Mix_FreeMusic(g_background_music);

    g_sound_bullet[0] = NULL;
    g_sound_bullet[1] = NULL;
    g_sound_exp[0] = NULL;
    g_money_sound = NULL;

    g_background_music = NULL;

    Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

std::vector<ThreatsObject*> MakeThreatList()
{
    std::vector<ThreatsObject*> list_threats;

    ThreatsObject* dynamic_threats = new ThreatsObject[20];
    for (int i=0; i < 20; i++)
    {
        ThreatsObject* p_threat = (dynamic_threats + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("./assets/image/threat_left.png", g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i*750);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);

            list_threats.push_back(p_threat);
        }
    }


    ThreatsObject* threats_objs = new ThreatsObject[20];
    for (int i=0; i<20; i++)
    {
        ThreatsObject* p_threat = (threats_objs + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("./assets/image/threat_level.png", g_screen);
            p_threat->set_clips();
            if (i < 5)
            {
                p_threat->set_x_pos(750 + i*1200);
            }
            else
            {
                p_threat->set_x_pos(750 + i*1300);
            }
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}



int main( int argc, char* args[] )
{
    if (InitData() == false)
    {
        return 0;
    }

    TTF_Font* font = TTF_OpenFont("./game_resource/dlxfont_.ttf", 18);
    if (font == NULL)
    {
        cout << "font is error";
    }

    Mix_PlayMusic(g_background_music, -1);

        // Start Menu
    int ret_menu = SDLCommonFunc::ShowMenu(g_screen, font_menu);
    if (ret_menu == 1)
    {
        close();
        return 0;
    }

    bool is_replay = true;
    static Uint32 totalTime = 300;

    while (is_replay == true)
    {
        ImpTimer fps_timer;


        GameMap game_map;
        game_map.LoadMap("./map/map01.txt");
        game_map.LoadTiles(g_screen);


        MainObject p_player;
        p_player.LoadImg("./assets/image/player_right.png", g_screen);
        p_player.set_clips();

        PlayerPower player_power;
        player_power.Init(g_screen);

        PlayerMoney player_money;
        player_money.Init(g_screen);
        player_money.SetPos(SCREEN_WIDTH*0.5 - 300, 8);



	    if (LoadBackGround() == false)
        {
            cout << "image's path is undefined!";
            return 0;
        }
        std::vector<ThreatsObject*> threats_list = MakeThreatList();
        int num_die = 0;

        ExplosionObject exp_threat;
        bool tRet = exp_threat.LoadImg("./assets/image/exp3.png", g_screen);
        if (!tRet) return -1;
        exp_threat.set_clip();
        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_height = exp_threat.get_frame_height();

        //Time text
        TextObject time_game;
        time_game.SetColor(TextObject::WHITE_TEXT);

        TextObject mark_game;
        mark_game.SetColor(TextObject::WHITE_TEXT);

        int mark_value = 0;

        TextObject money_game;
        money_game.SetColor(TextObject::WHITE_TEXT);

        bool is_quit = false;


        while (!is_quit)
	    {
            //Show game time
            std::string str_time = "Time: ";
            Uint32 time_val = SDL_GetTicks() / 1000;
            Uint32 val_time = totalTime - time_val;

            // start game
            fps_timer.start();
            while (SDL_PollEvent(&g_event) != 0)
            {
            if (g_event.type == SDL_QUIT)
                {
                    is_replay = false;
                    is_quit = true;
                }

                p_player.HandleInputAction(g_event, g_screen, g_sound_bullet);
            }

            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);

            g_background.Render(g_screen, NULL);

            Map map_data = game_map.getMap();

            p_player.HandleBullet(g_screen);
            p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
            p_player.Doplayer(map_data, g_money_sound);

            p_player.Show(g_screen);

            game_map.SetMap(map_data);
            game_map.DrawMap(g_screen);

            // Draw rectangle in the top
            GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
            ColorData color_data(36, 36, 36);
            Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

            GeometricFormat outlineSize(1, 1, SCREEN_WIDTH -1, 38);
            ColorData outline_color(255, 255, 255);
            Geometric::RenderOutline(outlineSize, outline_color, g_screen);

            player_power.Show(g_screen);
            player_money.Show(g_screen);

            int money_count = p_player.GetMoneyCount();
            if (p_player.CheckFinish(map_data))
            {
                int current_mark = mark_value + money_count;
                int totalMark = recordBestScore(current_mark);
                int ret_menu_over = SDLCommonFunc::ShowMenuOver(g_screen, font, font_menu_over, totalMark, current_mark);
                if (ret_menu_over == 1)
                {
                    is_quit = true;
                    is_replay = false;
                }
                if (ret_menu_over == 0)
                {
                    is_quit = true;
                    is_replay = true;
                }
                time_val = SDL_GetTicks() / 1000;
                totalTime = 300 + time_val;
            }

            //Xử lí rơi xuống vực thẳm (bắn chết p_threat đầu để check chính xác)
            if (p_player.isFallDown == true)
            {
                num_die++;
                if (num_die <= 3)
                {
                    p_player.SetRect(0,0);
                    p_player.set_comeback_time(60);
                    player_power.Decrease();
                    player_power.Render(g_screen);
                }
                else
                {
                    int current_mark = mark_value + money_count;
                    int totalMark = recordBestScore(current_mark);
                    int ret_menu_over = SDLCommonFunc::ShowMenuOver(g_screen, font, font_menu_over, totalMark, current_mark);
                    if (ret_menu_over == 1)
                    {
                        is_quit = true;
                        is_replay = false;
                    }
                    if (ret_menu_over == 0)
                    {
                        is_quit = true;
                        is_replay = true;
                    }
                    time_val = SDL_GetTicks() / 1000;
                    totalTime = 300 + time_val;
                }
                cout << "FallDown" << endl;
                p_player.isFallDown = false;
            }

            for (int i=0; i < threats_list.size(); i++)
            {
                ThreatsObject* p_threat = threats_list.at(i);
                if (p_threat != NULL)
                {
                    p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                    p_threat->ImpMoveType(g_screen);
                    p_threat->DoPlayer(map_data);
                    p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT); // phạm vi của đạn là nằm trong màn hình
                    p_threat->Show(g_screen);

                    SDL_Rect rect_player = p_player.GetRectFrame();
                    bool bCol1 = false;
                    std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                    for (int jj = 0; jj < tBullet_list.size(); ++jj)
                    {
                        BulletObject* pt_bullet = tBullet_list.at(jj);
                        if (pt_bullet)
                        {
                            bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
                            if (bCol1 == true)
                            {
                                break;
                            }
                        }
                    }


                    SDL_Rect rect_threat = p_threat->GetRectFrame();
                    bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);

                    if (bCol2 || bCol1)
                    {
                        if(bCol2) cout << "bCol2" << endl;
                        if (bCol1) cout << "bCol1" << endl;
                        Mix_PlayChannel(-1, g_sound_exp[0], 0);
                        num_die++;
                        if (num_die <= 3)
                        {
                            p_player.SetRect(0,0);
                            p_player.set_comeback_time(60);
                            SDL_Delay(1000);
                            player_power.Decrease();
                            player_power.Render(g_screen);
                            continue;
                        }
                        else
                        {
                            int current_mark = mark_value + money_count;
                            int totalMark = recordBestScore(current_mark);
                            int ret_menu_over = SDLCommonFunc::ShowMenuOver(g_screen, font, font_menu_over, totalMark, current_mark);
                            if (ret_menu_over == 1)
                            {
                                is_quit = true;
                                is_replay = false;
                            }
                            if (ret_menu_over == 0)
                            {
                                is_quit = true;
                                is_replay = true;
                            }
                            time_val = SDL_GetTicks() / 1000;
                            totalTime = 300 + time_val;
                        }
                    }
                }
            }

            std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
            for (int r = 0; r < bullet_arr. size(); ++r)
            {
                BulletObject* p_bullet = bullet_arr.at(r);
                if (p_bullet != NULL)
                {
                    for (int t=0; t < threats_list.size(); ++t)
                    {
                        ThreatsObject* obj_threat = threats_list.at(t);
                        if (obj_threat != NULL)
                        {
                            SDL_Rect tRect;
                            tRect.x = obj_threat->GetRect().x;
                            tRect.y = obj_threat->GetRect().y;
                            tRect.w = obj_threat->get_width_frame(); //do sử dụng frame nên chỉ lấy chiều rộng và chiều dài đúng bằng 1 khung hình
                            tRect.h = obj_threat->get_height_frame();

                            SDL_Rect bRect = p_bullet->GetRect(); // do đạn không có frame

                            bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

                            if (bCol)
                            {
                                for (int ex = 0; ex < NUM_FRAME_EXP; ++ex)
                                {
                                    int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
                                    int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;
                                    exp_threat.set_frame(ex);
                                    exp_threat.SetRect(x_pos, y_pos);
                                    exp_threat.Show(g_screen);
                                }
                                mark_value++;
                                p_player.RemoveBullet(r);
                                obj_threat->Free();
                                threats_list.erase(threats_list.begin() + t);
                                Mix_PlayChannel(-1, g_sound_exp[0], 0);
                            }
                        }
                    }
                }
            }


            // Show game time

            if (val_time <= 0)
            {
                    int current_mark = mark_value + money_count;
                    int totalMark = recordBestScore(current_mark);
                    int ret_menu_over = SDLCommonFunc::ShowMenuOver(g_screen, font, font_menu_over, totalMark, current_mark);
                    if (ret_menu_over == 1)
                    {
                        is_quit = true;
                        is_replay = false;
                    }
                    if (ret_menu_over == 0)
                    {
                        is_quit = true;
                        is_replay = true;
                    }
                    time_val = SDL_GetTicks() / 1000;
                    totalTime = 300 + time_val;
            }
            else
            {
                std::string str_val = std::to_string(val_time);
                str_time += str_val;

                time_game.SetText(str_time);
                time_game.LoadFromRenderText(font_time, g_screen);
                time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
            }

            std::string val_str_mark = std::to_string(mark_value);
            std::string strMark("Mark: ");
            strMark += val_str_mark;

            mark_game.SetText(strMark);
            mark_game.LoadFromRenderText(font_time, g_screen);
            mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, 15);


            std::string money_str = std::to_string(money_count);

            money_game.SetText(money_str);
            money_game.LoadFromRenderText(font_time, g_screen);
            money_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 250, 15);


            SDL_RenderPresent(g_screen);
            int real_imp_time = fps_timer.get_ticks();
            int time_one_frame = 1000/FRAME_PER_SECOND; //ms
            if (real_imp_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_imp_time;
                if (delay_time >= 0)
                {
                    SDL_Delay(delay_time);
                }
            }
        }

    // Release resources
	for (int i=0; i<threats_list.size(); i++)
    {
        ThreatsObject* p_threat = threats_list.at(i);
        if (p_threat != NULL)
        {
            p_threat->Free();
            p_threat = NULL;
        }
    }

    threats_list.clear();
	}

	close();

	return 0;
}
