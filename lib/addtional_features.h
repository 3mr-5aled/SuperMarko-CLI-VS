#include <iostream>
#include "struct.h"
using namespace std;

ORDER applyVAT(ORDER &order, double VAT_RATE = 14)
{
    order.TotalPrice *= (1 + (VAT_RATE / 100));
    return order; // Return reference to modified order
}
ORDER applyDiscount(ORDER &order, double DISCOUNT_RATE = 10)
{
    order.TotalPrice *= (1 - (DISCOUNT_RATE / 100));
    return order; // Return reference to modified order
}
ORDER ShippingCost(ORDER &order, double SHIPPING_COST = 100)
{
    order.TotalPrice += SHIPPING_COST;
    return order; // Return reference to modified order
}
