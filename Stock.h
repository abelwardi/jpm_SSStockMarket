//
// Stock.h
//
// 20170322
//

#ifndef __JPM_SSSM_STOCK__
#define __JPM_SSSM_STOCK__

#include <vector>
#include <string>

#include "Trade.h"

// Stock type : COMMON / PREFERRED
enum StockType {
    COMMON,
    PREFERRED
};

const std::string STOCK_COMMON = "COMMON";
const std::string STOCK_PREFERRED = "PREFERRED";

// Stock Class
class Stock {
public :
    // Constructors / destructor
    Stock();
    Stock(const std::string& symbol, StockType type, double lastDividend, double fixedDividend, double parValue);
    ~Stock();
    Stock(const Stock &s);
    Stock &operator =(const Stock &s);

    // get methods
    std::string getSymbol() const;
    StockType   getType() const;
    double      getLastDividend() const;
    double      getFixedDividend() const;
    double      getParValue() const;

    // set methods
    void    setSymbol(const std::string& symbol);
    void    setType(StockType type);
    void    setLastDividend(double lastDividend);
    void    setFixedDividend(double fixedDividend);
    void    setParValue(double parValue);

    //Record a trade
    void addTrade(time_t timeStamp, double quantity, TradeType type, double price);

    //calculate the dividend yield
    double  dividendYield(double price);
    //calculate the P/E Ratio
    double  peRatio(double price);
    //Calculate Volume Weighted Stock Price based on trades in past duration seconds
    double  volumeWeightedStockPrice(int duration);
    //Calculate the GBCE using the geometric mean of prices
    double  GBCE();

    //
    // TODO
    // Other methods to manage m_trades : get, set, print, find, ....
    //

private :
    std::string m_symbol;
    StockType   m_type;
    double      m_lastDividend;
    double      m_fixedDividend;
    double      m_parValue;

    // Record a trades
    std::vector<Trade> m_trades;
};

#endif // __JPM_SSSM_STOCK__
