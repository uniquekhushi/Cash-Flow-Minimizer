# Cash-Flow-Minimizer
The Cash Flow Minimizer project aims to reduce the number of financial transactions required to settle debts among multiple banks. The primary goal is to optimize cash flows and minimize transaction costs by consolidating payments and using an intermediary (World Bank) when direct transactions are not possible due to differing payment modes.

# In the Cash Flow Minimizer project, the primary algorithms used include the following:

1. Greedy Algorithm for Minimizing Transactions:

This algorithm works by always trying to settle the largest outstanding amounts first, ensuring that the transactions with the highest values are processed and reduced in the minimal number of steps.

2.  Graph Representation:

An adjacency matrix represents the debts between banks. Each cell in the matrix holds the amount of debt from one bank to another.
This matrix is used to calculate the net amounts owed by each bank and to track the settlements during the process.

3. Priority Queue (Implicit):

Although not explicitly implemented as a priority queue, the repeated process of finding the bank with the maximum and minimum net amounts functions similarly to how a priority queue would operate in terms of always selecting the highest-priority elements (largest debt and largest credit).

Given In
