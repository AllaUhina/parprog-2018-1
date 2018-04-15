import subprocess as pr
import sys
import random as rm

tasks = ["../bin/tasks/task_00", "../bin/tasks/task_01", "../bin/tasks/task_02",
         "../bin/tasks/task_03", "../bin/tasks/task_04", "../bin/tasks/task_05",
         "../bin/tasks/task_06", "../bin/tasks/task_07", "../bin/tasks/task_08",
         "../bin/tasks/task_09"]

answers = ["../bin/answers/answer_00", "../bin/answers/answer_01", "../bin/answers/answer_02",
           "../bin/answers/answer_03", "../bin/answers/answer_04", "../bin/answers/answer_05"
           , "../bin/answers/answer_06", "../bin/answers/answer_07", "../bin/answers/answer_08"
           , "../bin/answers/answer_09"]

results = ["../bin/results/result_00", "../bin/results/result_01", "../bin/results/result_02",
           "../bin/results/result_03", "../bin/results/result_04", "../bin/results/result_05",
           "../bin/results/result_06", "../bin/results/result_07", "../bin/results/result_08",
           "../bin/results/result_09"]


print("answersmaker is doing...")
code = pr.call("../bin/executables/answersmaker")
if code != 0:
    print("error of answersmaker")
else:
    print("answersmaker is done.")

for task in range(10):
    print("testsgenerator is doing...")
    code = pr.call(["python3", "./testsgenerator.py", str(task)])
    if code != 0:
        print("error of testsgenerator")
    else:
        print("testsgenerator is done.")

    print("doing...")
    code = pr.call(["../bin/executables/checker", tasks[task], answers[task], results[task]])
    if code != 0:
        print("error.")
    else:
        print("done.")
