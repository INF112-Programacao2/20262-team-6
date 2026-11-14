#include "grid.hpp"
#include "planta.hpp"
#include "posicao.hpp"
#include <iostream>

int main(){
    int x = 11;
    Grid mapa (x,x);

    mapa.set_celula(1,4,4);
    
    Posicao p = mapa.get_celula(4,4)->get_position(); 
    std::cout << p.get_x() << " " << p.get_y() << std::endl;
    
    for(int i=0; i < 90 ; i++)
    mapa.get_celula(4,4)->atualizar(&mapa);

        
    for(int i = 0; i < x; i++){
        for(int y = 0; y < x; y++){
            if(mapa.get_celula(i,y)!=0)
                std::cout << "I";
            else std::cout << "-";   
        }
        std::cout << std::endl; 
    }

    return 0;
}
