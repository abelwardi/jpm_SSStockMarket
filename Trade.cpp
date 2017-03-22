//
// Trade.cpp
//
// 201770322
//

#include "Trade.h"

//
// constructors  / destructor
//

Trade::Trade()
{

}

Trade::Trade(time_t timeStamp, double quantity, TradeType type, double price)
: m_timeStamp(timeStamp),
  m_quantity(quantity),
  m_type(type),
  m_price(price)
{

}

Trade::~Trade()
{

}

Trade::Trade(const Trade &t)
: m_timeStamp(t.m_timeStamp),
  m_quantity(t.m_quantity),
  m_type(t.m_type),
  m_price(t.m_price)
{

}

Trade &Trade::operator =(const Trade &t)
{
    if(this != &t)
    {
        m_timeStamp = t.m_timeStamp;
        m_quantity = t.m_quantity;
        m_type = t.m_type;
        m_price = t.m_price;
    }

    return *this;
}

//
// get methods
//

time_t Trade::getTimeStamp() const
{
    return m_timeStamp;
}

double  Trade::getQuantity() const
{
    return m_quantity;
}

TradeType Trade::getType() const
{
    return m_type;
}

double Trade::getPrice() const
{
    return m_price;
}

//
// set methods
//

void Trade::setTimeStamp(time_t timeStamp)
{
    m_timeStamp = timeStamp;
}

void Trade::setQuantity(double quantity)
{
    m_quantity = quantity;
}

void Trade::setType(TradeType type)
{
    m_type = type;
}

void Trade::setPrice(double price)
{
    m_price = price;
}





