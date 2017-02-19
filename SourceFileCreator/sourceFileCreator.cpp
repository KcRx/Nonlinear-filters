/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Tomek
 *
 * Created on 19 lutego 2017, 13:29
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <complex>

/*
 * 
 */
void addPreambule( std::complex<float> *complex, int size, int sign){
    for(int index = 0; index < size; index++, sign++){       
        if(index % 8 == 4){
            complex[sign] = {1,0};
        }else{
            complex[sign] = {0,0};
        }
    }
}

void addPayload( std::complex<float> *complex, int size, int sign){
    for(int index = 0; index < size; index++, sign++){  
        int real = std::rand() % 2;
        int imag = std::rand() % 2;
        complex[sign] = {real,imag};
    }
}

int main(int argc, char* argv){ 
    int numberOfFrames = 5;
    int preambuleSize = 64;
    int payloadSize = 1500;
    int numberOfSigns = (payloadSize + preambuleSize) * numberOfFrames;  
    std::complex<float> complex[numberOfSigns]; 
    
    srand( time( NULL ) );
    int sign = 0;
    for(int frame = 0; frame < numberOfFrames; frame++){       
        addPreambule(complex, preambuleSize, sign);
        sign += preambuleSize;
        addPayload(complex, payloadSize, sign);
        sign += payloadSize;
    }
        
    std::ofstream stream("source.bin", std::ios::binary);    
    stream.write(reinterpret_cast<const char*>(&complex), sizeof complex);   
}