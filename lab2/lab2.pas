var
nbyte, sumbyte, P:real; //байтов отправлено, всего байтов отправлено, цена
ip, f:string; //данный номер телефона, выходной файл
k:real; //множитель тарифного плана
c:array of string; //динамический массив полей строк файла
begin
ip:='192.168.250.41';
k:=1;
f:= 'Информация по ip 192.168.250.41'+#10+'Время, байтов отправлено, всего байтов отправлено'+#10;
foreach var s in ReadLines('data2.csv') do begin //ReadLines открывает файл и преобразует в последовательность строк, foreach проводит цикл для каждой
  c:= s.toWords(','); //разделяет строки на слова с разделителем запятая, помещает в массив с
  if c[0]='Summary' then break//прерывается, когда доходит до конца
  else if c[4]=ip then begin //если ip найден в поле da
   nbyte:= StrToFloat(c[12]); //strtofloat переводит строку в real
   sumbyte+=nbyte;
   f+= c[0]+','+nbyte+','+sumbyte+#10;
  end
end;
WriteAllText('outputData.txt', f);
writeln('Всего байтов: ',sumbyte);
writeln('Всего мегабайтов: ',Round(sumbyte/1048576,2));
writeln('Всего мегабитов: ',Round(sumbyte*8/1048576,2));
P:= Round(k*sumbyte*8/1048576,2);
writeln('Цена: ',P,' рублей.');
end.