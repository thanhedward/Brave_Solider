#include "commonFunction.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}


int SDLCommonFunc::ShowMenu(SDL_Renderer* screen, TTF_Font* font)
{
    BaseObject g_menu;
    bool ret = g_menu.LoadImg("../assets/image/start.png", screen);
    if (ret == false)
    {
        return 1;
    }


    const int kMenuItemNum = 2;
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 400;

    pos_arr[1].x = 200;
    pos_arr[1].y = 480;

    TextObject text_menu[kMenuItemNum];

    text_menu[0].SetText("Play Game");
    text_menu[0].SetColor(TextObject::BLACK_TEXT);
    text_menu[0].LoadFromRenderText(font, screen);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);
    text_menu[0].SetSize(text_menu[0].GetWidth(), text_menu[0].GetHeight());

    text_menu[1].SetText("Exit");
    text_menu[1].SetColor(TextObject::BLACK_TEXT);
    text_menu[1].LoadFromRenderText(font, screen);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);
    text_menu[1].SetSize(text_menu[1].GetWidth(), text_menu[1].GetHeight());

    bool selected[kMenuItemNum] = {0, 0};

    int xm = 0;
    int ym = 0;

    SDL_Event m_event;
    while (true)
    {
        g_menu.Render(screen, NULL);
        for (int i = 0; i < kMenuItemNum; i++)
        {
            text_menu[i].RenderText(screen, pos_arr[i].x, pos_arr[i].y);
        }

        while (SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;


                    for (int i = 0; i < kMenuItemNum; i++)
                    {
                        if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                        {
                            if (selected[i] == false)
                            {
                                selected[i] = 1;
                                text_menu[i].SetColor(TextObject::RED_TEXT);
                                text_menu[i].LoadTextWithColor(font, screen);
                            }
                        }
                        else
                        {
                            if (selected[i] == true)
                            {
                                selected[i] = 0;
                                text_menu[i].SetColor(TextObject::BLACK_TEXT);
                                text_menu[i].LoadTextWithColor(font, screen);
                            }
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    xm = m_event.button.x;
                    ym = m_event.button.y;

                    for (int i = 0; i < kMenuItemNum; i++)
                    {
                        if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                        {
                            return i;
                        }
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        return 1;
                    }
            default:
                break;
            }
        }

        SDL_RenderPresent(screen);
    }

    return 1;
}

int SDLCommonFunc::ShowMenuOver(SDL_Renderer* screen, TTF_Font* font, TTF_Font* font_mark, int total_mark, int current_mark)
{
    BaseObject g_menu_over;
    bool ret = g_menu_over.LoadImg("../assets/image/gameover.jpg", screen);
    if (ret == false)
    {
        return 1;
    }


    const int kMenuItemNum = 3;
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 545;
    pos_arr[0].y = 348;

    pos_arr[1].x = 700;
    pos_arr[1].y = 348;

    SDL_Rect score_item[2];
    score_item[0].x = 530;
    score_item[0].y = 450;

    score_item[1].x = 530;
    score_item[1].y = 500;

    TextObject text_menu[kMenuItemNum];

    text_menu[0].SetText("Yes");
    text_menu[0].SetColor(TextObject::WHITE_TEXT);
    text_menu[0].LoadFromRenderText(font, screen);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);
    text_menu[0].SetSize(text_menu[0].GetWidth(), text_menu[0].GetHeight());

    text_menu[1].SetText("No");
    text_menu[1].SetColor(TextObject::WHITE_TEXT);
    text_menu[1].LoadFromRenderText(font, screen);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);
    text_menu[1].SetSize(text_menu[1].GetWidth(), text_menu[1].GetHeight());


    // Text Objet scrore
    TextObject text_score[2];

    std::string val_total_mark = std::to_string(total_mark);
    std::string strTotalMark("Best score: ");
    strTotalMark += val_total_mark;


    text_score[0].SetText(strTotalMark);
    text_score[0].SetColor(TextObject::WHITE_TEXT);
    text_score[0].LoadFromRenderText(font_mark, screen);
    text_score[0].SetRect(score_item[0].x, score_item[0].y);

    std::string val_curr_mark = std::to_string(current_mark);
    std::string strCurrMark("Your score: ");
    strCurrMark += val_curr_mark;

    text_score[1].SetText(strCurrMark);
    text_score[1].SetColor(TextObject::WHITE_TEXT);
    text_score[1].LoadFromRenderText(font_mark, screen);
    text_score[1].SetRect(score_item[1].x, score_item[1].y);

    bool selected[kMenuItemNum] = {0, 0};

    int xm = 0;
    int ym = 0;

    SDL_Event m_event;
    while (true)
    {
        g_menu_over.Render(screen, NULL);
        text_score[0].RenderText(screen, score_item[0].x, score_item[0].y);
        text_score[1].RenderText(screen, score_item[1].x, score_item[1].y);
        for (int i = 0; i < kMenuItemNum; i++)
        {
            text_menu[i].RenderText(screen, pos_arr[i].x, pos_arr[i].y);
        }

        while (SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;


                    for (int i = 0; i < kMenuItemNum; i++)
                    {
                        if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                        {
                            if (selected[i] == false)
                            {
                                selected[i] = 1;
                                text_menu[i].SetColor(TextObject::RED_TEXT);
                                text_menu[i].LoadTextWithColor(font, screen);
                            }
                        }
                        else
                        {
                            if (selected[i] == true)
                            {
                                selected[i] = 0;
                                text_menu[i].SetColor(TextObject::WHITE_TEXT);
                                text_menu[i].LoadTextWithColor(font, screen);
                            }
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    xm = m_event.button.x;
                    ym = m_event.button.y;

                    for (int i = 0; i < kMenuItemNum; i++)
                    {
                        if (CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
                        {
                            return i;
                        }
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        return 1;
                    }
            default:
                break;
            }
        }

        SDL_RenderPresent(screen);
    }

    return 1;
}



bool SDLCommonFunc::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}


