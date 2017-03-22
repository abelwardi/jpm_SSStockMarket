# jpm_SSStockMarket
Example Assignment – Super Simple Stock Market
22/03/2017

- C++ 11
- Code::Blocks 16.01
- cygwin g++


To run the program :
run launchSSSM.bat

you need 5 parameters :

stocks.csv
csv file (space separator) contains list of stocks,
(stock symbol, stock type, last Dividend, fixed Dividend, par Value)

example :

TEA COMMON 0 0 100

POP COMMON 8 0 100
...

trades.csv
csv file (space separator) contains list of trades,
(stock symbol, timeStamp, quantity, type, price)
timeStamp : the trade datetime = number of seconds elapsed since January 1, 1970
The file must be sorted by timeStamp for every stock

example :

TEA 1490144508 50 SELL 1.25
JOE 1490145508 150 BUY 1.35
POP 1490146508 50 SELL 1.75
TEA 1490147508 550 BUY 1.27
GIN 1490148508 5000 BUY 1.05
.....

stockPrices.csv
csv file (space separator) contains list of stock price
(stock symbol, price)

example :

TEA 1.25
POP 0.99
ALE 2.011
.....

duration :
to calculate volume weighted stock srice
360 seconds for example

output stocksSSSM.csv :
csv file (space separator) contains stock results

example :

symbol price dividendYield peRatio VWSP GBCE
ALE 2.011 11.4371 0.0874348 -1 1.25
GIN 15.1264 0.132219 1.8908 -1 2.30856
JOE 1.054 12.334 0.0810769 -1 2.58749
