#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
void ler_arquivo();
int pulo=0;
char mapa[15][156];
char jogador=206;
void imprimir_arquivo();
void movimentacao(int* x,int* y);
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s \ on line %d\n", __FILE__, GetLastError(), api, __LINE__);}
int main(){
	system("MODE CON RATE=300 DELAY=0");
	system("mode con cols=155 lines=15");
	ler_arquivo();
	mapa[13][1] = jogador;
	int jogadorX=1;
	int jogadorY=13;
	int* x = &jogadorX;
	int* y = &jogadorY;
	while(1<2){
		fflush(stdin);
		if(kbhit!=0||pulo>0){
			imprimir_arquivo();
            fflush(stdin);
            movimentacao(x,y);
            Sleep(33);
		}

	}
}
void cls( HANDLE hConsole )
 {
    COORD coordScreen = { 0, 0 };    /* here's where we'll home the
                                        cursor */
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
    DWORD dwConSize;                 /* number of character cells in
                                        the current buffer */

    /* get the number of character cells in the current buffer */

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    PERR( bSuccess, "GetConsoleScreenBufferInfo" );
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    /* fill the entire screen with blanks */

    bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
       dwConSize, coordScreen, &cCharsWritten );
    PERR( bSuccess, "FillConsoleOutputCharacter" );

    /* get the current text attribute */

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    PERR( bSuccess, "ConsoleScreenBufferInfo" );

    /* now set the buffer's attributes accordingly */

    bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
       dwConSize, coordScreen, &cCharsWritten );
    PERR( bSuccess, "FillConsoleOutputAttribute" );

    /* put the cursor at (0, 0) */

    bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
    PERR( bSuccess, "SetConsoleCursorPosition" );
    return;
 }
void ler_arquivo(){
		FILE *arq;
	int c;
	arq = fopen("mapa.txt", "rt");
		if (arq == NULL)  // Se houve erro na abertura
	  {
	     printf("Problemas na abertura do arquivo\n");
	     system("pause");
	     system("mode con cols=153 lines=19");
	     return;
	  }

		while(!feof(arq)){
            for(int i=0;i<15;i++){
            	for(int j=0;j<153;j++){

					c = (int) fgetc(arq);

					if(c == '1'){
            			c = 219;
            		}

					mapa[i][j] = c;
            	}
	        }
		}
	fclose(arq);
}
void imprimir_arquivo(){
	int j=0,i=0;
//	system("cls");
cls(GetStdHandle (STD_OUTPUT_HANDLE));
	for(i=0;i<15;i++){
		if(i==0){
			printf("");
		}
//			printf("\r%s",mapa[i]);
WriteConsole (GetStdHandle (STD_OUTPUT_HANDLE), mapa[i], strlen (mapa[i]), NULL, NULL);
	}
printf("\0\0\0\0");
}
void dirPuloQueda(int* x,int* y){
					//se tiver apertado pra direita
				if(GetAsyncKeyState('D')!=0){
					if( (mapa[*y][*x+1]==' ') && (*x+1 < 153) ){
						mapa[*y][*x]=' ';
						*x+=1;
						mapa[*y][*x] = 206;
					}
				}
				//se tiver apertado pra esquerda
				if(GetAsyncKeyState('A')!=0){
					if( (mapa[*y][*x-1]==' ') && (*x-1 > 0) ){
						mapa[*y][*x]=' ';
						*x-=1;
						mapa[*y][*x] = 206;
					}
				}
}
void colisao(int dir,int* x,int* y){
	//Esquerda -1, Direita 1, Cima 2, Baixo -2
	//DIREITA
	if(dir==1){
		if( (mapa[*y][*x+1]==' ') && (*x+1 < 153) ){
			mapa[*y][*x]=' ';
			*x+=1;
			mapa[*y][*x] = 206;

		}
	}
	//ESQUERDA
		if(dir==-1){
			if(mapa[*y][*x-1]==' ' && *x-1 >0){
				mapa[*y][*x]=' ';
				*x-=1;
				mapa[*y][*x] = 206;
			}
	}
	//CIMA
		if(dir==2){
			if(mapa[*y-1][*x]==' ' && *y-1 > 0 &&  mapa[*y+1][*x] !=' '){
                pulo=0;
                while(pulo < 4){
                    mapa[*y][*x]=' ';
                    *y-=1;
                    dirPuloQueda(x,y);
                    mapa[*y][*x] = 206;
                    pulo++;
                    imprimir_arquivo();
                    Sleep(50);
                }
			}
	}
	//BAIXO
		if(dir==-2){
			if(mapa[*y+1][*x]==' ' && *y+1 < 14){
				mapa[*y][*x]=' ';
				*y+=1;
				mapa[*y][*x] = 206;
				dirPuloQueda(x,y);
			}
	}
}
void movimentacao(int* x,int* y){
//Queda
    while(mapa[*y+1][*x] == ' '){
        imprimir_arquivo();
		Sleep(50);
		colisao(-2,x,y);
		imprimir_arquivo();
		Sleep(50);
    }
	if(GetAsyncKeyState('D')!=0){
        	colisao(1,x,y);
	}
	if(GetAsyncKeyState('A')!=0){
        	colisao(-1,x,y);
	}
	if(GetAsyncKeyState('S')!=0){
        	colisao(-2,x,y);
	}
	if(GetAsyncKeyState('W')!=0){
        	colisao(2,x,y);
	}

	return;
}
