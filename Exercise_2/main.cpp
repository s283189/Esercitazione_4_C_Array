#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Funzione per leggere i dati dal file
bool ImportData(const string& inputFilePath, double& S, size_t& n, double*& w, double*& r);

// Funzione per calcolare il tasso di rendimento e il valore finale del portafoglio
void ComputeRateOfReturn(const double& S, const size_t& n, const double* const& w, const double* const& r, double& rateOfReturn, double& V);

// Funzione per esportare i dati su file
void ExportData(ostream& out, const double& S, const size_t& n, const double* const& w, const double* const& r, const double& rateOfReturn, const double& V);

// Funzione per convertire un array in una stringa
string ArrayToString(const size_t& n, const double* const& v)
{
    ostringstream toString;
    toString << "[ ";
    for (unsigned int i = 0; i < n; i++)
        toString << v[i] << " ";
    toString << "]";

    return toString.str();
}

int main()
{
    string inputFileName = "./data.csv";
    double S = 0.0;
    size_t n = 0;
    double* w = nullptr;
    double* r = nullptr;

    // Importo i dati dal file
    if (!ImportData(inputFileName, S, n, w, r))
    {
        cerr << "Something goes wrong with import" << endl;
        return -1;
    }

    double rateOfReturn;
    double V;

    // Calcolo il tasso di rendimento e il valore finale del portafoglio
    ComputeRateOfReturn(S, n, w, r, rateOfReturn, V);

    // Stampo i risultati
    ExportData(cout, S, n, w, r, rateOfReturn, V);

    // Scrivo i risultati su file
    string outputFileName = "./result.txt";
    ofstream file;
    file.open(outputFileName);

    if (!file.fail())
    {
        ExportData(file, S, n, w, r, rateOfReturn, V);
    }

    file.close();

    delete[] w;
    delete[] r;

    return 0;
}

// Funzione per leggere i dati dal file
bool ImportData(const string& inputFilePath, double& S, size_t& n, double*& w, double*& r)
{
    ifstream file;
    file.open(inputFilePath);
    if (file.fail())
    {
        cerr << "File open failed..." << endl;
        return false;
    }
    string line;

    // Leggo il valore di S
    getline(file,line);
    stringstream Sstr;
    for (unsigned int i = 2; i < line.length(); i++)
    {
        Sstr << line[i];
    }
    Sstr >> S;

    // Leggo il valore di n
    getline(file, line);
    stringstream nstr;
    for (unsigned int i = 2; i < line.length(); i++)
    {
        nstr << line[i];
    }
    nstr >> n;

    // Leggo il valore di w e r
    getline(file,line);
    w = new double[n];
    r = new double[n];
    stringstream wstr;
    stringstream rstr;

    for (unsigned int j = 0; j < n; j++)
    {
        getline(file,line);
        istringstream convert;
        line.replace(line.find(';'), 1, " ");
        convert.str(line);
        convert >> w[j] >> r[j];
    }
    file.close();

    return true;
}

// Funzione per calcolare il tasso di rendimento e il valore finale del portafoglio
void ComputeRateOfReturn(const double& S, const size_t& n, const double* const& w, const double* const& r, double& rateOfReturn, double& V)
{
    V = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        V += (1 + r[i]) * w[i] * S;
    }
    rateOfReturn = V / S - 1; // Calcolo il tasso di rendimento
    return;
}

// Funzione per esportare i dati
void ExportData(ostream& out, const double& S, const size_t& n, const double* const& w, const double* const& r, const double& rateOfReturn, const double& V)
{
    out <<"S = " << setprecision(2) << fixed << S << ", n = " << n << endl;
    out << defaultfloat << setprecision(6);

    out << "w = " << ArrayToString(n, w) << endl;
    out << "r = " << ArrayToString(n, r) << endl;

    out << "Rate of return of the portfolio: " << rateOfReturn << endl;
    out << "V: " << setprecision(2) << fixed << V << endl;

    return;
}

