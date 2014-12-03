#include "campo.h"

Campo::Campo(bool dono)
{
    this->dono = dono;

    this->hitCont = 0;
    this->desistencia = false;
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
    this->mat[x][y][0] = '1';
    this->mat[x+1][y][0] = '1';
    this->mat[x+2][y][0] ='1';
    this->mat[x+2][y+1][0] ='1';
    this->mat[x+2][y-1][0] = '1';
    this->showCampo();


    //4 4 1 1 1 2 1 3 1 8 1 9 2 1 2 2 3 2

    for(int i = 0; i < 3; i++){
        std::cout << "Posicionar Submarino " << i << " [1u]" << std::endl;
        std::cin >> x >> y;
        this->mat[x][y][0] = '1';

        this->showCampo();
    }

    for(int i = 0; i < 2; i++){
        std::cout << "Posicionar Barco A " << i << " [2u]" << std::endl;
        std::cin >> x >> y;
        this->mat[x][y][0] = '1';
        this->mat[x+1][y][0] ='1';

        this->showCampo();
    }

    for(int i = 0; i < 2; i++){
        std::cout << "Posicionar Barco B " << i << " [3u]" << std::endl;
        std::cin >> x >> y;
        this->mat[x][y][0] ='1';
        this->mat[x+1][y][0] ='1';
        this->mat[x+2][y][0] ='1';

        this->showCampo();
    }

    std::cout << "--- Todas unidades posicionadas ---" << std::endl;
}

int Campo::rcvTiro(int x, int y)
{
    int msg;
    if(this->mat[x][y][0] != ' '){
        msg = 2;
        this->hitCont++;
    }
    else
        msg = 3;

    this->mat[x][y][0] = 'X';
    return msg;
}

void Campo::rcvTiro(int x, int y, bool hit)
{
    if(hit){
        this->mat[x][y][1] = 'X';

    }
    else
        this->mat[x][y][1] = 'O';
}

void Campo::showCampo()
{

    std::cout << "--------------------" << std::endl;

    std::cout << " ";
    for(int i = 1; i < 11; i++)
        std::cout << " " << i << " ";
    std::cout << std::endl;

    for(int i = 1; i < 11; i++){
        std::cout << i << " ";
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
    std::cout<<"hitpoint="<<hitCont<<std::endl;
    if(this->desistencia)
        return true;
    if(this->hitCont > 17)
        return true;
    return false;
}

void Campo::surrender()
{
    this->desistencia = true;
}

std::pair<int,int> Campo::atirar()
{
    std::cout << "Posição do Tiro: " << std::endl;
    int x,y;
    std::cin >> x >> y;
    std::pair<int,int> p(x,y);
    return p;
}
