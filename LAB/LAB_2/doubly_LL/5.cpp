#include <iostream>
#include <list>
using namespace std;

class DataLog {
private:
    list<int> logList;
    list<int>::iterator currentState;

public:
    DataLog();
    DataLog(const int &data);
    void addCurrentState(int number);
    void subtractCurrentState(int number);
    void save();
    void undo();
    void redo();

    int getCurrentStateData(){
        return *currentState;
    }

    void printLog()
    {
        for (auto i = logList.begin(); i != logList.end(); i++) {
            if(i == currentState) cout << "Current state: ";
            cout << "[ " << *i << " ] => ";
        }
        cout << "END_LOG";
    }
};

DataLog::DataLog()
{
    /*
     * TODO:  add the first state with 0
     */
    logList.push_front(0);
    currentState = logList.begin();
}

DataLog::DataLog(const int &data)
{
    /*
     * TODO:  add the first state with data
     */
    logList.push_front(data);
    currentState = logList.begin();
}

void DataLog::addCurrentState(int number)
{
    /*
     * TODO: Increase the value of current state by number
     */
    int tmp = getCurrentStateData() + number;
    *currentState = tmp;
}

void DataLog::subtractCurrentState(int number)
{
    /*
     * TODO: Decrease the value of current state by number
     */
    int tmp = getCurrentStateData() - number;
    *currentState = tmp;
}

void DataLog::save()
{
    /*
     * TODO: This function will create a new state, copy the data of the currentState
     *       and move the currentState Iterator to this new state. If there are other states behind the
     *       currentState Iterator, we delete them all before creating a new state.
     */
    logList.insert(currentState, getCurrentStateData());
}

void DataLog::undo()
{
    /*
     * TODO: Switch to the previous state of the data
     *       If this is the oldest state in the log, nothing changes
     */
    list<int>::iterator tmp = logList.begin();
    if (currentState != tmp) currentState--;
}

void DataLog::redo()
{
    /*
     * TODO: Switch to the latter state of the data
     *       If this is the latest state in the log, nothing changes
     */
    list<int>::iterator tmp = logList.end();
    if (currentState != --tmp) currentState++;
}


int main() {
    DataLog log(10);
    log.save();
    log.addCurrentState(15);
    log.save();
    log.addCurrentState(15);
    log.save();
    log.undo();
    log.undo();
    log.printLog();
    cout << "\n";
    log.save();
    log.printLog();

    cout << endl;

    return 0;
}