#ifndef MAIN_OBJECT_
#define MAIN_OBJECT_

#include <vector>

#include "commonFunction.h"
#include "baseObject.h"
#include "BulletObject.h"


#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VAL 20
#define PLAYER_NUM_FRAME 8

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound[2]);
    void set_clips();
    enum WalkType
    {
        WALK_NONE_ = 0,
        WALK_RIGHT_ = 1,
        WALK_LEFT_ = 2,
        WALK_DOWN_LEFT = 3,
        WALK_DOWN_RIGHT = 4,
    };

    void Doplayer(Map& map_data, Mix_Chunk* money_sound);
    void CheckToMap(Map& map_data, Mix_Chunk* money_sound);
    bool CheckFinish(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;};
    void CenterEntityOnMap(Map& map_data);
    void UpdateImagePlayer(SDL_Renderer* des);

    void set_bullet_list(std::vector<BulletObject*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }
    std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list_;}
    void HandleBullet(SDL_Renderer* des);
    void RemoveBullet(const int& idx);
    void IncreaseMoney(Mix_Chunk* money_sound);

    void set_comeback_time(const int& cb_time) {come_back_time_ = cb_time;}
    int GetMoneyCount() const {return money_count; }

    SDL_Rect GetRectFrame();
    bool isFallDown;

private:
    int money_count;
    std::vector<BulletObject*> p_bullet_list_;
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_;
    bool on_ground_= false;
    bool is_down_ = false;

    int map_x_;
    int map_y_;

    int come_back_time_;
};


#endif // MAIN_OBJECT_
