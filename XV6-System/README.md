# XV6-System

Project 3 – Digging into Xv6 - System Calls
Overview:
In this project we will be examining the process table and scheduler in the Xv6 operating system and adding a system call and user program which tests the system.

Background:
This project can be completed on the class VM. All required software except xv6 is installed for you.

Resources:
About Xv6: https://pdos.csail.mit.edu/6.828/2012/xv6.htmlLinks to an external site.
Xv6 Manual: https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf
Required tasks
Part 0: Create a repository for the project and obtain required software
On gitlab.eecis.udel.edu, create a new repository called "xv6". Clone that repository (using SSH) to cisc361.cis.udel.edu. In the clone on cisc361.cis.udel.edu, run the command tar -xf /usa/roosen/xv6.tar. Then use "git add . ; git commit" to add the xv6 code to your project.

Once you've created your initial base repository, you can compile and run xv6 using "make qemu-nox". This will boot the Xv6 OS and launch a simple shell. Exit the shell using ctrl-a x

Note: If you want to run this on your own unix/linux system (wsl/mac) you will need to install qemu on your system. You can clone the xv6 repository directly from https://gitlab.eecis.udel.edu/silber/xv6-public.git, Links to an external site.but it would probably be better to initialize your repository as above and then clone that.

Part 1: Understanding the Scheduler
Review the scheduler() function in proc.c. Add a line to print out the current process name and pid in each loop of the scheduler (i.e., "process [%s:%d] is running").

Part 2: A user program in your xv6 operating system
Instructions and an example of adding a user program to Xv6 can be found here: http://recolog.blogspot.com/2016/03/adding-user-program-to-xv6.htmlLinks to an external site.

Add a program called hello that prints, "Hello, my name is <name>.", substituting your name for <name>

Part 3: Adding a system call
Detailed instructions and an example of adding a system call can be found here:

https://medium.com/@viduniwickramarachchi/add-a-new-system-call-in-xv6-5486c2437573Links to an external site.
http://recolog.blogspot.com/2016/03/a-new-system-call-to-xv6.htmlLinks to an external site.
Add a system call crsp() into Xv6, which prints out the current running and sleeping processes. Review carefully how the scheduler() function (line 323 of proc.c) works, as system call crsp() will loop over the same process table looking for both RUNNING and SLEEPING processes. Given that the process table (ptable) is a shared data structure, defined inside proc.c, within the Xv6 kernel, it has to be protected by a lock! See how scheduler() uses the lock associated with ptable and access process state of processes in ptable.

Part 4: Using crsp() in a program
Write a user program named ps (compiled from a file called ps.c) to test the invocation of crsp(). It should output something like the following:
