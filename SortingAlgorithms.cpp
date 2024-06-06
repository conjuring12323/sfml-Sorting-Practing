#include "SortingAlgorithms.h"
#include <cstdlib>
#include <ctime>

SortingAlgorithms::SortingAlgorithms(int numBars, int windowHeight) : _numBars(numBars), _windowHeight(windowHeight)
{
    srand(time(NULL));
}

void SortingAlgorithms::GenerateRandomBars(vector<Bar>& bars)
{
    for (int i = 0; i < _numBars; ++i)
    {
        bars[i].height = rand() % (_windowHeight / 2);
        bars[i].color = Color(rand() % 256, rand() % 256, rand() % 256);
    }
}

void SortingAlgorithms::DrawBars(RenderWindow& window, const vector<Bar>& bars, int yOffset)
{
    int barWidth = window.getSize().x / _numBars;
    for (int i = 0; i < _numBars; i++)
    {
        RectangleShape rectangle(Vector2f(barWidth, bars[i].height));
        rectangle.setFillColor(bars[i].color);
        rectangle.setPosition(i * barWidth, _windowHeight - yOffset - bars[i].height);
        window.draw(rectangle);
    }
}

void SortingAlgorithms::Merge(vector<Bar>& bars, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Bar> L(n1);
    vector<Bar> R(n2);

    for (int i = 0; i < n1; i++) 
    {
        L[i] = bars[l + i];
    }
    for (int i = 0; i < n2; i++) 
    {
        R[i] = bars[m + 1 + i];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].height <= R[j].height) 
        {
            bars[k] = L[i];
            i++;
        }
        else
        {
            bars[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        bars[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) 
    {
        bars[k] = R[j];
        j++;
        k++;
    }
}

void SortingAlgorithms::MergeSortStep(std::vector<Bar>& bars, int& l, int& m, int& r, int& step)
{
    static vector<tuple<int, int, int>> mergeRanges;
    static int rangeIndex = 0;
    if (step == 0)
    {
        for (int sz = 1; sz <= _numBars; sz = 2 * sz)
        {
            for (int l = 0; l < _numBars - sz; l += 2 * sz)
            {
                int m = l + sz - 1;
                int r = min(l + sz + sz - 1, _numBars - 1);
                mergeRanges.emplace_back(l, m, r);
            }
        }
        step = 1;
    }

    if (step == 1 && rangeIndex < mergeRanges.size())
    {
        tie(l, m, r) = mergeRanges[rangeIndex];
        Merge(bars, l, m, r);
        rangeIndex++;
    }
    else 
    {
        step = 2;
    }
}

void SortingAlgorithms::Heapify(vector<Bar>& bars, int n, int i) 
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && bars[left].height > bars[largest].height)
        largest = left;

    if (right < n && bars[right].height > bars[largest].height)
        largest = right;

    if (largest != i)
    {
        swap(bars[i], bars[largest]);
        Heapify(bars, n, largest);
    }
}

void SortingAlgorithms::HeapSortStep(vector<Bar>& bars, int& i, int& n)
{
    if (i == 0)
    {
        for (int j = n / 2 - 1; j >= 0; j--) 
        {
            Heapify(bars, n, j);
        }
        i = n - 1;
    }

    if (i > 0)
    {
        swap(bars[0], bars[i]);
        Heapify(bars, i, 0);
        i--;
    }
}