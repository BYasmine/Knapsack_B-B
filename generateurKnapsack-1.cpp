#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include<cstdlib>
#include<knapsack.cpp>
using namespace std;

int main()
{

  srand(time(NULL));
  
  int N,W,k;
  cout << "Choisissez N et W: " << endl;
  cin >> N >> W;
  cout << "Combien d'instances voulez-vous generer ?" << endl;
  cin >> k;

  for (int s = 1; s <= k ; ++s){

   // string nom = to_string(N) + "_" + to_string(W) + "_" + to_string(s) + ".txt";
    
    string nom="data.txt";
  
    ofstream of(nom.c_str(), ios::out);
    of << W << endl << N << endl;
  
    for (int i = 0 ; i < N ; ++i)
      {
	int w = (rand() % (40 - 5) + 5) * W/100;
	int p = (rand() % (220 - 80) + 80) * w/100;
	of << p << " " << w << endl;
      }
    of.close();
  }






  
  return 0;
}
