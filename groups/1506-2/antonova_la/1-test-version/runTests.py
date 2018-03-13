import subprocess as pr
import sys
import random as rm

test=["tests/test_00.tst","tests/test_01.tst","tests/test_02.tst","tests/test_03.tst","tests/test_04.tst","tests/test_05.tst","tests/test_06.tst"
      "tests/test_07.tst","tests/test_08.tst","tests/test_09.tst","tests/test_10.tst"]

result=["results/result_00.rslt","results/result_01.rslt","results/result_02.rslt","results/result_03.rslt","results/result_04.rslt",
        "results/result_05.rslt","results/result_06.rslt","results/result_07.rslt","results/result_08.rslt","results/result_09.rslt",
        "results/result_10.rslt"]
answer=["answers/answer_00.answ","answers/answer_01.answ","answers/answer_02.answ","answers/answer_03.answ","answers/answer_04.answ",
        "answers/answer_05.answ","answers/answer_06.answ","answers/answer_07.answ","answers/answer_08.answ","answers/answer_09.answ",
        "answers/answer_09.answ"]
for a in range(4):
    path=test[a]
    code=pr.call(["testsGenerator.exe",path])
    if code==100:
        print ("Ошибка при создании теста")
    else:
        if code==404:
            print ("Ошибка при открытии файла")
        else:
            print("Tecт", a, "создан")
    code = pr.call(["optimization.exe", path])
    if code!=0:
        print("Ошибка при выполнении теста")
    if code==2:
        print("Ошибка при открытии файла 1")
    if code==3:
        print("Ошибка при открытии файла 2")
    path_to_res=result[a];
    path_to_answ=answer[a];
    code=pr.call(["checker.exe", path_to_res,path_to_answ])
    if code==0:
        print("Тест не пройден")
    if code==1:
        print("Тест пройден")
    if code==2:
        print("Результат не найден")
    if code==3:
        print("Ответ не найден")
    if code==4:
        print("Недостаточно аргументов")


