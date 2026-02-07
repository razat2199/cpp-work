#include<iostream>
#include<list>
using namespace std;

class ISubscriber {
    public:
        virtual void notify(string msg) = 0;  // pure virtual
};
class User: public ISubscriber{
    private:
        int userId;
    public:
        User(int userId) {
            this->userId = userId;
        }
        void notify (string msg) {
            cout << "Received " << msg << endl;
        }
};

class Group {
    private:
        list<ISubscriber*> userList;
    public:
        void subscribe(User* user) {
            userList.push_back(user);
        }
        void unsubscribe(User* user) {
            userList.remove(user);
        }
        void notifyUsers(string msg) {
            for (auto user: userList) {
                user->notify(msg);
            }
        }
};

int main () {
    Group* group = new Group();

    User* user1 = new User(1);
    User* user2 = new User(2);
    User* user3 = new User(3);

    group->subscribe(user1);
    group->subscribe(user2);
    group->subscribe(user3);
    group->notifyUsers("msg1");

    group->unsubscribe(user1);
    group->notifyUsers("msg2");
    return 0;
}