#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>

using namespace std;
using namespace sf;

struct Bar 
{
    int height;
    Color color;
};

class SortingAlgorithms
{
public:
    SortingAlgorithms(int numBars, int windowHeight);
    void GenerateRandomBars(vector<Bar>& bars);
    void DrawBars(RenderWindow& window, const std::vector<Bar>& bars, int yOffset);
    void MergeSortStep(vector<Bar>& bars, int& l, int& m, int& r, int& step);
    void HeapSortStep(vector<Bar>& bars, int& i, int& n);

private:
    void Merge(vector<Bar>& bars, int l, int m, int r);
    void Heapify(vector<Bar>& bars, int n, int i);

    int _numBars;
    int _windowHeight;
};

#endif 
