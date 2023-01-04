/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-edouard.francois
** File description:
** main
*/

#include "Indi.hpp"
#include "Graphic.hpp"
#include "Menu.hpp"
#include <stdio.h>

bool tst(int a, int b)
{
    std::cout << "action\n";
    return true;
}

bool tstt(int a, int b)
{
    std::cout << "action\n";
    return false;
}

// std::vector <std::unique_ptr<Graphic::Button>> Create_bnt_player()
// {
//     std::vector<std::unique_ptr<Graphic::Button>> res;
//     // Graphic::Button first("PLAY", Vector2{30, 30}, Vector2{200, 60}, RED, (Color){ 240, 70, 90, 255 }, BLUE, tst);
//     res.push_back(std::make_unique<Graphic::Button>("PLAYEUR 1", Vector2{30, 30}, Vector2{400, 60}, RED, (Color){ 240, 70, 90, 255 }, BLUE, tst));
//     res.push_back(std::make_unique<Graphic::Button>("PLAYEUR 2", Vector2{30, 100}, Vector2{400, 60}, RED, (Color){ 240, 70, 90, 255 }, BLUE, tst));
//     res.push_back(std::make_unique<Graphic::Button>("PLAYEUR 3", Vector2{30, 170}, Vector2{400, 60}, RED, (Color){ 240, 70, 90, 255 }, BLUE, tst));
//     res.push_back(std::make_unique<Graphic::Button>("PLAYEUR 4", Vector2{30, 240}, Vector2{400, 60}, RED, (Color){ 240, 70, 90, 255 }, BLUE, tst));

//     res.push_back(std::make_unique<Graphic::Button>("PLAY", Vector2{790, 650}, Vector2{190, 60}, RED, (Color){ 240, 70, 90, 255 }, BLUE, tst));
//     // res.push_back(Graphic::Button("OK", Vector2{300, 300}, Vector2{200, 60}, RED, (Color){ 240, 70, 90, 255 }, BLUE, tstt));
//     std::cout << res.size() << " tst\n";
//     printf("end function\n");

//     return res;
// }

int main(void)
{
    Indi i;

    i.Run();

    // unsigned a = -1;
    // ShowCursor();
    // Graphic::Button btn("PLAY", Vector2{30, 30}, Vector2{200, 60}, RED, GREEN, BLUE);
    // while (!WindowShouldClose()) {
    //     BeginDrawing();
    //     ClearBackground(RAYWHITE);
    //     btn.Frame();
    //     EndDrawing();
    // }
    // CloseWindow();
    // i.SetUpMap();
    // i.Game();
    // Graphic::Graphic graphic(i.GetAllMapSizeX(), i.GetAllMapSizeY());
    // while (graphic.Frame(i.GetAllMap()));
    // MyRaylib::MyRaylib window(1080, 720, 60, "teste title");
    // MyRaylib::Camera cam;
    // Model model = window.CreateModel("../tst/guyanim/iqm");
        // MyRaylib::Touch touch('m', 'p', 'o', 'z', 's', 'q', 'd');
    // while (window.WindowIsOpen()) {
        // int a = (int)touch.GetActionFromTouch();
    //     if (a != 7)
    //         printf("%d\n", a);
    //     ClearBackground(RAYWHITE);
    //     BeginDrawing();
    //     BeginMode3D(cam.Get());
    //     DrawPlane((Vector3){0, 0, 0}, (Vector2){15, 13}, LIGHTGRAY);
        // DrawModelEx(model, (Vector3){0,0,0}, (Vector3){ 1.0f, 0.0f, 0.0f }, -90.0f, (Vector3){ 0.2f, 0.2f, 0.2f }, WHITE);
    //     EndMode3D();
    //     EndDrawing();
    // }
    return 0;
}
// tableau de modele comme ct avant
// tester classe qui possède se tableau