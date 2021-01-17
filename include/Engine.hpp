/*
** EPITECH PROJECT, 2021
** B-MAT-500-PAR-5-1-307multigrai   s-rayann.folleas
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <stdio.h>

class Engine {
    public:
        Engine();
        ~Engine() = default;

        int run(int ac, char **av);
        float compute();

        int checkArgs(int ac, char **av);
        void checkInputs();

        std::vector<std::vector<float>> createMatrix(std::vector<float> N, std::vector<float> P);
        std::pair<int, int> computePivots(std::vector<float> lastFiveElem, float smallest, std::vector<std::vector<float>> matrix, float matrixSize, std::size_t lineSize);
        std::vector<std::vector<float>> applyPivot(std::vector<std::vector<float>> matrix, int y_p, int x_p);
        std::pair<int, int> getPivotIndex(std::vector<std::vector<float>> matrix);
        std::pair<std::vector<float>, std::vector<std::vector<float>>> simplex(std::vector<std::vector<float>> matrix);

        void printUsage(std::string binaryName);
        void printSyntax();
        void printResult(float total);

        float getSmallestElem(std::vector<float> lastFiveElem);
        std::vector<float> GetLastFiveElems(std::vector<float> line);
        bool is_number(const std::string& s);

    private:
        std::vector<float> result;
        std::array<float, 4> F;
        std::array<float, 5> price;
};

#endif /* !ENGINE_HPP_ */
