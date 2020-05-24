#include <iostream>
#include <system/string.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include <Aspose.Words.Cpp/Model/Document/Document.h>
#include <Aspose.Words.Cpp/Model/Text/Range.h>
#include <Aspose.Words.Cpp/Model/FindReplace/FindReplaceOptions.h>
#include <Aspose.Words.Cpp/Model/FindReplace/FindReplaceDirection.h>
#include <Aspose.Words.Cpp/Model/Saving/PdfSaveOptions.h>

using namespace std;
using namespace System;
using namespace Aspose::Words;
using namespace Aspose::Words::Replacing;

double mout, minin, sms, pricet, pricesms; //минуты входящих, минуты исходящих, количество смс с номера, цена телефонии
double sumbyte, priceint; ////байтов отправлено, всего байтов отправлено, цена интернета

void Telephony()
{
    string phone; //данный номер телефона
    vector<string> c(5); //вектор полей строк файла
    vector<double> k(3); //вектор множителей тарифного плана
    vector<double> free(3); //вектор времени, в которое звонки бесплатны/кол-ва бесплатных смс

    phone = "911926375";
    k[0] = 2;
    k[1] = 1;
    k[2] = 1;
    free[0] = 0;
    free[1] = 50;
    free[2] = 0;

    ifstream fileToRead("data1.csv");

    string line, word, temp;

    while (getline(fileToRead, line))
    {
        c.clear();

        stringstream s(line); //строка вводится в s
        while (getline(s, word, ','))
        {
            c.push_back(word); //разделяет строку на слова с разделителем запятая, помещает в вектор с
        }

        //c[0] = timestamp
        //c[1] = origin
        //c[2] = dest
        //c[3] = call_duration
        //c[4] = sms_number

        if (c[1] == phone) //если номер найден в поле источника
        {
            mout += stod(c[3]);
            sms += stod(c[4]);
        }
        if (c[2] == phone) //если номер найден в поле назначения
        {
            minin += stod(c[3]);
        }
    }
    fileToRead.close();

    if (mout > free[0])
    {
        pricet += k[0] * (mout - free[0]);
    }
    if (minin > free[1])
    {
        pricet += k[1] * (minin - free[1]);
    }
    if (sms > free[2])
    {
        pricesms += k[2] * (sms - free[2]);
    }
}

void Internet()
{
    string ip; //данный айпи
    double k; //множитель тарифного плана
    ip = "192.168.250.41";
    k = 1;
    vector<string> c(48); //вектор полей строк файла

    ifstream fileToRead("data2.csv");

    string line, word, temp;

    while (getline(fileToRead, line))
    {
        c.clear();

        stringstream s(line); //строка вводится в s
        while (getline(s, word, ','))
        {
            c.push_back(word); //разделяет строку на слова с разделителем запятая, помещает в вектор с
        }

        //c[3] = source address
        //c[4] = destination address
        //c[12] = In byte
        if (c[0] == "Summary")
        {
            break;
        }
        if (c[3] == ip) //если ip найден в поле da
        {
            sumbyte += stod(c[12]);
        }
    }
    fileToRead.close();

    sumbyte = round(sumbyte * 800 / 1048576) / 100;

    priceint = sumbyte * k;
}

void FindAndReplace()
{
    String documentPath = u"template.doc";
    String outputPath = u"output.pdf";

    SharedPtr<Document> doc = MakeObject<Document>(documentPath);

    doc->get_Range()->Replace(u"{{recipient.bank.name}}", u"Банк Университета \"ИТМО\"", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{recipient.bank.bik}}", u"3350", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{recipient.bank.account}}", u"3350243999", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{recipient.inn}}", u"2439991", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{recipient.ppc}}", u"2439992", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{recipient.name}}", u"Санжиев Доржи Чимитович", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{recipient.account}}", u"2439993", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{id}}", u"3", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{date}}", u"24.05.19", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{recipient.inn}}", u"2439994", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{recipient.address}}", u"243999, Санкт-Петербург г., Энергетиков пр., дом 8, корпус 17", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{consumer.address}}", u"243999, Санкт-Петербург г., Энергетиков пр., дом 8, корпус 16", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{consumer.name}}", u"Доржиев Санжи Чингисович", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{consumer.inn}}", u"2439995", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{consumer.ppc}}", u"2439996", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{reason}}", u"№ N3350 от 24.05.2020", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{recipient.director}}", u"Динозавров Д.И.", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{recipient.accountant}}", u"Мегалодонов М.Е.", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{1.description}}", u"Звонки", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{2.description}}", u"СМС", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{3.description}}", u"Интернет", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{1.unit}}", u"мин", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{2.unit}}", u"шт", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{3.unit}}", u"Мб", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{1.price}}", u"2 руб/мин исходящие, 0 руб/мин входящие первые 50 минут, далее 1 руб/мин", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{2.price}}", u"1 руб/шт", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));
    doc->get_Range()->Replace(u"{{3.price}}", u"1руб/Мб", MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));

    String tempo;

    tempo += mout;
    tempo += u" / ";
    tempo += minin;
    doc->get_Range()->Replace(u"{{1.quantity}}", tempo, MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));

    tempo = u"";
    tempo += sms;
    doc->get_Range()->Replace(u"{{2.quantity}}", tempo, MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));

    tempo = u"";
    tempo += sumbyte;
    doc->get_Range()->Replace(u"{{3.quantity}}", tempo, MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));

    tempo = u"";
    tempo += pricet;
    doc->get_Range()->Replace(u"{{1.amount}}", tempo, MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));

    tempo = u"";
    tempo += pricesms;
    doc->get_Range()->Replace(u"{{2.amount}}", tempo, MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));

    tempo = u"";
    tempo += priceint;
    doc->get_Range()->Replace(u"{{3.amount}}", tempo, MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));

    tempo = u"";
    tempo += pricet + pricesms + priceint;
    doc->get_Range()->Replace(u"{{total}}", tempo, MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));

    tempo = u"";
    tempo += (pricet + pricesms + priceint) / 5;
    doc->get_Range()->Replace(u"{{taxes}}", tempo, MakeObject<FindReplaceOptions>(FindReplaceDirection::Forward));

    doc->Save(outputPath);
}

int main()
{
    Telephony();
    Internet();
    FindAndReplace();

    return 0;
}