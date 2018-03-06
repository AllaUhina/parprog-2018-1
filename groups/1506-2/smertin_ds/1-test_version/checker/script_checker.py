import subprocess as pr
import sys
import random as rm

tasks = ["../tasks/task_00.task", "../tasks/task_01.task", "../tasks/task_02.task",
         "../tasks/task_03.task", "../tasks/task_04.task"]

answers = ["../answers/answer_00.answ", "../answers/answer_01.answ",
           "../answers/answer_02.answ", "../answers/answer_03.answ", "../answers/answer_04.answ"]
           
results = ["../results/result_00.rslt", "../results/result_01.rslt",
           "../results/result_02.rslt", "../results/result_03.rslt", "../results/result_04.rslt"]


task = 1
if (len(sys.argv) > 1):
    task = int(sys.argv[1])
else:
    task = rm.randint(0, 4)

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
