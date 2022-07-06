/*Versão beta desenvolvida por Thiago Felski Pereira para disciplina de Algoritmos*/
#include <iostream>  // Para conseguir usar inputs e outputs no terminal
#include <windows.h> // Comandos para rodar o programa no Windows
#include <conio.h>   /// Para usar o getch() no Windows
#include <time.h>    // Habilita a função time

// Código feito por: Bruna Pioner, Lucas da Silva, Luiz Triches

using namespace std;

int main()
{
    srand(time(NULL)); // srand irá nos permitir gerar valores aleatórios, e nos permite usar o rand

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    // FIM: COMANDOS PARA QUE O CURSOR NÃO FIQUE PISCANDO NA TELA
    // INÍCIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA
    COORD coord;
    // FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA

    int tecla; // Verifica a tecla pressionada
    int bird_x = 5, bird_y = 10, bird_y_clear;
    int obstaculo_x = 70, obstaculo_y, obstaculo_x_clear;
    int obstaculo2_x = obstaculo_x + 40, obstaculo2_y, obstaculo2_x_clear;
    int pontos_x = 1, pontos_y = 0, pontos = 0;         // Posição do placar e pontuação do jogador
    int vao1 = rand() % 15 , vao2 = rand() % 15 + 4; // Randomiza a posição do vão do 1° e do 2° obstáculo. O +4 é para impedir que o vão seja gerado em um ponto muito extremo do cenário
    int velocidade = 160;                               // Velocidade em que o jogo esta no momento
    bool game_over;                                     // Faz o jogo rodar. False = para | True = continua

    system("cls"); // Limpa a tela do cmd (elimina o rastro)
    cout << "----------------------------------------------------------------------------------------------------------------------";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "----------------------------------------------------------------------------------------------------------------------";
    cout << endl;

    game_over = true; // Definido como True para fazer o jogo funcionar, continuar rodando.

    while (game_over)
    {
        
        // Seta a posição do placar
        coord.X = pontos_x;
        coord.Y = pontos_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "Pontos Atuais:  " << pontos;

        // Pontuação do jogo
        if (bird_x == obstaculo_x + 1 || bird_x == obstaculo2_x + 1) // Incrementa pontuação no jogo ao passar pelos vãos
        {
            pontos = pontos + 1; // Acrescenta +1 ponto

            if (pontos != 0 && pontos % 2 == 0 && velocidade) // A cada 5 pontos feitos, a velocidade é aumentada
            {
                velocidade = velocidade - 15; // A velocidade é aumentada em 15
            }
        }

        // Posição do obstáculo
        obstaculo_y = 1;
        obstaculo2_y = 1;
        while (obstaculo_y < 20 && obstaculo2_y < 20)
        {
            // Remove o rastro do 1° e 2° pilar
            coord.X = obstaculo_x_clear;
            coord.Y = obstaculo_y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout << " ";

            coord.X = obstaculo2_x_clear;
            coord.Y = obstaculo2_y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout << " ";
            // ---------------------------------

            // Posição dos pilares e a posição do vão
            coord.X = obstaculo_x;
            coord.Y = obstaculo_y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

            // Impede que o pássaro atravesse o pilar
            if (obstaculo_y < vao1 - 1 || obstaculo_y > vao1 + 1)
            {
                cout << char(219);
            }
            else
            {
                // Faz o pássaro conseguir passar pelo vão
                cout << " ";
            }
            obstaculo_y++;

            // Posiciona Obstáculo 2
            if (obstaculo2_x < 110)
            {
                coord.X = obstaculo2_x;
                coord.Y = obstaculo2_y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

                // Impede que o pássaro atravesse o pilar
                if (obstaculo2_y < vao2 - 1 || obstaculo2_y > vao2 + 1)
                {
                    cout << char(219);
                }
                else
                {
                    // Faz o pássaro conseguir passar pelo vão
                    cout << " ";
                }
            }
            obstaculo2_y++;
        }

        // Apaga o rastro do movimento dos pilares
        obstaculo_x_clear = obstaculo_x;
        obstaculo2_x_clear = obstaculo2_x;

        // Colisão do 1° pilar
        if (bird_x == obstaculo_x && (bird_y < vao1 - 1 || bird_y > vao1 + 1))
        {
            game_over = false;
        }

        // Colisão do 2° pilar
        else if (bird_x == obstaculo2_x && (bird_y < vao2 - 1 || bird_y > vao2 + 1))
        {
            game_over = false;
        }

        if (bird_y > 20 || bird_y < 0)
        {
            game_over = false;
        }

        // Verifica comando do jogador
        if (kbhit()) // Verifica se uma tecla foi pressionada
        {
            tecla = getch(); // verifica comando do jogador
        }

        // Elimina o rastro do pássaro
        coord.X = bird_x;
        coord.Y = bird_y_clear;
        bird_y_clear = bird_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";

        // Posição do pássaro
        coord.X = bird_x;
        coord.Y = bird_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << char(86);


        // Pássaro sobe 1 pixel ao pressionar a tecla "w"
        if (tecla == 'w')
        {
            bird_y--;

            tecla = '0';
        }
        // PÁSSARO CAI 1 POSIÇÃO SE NÃO FOI PRESSIONADO PARA SUBIR
        else
        {
            bird_y++;
        }

        // Pilares avançam uma posição para esquerda
        obstaculo_x--;
        obstaculo2_x--;

        // Faz os obstáculos voltarem as suas posições iniciais e randomizar a posição do vão com o rand
        if (obstaculo_x < 0)
        {
            obstaculo_x = 110;
            vao1 = rand() % 15 + 4;
        }
        else if (obstaculo2_x < 0)
        {
            obstaculo2_x = 110;
            vao2 = rand() % 15 + 4;
        }

        // Tempo de espera
        Sleep(velocidade);
    }

    return 0;
}
