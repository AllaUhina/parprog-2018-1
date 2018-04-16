import subprocess as pr
import sys
import random as rm

tasks = ["../tasks/task_00.task", "../tasks/task_01.task", "../tasks/task_02.task",
         "../tasks/task_03.task", "../tasks/task_04.task", "../tasks/task_05.task",
         "../tasks/task_06.task", "../tasks/task_07.task", "../tasks/task_08.task",
         "../tasks/task_09.task"]

answers = ["../answers/answer_00.answ", "../answers/answer_01.answ", "../answers/answer_02.answ",
           "../answers/answer_03.answ", "../answers/answer_04.answ", "../answers/answer_05.answ"
           , "../answers/answer_06.answ", "../answers/answer_07.answ", "../answers/answer_08.answ"
           , "../answers/answer_09.answ"]

results = ["../results/result_00.rslt", "../results/result_01.rslt", "../results/result_02.rslt",
           "../results/result_03.rslt", "../results/result_04.rslt", "../results/result_05.rslt",
           "../results/result_06.rslt", "../results/result_07.rslt", "../results/result_08.rslt",
           "../results/result_09.rslt"]


task = 1
if (len(sys.argv) > 1):
    task = int(sys.argv[1])
else:
    task = rm.randint(0, 9)

print("answersmaker is doing...")
code = pr.call("../bin/answersmaker")
if code != 0:
    print("error of answersmaker")
else:
    print("answersmaker is done.")

print("testsgenerator is doing...")
code = pr.call(["python3", "../testsgenerator/testsgenerator.py", str(task)])
if code != 0:
    print("error of testsgenerator")
else:
    print("testsgenerator is done.")

print("checker is doing...")
code = pr.call(["../bin/checker", tasks[task], answers[task], results[task]])
if code != 0:
    print("error of checker")
else:
    print("checker is done.")
