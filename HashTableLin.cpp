#include "HashTableLin.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iostream>
using namespace std;

HashTableLin::HashTableLin(int maxNum, double load)
{
    size = maxNum / load;
    double d = maxNum / load;
    if (d > size) {
        size++;
    }
    while (!isPrime(size)) {
        size++;
    }
    vector<int> temp(size);
    table = temp;
    numKeys = 0;
    maxKeys = size * load;
    maxLoad = load;

}

void HashTableLin::insert(int n)
{

    if(!isIn(n)){

        
        ++numKeys;
        if(maxKeys < numKeys){rehash();}
        int index = n%size;
        if(table[index]==NULL){table[index] = n;}
        else{
            while(table[index] !=NULL){index=(index+1)%size;}
            table[index] = n;
        }

    }
}
int HashTableLin::isPrime(int n){

    for(int i = 2; i < n; i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}



void HashTableLin::rehash()
{
    size = size* 2 + 1;
    maxKeys = size * maxLoad;
    vector<int> tCopy = table;
    while (!isPrime(size)){size++;}
    numKeys = 0;

    table.resize(0);
    table.resize(size);
    for(int x = 0; x < tCopy.size(); x++){
        if(tCopy[x] != NULL){insert(tCopy[x]);}
    }
}
bool HashTableLin::isIn(int n)
{
    int index = n %size;
    while(table[index] != NULL){
        if(table[index] == n){
            return true;
        }else{
            index = (index+1) % size; //this is the quadratic probe
            if(index==n%size){return false;}
                   
        }
    }
    return false;
}

void HashTableLin::printKeys()
{
    for(int x = 0; x < size; x++){
        if(table[x] != NULL){
            cout<<table[x]<<", ";
        }
    }
}

void HashTableLin::printKeysAndIndexes()
{
    for(int x = 0; x < size; x++){
        if(table[x] != NULL){
            cout<< x << ", " << table[x]<<", ";
        }
    }
}

int HashTableLin::getNumKeys() {
	// TODO, change following code after completing this function
    return numKeys;
}

int HashTableLin::getTableSize() {
	// TODO, change following code after completing this function
    return size;
}

double HashTableLin::getMaxLoadFactor() {
	// TODO, change following code after completing this function
    return maxLoad;
}

int  HashTableLin::probing(int n)
{
    int p = 0;
    if(!isIn(n)){
        
        numKeys++;
        if(numKeys > maxKeys){
            rehash();
        }
        int x = n % size;
        if(table[x] == NULL){
            table[x] = n;
            p++;
        }else{
            while(table[x] != NULL){

                p++;
                x = (x+1)%size;
            }
            table[x] = n;
            
        }

    }
    return p;
}

std::vector<double> HashTableLin::simProbeSuccess()
{
    {
    // TODO, change following code after completing this function
    vector<double> result(9);
    int maximum = 100000; //at least 100k
    int randoms[100000];
    double sum = 0; double probeMean = 0; double ssize = 100000;
    int c = 0; 


    // create random set (n^2)
    for(int x = 0; x< maximum; x++){
        bool in = true;
        int rando;
        while(in){
            in = false;
            rando = (rand()*rand());
            for(int y = 0; y < x; y++){
                if(rando == randoms[y]){
                    in = true;
                    break;
                }
            }
            randoms[x] = rando; 
        }
    }

    for(double l = 0.1; l <= 0.9; l+=.1){
        sum = 0;
        cout<<"\n";
        for(int x = 0; x < 100; x++){
            HashTableLin hT = HashTableLin(maximum, l);
            for(int y = 0; y < ssize; y++){
                sum += (double)hT.probing(randoms[y])/ssize;
            }
        }
        probeMean = sum/100;
        result[c] = probeMean;
        c++;
    }
    return result;
}

// for bonus
std::vector<double> HashTableLin::simProbeUnsuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    return result;
}
