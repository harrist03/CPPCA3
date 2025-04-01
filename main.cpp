#include <iostream>
#include <vector>
#include "Crawler.h"
#include <fstream>
#include <sstream>

void parse(string line, int& id, int& x, int& y, int& direction, int& size)
{
    string temp;
    stringstream ss(line);
    // parse id
    getline(ss, temp, ',');
    id = stoi(temp);
    // parse x coordinate
    getline(ss, temp, ',');
    x = stoi(temp);
    // parse y coordinate
    getline(ss, temp, ',');
    y = stoi(temp);
    // parse direction
    getline(ss, temp, ',');
    direction = stoi(temp);
    // parse size
    getline(ss, temp, ',');
    size = stoi(temp);
}

void populateCrawlers(vector<Crawler *>& crawlers)
{
    ifstream fin("crawler-bugs.txt");

    if (fin)
    {
        string line;
        while (!fin.eof())
        {
            string bugType;
            int id;
            int x;
            int y;
            int direction;
            int size;

            getline(fin, line);
            parse(line, id, x, y, direction, size);
            Position p = {x, y}; // or p.x = x, p.y = y;
            Crawler* c1 = new Crawler(id, p, static_cast<Direction>(direction), size, {});
            crawlers.push_back(c1);
        }
    }
}

int main()
{
    vector<Crawler *> crawlers;
    populateCrawlers(crawlers);

    // for testing
    cout << "Number of crawlers loaded: " << crawlers.size() << endl;
}