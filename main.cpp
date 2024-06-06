
//--------------------------------Merge + Heap sort----------------------------------
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "SortingAlgorithms.h"

const int numBars = 800;
const int windowHeight = 600;
const int windowWidth = 800;

vector<Bar> mergeSortBars(numBars);
vector<Bar> heapSortBars(numBars);

int main() 
{
    RenderWindow appWindow(sf::VideoMode(windowWidth, windowHeight), "Sorting Algorithms Visualization");

    Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "Error loading font\n";
        return -1;
    }

    Text mergeSortText, heapSortText;
    mergeSortText.setFont(font);
    heapSortText.setFont(font);

    mergeSortText.setCharacterSize(24);
    heapSortText.setCharacterSize(24);

    mergeSortText.setFillColor(sf::Color::White);
    heapSortText.setFillColor(sf::Color::White);

    mergeSortText.setPosition(10, 10);
    heapSortText.setPosition(10, windowHeight / 2 + 10);

    SortingAlgorithms sorter(numBars, windowHeight);
    sorter.GenerateRandomBars(mergeSortBars);
    sorter.GenerateRandomBars(heapSortBars);

    int heapSortI = 0;
    bool heapSortFinished = false;
    int n = numBars;

    int mergeSortStepCounter = 0;
    int mergeSortL = 0, mergeSortM = 0, mergeSortR = 0;
    bool mergeSortFinished = false;

    Clock heapSortClock, mergeSortClock;
    Time heapSortTime, mergeSortTime;

    while (appWindow.isOpen()) 
    {
        Event appEvent;
        while (appWindow.pollEvent(appEvent))
        {
            if (appEvent.type == Event::Closed)
            {
                appWindow.close();
            }
        }

        if (!heapSortFinished)
        {
            heapSortClock.restart();
            sorter.HeapSortStep(heapSortBars, heapSortI, n);
            heapSortTime += heapSortClock.getElapsedTime();
            if (heapSortI <= 0) 
            {
                heapSortFinished = true;
            }
        }

        if (!mergeSortFinished)
        {
            mergeSortClock.restart();
            sorter.MergeSortStep(mergeSortBars, mergeSortL, mergeSortM, mergeSortR, mergeSortStepCounter);
            mergeSortTime += mergeSortClock.getElapsedTime();
            if (mergeSortStepCounter == 2) 
            {
                mergeSortFinished = true;
            }
        }

        if (mergeSortFinished)
        {
            mergeSortText.setString("Merge Sort\nTime: " + to_string(mergeSortTime.asSeconds()) + " s\nComplexity: O(n log n)\nElements: " + to_string(numBars));
        }
        else
        {
            mergeSortText.setString("Merge Sort\nSorting...");
        }

        if (heapSortFinished)
        {
            heapSortText.setString("Heap Sort\nTime: " + to_string(heapSortTime.asSeconds()) + " s\nComplexity: O(n log n)\nElements: " + to_string(numBars));
        }
        else 
        {
            heapSortText.setString("Heap Sort\nSorting...");
        }

        appWindow.clear(Color::Black);
        appWindow.draw(mergeSortText);
        appWindow.draw(heapSortText);
        sorter.DrawBars(appWindow, mergeSortBars, windowHeight / 2);
        sorter.DrawBars(appWindow, heapSortBars, 0);
        appWindow.display();
    }

    return 0;
}


//---------------------------------Merge + Bubble sort--------------------------------------

