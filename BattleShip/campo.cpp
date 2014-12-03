#include "campo.h"

Campo::Campo(bool dono)
{
    this->dono = dono;
    this->hitCont = 0;
    for(int i = 0; i < 11; i++)
        for(int j = 0; j < 11; j++){
            this->mat[i][j][0] = ' ';
            this->mat[i][j][1] = ' ';
        }
}

//TODO: Rotation
void Campo::posicionar()
{
    int x,y;
    std::cout << "Posicionar Porta-Avioes [5u]" << std::endl;
    std::cin >> x >> y;
    this->mat[x][y][0] = 'P';
    this->mat[x+1][y][0] = 'P';
    this->mat[x+1][y+1][0] = 'P';
    this->mat[x+1][y-1][0] = 'P';

    for(char i = 0; i < 3; i++){
        std::cout << "Posicionar Submarino " << i << " [1u]" << std::endl;
        std::cin >> x >> y;
        this->mat[x][y][0] = 'S';
    }

    for(char i = 0; i < 2; i++){
        std::cout << "Posicionar Barco A " << i << " [2u]" << std::endl;
        std::cin >> x >> y;
        this->mat[x][y][0] = 'A';
        this->mat[x+1][y][0] = 'A';
    }

    for(char i = 0; i < 3; i++){
        std::cout << "Posicionar Barco B " << i << " [3u]" << std::endl;
        std::cin >> x >> y;
        this->mat[x][y][0] = 'B';
        this->mat[x+1][y][0] = 'B';
        this->mat[x+2][y][0] = 'B';
    }

    std::cout << "--- Todas unidades posicionadas ---" << std::endl;
}

char* Campo::atirar(int x, int y)
{
    char *msg;
    if(this->mat[x][y][0] != ' '){
        msg = "Hit!";
        if(!this->dono) this->hitCont++;
    }
    else
        msg = "Miss";

    this->mat[x][y][1] = 'H';
    return msg;
}

void Campo::showCampo()
{
    if(this->dono)
        std::cout << "My ";
    else
        std::cout << "Enemy ";
    std::cout << "Side" << std::endl;

    for(int i = 1; i < 11; i++){
        for(int j = 1; j < 11; j++){
            std::cout << this->mat[i][j][0];
            std::cout << this->mat[i][j][1];
            std::cout << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "---------------------------------" << std::endl << std::endl;
}

bool Campo::isGameOver()
{
    if(this->hitCont == 17)
        return true;
    return false;
}
