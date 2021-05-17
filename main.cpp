#include "imgui.h"
#include "imgui-SFML.h"
#include <stdio.h>
#include <SFML/Graphics.hpp>

#define GRID_WIDTH 500
#define GRID_HEIGHT 500
#define SQUARE_SIZE 10
#define OFFSET 10

int grid_status[GRID_HEIGHT][GRID_WIDTH];

//sf::RectangleShape grid[GRID_HEIGHT][GRID_WIDTH];
sf::Sprite grid[GRID_HEIGHT][GRID_WIDTH];
sf::Image img_white;
sf::Image img_black;
sf::Texture tex_white;
sf::Texture tex_black;

typedef struct LAnt
{
    sf::Vector2i pos;
    int orientation;
}LAnt;

LAnt lant;


void InitializeGrid();
void DrawGrid(sf::RenderWindow &window);
void CalculateAntPath();
void DrawAnt(sf::RenderWindow &window);

void ShowStartDialog(sf::RenderWindow &window);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Langton's Ant");
    sf::View view(sf::FloatRect(0,0,window.getSize().x,window.getSize().y));
    lant.orientation = 180;
    lant.pos.x = 250;
    lant.pos.y = 250;

    ImGui::SFML::Init(window);

    ShowStartDialog(window);

    view.setCenter(lant.pos.x*SQUARE_SIZE,lant.pos.y*SQUARE_SIZE);
    window.setView(view);
    InitializeGrid();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        DrawGrid(window);
        DrawAnt(window);
        CalculateAntPath();
//        sf::sleep(sf::seconds(0.1f));
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}

void InitializeGrid()
{
    int i,j;

    img_black.create(SQUARE_SIZE,SQUARE_SIZE,sf::Color::Black);
    img_white.create(SQUARE_SIZE,SQUARE_SIZE,sf::Color::White);

    for(i=0;i<SQUARE_SIZE;++i)
    {
        img_white.setPixel(i,0,sf::Color::Black);
        img_white.setPixel(0,i,sf::Color::Black);
        img_white.setPixel(SQUARE_SIZE-1,i,sf::Color::Black);
        img_white.setPixel(i,SQUARE_SIZE-1,sf::Color::Black);
    }

    tex_black.loadFromImage(img_black);
    tex_white.loadFromImage(img_white);

//    for(i=0;i<GRID_HEIGHT;++i)
//    {
//        for(j=0;j<GRID_WIDTH;++j)
//        {
//            grid[i][j].setSize(sf::Vector2f(10.f,10.f));
//            grid[i][j].setPosition(j*10+OFFSET,i*10+OFFSET);
//            grid[i][j].setFillColor(sf::Color::White);
//            grid[i][j].setOutlineThickness(1.f);
//            grid[i][j].setOutlineColor(sf::Color::Black);
//        }
//    }

    for(i=0;i<GRID_HEIGHT;++i)
    {
        for(j=0;j<GRID_WIDTH;++j)
        {
            grid[i][j].setTexture(tex_white);
            grid[i][j].setPosition(j*10+OFFSET,i*10+OFFSET);
            grid_status[i][j] = 1;
        }
    }
}

void DrawGrid(sf::RenderWindow &window)
{
    int i,j;
    for(i=0;i<GRID_HEIGHT;++i)
    {
        for(j=0;j<GRID_WIDTH;++j)
        {
            window.draw(grid[i][j]);
        }
    }
}

void CalculateAntPath()
{
    int x = lant.pos.x;
    int y = lant.pos.y;

//    int new_x = x;
//    int new_y = y;

    if(grid_status[y][x] == 1)
    {
        grid_status[y][x] = 0;
        grid[y][x].setTexture(tex_black);
        switch(lant.orientation)
        {
        case 0:
            ++lant.pos.y;
            lant.orientation = 270;
            break;
        case 90:
            ++lant.pos.x;
            lant.orientation = 0;
            break;
        case 180:
            --lant.pos.y;
            lant.orientation = 90;
            break;
        case 270:
            --lant.pos.x;
            lant.orientation = 180;
            break;
        }
        return;
    }

    if(grid_status[y][x] ==0)
    {
        grid_status[y][x] = 1;
        grid[y][x].setTexture(tex_white);
        switch(lant.orientation)
        {
        case 0:
            --lant.pos.y;
            lant.orientation = 90;
            break;
        case 90:
            --lant.pos.x;
            lant.orientation = 180;
            break;
        case 180:
            ++lant.pos.y;
            lant.orientation = 270;
            break;
        case 270:
            ++lant.pos.x;
            lant.orientation = 0;
            break;
        }
    }

}

void DrawAnt(sf::RenderWindow &window)
{
    sf::CircleShape ant(3.f);
    ant.setFillColor(sf::Color::Red);
    ant.setPosition(lant.pos.x*SQUARE_SIZE+OFFSET,lant.pos.y*SQUARE_SIZE+OFFSET);
    window.draw(ant);
}

void ShowStartDialog(sf::RenderWindow &window)
{
    bool start_click = false;
    bool exit_click = false;
    sf::Clock deltaClock;
    while(window.isOpen())
    {

        window.clear();
        sf::Event event;
        while(window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin(" ");
        if(ImGui::Button("Start"))
            start_click = true;
        if(ImGui::Button("Exit"))
            exit_click = true;

        ImGui::End();
        ImGui::SFML::Render(window);
        window.display();
        if(start_click)
            return;
        if(exit_click)
            exit(1);
    }
}

































