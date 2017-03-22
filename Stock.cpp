//
// Stock.cpp
//
// 20170322
//

#include <cmath>

#include "Stock.h"

//
// Constructors  / destructor
//

Stock::Stock()
{

}

Stock::Stock(const std::string& symbol, StockType type, double lastDividend, double fixedDividend, double parValue)
: m_symbol(symbol),
  m_type(type),
  m_lastDividend(lastDividend),
  m_fixedDividend(fixedDividend),
  m_parValue(parValue)
{

}

Stock::~Stock()
{

}

Stock::Stock(const Stock &s)
: m_symbol(s.m_symbol),
  m_type(s.m_type),
  m_lastDividend(s.m_lastDividend),
  m_fixedDividend(s.m_fixedDividend),
  m_parValue(s.m_parValue),
  m_trades(s.m_trades)
{

}

Stock &Stock::operator =(const Stock &s)
{
    if(this != &s)
    {
        m_symbol = s.m_symbol;
        m_type = s.m_type;
        m_lastDividend = s.m_lastDividend;
        m_fixedDividend = s.m_fixedDividend;
        m_parValue = s.m_parValue;
        m_trades = s.m_trades;
    }

    return *this;
}

//
// get methods
//

std::string Stock::getSymbol() const
{
    return m_symbol;
}

StockType Stock::getType() const
{
    return m_type;
}

double Stock::getLastDividend() const
{
        return m_lastDividend;
}

double Stock::getFixedDividend() const
{
    return m_fixedDividend;
}

double Stock::getParValue() const
{
    return m_parValue;
}

//
// set methods
//

void Stock::setSymbol(const std::string& symbol)
{
    m_symbol = symbol;
}

void Stock::setType(StockType type)
{
    m_type = type;
}

void Stock::setLastDividend(double lastDividend)
{
    m_lastDividend = lastDividend;
}

void Stock::setFixedDividend(double fixedDividend)
{
    m_fixedDividend = fixedDividend;
}

void Stock::setParValue(double parValue)
{
        m_parValue = parValue;
}

//
//Record a trade
//

void Stock::addTrade(time_t timeStamp, double quantity, TradeType type, double price)
{
    Trade t(timeStamp, quantity, type, price);
    m_trades.push_back(t);
}

//
//calculate the dividend yield
//

double Stock::dividendYield(double price)
{
    double dy;

    switch(m_type)
    {
    case COMMON:
        dy = m_lastDividend;
        break;
    case PREFERRED:
        dy =  m_fixedDividend*m_parValue;
        break;
    default:
         dy = 0.0;
    }

    return (price != 0) ? dy/price : -1;
}

//
//calculate the P/E Ratio
//

double Stock::peRatio(double price)
{
    return (m_lastDividend != 0.0) ? price/m_lastDividend : -1;
}

//
//Calculate Volume Weighted Stock Price based on trades in past duration seconds
//

double  Stock::volumeWeightedStockPrice(int durationSec)
{
    time_t pastTimeSec = time(0) - durationSec;
    double totQuantity{0.0}, totPriceQuantity{0.0};
    int tradeNbre = m_trades.size();
    for(auto i = tradeNbre-1; 0<=i; --i)
    {
        if(pastTimeSec <= m_trades[i].getTimeStamp())
        {
            totQuantity += m_trades[i].getQuantity();
            // be careful the max value of double
            totPriceQuantity += m_trades[i].getPrice() * m_trades[i].getQuantity();
        }
        else
        {
            break;
        }
    }
    return (totQuantity != 0.0) ? totPriceQuantity/totQuantity : -1;
}

//
//Calculate the GBCE using the geometric mean of prices
//

double  Stock::GBCE()
{
    double prodPrice{1.0};
    int tradeNbre = m_trades.size();
    for(auto i = 0; i < tradeNbre; ++i)
    {
        prodPrice *= m_trades[i].getPrice();
    }
    return (tradeNbre != 0) ? pow (prodPrice, 1/(double) tradeNbre) : -1;
}



