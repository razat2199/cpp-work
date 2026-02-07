#include<iostream>
using namespace std;

class XMLData {
    string xmlData;
public:
    XMLData(string pXmlData) {
        xmlData = pXmlData;
    }
    string getXMLData() {
        return xmlData;
    }
};

class DataAnalyticsTool{
    string jsonData;
public:
    DataAnalyticsTool() {}
    DataAnalyticsTool(string pJsonData) {
        jsonData = pJsonData;
    }
    virtual void analyseData() {   // virtual added coz analyseData will be called from adapter
        cout << "Analyse Data " << jsonData << endl;
    }
};

class Adapter: public DataAnalyticsTool {
private:
    XMLData* xmlData;
public:
    Adapter(XMLData* pXmlData) {
        xmlData = pXmlData;
    }
    void analyseData() override {
       cout << "Converting XML Data " << xmlData->getXMLData() << " to JSON Data" << endl;
       cout << "Analysing the converted JSON data" << endl; 
    }
};

class Client {
    public:
        void ProcessData (DataAnalyticsTool* tool) {
            tool->analyseData();
        }
};

int main () {
    XMLData* xmlData = new XMLData("Samplw XML Data");
    // DataAnalytics tool expects json data, not xml data, hence create Adapter Class, without bothering client
    // DataAnalyticsTool* tool = new DataAnalyticsTool("");
    DataAnalyticsTool* tool = new Adapter(xmlData); // changed the object type to adapter, client not bothered

    Client* client = new Client;
    client->ProcessData(tool);
    return 0;
}