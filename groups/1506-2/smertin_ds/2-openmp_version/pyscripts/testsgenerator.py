import subprocess as pr
import sys
import random as rm

tasks = ["../bin/tasks/task_00", "../bin/tasks/task_01", "../bin/tasks/task_02",
         "../bin/tasks/task_03", "../bin/tasks/task_04", "../bin/tasks/task_05",
         "../bin/tasks/task_06", "../bin/tasks/task_07", "../bin/tasks/task_08",
         "../bin/tasks/task_09"]

print("testsmaker is doing...")
code = pr.call("../bin/executables/tasksmaker")
if code != 0:
    print("error of tasksmaker")
else:
    print("testsmaker is done.")

path = "../bin/tasks/task_01"
if (len(sys.argv) > 1):
    ind = int(sys.argv[1])
    path = tasks[ind]
else:
    path = rm.choice(tasks)

print("gsa is doing with " + path)
code = pr.call(["../bin/executables/gsa", path])
if code != 0:
    print("\n\n\terror of gsa\n\n")
else:
    print("gsa is done.")
