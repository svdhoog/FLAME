#include "../header.h"
#include "../firm_agent_header.h"

/*
 * \fn: int firm_consumption_supply()
 * \brief:
 */
int firm_consumption_supply()
{
    
    //if (ISCONSTRUCTOR == 1) {
    //    return 0;
    //}
    
    if (UNIT_GOODS_PRICE == 0) {
        return 0;
    }
    if (INVENTORY > 0 && UNIT_GOODS_PRICE > 0) {
        add_sell_message(ID, UNIT_GOODS_PRICE, INVENTORY);
        if (PRINT_DEBUG_MODE) {
         printf("Firm Id = %d Sends = %d Goods to Mall with a price = %f\n", ID, INVENTORY, UNIT_GOODS_PRICE);   
        }
    }

	return 0; /* Returning zero means the agent is not removed */
}

/*
 * \fn: int firm_consumption_recieve_sales()
 * \brief:
 */
int firm_consumption_receive_sales()
{
    int quantity_sold = 0;
    double weekly_sales_income = 0;
    
    START_SOLD_MESSAGE_LOOP
    quantity_sold += sold_message->sold_quantities;
	FINISH_SOLD_MESSAGE_LOOP
    weekly_sales_income = quantity_sold * UNIT_GOODS_PRICE;
    /* Updating the inventory. */
    INVENTORY -= quantity_sold;
    if (INVENTORY < 0){
        if (WARNING_MODE) {
            printf("Warning @firm_consumption_receive_sales(): More than available goods were sold Firm ID = %d, Inventory =%d \n", ID, INVENTORY);
        }
        INVENTORY = 0;
    }
    
    /* Updating the sales. */
    SALES += quantity_sold;
    LIQUIDITY += weekly_sales_income;
    REVENUES += weekly_sales_income;

    
    if (PRINT_DEBUG_MODE) {
        printf("Firm ID = %d Quantity Sold = %d Weekly Revenue = %f\n", ID, quantity_sold, weekly_sales_income);
    }

    
	return 0; /* Returning zero means the agent is not removed */
}

/*
 * \fn: int firm_consumption_update_market_price()
 * \brief: The producer firm gets average market price per good.
 */
int firm_consumption_update_market_price()
{
    if (PRINT_DEBUG_MODE) {
        printf("Firm ID = %d checks average goods price at the market\n", ID);
    }
    
    START_GOODS_TRANSACTIONS_SUMMARY_MESSAGE_LOOP
    AVERAGE_GOODS_PRICE = goods_transactions_summary_message->avg_price;
	FINISH_GOODS_TRANSACTIONS_SUMMARY_MESSAGE_LOOP
    

	return 0; /* Returning zero means the agent is not removed */
}
