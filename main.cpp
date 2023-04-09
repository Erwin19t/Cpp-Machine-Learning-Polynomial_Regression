/*
Programa de Regresion Lineal

Compilacion: g++ main.cpp -o Ejecutable -std=c++11
Ejecucion: ./Ejecutable
*/

#include <iostream>
#include <unistd.h>
#include <math.h>
#define Alpha 0.0000002

using namespace std;

long double Initial_Theta(int);
long double Evaluate(long double, long double, long double, long double, long double, long double, long double, int);
long double MSE(long double, long double);
long double Grad_MSE(long double, long double, int, int);
long double Relative_Error(long double, long double, long double, long double, long double, long double, long double, long double, long double, long double, long double, long double, long double, long double);

int main(){
    long double Y[5] = {5, 6 , 7, 8, 9};
    long double Y_g[5] = {0};
    long double Theta_ant[7];            
    long double Theta_act[7];
    long double Init_Theta[7];
    long double mse   = 0;
    long double GMSE[7] = {0};
    long double Error = 100;
    int i, j;
    int Counter = 1;
 
    for(i = 0 ; i < 7 ; i++){
        Theta_ant[i] = Initial_Theta(i);
        Theta_act[i] = Theta_ant[i];
        Init_Theta[i] = Theta_act[i];
    }

    while(Error > (1*pow(10,-15))){
        //Se evalua la funcion y se calcula el MSE
        for(i = 0; i < 5; i++){
            Y_g[i] = Evaluate(Theta_act[0], Theta_act[1], Theta_act[2], Theta_act[3], Theta_act[4], Theta_act[5], Theta_act[6], i);
            mse = MSE(Y_g[i], Y[i]) + mse;
        }
        mse = mse/5;

        //Se calcula el Gradiente
        for(j = 0; j < 7; j++){
            for(i = 0; i < 5; i++){
                GMSE[j] = Grad_MSE(Y_g[i], Y[i], i, j) + GMSE[j];
            }
            GMSE[j] = GMSE[j]*2/5;
        }

        //Paso 5: Se calcula el nuevo vector Theta
        for(i = 0 ; i < 7 ; i++){
            Theta_act[i] = Theta_ant[i] - Alpha*GMSE[i];
        }

        //Se calcula el Error
        Error = Relative_Error(Theta_act[0], Theta_act[1], Theta_act[2], Theta_act[3],Theta_act[4], Theta_act[5],Theta_act[6], Theta_ant[0], Theta_ant[1], Theta_ant[2], Theta_ant[3], Theta_ant[4], Theta_ant[5], Theta_ant[6]);

        //Actualizamos el vector theta anterior,
        //aumentamos contador de iteraciones
        //y reseteamos algunas variables
        for(i = 0 ; i < 7 ; i++){
            Theta_ant[i] = Theta_act[i];
            GMSE[i] = 0;
        }
        mse = 0;
        Counter++;
    }

    //Chingo de Impresiones
    cout<<"Iteracion "<<Counter<<endl;
    cout<<"Error Medio Cuadratico = "<<mse<<endl;
    cout<<"Error = "<<Error<<endl;
    cout<<"Alpha = "<<Alpha<<endl;
    cout<<"Pesos deseados = [5 ; 1 ; 0 ; 0 ; 0 ; 0 ; 0]"<<endl;
    cout<<"Pesos iniciales= [";
    for(i = 0; i < 7 ; i++){
        if(i != 6){
            cout<<Init_Theta[i]<<" ; ";
        }
        else{
            cout<<Init_Theta[i];
        }
    }
    cout<<"]"<<endl;
    cout<<"Gradiente del MSE= [";
    for(i = 0; i < 7 ; i++){
        if(i != 6){
            cout<<GMSE[i]<<" ; ";
        }
        else{
            cout<<GMSE[i];
        }
    }
    cout<<"]"<<endl;
    cout<<"Nuevo vector Theta = [";
    for(i = 0; i < 7 ; i++){
        if(i != 6){
            cout<<Theta_act[i]<<" ; ";
        }
        else{
            cout<<Theta_act[i];
        }
    }
    cout<<"]"<<endl;
    for(i = 0 ; i < 5 ; i++){
        cout<<"Y("<<i<<") = "<<Y_g[i]<<endl;
    }
    return 0;
}

//Paso 1: Inicializar los pesos aleatoriamente
long double Initial_Theta(int id){
    long double Theta;
    int Sign;
    srand(id + (int)time(NULL));
    Sign = 1 + rand()%100;
    if(Sign%2 == 0){    //Para genera numeros pseudoaleatorios positivos
        srand(id + (int)time(NULL));
        //Theta = 1 + rand()%9;
        Theta = 1 + ((rand()%(10001))/1000.00f);
    }
    else{               //Para generar numeros pseudoaleatorios negativos
        srand(id + (int)time(NULL));
        Theta = -9 + ((rand()%(-10001))/1000.00f);
    }
    return Theta;
}

//Paso 2: Evaluacioes
long double Evaluate(long double theta_0, long double theta_1,long double theta_2, long double theta_3, long double theta_4, long double theta_5, long double theta_6, int x){
    double Y = 0;
    Y = theta_0 + theta_1*x + theta_2*pow(x,2) + theta_3*pow(x,3) + theta_4*pow(x,4) + theta_5*pow(x,5) + theta_6*pow(x,6);
    return Y;
}

//Paso 3: Calculo de Error Medio Cuadratico
long double MSE(long double y_g, long double y){
    return pow((y_g - y),2);
}

//Paso 4: Calculo del Gradiente del MSE
long double Grad_MSE(long double y_g, long double y, int x, int exp){
    return (y_g - y)*pow(x,exp);
}

//Paso 6: Calculo de Error Relativo (Criterio de Parada)
long double Relative_Error(long double theta_g0, long double theta_g1, long double theta_g2, long double theta_g3, long double theta_g4, long double theta_g5, long double theta_g6, long double theta_0, long double theta_1, long double theta_2, long double theta_3, long double theta_4, long double theta_5, long double theta_6){
    long double Norm_act, Norm_ant, err;
    Norm_act = sqrt(pow(theta_g0, 2) + pow(theta_g1, 2) + pow(theta_g2, 2) + pow(theta_g3, 2) + pow(theta_g4, 2) + pow(theta_g5, 2) + pow(theta_g6, 2));
    Norm_ant = sqrt(pow(theta_0, 2) + pow(theta_1, 2) + pow(theta_2, 2) + pow(theta_3, 2) + pow(theta_4, 2) + pow(theta_5, 2) + pow(theta_6, 2));
    err    = abs(Norm_act - Norm_ant);
    return err;
}