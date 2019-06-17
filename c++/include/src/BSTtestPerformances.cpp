/**
 * @file BSTtestPerformances.cpp
 * @author Francesca Cairoli
 * @date 17 June 2019
 * @brief Source file to test the performances of the BST class.
 */

#include "BST.h"
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <map>
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

int N_max=25000; 

// Test number one:
// Define two BST of int and float respectively and measure the time required to find N different elements in a BST of size N.
// Results are printed on a file. 

template<class T>
void measure_lookups_time(T bst,ofstream& results_file){
        results_file <<"N   total time    time per operation   Log(N)"<<endl;
        for(int j=0;j<N_max;j+=50){
            auto start_timer = chrono::high_resolution_clock::now();
            for(int i=0;i<j;++i){
                bst.find(i);
                }
        auto end_timer = chrono::high_resolution_clock::now();
        auto global_time = chrono::duration_cast<chrono::microseconds>(end_timer-start_timer).count();
        results_file << j << "        " << global_time << "         " << global_time/double(j) << "       " << log2(global_time/double(j)) <<endl;
        }

};

template<class T, typename Y>
void measure_lookups_time_from_vect(T bst,ofstream& results_file, std::vector<Y>& val){
        results_file <<"N   total time    time per operation   Log(N)"<<endl;
        for(int j=0;j<N_max;j+=50){
            auto start_timer = chrono::high_resolution_clock::now();
            for(int i=0;i<j;++i){
                bst.find(val[i]);
            }
            auto end_timer = chrono::high_resolution_clock::now();
            auto global_time = chrono::duration_cast<chrono::microseconds>(end_timer-start_timer).count();
            results_file << j << "        " << global_time << "         " << global_time/double(j) << "       "<< log2(global_time/double(j)) <<endl;
        }

};


void compare_different_types(string type){
	ofstream results_file;
    results_file.open ("performance_different_types"+type+"_1.txt");
	if(type=="int"){
		BST<int,int> bst;
        std::vector<int> val;
        for(int i=0; i<N_max; ++i){
            int x = ( rand() / RAND_MAX) * (100 - 1) + 1;
            pair<int, int> pair{x,x};
            bst.insert(pair);
            val.push_back(x);
        }
		cout<<"Accessing Elements for int type."<<endl;
		results_file<<"Accessing Elements for int type."<<endl;
		measure_lookups_time_from_vect(bst, results_file, val);
        results_file.close();
	}
	if(type=="double"){
        BST<double,double> bst;
        std::vector<double> val;
        for(int i=0; i<N_max; ++i){
			double x = ((double) rand() / RAND_MAX) * (100. - 1.) + 1.;
			pair<double, double> pair{x,x};
            bst.insert(pair);
			val.push_back(x);
        }
        cout << "Accessing Elements for double type." << endl;
        results_file<<"Accessing Elements for double type."<<endl;
        measure_lookups_time_from_vect(bst, results_file, val);
		results_file.close();
    }

};

// Test number two:
// Compare the performances of unbalanced BST, balanced BST, map and unordered_map.

void compare_bst_map(){
	ofstream unbalanced_results_file;
    unbalanced_results_file.open ("performance_unbalanced.txt");
    BST<int,int> bst;
    for(int i=0;i<N_max;++i){
      	pair<int, int> pair{i,i};
        bst.insert(pair);
                }
	measure_lookups_time(bst, unbalanced_results_file);
    unbalanced_results_file.close();

	ofstream balanced_results_file;
	balanced_results_file.open ("performance_balanced.txt");
	bst.balance();
	measure_lookups_time(bst,balanced_results_file);
	balanced_results_file.close();

	map<int,int> bst_map;
	ofstream map_results_file;
    map_results_file.open ("performance_map.txt");
	for(int i=0;i<N_max;++i){
        pair<int, int> pair{i,i};
        bst_map.insert(pair);
    }
	measure_lookups_time(bst_map, map_results_file);
    map_results_file.close();

	unordered_map<int,int> bst_umap;
    ofstream umap_results_file;
    umap_results_file.open ("performance_unordered_map.txt");
    for(int i=0;i<N_max;++i){
        pair<int, int> pair{i,i};
        bst_umap.insert(pair);
    }
	measure_lookups_time(bst_umap, umap_results_file);
    umap_results_file.close();
};

int main(){
	
	compare_different_types("int");
	compare_different_types("double");
	compare_bst_map();
	return 0;
};