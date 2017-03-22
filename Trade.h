//
// Trade.h
//
// 20170322
//

#ifndef __JPM_SSSM_TRADE__
#define __JPM_SSSM_TRADE__

#include <ctime>
#include <string>

// Trade type : BUY / SELL
enum TradeType {
    BUY,
    SELL
};

const std::string TRADE_SELL = "SELL";
const std::string TRADE_BUY  = "BUY";

// Class Trade
class Trade {
public :
    // constructors  / destructor
    Trade();
    Trade(time_t timeStamp, double quantity, TradeType type, double price);
    ~Trade();
    Trade(const Trade &t);
    Trade &operator =(const Trade &t);

    // get methods
    time_t getTimeStamp() const;
    double  getQuantity() const;
    TradeType getType() const;
    double getPrice() const;

    // set methods
    void setTimeStamp(time_t timeStamp);
    void setQuantity(double quantity);
    void setType(TradeType type);
    void setPrice(double price);

    //
    // other methods
    //

private :
    //timestamp : number of seconds elapsed since January 1, 1970
    time_t m_timeStamp;
    double m_quantity;
    TradeType m_type;
    double m_price;
};

#endif // __JPM_SSSM_TRADE__
