/******************************************************************************
Author: CJ Kim
Date: 3/3/2020
Title: Find Fibonacci Number with Index using Memoization
Explain: Input: 6
         Output: 8
*******************************************************************************/

#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>

using namespace std;

unordered_map<int, unsigned long long> Cache;

unsigned long long FindRecursion(int index){
    if(index == 0 || index == 1) return 1;

    return FindRecursion(index - 1) + FindRecursion(index - 2);
}

unsigned long long FindFibonaaci(int index){
    // If I have the number for this index in "Cache" (hashmap),
    // then return that instead of calculating again.
    if(Cache.find(index) != Cache.end()){
        return Cache[index];
    }

    // If I have the previous two numbers than just add them.
    if(index > 2){
        if(Cache.find(index - 1) != Cache.end()){
            if(Cache.find(index - 2) != Cache.end()){
                // Make sure to save it into cache first.
                Cache[index] = Cache[index - 1] + Cache[index - 2];
                return Cache[index];
            }
        }
    }

    // If not in cache, just solve it normal way.
    Cache[index] = FindRecursion(index);
    return Cache[index];
}


void Tester(const int TestNum, const string Memo, int input, vector<unsigned long long> const& output){
    cout << "#" << TestNum << "\t" << Memo << endl;
    
    cout << "Without Memoization\t";

    auto start = chrono::high_resolution_clock::now();

    bool Correct = true;
    for(int i = 0; i < output.size(); i ++){
        unsigned long long fibo = FindRecursion(i);
        if(output[i] != fibo){
            Correct = false;
            break;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start); 
    
    cout << duration.count() << " ms\t"; 

    if(Correct){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
    
    cout << "With Memoization\t";
    Cache.clear(); // Make sure cache is cleared for each test.

    start = chrono::high_resolution_clock::now();

    Correct = true;
    for(int i = 0; i < output.size(); i ++){
        unsigned long long fibo = FindFibonaaci(i);
        if(output[i] != fibo){
            Correct = false;
            break;
        }
    }

    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start); 
    
    cout << duration.count() << " ms\t"; 

    if(Correct){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    vector<unsigned long long> Fibonacci{1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,
        10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,
        5702887,9227465,14930352,24157817,39088169,63245986,102334155};


    cout << "This is to test the runtime as well as how accurately we get the numbers." << endl;
    Tester(1, "1 - 10", 40, vector<unsigned long long>(Fibonacci.begin(), Fibonacci.begin() + 10));
    Tester(2, "1 - 20", 40, vector<unsigned long long>(Fibonacci.begin(), Fibonacci.begin() + 20));
    Tester(3, "1 - 30", 40, vector<unsigned long long>(Fibonacci.begin(), Fibonacci.begin() + 30));
    Tester(4, "1 - 40", 40, vector<unsigned long long>(Fibonacci.begin(), Fibonacci.begin() + 40));
}