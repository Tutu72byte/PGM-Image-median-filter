#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<cmath>
using namespace std;

void bubbleSort(vector<int> &v) {
    int aux;
    for(int i = 0; i < v.size()-1; i++) {
        for(int j = i+1; j < v.size(); j++) {
            if(v[i] > v[j]) {
                aux = v[i];
                v[i]=v[j];
                v[j]=aux;
            }
        }
    }
}

void merge(vector<int> &v, int l, int mid, int r) {
    int c1 = mid - l + 1;
    int c2 = r - mid;
    vector<int> L(c1), R(c2);
    for(int i = 0; i < c1; i++) {
        L[i] = v[l + i];
    }
    for(int i = 0; i < c2; i++) {
        R[i] = v[mid + 1 + i];
    }
    int i = 0, j = 0, k = l;
    while(i < c1 && j < c2) {
        if(L[i] <= R[j]) {
            v[k++] = L[i++];
        }
        else {
            v[k++] = R[j++];
        }
    }
    while(i < c1) {
        v[k++] = L[i++];
    }
    while(j < c2) {
        v[k++] = R[j++];
    }
}

void mergeSort(vector<int> &v, int l, int r) {
    if(l >= r) return;
    int mid = l + (r - l) / 2;
    mergeSort(v, l, mid);
    mergeSort(v, mid+1, r);
    merge(v, l, mid, r);
}

int median(vector<int> fer, const string &alg) {
    if(alg == "merge") {
        mergeSort(fer, 0, fer.size()-1);
    }
    else if(alg == "bubble") {
        bubbleSort(fer);
    }
    return fer[fer.size()/2];
}

int main() {
    string alg,inFile,outFile;
    int W;
    cin>>alg>>W>>inFile>>outFile;
    // alg = "merge";
    // W = 3;
    // inFile = "C:\\Users\\Laptop\\Downloads\\lena_noise.pgm";
    // outFile = "C:\\Users\\Laptop\\Downloads\\lena_output.pgm";
    ifstream fin(inFile);
    ofstream fout(outFile);
    string identif,x;
    int w,h,maxdim;
    fin>>identif;
    string line;
    fin.ignore();
    while (true) {
        getline(fin, line);
        if(line.size() == 0) continue;
        if(line[0] == '#') continue;
        break;
    }
    stringstream ss(line);
    ss >> w >> h;
    fin>>maxdim;
    int** img = new int*[h];
    for(int i = 0; i < h; i++) {
        img[i] = new int[w];
    }
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            fin>>img[i][j];
        }
    }
    fin.close();
    int** out = new int*[h];
    for (int i = 0; i < h; i++)
        out[i] = new int[w];

    int offset = W / 2;
    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            vector<int>fer;
            for(int dy = -offset; dy <= offset; dy++) {
                for(int dx = -offset; dx <= offset; dx++) {
                    int new_y = y+dy;
                    int new_x = x+dx;
                    if(new_x <0) new_x = 0;
                    if (new_x >= w) new_x = w-1;
                    if (new_y >= h) new_y = h-1;
                    if (new_y < 0) new_y = 0;

                    fer.push_back(img[new_y][new_x]);
                }
            }
            out[y][x] = median(fer, alg);
        }
    }
    fout << "P2\n";
    fout << w << " " << h << "\n";
    fout << maxdim << "\n";

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            fout << out[i][j] << " ";
        }
        fout << "\n";
    }
    fout.close();
    for (int i = 0; i < h; i++) {
        delete[] img[i];
        delete[] out[i];
    }
    delete[] img;
    delete[] out;

    return 0;
}