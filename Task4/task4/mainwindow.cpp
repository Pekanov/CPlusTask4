#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QFileDialog>
#include<iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

map<string, vector<string>> studs;
string file;

 map<string, vector<string>> parseFile(string fileName){
    ifstream ifs(fileName);
    map<string, vector<string>> mymap;
    if(ifs.is_open()){
        while(ifs){
            using input = istream_iterator<string>;
            string line;
            getline(ifs, line);
            istringstream iss(line);
            vector<string> data({input(iss), input()});
            if(data.size() >=2) {
                vector<string> v = {data.begin()+1, data.end()};
                mymap.emplace(data[0], v);
            }
        }
    }
    return mymap;

}

 void insertInFile(string insertion){
     ofstream fileOut;
     fileOut.open(file, ios::app);
     fileOut.write(insertion.c_str(), insertion.length());
     fileOut << endl;
     fileOut.close();
 }

 QString displayList(map<string, vector<string>> v){
     string res = "";
     for(auto item: v){
         res += item.first + ": ";
         for(auto a: item.second){
             res += a + " ";
         }
         res += "\n";
     }
     return(QString::fromStdString(res));
 }


void MainWindow::on_pushButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Text File (*.txt)");
    file = filename.toStdString();
    studs = parseFile(file);
    ui->textBrowser->setText(displayList(studs));


    //cout<<filename.toStdString()<<endl;
}


void MainWindow::on_groupBox_3_toggled(bool arg1)
{

}


void MainWindow::on_pushButton_3_clicked()//insert button
{
    string insertion = "\n" + ui->lineEdit->displayText().toStdString();
    int check = insertion.size();
    if(ui->checkBox_10->isChecked()){
        insertion += " математика";
    }
    if(ui->checkBox_9->isChecked()){
        insertion += " физика";
    }
    if(ui->checkBox_11->isChecked()){
        insertion += " биология";
    }
    if(ui->checkBox_12->isChecked()){
        insertion += " химия";
    }
    if(insertion.size() > check){
        insertInFile(insertion);
        studs = parseFile(file);
        displayList(studs);
    }
    ui->textBrowser->setText(displayList(studs));
}

bool findInVect(vector<string> v, string s){
    for(string str: v){
        if(str==s) return true;
    }
    return false;
}


void MainWindow::on_pushButton_2_clicked()//select button
{
    vector<string> include;
    vector<string> ban;

    if(ui->checkBox_6->isChecked()){
        ban.push_back("математика");
    }
    if(ui->checkBox_5->isChecked()){
        ban.push_back("физика");
    }
    if(ui->checkBox_7->isChecked()){
        ban.push_back("биология");
    }
    if(ui->checkBox_8->isChecked()){
        ban.push_back("химия");
    }

    if(ui->checkBox_2->isChecked()){
        include.push_back("математика");
    }
    if(ui->checkBox->isChecked()){
        include.push_back("физика");
    }
    if(ui->checkBox_3->isChecked()){
        include.push_back("биология");
    }
    if(ui->checkBox_4->isChecked()){
        include.push_back("химия");
    }

    if(ban.empty()){

    }
    else{
        vector<string> tmp;
        for(string s: include){
            bool flag = true;
            for(string i: ban){
                if(i==s){
                    flag = false;
                }
            }
            if(flag){
                tmp.push_back(s);
            }
        }
        include = tmp;
    }
    map <string, vector<string>> newMap;
    string tmp;
    for(auto item: studs){
        tmp = item.first;
        bool f = true;
        for(string c: include){
            bool miniF = false;
            for(auto a: item.second){
                if(a == c ){
                    miniF = true;
                }
                if(findInVect(ban, a)){
                    miniF = false;
                    break;
                }
            }
            if(!miniF){
                f= false;
            }

        }
        if(f){
            newMap.emplace(item.first, item.second);
        }
    }
    ui->textBrowser->setText(displayList(newMap));
}

