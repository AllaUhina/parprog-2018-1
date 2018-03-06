import subprocess as pr
import sys
import random as rm

tasks = ["../tasks/task_00.task", "../tasks/task_01.task", "../tasks/task_02.task",
         "../tasks/task_03.task", "../tasks/task_04.task"]

print("testsmaker is doing...")
code = pr.call("../bin/tasksmaker")
if code != 0:
    print("error of tasksmaker")
else:
    print("testsmaker is done.")

path = "../tasks/task_01.task"
if (len(sys.argv) > 1):
    ind = int(sys.argv[1])
    path = tasks[ind]
else:
    path = rm.choice(tasks)

print("gsa is doing with " + path)
code = pr.call(["../bin/gsa", path])
if code != 0:
    print("error of gsa")
else:
    print("gsa is done.")