//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <cstdlib>
//#include <ctime>
//#include <iostream>
//#include <tuple>
//
//using namespace sf;
//using namespace std;
//
//struct Bar {
//    int height;
//    Color color;
//};
//
//const int numBars = 1000;
//const int windowHeight = 800;
//const int windowWidth = 1000;
//const int barWidth = windowWidth / numBars;
//
//vector<Bar> mergeSortBars(numBars);
//vector<Bar> bubbleSortBars(numBars);
//
//void generateRandomBars(vector<Bar>& bars) {
//    for (int i = 0; i < numBars; ++i) {
//        bars[i].height = rand() % (windowHeight / 2);
//        bars[i].color = Color(rand() % 256, rand() % 256, rand() % 256);
//    }
//}
//
//void drawBars(RenderWindow& window, const vector<Bar>& bars, int yOffset) {
//    for (int i = 0; i < numBars; ++i) {
//        RectangleShape rectangle(Vector2f(barWidth, bars[i].height));
//        rectangle.setFillColor(bars[i].color);
//        rectangle.setPosition(i * barWidth, windowHeight - yOffset - bars[i].height);
//        window.draw(rectangle);
//    }
//}
//
//void merge(vector<Bar>& bars, int l, int m, int r) {
//    int n1 = m - l + 1;
//    int n2 = r - m;
//
//    vector<Bar> L(n1);
//    vector<Bar> R(n2);
//
//    for (int i = 0; i < n1; i++) {
//        L[i] = bars[l + i];
//    }
//    for (int i = 0; i < n2; i++) {
//        R[i] = bars[m + 1 + i];
//    }
//
//    int i = 0, j = 0, k = l;
//    while (i < n1 && j < n2) {
//        if (L[i].height <= R[j].height) {
//            bars[k] = L[i];
//            i++;
//        }
//        else {
//            bars[k] = R[j];
//            j++;
//        }
//        k++;
//    }
//    while (i < n1) {
//        bars[k] = L[i];
//        i++;
//        k++;
//    }
//
//    while (j < n2) {
//        bars[k] = R[j];
//        j++;
//        k++;
//    }
//
//}
//
//void mergeSortStep(vector<Bar>& bars, int& l, int& m, int& r, int& step) {
//    static vector<tuple<int, int, int>> mergeRanges;
//    static int rangeIndex = 0;
//    if (step == 0) {
//        for (int sz = 1; sz <= numBars; sz = 2 * sz) {
//            for (int l = 0; l < numBars - sz; l += 2 * sz) {
//                int m = l + sz - 1;
//                int r = min(l + sz + sz - 1, numBars - 1);
//                mergeRanges.emplace_back(l, m, r);
//            }
//        }
//        step = 1;
//    }
//
//    if (step == 1 && rangeIndex < mergeRanges.size()) {
//        tie(l, m, r) = mergeRanges[rangeIndex];
//        merge(bars, l, m, r);
//        rangeIndex++;
//    }
//    else {
//        step = 2;
//    }
//
//}
//
//void bubbleSortStep(vector<Bar>& bars, int& i, int& j) {
//    if (i < numBars) {
//        if (j < numBars - i - 1) {
//            if (bars[j].height > bars[j + 1].height) {
//                swap(bars[j], bars[j + 1]);
//            }
//            j++;
//        }
//        else {
//            j = 0;
//            i++;
//        }
//    }
//}
//
//int main() {
//    RenderWindow appWindow(VideoMode(windowWidth, windowHeight), "Sorting Algorithms Visualization");
//    // Using default font for text
//    Font font;
//    if (!font.loadFromFile("arial.ttf")) {
//        cout << "Error loading font\n";
//        return -1;
//    }
//
//    Text mergeSortText, bubbleSortText;
//    mergeSortText.setFont(font);
//    bubbleSortText.setFont(font);
//
//    mergeSortText.setCharacterSize(24);
//    bubbleSortText.setCharacterSize(24);
//
//    mergeSortText.setFillColor(Color::White);
//    bubbleSortText.setFillColor(Color::White);
//
//    mergeSortText.setPosition(10, 10);
//    bubbleSortText.setPosition(10, windowHeight / 2 + 10);
//
//    srand(time(NULL));
//
//    generateRandomBars(mergeSortBars);
//    generateRandomBars(bubbleSortBars);
//
//    int bubbleSortI = 0, bubbleSortJ = 0;
//    bool bubbleSortFinished = false;
//
//    int mergeSortStepCounter = 0;
//    int mergeSortI = 0, mergeSortJ = 0;
//    int mergeSortL = 0, mergeSortM = 0, mergeSortR = 0;
//    bool mergeSortFinished = false;
//
//    Clock bubbleSortClock, mergeSortClock;
//    Time bubbleSortTime, mergeSortTime;
//
//    while (appWindow.isOpen()) {
//        Event appEvent;
//        while (appWindow.pollEvent(appEvent)) {
//            if (appEvent.type == Event::Closed) {
//                appWindow.close();
//            }
//        }
//
//        if (!bubbleSortFinished) {
//            bubbleSortClock.restart();
//            bubbleSortStep(bubbleSortBars, bubbleSortI, bubbleSortJ);
//            bubbleSortTime += bubbleSortClock.getElapsedTime();
//            if (bubbleSortI >= numBars) {
//                bubbleSortFinished = true;
//            }
//        }
//
//        if (!mergeSortFinished) {
//            mergeSortClock.restart();
//            mergeSortStep(mergeSortBars, mergeSortL, mergeSortM, mergeSortR, mergeSortStepCounter);
//            mergeSortTime += mergeSortClock.getElapsedTime();
//            if (mergeSortStepCounter == 2) {
//                mergeSortFinished = true;
//            }
//        }
//
//        if (mergeSortFinished) {
//            mergeSortText.setString("Merge Sort\nTime: " + to_string(mergeSortTime.asSeconds()) + " s\nComplexity: O(n log n)\nElements: " + to_string(numBars));
//        }
//        else {
//            mergeSortText.setString("Merge Sort\nSorting...");
//        }
//
//        if (bubbleSortFinished) {
//            bubbleSortText.setString("Bubble Sort\nTime: " + to_string(bubbleSortTime.asSeconds()) + " s\nComplexity: O(n^2)\nElements: " + to_string(numBars));
//        }
//        else {
//            bubbleSortText.setString("Bubble Sort\nSorting...");
//        }
//
//        appWindow.clear(Color::Black);
//        appWindow.draw(mergeSortText);
//        appWindow.draw(bubbleSortText);
//        drawBars(appWindow, mergeSortBars, windowHeight / 2);
//        drawBars(appWindow, bubbleSortBars, 0);
//        appWindow.display();
//    }
//
//    return 0;
//}

