var
mout, min, sms, P:real; //минуты входящих, минуты исходящих, количество смс с номера, цена
num:string; //данный номер телефона
k:array[1..3] of real; //массив множителей тарифного плана
free:array[1..3] of real; //массив времени, в которое звонки бесплатны/кол-ва бесплатных смс
c:array of string; //динамический массив полей строк файла
skip:boolean; //для пропуска первой строки
begin
num:='911926375';
k[1]:=2;
k[2]:=1;
k[3]:=1;
free[1]:=0;
free[2]:=50;
free[3]:=0;
skip:=False;
foreach var s in ReadLines('data.csv') do begin //ReadLines открывает файл и преобразует в последовательность строк, foreach проводит цикл для каждой
  if skip=True then begin
   c:= s.toWords(','); //разделяет строки на слова с разделителем запятая, помещает в массив с
   if c[1]=num then begin //если номер найден в поле источника
    mout+=StrToFloat(c[3]); //strtofloat переводит строку в real
    sms+=StrToFloat(c[4]);
   end
   else if c[2]=num then //если номер найден в поле назначения
    min+=StrToFloat(c[3]);
  end
  else skip:=True; //пропускает первую строку с информацией о полях строк
end;
writeln('Длительность исходящих звонков: ',mout);
writeln('Длительность входящих звонков: ',min);
writeln('Количество смс, присланных с этого номера: ',sms);
if mout>free[1] then P+=k[1]*(mout-free[1]);
if min>free[2] then P+=k[2]*(min-free[2]);
if sms>free[3] then P+=k[3]*(sms-free[3]);
writeln('Цена: ',P);
end.