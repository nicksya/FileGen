//
//  main.cpp
//  Sorting
//
//  Created by Mykyta on 23.04.17.
//  Copyright © 2017 Mykyta Khomenko. All rights reserved.
//
#include <iostream>
#include <random>

#define MEGABYTE 1024*1024
#define GIGABYTE 1024*MEGABYTE
#define FULL 44*GIGABYTE
#define HALF 6*GIGABYTE
#define SHORT 3*GIGABYTE
#define SUPER_SHORT 200*MEGABYTE
#define OUTPUT_FILE "/tmp/data.in"

long long filesize = SUPER_SHORT;

void displayUsage() {
    std::cout << "Recognized parameters are:\n";
    std::cout << "'-t'  - super short file with 200*MEGABYTE size\n";
    std::cout << "'-s'  - short-sized file with 3*GIGABYTE size\n";
    std::cout << "'-h'  - half-sized file with 6*GIGABYTE size\n";
    std::cout << "'-f'  - full-sized file with 44*GIGABYTE size\n";
};

void displayNoParamWarn() {
    std::cout << "No command line parameter or given incorrectly!\n";
    displayUsage();
    std::cout << "Super short mode would be used by default !\n\n";
}

void getMode(int argc, const char * argv[]) {
    if (argc <= 1) {
        displayNoParamWarn();
        return;
    }
    
    std::string str_param = argv[1];
    char c_param = '-';
    if (str_param.length() == 2) {c_param = str_param[1];
        switch (c_param) {
            case 't':
                filesize = SUPER_SHORT;
                break;
            case 's':
                filesize = (long)SHORT;
                break;
            case 'h':
                filesize = (long)HALF;
                break;
            case 'f':
                filesize = (long)FULL;
                break;
            case '?':
                displayUsage();
                exit(EXIT_SUCCESS);
                break;
            default:
                displayNoParamWarn();
                break;
        }
    };
}

void generateFile() {
    std::cout << "Generating file according to the parameters: " << std::endl;
    unsigned long long random_ull; //0 to 18,446,744,073,709,551,615
    short random_str_len = 0;
    
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937_64 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<unsigned long long> dis{}; //constructor call

    std::cout << "Filesize requested : " << filesize << " bytes" << std::endl;
    std::cout << "Generator's min is : " << dis.min() << std::endl;
    std::cout << "Generator's max is : " << dis.max() << std::endl << std::endl;
	std::cout << "Progress";
    
    FILE *out = fopen(OUTPUT_FILE, "w");
    long long int remainingFile = filesize;
    unsigned long long int progress = filesize;
    unsigned long long int progressPercent = filesize / 100;
    for ( ; remainingFile > 0; ) {
        if (remainingFile < progress) {
            std::cout << ".";
            progress -= progressPercent;
        }
        random_ull = dis(gen);
        random_str_len = std::to_string(random_ull).length();
        //std::cout << "Generated random is: " << random_ull << std::endl;
        fprintf(out, "%llu\n", random_ull);
        remainingFile -= random_str_len;
    }
    fclose(out);
    std::cout << "done." << std::endl;
}

int main(int argc, const char * argv[]) {
    
    getMode(argc, argv);
    generateFile();
    return 0;
}
