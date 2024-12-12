#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

int compare_prefix_suffix(string a, string b, int n) {
    if (a.substr(0, n) == b.substr(b.size() - n, n)) {
        return n;
    } else {
        return 0;
    }
}

int gen_state_mach(string a, string b) {
    int max_match = 0; 
    
    for (int n = min(a.size(), b.size()); n > 0; --n) {
        int match_length = compare_prefix_suffix(a, b, n);
        if (match_length > 0) {
            max_match = max(max_match, match_length);
        }
    }
    return max_match;
}


uint32_t bin_rep_2(const string key) {
    uint32_t temp = 0b00000000000000000000000000000000;
    for (char c : key) {
        temp |= (1 << (c - 'a')); 
    }
    return temp;
}

string masking(uint32_t binar){
    string temp;
    for(int i=0; i<26;i++){
        if (binar & (1 << i)) {
            temp += ('a' + i); 
        }
    }
    return temp;
}

int** gen_arr(int rows, int col){
    int** arr = new int*[rows];
    for (int i = 0; i < rows; i++)
        arr[i] = new int[col];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < col; j++) {
            arr[i][j] = 0;
        }
    }

    return arr;
}

int mask_index(string mask, char c){
    int in=0;

    for(int i=0; i<mask.length(); i++){
        if(c == mask[i]){
            return in;
        }
        in++;
    }

    return in;
}

int main() {
    string word1 = "ababaca";
    string mask = masking(bin_rep_2(word1));
    string words = "abababacaba";
    //cout<< mask<<endl;

    int rows = word1.length()+1;
    int col = mask.length();

    int** arr = gen_arr(rows, col);

    string key;
    string temp;

    //generowanie macierzy stanu maszyny
    for(int j=0; j<rows;j++){
        key.push_back(word1[j]);
        for(int i=0; i<col; i++){
            temp.push_back(mask[i]);
            arr[j][i] = gen_state_mach(key, temp);
            temp.pop_back();
        }
        temp = key;
    }

    //wypisywanie stanu maszyny
    for(int i=0; i<rows; i++){
        for(int j=0; j<col; j++){
            cout<<arr[i][j]<<", ";
        }
        cout<<"\n";
    }
    
    int* tab = new int(rows+1);
    for(int i=0; i<rows+1;i++){
        tab[i] = 0;
    }

    for(int i=1; i<words.length()+1;i++){
        char c = words[i-1];
        //cout<<c<<"\n";
        int index = mask_index(mask, c);
        int index2 = tab[i-1];
        
        tab[i] = arr[index2][index];

        /*
        //wypisywanie kolejnej iteracji
        cout<<"   "<<c<<"\n";
        cout<<index2<<", "<<arr[index2][index]<<"\n";
        cout<<"\n";
        */
    }

    for(int i =0; i<words.length()+1;i++){
        cout<<tab[i]<<", ";
    }

    for (int i = 0; i < rows; i++)
        delete[] arr[i];

    delete[] arr;
    return 0;
}
