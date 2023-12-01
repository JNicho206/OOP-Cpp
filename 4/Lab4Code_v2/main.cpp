#include <iostream>
#include <chrono>
#include <optional>
#include <vector>
#include <fstream>

#include "poly.h"

void write_poly(const char* outfile, std::vector<std::pair<power, coeff>> terms)
{
    std::ofstream outputFile(outfile);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file: " << outfile << std::endl;
        return;
    }

    for (const auto& term : terms) {
        outputFile << term.second << "x^" << term.first << std::endl;
    }

    outputFile.close();
    std::cout << "Polynomial written to file: " << outfile << std::endl;
}

std::optional<double> poly_test(polynomial& p1,
                                polynomial& p2,
                                std::vector<std::pair<power, coeff>> solution)

{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    polynomial p3 = p1 * p2;
    auto p3_can_form = p3.canonical_form();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    p3.print();
    write_poly("myresult.txt", p3.canonical_form());
    if (p3_can_form != solution)
    {
        return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}


std::vector<polynomial> poly_from_file(const char* path)
{
    std::ifstream inputFile(path);

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file!" << std::endl;
        exit(1);
    }

    std::string line;
    std::vector<std::pair<power, coeff>> terms1;
    power pow;
    coeff c;
    while (std::getline(inputFile, line)) 
    {
        if (line == ";") { break; }

        int pos = line.find("x^", 0);
        c = std::stoi(line.substr(0, pos));
        pow = std::stoi(line.substr(pos + 2, line.size() - pos + 2));
        terms1.emplace_back(pow, c);
    }

    std::vector<std::pair<power, coeff>> terms2;
    while (std::getline(inputFile, line)) 
    {
        if (line == ";") { break; }
        int pos = line.find("x^", 0);
        c = std::stoi(line.substr(0, pos));
        pow = std::stoi(line.substr(pos + 2, line.size() - pos + 2));
        terms2.emplace_back(pow, c);
    }

    // Close the file
    inputFile.close();
    
    std::vector<polynomial> res = {terms1, terms2};
    return res;
}


std::vector<std::pair<power, coeff>> solution_poly_from_file(const char* path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Unable to open the file!" << std::endl;
        exit(1);
    }

    std::vector<std::pair<power, coeff>> res;
    std::string line;
    power pow;
    coeff c;
    while (std::getline(file, line)) 
    {
        if (line == ";") { break; }

        int pos = line.find("x^", 0);
        c = std::stoi(line.substr(0, pos));
        pow = std::stoi(line.substr(pos + 2, line.size() - pos + 2));
        res.emplace_back(pow, c);
    }

    file.close();
    return res;

}

int main()
{
    /** We're doing (x+1)^2, so solution is x^2 + 2x + 1*/
    std::vector<std::pair<power, coeff>> solution = {{2,1}, {1,2}, {0,1}};

    /** This holds (x+1), which we'll pass to each polynomial */
    std::vector<std::pair<power, coeff>> poly_input = {{1,1}, {0,1}};

    

    auto res = poly_from_file("simple_poly.txt");
    // res[0].print();
    // res[1].print();
    polynomial p1(poly_input.begin(), poly_input.end());
    polynomial p2(poly_input.begin(), poly_input.end());

    std::optional<double> result = poly_test(res[0], res[1], solution_poly_from_file("result.txt"));
    

    if (result.has_value())
    {
        std::cout << "Passed test, took " << result.value()/1000 << " seconds" << std::endl;
    } 
    else 
    {
        std::cout << "Failed test" << std::endl;
    }

    //res[0].print();
    //res[1].print();
}