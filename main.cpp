#include <QSqlDatabase> //მონეცმთა ბაზის ტიპის განსაზღვრის კლასი
#include <QSqlError> //სქლ შეცდომების დამჭერი
#include <QStringList>
#include <QtDebug>
#include <QSql> //ბაზის კლასი
#include <QCoreApplication>
#include <QPluginLoader> //დამატებების ჩამტვირთავი კლასი
#include <QSqlQuery> //სქლ-ის ბრძანებების კლასი
#include <QSqlRecord> //ბაზის პასუხის შემნახველი

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //ტიპის განსაზღვრა ამ შემთხვევაში SQLite
    db.setDatabaseName("/home/alex/newbase"); //მისამართის მითითება (თუ არ არსებობს ფაილი ასეთი შეიქმნება)
    if(db.open()){ //თუ ბაზა გახსნადია ან გახსნილია
        qDebug()<<"ბაზას დაუკავშირდა";
    }
    else qDebug()<<"ვერ დაკავშირდა";
    QSqlQuery query; //ბრძანების გაშვების კლასის ობიექტი
    /*
    * შექმენი ცხრილი gakvetili
    *  რომელსაც ექნება ცვლადები
    *  number არის int ტიპის რომელიც არ არის ნოლი და რომელიც არის მთავარი ელემენტი ბაზაში
    *  name არის 30 ელემენტიანი ჩარების მასივი (იგივე სტრინგი)
    *  ანალოგიურად sname და position
    *  salary არის int ცვლადი
    */
    QString go = "CREATE TABLE gakvetili("
            "number integer PRIMARY KEY NOT NULL,"
            "name VARCHAR(30),"
            "sname VARCHAR(30),"
            "position VARCHAR(30),"
            "salary integer"
            ");";
    bool b = query.exec(go); //query.exec() მეთოდი აბრუნებს 1 ან 0-იანს იმის მიხედვით, შესრულდა თუ არა სკრიპტი
    if(!b){
        qDebug()<<"ვერ მოხერხდა ცხრილის შექმნა";
    }
    else qDebug()<<"ცხრილი წარმატებით შეიქმნა";

    //ეს სტრინგი არის მონაცემთა ბაზის ბრძანება, სტრინგი ასევე ელოდება არგუმენტებს
    QString strInsert = "INSERT INTO gakvetili(number,name,sname,position,salary)"
            "VALUES(%1, '%2', '%3', '%4', %5);";
    go = strInsert.arg("1")
            .arg("მიხეილ")
            .arg("სააკაშვილი")
            .arg("პრეზიდენტი")
            .arg("3000");
    b = query.exec(go);
    if(!b){
        qDebug()<<"ვერ ხერხდება მონაცემების ჩასმა";
    }
    else qDebug()<<"მონაცემების წარმატებით ჩაისვა";
    if(!query.exec("SELECT * FROM gakvetili")){
        qDebug()<<"ვერ მოინიშნა ინფორმაცია";
    }
    qDebug()<<"მონაცემები წარმატებით მოინიშნა";
    QSqlRecord rec= query.record(); //მონაცემთა ბაზიდან დაბრუნებული ინფორმაციის შემნახველი კლასის ობიექტი
    QString name;
    QString sName;
    QString position;
    int salary;
    while(query.next()){ //სანამ შეიძლება ზემოთ დაწერილი ბრძანების გაშვება (ანუ სანამ არის საკმარისი ინფორმაცია)
        //query.value(rec.indexOf()) მეთოდი აბრუნებს ჩვენთვის სასურველ ინფორმაციას ჩვეულერბრივი C++ის ცვლადებად
        name= query.value(rec.indexOf("name")).toString();
        sName = query.value(rec.indexOf("sname")).toString();
        position = query.value(rec.indexOf("position")).toString();
        salary = query.value(rec.indexOf("salary")).toInt();
        qDebug()<<name<<" "<<sName<< " "<<position<<" "<<salary;
    }

    return a.exec();
}
