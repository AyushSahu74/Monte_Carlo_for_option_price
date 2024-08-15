#include "BSM.h"
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <math.h>
#include <cmath>
#include <random>
using namespace std;

BSM::BSM(
    float assPrc,
    float strPrc,
    float gth,
    float vola,
    float yrs,
    float risk,
    long stps,
    long monsims)
{
    setBsmAssetPrice(assPrc);
    setBsmStrikePrice(strPrc);
    setBsmGrowth(gth);
    setBsmVolatility(vola);
    setBsmYears(yrs);
    setBsmRiskFreeRate(risk);
    setBsmSteps(stps);
    setBsmMonteCarloSims(monsims);
};

// Function to generate a random number between min and max (inclusive)
double BSM::rn()
{
    return (double)rand() / (double)(RAND_MAX + 1.0);
};

BSM::~BSM() {};

// Box muller transformation
mt19937 gen; // Mersenne Twister random number generator
uniform_real_distribution<double> dis; // Uniform distribution for Box-Muller

// Box-Muller transformation
double BSM::rn_normal() {
    double u1 = dis(gen); // Generate two random numbers between 0 and 1
    double u2 = dis(gen);

    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    return z0; // We only need one standard normal random variable, so return z0
}

void BSM::logNormalRandomWalk()
{
    double callPayoffPot = 0;
    double putPayoffPot = 0;

    double timeStep = getBsmYears() / getBsmSteps();
    double r = getBsmRiskFreeRate();
    double mu = getBsmGrowth();
    double sigma = getBsmVolatility();

    for (long i = 1; i <= getBsmMonteCarloSims() / 2; i++)
    {
        double assPrice1 = getBsmAssetPrice();
        double assPrice2 = getBsmAssetPrice();

        for (int j = 1; j <= getBsmSteps(); j++)
        {
            double drift = (mu - 0.5 * sigma * sigma) * timeStep;
            double diffusion1 = sigma * sqrt(timeStep) * rn_normal();
            double diffusion2 = -diffusion1; // Antithetic variate

            assPrice1 *= exp(drift + diffusion1);
            assPrice2 *= exp(drift + diffusion2);
        }

        callPayoffPot += max(assPrice1 - getBsmStrikePrice(), 0.0) +
                        max(assPrice2 - getBsmStrikePrice(), 0.0);
        putPayoffPot += max(getBsmStrikePrice() - assPrice1, 0.0) +
                        max(getBsmStrikePrice() - assPrice2, 0.0);
    }

    setBsmCallPrice((callPayoffPot / getBsmMonteCarloSims()) * exp(-r * getBsmYears()));
    setBsmPutPrice((putPayoffPot / getBsmMonteCarloSims()) * exp(-r * getBsmYears()));
}

void BSM::setBsmCallPrice(double prc)
{
    bsmCallPrice = prc;
}

void BSM::setBsmPutPrice(double prc)
{
    bsmPutPrice = prc;
}

double BSM::getBsmCallPrice()
{
    return bsmCallPrice;
}

double BSM::getBsmPutPrice()
{
    return bsmPutPrice;
}

float BSM::getBsmAssetPrice()
{
    return bsmAssetPrice;
};

float BSM::getBsmGrowth()
{
    return bsmMarketGrowth;
};

long BSM::getBsmMonteCarloSims()
{
    return bsmMonteCarloSims;
};

long BSM::getBsmSteps()
{
    return bsmSteps;
};

float BSM::getBsmStrikePrice()
{
    return bsmStrikePrice;
};

float BSM::getBsmVolatility()
{
    return bsmAssetVol;
};

float BSM::getBsmYears()
{
    return bsmYrsToExpiry;
}

float BSM::getBsmRiskFreeRate()
{
    return bsmRiskFreeRate;
}

void BSM::setBsmAssetPrice(float asstPrc)
{
    bsmAssetPrice = asstPrc;
};
void BSM::setBsmStrikePrice(float strkPrc)
{
    bsmStrikePrice = strkPrc;
};
void BSM::setBsmGrowth(float grwth)
{
    bsmMarketGrowth = grwth;
};
void BSM::setBsmVolatility(float vlt)
{
    bsmAssetVol = vlt;
};
void BSM::setBsmYears(float yrs)
{
    bsmYrsToExpiry = yrs;
};
void BSM::setBsmRiskFreeRate(float risk)
{
    bsmRiskFreeRate = risk;
};
void BSM::setBsmSteps(long stps)
{
    bsmSteps = stps;
};
void BSM::setBsmMonteCarloSims(long montsims)
{
    bsmMonteCarloSims = montsims;
};