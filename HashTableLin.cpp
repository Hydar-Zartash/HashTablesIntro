#include "HashTableLin.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

HashTableLin::HashTableLin(int maxNum, double load) //O(n^2) time, O(1) space
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

void HashTableLin::insert(int n) //O(n^2) time (rehash) O(n) otherwise, O(1) space
{
    
    if(!isIn(n)){

        
        ++numKeys;
        if(maxKeys < numKeys){rehash();} // only n^2 if rehashing 
        int index = n%size;
        if(table[index]==NULL){table[index] = n;}
        else{
            while(table[index] !=NULL){index=(index+1)%size;}
            table[index] = n;
        }

    }
}
int HashTableLin::isPrime(int n){////O(n) time, O(1) space

    for(int i = 2; i < n; i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}



void HashTableLin::rehash() //O(n^2) time, O(1) space
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
bool HashTableLin::isIn(int n) //O(n) WORST CASE time, O(1) space
{
    int index = n %size;//
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

void HashTableLin::printKeys()//O(n) time, O(1) space
{
    for(int x = 0; x < size; x++){
        if(table[x] != NULL){
            cout<<table[x]<<", ";
        }
    }
}

void HashTableLin::printKeysAndIndexes()//O(n) time, O(1) space
{
    for(int x = 0; x < size; x++){
        if(table[x] != NULL){
            cout<< x << ", " << table[x]<<", ";
        }
    }
}

int HashTableLin::getNumKeys() {//O(1) time, O(1) space
	// TODO, change following code after completing this function
    return numKeys;
}

int HashTableLin::getTableSize() {//O(1) time, O(1) space
	// TODO, change following code after completing this function
    return size;
}

double HashTableLin::getMaxLoadFactor() {//O(1) time, O(1) space
	// TODO, change following code after completing this function
    return maxLoad;
}

int  HashTableLin::insertCount(int n)////O(n^2) time, O(1) space
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
                x = (x+1)%size;
                p++;

            }
            table[x] = n;
            p++;
            
        }

    }
    return p;
}

std::vector<double> HashTableLin::simProbeSuccess()//

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
        for(int x = 0; x < 100; x++){
            HashTableLin hT = HashTableLin(maximum, l);
            for(int y = 0; y < ssize; y++){
                sum += (double)hT.insertCount(randoms[y])/ssize;
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
