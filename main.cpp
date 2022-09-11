#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
//Function Declaration
void print_stats(vector<double> vector1);
const double covar(vector <double> vectorData1, vector<double> vectorData2);
const double cor(vector<double> vector1, vector<double> vector2);

int main() {
    ifstream inFS;  //Input file stream
    string line;
    string rm_in, medv_in;
    const int MAX_LEN = 1000;
    vector<double> rm(MAX_LEN);
    vector<double> medv(MAX_LEN);

    //Trying to open file
    cout << "Opening the file Boston.csv" << endl;

    inFS.open("Boston.csv");

    if(!inFS.is_open()){
        cout << "File could not be opened" << endl;
        return 1;
    }

    //Can now use inFS stream like cin stream
    //Boston.csv should contain 2 doubles

    cout << "Reading line 1" << endl;
    getline(inFS, line);

    //echo heading
    cout << "heading: " << line << endl;

    int numObservations = 0;
    while (inFS.good()) {
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');

        rm.at(numObservations) = stof(rm_in);
        medv.at(numObservations) = stof(medv_in);

        numObservations++;
    }

    rm.resize(numObservations);
    medv.resize(numObservations);

    cout << "new length " << rm.size() << endl;
    cout << "Closing file Boston.csv" << endl;
    inFS.close(); // Done with file so close it

    cout << "Number of records: " << numObservations << endl;

    cout << "\nStats for rm" << endl;
    print_stats(rm);

    cout << "\nStats for medv" << endl;
    print_stats(medv);



    cout << "\nCovariance = " << covar(rm, medv) << endl;

    cout << "\nCorrelation = " <<cor(rm, medv) << endl;

    cout << "\nProgram terminated";
    return 0;
}




//Function Definitions
void print_stats(vector<double> vector1) {

    double sum = 0;
    double median = 0;
    double range = 0;
    double mean = 0;

    sort(vector1.begin(), vector1.end());

    for (int i = 0; i < vector1.size(); i++){
        sum += vector1.at(i);
        median = vector1.at(vector1.size()/2);
        range = vector1.at(505) - vector1.at(0);
        mean = sum/vector1.size();

        //cout << vector1.at(i) + vector1.at(i+1) << " ,";

    }
    cout << "Sum: " << sum << endl;
    cout << "Mean: " << mean << endl;
    cout << "Median: " << median << endl;
    cout << "Range: " << range << endl;


}

const double covar(vector <double> vector1, vector<double> vector2) {
    //vector 1 is rm and vector 2 is medv
    double sum = 0;
    double sumRm = 0;
    double sumMedv = 0;
    double meanRm = 0;
    double meanMedv = 0;


    for (int i = 0; i < vector1.size(); i++) {
        sumRm += vector1.at(i);
        meanRm = sumRm/vector1.size();
    }

    for (int i = 0; i < vector2.size(); i++) {
        sumMedv += vector2.at(i);
        meanMedv = sumMedv/vector2.size();
    }

    for (int i = 0; i < vector1.size(); i++) {

        sum += ((vector1.at(i) - meanRm) *(vector2.at(i) - meanMedv));
    }


    double covariance = sum/(vector1.size() - 1);

    return covariance;
}

const double cor(vector<double> vector1, vector<double> vector2){
    double varianceRm = 0;
    double varianceMedv = 0;

    double sumRm = 0;
    double sumMedv = 0;
    double meanRm = 0;
    double meanMedv = 0;


    for (int i = 0; i < vector1.size(); i++) {
        sumRm += vector1.at(i);
        meanRm = sumRm/vector1.size();
    }

    for (int i = 0; i < vector2.size(); i++) {
        sumMedv += vector2.at(i);
        meanMedv = sumMedv/vector2.size();
    }

    for (int i = 0; i < vector1.size(); i++) {
        varianceRm += pow((vector1.at(i) - meanRm),2);
        varianceMedv += pow((vector2.at(i) - meanMedv),2);
    }

    varianceRm = varianceRm/(vector1.size() - 1);
    varianceMedv = varianceMedv/(vector2.size() - 1);
    double standardRm = sqrt(varianceRm);
    double standardMedv = sqrt(varianceMedv);

    return ((covar(vector1,vector2))/(standardRm * standardMedv));
}