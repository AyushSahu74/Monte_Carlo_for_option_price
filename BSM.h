#include <iostream>

class BSM
{
public:
    BSM(
        float, float, float, float, float, float, long, long);

    float getBsmAssetPrice();
    float getBsmStrikePrice();
    float getBsmGrowth();
    float getBsmVolatility();
    float getBsmYears();
    float getBsmRiskFreeRate();
    long getBsmSteps();
    long getBsmMonteCarloSims();

    void setBsmAssetPrice(float);
    void setBsmStrikePrice(float);
    void setBsmGrowth(float);
    void setBsmVolatility(float);
    void setBsmYears(float);
    void setBsmRiskFreeRate(float);
    void setBsmSteps(long);
    void setBsmMonteCarloSims(long);

    void logNormalRandomWalk();

    double getBsmCallPrice();
    double getBsmPutPrice();
    void setBsmCallPrice(double);
    void setBsmPutPrice(double);

    double rn();        // Function to generate random number
    double rn_normal(); // Box-Muller transformation

    ~BSM();

private:
    float bsmAssetPrice;
    float bsmStrikePrice;
    float bsmMarketGrowth;
    float bsmAssetVol;
    float bsmYrsToExpiry;
    float bsmRiskFreeRate;
    long bsmSteps;
    long bsmMonteCarloSims;
    double bsmCallPrice;
    double bsmPutPrice;
};