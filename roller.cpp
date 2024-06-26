#include "roller.h"

#include <iostream>
#include <random>

using std::cerr;
using std::cout;
using std::endl;

QString Roller::roll(QString rollStr, QString &subtotalStr)
{
    // Sanity check
    if (rollStr == nullptr || rollStr == "")
    {
        cerr << "Roll string is null." << endl;
        subtotalStr = "Invalid roll entered.";
        return "";
    }

    rollStr = rollStr.simplified().toUpper();

    if (rollStr.contains('+') || rollStr.contains('-') || rollStr.contains('*') || rollStr.contains('/'))
    {
        cerr << "Mathematical operations are not yet supported." << endl;
        subtotalStr = "Mathematical operations are not yet supported.";
        return "";
    }

    int diceCount, diceSides;
    int firstDIndex = rollStr.indexOf('D');
    if (firstDIndex == -1) // No 'D' in text
    {
        cerr << "No D found in roll string." << endl;
        subtotalStr = "Invalid roll entered.";
        return "";
    } else if (firstDIndex == 0) // 'D' is the first character
    {
        diceCount = 1;
    }
    else // 'D' is not the first character
    {
        // Get number of dice to roll
        QString diceCountStr = rollStr.mid(0, firstDIndex);
        bool success;
        diceCount = diceCountStr.toInt(&success);
        if (!success)
        {
            cerr << "Invalid number of dice." << endl;
            subtotalStr = "Invalid number of dice.";
            return "";
        }
    }

    // Get dice number of sides
    QString diceSidesStr = rollStr.mid(firstDIndex + 1);
    bool success;
    diceSides = diceSidesStr.toInt(&success);
    if (!success || diceSides < 1)
    {
        cerr << "Invalid number of sides." << endl;
        subtotalStr = "Invalid number of sides.";
        return "";
    }

    int result = roll(diceCount, diceSides, subtotalStr);
    return QString::number(result);
}

int Roller::roll(int diceCount, int sides, QString &subtotalStr)
{
    int total = 0;

    for (int i = 0; i < diceCount; i++)
    {
        int roll = rollDie(sides);
        subtotalStr += "D" + QString::number(sides) + " #" + QString::number(i + 1) + " -> " + QString::number(roll);
        if (i < diceCount - 1)
        {
            subtotalStr += "\n";
        }
        cout << "D" << sides << " #" << i + 1 << " rolled " << roll << endl;
        total += roll;
    }
    return total;
}

int Roller::rollDie(int sides)
{
    // Create a random device to seed the random number generator
    static std::random_device rd;
    // Create a random number engine using the random device as the seed
    static std::mt19937 gen(rd());
    // Create a uniform distribution for integers from 1 to 20
    std::uniform_int_distribution<> dis(1, sides);
    // Generate a random number
    return dis(gen);
}
