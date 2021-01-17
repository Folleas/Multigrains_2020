/*
** EPITECH PROJECT, 2021
** B-MAT-500-PAR-5-1-307multigrains-rayann.folleas
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine()
{
    result = {0, 0, 0, 0, 0};
}

std::pair<int, int> Engine::getPivotIndex(std::vector<std::vector<float>> matrix)
{
    std::size_t matrixSize = matrix.size();
    if (matrixSize <= 0)
        return std::pair<int, int>(-1, -1);

    std::size_t lineSize = matrix[0].size();
    if (lineSize <= 5)
        return std::pair<int, int>(-1, -1);

    std::vector<float> line = matrix[matrixSize - 1];
    std::vector<float> lastFiveElem = GetLastFiveElems(line);

    float smallest = getSmallestElem(lastFiveElem);
    if (smallest == -1)
        return std::pair<int, int>(-1, -1);
    return (computePivots(lastFiveElem, smallest, matrix, matrixSize, lineSize));
}

std::pair<int, int> Engine::computePivots(std::vector<float> lastFiveElem, float smallest, std::vector<std::vector<float>> matrix, float matrixSize, std::size_t lineSize)
{
    int xPivot = -1, yPivot = -1;
    xPivot = std::distance(lastFiveElem.begin(), std::find(lastFiveElem.begin(), lastFiveElem.end(), smallest));
    smallest = 99999999999999;
    for (int i = 0; i < matrixSize - 1; i++) {
        if (matrix[i][lineSize - 1]) {
            if (matrix[i][xPivot] > 0 && (smallest > matrix[i][lineSize - 1] / matrix[i][xPivot] && matrix[i][lineSize - 1] / matrix[i][xPivot] > 0)) {
                yPivot = i;
                smallest = matrix[i][lineSize - 1] / matrix[i][xPivot];
            }
        }
        else if (smallest > matrix[i][xPivot] && matrix[i][xPivot] > 0) {
            yPivot = i;
            smallest = matrix[i][lineSize - 1] / matrix[i][xPivot];
        }
    }
    return (std::pair<int, int>(yPivot, xPivot));
}

std::vector<float> Engine::GetLastFiveElems(std::vector<float> line)
{
    std::vector<float> lastFiveElem;

    for (int i = 0; i < 5; i++) {
        lastFiveElem.push_back(line[i]);
    }
    return lastFiveElem;
}

float Engine::getSmallestElem(std::vector<float> lastFiveElem)
{
    float smallest = std::numeric_limits<float>::max();

    for (float i : lastFiveElem)
        smallest = std::min(i, smallest);
    if (smallest >= 0)
        return -1;
    return smallest;
}

bool Engine::is_number(const std::string &s)
{
    for (int i = 0; i < s.size(); i++)
        if (!(s[i] >= '0' && s[i] <= '9'))
            return (false);
    return (true);
}

std::vector<std::vector<float>> Engine::createMatrix(std::vector<float> N, std::vector<float> P)
{
    std::vector<float> minusP;
    for (int value : P)
        minusP.push_back(-value);
    for (int i = 0; i < 5; i++)
        minusP.push_back(0);
    std::vector<std::vector<float>> matrix = {
        std::vector<float>{1, 0, 1, 0, 2},
        std::vector<float>{1, 2, 0, 1, 0},
        std::vector<float>{2, 1, 0, 1, 0},
        std::vector<float>{0, 0, 3, 1, 2},
        minusP
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == i)
                matrix[i].push_back(1);
            else
                matrix[i].push_back(0);
        }
        matrix[i].push_back(N[i]);
    }
    return (matrix);
}

std::vector<std::vector<float>> Engine::applyPivot(std::vector<std::vector<float>> matrix, int y_p, int x_p)
{
    float p_value = matrix[y_p][x_p];
    for (int i = 0; i < matrix[y_p].size(); i++)
    {
        matrix[y_p][i] = matrix[y_p][i] / p_value;
    }
    int maxy = matrix.size();
    int maxx = matrix[0].size();
    for (int i = 0; i < maxy; i++)
    {
        if (i == y_p)
            continue;
        float km = matrix[i][x_p];
        for (int j = 0; j < maxx; j++)
            matrix[i][j] -= km * matrix[y_p][j];
    }
    return (matrix);
}

std::pair<std::vector<float>, std::vector<std::vector<float>>> Engine::simplex(std::vector<std::vector<float>> matrix)
{
    std::vector<float> products;
    for (int i = 0; i < 4; i++)
        products.push_back(-1);
    int i = 0;
    while (true)
    {
        i++;
        if (i == 6)
            break;
        std::pair<int, int> p = getPivotIndex(matrix);
        int x_p = p.second;
        int y_p = p.first;
        if (y_p < 0 || x_p < 0)
            break;
        matrix = applyPivot(matrix, y_p, x_p);
        products[y_p] = x_p;
    }
    return std::pair<std::vector<float>, std::vector<std::vector<float>>>(products, matrix);
}

void Engine::printUsage(std::string binaryName)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t" << binaryName << " n1 n2 n3 n4 po pw pc pb ps" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tn1\tnumber of tons of fertilizer F1" << std::endl;
    std::cout << "\tn2\tnumber of tons of fertilizer F2" << std::endl;
    std::cout << "\tn3\tnumber of tons of fertilizer F3" << std::endl;
    std::cout << "\tn4\tnumber of tons of fertilizer F4" << std::endl;
    std::cout << "\tpo\tprice of one unit of oat" << std::endl;
    std::cout << "\tpw\tprice of one unit of wheat" << std::endl;
    std::cout << "\tpc\tprice of one unit of corn" << std::endl;
    std::cout << "\tpb\tprice of one unit of barley" << std::endl;
    std::cout << "\tps\tprice of one unit of soy" << std::endl;
}

int Engine::checkArgs(int ac, char **av)
{
    for (int i = 1; i < 10; i++)
        if (!is_number(std::string(av[i])))
        {
            std::cerr << "Invalid syntax." << std::endl;
            return (84);
        }
    F[0] = std::atoi(av[1]);
    F[1] = std::atoi(av[2]);
    F[2] = std::atoi(av[3]);
    F[3] = std::atoi(av[4]);
    price[0] = std::atoi(av[5]);
    price[1] = std::atoi(av[6]);
    price[2] = std::atoi(av[7]);
    price[3] = std::atoi(av[8]);
    price[4] = std::atoi(av[9]);
    if (F[0] < 0 || F[1] < 0 || F[2] < 0 || F[3] < 0 || price[0] < 0 || price[1] < 0 || price[2] < 0 || price[3] < 0 || price[4] < 0) {
        std::cerr << "Invalid Usage, please check usage" << std::endl;
        return 84;
    }
    return 0;
}

float Engine::compute()
{
    std::vector<float> N = {F[0], F[1], F[2], F[3]};
    std::vector<float> P = {price[0], price[1], price[2], price[3], price[4]};
    std::vector<std::vector<float>> matrix = createMatrix(N, P);
    std::pair<std::vector<float>, std::vector<std::vector<float>>> res2 = simplex(matrix);
    std::vector<float> res = res2.first;
    matrix = res2.second;
    float total = 0;

    for (int i = 0; i < 4; i++)
        if (res[i] != -1)
            if (matrix[i][matrix[i].size() - 1] != 0) {
                result[res[i]] = matrix[i][matrix[i].size() - 1];
                total += matrix[i][matrix[i].size() - 1.0f] * P[res[i]];
            }
            else
                result[res[i]] = matrix[i][matrix[i].size() - 1.0f];
    return total;
}

void Engine::printResult(float total)
{
    printf("Resources: %.0f F1, %.0f F2, %.0f F3, %.0f F4\n\n", F[0], F[1], F[2], F[3]);
    if (!result[0])
        printf("Oat: 0 units at $%.0f/unit\n", price[0]);
    else
        printf("Oat: %.2f units at $%.0f/unit\n", result[0], price[0]);
    if (!result[1])
        printf("Wheat: 0 units at $%.0f/unit\n", price[1]);
    else
        printf("Wheat: %.2f units at $%.0f/unit\n", result[1], price[1]);
    if (!result[2])
        printf("Corn: 0 units at $%.0f/unit\n", price[2]);
    else
        printf("Corn: %.2f units at $%.0f/unit\n", result[2], price[2]);
    if (!result[3])
        printf("Barley: 0 units at $%.0f/unit\n", price[3]);
    else
        printf("Barley: %.2f units at $%.0f/unit\n", result[3], price[3]);
    if (!result[4])
        printf("Soy: 0 units at $%.0f/unit\n\n", price[4]);
    else
        printf("Soy: %.2f units at $%.0f/unit\n\n", result[4], price[4]);
    printf("Total production value: $%.2f", total);
}

int Engine::run(int ac, char **av)
{
    std::string line;

    if (ac >= 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
        printUsage(av[0]);
        return (0);
    }
    if (ac != 10) {
        std::cerr << "Bad usage." << std::endl;
        return (84);
    }
    if (checkArgs(ac, av) == 84)
        return (84);

    float total = compute();
    printResult(total);
    return (0);
}