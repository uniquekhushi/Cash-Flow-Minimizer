#include <iostream>
#include <set>
#include <unordered_map>
#include <climits>
using namespace std;

class Bank {
public:
    string name; 
    int netAmount; 
    set<string> types;
};

int getMinIndex(Bank banks[], int numBanks) {
    int minIndex = -1, minAmount = INT_MAX;
    for (int i = 0; i < numBanks; i++) {
        if (banks[i].netAmount < minAmount && banks[i].netAmount != 0) {
            minAmount = banks[i].netAmount;
            minIndex = i;
        }
    }
    return minIndex;
}

int getSimpleMaxIndex(Bank banks[], int numBanks) {
    int maxIndex = -1, maxAmount = INT_MIN;
    for (int i = 0; i < numBanks; i++) {
        if (banks[i].netAmount > maxAmount && banks[i].netAmount != 0) {
            maxAmount = banks[i].netAmount;
            maxIndex = i;
        }
    }
    return maxIndex;
}

int getMaxIndex(Bank banks[], int numBanks, int minIndex, string &commonType, int maxTypes) {
    int maxIndex = -1, maxAmount = INT_MIN;

    for (int i = 0; i < numBanks; i++) {
        if (banks[i].netAmount <= 0) continue;

        set<string> &minTypes = banks[minIndex].types;
        set<string> &iTypes = banks[i].types;

        for (const string &type : minTypes) {
            if (iTypes.count(type)) {
                if (banks[i].netAmount > maxAmount) {
                    maxAmount = banks[i].netAmount;
                    maxIndex = i;
                    commonType = type;
                }
            }
        }
    }
    return maxIndex;
}

void printTransactions(int transactions[50][50], string types[50][50], int numBanks, Bank banks[]) {
    cout << "The transactions for minimum cash flow are:\n";
    for (int i = 0; i < numBanks; i++) {
        for (int j = 0; j < numBanks; j++) {
            if (transactions[i][j] > 0) {
                cout << banks[i].name << " pays Rs " << transactions[i][j] << " to " << banks[j].name << " via " << types[i][j] << endl;
            }
        }
    }
}

void minimizeCashFlow(int numBanks, Bank banks[], int maxTypes, int transactions[50][50]) {
    Bank netAmounts[numBanks];

    for (int i = 0; i < numBanks; i++) {
        netAmounts[i].name = banks[i].name;
        netAmounts[i].types = banks[i].types;

        int amount = 0;
        for (int j = 0; j < numBanks; j++) {
            amount += transactions[j][i] - transactions[i][j];
        }
        netAmounts[i].netAmount = amount;
    }

    int result[50][50] = {0};
    string resultTypes[50][50];
    int zeroNetAmounts = 0;

    while (zeroNetAmounts != numBanks) {
        int minIndex = getMinIndex(netAmounts, numBanks);
        string commonType;
        int maxIndex = getMaxIndex(netAmounts, numBanks, minIndex, commonType, maxTypes);

        if (maxIndex == -1) {
            int simpleMaxIndex = getSimpleMaxIndex(netAmounts, numBanks);
            result[0][simpleMaxIndex] += abs(netAmounts[minIndex].netAmount);
            resultTypes[0][simpleMaxIndex] = *banks[simpleMaxIndex].types.begin();
            netAmounts[simpleMaxIndex].netAmount += netAmounts[minIndex].netAmount;
            netAmounts[minIndex].netAmount = 0;
        } else {
            int transferAmount = min(abs(netAmounts[minIndex].netAmount), netAmounts[maxIndex].netAmount);
            result[minIndex][maxIndex] += transferAmount;
            resultTypes[minIndex][maxIndex] = commonType;
            netAmounts[minIndex].netAmount += transferAmount;
            netAmounts[maxIndex].netAmount -= transferAmount;
        }

        zeroNetAmounts = 0;
        for (int i = 0; i < numBanks; i++) {
            if (netAmounts[i].netAmount == 0) zeroNetAmounts++;
        }
    }

    printTransactions(result, resultTypes, numBanks, banks);
}

int main() {
    cout << "Welcome to CASH FLOW MINIMIZER SYSTEM\n";
    cout << "Enter the number of banks: ";
    int numBanks; cin >> numBanks;

    Bank banks[numBanks];
    unordered_map<string, int> bankIndex;

    cout << "Enter details of banks (name and payment modes):\n";
    int maxTypes;
    for (int i = 0; i < numBanks; i++) {
        cin >> banks[i].name;
        bankIndex[banks[i].name] = i;

        int numTypes; cin >> numTypes;
        if (i == 0) maxTypes = numTypes;

        while (numTypes--) {
            string type; cin >> type;
            banks[i].types.insert(type);
        }
    }

    cout << "Enter number of transactions: ";
    int numTransactions; cin >> numTransactions;

    int transactions[50][50] = {0};
    cout << "Enter details of each transaction (debtor, creditor, amount):\n";
    for (int i = 0; i < numTransactions; i++) {
        string debtor, creditor; int amount;
        cin >> debtor >> creditor >> amount;
        transactions[bankIndex[debtor]][bankIndex[creditor]] = amount;
    }

    minimizeCashFlow(numBanks, banks, maxTypes, transactions);
    return 0;
}
