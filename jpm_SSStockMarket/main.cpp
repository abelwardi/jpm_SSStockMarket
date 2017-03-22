//
// main.cpp
// jpm_SSStockMarket
//
// 20170322
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include <map>
#include "Stock.h"

using namespace std;


//
// read stocks from input file
//
int initStocks(map<string, Stock>& stockMap, string filePathStock)
{
    // read Stocks file csv
    //(symbol type lastDividend fixedDividend parValue)
    ifstream inFileStock(filePathStock);
    if (inFileStock.fail())
    {
        perror(filePathStock.c_str());
        return -1;
    }

    string symbol, type;
    double lastDividend, fixedDividend, parValue;

    while (inFileStock >> symbol >> type >> lastDividend >> fixedDividend >> parValue )
    {
        StockType sType;
        if(type == STOCK_COMMON)
            sType = COMMON;
        else if (type == STOCK_PREFERRED)
            sType = PREFERRED;

        // create a stock object
        Stock s(symbol, sType, lastDividend, fixedDividend, parValue);
        // add a stock in the list
        stockMap.insert(pair<string, Stock> (symbol, s));
    }

    inFileStock.close();

    return 0;
}

//
// read trade from input file
//
int addTrades(map<string, Stock>& stockMap, string filePathTrade)
{
    ifstream inFileTrade(filePathTrade);
    if (inFileTrade.fail())
    {
        perror(filePathTrade.c_str());
        return -1;
    }

    string symbol, type;
    time_t timeStamp;
    double quantity, price;

    while (inFileTrade >> symbol >> timeStamp >> quantity >> type >> price )
    {
        TradeType sType;
        if(type == TRADE_BUY)
            sType = BUY;
        else if (type == TRADE_SELL)
            sType = SELL;

        stockMap[symbol].addTrade(timeStamp, quantity, sType, price);
    }

    inFileTrade.close();

    return 0;
}


//
// read stock price from input file
//
int readStockPrices(map<string, double>& stockPriceMap, string filePathStockPrices)
{
    ifstream inFileStockPrice(filePathStockPrices);
    if (inFileStockPrice.fail())
    {
        perror(filePathStockPrices.c_str());
        return -1;
    }

    string symbol;
    double price;

    while (inFileStockPrice >> symbol >> price )
    {
        stockPriceMap.insert(pair<string, double> (symbol, price));
    }

    inFileStockPrice.close();

    return 0;
}

//
// write results in output file
//
int writeStocksSSSM(map<string, Stock> stockMap,
                    map<string, double> stockPriceMap,
                    string filePathStocksSSSM, int duration)
{

    ofstream outFileStocksSSSM(filePathStocksSSSM);
    if (outFileStocksSSSM.fail())
    {
        perror(filePathStocksSSSM.c_str());
        return -1;
    }

    outFileStocksSSSM << "symbol price dividendYield peRatio VWSP GBCE" << endl;

    for(auto& m : stockMap)
    {
        //symbol price dividendYield peRatio VWSP GBCE
        outFileStocksSSSM << m.first << " "
        << stockPriceMap[m.first] << " "
        << m.second.dividendYield( stockPriceMap[m.first] ) << " "
        << m.second.peRatio( stockPriceMap[m.first] ) << " "
        << m.second.volumeWeightedStockPrice(duration) << " "
        << m.second.GBCE() << endl;
    }

    outFileStocksSSSM.close();
    return 0;
}



//
char debug{'N'};

int main(int argc, const char * argv[])
{
    // get parameters
    if(argc != 6)
    {
        cout << "usage jpm_SSStockMarket filePathStock filePathTrade filePathStockPrices duration(seconds) outFilePathStocksSSSM" << endl;
        cout << "jpm_SSStockMarket stocks2.csv trade2.csv stockPrices.csv 3600 stocksSSSM.csv" << endl;
        return -1;
    }

    //parameters
    string filePathStock = argv[1];
    string filePathTrade = argv[2];
    string filePathStockPrices = argv[3];
    int duration = atof(argv[4]);
    string filePathStocksSSSM = argv[5];

    //
    /*string filePathStock="stocks2.csv";
    string filePathTrade="trade2.csv";
    string filePathStockPrices="stockPrices.csv";
    int duration = 15*600; //seconds
    string filePathStocksSSSM = "stocksSSSM.csv";*/

    //
    //
    //
    map<string, Stock> stockMap;
    map<string, double> stockPriceMap;

    //
    cout << "SSSM Start ..." << endl;
    //
    cout << "SSSM initStocks ..." << endl;
    //
    // read stocks from input file
    //
    initStocks(stockMap, filePathStock);
    //
    if(debug == 'Y')
    {
        cout << "* stockMap *" << endl;
        for(auto& m : stockMap)
        {
            cout << m.first << " "
            << m.second.getSymbol() << " "
            << m.second.getType() << " "
            << m.second.getLastDividend() << " "
            << m.second.getFixedDividend() << " "
            << m.second.getParValue() << endl;
        }
    }

    //
    cout << "SSSM addTrades ..." << endl;
    //
    // read trade from input file
    //
    addTrades(stockMap, filePathTrade);

    //
    cout << "SSSM readStockPrices ..." << endl;
    //
    // read stock price from input file
    //
    readStockPrices(stockPriceMap, filePathStockPrices);
    //
    if(debug == 'Y')
    {
        for(auto& m : stockPriceMap)
        {
            cout << m.first <<" " << m.second << endl;
        }
    }

    //
    cout << "SSSM writeStocksSSSM ..." << endl;
    //
    // write results in output file
    //
    writeStocksSSSM(stockMap,stockPriceMap, filePathStocksSSSM, duration);

    //
    cout << "SSSM end" << endl;
    return 0;

}
