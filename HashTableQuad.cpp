#include "HashTableQuad.h"
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

HashTableQuad::HashTableQuad(int maxNum, double load)//n^2 time, constant space
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

bool HashTableQuad::isPrime(int n){ 
    for(int i = 2; i < n; i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}

void HashTableQuad::insert(int n) //O(n^2) rehash O(n) otherwise
{
    int c = 1; 
    if(!isIn(n)){

        int index = n % size;
        if(table[index]==NULL){
            table[index] = n;
            ++numKeys;
        }else{
            while(table[index] != NULL){
                index = (n%size+c*c)%size; //quadratic probe here as well
                if(c==size){return;}
                c++;

            }
            numKeys++;
            table[index] = n;

        }
    }
    if (maxKeys < numKeys){rehash();}

}

void HashTableQuad::rehash()// n^2
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

bool HashTableQuad::isIn(int n) //n 
{
    int c = 1;
    int index = n %size;
    while(table[index] != NULL){
        if(table[index] == n){
            return true;
        }else{
            index = (n%size + (c*c)) % size; //this is the quadratic probe
            if(c==size){return false;}
            ++c;       
        }
    }
    return false;
}

void HashTableQuad::printKeys() //n time
{
    for(int x = 0; x < size; x++){
        if(table[x] != NULL){
            cout<<table[x]<<", ";
        }
    }
}

void HashTableQuad::printKeysAndIndexes() // n time
{
    for(int x = 0; x < size; x++){
        if(table[x] != NULL){
            cout<< x << ", " << table[x]<<", ";
        }
    }
}

int HashTableQuad::getNumKeys() { //1 time
	// TODO, change following code after completing this function
    return numKeys;
}

int HashTableQuad::getTableSize() {//1 time
	// TODO, change following code after completing this function
    return size;
}

double HashTableQuad::getMaxLoadFactor() {// 1 time
	// TODO, change following code after completing this function
    return maxLoad;
}

int  HashTableQuad::insertCount(int n) //O(n^2) O(n) otherwise
{
    int p = 0;int c = 1;
    if(!isIn(n)){
        
        int x = n%size;
        if(table[x] == NULL){
            table[x] = n;
            p++; numKeys++;
        }else{
            while(table[x] != NULL){
                x = (n%size+c*c)%size;
                p++;
                if(c==size){return 0;}
                c++;
            }
            table[x] = n;
            p++; numKeys++;
        }
        if(numKeys > maxKeys){
            rehash();
        }
    }
    return p;
}


std::vector<double> HashTableQuad::simProbeSuccess()

{
    
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
        for(int x = 0; x < 200; x++){
            HashTableQuad hT = HashTableQuad(maximum, l);
            for(int y = 0; y < ssize; y++){
                sum += (double)hT.insertCount(randoms[y])/ssize;
            }
        }
        probeMean = sum/200;
        result[c] = probeMean;
        c++;
    }
    return result;
}
