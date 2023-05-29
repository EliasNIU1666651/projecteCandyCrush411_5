#include "Joc.hpp"
#include "InfoJoc.h"
#include "GraphicManager.h"


void Joc::inicialitza(const string& nomFitxer)
{
   
  
    m_partida.inicialitza(nomFitxer);
    m_estat = ESTAT_JOC_ESPERA;
    GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, CELL_INIT_X, CELL_INIT_Y, false);

    
}


void Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus, double deltaTime) //IMPORTANT, ENTRA A LA FUNCIO CADA "MICROSEGON", PER LO QUE POSAR VARIABLES DE CONTROL 
{
    GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, CELL_INIT_X, CELL_INIT_Y, false);

    Posicio PosX1; //primera coordenada moviment
    Posicio PosX2; //segona coordenada moviment
    int posX = 0; //lloc caramel
    int posY = 0;

    ColorCandy caramel;

    bool controlPrimerClick = true; //click per primer cop
    bool controlSegonClick = true;
    bool controlMoviment = true;

    while (posX < 10)
    {
        posY = 0;
        while (posY < 10)
        {
            caramel = m_partida.getTauler().getTauler(posY, posX).getColor();
            switch (caramel)
            {

            case VERD:
                GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_GREEN, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);
                break;
            case LILA:
                GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PURPLE, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);
                break;
            case BLAU:
                GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);
                break;
            case TARONJA:
                GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ORANGE, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);
                break;
            case VERMELL:
                GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_RED, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);
                break;
            case GROC:
                GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_YELLOW, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);
                break;
            }

            posY++;
        }
        posX++;
    }

    string msg = "X: " + to_string(mousePosX) + ", Y: " + to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, FINAL_INIT_X, FINAL_INIT_Y, 1.0, msg);


    switch (m_estat)
    {
    case ESTAT_JOC_ESPERA:
        if ((mouseStatus) && (mousePosX < 550) && (mousePosY < 650) && (mousePosX > 50) && (mousePosY > 150)) //limits tauler en px, per conversió a m_tauler mirar PosX1 o PosX2
        {
            m_estat = ESTAT_JOC_INTERCANVI;
        }
        break;
    case ESTAT_JOC_INTERCANVI:
        
        if (mouseStatus)
        {
            if (controlPrimerClick)
            {

                PosX1.setColumna((mousePosY / 50) - 3); //offset de 3 pq mousePos del tablero empieza en 150, cada celda de 50
                PosX1.setFila((mousePosX / 50) - 1); //offset de 1 pq mousePos del tablero empieza en 50, cada celda de 50
                
                controlPrimerClick = false;
            }
         
            

        }
        else
        {
            if (!controlPrimerClick) //ja tenim les coordenades del primer caramel
            {
                if ((controlSegonClick)&&(PosX1.getColumna()!= (mousePosY / 50) - 3)&&(PosX1.getFila()!= (mousePosX / 50) - 1)) //mateixa cel·la
                {
                    PosX2.setColumna((mousePosY / 50) - 3);
                    PosX2.setFila((mousePosX / 50) - 1);
                    controlSegonClick = false;
                }
                else
                {
                    controlPrimerClick = true;
                }

                if (!controlSegonClick) //ja tenim segona coordenada
                {
                    // controlMoviment = m_partida.fesMoviment(PosX1, PosX2); a modificar amb les teves funcions, nms posar la funció que detecta si es vàlid
                    // Al fer la funció moviment, el desplçament s'hauria de fer directament,ja que entra al case d'adalt de tot.
                    // Sinó quan m'ho tornis a pasar, será qüestió de posar el if(deltatime>time){continuamoviment; "funció teva"} i poc més.
                    if (controlMoviment) //ha determinar amb les teves funcions 
                    {
                        m_estat = ESTAT_JOC_MOVIMENTS;
                    }
                    else //no vàlid, ha de tornar a validar clicks
                    {
                        controlPrimerClick = true;
                        controlSegonClick = true;
                        m_estat = ESTAT_JOC_ESPERA;
                    }
                }
              

            }
            else
            {
                m_estat = ESTAT_JOC_ESPERA;
            }
        }
       
      
        break;
    case ESTAT_JOC_MOVIMENTS:
        //implementar amb les teves funcions
        //implementar l'operator == per a buscar si s'ha assolit l'objectiu, a partir del teu codi
        break;
    case ESTAT_FINAL:
        
        break;
    }

}



   // Afegir l'include de GraphicManager --> #include "GraphicManager.h"
   // Fer la crida de dibuixar un sprite --> GraphicManager::getInstance()->drawSprite(image, posX, posY, centered);
   //	    Per començar podem cridar el drawSprite amb els params --> 
   //          (IMAGE_BACKGROUND,0,0, false) i 
   //          (IMAGE_BOARD, CELL_INIT_X, CELL_INIT_Y, false)



   // Dibuixar a pantalla el gràfic amb el tauler i un caramel blau centrat a la posició (2,2) del tauler


   //GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);





   // Dibuixar un caramel blau centrat a la posició (2,2) del tauler només si estem pressionant el botó esquerre del mouse
   // Si no l'estem pressionant només s'ha de dibuixar el tauler sense el caramel

   //if (mouseStatus)
   //{
   //    GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);
   //}



   // Si estem pressionant el botó esquerre del mouse, dibuixar un caramel blau centrat a la posició del tauler on tenim el mouse
   // Si no l'estem pressionant només s'ha de dibuixar el tauler sense el caramel

   //if (mouseStatus)
   //{
    //   GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE, CELL_INIT_X + (mousePosX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (mousePosY * CELL_H) + (CELL_H / 2), true);
   //}


   // Dibuixar un caramel blau a la posicio (2,2) del tauler. Eliminar-lo quan hagi passat mig segon. 
   // Tornar-lo a dibuixar al cap de mig segon i anar repetint el cicle eliminar/dibuixar cada mig segon

   //m_temps += deltaTime;
   //if (m_temps > 0.5)
   //{
     //  m_visible = !m_visible;
       //m_temps = 0.0;
   //}
    //if (m_visible)
    //   GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BLUE, CELL_INIT_X + (posX * CELL_W) + (CELL_W / 2), CELL_INIT_Y + (posY * CELL_H) + (CELL_H / 2), true);


   
    //Imprimir les coordenades de la posició actual del ratolí a sota del tauler
    //string msg = "X: " + to_string(mousePosX) + ", Y: " + to_string(mousePosY);
    //GraphicManager::getInstance()->drawFont(FONT_WHITE_30, FINAL_INIT_X, FINAL_INIT_Y, 1.0, msg);
