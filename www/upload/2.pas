program ex4v;
{BaaBB}
var
  S: string;
  i, j: integer;

begin
  writeln('Введите строку символов ');
  readln(S);
  
  for i := 1 to Length(s) do 
    begin
      if s[i] = 'B' then Delete(s, i, 1);   

    end;
      
  writeln('Строка без символов -В-', s); readln;
end.