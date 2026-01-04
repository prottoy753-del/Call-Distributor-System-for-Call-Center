#include <iostream>

using namespace std;

class Call {

public:

    int callID;

    int arrivalTime;

    Call() {

        callID = 0;

        arrivalTime = 0;
    }

    Call(int id, int time) {

        callID = id;

        arrivalTime = time;
    }
};

class Stack {

    int top;

    Call arr[50];

public:

    Stack() {

        top = -1;
    }

    void push(Call c) {

        arr[++top] = c;
    }
};

class Queue {

    int front, rear;

    Call arr[100];

public:

    Queue() {

        front = rear = -1;
    }

    bool isEmpty() {

        return front == -1;
    }

    void enqueue(Call c) {

        if (front == -1)

            front = 0;

        arr[++rear] = c;
    }

    Call dequeue() {

        Call c = arr[front];

        if (front == rear)

            front = rear = -1;

        else

            front++;

        return c;
    }
};

class Server {

public:

    int serverID;

    bool busy;

    int remainingTime;

    int totalCalls;

    Stack history;

    Server *next;

    Server(int id) {

        serverID = id;

        busy = false;

        remainingTime = 0;

        totalCalls = 0;

        next = NULL;
    }
};

Server *createServers(int n) {

    Server *head = NULL;

    Server *tail = NULL;

    for (int i = 1; i <= n; i++) {

        Server *s = new Server(i);

        if (head == NULL) {

            head = tail = s;

        } else {

            tail->next = s;

            tail = s;
        }
    }

    return head;
}

int main() {

    int numServers, numCalls;

    cout << "Enter number of servers: ";

    cin >> numServers;

    cout << "Enter number of incoming calls: ";

    cin >> numCalls;

    Queue callQueue;

    Server *servers = createServers(numServers);

    for (int i = 1; i <= numCalls; i++) {

        int time;

        cout << "Enter arrival time of call " << i << ": ";

        cin >> time;

        callQueue.enqueue(Call(i, time));
    }

    int time = 0;

    while (!callQueue.isEmpty() || time < 50) {

        time++;

        Server *temp = servers;

        while (temp != NULL) {

            if (temp->busy) {

                temp->remainingTime--;

                if (temp->remainingTime == 0) {

                    temp->busy = false;
                }
            }

            if (!temp->busy && !callQueue.isEmpty()) {

                Call c = callQueue.dequeue();

                temp->busy = true;

                temp->remainingTime = 10;

                temp->totalCalls++;

                temp->history.push(c);
            }

            temp = temp->next;
        }
    }

    cout << "Call Distribution Statistics are: \n";

    Server* s = servers;

    while (s != NULL) {

        cout << "Server " << s->serverID << " handled " << s->totalCalls << " calls \n";

        s = s->next;
    }

    return 0;
}
