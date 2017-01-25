#include <iostream>
#include<fstream>
#include <string>
#include <time.h>
#include <ctime>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <math.h>
using namespace std;

int  HorowitzEtSahni(float *P, int W, float *w, int N ){
Step0:
    float* R;
    R = new float[N+1];

   /*cout<<"p=";
    for(int i=1; i<=N;i++){
        cout<<P[i]<<" ";
        }cout<<endl;*/


  /*  cout<<"W=";
    for(int i=1; i<=N;i++){
    cout<<w[i]<<" ";
    }cout<<endl;*/

    for(int i = 1; i <= N; i++){
        R[i] = (P[i]/w[i]);
    }


  /*  cout<<"pi/wi :"<<endl;
    for(int i=1; i<=N;i++){
    cout<<R[i]<<" ";
   }cout<<endl;
*/
    cout<<"je fait une copie du R initial"<<endl;
    float* R0;
    R0 = new float[N+1];
    for(int i = 1; i <= N; i++){
        R0[i] = R[i];
    }
    cout<<endl;

    /*cout<<"R0 :"<<endl;
    for(int i=1; i<=N;i++){
    cout<<R0[i]<<" ";
   }cout<<endl;*/



//cout<<"pour le tri pi/wi >>> j'utilise l'algorithme de tri par selection "<<endl;
    for(int i=1;i<=N-1;i++){
        int m = i;
        for(int j=i+1;j<=N;j++){
            if(R[j]>R[m]){
                m = j;
                float temp;
                temp = R[m];
                R[m] = R[i];
                R[i] = temp;
                m = i;
            }
        }
    }

    cout<<"le tris par ordre decroissant est: ";
    for(int i=1;i<=N;i++){
        cout<<R[i]<<" - ";
    }
    cout<<endl;

    int* ptri;
    ptri= new int[N+1];
    int* wtri;
    wtri= new int[N+1];
    //affectation
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            if(R[i]==R0[j]){
                ptri[i]=P[j];
                wtri[i]=w[j];
            }
        }
    }
    //Affichage des tableaux trié
    cout<<"ptri"<<endl;
    for(int i=1;i<=N;i++){
      cout<<ptri[i]<<" ";
    } 
    cout<<endl;
    cout<<"wtri= "<<endl;
    for(int i=1;i<=N;i++){
        cout<<wtri[i]<<" ";
    }
    cout<<endl;

//INITIALISATION
Step1:
cout<<"\n********** ON RENTRE DANS STEP 1 \n";

    int i = 1;
    int C = W;
    int z = 0;
    int INC = 0;
    float UB=10e9;

    int * xopt;
    float PLopt=0;
    xopt =new int[N+1];
    for(int k=1;k<=N;k++){
        xopt[k]=0;
    }

    float * x;
    x =new float[N+1];
    for(int k=1;k<=N;k++){
        x[k] = 0;
    }

//Calcul de la borne
Step2:
cout<<"\n********** ON RENTRE DANS STEP 2 \n";
    float PL = 0;
    UB = z+PL;
    int WSAC = 0;
    double Wrest;
    for( i ; i <=N ; i++){
        if( wtri[i] <= C) {
            WSAC = WSAC + wtri[i];
            C = C - wtri[i] ;
            x[i]=1;
            PL = PL +ptri[i];
            cout<<"iteration "<<i<<endl;
            cout<<"WSAC: "<<WSAC<<"\t";
            cout<<"c: "<<C<<"\t";
            cout<<"pl:"<<PL<<endl;
         }
         else{
             cout<<"ici : "<<endl;
             WSAC=WSAC+C;
             cout<<"Wsac "<<WSAC<<" \t";
             if( WSAC <= C){
                 x[i] = float(C) / wtri[i];
                 PL  = PL+P[i]*x[i];
                 cout<<"x "<<x[i]<<"\t";
                 cout<<"PL :"<<PL<<endl;
             }else{
                 for(int j=i+1; j<=N;j++){
                    x[j]=0;
                }
            }
        }
    }
    cout<<endl<<"la solution temporaire : ";
    for(int k=1;k<=N;k++){
        cout<<x[k]<<" ";
    }

    if (PLopt < PL){
        PLopt=PL;
        for(int k=1;k<=N;k++){
            xopt[k]=x[k];
        }
    }


    if( UB <= INC ){ goto Step6;}

Step3:
cout<<"\n********** ON RENTRE DANS STEP 3 \n";

    while(C >wtri[i]){
        x[i] = 1;
        z = z+ptri[i];
        C = C-wtri[i];

        if(i<N){
            i++;
        }else{ break; }
    }

Step4:
cout<<"\n********** ON RENTRE DANS STEP 4 \n";

    if( i<N ){
        x[i] = 0; 
        i++;
        goto Step2;
    }

Step5:
cout<<"\n********** ON RENTRE DANS STEP 5 \n";
     if(i==N){
         if( z > INC){
             for(int k=1; k<=N; k++){
                xopt[k] = x[k];
                INC = z ;
            }
        }
     }

Step6:
cout<<"\n********** ON RENTRE DANS STEP 6 \n";
     if(i>=N){
         x[N] = 0;
         z = z - ptri[N];
         C = C + wtri[N];
         i--;
    }
    while(x[i]==0 && i>0){
        i--;
    }
   if (i==0)  {goto Step7;}

    x[i] = 0;
    z = z - ptri[i];
    C = C + wtri[i];
    i++;
    goto Step2;

Step7:
    cout<<"c'est fini"<<endl;
    cout<<"La bonne solution est : ";
    for(int k=1;k<=N;k++){
        cout<<xopt[k]<<" ";
    }
    cout<<"\tSon Profil : "<<PLopt<<endl;
} //fin de la fct


int main(){
    clock_t debut;
    string S ;
    debut = clock ();
    cout<<"Entrer le nom du fichier"<<endl;
    cin>>S;
     ifstream fichier ( S.c_str() ,ios::in);
    if(fichier.fail())
        cout<<"le fichier n'existe pas "<<endl ;

    else
    {

        int W;
        fichier>>W>>ws;
        cout<<"W:"<<W<<endl;
        int N;
        fichier>>N>>ws;
        cout<<"N:"<<N<<endl;
        float* P;
        P = new float[N];

        float * w;
        w = new float[N];

        float* R;
        R = new float[N];

        for(int i=1; i<=N;i++){
         fichier>>P[i]>>w[i]>>ws;
        }

        int point=HorowitzEtSahni(P,W,w,N);
        
 
       printf ("Temps consommé : %f\n", (double)(clock () - debut) / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;

}
}
