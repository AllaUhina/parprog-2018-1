import subprocess as pr

code = pr.call("../bin/tasksmaker.sh")
if code != 0:
    print("error of tasksmaker")
#generator
code = pr.call(["../bin/gsa.sh", "../tasks/task_01.task"])
if code != 0:
    print("error of gsa")
