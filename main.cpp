#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int N = 20;


void WczytajLabirynt(int Lab[][N]) {
    string s;
    ifstream we("labirynt.txt");

    for (int i = 0; i < N; i++) {
        we >> s;
        for (int j = 0; j < N; j++) {
            if (s[j] == 'X')
                Lab[i][j] = -1;
            else
                Lab[i][j] = 0;
        }
    }

    we.close();
}


bool Droga(int Lab[][N], int w, int k, int x, int &w1, int &k1) {
    Lab[w][k] = x;


    if (w == 0 || w == N - 1 || k == 0 || k == N - 1) {
        w1 = w;
        k1 = k;
        return true;
    }


    if (w > 0 && Lab[w - 1][k] == 0 && Droga(Lab, w - 1, k, x + 1, w1, k1)) return true;
    if (w < N - 1 && Lab[w + 1][k] == 0 && Droga(Lab, w + 1, k, x + 1, w1, k1)) return true;
    if (k > 0 && Lab[w][k - 1] == 0 && Droga(Lab, w, k - 1, x + 1, w1, k1)) return true;
    if (k < N - 1 && Lab[w][k + 1] == 0 && Droga(Lab, w, k + 1, x + 1, w1, k1)) return true;

    return false;
}


void OznaczDroge(int Lab[][N], int w, int k) {
    int x = Lab[w][k];
    Lab[w][k] = -2;

    while (x > 1) {
        x--;
        if (w > 0 && Lab[w - 1][k] == x) w--;
        else if (w < N - 1 && Lab[w + 1][k] == x) w++;
        else if (k > 0 && Lab[w][k - 1] == x) k--;
        else k++;
        Lab[w][k] = -2;
    }
}

void WypiszLabirynt(int Lab[][N]) {
    cout << "   ";

    for (int j = 0; j < N; j++) {
        cout << setw(3) << j;
    }
    cout << endl;

    for (int i = 0; i < N; i++) {
        cout << setw(3) << i;
        for (int j = 0; j < N; j++) {
            if (Lab[i][j] == -1) {
                cout << setw(3) << "X";
            } else if (Lab[i][j] == -2) {
                cout << setw(3) << "D";
            } else {
                cout << setw(3) << " ";
            }
        }
        cout << endl;
    }
}




int main() {
    int Lab[N][N];
    int w, k;
    int w1, k1;


    WczytajLabirynt(Lab);


    cout << "Podaj w i k-" << endl;
    cout << "w = ";
    cin >> w;
    cout << "k = ";
    cin >> k;

    if (Droga(Lab, w, k, 1, w1, k1)) {
        OznaczDroge(Lab, w1, k1);
        WypiszLabirynt(Lab);
    } else {
        cout << "Nie ma drogi" << endl;
    }

    return 0;
}
